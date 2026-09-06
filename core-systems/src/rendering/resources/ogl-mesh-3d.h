#pragma once
#include <containers/fixed-array.h>
#include <rendering/resources/i-mesh-3d.h>
#include <rendering/i-renderer-managed.h>
#include <rendering/ogl-renderer-user.h>
#include <types/vertex-3d.h>
#include <utils/shared.h>

class OGLMesh3D : public IMesh3D, public IRendererManaged, public OGLRendererUser
{
public:
	OGLMesh3D(OGLRenderer& renderer, const Shared<FixedArray<Vertex3D>> vertices, const Shared<FixedArray<unsigned int>> indices);
	bool IsValid() const override;
	void Draw() override;
	MeshType GetMeshType() const override;
	void Create() override;
	void Destroy() override;
private:
	unsigned int m_vbo;
	unsigned int m_vao;
	unsigned int m_ebo;
	unsigned int m_indicesCount;

	const Shared<FixedArray<Vertex3D>> m_cachedVertices;
	const Shared<FixedArray<unsigned int>> m_cachedIndices;
};
