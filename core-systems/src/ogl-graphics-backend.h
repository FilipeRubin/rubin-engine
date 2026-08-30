#pragma once
#include <i-graphics-backend.h>

class OGLGraphicsBackend : public IGraphicsBackend
{
public:
	static OGLGraphicsBackend* GetCurrent();
	OGLGraphicsBackend(const void* windowHandle, Dimensions viewportSize);
	bool TryInitialize(IGraphicsBackend* sharedBackend = nullptr) override;
	void MakeCurrent() const override;
	void SwapBuffers() const override;
	void Finalize() override;
	IRenderer& Renderer() const override;
private:
	static unsigned int s_instanceCount;
	static OGLGraphicsBackend* s_current;
	static bool TryIncrement();
	static void Decrement();
	const void* m_windowHandle;
	const void* m_oglContext;
	void* m_hdc;
	IRenderer* m_renderer;
	Dimensions m_cachedStartingViewportSize;
	void SetDefaultRendererSettings();
};
