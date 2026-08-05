#pragma once
#include <rendering/parameters/i-directional-light-parameter.h>
#include <rendering/ogl-renderer-user.h>

class OGLDirectionalLightParameter : public IDirectionalLightParameter, public OGLRendererUser
{
public:
	OGLDirectionalLightParameter(OGLRenderer& renderer);
	void Bind() override;
	DirectionalLight& Light() override;
private:
	DirectionalLight m_light;
};
