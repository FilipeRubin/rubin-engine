#include <rendering/data-generation/rendering-rule/canvas-rendering-rule-generator.h>

RenderingRuleDescriptor CanvasRenderingRuleGenerator::GenerateDescriptor() const
{
    return {
        .useProjection2D = true,
        .useProjectionView3D = false,
        .useModel2D = true,
        .useModel3D = false,
    };
}
