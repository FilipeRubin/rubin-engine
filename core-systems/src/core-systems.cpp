#include <core-systems.h>
#include "win32-window.h"
#include "ogl-graphics-backend.h"
#include <logging/log-macros.h>

IWindow* CoreSystems::CreateWindow()
{
	LOG_DEBUG("Creating Win32 window.");
	return new Win32Window();
}

IGraphicsBackend* CoreSystems::CreateGraphicsBackend(IWindow* window)
{
	LOG_DEBUG("Creating OpenGL graphics backend.");
	Win32Window* win32Window = static_cast<Win32Window*>(window);
	return new OGLGraphicsBackend(win32Window->GetHandle(), window->GetSize());
}
