#pragma once
#include "i-render-parameter.h"
#include <types/camera-2d.h>

class ICamera2DParameter : public IRenderParameter
{
public:
	virtual ~ICamera2DParameter() = default;
	virtual Camera2D& Camera() = 0;
};
