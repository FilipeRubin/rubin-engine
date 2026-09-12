#pragma once
#include "i-bindable-resource.h"

// Maybe create an inheritance tree of IText2D with inherited types IStaticText2D and IDynamicText2D
class IStaticText2D : public IBindableResource
{
public:
	virtual ~IStaticText2D() = default;
};
