#include <rendering/data-generation/mesh-3d/plane-mesh-3d-generator.h>

PlaneMesh3DGenerator::PlaneMesh3DGenerator(Vector2 dimensions) :
	m_dimensions(dimensions)
{
}

MeshData3D PlaneMesh3DGenerator::GenerateMeshData() const
{
	Vertex3D rawVertices[]
	{
		{ {  m_dimensions.x / 2.0f, 0.0f,  m_dimensions.y / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
		{ {  m_dimensions.x / 2.0f, 0.0f, -m_dimensions.y / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { -m_dimensions.x / 2.0f, 0.0f, -m_dimensions.y / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { -m_dimensions.x / 2.0f, 0.0f,  m_dimensions.y / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } }
	};

	unsigned int rawIndices[]
	{
		0U, 1U, 2U,
		0U, 2U, 3U
	};

	Shared<FixedArray<Vertex3D>> vertices = Shared<FixedArray<Vertex3D>>(new FixedArray<Vertex3D>(24ULL));
	Shared<FixedArray<unsigned int>> indices = Shared<FixedArray<unsigned int>>(new FixedArray<unsigned int>(36ULL));

	std::copy(rawVertices, rawVertices + 4ULL, vertices->GetData());
	std::copy(rawIndices, rawIndices + 6ULL, indices->GetData());

	MeshData3D data;
	data.SetVertices(vertices);
	data.SetIndices(indices);
	return data;
}
