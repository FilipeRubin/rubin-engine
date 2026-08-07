#pragma once
#include <math/vector3.h>
#include <math/vector4.h>
#include <math/matrix4x4.h>
#include <types/color.h>

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
	unsigned int m_program;
	bool TryCompileShader(unsigned int shaderType, const char* source, unsigned int& out_shader) const;
	bool TryLink(const unsigned int vertexShader, const unsigned int fragmentShader);
};
