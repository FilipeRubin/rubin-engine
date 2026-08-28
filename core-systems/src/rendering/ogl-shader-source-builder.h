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
	std::string GenerateVertexLayout() const;
	std::string GenerateVertexOutput() const;
	std::string GenerateVertexUniforms() const;
	std::string GenerateVertexLogic() const;
	std::string GenerateFragmentStructs() const;
	std::string GenerateFragmentInput() const;
	std::string GenerateFragmentOutput() const;
	std::string GenerateFragmentUniforms() const;
	std::string GenerateFragmentLogic() const;
};
