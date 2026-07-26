#include <rendering/data-generation/mesh-3d/terrain-mesh-3d-generator.h>
#include <logging/log-macros.h>
#include <cmath>

TerrainMesh3DGenerator::TerrainMesh3DGenerator(const Dimensions& gridSize, Shared<FixedArray<float>> heightMapData) :
    m_gridSize(gridSize),
    m_heightMapData(heightMapData)
{
}

MeshData TerrainMesh3DGenerator::GenerateMeshData() const
{
    MeshData result;
    size_t vertexCount = (size_t)m_gridSize.width * (size_t)m_gridSize.height;
    if (vertexCount > INT_MAX)
    {
        LOG_ERROR("Tried to generate terrain with 'vertexCount > INT_MAX'.");
        return {};
    }

    Shared<FixedArray<Vertex3D>> vertices = Shared<FixedArray<Vertex3D>>(new FixedArray<Vertex3D>(vertexCount));
    for (size_t i = 0ULL; i < vertexCount; i++)
    {
        int x = i % m_gridSize.width;
        int y = (int)i / m_gridSize.width;

        (*vertices)[i].position.x = (float)x / (float)(m_gridSize.width - 1);
        (*vertices)[i].position.y = (*m_heightMapData)[i];
        (*vertices)[i].position.z = (float)y / (float)(m_gridSize.height - 1);

        (*vertices)[i].normal = GetPointNormal({x, y});

        (*vertices)[i].uv.x = (float)x;
        (*vertices)[i].uv.y = float(m_gridSize.height - y);
    }

    size_t indicesCount = 6ULL * size_t(m_gridSize.width - 1) * size_t(m_gridSize.height - 1);
    Shared<FixedArray<unsigned int>> indices = Shared<FixedArray<unsigned int>>(new FixedArray<unsigned int>(indicesCount));
    {
        for (int y = 0; y < m_gridSize.height - 1; y++)
        {
            for (int x = 0; x < m_gridSize.width - 1; x++)
            {
                //
                //  v1------v2
                //   |\     |
                //   | \    |
                //   |  \   |
                //   |   \  |
                //   |    \ |
                //   |     \|
                //  v3------v4
                //

                const int v1 = y * m_gridSize.width + x;
                const int v2 = y * m_gridSize.width + x + 1;
                const int v3 = (y + 1) * m_gridSize.width + x;
                const int v4 = (y + 1) * m_gridSize.width + x + 1;

                const size_t i = size_t(x + (m_gridSize.width - 1) * y) * 6ULL;

                (*indices)[i + 0] = v3;
                (*indices)[i + 1] = v4;
                (*indices)[i + 2] = v1;

                (*indices)[i + 3] = v4;
                (*indices)[i + 4] = v2;
                (*indices)[i + 5] = v1;
            }
        }
    }

    result.SetVertices(vertices);
    result.SetIndices(indices);

    return result;
}

float TerrainMesh3DGenerator::GetPointHeight(const Point2D point) const
{
    return (*m_heightMapData)[point.x + (size_t)point.y * m_gridSize.width];
}

Vector2 TerrainMesh3DGenerator::GetPointInclination(const Point2D point) const
{
    //
    // Top-view:
    // 
    //     U
    //     |
    //     |
    // L---P---R
    //     |
    //     |
    //     D
    //

    float p = GetPointHeight(point);
    float l = point.x == 0 ? NAN : GetPointHeight({ point.x - 1, point.y });
    float r = point.x == m_gridSize.width - 1 ? NAN : GetPointHeight({ point.x + 1, point.y });
    float u = point.y == 0 ? NAN : GetPointHeight({ point.x, point.y - 1 });
    float d = point.y == m_gridSize.height - 1 ? NAN : GetPointHeight({ point.x, point.y + 1 });

    float spacingX = 1.0f / (m_gridSize.width - 1);
    float spacingY = 1.0f / (m_gridSize.height - 1);

    float horizontal = 0.0f;
    if (isnan(l) and not isnan(r))
        horizontal = r - p;
    else if (not isnan(l) and isnan(r))
        horizontal = p - l;
    else if (not isnan(l) and not isnan(r))
        horizontal = (r - l) / (2.0f * spacingX);

    float vertical = 0.0f;
    if (isnan(u) and not isnan(d))
        vertical = d - p;
    else if (not isnan(u) and isnan(d))
        vertical = p - u;
    else if (not isnan(u) and not isnan(d))
        vertical = (d - u) / (2.0f * spacingY);

    return Vector2(horizontal, vertical);
}

Vector3 TerrainMesh3DGenerator::GetPointNormal(const Point2D point) const
{
    Vector2 inclination = GetPointInclination(point);

    Vector3 normal = {
        -inclination.x,
        1.0f,
        -inclination.y
    };

    return normal.Normalized();
}
