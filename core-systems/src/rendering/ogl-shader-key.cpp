#include "ogl-shader-key.h"
#include <logging/log-macros.h>

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
