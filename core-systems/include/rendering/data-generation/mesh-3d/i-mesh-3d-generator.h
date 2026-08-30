#pragma once
#include <containers/mesh-data-3d.h>

class IMesh3DGenerator
{
public:
	virtual ~IMesh3DGenerator() = default;
	virtual MeshData3D GenerateMeshData() const = 0;
};
