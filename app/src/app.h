#pragma once
#include "graphics-window.h"

class App
{
public:
	void Init(GraphicsWindow& graphicsWindow);
	void Start();
	void Update();
private:
	IRenderer* renderer = nullptr;
	IRendererResourceManager* resourceManager = nullptr;
	IWindow* window = nullptr;
	IBasicInput* input = nullptr;

	IRenderingRule* worldRenderingRule = nullptr;
	IRenderingRule* canvasRenderingRule = nullptr;
	IRenderingRule* currentRenderingRule = nullptr;
	IMesh3D* terrainMesh = nullptr;
	IMesh3D* cubeMesh = nullptr;
	IMesh2D* quadMesh2D = nullptr;
	ITexture2D* terrainTexture = nullptr;
	ITexture2D* cubeTexture = nullptr;

	ICamera3DParameter* cameraParameter = nullptr;
	ISceneLightingParameter* lightParameter = nullptr;
	ITransform3DParameter* transformParameter = nullptr;
	ITransform3DParameter* cubeTransformParameter = nullptr;
	ITransform2DParameter* transform2DParameter = nullptr;

	float lightRotation = 0.0f;
	float cubeHeightOffset = 0.0f;

	float lastTime = 0.0f;
};
