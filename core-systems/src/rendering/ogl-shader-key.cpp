#include "ogl-shader-key.h"

OGLShaderKey::OGLShaderKey(const RenderingRuleDescriptor& descriptor, MeshType meshType) :
	m_descriptor(descriptor),
	m_meshType(meshType)
{
}

const RenderingRuleDescriptor& OGLShaderKey::GetDescriptor() const
{
	return m_descriptor;
}

MeshType OGLShaderKey::GetMeshType() const
{
	return m_meshType;
}

size_t OGLShaderKey::Hash::operator()(const OGLShaderKey& key) const noexcept
{
	size_t h1 = RenderingRuleDescriptor::Hash{}(key.GetDescriptor());
	size_t h2 = std::hash<MeshType>{}(key.GetMeshType());

	return h1 ^ (h2 << 1);
}
