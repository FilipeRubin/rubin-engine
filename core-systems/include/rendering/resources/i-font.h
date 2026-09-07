#pragma once
#include "i-renderer-resource.h"

class IFont : public IRendererResource
{
public:
	virtual ~IFont() = default;
	virtual void Bind() = 0;
};
