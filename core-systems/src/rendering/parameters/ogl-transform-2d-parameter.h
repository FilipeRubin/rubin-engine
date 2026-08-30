#pragma once
#include <rendering/parameters/i-transform-2d-parameter.h>
#include <rendering/ogl-renderer-user.h>

class OGLTransform2DParameter final : public ITransform2DParameter, public OGLRendererUser
{
public:
	OGLTransform2DParameter(OGLRenderer& renderer);
	void Bind() override;
	Transform2D& Transform() override;
private:
	Transform2D m_transform;
};