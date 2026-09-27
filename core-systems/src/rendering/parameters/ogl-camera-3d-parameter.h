#pragma once
#include <rendering/parameters/i-camera-3d-parameter.h>
#include <rendering/ogl-renderer-user.h>

class OGLCamera3DParameter : public ICamera3DParameter, public OGLRendererUser
{
public:
	OGLCamera3DParameter(OGLRenderer& renderer);
	~OGLCamera3DParameter();
	void Bind() override;
	Camera3D& Camera() override;
protected:
	IRenderParameterImplementation* GetImplementation() override;
private:
	Camera3D m_camera;
	IRenderParameterImplementation* m_impl;
};
