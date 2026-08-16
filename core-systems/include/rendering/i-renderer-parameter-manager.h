#pragma once
#include "parameters/i-camera-3d-parameter.h"
#include "parameters/i-scene-lighting-parameter.h"
#include "parameters/i-transform-3d-parameter.h"
#include <types/scene-lighting-descriptor.h>

class IRendererParameterManager
{
public:
	virtual ~IRendererParameterManager() = default;
	virtual ICamera3DParameter* CreateCamera3D() = 0;
	virtual ISceneLightingParameter* CreateSceneLighting(const SceneLightingDescriptor& lightingDescriptor) = 0;
	virtual ITransform3DParameter* CreateTransform3D() = 0;
};
