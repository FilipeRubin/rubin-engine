#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>

RenderingRuleDescriptor LambertRenderingRuleGenerator::GenerateDescriptor() const
{
    RenderingRuleDescriptor result{};

    result.useDirectionalLight = true;
    result.useViewProjection = true;
    result.useModelMatrix = true;

    return result;
}
