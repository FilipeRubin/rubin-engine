#pragma once
#include "scene-lighting-descriptor.h"
#include <utils/shared.h>

struct RenderingRuleDescriptor
{
	bool useProjection;
	bool useProjectionView;
	bool useModelMatrix;
	Shared<SceneLightingDescriptor> sceneLighting;

	bool operator==(const RenderingRuleDescriptor& other) const = default;
};
