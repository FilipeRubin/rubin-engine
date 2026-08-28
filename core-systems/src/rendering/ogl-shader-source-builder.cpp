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
    std::string logic = GenerateVertexLogic();
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
    std::string logic = GenerateFragmentLogic();
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
    bool use3D = false;
    switch (m_key.GetMeshType())
    {
    case MeshType::STATIC_3D:
    case MeshType::TERRAIN_3D:
        use3D = true;
    }
    size_t numDirectionalLights = 0U;
    if (d.sceneLighting != nullptr) numDirectionalLights = d.sceneLighting->directionalLightCount;
    return
        std::format("#define {} {:d}\n", USE_LIGHTING, d.sceneLighting != nullptr) +
        std::format("#define {} {:d}\n", USE_PROJECTION, d.useProjection) +
        std::format("#define {} {:d}\n", USE_PROJECTION_VIEW, d.useProjectionView) +
        std::format("#define {} {:d}\n", USE_MODEL_MATRIX, d.useModelMatrix) +
        std::format("#define {} {:d}\n", USE_3D_VERTEX, use3D) +
        std::format("#define {} {:d}\n", NUM_DIRECTIONAL_LIGHTS, numDirectionalLights);
}

std::string OGLShaderSourceBuilder::GenerateVertexLayout() const
{
    switch (m_key.GetMeshType())
    {
    case MeshType::STATIC_2D:
        return R"(
layout(location=0) in vec2 v_in_pos;
layout(location=1) in vec2 v_in_uv;
)";
    case MeshType::STATIC_3D:
    case MeshType::TERRAIN_3D:
        return R"(
layout(location=0) in vec3 v_in_pos;
layout(location=1) in vec3 v_in_nor;
layout(location=2) in vec2 v_in_uv;
)";
    }
    return "";
}

std::string OGLShaderSourceBuilder::GenerateVertexOutput() const
{
    switch (m_key.GetMeshType())
    {
    case MeshType::STATIC_2D:
        return R"(
out vec2 v_out_uv;
)";
    case MeshType::STATIC_3D:
    case MeshType::TERRAIN_3D:
        return R"(
out vec2 v_out_uv;
out vec3 v_out_nor;
)";
    }
    return "";
}

std::string OGLShaderSourceBuilder::GenerateVertexUniforms() const
{
    using namespace OGLShaderConstants::Uniform;
    std::string result;

    switch (m_key.GetMeshType())
    {
    case MeshType::STATIC_2D:
        result =
            std::format("uniform mat3 {};\n", MODEL) +
            std::format("uniform mat3 {};\n", PROJECTION);
        break;
    case MeshType::STATIC_3D:
    case MeshType::TERRAIN_3D:
        result =
            std::format("uniform mat4 {};\n", MODEL) +
            std::format("uniform mat4 {};\n", PROJECTION_VIEW);
        break;
    }

    return result;
}

std::string OGLShaderSourceBuilder::GenerateVertexLogic() const
{
    return R"(
void main()
{
	gl_Position =
#if USE_PROJECTION_VIEW
        u_projectionView *
#elif USE_PROJECTION
        u_projection *
#endif
#if USE_MODEL_MATRIX
        u_model *
#endif
#if USE_3D_VERTEX
        vec4(v_in_pos, 1.0);
#else
        vec4(v_in_pos, 0.0, 1.0);
#endif
	v_out_uv = v_in_uv;
#if USE_3D_VERTEX
	v_out_nor =
    #if USE_MODEL_MATRIX
        mat3(transpose(inverse(u_model))) *
    #endif
        v_in_nor;
#endif
}
)";
}

std::string OGLShaderSourceBuilder::GenerateFragmentStructs() const
{
    std::string result;
    if (m_key.GetDescriptor().sceneLighting != nullptr)
    {
        if (m_key.GetDescriptor().sceneLighting->directionalLightCount > 0U)
        {
            result += R"(
struct DirectionalLight
{
    vec3 direction;
    vec4 diffuse;
};
)";
        }
    }
    return result;
}

std::string OGLShaderSourceBuilder::GenerateFragmentInput() const
{
    switch (m_key.GetMeshType())
    {
    case MeshType::STATIC_2D:
        return R"(
in vec2 v_out_uv;
)";
    case MeshType::STATIC_3D:
    case MeshType::TERRAIN_3D:
        return R"(
in vec2 v_out_uv;
in vec3 v_out_nor;
)";
    }
    return "";
}

std::string OGLShaderSourceBuilder::GenerateFragmentOutput() const
{
    return "out vec4 f_color;\n";
}

std::string OGLShaderSourceBuilder::GenerateFragmentUniforms() const
{
    using namespace OGLShaderConstants::Uniform;
    std::string result;
    result += std::format("uniform sampler2D {};\n", TEXTURE);
    if (m_key.GetDescriptor().sceneLighting != nullptr)
    {
        result += std::format("uniform vec4 {};\n", LIGHTING_AMBIENT);
        if (m_key.GetDescriptor().sceneLighting->directionalLightCount > 0U)
        {
            result += std::format("uniform DirectionalLight {}[NUM_DIRECTIONAL_LIGHTS];\n", LIGHTING_DIRECTIONAL_ARRAY);
        }
    }

    return result;
}

std::string OGLShaderSourceBuilder::GenerateFragmentLogic() const
{
    return R"(
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
        (u_ambientLight
    #if NUM_DIRECTIONAL_LIGHTS != 0
        + calculatetDirectionalLightsColor()
    #endif
        ) *
#endif
        texture(u_texture, v_out_uv);
}
)";
}
