#pragma once
#include "ogl-render-parameters-state.h"
#include "ogl-shader-program-cache.h"
#include <rendering/i-renderer.h>
#include <ogl-graphics-backend.h>

class OGLRenderer final : public IRenderer
{
public:
	OGLRenderer(OGLGraphicsBackend* backend);
	~OGLRenderer();
	void ClearScreen() const override;
	void SetClearColor(const Color& color) override;
	void SetViewportSize(const Dimensions& size) override;
	IRendererParameterManager* GetParameterManager() const override;
	IRendererResourceManager* GetResourceManager() const override;
	OGLRenderingRule* GetCurrentRenderingRule() const;
	void SetCurrentRenderingRule(OGLRenderingRule* renderingRule);
	OGLRenderParametersState& RenderParametersState();
	OGLShaderProgramCache& ShaderCache();
private:
	OGLRenderingRule* m_currentRenderingRule;
	OGLRenderParametersState m_parametersState;
	OGLShaderProgramCache m_shaderCache;
	IRendererParameterManager* m_parameterManager;
	IRendererResourceManager* m_resourceManager;
};
