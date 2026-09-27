#pragma once
#include <rendering/i-renderer-managed.h>
#include <rendering/resources/i-rendering-rule.h>
#include <rendering/ogl-renderer-user.h>
#include <rendering/ogl-shader-program.h>
#include <rendering/data-generation/rendering-rule/descriptor/rendering-rule-descriptor.h>

class OGLRenderingRule : public IRenderingRule, public IRendererManaged, public OGLRendererUser
{
public:
	OGLRenderingRule(OGLRenderer& renderer, RenderingRuleDescriptor descriptor);
	void Bind() override;
	bool IsValid() const override;
	void Create() override;
	void Destroy() override;
	OGLShaderProgram& ShaderProgram();
private:
	RenderingRuleDescriptor m_descriptor;
	OGLShaderProgram m_shaderProgram;
};
