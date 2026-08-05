#pragma once
#include "i-renderer-resource.h"
#include <rendering/i-mesh.h>

class IMesh3D : public IRendererResource, public IMesh
{
public:
	virtual ~IMesh3D() = default;
};
