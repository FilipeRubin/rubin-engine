#pragma once
#include <types/rendering-rule-descriptor.h>

class IRenderingRuleGenerator
{
public:
	virtual ~IRenderingRuleGenerator() = default;
	virtual RenderingRuleDescriptor GenerateDescriptor() const = 0;
};
