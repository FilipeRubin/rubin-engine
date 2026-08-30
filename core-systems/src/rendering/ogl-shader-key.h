#pragma once
#include <types/rendering-rule-descriptor.h>
#include <types/mesh-type.h>
#include <functional>

class OGLShaderKey final
{
public:
	OGLShaderKey(const RenderingRuleDescriptor& descriptor, MeshType meshType);
	const RenderingRuleDescriptor& GetDescriptor() const;
	MeshType GetMeshType() const;
	bool operator==(const OGLShaderKey& other) const = default;
	struct Hash
	{
		std::size_t operator()(const OGLShaderKey& key) const noexcept
		{
			std::size_t h1 = std::hash<bool>{}(key.m_descriptor.sceneLighting != nullptr);
			std::size_t h2 = std::hash<bool>{}(key.m_descriptor.useProjection2D);
			std::size_t h3 = std::hash<bool>{}(key.m_descriptor.useProjectionView3D);
			std::size_t h4 = std::hash<bool>{}(key.m_descriptor.useModel2D);
			std::size_t h5 = std::hash<bool>{}(key.m_descriptor.useModel3D);
			std::size_t h6 = std::hash<MeshType>{}(key.m_meshType);

			return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3) ^ (h5 << 4) ^ (h6 << 5);
		}
	};
private:
	RenderingRuleDescriptor m_descriptor;
	MeshType m_meshType;
};
