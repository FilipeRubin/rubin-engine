#pragma once
#include <rendering/parameters/i-render-parameter.h>
#include <rendering/parameters/implementation/i-render-parameter-implementation.h>
#include <rendering/ogl-shader-program.h>
#include <rendering/ogl-renderer.h>

class OGLRenderParameterImplementation : public IRenderParameterImplementation
{
public:
	OGLRenderParameterImplementation(void(*setUniformFunc)(OGLRenderer& renderer, OGLShaderProgram& program, IRenderParameter* param), OGLRenderer& renderer);
	inline void SetUniform(OGLShaderProgram& program, IRenderParameter* param)
	{
		m_setUniformFunc(m_renderer, program, param);
	}
private:
	void(*m_setUniformFunc)(OGLRenderer& renderer, OGLShaderProgram& program, IRenderParameter* param);
	OGLRenderer& m_renderer;
};
