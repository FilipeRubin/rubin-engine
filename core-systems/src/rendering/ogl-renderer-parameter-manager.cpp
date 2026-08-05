#include "ogl-renderer-parameter-manager.h"
#include "parameters/ogl-camera-3d-parameter.h"
#include "parameters/ogl-directional-light-parameter.h"
#include "parameters/ogl-transform-3d-parameter.h"

OGLRendererParameterManager::OGLRendererParameterManager(OGLRenderer& renderer) :
    OGLRendererUser(renderer)
{
}

ICamera3DParameter* OGLRendererParameterManager::CreateCamera3D()
{
    return CreateParameter<OGLCamera3DParameter>();
}

IDirectionalLightParameter* OGLRendererParameterManager::CreateDirectionalLight()
{
    return CreateParameter<OGLDirectionalLightParameter>();
}

ITransform3DParameter* OGLRendererParameterManager::CreateTransform3D()
{
    return CreateParameter<OGLTransform3DParameter>();
}
