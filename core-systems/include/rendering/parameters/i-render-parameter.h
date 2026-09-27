#pragma once
#include "implementation/i-render-parameter-implementation.h"

class IRenderParameter
{
public:
	virtual ~IRenderParameter() = default;
	virtual void Bind() = 0;
protected:
	virtual IRenderParameterImplementation* GetImplementation() = 0;
};
