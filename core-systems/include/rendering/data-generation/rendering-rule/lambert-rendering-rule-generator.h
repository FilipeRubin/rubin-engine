#pragma once
#include "i-rendering-rule-generator.h"

class LambertRenderingRuleGenerator final : public IRenderingRuleGenerator
{
public:
	RenderingRuleDescriptor GenerateDescriptor() const override;
};
