#pragma once
#include <rendering/parameters/i-scene-lighting-parameter.h>
#include <rendering/ogl-renderer-user.h>
#include <types/scene-lighting-descriptor.h>
#include <containers/fixed-array.h>

class OGLSceneLightingParameter : public ISceneLightingParameter, public OGLRendererUser
{
public:
	OGLSceneLightingParameter(OGLRenderer& renderer, const SceneLightingDescriptor& lightingDescriptor);
	~OGLSceneLightingParameter();
	void Bind() override;
	Color& AmbientLight() override;
	FixedArray<DirectionalLight>& DirectionalLights() override;
protected:
	IRenderParameterImplementation* GetImplementation() override;
private:
	Color m_ambientLight;
	FixedArray<DirectionalLight> m_directionallights;
	IRenderParameterImplementation* m_impl;
};
