//
// Created by Keal on 4/26/2026.
//

#include "Texture.hpp"
#include <iostream>

Texture::Texture(const char* texturePath, const GLenum texType, const GLenum unit) {
    m_type = texType;
    glGenTextures(1, &m_ID);

    bind(unit);

    setWrappingMode(GL_REPEAT);
    setFilteringMode(GL_LINEAR);

    stbi_set_flip_vertically_on_load(true); // Flip texture vertically to match OpenGL's coordinate system
    int numChannels;
    GLubyte* data { stbi_load(texturePath, &m_width, &m_height, &numChannels,
        STBI_default)};

    GLint format {};
    switch (numChannels) {
        case 1:
            format = GL_RED; break;
        case 2:
            format = GL_RG; break;
        case 3:
            format = GL_RGB; break;
        case 4:
            format = GL_RGBA; break;
        default:
            std::cerr << "Unsupported number of channels: " << numChannels << std::endl;
            stbi_image_free(data);
    }

    if (data) {
        glTexImage2D(m_type, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE,
            data);
        glGenerateMipmap(m_type);
    } else {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_ID);
}

void Texture::bind(const GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(m_type, m_ID);
}

void Texture::unbind() const {
    glBindTexture(m_type, 0);
}

void Texture::setWrappingMode(const GLint wrapMode) const {
    glBindTexture(m_type, m_ID);
    glTexParameteri(m_type, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(m_type, GL_TEXTURE_WRAP_T, wrapMode);
}

void Texture::setFilteringMode(const GLint filterMode) const {
    glBindTexture(m_type, m_ID);
    glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, filterMode);
}
