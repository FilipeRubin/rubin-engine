#include <rendering/data-generation/rendering-rule/descriptor/rendering-rule-descriptor.h>
#include "implementation/ogl-rendering-rule-descriptor-implementation.h"

RenderingRuleDescriptor::RenderingRuleDescriptor() :
    m_impl(new OGLRenderingRuleDescriptorImplementation())
{}

IRenderingRuleDescriptorImplementation* RenderingRuleDescriptor::GetImplementation()
{
    return m_impl.Get();
}
