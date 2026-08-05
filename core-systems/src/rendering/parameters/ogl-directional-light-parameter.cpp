#include "ogl-directional-light-parameter.h"
#include <rendering/ogl-renderer.h>

OGLDirectionalLightParameter::OGLDirectionalLightParameter(OGLRenderer& renderer) :
    OGLRendererUser(renderer)
{}

void OGLDirectionalLightParameter::Bind()
{
    GetRenderer().RenderParametersState().directionalLight = this;
}

DirectionalLight& OGLDirectionalLightParameter::Light()
{
    return m_light;
}
