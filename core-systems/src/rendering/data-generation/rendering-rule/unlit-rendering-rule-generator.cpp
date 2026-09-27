#include "descriptor/implementation/ogl-rendering-rule-descriptor-implementation.h"
#include <rendering/ogl-renderer.h>
#include <rendering/data-generation/rendering-rule/unlit-rendering-rule-generator.h>
#include <rendering/ogl-shader-constants.h>
#include <format>

RenderingRuleDescriptor UnlitRenderingRuleGenerator::GenerateDescriptor(IRenderer& renderer) const
{
    RenderingRuleDescriptor result;

    auto& impl = *static_cast<OGLRenderingRuleDescriptorImplementation*>(result.GetImplementation());
    using namespace OGLShaderConstants;

    impl.VertexSource() = std::format(R"(
#version 460 core

layout(location=0) in vec3 v_in_pos;
layout(location=2) in vec2 v_in_uv;

uniform mat4 {0}; // projection view
uniform mat4 {1}; // model

out vec2 v_out_uv;

void main()
{{
    gl_Position = {0} * {1} * vec4(v_in_pos, 1.0);
    v_out_uv = v_in_uv;
}}
)", PROJECTION_VIEW, MODEL);

    impl.FragmentSource() = std::format(R"(
#version 460 core

in vec2 v_out_uv;

uniform sampler2D {0};

out vec4 f_color;

void main()
{{
    f_color = texture({0}, v_out_uv);
}}
)", TEXTURE);

    OGLRenderParametersState& params = static_cast<OGLRenderer&>(renderer).RenderParametersState();
    impl.Parameters() = {
        (IRenderParameter**)&params.transform3D,
        (IRenderParameter**)&params.camera3D
    };

    return result;
}
