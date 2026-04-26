//
// Created by Keal on 4/13/2026.
//

#include "VBO.hpp"

VBO::VBO(const GLfloat *vertices, const GLsizeiptr size) {
    glGenBuffers(1, &m_ID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO() {
    glDeleteBuffers(1, &m_ID);
}

void VBO::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
