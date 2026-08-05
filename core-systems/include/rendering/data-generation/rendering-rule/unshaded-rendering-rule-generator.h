#pragma once
#include "i-rendering-rule-generator.h"

class UnshadedRenderingRuleGenerator final : public IRenderingRuleGenerator
{
public:
	RenderingRuleDescriptor GenerateDescriptor() const override;
};
