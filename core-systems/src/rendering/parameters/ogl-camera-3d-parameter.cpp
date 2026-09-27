#include "ogl-camera-3d-parameter.h"
#include "implementation/ogl-render-parameter-implementation.h"
#include <math/matrix4x4.h>
#include <rendering/ogl-renderer.h>
#include <rendering/ogl-shader-constants.h>
#include <ogl.h>

OGLCamera3DParameter::OGLCamera3DParameter(OGLRenderer& renderer) :
	OGLRendererUser(renderer),
	m_impl(new OGLRenderParameterImplementation([](OGLRenderer& renderer, OGLShaderProgram& program, IRenderParameter* param) {
		auto& c = static_cast<OGLCamera3DParameter*>(param)->Camera();
		Matrix4x4 projection = Matrix4x4::Perspective(c.aspectRatio, c.vFOV, c.zNear, c.zFar);
		Matrix4x4 view = Matrix4x4::View(-c.position, -c.rotation);
		Matrix4x4 projectionView = projection * view;
		using namespace OGLShaderConstants;
		program.SetUniform(PROJECTION_VIEW, projectionView);
	}, renderer))
{}

OGLCamera3DParameter::~OGLCamera3DParameter()
{
	delete m_impl;
}

void OGLCamera3DParameter::Bind()
{
	Renderer().RenderParametersState().camera3D = this;
	if (auto rr = Renderer().GetCurrentRenderingRule())
	{
		auto& impl = *static_cast<OGLRenderParameterImplementation*>(GetImplementation());
		impl.SetUniform(rr->ShaderProgram(), this);
	}
}

Camera3D& OGLCamera3DParameter::Camera()
{
	return m_camera;
}

IRenderParameterImplementation* OGLCamera3DParameter::GetImplementation()
{
	return m_impl;
}
