#pragma once
#include <containers/fixed-array.h>
#include <utils/shared.h>
#include <types/dimensions.h>
#include <types/color8.h>
#include <rendering/resources/i-texture-2d.h>
#include <rendering/i-renderer-managed.h>
#include <rendering/ogl-renderer-user.h>

class OGLTexture2D : public ITexture2D, public IRendererManaged, public OGLRendererUser
{
public:
	OGLTexture2D(OGLRenderer& renderer, const Shared<FixedArray<Color8>> pixels, const Dimensions& dimensions);
	void Bind() override;
	const Dimensions& GetDimensions() const override;
	bool IsValid() const override;
	void Destroy() override;
	void CreateResource() override;
	void DestroyResource() override;
private:
	const Shared<FixedArray<Color8>> m_pixels;
	const Dimensions& m_dimensions;
	unsigned int m_texture;
};
