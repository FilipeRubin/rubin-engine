#pragma once

namespace OGLShaderConstants
{
    namespace Uniform
    {
        constexpr const char* MODEL = "u_model";
        constexpr const char* VIEW = "u_view";
        constexpr const char* PROJECTION = "u_projection";
        constexpr const char* TEXTURE = "u_texture";
        constexpr const char* DIR_LIGHT_AMBIENT = "u_ambientLight";
        constexpr const char* DIR_LIGHT_DIFFUSE = "u_directionalLightDiffuse";
        constexpr const char* DIR_LIGHT_DIRECTION = "u_directionalLightDirection";
    }
    namespace Define
    {
        constexpr const char* USE_DIRECTIONAL_LIGHT = "USE_DIRECTIONAL_LIGHT";
        constexpr const char* USE_CAMERA_3D = "USE_CAMERA_3D";
        constexpr const char* USE_TRANSFORM_3D = "USE_TRANSFORM_3D";
    }
}
