#pragma once
#include <rendering/parameters/ogl-camera-3d-parameter.h>
#include <rendering/parameters/ogl-scene-lighting-parameter.h>
#include <rendering/parameters/ogl-transform-2d-parameter.h>
#include <rendering/parameters/ogl-transform-3d-parameter.h>

struct OGLRenderParametersState
{
	OGLCamera3DParameter* camera3D = nullptr;
	OGLSceneLightingParameter* sceneLighting = nullptr;
	OGLTransform2DParameter* transform2D = nullptr;
	OGLTransform3DParameter* transform3D = nullptr;
};
