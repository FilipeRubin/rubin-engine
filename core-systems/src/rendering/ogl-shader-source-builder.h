#pragma once
#include "ogl-shader-key.h"
#include <string>

class OGLShaderSourceBuilder final
{
public:
	OGLShaderSourceBuilder(OGLShaderKey key);
	std::string GenerateVertexSource() const;
	std::string GenerateFragmentSource() const;
private:
	OGLShaderKey m_key;
	std::string GenerateVersion() const;
	std::string GenerateDefines() const;
	std::string GenerateUniforms() const;
};
