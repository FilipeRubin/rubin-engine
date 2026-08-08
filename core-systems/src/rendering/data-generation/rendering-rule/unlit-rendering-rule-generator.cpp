#include <rendering/data-generation/rendering-rule/unlit-rendering-rule-generator.h>

RenderingRuleDescriptor UnlitRenderingRuleGenerator::GenerateDescriptor() const
{
    RenderingRuleDescriptor result{};

    result.useDirectionalLight = false;
    result.useViewProjection = true;
    result.useModelMatrix = true;

    return result;
}
