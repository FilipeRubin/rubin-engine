#pragma once

struct SceneLightingDescriptor
{
	size_t directionalLightCount;

	bool operator==(const SceneLightingDescriptor& other) const = default;
};
