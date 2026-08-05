#pragma once
#include "resources/ogl-rendering-rule.h"
#include "ogl-shader-key.h"
#include <types/mesh-type.h>
#include <unordered_map>

class OGLShaderProgramCache final : public OGLRendererUser
{
public:
	OGLShaderProgramCache(OGLRenderer& renderer);
	~OGLShaderProgramCache();
	void BindOrCreate(const OGLRenderingRule& renderingRule, MeshType meshType);
	void SetUniforms(const OGLRenderingRule& renderingRule);
private:
	unsigned int m_currentProgram;
	std::unordered_map<OGLShaderKey, unsigned int, OGLShaderKey::Hash> m_cache;
	unsigned int CreateProgram(const OGLShaderKey& key);
};
