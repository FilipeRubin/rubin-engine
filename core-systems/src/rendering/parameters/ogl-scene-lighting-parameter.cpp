#include "ogl-scene-lighting-parameter.h"
#include "implementation/ogl-render-parameter-implementation.h"
#include <rendering/ogl-renderer.h>
#include <rendering/ogl-shader-constants.h>
#include <logging/log-macros.h>
#include <format>

OGLSceneLightingParameter::OGLSceneLightingParameter(OGLRenderer& renderer, const SceneLightingDescriptor& lightingDescriptor) :
    OGLRendererUser(renderer),
    m_directionallights(FixedArray<DirectionalLight>(lightingDescriptor.directionalLightCount)),
    m_impl(new OGLRenderParameterImplementation([](OGLRenderer& renderer, OGLShaderProgram& program, IRenderParameter* param) {
        auto& a = static_cast<OGLSceneLightingParameter*>(param)->AmbientLight();
        auto& d = static_cast<OGLSceneLightingParameter*>(param)->DirectionalLights();
        using namespace OGLShaderConstants;
        program.SetUniform(LIGHTING_AMBIENT, a);
        for (size_t i = 0; i < d.GetSize(); i++)
        {
            std::string arrayName = std::format("{0}[{1}]", LIGHTING_DIRECTIONAL_ARRAY, std::to_string(i));
            std::string color = arrayName + '.' + LIGHTING_DIRECTIONAL_STRUCT_COLOR;
            std::string direction = arrayName + '.' + LIGHTING_DIRECTIONAL_STRUCT_DIRECTION;
            program.SetUniform(color.c_str(), d[i].color);
            program.SetUniform(direction.c_str(), d[i].direction * d[i].intensity);
        }
    }, renderer))
{}

OGLSceneLightingParameter::~OGLSceneLightingParameter()
{
    delete m_impl;
}

void OGLSceneLightingParameter::Bind()
{
    Renderer().RenderParametersState().sceneLighting = this;
    if (auto rr = Renderer().GetCurrentRenderingRule())
    {
        auto& impl = *static_cast<OGLRenderParameterImplementation*>(GetImplementation());
        impl.SetUniform(rr->ShaderProgram(), this);
    }
}

Color& OGLSceneLightingParameter::AmbientLight()
{
    return m_ambientLight;
}

FixedArray<DirectionalLight>& OGLSceneLightingParameter::DirectionalLights()
{
    return m_directionallights;
}

IRenderParameterImplementation* OGLSceneLightingParameter::GetImplementation()
{
    return m_impl;
}
