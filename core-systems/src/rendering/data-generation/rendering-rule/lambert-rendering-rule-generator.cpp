#include "descriptor/implementation/ogl-rendering-rule-descriptor-implementation.h"
#include <rendering/ogl-renderer.h>
#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>
#include <rendering/ogl-shader-constants.h>
#include <format>

LambertRenderingRuleGenerator::LambertRenderingRuleGenerator(const SceneLightingDescriptor& lightingDescriptor) :
    m_lightingDescriptor(lightingDescriptor)
{}

RenderingRuleDescriptor LambertRenderingRuleGenerator::GenerateDescriptor(IRenderer& renderer) const
{
    RenderingRuleDescriptor result;

    auto& impl = *static_cast<OGLRenderingRuleDescriptorImplementation*>(result.GetImplementation());
    using namespace OGLShaderConstants;

    impl.VertexSource() = std::format(R"(
#version 460 core

layout(location=0) in vec3 v_in_pos;
layout(location=1) in vec3 v_in_nor;
layout(location=2) in vec2 v_in_uv;

uniform mat4 {0}; // projection view
uniform mat4 {1}; // model

out vec2 v_out_uv;
out vec3 v_out_nor;

void main()
{{
    gl_Position = {0} * {1} * vec4(v_in_pos, 1.0);
    v_out_uv = v_in_uv;
    v_out_nor = mat3(transpose(inverse({1}))) * v_in_nor;
}}
)", PROJECTION_VIEW, MODEL);

    impl.FragmentSource() = std::format(R"(
#version 460 core
#define NUM_DIRECTIONAL_LIGHTS {0}

struct DirectionalLight
{{
    vec4 {1}; // color
    vec3 {2}; // direction
}};

in vec2 v_out_uv;
in vec3 v_out_nor;

uniform sampler2D {3}; // texture
uniform vec4 {4}; // ambient light
uniform DirectionalLight {5}[NUM_DIRECTIONAL_LIGHTS]; // directional lights

out vec4 f_color;

vec4 calculateDirectionalLights()
{{
    vec4 result = vec4(0.0, 0.0, 0.0, 0.0);

    for (int i = 0; i < NUM_DIRECTIONAL_LIGHTS; i++)
    {{
        float directionalLightAmount = max(dot(normalize(v_out_nor), normalize(-{5}[i].{2})), 0.0);
        result += {5}[i].{1} * directionalLightAmount;
    }}

    return result;
}}

void main()
{{
    f_color = texture({3}, v_out_uv) * (calculateDirectionalLights() + {4});
}}
)",
        m_lightingDescriptor.directionalLightCount,
        LIGHTING_DIRECTIONAL_STRUCT_COLOR,
        LIGHTING_DIRECTIONAL_STRUCT_DIRECTION,
        TEXTURE,
        LIGHTING_AMBIENT,
        LIGHTING_DIRECTIONAL_ARRAY
    );

    OGLRenderParametersState& params = static_cast<OGLRenderer&>(renderer).RenderParametersState();
    impl.Parameters() = {
        (IRenderParameter**)&params.transform3D,
        (IRenderParameter**)&params.camera3D,
        (IRenderParameter**)&params.sceneLighting
    };

    return result;
}
