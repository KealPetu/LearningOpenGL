//
// Created by Keal on 4/26/2026.
//

#include "Texture.hpp"
#include <iostream>

Texture::Texture(const char* texturePath, const GLenum texType, const GLenum slot, const GLenum format, const GLenum pixelType) {
    m_type = texType;
    glGenTextures(1, &m_ID);
    glActiveTexture(slot);
    glBindTexture(m_type, m_ID);

    // set the texture wrapping parameters
    glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true); // Flip texture vertically to match OpenGL's coordinate system
    int numChannels;
    GLbyte* m_textureData { stbi_load(texturePath, &m_width, &m_height,&numChannels,
        STBI_default)};

    if (m_textureData) {
        glTexImage2D(m_type, 0, format, m_width, m_height, 0, format,
            pixelType, m_textureData);
        glGenerateMipmap(m_type);
    } else {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }
    stbi_image_free(m_textureData);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_ID);
    std::cout << "Texture destroyed, ID: " << m_ID << std::endl;
}

void Texture::bind(const GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(m_type, m_ID);
}

void Texture::unbind() const {
    glBindTexture(m_type, 0);
}
