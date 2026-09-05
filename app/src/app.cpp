#include "app.h"
#include "3d-data.h"
#include <rendering/data-generation/mesh-2d/quad-mesh-2d-generator.h>
#include <rendering/data-generation/mesh-3d/plane-mesh-3d-generator.h>
#include <rendering/data-generation/mesh-3d/cube-mesh-3d-generator.h>
#include <rendering/data-generation/mesh-3d/terrain-mesh-3d-generator.h>
#include <rendering/data-generation/rendering-rule/unlit-rendering-rule-generator.h>
#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>
#include <rendering/data-generation/rendering-rule/canvas-rendering-rule-generator.h>
#include <rendering/data-generation/texture-2d/raw-data-texture-2d-generator.h>
#include <rendering/data-generation/texture-2d/checkerboard-texture-2d-generator.h>

class RandomRenderingRuleGenerator : public IRenderingRuleGenerator
{
	RenderingRuleDescriptor GenerateDescriptor() const override
	{
		static size_t n = 0U;
		n++;
		srand(time(NULL) * n);
		RenderingRuleDescriptor result = RenderingRuleDescriptor();
		result.sceneLighting = rand() % 2 == 0 ? new SceneLightingDescriptor{ .directionalLightCount = size_t(rand() % 3) } : nullptr;
		result.useProjection = rand() % 2 == 0;
		result.useViewCamera = rand() % 2 == 0;
		result.useModelTransform = rand() % 2 == 0;
		return result;
	}
};

void ProcessHeight(int x, int y, const int maxX, const int maxY, float& height);

void App::Init(GraphicsWindow& graphicsWindow)
{
	renderer = &graphicsWindow.GraphicsBackend().Renderer();
	resourceManager = &renderer->ResourceManager();
	window = &graphicsWindow.Window();
	input = &window->BasicInput();
	lastTime = window->GetTime();
}

void App::Start()
{
	const int terrainX = 30;
	const int terrainY = 30;

	Dimensions terrainGrid = { terrainX, terrainY };
	size_t terrainDataSize = terrainGrid.width * terrainGrid.height;
	Shared<FixedArray<float>> terrainData = Shared<FixedArray<float>>(new FixedArray<float>(terrainDataSize));

	for (int i = 0; i < terrainY; i++)
	{
		for (int j = 0; j < terrainX; j++)
		{
			float height = 0.0f;
			ProcessHeight(j, i, terrainX, terrainY, height);
			(*terrainData)[i * terrainX + j] = height;
		}
	}

	Shared<FixedArray<Color8>> patTexture = GeneratePatternTexture(resourceManager, 16, 16);

	SceneLightingDescriptor sceneLightingDescriptor
	{
		.directionalLightCount = 2U
	};

	worldRenderingRule = renderer->ResourceManager().CreateRenderingRule(LambertRenderingRuleGenerator(sceneLightingDescriptor));
	canvasRenderingRule = renderer->ResourceManager().CreateRenderingRule(CanvasRenderingRuleGenerator());
	terrainMesh = resourceManager->CreateMesh3D(TerrainMesh3DGenerator(terrainGrid, terrainData));
	terrainTexture = resourceManager->CreateTexture2D(CheckerboardTexture2DGenerator({ 2, 2 }, Color(0.85f, 0.85f, 0.80f), Color(0.15f, 0.15f, 0.2f)));
	cubeTexture = resourceManager->CreateTexture2D(RawDataTexture2DGenerator(patTexture, { 16, 16 }));
	cubeMesh = resourceManager->CreateMesh3D(CubeMesh3DGenerator(Vector3(3.0f, 3.0f, 3.0f)));
	quadMesh2D = resourceManager->CreateMesh2D(QuadMesh2DGenerator({ 64.0f, 64.0f }));
	
	cameraParameter = renderer->ParameterManager().CreateCamera3D();
	lightParameter = renderer->ParameterManager().CreateSceneLighting(sceneLightingDescriptor);
	transformParameter = renderer->ParameterManager().CreateTransform3D();
	cubeTransformParameter = renderer->ParameterManager().CreateTransform3D();
	transform2DParameter = renderer->ParameterManager().CreateTransform2D();

	cameraParameter->Camera().aspectRatio = window->GetAspectRatio();
	cameraParameter->Camera().vFOV = 3.1415f / 2.0f;
	cameraParameter->Camera().zNear = 0.1f;
	cameraParameter->Camera().zFar = 1000.0f;
	cameraParameter->Camera().position = Vector3(0.0f, 5.0f, 0.0f);

	lightParameter->AmbientLight() = Color(0.11f, 0.14f, 0.11f);
	lightParameter->DirectionalLights()[0U].diffuse = Color(0.2f, 0.35f, 1.0f);
	lightParameter->DirectionalLights()[0U].direction = Vector3(1.0f, -0.9f, 0.5f).Normalized();
	lightParameter->DirectionalLights()[0U].intensity = 1.0f;
	lightParameter->DirectionalLights()[1U].diffuse = Color(0.85f, 0.3f, 0.1f);
	lightParameter->DirectionalLights()[1U].direction = Vector3(-1.0f, -0.15f, 0.05f).Normalized();
	lightParameter->DirectionalLights()[1U].intensity = 1.2f;

	transformParameter->Transform().scale = { 200.0f, 1.0f, 200.0f };
	transformParameter->Transform().position = {
		-transformParameter->Transform().scale.x / 2.0f,
		0.0f,
		-transformParameter->Transform().scale.z / 2.0f 
	};

	cubeTransformParameter->Transform().position = {25.0f, 10.0f, -40.0f};
	cubeTransformParameter->Transform().scale = {3.0f, 5.0f, 8.0f};

	transform2DParameter->Transform().position = { 0.0f, 0.0f };
}

void App::Update()
{
	const float deltaTime = window->GetTime() - lastTime;
	lastTime = window->GetTime();

	// Input, camera and movement
	if (input->IsKeyJustPressed(KeyboardKey::SPACE))
	{
		renderer->ResourceManager().Destroy(worldRenderingRule);
		worldRenderingRule = renderer->ResourceManager().CreateRenderingRule(RandomRenderingRuleGenerator());
	}
	if (input->IsMouseButtonDown(MouseButton::LEFT))
	{
		Vector2 mouseMovement = input->GetMouseMovement();
		cameraParameter->Camera().rotation.y -= mouseMovement.x * 0.01f;
		cameraParameter->Camera().rotation.x -= mouseMovement.y * 0.01f;
	}
	{
		Vector3& pos = cameraParameter->Camera().position;
		Vector3& rot = cameraParameter->Camera().rotation;
		Vector2 dir = {
			float(input->IsKeyDown(KeyboardKey::A) - input->IsKeyDown(KeyboardKey::D)),
			float(input->IsKeyDown(KeyboardKey::S) - input->IsKeyDown(KeyboardKey::W))
		};
		pos += Vector3(
			dir.x * -cosf(rot.y) + dir.y * sinf(rot.y),
			float(input->IsKeyDown(KeyboardKey::E)) - float(input->IsKeyDown(KeyboardKey::Q)),
			dir.y * cosf(rot.y) + dir.x * sinf(rot.y)
		) * deltaTime * 15.0f;
	}
	cubeTransformParameter->Transform().rotation.z += deltaTime;
	cubeTransformParameter->Transform().rotation.x += deltaTime * 0.025f;
	transform2DParameter->Transform().position = { (renderer->GetViewportSize().width - 64) * std::sin(lastTime * 2.0f) / 2.0f + (renderer->GetViewportSize().width - 64) / 2.0f, 0.0f };

	// State updating
	renderer->SetClearColor({ 0.05f, 0.1f, 0.2f });
	cameraParameter->Camera().aspectRatio = window->GetAspectRatio();

	// State binding
	cameraParameter->Bind();
	lightParameter->Bind();

	// Drawing 3D
	worldRenderingRule->Bind();
	transformParameter->Bind();
	terrainTexture->Bind();
	terrainMesh->Draw();
	cubeTransformParameter->Bind();
	cubeTexture->Bind();
	cubeMesh->Draw();

	// Drawing 2D
	canvasRenderingRule->Bind();
	transform2DParameter->Bind();
	quadMesh2D->Draw();
}

void ProcessHeight(int x, int y, const int maxX, const int maxY, float& height)
{
	const float nx = static_cast<float>(x) / maxX;
	const float ny = static_cast<float>(y) / maxY;

	height =
		std::sin(nx * 3.14159f * 2.0f) * 5.0f +
		std::cos(ny * 3.14159f * 2.5f) * 3.0f +
		std::sin((nx + ny) * 3.14159f * 3.0f) * 2.0f;
}
