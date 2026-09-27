#pragma once
#include "ogl-render-parameters-state.h"
#include "ogl-shader-program.h"
#include <rendering/i-renderer.h>
#include <rendering/resources/ogl-rendering-rule.h>
#include <ogl-graphics-backend.h>

class OGLRenderer final : public IRenderer
{
public:
	OGLRenderer(OGLGraphicsBackend* backend, Dimensions viewportSize);
	~OGLRenderer();
	void ClearScreen() const override;
	Dimensions GetViewportSize() const override;
	void SetClearColor(const Color& color) override;
	void SetViewportSize(const Dimensions& size) override;
	IRendererParameterManager& ParameterManager() const override;
	IRendererResourceManager& ResourceManager() const override;
	OGLRenderingRule* GetCurrentRenderingRule() const;
	void SetCurrentRenderingRule(OGLRenderingRule* renderingRule);
	OGLRenderParametersState& RenderParametersState();
private:
	OGLRenderParametersState m_parametersState;
	OGLRenderingRule* m_currentRenderingRule;
	IRendererParameterManager* m_parameterManager;
	IRendererResourceManager* m_resourceManager;
	Dimensions m_cachedViewportSize;
};
