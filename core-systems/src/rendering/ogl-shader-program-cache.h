#pragma once
#include "resources/ogl-rendering-rule.h"
#include "ogl-shader-key.h"
#include <types/mesh-type.h>
#include <unordered_map>

class OGLShaderProgram;

class OGLShaderProgramCache final : public OGLRendererUser
{
public:
	OGLShaderProgramCache(OGLRenderer& renderer);
	~OGLShaderProgramCache();
	void BindOrCreate(const OGLRenderingRule& renderingRule, MeshType meshType);
	void SetUniforms(const OGLShaderKey& key);
private:
	OGLShaderProgram* m_currentProgram;
	std::unordered_map<OGLShaderKey, OGLShaderProgram*, OGLShaderKey::Hash> m_cache;
	OGLShaderProgram* CreateProgram(const OGLShaderKey& key);
};
