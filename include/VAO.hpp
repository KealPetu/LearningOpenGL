//
// Created by Keal on 4/13/2026.
//
#pragma once

#include "VBO.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class VAO {
private:
    GLuint ID;
public:
    VAO();
    ~VAO();

    void bind() const;
    static void unbind();

    void linkAttrib(const VBO& VBO, GLuint layout, GLint numComponents, GLenum type, GLsizeiptr stride, const void* offset);
};
