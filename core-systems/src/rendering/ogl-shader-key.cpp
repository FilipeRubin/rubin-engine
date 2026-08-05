#include "ogl-shader-key.h"
#include <logging/log-macros.h>

OGLShaderKey::OGLShaderKey(const RenderingRuleDescriptor& descriptor, MeshType meshType) :
	m_descriptor(descriptor),
	m_meshType(meshType)
{
	// LOG_WARNING("Needs to be optimized. Do not store the entire RenderingRuleDescriptor object inside this.");
}
