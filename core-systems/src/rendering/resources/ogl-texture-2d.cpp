#include "ogl-texture-2d.h"
#include <ogl.h>
#include <logging/log-macros.h>

OGLTexture2D::OGLTexture2D(OGLRenderer& renderer, Shared<FixedArray<Color8>> data, const Dimensions& dimensions) :
    OGLRendererUser(renderer),
    m_data(data),
    m_dimensions(dimensions),
    m_texture(0U)
{
}

void OGLTexture2D::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

const Dimensions& OGLTexture2D::GetDimensions() const
{
    return m_dimensions;
}

bool OGLTexture2D::IsValid() const
{
    return m_texture != 0U;
}

void OGLTexture2D::Create()
{
	LOG_DEBUG("Creating OpenGL texture with size " + std::to_string(m_dimensions.width) + "x" + std::to_string(m_dimensions.height) + ".");
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_dimensions.width, m_dimensions.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data->GetData());
    glGenerateMipmap(GL_TEXTURE_2D);
    m_data.Reset();
}

void OGLTexture2D::Destroy()
{
	LOG_DEBUG("Destroying OpenGL texture.");
    glDeleteTextures(1, &m_texture);
}
