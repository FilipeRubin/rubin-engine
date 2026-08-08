#include "ogl-shader-source-builder.h"
#include "ogl-shader-constants.h"
#include <format>

OGLShaderSourceBuilder::OGLShaderSourceBuilder(OGLShaderKey key) :
    m_key(key)
{}

std::string OGLShaderSourceBuilder::GenerateVertexSource() const
{
    std::string version = GenerateVersion();
    std::string defines = GenerateDefines();
    std::string vertexLayout = R"(
layout(location=0) in vec3 v_in_pos;
layout(location=1) in vec3 v_in_nor;
layout(location=2) in vec2 v_in_uv;
)";
    std::string outputs = R"(
out vec2 v_out_uv;
out vec3 v_out_nor;
)";
    std::string uniforms = GenerateUniforms();
    std::string logic = R"(
void main()
{
	gl_Position =
#if USE_PROJECTION_VIEW
        u_projectionView *
#endif
#if USE_MODEL_MATRIX
        u_model *
#endif
        vec4(v_in_pos, 1.0);
	v_out_uv = v_in_uv;
	v_out_nor =
#if USE_MODEL_MATRIX
        mat3(transpose(inverse(u_model))) *
#endif
        v_in_nor;
}
)";
    return version + defines + vertexLayout + outputs + uniforms + logic;
}

std::string OGLShaderSourceBuilder::GenerateFragmentSource() const
{
    std::string version = GenerateVersion();
    std::string defines = GenerateDefines();
    std::string input = R"(
in vec2 v_out_uv;
in vec3 v_out_nor;
)";
    std::string output = "out vec4 f_color;\n";
    std::string uniforms = GenerateUniforms();
    std::string logic = R"(
vec4 calculateDirectionalLight()
{
    float directionalLightAmount = max(dot(normalize(v_out_nor), normalize(-u_directionalLightDirection)), 0.0);
    vec4 directionalLightColor = u_directionalLightDiffuse * directionalLightAmount;
	return u_ambientLight + directionalLightColor;
}

void main()
{
	f_color =
#if USE_DIRECTIONAL_LIGHT
        calculateDirectionalLight() *
#endif
        texture(u_texture, v_out_uv);
}
)";
    return version + defines + input + output + uniforms + logic;
}

std::string OGLShaderSourceBuilder::GenerateVersion() const
{
    return "#version 460 core\n";
}

std::string OGLShaderSourceBuilder::GenerateDefines() const
{
    using namespace OGLShaderConstants::Define;
    const RenderingRuleDescriptor& d = m_key.GetDescriptor();
    return
        std::format("#define {} {:d}\n", USE_DIRECTIONAL_LIGHT, d.useDirectionalLight) +
        std::format("#define {} {:d}\n", USE_VIEW_PROJECTION, d.useViewProjection) +
        std::format("#define {} {:d}\n", USE_MODEL_MATRIX, d.useModelMatrix);
}

std::string OGLShaderSourceBuilder::GenerateUniforms() const
{
    using namespace OGLShaderConstants::Uniform;
    return
        std::format("uniform mat4 {};\n", MODEL) +
        std::format("uniform mat4 {};\n", PROJECTION_VIEW) +
        std::format("uniform sampler2D {};\n", TEXTURE) +
        std::format("uniform vec4 {};\n", DIR_LIGHT_AMBIENT) +
        std::format("uniform vec4 {};\n", DIR_LIGHT_DIFFUSE) +
        std::format("uniform vec3 {};\n", DIR_LIGHT_DIRECTION);
}
