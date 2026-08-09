#pragma once

namespace OGLShaderConstants
{
    namespace Uniform
    {
        constexpr const char* MODEL = "u_model";
        constexpr const char* PROJECTION_VIEW = "u_projectionView";
        constexpr const char* TEXTURE = "u_texture";
        constexpr const char* LIGHTING_AMBIENT = "u_ambientLight";
        constexpr const char* LIGHTING_DIRECTIONAL_ARRAY = "u_directionalLights";
    }
    namespace Define
    {
        constexpr const char* USE_LIGHTING = "USE_LIGHTING";
        constexpr const char* USE_PROJECTION_VIEW = "USE_PROJECTION_VIEW";
        constexpr const char* USE_MODEL_MATRIX = "USE_MODEL_MATRIX";
        constexpr const char* NUM_DIRECTIONAL_LIGHTS = "NUM_DIRECTIONAL_LIGHTS";
    }
}
