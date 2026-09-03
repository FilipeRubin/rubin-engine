#include <rendering/data-generation/rendering-rule/canvas-rendering-rule-generator.h>

RenderingRuleDescriptor CanvasRenderingRuleGenerator::GenerateDescriptor() const
{
    RenderingRuleDescriptor result{};

    result.sceneLighting = nullptr;
    result.useProjection = true;
    result.useViewCamera = false;
    result.useModelTransform = true;

    return result;
}
