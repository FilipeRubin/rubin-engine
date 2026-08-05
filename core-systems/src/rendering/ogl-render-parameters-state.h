#pragma once
#include <rendering/parameters/ogl-camera-3d-parameter.h>
#include <rendering/parameters/ogl-directional-light-parameter.h>
#include <rendering/parameters/ogl-transform-3d-parameter.h>

struct OGLRenderParametersState
{
	OGLCamera3DParameter* camera;
	OGLDirectionalLightParameter* directionalLight;
	OGLTransform3DParameter* transform;
};
