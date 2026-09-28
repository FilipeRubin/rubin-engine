#include "ogl-transform-2d-parameter.h"
#include "implementation/ogl-render-parameter-implementation.h"
#include <rendering/ogl-renderer.h>
#include <rendering/ogl-shader-constants.h>

OGLTransform2DParameter::OGLTransform2DParameter(OGLRenderer& renderer) :
    OGLRendererUser(renderer),
	m_impl(new OGLRenderParameterImplementation([](OGLRenderer& renderer, OGLShaderProgram& program, IRenderParameter* param) {
		auto& t = static_cast<OGLTransform2DParameter*>(param)->Transform();
		using namespace OGLShaderConstants;
		Matrix3x3 model = Matrix3x3::Model(t.position, t.rotation, t.scale);
		program.SetUniform(MODEL, model);
	}, renderer))
{}

OGLTransform2DParameter::~OGLTransform2DParameter()
{
    delete m_impl;
}

void OGLTransform2DParameter::Bind()
{
    Renderer().RenderParametersState().transform2D = this;
	if (auto rr = Renderer().GetCurrentRenderingRule())
	{
		auto& impl = *static_cast<OGLRenderParameterImplementation*>(GetImplementation());
		impl.SetUniform(rr->ShaderProgram(), this);
	}
}

Transform2D& OGLTransform2DParameter::Transform()
{
    return m_transform;
}

IRenderParameterImplementation* OGLTransform2DParameter::GetImplementation()
{
	return m_impl;
}
