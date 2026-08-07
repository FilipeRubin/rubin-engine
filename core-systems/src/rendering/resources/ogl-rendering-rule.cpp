#include "ogl-rendering-rule.h"
#include <rendering/ogl-renderer.h>
#include <logging/log-macros.h>

OGLRenderingRule::OGLRenderingRule(OGLRenderer& renderer, RenderingRuleDescriptor descriptor) :
	OGLRendererUser(renderer),
	m_descriptor(descriptor)
{
}

void OGLRenderingRule::Bind()
{
	GetRenderer().SetCurrentRenderingRule(this);
}

const RenderingRuleDescriptor& OGLRenderingRule::GetDescriptor() const
{
	return m_descriptor;
}

bool OGLRenderingRule::IsValid() const
{
	return true;
}

void OGLRenderingRule::Create()
{
	// Renderer rule is a logical resource, even though it doesn`t allocate anything on the GPU directly
}

void OGLRenderingRule::Destroy()
{
}
