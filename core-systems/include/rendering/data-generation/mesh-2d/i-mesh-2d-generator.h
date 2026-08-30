#pragma once
#include <containers/mesh-data-2d.h>

class IMesh2DGenerator
{
public:
	virtual ~IMesh2DGenerator() = default;
	virtual MeshData2D GenerateMeshData() const = 0;
};
