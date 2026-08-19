#pragma once
#include <core-systems.h>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;

class GraphicsWindow
{
public:
	static bool IsAnyWindowOpen();
	bool TryInitialize(const WindowParameters& params, IGraphicsBackend* sharedBackend = nullptr);
	bool ShouldClose() const;
	void BeginDraw() const;
	void EndDraw() const;
	bool IsInitialized() const;
	void Finalize();
	IWindow& Window() const;
	IGraphicsBackend& GraphicsBackend() const;
private:
	static vector<GraphicsWindow*> s_instances;
	unique_ptr<IWindow> m_window;
	unique_ptr<IGraphicsBackend> m_graphics;
};
