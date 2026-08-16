#pragma once
#include "i-rendering-rule-generator.h"

class LambertRenderingRuleGenerator final : public IRenderingRuleGenerator
{
public:
	LambertRenderingRuleGenerator(const SceneLightingDescriptor& lightingDescriptor);
	RenderingRuleDescriptor GenerateDescriptor() const override;
private:
	const SceneLightingDescriptor& m_lightingDescriptor;
};
