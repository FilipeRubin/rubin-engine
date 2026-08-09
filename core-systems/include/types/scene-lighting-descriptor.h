#pragma once
#include <functional>

struct SceneLightingDescriptor
{
	size_t m_directionalLightCount;

	bool operator==(const SceneLightingDescriptor& other) const = default;
};
