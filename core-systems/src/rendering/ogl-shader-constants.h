#pragma once

namespace OGLShaderConstants
{
    namespace Uniform
    {
        constexpr const char* MODEL = "u_model";
        constexpr const char* VIEW = "u_view";
        constexpr const char* PROJECTION = "u_projection";
        constexpr const char* PROJECTION_VIEW = "u_projectionView";
        constexpr const char* TEXTURE = "u_texture";
        constexpr const char* LIGHTING_AMBIENT = "u_ambientLight";
        constexpr const char* LIGHTING_DIRECTIONAL_ARRAY = "u_directionalLights";
    }
    namespace Define
    {
        namespace Feature
        {
            constexpr const char* USE_LIGHTING = "USE_LIGHTING";
            constexpr const char* USE_PROJECTION = "USE_PROJECTION";
            constexpr const char* USE_VIEW = "USE_VIEW";
            constexpr const char* USE_MODEL = "USE_MODEL";
            constexpr const char* NUM_DIRECTIONAL_LIGHTS = "NUM_DIRECTIONAL_LIGHTS";
        }
        namespace VertexAttribute
        {
            constexpr const char* HAS_POSITION_2D = "HAS_POSITION_2D";
            constexpr const char* HAS_POSITION_3D = "HAS_POSITION_3D";
            constexpr const char* HAS_UV = "HAS_UV";
            constexpr const char* HAS_NORMAL_3D = "HAS_NORMAL_3D";
        }
    }
}
