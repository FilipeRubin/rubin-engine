#pragma once
#include <rendering/parameters/i-scene-lighting-parameter.h>
#include <rendering/ogl-renderer-user.h>
#include <containers/fixed-array.h>

class OGLSceneLightingParameter : public ISceneLightingParameter, public OGLRendererUser
{
public:
	OGLSceneLightingParameter(OGLRenderer& renderer, const SceneLightingDescriptor& lightingDescriptor);
	void Bind() override;
	Color& AmbientLight() override;
	FixedArray<DirectionalLight>& DirectionalLights() override;
private:
	Color m_ambientLight;
	FixedArray<DirectionalLight> m_directionallights;
};
