#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>

RenderingRuleDescriptor LambertRenderingRuleGenerator::GenerateDescriptor() const
{
    RenderingRuleDescriptor result{};

    result.useDirectionalLight = true;
    result.useCamera3D = true;
    result.useTransform3D = true;

    return result;
}
