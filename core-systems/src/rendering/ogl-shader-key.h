#pragma once
#include <types/rendering-rule-descriptor.h>
#include <types/mesh-type.h>

class OGLShaderKey final
{
public:
	OGLShaderKey(const RenderingRuleDescriptor& descriptor, MeshType meshType);
	const RenderingRuleDescriptor& GetDescriptor() const;
	MeshType GetMeshType() const;
	bool operator==(const OGLShaderKey& other) const = default;
	struct Hash
	{
		size_t operator()(const OGLShaderKey& key) const noexcept
		{
			size_t h1 = RenderingRuleDescriptor::Hash{}(key.GetDescriptor());
			size_t h2 = std::hash<MeshType>{}(key.GetMeshType());

			return h1 ^ (h2 << 1);
		}
	};
private:
	RenderingRuleDescriptor m_descriptor;
	MeshType m_meshType;
};
