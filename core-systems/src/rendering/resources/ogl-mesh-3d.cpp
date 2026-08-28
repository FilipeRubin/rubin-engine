#include "ogl-mesh-3d.h"
#include <rendering/ogl-renderer.h>
#include <logging/log-macros.h>
#include <ogl.h>

OGLMesh3D::OGLMesh3D(OGLRenderer& renderer, Shared<FixedArray<Vertex3D>> vertices, Shared<FixedArray<unsigned int>> indices) :
	OGLRendererUser(renderer),
	m_vbo(0U), m_vao(0U), m_ebo(0U), m_indicesCount(unsigned int(indices->GetElementCount())),
	m_cachedVertices(vertices),
	m_cachedIndices(indices)
{
	LOG_WARNING("Decide to copy vertices passed by argument or remove this warning");
}

bool OGLMesh3D::IsValid() const
{
	return
		m_vbo != 0U and
		m_vao != 0U and
		m_ebo != 0U;
}

void OGLMesh3D::Draw()
{
	OGLRenderingRule* renderingRule = Renderer().GetCurrentRenderingRule();
	MeshType meshType = GetMeshType();
	Renderer().ShaderCache().BindOrCreate(*renderingRule, meshType);

	Renderer().ShaderCache().SetUniforms(*renderingRule);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, NULL);
}

MeshType OGLMesh3D::GetMeshType() const
{
	return MeshType::STATIC_3D;
}

void OGLMesh3D::Create()
{
	LOG_DEBUG("Creating OGLMesh3D.");
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	GLsizeiptr verticesSize = m_cachedVertices->GetElementCount() * sizeof(Vertex3D);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, m_cachedVertices->GetData(), GL_STATIC_DRAW);

	glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glVertexAttribPointer(1U, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)12);
	glVertexAttribPointer(2U, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)24);
	glEnableVertexAttribArray(0U);
	glEnableVertexAttribArray(1U);
	glEnableVertexAttribArray(2U);

	GLsizeiptr indicesSize = m_cachedIndices->GetElementCount() * sizeof(unsigned int);
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, m_cachedIndices->GetData(), GL_STATIC_DRAW);

	m_cachedVertices.Reset();
	m_cachedIndices.Reset();
	LOG_DEBUG("OGLMesh3D created.");
}

void OGLMesh3D::Destroy()
{
	LOG_DEBUG("Destroying OGLMesh3D.");
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_ebo);

	m_indicesCount = 0U;
}
