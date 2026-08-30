#pragma once
#include "i-rendering-rule-generator.h"

class CanvasRenderingRuleGenerator : public IRenderingRuleGenerator
{
public:
	RenderingRuleDescriptor GenerateDescriptor() const override;
};
