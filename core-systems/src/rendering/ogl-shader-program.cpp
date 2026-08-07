#include "ogl-shader-program.h"
#include <ogl.h>
#include <logging/log-macros.h>

OGLShaderProgram::OGLShaderProgram() :
    m_program(0U)
{}

void OGLShaderProgram::Delete()
{
	glDeleteProgram(m_program);
	m_program = 0U;
}

bool OGLShaderProgram::TryCompile(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	if (m_program != 0U)
	{
		LOG_WARNING("Tried to compile shader more than once. Instruction will be ignored.");
		return true;
	}

	GLuint vs;
	GLuint fs;
	if (not TryCompileShader(GL_VERTEX_SHADER, vertexShaderSource, vs))
	{
		return false;
	}
	if (not TryCompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource, fs))
	{
		glDeleteShader(vs);
		return false;
	}

	bool linkedSuccessfully = TryLink(vs, fs);

	glDeleteShader(vs);
	glDeleteShader(fs);

    return linkedSuccessfully;
}

unsigned int OGLShaderProgram::GetProgram() const
{
    return m_program;
}

void OGLShaderProgram::Use() const
{
	if (m_program == 0U)
	{
		LOG_WARNING("Trying to use invalid shader program.");
	}
    glUseProgram(m_program);
}

void OGLShaderProgram::SetUniform(const char* name, const Vector3 value) const
{
	GLint loc = glGetUniformLocation(m_program, name);
	if (loc == -1)
	{
		LOG_ERROR(std::string("Tried to set unexisting uniform: ") + name);
	}
	glUniform3fv(loc, 1, reinterpret_cast<const GLfloat*>(&value));
}

void OGLShaderProgram::SetUniform(const char* name, const Vector4 value) const
{
	GLint loc = glGetUniformLocation(m_program, name);
	if (loc == -1)
	{
		LOG_ERROR(std::string("Tried to set unexisting uniform: ") + name);
	}
	glUniform4fv(loc, 1, reinterpret_cast<const GLfloat*>(&value));
}

void OGLShaderProgram::SetUniform(const char* name, const Color value) const
{
	GLint loc = glGetUniformLocation(m_program, name);
	if (loc == -1)
	{
		LOG_ERROR(std::string("Tried to set unexisting uniform: ") + name);
	}
	glUniform4fv(loc, 1, reinterpret_cast<const GLfloat*>(&value));
}

void OGLShaderProgram::SetUniform(const char* name, const Matrix4x4 & value) const
{
	GLint loc = glGetUniformLocation(m_program, name);
	if (loc == -1)
	{
		LOG_ERROR(std::string("Tried to set unexisting uniform: ") + name);
	}
	glUniformMatrix4fv(loc, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&value));
}

bool OGLShaderProgram::TryCompileShader(unsigned int shaderType, const char* source, unsigned int& out_shader) const
{
	out_shader = glCreateShader(shaderType);
	if (out_shader == 0U)
	{
		LOG_ERROR("Shader couldn't be created.");
		return false;
	}

	glShaderSource(out_shader, 1, &source, nullptr);

	glCompileShader(out_shader);

	GLint success = GL_FALSE;
	glGetShaderiv(out_shader, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint logLength = 0;
		glGetShaderiv(out_shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength < 1)
		{
			logLength = 1;
		}
		char* logString = new char[logLength];
		glGetShaderInfoLog(out_shader, logLength, nullptr, logString);
		LOG_ERROR(std::string("Shader failed to compile: ") + logString);
		delete[] logString;
		glDeleteShader(out_shader);
		out_shader = 0U;
		return false;
	}

	return true;
}

bool OGLShaderProgram::TryLink(const unsigned int vertexShader, const unsigned int fragmentShader)
{
	m_program = glCreateProgram();
	if (m_program == 0U)
	{
		LOG_ERROR("Shader program couldn't be created.");
		return false;
	}

	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);

	GLint linkStatus = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE)
	{
		GLint logLength;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength < 1)
		{
			logLength = 1;
		}
		char* logString = new char[logLength];
		glGetProgramInfoLog(m_program, logLength, nullptr, logString);
		LOG_ERROR(std::string("Shader program failed to link: ") + logString);
		delete[] logString;
		glDeleteProgram(m_program);
		m_program = 0U;
		return false;
	}

	return true;
}
