#include <rendering/data-generation/mesh-2d/quad-mesh-2d-generator.h>

QuadMesh2DGenerator::QuadMesh2DGenerator(Vector2 size) :
    m_size(size)
{
}

MeshData2D QuadMesh2DGenerator::GenerateMeshData() const
{
    Vertex2D rawVertices[]
    {
        { { m_size.x,     0.0f }, { 1.0f, 1.0f } },
        { { m_size.x, m_size.y }, { 1.0f, 0.0f } },
        { {     0.0f, m_size.y }, { 0.0f, 0.0f } },
        { {     0.0f,     0.0f }, { 0.0f, 1.0f } }
    };
    unsigned int rawIndices[]
    {
        0U, 1U, 2U,
        2U, 3U, 0U
    };

    Shared<FixedArray<Vertex2D>> vertices = Shared<FixedArray<Vertex2D>>(new FixedArray<Vertex2D>(4ULL));
    Shared<FixedArray<unsigned int>> indices = Shared<FixedArray<unsigned int>>(new FixedArray<unsigned int>(6ULL));

    std::copy(rawVertices, rawVertices + 4ULL, vertices->GetData());
    std::copy(rawIndices, rawIndices + 6ULL, indices->GetData());

    MeshData2D data;
    data.SetVertices(vertices);
    data.SetIndices(indices);
    return data;
}
