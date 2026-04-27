//
// Created by Keal on 4/13/2026.
//

#include "VAO.hpp"

VAO::VAO() {
    glGenVertexArrays(1, &m_ID);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &m_ID);
}

void VAO::bind() const {
    glBindVertexArray(m_ID);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::linkAttrib(const VBO &VBO, const GLuint layout, const GLint numComponents, const GLenum type,
    const GLsizei stride, const void *offset) {
    VBO.bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.unbind();
}
