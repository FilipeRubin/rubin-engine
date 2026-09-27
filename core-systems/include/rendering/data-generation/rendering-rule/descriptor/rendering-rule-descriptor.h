#pragma once
#include "implementation/i-rendering-rule-descriptor-implementation.h"
#include <utils/shared.h>

class RenderingRuleDescriptor final
{
public:
	RenderingRuleDescriptor();
	IRenderingRuleDescriptorImplementation* GetImplementation();
private:
	Shared<IRenderingRuleDescriptorImplementation> m_impl;
};
