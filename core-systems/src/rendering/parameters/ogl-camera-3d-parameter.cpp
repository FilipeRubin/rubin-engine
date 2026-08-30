#include "ogl-camera-3d-parameter.h"
#include <rendering/ogl-renderer.h>

OGLCamera3DParameter::OGLCamera3DParameter(OGLRenderer& renderer) :
	OGLRendererUser(renderer)
{}

void OGLCamera3DParameter::Bind()
{
	Renderer().RenderParametersState().camera3D = this;
}

Camera3D& OGLCamera3DParameter::Camera()
{
	return m_camera;
}
