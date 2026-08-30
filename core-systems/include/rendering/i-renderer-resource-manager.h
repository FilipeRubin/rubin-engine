#pragma once
#include "data-generation/mesh-2d/i-mesh-2d-generator.h"
#include "data-generation/mesh-3d/i-mesh-3d-generator.h"
#include "data-generation/rendering-rule/i-rendering-rule-generator.h"
#include "data-generation/texture-2d/i-texture-2d-generator.h"
#include "resources/i-rendering-rule.h"
#include "resources/i-mesh-2d.h"
#include "resources/i-mesh-3d.h"
#include "resources/i-texture-2d.h"
#include "resources/i-renderer-resource.h"
#include <types/color8.h>

class IRendererResourceManager
{
public:
	virtual ~IRendererResourceManager() = default;
	virtual IRenderingRule* CreateRenderingRule(const IRenderingRuleGenerator& generator) = 0;
	virtual IMesh2D* CreateMesh2D(const IMesh2DGenerator& generator) = 0;
	virtual IMesh3D* CreateMesh3D(const IMesh3DGenerator& generator) = 0;
	virtual ITexture2D* CreateTexture2D(const ITexture2DGenerator& generator) = 0;
	template<typename T>
	void Destroy(T*& resource)
	{
		DestroyImpl(resource);
		resource = nullptr;
	}
protected:
	virtual void DestroyImpl(IRendererResource* resource) = 0;
};
