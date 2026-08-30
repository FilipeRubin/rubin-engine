#include "ogl-renderer-resource-manager.h"
#include "ogl-renderer.h"
#include "resources/ogl-rendering-rule.h"
#include "resources/ogl-mesh-2d.h"
#include "resources/ogl-mesh-3d.h"
#include "resources/ogl-texture-2d.h"
#include <containers/source-container.h>
#include <logging/log-macros.h>

#ifdef ERROR
#undef ERROR
#endif

using std::unique_ptr;
using std::list;

OGLRendererResourceManager::OGLRendererResourceManager(OGLGraphicsBackend* backend, OGLRenderer& renderer) :
    OGLRendererUser(renderer),
    m_backend(backend),
    m_waitingToCreate(list<unique_ptr<IRendererManaged>>()),
    m_waitingToDestroy(list<unique_ptr<IRendererManaged>>()),
    m_resources(list<unique_ptr<IRendererManaged>>())
{
	LOG_INFO("OpenGL renderer resource manager created.");
}

OGLRendererResourceManager::~OGLRendererResourceManager()
{
	LOG_INFO("Destroying OpenGL renderer resources.");
    OGLGraphicsBackend* currentBackend = OGLGraphicsBackend::GetCurrent();
    
    if (currentBackend != m_backend)
        m_backend->MakeCurrent();

    for (unique_ptr<IRendererManaged>& managed : m_waitingToDestroy)
        managed->Destroy();
    m_waitingToDestroy.clear();

    for (unique_ptr<IRendererManaged>& managed : m_waitingToCreate)
        managed->Destroy();
    m_waitingToCreate.clear();

    for (unique_ptr<IRendererManaged>& managed : m_resources)
        managed->Destroy();
    m_resources.clear();

    if (currentBackend != m_backend)
        currentBackend->MakeCurrent();
}

IRenderingRule* OGLRendererResourceManager::CreateRenderingRule(const IRenderingRuleGenerator& generator)
{
    return CreateResource<OGLRenderingRule>(generator.GenerateDescriptor());
}

IMesh2D* OGLRendererResourceManager::CreateMesh2D(const IMesh2DGenerator& generator)
{
    const MeshData2D& data = generator.GenerateMeshData();
    LOG_DEBUG("Queuing 2D mesh creation with " + std::to_string(data.GetVertices()->GetElementCount()) + " vertices and " + std::to_string(data.GetIndices()->GetElementCount()) + " indices.");
    return CreateResource<OGLMesh2D>(
        data.GetVertices(),
        data.GetIndices()
    );
}

IMesh3D* OGLRendererResourceManager::CreateMesh3D(const IMesh3DGenerator& generator)
{
    const MeshData3D& data = generator.GenerateMeshData();
	LOG_DEBUG("Queuing 3D mesh creation with " + std::to_string(data.GetVertices()->GetElementCount()) + " vertices and " + std::to_string(data.GetIndices()->GetElementCount()) + " indices.");
    return CreateResource<OGLMesh3D>(
        data.GetVertices(),
        data.GetIndices()
    );
}

ITexture2D* OGLRendererResourceManager::CreateTexture2D(const ITexture2DGenerator& generator)
{
    const TextureData& data = generator.GenerateTextureData();
	LOG_DEBUG("Queuing 2D texture creation with size " + std::to_string(data.GetDimensions().width) + "x" + std::to_string(data.GetDimensions().height) + ".");
    return CreateResource<OGLTexture2D>(
        data.GetData(),
        data.GetDimensions()
    );
}

void OGLRendererResourceManager::Update()
{
	if (not m_waitingToCreate.empty() or not m_waitingToDestroy.empty())
		LOG_DEBUG("Applying queued OpenGL resource changes: " + std::to_string(m_waitingToCreate.size()) + " creation(s), " + std::to_string(m_waitingToDestroy.size()) + " destruction(s).");

    for (unique_ptr<IRendererManaged>& managed : m_waitingToCreate)
    {
        managed->Create();
        m_resources.push_back(std::move(managed));
    }

    for (unique_ptr<IRendererManaged>& managed : m_waitingToDestroy)
    {
        managed->Destroy();
    }

    m_waitingToCreate.clear();
    m_waitingToDestroy.clear();
}

void OGLRendererResourceManager::DestroyImpl(IRendererResource* resource)
{
    list<unique_ptr<IRendererManaged>>::iterator managedIt = std::find_if(m_resources.begin(), m_resources.end(),
        [&resource](unique_ptr<IRendererManaged>& managed)
        {
            return dynamic_cast<IRendererManaged*>(resource) == managed.get();
        });

    if (managedIt != m_resources.end())
    {
        unique_ptr<IRendererManaged> managed = std::move(*managedIt);
        m_resources.erase(managedIt);

        bool isCurrentBackend = OGLGraphicsBackend::GetCurrent() == m_backend;
        if (isCurrentBackend)
        {
            managed->Destroy();
        }
        else
        {
            m_waitingToDestroy.emplace_back(std::move(managed));
        }

        resource = nullptr;
    }
	else
	{
		LOG_WARNING("Attempted to destroy a renderer resource that is not managed by this resource manager.");
	}
}
