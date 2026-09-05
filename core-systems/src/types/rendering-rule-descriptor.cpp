#include <types/rendering-rule-descriptor.h>

static bool compareSceneLightingDescriptor(const SceneLightingDescriptor* a, const SceneLightingDescriptor* b);

size_t RenderingRuleDescriptor::Hash::operator()(const RenderingRuleDescriptor& desc) const noexcept
{
	size_t hashes[]
	{
		std::hash<bool>{}(desc.useProjection),
		std::hash<bool>{}(desc.useViewCamera),
		std::hash<bool>{}(desc.useModelTransform),
		desc.sceneLighting != nullptr
			? SceneLightingDescriptor::Hash{}(*desc.sceneLighting) + 1U
			: std::hash<std::size_t>{}(0U)
	};

	size_t result = hashes[0];

	for (size_t i = 1U; i < sizeof(hashes) / sizeof(hashes[0]); i++)
	{
		result ^= hashes[i] << i;
	}

	return result;
}

bool RenderingRuleDescriptor::operator==(const RenderingRuleDescriptor& other) const
{
	return (
		useProjection == other.useProjection and
		useViewCamera == other.useViewCamera and
		useModelTransform == other.useModelTransform and
		compareSceneLightingDescriptor(sceneLighting.Get(), other.sceneLighting.Get())
	);
}

bool compareSceneLightingDescriptor(const SceneLightingDescriptor* a, const SceneLightingDescriptor* b)
{
	if (a == b)
		return true;

	if (a == nullptr or b == nullptr)
		return false;

	return *a == *b;
}
