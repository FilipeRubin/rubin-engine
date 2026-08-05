#pragma once
#include <rendering/i-renderer-managed.h>
#include <rendering/resources/i-rendering-rule.h>
#include <rendering/ogl-renderer-user.h>

class OGLRenderingRule : public IRenderingRule, public IRendererManaged, public OGLRendererUser
{
public:
	OGLRenderingRule(OGLRenderer& renderer, RenderingRuleDescriptor descriptor);
	void Bind() override;
	const RenderingRuleDescriptor& GetDescriptor() const override;
	bool IsValid() const override;
	void Create() override;
	void Destroy() override;
private:
	RenderingRuleDescriptor m_descriptor;
};
