#pragma once
#include <rendering/parameters/i-transform-3d-parameter.h>
#include <rendering/ogl-renderer-user.h>

class OGLTransform3DParameter : public ITransform3DParameter, public OGLRendererUser
{
public:
	OGLTransform3DParameter(OGLRenderer& renderer);
	void Bind() override;
	Transform3D& Transform() override;
private:
	Transform3D m_transform;
};
