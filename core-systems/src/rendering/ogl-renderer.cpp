#include "ogl-renderer.h"
#include "ogl.h"
#include "ogl-renderer-parameter-manager.h"
#include "ogl-renderer-resource-manager.h"
#include <logging/log-macros.h>

OGLRenderer::OGLRenderer(OGLGraphicsBackend* backend) :
	m_currentRenderingRule(nullptr),
	m_parametersState(OGLRenderParametersState()),
	m_shaderCache(*this),
	m_parameterManager(new OGLRendererParameterManager(*this)),
	m_resourceManager(new OGLRendererResourceManager(backend, *this))
{
	LOG_INFO("OpenGL renderer created.");
}

OGLRenderer::~OGLRenderer()
{
	LOG_INFO("OpenGL renderer destroyed.");
	delete m_parameterManager;
	delete m_resourceManager;
}

void OGLRenderer::ClearScreen() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLRenderer::SetClearColor(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void OGLRenderer::SetViewportSize(const Dimensions& size)
{
	glViewport(0, 0, size.width, size.height);
}

IRendererParameterManager& OGLRenderer::ParameterManager() const
{
	return *m_parameterManager;
}

IRendererResourceManager& OGLRenderer::ResourceManager() const
{
	return *m_resourceManager;
}

OGLRenderingRule* OGLRenderer::GetCurrentRenderingRule() const
{
	return m_currentRenderingRule;
}

void OGLRenderer::SetCurrentRenderingRule(OGLRenderingRule* renderingRule)
{
	m_currentRenderingRule = renderingRule;
}

OGLRenderParametersState& OGLRenderer::RenderParametersState()
{
	return m_parametersState;
}

OGLShaderProgramCache& OGLRenderer::ShaderCache()
{
	return m_shaderCache;
}
