#pragma once
#include "i-mesh-3d-generator.h"

class CubeMesh3DGenerator : public IMesh3DGenerator
{
public:
	CubeMesh3DGenerator(const Vector3& dimensions);
	MeshData3D GenerateMeshData() const override;
private:
	Vector3 m_dimensions;
};
