#include "graphics-window.h"
#include <algorithm>
#include <iostream>

vector<GraphicsWindow*> GraphicsWindow::s_instances = vector<GraphicsWindow*>();

bool GraphicsWindow::IsAnyWindowOpen()
{
	for (GraphicsWindow*& w : s_instances)
	{
		if (not w->ShouldClose())
		{
			return true;
		}
	}
	return false;
}

bool GraphicsWindow::TryInitialize(const WindowParameters& params, IGraphicsBackend* sharedBackend)
{
	m_window = unique_ptr<IWindow>(CoreSystems::CreateWindow());
	if (not m_window->TryInitialize(params))
	{
		return false;
	}

	m_graphics = unique_ptr<IGraphicsBackend>(CoreSystems::CreateGraphicsBackend(m_window.get()));
	if (not m_graphics->TryInitialize(sharedBackend))
	{
		m_window->Finalize();
		return false;
	}

	IRenderer& renderer = this->m_graphics->Renderer();
	m_window->SetWindowSizeCallback([&renderer](const Dimensions& size) {renderer.SetViewportSize({ size.width, size.height }); });

	s_instances.emplace_back(this);

	return true;
}

bool GraphicsWindow::ShouldClose() const
{
	return m_window->ShouldClose();
}

void GraphicsWindow::BeginDraw() const
{
	m_graphics->MakeCurrent();
	m_graphics->Renderer().ClearScreen();
}

void GraphicsWindow::EndDraw() const
{
	m_graphics->SwapBuffers();
	m_window->Process();
}

bool GraphicsWindow::IsInitialized() const
{
	return m_window->IsInitialized();
}

void GraphicsWindow::Finalize()
{
	using std::remove;

	if (not IsInitialized())
	{
		return;
	}

	m_graphics->Finalize();
	m_window->Finalize();
	s_instances.erase(remove(s_instances.begin(), s_instances.end(), this), s_instances.end());
}

IWindow& GraphicsWindow::Window() const
{
	return *m_window.get();
}

IGraphicsBackend& GraphicsWindow::GraphicsBackend() const
{
	return *m_graphics.get();
}
