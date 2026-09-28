#include "ogl-camera-2d-parameter.h"
#include "implementation/ogl-render-parameter-implementation.h"
#include <math/matrix4x4.h>
#include <rendering/ogl-renderer.h>
#include <rendering/ogl-shader-constants.h>
#include <ogl.h>

OGLCamera2DParameter::OGLCamera2DParameter(OGLRenderer& renderer) :
	OGLRendererUser(renderer),
	m_impl(new OGLRenderParameterImplementation([](OGLRenderer& renderer, OGLShaderProgram& program, IRenderParameter* param) {
		auto& c = static_cast<OGLCamera2DParameter*>(param)->Camera();
		Matrix3x3 projection = Matrix3x3::ScreenToNDC((Vector2)renderer.GetViewportSize());
		Matrix3x3 view = Matrix3x3::View(c.position, -c.rotation);
		Matrix3x3 projectionView = projection * view;
		using namespace OGLShaderConstants;
		program.SetUniform(PROJECTION_VIEW, projectionView);
	}, renderer))
{}

OGLCamera2DParameter::~OGLCamera2DParameter()
{
	delete m_impl;
}

void OGLCamera2DParameter::Bind()
{
	Renderer().RenderParametersState().camera2D = this;
	if (auto rr = Renderer().GetCurrentRenderingRule())
	{
		auto& impl = *static_cast<OGLRenderParameterImplementation*>(GetImplementation());
		impl.SetUniform(rr->ShaderProgram(), this);
	}
}

Camera2D& OGLCamera2DParameter::Camera()
{
	return m_camera;
}

IRenderParameterImplementation* OGLCamera2DParameter::GetImplementation()
{
	return m_impl;
}
