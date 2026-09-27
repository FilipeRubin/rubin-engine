#pragma once
#include <rendering/data-generation/rendering-rule/descriptor/implementation/i-rendering-rule-descriptor-implementation.h>
#include <rendering/parameters/i-render-parameter.h>
#include <containers/fixed-array.h>
#include <string>

class OGLRenderingRuleDescriptorImplementation : public IRenderingRuleDescriptorImplementation
{
public:
	OGLRenderingRuleDescriptorImplementation();
	std::string& VertexSource();
	std::string& FragmentSource();
	FixedArray<IRenderParameter**>& Parameters();
private:
	std::string m_vertexSource;
	std::string m_fragmentSource;
	FixedArray<IRenderParameter**> m_parameters;
};