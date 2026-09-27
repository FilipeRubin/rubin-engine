#include "ogl-rendering-rule.h"
#include <rendering/ogl-renderer.h>
#include <rendering/data-generation/rendering-rule/descriptor/implementation/ogl-rendering-rule-descriptor-implementation.h>

OGLRenderingRule::OGLRenderingRule(OGLRenderer& renderer, RenderingRuleDescriptor descriptor) :
	OGLRendererUser(renderer),
	m_descriptor(descriptor)
{
}

void OGLRenderingRule::Bind()
{
	Renderer().SetCurrentRenderingRule(this);
	m_shaderProgram.Use();
	auto& desc = *static_cast<OGLRenderingRuleDescriptorImplementation*>(m_descriptor.GetImplementation());
	FixedArray<IRenderParameter**>& params = desc.Parameters();
	for (size_t i = 0; i < params.GetElementCount(); i++)
	{
		if (*params[i] != nullptr)
			(*params[i])->Bind();
	}
}

bool OGLRenderingRule::IsValid() const
{
	return m_shaderProgram.GetProgram() != 0U;
}

void OGLRenderingRule::Create()
{
	auto& desc = *static_cast<OGLRenderingRuleDescriptorImplementation*>(m_descriptor.GetImplementation());
	m_shaderProgram.TryCompile(desc.VertexSource().c_str(), desc.FragmentSource().c_str());
}

void OGLRenderingRule::Destroy()
{
	m_shaderProgram.Delete();
}

OGLShaderProgram& OGLRenderingRule::ShaderProgram()
{
	return m_shaderProgram;
}
