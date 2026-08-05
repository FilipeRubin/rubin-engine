#pragma once

struct RenderingRuleDescriptor
{
	bool useDirectionalLight;
	bool useCamera3D;
	bool useTransform3D;

	bool operator==(const RenderingRuleDescriptor& other) const = default;
};
