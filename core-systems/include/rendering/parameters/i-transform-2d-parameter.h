#pragma once

#include <types/transform-2d.h>
#include "i-render-parameter.h"

class ITransform2DParameter : public IRenderParameter
{
public:
	virtual ~ITransform2DParameter() = default;
	virtual Transform2D& Transform() = 0;
};
