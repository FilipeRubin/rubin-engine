#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>
#include <logging/log-macros.h>

RenderingRuleDescriptor LambertRenderingRuleGenerator::GenerateDescriptor() const
{
    RenderingRuleDescriptor result{};

    result.sceneLighting = Shared<SceneLightingDescriptor>(new SceneLightingDescriptor());
    LOG_WARNING("Remove magic number after testing.");
    result.sceneLighting->directionalLightCount = 2U;
    result.useProjectionView = true;
    result.useModelMatrix = true;

    return result;
}
