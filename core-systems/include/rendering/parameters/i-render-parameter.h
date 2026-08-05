#pragma once
#include <rendering/resources/i-rendering-rule.h>

class IRenderParameter
{
public:
	virtual ~IRenderParameter() = default;
	virtual void Bind() = 0;
};
