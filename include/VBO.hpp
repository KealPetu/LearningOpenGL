//
// Created by Keal on 4/13/2026.
//
#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class VBO {
private:
    GLuint ID {};
public:
    VBO(const GLfloat* vertices, GLsizeiptr size);
    ~VBO();

    void bind() const;
    static void unbind();
};