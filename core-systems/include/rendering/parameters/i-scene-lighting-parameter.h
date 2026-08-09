#pragma once
#include "i-render-parameter.h"
#include <containers/fixed-array.h>
#include <types/directional-light.h>

class ISceneLightingParameter : public IRenderParameter
{
public:
	virtual ~ISceneLightingParameter() = default;
	virtual Color& AmbientLight() = 0;
	virtual FixedArray<DirectionalLight>& DirectionalLights() = 0;
};
