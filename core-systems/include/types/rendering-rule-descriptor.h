#pragma once
#include "scene-lighting-descriptor.h"
#include <utils/shared.h>

struct RenderingRuleDescriptor
{
	bool useProjection2D;
	bool useProjectionView3D;
	bool useModel2D;
	bool useModel3D;
	Shared<SceneLightingDescriptor> sceneLighting;

	bool operator==(const RenderingRuleDescriptor& other) const = default;
};
