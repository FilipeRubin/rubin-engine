#pragma once
#include "i-renderer-resource.h"
#include <rendering/i-mesh.h>

class IMesh2D : public IRendererResource, public IMesh
{
public:
	virtual ~IMesh2D() = default;
};
