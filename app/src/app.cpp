#include "app.h"
#include "3d-data.h"
#include <rendering/data-generation/mesh-3d/plane-mesh-3d-generator.h>
#include <rendering/data-generation/mesh-3d/cube-mesh-3d-generator.h>
#include <rendering/data-generation/mesh-3d/terrain-mesh-3d-generator.h>
#include <rendering/data-generation/rendering-rule/unshaded-rendering-rule-generator.h>
#include <rendering/data-generation/rendering-rule/lambert-rendering-rule-generator.h>
#include <rendering/data-generation/texture-2d/raw-data-texture-2d-generator.h>
#include <rendering/data-generation/texture-2d/checkerboard-texture-2d-generator.h>

void ProcessHeight(int x, int y, const int maxX, const int maxY, float& height);

void App::Init(GraphicsWindow& graphicsWindow)
{
	renderer = graphicsWindow.GetGraphicsBackend()->GetRenderer();
	resourceManager = renderer->GetResourceManager();
	window = graphicsWindow.GetWindow();
	input = window->GetBasicInput();
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

	lambertRenderingRule = renderer->GetResourceManager()->CreateRenderingRule(LambertRenderingRuleGenerator());
	unshadedRenderingRule = renderer->GetResourceManager()->CreateRenderingRule(UnshadedRenderingRuleGenerator());
	terrainMesh = resourceManager->CreateMesh3D(TerrainMesh3DGenerator(terrainGrid, terrainData));
	terrainTexture = resourceManager->CreateTexture2D(CheckerboardTexture2DGenerator({ 2, 2 }, Color(0.85f, 0.85f, 0.80f), Color(0.15f, 0.15f, 0.2f)));
	cubeTexture = resourceManager->CreateTexture2D(RawDataTexture2DGenerator(patTexture, { 16, 16 }));
	cubeMesh = resourceManager->CreateMesh3D(CubeMesh3DGenerator(Vector3(3.0f, 3.0f, 3.0f)));

	cameraParameter = renderer->GetParameterManager()->CreateCamera3D();
	lightParameter = renderer->GetParameterManager()->CreateDirectionalLight();
	transformParameter = renderer->GetParameterManager()->CreateTransform3D();
	cubeTransformParameter = renderer->GetParameterManager()->CreateTransform3D();

	cameraParameter->Camera().aspectRatio = window->GetAspectRatio();
	cameraParameter->Camera().vFOV = 3.1415f / 2.0f;
	cameraParameter->Camera().zNear = 0.1f;
	cameraParameter->Camera().zFar = 1000.0f;
	cameraParameter->Camera().position = Vector3(0.0f, -5.0f, 0.0f);

	lightParameter->Light().ambient = Color(0.12f, 0.12f, 0.12f);
	lightParameter->Light().diffuse = Color(1.0f, 1.0f, 1.0f);
	lightParameter->Light().direction = Vector3(1.0f, -1.0f, 0.3f).Normalized();

	transformParameter->Transform().scale = { 200.0f, 1.0f, 200.0f };
	transformParameter->Transform().position = {
		-transformParameter->Transform().scale.x / 2.0f,
		0.0f,
		-transformParameter->Transform().scale.z / 2.0f 
	};

	cubeTransformParameter->Transform().position = {0.0f, 5.0f, 0.0f};
	cubeTransformParameter->Transform().scale = {3.0f, 5.0f, 8.0f};
}

void App::Update()
{
	const float deltaTime = window->GetTime() - lastTime;
	lastTime = window->GetTime();

	// Input, camera and movement
	if (input->IsKeyJustPressed(KeyboardKey::SPACE))
		useLambertRenderingRule = not useLambertRenderingRule;
	if (input->IsMouseButtonDown(MouseButton::LEFT))
	{
		Vector2 mouseMovement = input->GetMouseMovement();
		cameraParameter->Camera().rotation.y += mouseMovement.x * 0.01f;
		cameraParameter->Camera().rotation.x += mouseMovement.y * 0.01f;
	}
	{
		Vector3& pos = cameraParameter->Camera().position;
		Vector3& rot = cameraParameter->Camera().rotation;
		Vector2 dir = {
			float(input->IsKeyDown(KeyboardKey::D) - input->IsKeyDown(KeyboardKey::A)),
			float(input->IsKeyDown(KeyboardKey::W) - input->IsKeyDown(KeyboardKey::S))
		};
		pos += Vector3(
			dir.x * -cosf(rot.y) + dir.y * -sinf(rot.y),
			float(input->IsKeyDown(KeyboardKey::Q)) - float(input->IsKeyDown(KeyboardKey::E)),
			dir.y * cosf(rot.y) + dir.x * -sinf(rot.y)
		) * deltaTime * 15.0f;
	}
	cubeTransformParameter->Transform().rotation.z += deltaTime;

	// Rule binding
	if (useLambertRenderingRule and lambertRenderingRule != nullptr)
	{
		currentRenderingRule = lambertRenderingRule;
		renderer->SetClearColor({ 0.05f, 0.1f, 0.2f });
	}
	else
	{
		currentRenderingRule = unshadedRenderingRule;
		renderer->SetClearColor({ 0.1f, 0.2f, 0.4f });
	}
	currentRenderingRule->Bind();
	
	// State updating
	cameraParameter->Camera().aspectRatio = window->GetAspectRatio();

	// State binding
	cameraParameter->Bind(currentRenderingRule);
	lightParameter->Bind(currentRenderingRule);

	// Drawing
	transformParameter->Bind(currentRenderingRule);
	terrainTexture->Bind();
	terrainMesh->Draw();
	cubeTransformParameter->Bind(currentRenderingRule);
	cubeTexture->Bind();
	cubeMesh->Draw();
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
