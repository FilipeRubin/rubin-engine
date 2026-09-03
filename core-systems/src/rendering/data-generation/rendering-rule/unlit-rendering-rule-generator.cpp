#include <rendering/data-generation/rendering-rule/unlit-rendering-rule-generator.h>

RenderingRuleDescriptor UnlitRenderingRuleGenerator::GenerateDescriptor() const
{
    RenderingRuleDescriptor result{};

    result.sceneLighting = nullptr;
    result.useProjection = true;
    result.useViewCamera = true;
    result.useModelTransform = true;

    return result;
}
