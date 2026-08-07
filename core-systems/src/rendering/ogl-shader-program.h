#pragma once

class OGLShaderProgram final
{
public:
	OGLShaderProgram();
	void Delete();
	bool TryCompile(const char* vertexShaderSource, const char* fragmentShaderSource);
	unsigned int GetProgram() const;
	void Use() const;
private:
	unsigned int m_program;
	bool TryCompileShader(unsigned int shaderType, const char* source, unsigned int& out_shader) const;
	bool TryLink(const unsigned int vertexShader, const unsigned int fragmentShader);
};
