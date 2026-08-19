#include "ogl-scene-lighting-parameter.h"
#include <rendering/ogl-renderer.h>
#include <logging/log-macros.h>

OGLSceneLightingParameter::OGLSceneLightingParameter(OGLRenderer& renderer, const SceneLightingDescriptor& lightingDescriptor) :
    OGLRendererUser(renderer),
    m_directionallights(FixedArray<DirectionalLight>(lightingDescriptor.directionalLightCount))
{}

void OGLSceneLightingParameter::Bind()
{
    Renderer().RenderParametersState().sceneLighting = this;
}

Color& OGLSceneLightingParameter::AmbientLight()
{
    return m_ambientLight;
}

FixedArray<DirectionalLight>& OGLSceneLightingParameter::DirectionalLights()
{
    return m_directionallights;
}
