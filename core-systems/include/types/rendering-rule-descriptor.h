#pragma once
#include "scene-lighting-descriptor.h"
#include <utils/shared.h>

struct RenderingRuleDescriptor
{
	bool useProjection;
	bool useViewCamera;
	bool useModelTransform;
	Shared<SceneLightingDescriptor> sceneLighting;

	bool operator==(const RenderingRuleDescriptor& other) const;

	struct Hash
	{
		size_t operator()(const RenderingRuleDescriptor& desc) const noexcept;
	};
};
