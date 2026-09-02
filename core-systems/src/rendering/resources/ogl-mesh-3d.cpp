#include "ogl-mesh-3d.h"
#include <rendering/ogl-renderer.h>
#include <rendering/ogl-attribute-location-constants.h>
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
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

	using namespace OGLAttributeLocationConstants;

	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)12);
	glVertexAttribPointer(UV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)24);
	glEnableVertexAttribArray(POSITION);
	glEnableVertexAttribArray(NORMAL);
	glEnableVertexAttribArray(UV);

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
