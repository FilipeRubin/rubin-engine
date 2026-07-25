#pragma once
#include "i-mesh-3d-generator.h"
#include <types/dimensions.h>

class TerrainMesh3DGenerator : public IMesh3DGenerator
{
public:
	TerrainMesh3DGenerator(const Dimensions& gridSize, Shared<FixedArray<float>> heightMapData);
	MeshData GenerateMeshData() const override;
private:
	Dimensions m_gridSize;
	Shared<FixedArray<float>> m_heightMapData;
	float GetPointHeight(int x, int y) const;
	Vector2 GetPointInclination(int x, int y) const;
	Vector3 GetPointNormal(int x, int y) const;
};
