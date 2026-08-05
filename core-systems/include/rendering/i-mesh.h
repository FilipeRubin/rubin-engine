#pragma once
#include "i-drawable.h"
#include <types/mesh-type.h>

class IMesh : public IDrawable
{
public:
	virtual	~IMesh() = default;
	virtual MeshType GetMeshType() const = 0;
};
