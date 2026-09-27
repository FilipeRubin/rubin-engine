#include "ogl-render-parameter-implementation.h"

OGLRenderParameterImplementation::OGLRenderParameterImplementation(void(*setUniformFunc)(OGLRenderer& renderer, OGLShaderProgram& program, IRenderParameter* param), OGLRenderer& renderer) :
	m_setUniformFunc(setUniformFunc),
	m_renderer(renderer)
{
}
