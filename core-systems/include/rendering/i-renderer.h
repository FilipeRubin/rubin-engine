#pragma once
#include "i-renderer-parameter-manager.h"
#include "i-renderer-resource-manager.h"

class IRenderer
{
public:
	virtual ~IRenderer() = default;
	virtual void ClearScreen() const = 0;
	virtual void SetClearColor(const Color& color) = 0;
	virtual void SetViewportSize(const Dimensions& size) = 0;
	virtual IRendererParameterManager& ParameterManager() const = 0;
	virtual IRendererResourceManager& ResourceManager() const = 0;
};
