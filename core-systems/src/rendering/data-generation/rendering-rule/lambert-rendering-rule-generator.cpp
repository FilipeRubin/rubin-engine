#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>
#include <logging/log-macros.h>

LambertRenderingRuleGenerator::LambertRenderingRuleGenerator(const SceneLightingDescriptor& lightingDescriptor) :
    m_lightingDescriptor(lightingDescriptor)
{}

RenderingRuleDescriptor LambertRenderingRuleGenerator::GenerateDescriptor() const
{
    RenderingRuleDescriptor result{};

    result.sceneLighting = MakeShared<SceneLightingDescriptor>(m_lightingDescriptor);
    result.useProjection = true;
    result.useViewCamera = true;
    result.useModelTransform = true;

    return result;
}
