#include "ogl-transform-3d-parameter.h"
#include <rendering/resources/ogl-rendering-rule.h>
#include <rendering/ogl-renderer.h>

OGLTransform3DParameter::OGLTransform3DParameter(OGLRenderer& renderer) :
	OGLRendererUser(renderer)
{}

void OGLTransform3DParameter::Bind()
{
	Renderer().RenderParametersState().transform3D = this;
}

Transform3D& OGLTransform3DParameter::Transform()
{
	return m_transform;
}
