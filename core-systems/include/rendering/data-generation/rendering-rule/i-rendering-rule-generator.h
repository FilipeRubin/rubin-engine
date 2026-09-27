#pragma once
#include "descriptor/rendering-rule-descriptor.h"

class IRenderer;

class IRenderingRuleGenerator
{
public:
	virtual ~IRenderingRuleGenerator() = default;
	virtual RenderingRuleDescriptor GenerateDescriptor(IRenderer& renderer) const = 0;
};
