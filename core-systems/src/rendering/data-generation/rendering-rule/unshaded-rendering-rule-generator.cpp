#include <rendering/data-generation/rendering-rule/unshaded-rendering-rule-generator.h>

RenderingRuleDescriptor UnshadedRenderingRuleGenerator::GenerateDescriptor() const
{
    RenderingRuleDescriptor result{};

    result.useDirectionalLight = false;
    result.useCamera3D = true;
    result.useTransform3D = true;

    return result;
}
