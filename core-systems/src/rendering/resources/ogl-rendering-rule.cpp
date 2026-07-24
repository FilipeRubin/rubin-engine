#include "ogl-rendering-rule.h"
#include <ogl.h>
#include <types/color.h>
#include <logging/log-macros.h>

OGLRenderingRule::OGLRenderingRule(const char* vertexShaderSource, const char* fragmentShaderSource) :
	m_program(0U),
	m_vertexShaderSource(vertexShaderSource),
	m_fragmentShaderSource(fragmentShaderSource)
{
}

void OGLRenderingRule::Bind()
{
	glUseProgram(m_program);
}

bool OGLRenderingRule::IsValid() const
{
	return m_program != 0U;
}

void OGLRenderingRule::Create()
{
	LOG_DEBUG("Creating OpenGL rendering rule.");
	m_program = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vs, 1, &m_vertexShaderSource, nullptr);
	glShaderSource(fs, 1, &m_fragmentShaderSource, nullptr);
	glCompileShader(vs);
	glCompileShader(fs);
	glAttachShader(m_program, vs);
	glAttachShader(m_program, fs);
	glLinkProgram(m_program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	m_vertexShaderSource = nullptr;
	m_fragmentShaderSource = nullptr;
	LOG_DEBUG("OpenGL rendering rule created.");
}

void OGLRenderingRule::Destroy()
{
	LOG_DEBUG("Destroying OpenGL rendering rule.");
	glDeleteProgram(m_program);
	m_program = 0U;
}

void OGLRenderingRule::SetUniform(const char* name, const Vector3& value)
{
	GLint location = glGetUniformLocation(m_program, name);
	glUniform3fv(location, 1, reinterpret_cast<const GLfloat*>(&value));
}

void OGLRenderingRule::SetUniform(const char* name, const Vector4& value)
{
	GLint location = glGetUniformLocation(m_program, name);
	glUniform4fv(location, 1, reinterpret_cast<const GLfloat*>(&value));
}

void OGLRenderingRule::SetUniform(const char* name, const Color& value)
{
	GLint location = glGetUniformLocation(m_program, name);
	glUniform4fv(location, 1, reinterpret_cast<const GLfloat*>(&value));
}

void OGLRenderingRule::SetUniform(const char* name, const Matrix4x4& value)
{
	GLint location = glGetUniformLocation(m_program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&value));
}
