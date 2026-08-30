#pragma once
#include "i-mesh-3d-generator.h"
#include <types/dimensions.h>
#include <types/point-2d.h>

class TerrainMesh3DGenerator : public IMesh3DGenerator
{
public:
	TerrainMesh3DGenerator(const Dimensions& gridSize, Shared<FixedArray<float>> heightMapData);
	MeshData3D GenerateMeshData() const override;
private:
	Dimensions m_gridSize;
	Shared<FixedArray<float>> m_heightMapData;
	float GetPointHeight(const Point2D point) const;
	Vector2 GetPointInclination(const Point2D point) const;
	Vector3 GetPointNormal(const Point2D point) const;
};
