#pragma once
#include <rendering/parameters/i-transform-3d-parameter.h>
#include <rendering/ogl-renderer-user.h>

class OGLTransform3DParameter final : public ITransform3DParameter, public OGLRendererUser
{
public:
	OGLTransform3DParameter(OGLRenderer& renderer);
	~OGLTransform3DParameter();
	void Bind() override;
	Transform3D& Transform() override;
protected:
	IRenderParameterImplementation* GetImplementation() override;
private:
	Transform3D m_transform;
	IRenderParameterImplementation* m_impl;
};
