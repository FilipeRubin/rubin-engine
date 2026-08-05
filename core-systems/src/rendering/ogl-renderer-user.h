#pragma once

class OGLRenderer;

class OGLRendererUser
{
public:
	OGLRendererUser(OGLRenderer& renderer);
	virtual ~OGLRendererUser() = default;
protected:
	OGLRenderer& GetRenderer();
private:
	OGLRenderer& m_renderer;
};
