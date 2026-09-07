#pragma once
#include "i-drawable-resource.h"
#include <types/mesh-type.h>

class IMesh : public IDrawableResource
{
public:
	virtual	~IMesh() = default;
	virtual MeshType GetMeshType() const = 0;
};
