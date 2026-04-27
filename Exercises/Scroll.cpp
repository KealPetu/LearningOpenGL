//
// Created by Keal on 4/26/2026.
//

#include <vector>

#include "WindowManager.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT { 600 };

const float BACKGROUND_COLOR[4] {0.2f, 0.3f, 0.3f, 1.0f};

int main() {
    WindowManager::initializeGLFW(3, 3);
    WindowManager wm;
    wm.initializeWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Scroll Exercise");

    const std::vector<GLfloat> vertices {
        0.5f,  0.5f,    1.0f, 1.0f, // Upper right corner
        0.5f, -0.5f,    1.0f, 0.0f, // Lower right corner
       -0.5f, -0.5f,    0.0f, 0.0f, // Lower left corner
       -0.5f,  0.5f,    0.0f, 1.0f, // Upper left corner
   };

    const std::vector<GLuint> indices {
        0, 1, 3,
        1, 2, 3
    };

    const VBO vbo((vertices.data()), static_cast<GLsizeiptr>(sizeof(GLfloat) * vertices.size()));
    const EBO ebo((indices.data()), static_cast<GLsizeiptr>(sizeof(GLuint) * indices.size()));
    VAO vao;

    vao.bind();
    ebo.bind();

    // Atribute 0: Position (2 floats)
    vao.linkAttrib(vbo, 0, 2, GL_FLOAT, 4 * sizeof(GLfloat), nullptr);
    // Atribute 1: Texture (2 floats)
    vao.linkAttrib(vbo, 1, 2, GL_FLOAT, 4 * sizeof(GLfloat),
        reinterpret_cast<void*>(2 * sizeof(GLfloat)));

    VAO::unbind();
    EBO::unbind();

    Texture containerTexture("./resources/textures/container.jpg", GL_TEXTURE_2D, GL_TEXTURE0);

    const Shader shader("./resources/shaders/ScrollShader.vert","./resources/shaders/ScrollShader.frag");
    shader.use();

    while (!wm.windowShouldClose()) {
        const float timeValue { static_cast<float>(glfwGetTime()) };

        shader.setFloat("timeValue", timeValue);

        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2],
            BACKGROUND_COLOR[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        vao.unbind();

        wm.endDrawing();
    }
    glfwTerminate();
    return 0;
}