#include "ogl-mesh-2d.h"
#include <rendering/resources/ogl-rendering-rule.h>
#include <rendering/ogl-renderer.h>
#include <logging/log-macros.h>
#include <ogl.h>

OGLMesh2D::OGLMesh2D(OGLRenderer& renderer, Shared<FixedArray<Vertex2D>> vertices, Shared<FixedArray<unsigned int>> indices) :
    OGLRendererUser(renderer),
    m_vbo(0U), m_vao(0U), m_ebo(0U), m_indicesCount(unsigned int(indices->GetElementCount())),
    m_cachedVertices(vertices),
    m_cachedIndices(indices)
{
    LOG_WARNING("Decide to copy vertices passed by argument or remove this warning");
}

bool OGLMesh2D::IsValid() const
{
    return
        m_vbo != 0U and
        m_vao != 0U and
        m_ebo != 0U;
}

void OGLMesh2D::Draw()
{
    OGLRenderingRule* renderingRule = Renderer().GetCurrentRenderingRule();
    MeshType meshType = GetMeshType();
    Renderer().ShaderCache().BindOrCreate(*renderingRule, meshType);

    Renderer().ShaderCache().SetUniforms(*renderingRule);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, NULL);
}

MeshType OGLMesh2D::GetMeshType() const
{
    return MeshType::STATIC_2D;
}

void OGLMesh2D::Create()
{
    LOG_DEBUG("Creating OGLMesh2D.");
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    GLsizeiptr verticesSize = m_cachedVertices->GetElementCount() * sizeof(Vertex3D);
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, m_cachedVertices->GetData(), GL_STATIC_DRAW);

    glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
    glVertexAttribPointer(1U, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)8);
    glEnableVertexAttribArray(0U);
    glEnableVertexAttribArray(1U);

    GLsizeiptr indicesSize = m_cachedIndices->GetElementCount() * sizeof(unsigned int);
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, m_cachedIndices->GetData(), GL_STATIC_DRAW);

    m_cachedVertices.Reset();
    m_cachedIndices.Reset();
    LOG_DEBUG("OGLMesh2D created.");
}

void OGLMesh2D::Destroy()
{
    LOG_DEBUG("Destroying OGLMesh2D.");
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_ebo);

    m_indicesCount = 0U;
}
