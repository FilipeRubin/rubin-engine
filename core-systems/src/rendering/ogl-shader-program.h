#pragma once
#include <math/vector3.h>
#include <math/vector4.h>
#include <math/matrix4x4.h>
#include <types/color.h>
#include <unordered_map>
#include <string>

class OGLShaderProgram final
{
public:
	OGLShaderProgram();
	void Delete();
	bool TryCompile(const char* vertexShaderSource, const char* fragmentShaderSource);
	unsigned int GetProgram() const;
	void Use() const;
	void SetUniform(const char* name, const Vector3 value) const;
	void SetUniform(const char* name, const Vector4 value) const;
	void SetUniform(const char* name, const Color value) const;
	void SetUniform(const char* name, const Matrix4x4& value) const;
private:
	static unsigned int s_currentProgram;
	unsigned int m_program;
	mutable std::unordered_map<std::string, int> m_cachedUniforms;
	bool TryCompileShader(unsigned int shaderType, const char* source, unsigned int& out_shader) const;
	bool TryLink(const unsigned int vertexShader, const unsigned int fragmentShader);
	int GetUniform(const char* const name) const;
};
