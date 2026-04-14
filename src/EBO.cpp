//
// Created by Keal on 4/13/2026.
//
#include "EBO.hpp"

EBO::EBO(const GLuint *indices, const GLsizeiptr size) {
    glGenBuffers(1, &ID);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

EBO::~EBO() {
    glDeleteBuffers(1, &ID);
}

void EBO::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}