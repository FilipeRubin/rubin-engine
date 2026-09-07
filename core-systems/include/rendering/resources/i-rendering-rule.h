#pragma once
#include "i-bindable-resource.h"
#include <types/rendering-rule-descriptor.h>

class IRenderingRule : public IBindableResource
{
public:
	virtual ~IRenderingRule() = default;
	virtual const RenderingRuleDescriptor& GetDescriptor() const = 0;
};
