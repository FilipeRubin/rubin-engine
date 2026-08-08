#pragma once

struct RenderingRuleDescriptor
{
	bool useDirectionalLight;
	bool useProjectionView;
	bool useModelMatrix;

	bool operator==(const RenderingRuleDescriptor& other) const = default;
};
