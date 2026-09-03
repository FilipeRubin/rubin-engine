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
    using namespace OGLShaderConstants::Define::Feature;
    using namespace OGLShaderConstants::Define::VertexAttribute;
    
    const RenderingRuleDescriptor& d = m_key.GetDescriptor();
    const MeshType& m = m_key.GetMeshType();
    
    size_t numDirectionalLights = 0U;

    bool hasPosition2D = m == MeshType::STATIC_2D;
    bool hasPosition3D = m == MeshType::STATIC_3D;
    bool hasUV = m == MeshType::STATIC_3D or m == MeshType::STATIC_2D;
    bool hasNormals3D = m == MeshType::STATIC_3D;

    if (d.sceneLighting != nullptr) numDirectionalLights = d.sceneLighting->directionalLightCount;
    return
        std::string("// Feature macros\n") +
        std::format("#define {} {:d}\n", USE_LIGHTING, d.sceneLighting != nullptr) +
        std::format("#define {} {:d}\n", USE_PROJECTION, d.useProjection) +
        std::format("#define {} {:d}\n", USE_VIEW, d.useViewCamera) +
        std::format("#define {} {:d}\n", USE_MODEL, d.useModelTransform) +
        std::format("#define {} {:d}\n", NUM_DIRECTIONAL_LIGHTS, numDirectionalLights) +
        std::string("// Vertex attribute macros\n") +
        std::format("#define {} {:d}\n", HAS_POSITION_2D, hasPosition2D) +
        std::format("#define {} {:d}\n", HAS_POSITION_3D, hasPosition3D) +
        std::format("#define {} {:d}\n", HAS_UV, hasUV) +
        std::format("#define {} {:d}\n", HAS_NORMAL_3D, hasNormals3D);
}

std::string OGLShaderSourceBuilder::GenerateVertexLayout() const
{
    using namespace OGLShaderConstants::Define::VertexAttribute;

    constexpr std::string_view result = R"(
#if {0}
layout(location=0) in vec2 v_in_pos;
#elif {1}
layout(location=0) in vec3 v_in_pos;
#endif
#if {2}
layout(location=1) in vec3 v_in_nor;
#endif
#if {3}
layout(location=2) in vec2 v_in_uv;
#endif
)";

    return std::format(result, HAS_POSITION_2D, HAS_POSITION_3D, HAS_NORMAL_3D, HAS_UV);
}

std::string OGLShaderSourceBuilder::GenerateVertexOutput() const
{
    using namespace OGLShaderConstants::Define::VertexAttribute;

    constexpr std::string_view result = R"(
#if {0}
out vec3 v_out_nor;
#endif
#if {1}
out vec2 v_out_uv;
#endif
)";
    
    return std::format(result, HAS_NORMAL_3D, HAS_UV);
}

std::string OGLShaderSourceBuilder::GenerateVertexUniforms() const
{
    using namespace OGLShaderConstants::Uniform;
    using namespace OGLShaderConstants::Define::Feature;

    constexpr std::string_view result = R"(
#if {5}
uniform {0} {1};
#endif
#if !({6} && {7})
    #if {6}
uniform {0} {2};
    #elif {7}
uniform {0} {3};
    #endif
#else
uniform {0} {4};
#endif
)";

    std::string matrixType = m_key.GetMeshType() == MeshType::STATIC_2D ? "mat3" : "mat4";

    return std::format(result, matrixType, MODEL, PROJECTION, VIEW, PROJECTION_VIEW, USE_MODEL, USE_PROJECTION, USE_VIEW);
}

std::string OGLShaderSourceBuilder::GenerateVertexLogic() const
{
    using namespace OGLShaderConstants::Uniform;
    using namespace OGLShaderConstants::Define::Feature;
    using namespace OGLShaderConstants::Define::VertexAttribute;

    std::string result;

    constexpr std::string_view transformedPositionFunc = R"(
vec4 transformedPosition()
{{
#if {0} // HAS_POSITION_2D
    vec3 transformedPos =

    #if {2} && {3} // USE_PROJECTION USE_VIEW
        {4} * // u_projectionView
    #else
        #if {2}
        {5} * // u_projection
        #elif {3}
        {6} * // u_view
        #endif
    #endif

    #if {7} // USE_MODEL
        {8} * // u_model
    #endif

    vec3(v_in_pos, 1.0);
    return vec4(transformedPos, 1.0);
#elif {1} // HAS_POSITION_3D
    return 
    #if {2} && {3} // USE_PROJECTION USE_VIEW
        {4} * // u_projectionView
    #else
        #if {2}
        {5} * // u_projection
        #elif {3}
        {6} * // u_view
        #endif
    #endif

    #if {7} // USE_MODEL
        {8} * // u_model
    #endif
    vec4(v_in_pos, 1.0);
#else
    return vec4(0.0, 0.0, 0.0, 1.0);
#endif
}}
)";
    result += std::format(transformedPositionFunc, HAS_POSITION_2D, HAS_POSITION_3D, USE_PROJECTION, USE_VIEW, PROJECTION_VIEW, PROJECTION, VIEW, USE_MODEL, MODEL);
    
    constexpr std::string_view mainFunc = R"(
void main()
{{
	gl_Position = transformedPosition();
#if {0} // HAS_UV
	v_out_uv = v_in_uv;
#endif
#if {1} // HAS_NORMAL_3D
	v_out_nor =
    #if {2} // USE_MODEL
        mat3(transpose(inverse({3}))) * // u_model
    #endif
        v_in_nor;
#endif
}}
)";
    result += std::format(mainFunc, HAS_UV, HAS_NORMAL_3D, USE_MODEL, MODEL);
    return result;
}

std::string OGLShaderSourceBuilder::GenerateFragmentStructs() const
{
    if (m_key.GetDescriptor().sceneLighting == nullptr)
        return "";
    if (m_key.GetDescriptor().sceneLighting->directionalLightCount == 0U)
        return "";
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
    using namespace OGLShaderConstants::Define::VertexAttribute;
    return std::format(R"(
#if {0}
in vec3 v_out_nor;
#endif
#if {1}
in vec2 v_out_uv;
#endif
)", HAS_NORMAL_3D, HAS_UV);
}

std::string OGLShaderSourceBuilder::GenerateFragmentOutput() const
{
    return "out vec4 f_color;\n";
}

std::string OGLShaderSourceBuilder::GenerateFragmentUniforms() const
{
    using namespace OGLShaderConstants::Uniform;
    using namespace OGLShaderConstants::Define::Feature;

    constexpr std::string_view result = R"(
uniform sampler2D {0};
#if {1}
uniform vec4 {2};
    #if {3} > 0
uniform DirectionalLight {4}[{3}];
    #endif
#endif
)";

    return std::format(result, TEXTURE, USE_LIGHTING, LIGHTING_AMBIENT, NUM_DIRECTIONAL_LIGHTS, LIGHTING_DIRECTIONAL_ARRAY);
}

std::string OGLShaderSourceBuilder::GenerateFragmentLogic() const
{
    using namespace OGLShaderConstants::Uniform;
    using namespace OGLShaderConstants::Define::Feature;
    using namespace OGLShaderConstants::Define::VertexAttribute;

    std::string result;
    
    constexpr std::string_view calculateDirectionalLightsColorFunc = R"(
#if {0} != 0 // NUM_DIRECTIONAL_LIGHTS
vec4 calculatetDirectionalLightsColor()
{{
    vec4 result = vec4(0.0);
    for (int i = 0; i < {0}; i++)
    {{
        float directionalLightAmount = max(dot(normalize(v_out_nor), normalize(-{1}[i].direction)), 0.0); // u_directionalLights
        result += {1}[i].diffuse * directionalLightAmount;
    }}
	return result;
}}
#endif
)";
    result += std::format(calculateDirectionalLightsColorFunc, NUM_DIRECTIONAL_LIGHTS, LIGHTING_DIRECTIONAL_ARRAY);

    constexpr std::string_view mainFunc = R"(
void main()
{{
	f_color =
#if {0} // USE_LIGHTING
        ({1} // u_ambientLight
    #if {2} != 0 // NUM_DIRECTIONAL_LIGHTS
        + calculatetDirectionalLightsColor()
    #endif
        ) *
#endif
#if {4} // HAS_UV
        texture({3}, v_out_uv); // u_texture
#else
        vec4(1.0);
#endif
}}
)";
    result += std::format(mainFunc, USE_LIGHTING, LIGHTING_AMBIENT, NUM_DIRECTIONAL_LIGHTS, TEXTURE, HAS_UV);

    return result;
}
