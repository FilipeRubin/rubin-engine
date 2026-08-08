#pragma once

struct RenderingRuleDescriptor
{
	bool useDirectionalLight;
	bool useViewProjection;
	bool useModelMatrix;

	bool operator==(const RenderingRuleDescriptor& other) const = default;
};
