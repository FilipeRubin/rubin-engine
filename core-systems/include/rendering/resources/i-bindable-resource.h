#pragma once
#include "i-renderer-resource.h"

class IBindableResource : public IRendererResource
{
public:
	virtual ~IBindableResource() = default;
	virtual void Bind() = 0;
};
