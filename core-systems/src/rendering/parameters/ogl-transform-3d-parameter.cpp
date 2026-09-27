#include "ogl-transform-3d-parameter.h"
#include "implementation/ogl-render-parameter-implementation.h"
#include <rendering/resources/ogl-rendering-rule.h>
#include <rendering/ogl-renderer.h>
#include <rendering/ogl-shader-constants.h>

OGLTransform3DParameter::OGLTransform3DParameter(OGLRenderer& renderer) :
	OGLRendererUser(renderer),
	m_impl(new OGLRenderParameterImplementation([](OGLRenderer& renderer, OGLShaderProgram& program, IRenderParameter* param) {
		auto& t = static_cast<OGLTransform3DParameter*>(param)->Transform();
		using namespace OGLShaderConstants;
		Matrix4x4 model = Matrix4x4::Model(t.position, t.rotation, t.scale);
		program.SetUniform(MODEL, model);
	}, renderer))
{}

OGLTransform3DParameter::~OGLTransform3DParameter()
{
	delete m_impl;
}

void OGLTransform3DParameter::Bind()
{
	Renderer().RenderParametersState().transform3D = this;
	if (auto rr = Renderer().GetCurrentRenderingRule())
	{
		auto& impl = *static_cast<OGLRenderParameterImplementation*>(GetImplementation());
		impl.SetUniform(rr->ShaderProgram(), this);
	}
}

Transform3D& OGLTransform3DParameter::Transform()
{
	return m_transform;
}

IRenderParameterImplementation* OGLTransform3DParameter::GetImplementation()
{
	return m_impl;
}
