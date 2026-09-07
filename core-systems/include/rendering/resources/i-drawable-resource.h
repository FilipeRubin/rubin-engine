#pragma once
#include "i-renderer-resource.h"

class IDrawableResource : public IRendererResource
{
public:
	virtual ~IDrawableResource() = default;
	virtual void Draw() = 0;
};
