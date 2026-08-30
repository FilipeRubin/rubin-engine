#include "ogl-renderer-parameter-manager.h"
#include "parameters/ogl-camera-3d-parameter.h"
#include "parameters/ogl-scene-lighting-parameter.h"
#include "parameters/ogl-transform-2d-parameter.h"
#include "parameters/ogl-transform-3d-parameter.h"

OGLRendererParameterManager::OGLRendererParameterManager(OGLRenderer& renderer) :
    OGLRendererUser(renderer)
{
}

ICamera3DParameter* OGLRendererParameterManager::CreateCamera3D()
{
    return CreateParameter<OGLCamera3DParameter>();
}

ISceneLightingParameter* OGLRendererParameterManager::CreateSceneLighting(const SceneLightingDescriptor& lightingDescriptor)
{
    return CreateParameter<OGLSceneLightingParameter>(lightingDescriptor);
}

ITransform2DParameter* OGLRendererParameterManager::CreateTransform2D()
{
    return CreateParameter<OGLTransform2DParameter>();
}

ITransform3DParameter* OGLRendererParameterManager::CreateTransform3D()
{
    return CreateParameter<OGLTransform3DParameter>();
}
