#pragma once

namespace OGLShaderConstants
{
    namespace Uniform
    {
        constexpr const char* MODEL = "u_model";
        constexpr const char* PROJECTION_VIEW = "u_projectionView";
        constexpr const char* TEXTURE = "u_texture";
        constexpr const char* DIR_LIGHT_AMBIENT = "u_ambientLight";
        constexpr const char* DIR_LIGHT_DIFFUSE = "u_directionalLightDiffuse";
        constexpr const char* DIR_LIGHT_DIRECTION = "u_directionalLightDirection";
    }
    namespace Define
    {
        constexpr const char* USE_DIRECTIONAL_LIGHT = "USE_DIRECTIONAL_LIGHT";
        constexpr const char* USE_PROJECTION_VIEW = "USE_PROJECTION_VIEW";
        constexpr const char* USE_MODEL_MATRIX = "USE_MODEL_MATRIX";
    }
}
