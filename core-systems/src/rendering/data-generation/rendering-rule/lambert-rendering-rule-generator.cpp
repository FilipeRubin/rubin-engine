#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>
#include <logging/log-macros.h>

LambertRenderingRuleGenerator::LambertRenderingRuleGenerator(const SceneLightingDescriptor& lightingDescriptor) :
    m_lightingDescriptor(lightingDescriptor)
{}

RenderingRuleDescriptor LambertRenderingRuleGenerator::GenerateDescriptor() const
{
    RenderingRuleDescriptor result{};

    result.sceneLighting = Shared<SceneLightingDescriptor>(new SceneLightingDescriptor(m_lightingDescriptor));
    result.useProjectionView = true;
    result.useModelMatrix = true;

    return result;
}
