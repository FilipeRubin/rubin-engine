#include "ogl-scene-lighting-parameter.h"
#include <rendering/ogl-renderer.h>
#include <logging/log-macros.h>

OGLSceneLightingParameter::OGLSceneLightingParameter(OGLRenderer& renderer, size_t directionalLightCount) :
    OGLRendererUser(renderer),
    m_directionallights(FixedArray<DirectionalLight>(directionalLightCount))
{}

void OGLSceneLightingParameter::Bind()
{
    GetRenderer().RenderParametersState().sceneLighting = this;
}

Color& OGLSceneLightingParameter::AmbientLight()
{
    return m_ambientLight;
}

FixedArray<DirectionalLight>& OGLSceneLightingParameter::DirectionalLights()
{
    return m_directionallights;
}
