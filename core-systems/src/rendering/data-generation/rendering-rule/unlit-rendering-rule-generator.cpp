#include <rendering/data-generation/rendering-rule/unlit-rendering-rule-generator.h>

RenderingRuleDescriptor UnlitRenderingRuleGenerator::GenerateDescriptor() const
{
    RenderingRuleDescriptor result{};

    result.sceneLighting = nullptr;
    result.useProjectionView3D = true;
    result.useModel3D = true;

    return result;
}
