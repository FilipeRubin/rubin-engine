#pragma once

class OGLRenderer;

class OGLRendererUser
{
public:
	OGLRendererUser(OGLRenderer& renderer);
	virtual ~OGLRendererUser() = default;
protected:
	OGLRenderer& Renderer();
private:
	OGLRenderer& m_renderer;
};
