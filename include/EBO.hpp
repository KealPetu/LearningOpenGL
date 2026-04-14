//
// Created by Keal on 4/13/2026.
//
#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class EBO {
private:
    GLuint ID;
public:
    EBO(const GLuint* indices, GLsizeiptr size);
    ~EBO();

    void bind() const;
    static void unbind();
};