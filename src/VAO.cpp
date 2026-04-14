//
// Created by Keal on 4/13/2026.
//

#include "VAO.hpp"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &ID);
}

void VAO::bind() const {
    glBindVertexArray(ID);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::linkAttrib(const VBO &VBO, const GLuint layout, const GLint numComponents, const GLenum type, const GLsizeiptr stride, const void *offset) {
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}
