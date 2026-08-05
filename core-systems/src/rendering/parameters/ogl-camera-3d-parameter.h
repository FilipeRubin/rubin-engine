#pragma once
#include <rendering/parameters/i-camera-3d-parameter.h>
#include <rendering/ogl-renderer-user.h>

class OGLCamera3DParameter : public ICamera3DParameter, public OGLRendererUser
{
public:
	OGLCamera3DParameter(OGLRenderer& renderer);
	void Bind() override;
	Camera3D& Camera() override;
private:
	Camera3D m_camera;
};
