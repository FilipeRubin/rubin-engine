#pragma once
#include <rendering/parameters/ogl-camera-3d-parameter.h>
#include <rendering/parameters/ogl-scene-lighting-parameter.h>
#include <rendering/parameters/ogl-transform-3d-parameter.h>

struct OGLRenderParametersState
{
	OGLCamera3DParameter* camera;
	OGLSceneLightingParameter* sceneLighting;
	OGLTransform3DParameter* transform;
};
