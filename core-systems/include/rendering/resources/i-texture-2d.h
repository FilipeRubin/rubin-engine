#pragma once
#include "i-bindable-resource.h"
#include <types/dimensions.h>

class ITexture2D : public IBindableResource
{
public:
	virtual ~ITexture2D() = default;
	virtual const Dimensions& GetDimensions() const = 0;
};
