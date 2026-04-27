//
// Created by Keal on 4/27/2026.
//

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "WindowManager.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

constexpr int SCREEN_WIDTH { 800 };
constexpr int SCREEN_HEIGHT { 600 };

constexpr float BACKGROUND_COLOR[4] { 20.4f / 255.f, 20.4f / 255.f, 25.5f / 255.f, 1.f };

int main() {
    WindowManager::initializeGLFW(3, 3);
    WindowManager wm;
    wm.initializeWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Transformations");

    const std::vector<GLfloat> VERTICES {
        0.5f,  0.5f, 1.0, 0.0, 0.0, 2.0f, 2.0f, // Upper right corner Red
        0.5f, -0.5f, 0.0, 1.0, 0.0, 2.0f, 0.0f, // Lower right corner Green
       -0.5f, -0.5f, 0.0, 0.0, 1.0, 0.0f, 0.0f, // Lower left corner Blue
       -0.5f,  0.5f, 1.0, 1.0, 1.0, 0.0f, 2.0f, // Upper left corner White
   };

    constexpr int STRIDE { 7 * sizeof(GLfloat) };

    const std::vector<GLuint> INDICES {
        0, 1, 3,
        1, 2, 3
    };

    const VBO VBO((VERTICES.data()), static_cast<GLsizeiptr>(sizeof(GLfloat) * VERTICES.size()));
    const EBO EBO((INDICES.data()), static_cast<GLsizeiptr>(sizeof(GLuint) * INDICES.size()));
    VAO VAO;
    VAO.bind();
    EBO.bind();

    // Atribute 0: Position (2 floats)
    VAO.linkAttrib(VBO, 0, 2, GL_FLOAT, STRIDE, nullptr);
    // Atribute 1: Color (3 floats)
    VAO.linkAttrib(VBO, 1, 3, GL_FLOAT, STRIDE, reinterpret_cast<void*>(2 * sizeof(GLfloat)));
    // Atribute 2: Texture (3 floats)
    VAO.linkAttrib(VBO, 2, 2, GL_FLOAT, STRIDE, reinterpret_cast<void*>(5 * sizeof(GLfloat)));

    VAO::unbind();
    EBO::unbind();

    const Texture happyFace("./resources/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE0);
    happyFace.setWrappingMode(GL_MIRRORED_REPEAT);
    happyFace.setFilteringMode(GL_NEAREST);

    const Shader SHADER("./resources/TransformationsShader.vert","./resources/TransformationsShader.frag");
    SHADER.use();

    while (!wm.windowShouldClose()) {
        glm::mat4 trans {glm::mat4(1.0f)};
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 1.0, 1.0));

        SHADER.setMat4("transform", trans);

        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2],
            BACKGROUND_COLOR[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        VAO.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        VAO.unbind();

        wm.endDrawing();
    }
    glfwTerminate();
    return 0;
}