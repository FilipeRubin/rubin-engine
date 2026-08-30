#include "ogl-transform-2d-parameter.h"
#include <rendering/ogl-renderer.h>

OGLTransform2DParameter::OGLTransform2DParameter(OGLRenderer& renderer) :
    OGLRendererUser(renderer)
{}

void OGLTransform2DParameter::Bind()
{
    Renderer().RenderParametersState().transform2D = this;
}

Transform2D& OGLTransform2DParameter::Transform()
{
    return m_transform;
}
