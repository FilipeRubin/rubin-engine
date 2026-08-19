#include "ogl-graphics-backend.h"
#include "ogl.h"
#include "rendering/ogl-renderer.h"
#include "rendering/ogl-renderer-resource-manager.h"
#include <logging/log-macros.h>
#ifdef _WIN32
#include <Windows.h>

#ifdef ERROR
#undef ERROR
#endif

unsigned int OGLGraphicsBackend::s_instanceCount = 0U;
OGLGraphicsBackend* OGLGraphicsBackend::s_current = nullptr;

OGLGraphicsBackend* OGLGraphicsBackend::GetCurrent()
{
	return s_current;
}

OGLGraphicsBackend::OGLGraphicsBackend(const void* windowHandle) :
	m_windowHandle(windowHandle),
	m_oglContext(nullptr),
	m_hdc(nullptr),
	m_renderer(nullptr)
{
}

bool OGLGraphicsBackend::TryInitialize(IGraphicsBackend* sharedBackend)
{
	if (m_oglContext != nullptr)
	{
		LOG_WARNING("OpenGL graphics backend initialization was requested more than once.");
		return true;
	}

	if (not TryIncrement())
	{
		LOG_ERROR("Failed to load OpenGL before initializing the graphics backend.");
		return false;
	}
	
	m_hdc = GetDC((HWND)m_windowHandle);

	HGLRC sharedContext = nullptr;
	if (sharedBackend)
	{
		sharedContext = (HGLRC)static_cast<OGLGraphicsBackend*>(sharedBackend)->m_oglContext;
	}

	m_oglContext = CreateContext(m_windowHandle, sharedContext);
	if (m_oglContext == nullptr)
	{
		LOG_ERROR("Failed to initialize the OpenGL graphics backend.");
		Finalize();
		return false;
	}

	m_renderer = new OGLRenderer(this);

	SetDefaultRendererSettings();
	LOG_INFO("OpenGL graphics backend initialized.");

	return true;
}

void OGLGraphicsBackend::MakeCurrent() const
{
	wglMakeCurrent((HDC)m_hdc, (HGLRC)m_oglContext);
	s_current = const_cast<OGLGraphicsBackend*>(this);
	OGLRendererResourceManager& rm = static_cast<OGLRendererResourceManager&>(Renderer().ResourceManager());
	rm.Update();
}

void OGLGraphicsBackend::SwapBuffers() const
{
	::SwapBuffers((HDC)m_hdc);
}

void OGLGraphicsBackend::Finalize()
{
	LOG_INFO("Finalizing OpenGL graphics backend.");
	delete m_renderer;

	if (wglGetCurrentContext() == m_oglContext)
	{
		wglMakeCurrent((HDC)m_hdc, NULL);
	}

	wglDeleteContext((HGLRC)m_oglContext);

	ReleaseDC((HWND)m_windowHandle, (HDC)m_hdc);

	Decrement();
}

IRenderer& OGLGraphicsBackend::Renderer() const
{
	return *m_renderer;
}

bool OGLGraphicsBackend::TryIncrement()
{
	if (s_instanceCount == 0U)
	{
		if (not TryLoadOGL())
		{
			return false;
		}
	}
	s_instanceCount++;
	LOG_DEBUG("OpenGL graphics backend instance count: " + std::to_string(s_instanceCount) + ".");
	return true;
}

void OGLGraphicsBackend::Decrement()
{
	s_instanceCount--;
	LOG_DEBUG("OpenGL graphics backend instance count: " + std::to_string(s_instanceCount) + ".");
	if (s_instanceCount == 0U)
	{
		UnloadOGL();
	}
}

void OGLGraphicsBackend::SetDefaultRendererSettings()
{
	HGLRC previousContext = wglGetCurrentContext();
	wglMakeCurrent((HDC)m_hdc, (HGLRC)m_oglContext);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	wglMakeCurrent((HDC)m_hdc, previousContext);
}

#endif // _WIN32
