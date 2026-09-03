#pragma once
#include <functional>

struct SceneLightingDescriptor
{
	size_t directionalLightCount;

	bool operator==(const SceneLightingDescriptor& other) const = default;

	struct Hash
	{
		std::size_t operator()(const SceneLightingDescriptor& desc) const noexcept
		{
			return std::hash<size_t>{}(desc.directionalLightCount + 1U);
		}
	};
};
