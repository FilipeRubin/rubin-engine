#include "ogl-renderer-user.h"
#include "ogl-renderer.h"

OGLRendererUser::OGLRendererUser(OGLRenderer& renderer) :
	m_renderer(renderer)
{}

OGLRenderer& OGLRendererUser::Renderer()
{
	return m_renderer;
}
