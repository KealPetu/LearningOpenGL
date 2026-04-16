//
// Created by Keal on 4/16/2026.
//
//Adjust the vertex shader so that the triangle is upside down
#include <vector>
#include <iostream>

#include "WindowManager.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

constexpr unsigned int WINDOW_WIDTH  { 800 };
constexpr unsigned int WINDOW_HEIGHT { 600 };
constexpr GLfloat BACKGROUND_COLOR[4] { 0.1f, 0.1f, 0.15f, 1.0f }; // Elegant dark gray

int main() {
    WindowManager windowManager;
    WindowManager::initializeGLFW(3, 3);
    windowManager.initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mi Motor Grafico");

    const Shader shaderProgram("./resources/shaders/vShader1.vert", "./resources/shaders/fShader1.frag");

    const std::vector vertices {
         0.0f,  0.5f,    1.0f, 0.0f, 0.0f, // Up Right (Red)
         0.5f, -0.5f,    0.0f, 1.0f, 0.0f, // Down Right (Green)
        -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, // Down Left (Blue)
    };

    const std::vector<GLuint> indices {
        0, 1, 2
    };

    // 4. BUFFERS CONFIGURATION
    const VBO vbo(vertices.data(), static_cast<GLsizeiptr>(sizeof(GLfloat) * vertices.size()));
    const EBO ebo(indices.data(), static_cast<GLsizeiptr>(sizeof(GLuint) * indices.size()));
    VAO vao;

    vao.bind();
    ebo.bind();

    // Atribute 0: Position (2 floats)
    vao.linkAttrib(vbo, 0, 2, GL_FLOAT, 5 * sizeof(GLfloat), nullptr);
    // Atribute 1: Color (3 floats)
    vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 5 * sizeof(GLfloat), reinterpret_cast<void*>(2 * sizeof(GLfloat)));

    VAO::unbind();
    EBO::unbind();

    while (!windowManager.windowShouldClose()) {
        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], BACKGROUND_COLOR[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();

        vao.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
        VAO::unbind();

        windowManager.endDrawing();
    }

    windowManager.destroyWindow();
    glfwTerminate();

    return 0;
}