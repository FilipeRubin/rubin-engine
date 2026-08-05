#pragma once
#include "i-renderer-resource.h"
#include <types/rendering-rule-descriptor.h>

class IRenderingRule : public IRendererResource
{
public:
	virtual ~IRenderingRule() = default;
	virtual void Bind() = 0;
	virtual const RenderingRuleDescriptor& GetDescriptor() const = 0;
};
