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

	IRenderingRule* lambertRenderingRule = nullptr;
	IRenderingRule* unshadedRenderingRule = nullptr;
	IRenderingRule* currentRenderingRule = nullptr;
	IMesh3D* terrainMesh = nullptr;
	IMesh3D* cubeMesh = nullptr;
	ITexture2D* terrainTexture = nullptr;
	ITexture2D* cubeTexture = nullptr;

	ICamera3DParameter* cameraParameter = nullptr;
	IDirectionalLightParameter* lightParameter = nullptr;
	ITransform3DParameter* transformParameter = nullptr;
	ITransform3DParameter* cubeTransformParameter = nullptr;

	bool useLambertRenderingRule = false;

	float lightRotation = 0.0f;
	float cubeHeightOffset = 0.0f;

	float lastTime = 0.0f;
};
