#pragma once
#include "scene-lighting-descriptor.h"
#include <utils/shared.h>

struct RenderingRuleDescriptor
{
	bool useProjection = false;
	bool useViewCamera = false;
	bool useModelTransform = false;
	Shared<SceneLightingDescriptor> sceneLighting;

	bool operator==(const RenderingRuleDescriptor& other) const;

	struct Hash
	{
		size_t operator()(const RenderingRuleDescriptor& desc) const noexcept;
	};
};
