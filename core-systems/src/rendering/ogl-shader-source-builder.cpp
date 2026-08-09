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
    std::string vertexLayout = GenerateVertexLayout();
    std::string output = GenerateVertexOutput();
    std::string uniforms = GenerateVertexUniforms();
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
    return version + defines + vertexLayout + output + uniforms + logic;
}

std::string OGLShaderSourceBuilder::GenerateFragmentSource() const
{
    std::string version = GenerateVersion();
    std::string defines = GenerateDefines();
    std::string structs = GenerateFragmentStructs();
    std::string input = GenerateFragmentInput();
    std::string output = GenerateFragmentOutput();
    std::string uniforms = GenerateFragmentUniforms();
    std::string logic = R"(
#if NUM_DIRECTIONAL_LIGHTS != 0
vec4 calculatetDirectionalLightsColor()
{
    vec4 result;
    for (int i = 0; i < NUM_DIRECTIONAL_LIGHTS; i++)
    {
        float directionalLightAmount = max(dot(normalize(v_out_nor), normalize(-u_directionalLights[i].direction)), 0.0);
        result += u_directionalLights[i].diffuse * directionalLightAmount;
    }
	return result;
}
#endif

void main()
{
	f_color =
#if USE_LIGHTING
        u_ambientLight *
    #if NUM_DIRECTIONAL_LIGHTS != 0
        calculatetDirectionalLightsColor() *
    #endif
#endif
        texture(u_texture, v_out_uv);
}
)";
    return version + defines + structs + input + output + uniforms + logic;
}

std::string OGLShaderSourceBuilder::GenerateVersion() const
{
    return "#version 460 core\n";
}

std::string OGLShaderSourceBuilder::GenerateDefines() const
{
    using namespace OGLShaderConstants::Define;
    const RenderingRuleDescriptor& d = m_key.GetDescriptor();
    size_t numDirectionalLights = 0U;
    if (d.sceneLighting != nullptr) numDirectionalLights = d.sceneLighting->m_directionalLightCount;
    return
        std::format("#define {} {:d}\n", USE_LIGHTING, (d.sceneLighting != nullptr)) +
        std::format("#define {} {:d}\n", USE_PROJECTION_VIEW, d.useProjectionView) +
        std::format("#define {} {:d}\n", USE_MODEL_MATRIX, d.useModelMatrix) +
        std::format("#define {} {:d}\n", NUM_DIRECTIONAL_LIGHTS, numDirectionalLights);
}

std::string OGLShaderSourceBuilder::GenerateVertexLayout() const
{
    return R"(
layout(location=0) in vec3 v_in_pos;
layout(location=1) in vec3 v_in_nor;
layout(location=2) in vec2 v_in_uv;
)";
}

std::string OGLShaderSourceBuilder::GenerateVertexOutput() const
{
    return R"(
out vec2 v_out_uv;
out vec3 v_out_nor;
)";
}

std::string OGLShaderSourceBuilder::GenerateVertexUniforms() const
{
    using namespace OGLShaderConstants::Uniform;

    std::string result =
        std::format("uniform mat4 {};\n", MODEL) +
        std::format("uniform mat4 {};\n", PROJECTION_VIEW);

    return result;
}

std::string OGLShaderSourceBuilder::GenerateFragmentStructs() const
{
    return R"(
struct DirectionalLight
{
    vec3 direction;
    vec4 diffuse;
};
)";
}

std::string OGLShaderSourceBuilder::GenerateFragmentInput() const
{
    return R"(
in vec2 v_out_uv;
in vec3 v_out_nor;
)";
}

std::string OGLShaderSourceBuilder::GenerateFragmentOutput() const
{
    return "out vec4 f_color;\n";
}

std::string OGLShaderSourceBuilder::GenerateFragmentUniforms() const
{
    using namespace OGLShaderConstants::Uniform;
    std::string result =
        std::format("uniform sampler2D {};\n", TEXTURE) +
        std::format("uniform vec4 {};\n", LIGHTING_AMBIENT);
    if (m_key.GetDescriptor().sceneLighting != nullptr)
    {
        if (m_key.GetDescriptor().sceneLighting->m_directionalLightCount > 0U)
        {
            result += std::format("uniform DirectionalLight {}[NUM_DIRECTIONAL_LIGHTS];\n", LIGHTING_DIRECTIONAL_ARRAY);
        }
    }

    return result;
}
