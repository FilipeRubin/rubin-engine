#pragma once
#include "scene-lighting-descriptor.h"
#include <utils/shared.h>

struct RenderingRuleDescriptor
{
	bool useProjection;
	bool useViewCamera;
	bool useModelTransform;
	Shared<SceneLightingDescriptor> sceneLighting;

	bool operator==(const RenderingRuleDescriptor& other) const = default;

	struct Hash
	{
		size_t operator()(const RenderingRuleDescriptor& desc) const noexcept
		{
			size_t hashes[]
			{
				std::hash<bool>{}(desc.useProjection),
				std::hash<bool>{}(desc.useViewCamera),
				std::hash<bool>{}(desc.useModelTransform),
				desc.sceneLighting != nullptr
					? SceneLightingDescriptor::Hash{}(*desc.sceneLighting)
					: 0U
			};

			size_t result = hashes[0];

			for (size_t i = 1U; i < sizeof(hashes) / sizeof(hashes[0]); i++)
			{
				result ^= hashes[i] << i;
			}

			return result;
		}
	};
};
