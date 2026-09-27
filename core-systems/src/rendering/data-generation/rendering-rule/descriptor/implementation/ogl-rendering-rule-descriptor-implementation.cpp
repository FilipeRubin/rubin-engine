#include "ogl-rendering-rule-descriptor-implementation.h"

OGLRenderingRuleDescriptorImplementation::OGLRenderingRuleDescriptorImplementation() :
    m_parameters({})
{}

std::string& OGLRenderingRuleDescriptorImplementation::VertexSource()
{
    return m_vertexSource;
}

std::string& OGLRenderingRuleDescriptorImplementation::FragmentSource()
{
    return m_fragmentSource;
}

FixedArray<IRenderParameter**>& OGLRenderingRuleDescriptorImplementation::Parameters()
{
    return m_parameters;
}
