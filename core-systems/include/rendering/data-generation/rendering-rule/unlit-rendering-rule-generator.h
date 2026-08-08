#pragma once
#include "i-rendering-rule-generator.h"

class UnlitRenderingRuleGenerator final : public IRenderingRuleGenerator
{
public:
	RenderingRuleDescriptor GenerateDescriptor() const override;
};
