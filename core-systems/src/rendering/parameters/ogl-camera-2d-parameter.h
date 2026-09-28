#pragma once
#include <rendering/parameters/i-camera-2d-parameter.h>
#include <rendering/ogl-renderer-user.h>

class OGLCamera2DParameter : public ICamera2DParameter, public OGLRendererUser
{
public:
	OGLCamera2DParameter(OGLRenderer& renderer);
	~OGLCamera2DParameter();
	void Bind() override;
	Camera2D& Camera() override;
protected:
	IRenderParameterImplementation* GetImplementation() override;
private:
	Camera2D m_camera;
	IRenderParameterImplementation* m_impl;
};
