//
// Created by Keal on 4/26/2026.
//

#pragma once

#include "glad/glad.h"
#include "stb_image.h"

class Texture {
private:
    GLuint m_ID {};
    GLsizei m_width {};
    GLsizei m_height {};
    GLenum m_type {};

public:
    Texture(const char* texturePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    ~Texture();

    void bind(GLenum textureUnit) const;
    void unbind() const;
};
