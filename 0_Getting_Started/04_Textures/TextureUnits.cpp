//
// Created by Keal on 4/25/2026.
//

//
// Created by Keal on 4/25/2026.
//
#include <vector>
#include <iostream>

#include "WindowManager.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "stb_image.h"


// --- GLOBAL CONFIGURATION ---
constexpr unsigned int WINDOW_WIDTH  { 600 };
constexpr unsigned int WINDOW_HEIGHT { 600 };
constexpr GLfloat BACKGROUND_COLOR[4] { 0.1f, 0.1f, 0.15f, 1.0f }; // Elegant dark gray

int main() {
    // 1. SYSTEM INITIALIZATION
    WindowManager windowManager;
    WindowManager::initializeGLFW(3, 3);
    windowManager.initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Textures");

    // 2. SHADERS COMPILATION
    const Shader shaderProgram("./resources/shaders/TextureUnits/shader.vert", "./resources/shaders/TextureUnits/shader.frag");

    GLuint containerTexture {};
    glGenTextures(1, &containerTexture);
    glBindTexture(GL_TEXTURE_2D, containerTexture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    GLsizei textWidth {};
    GLsizei textHeight {};
    int nChannels {};

    stbi_set_flip_vertically_on_load(true); // Flip texture vertically to match OpenGL's coordinate system
    GLubyte* containerTextData{
        stbi_load("./resources/textures/container.jpg", &textWidth, &textHeight,&nChannels,
            STBI_default)
    };

    if (containerTextData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textWidth, textHeight, 0, GL_RGB,
            GL_UNSIGNED_BYTE, containerTextData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(containerTextData);

    // HAPPY FACE TEXTURE
    GLuint happyFaceTexture {};
    glGenTextures(1, &happyFaceTexture);
    glBindTexture(GL_TEXTURE_2D, happyFaceTexture);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    GLubyte* happyFaceTextData{
        stbi_load("./resources/textures/awesomeface.png", &textWidth, &textHeight,&nChannels,
            STBI_default)
    };

    if (happyFaceTextData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textWidth, textHeight, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, happyFaceTextData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(happyFaceTextData);

    // 3. GEOMETRY DEFINITION
    // X, Y Coordinates  |  R, G, B Colors      |  U, V Texture Coords
    std::vector<GLfloat> vertices {
        // positions // texture coords
        0.5f,  0.5f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f, 1.0f    // top left
   };

    std::vector<GLuint> indices {
        0, 1, 2,
        0, 2, 3
    };

    // 4. BUFFERS CONFIGURATION
    const VBO vbo(vertices.data(), static_cast<GLsizeiptr>(sizeof(GLfloat) * vertices.size()));
    const EBO ebo(indices.data(), static_cast<GLsizeiptr>(sizeof(GLuint) * indices.size()));
    VAO vao;

    vao.bind();
    ebo.bind();

    // Atribute 0: Position (2 floats)
    vao.linkAttrib(vbo, 0, 2, GL_FLOAT, 4 * sizeof(GLfloat), nullptr);
    // Atribute 1: Texture (2 floats)
    vao.linkAttrib(vbo, 1, 2, GL_FLOAT, 4 * sizeof(GLfloat), reinterpret_cast<void*>(2 * sizeof(GLfloat)));

    VAO::unbind();
    EBO::unbind();

    shaderProgram.use();
    shaderProgram.setInt("texture1", 0); // Texture unit 0
    shaderProgram.setInt("texture2", 1); // Texture unit 1
    // 5. CORE LOOP (Game Loop)
    while (!windowManager.windowShouldClose()) {
        // A. Logic / State Updates (Inputs, Physics, etc.)
        const auto timeValue = static_cast<float>(glfwGetTime());

        // B. Rendering
        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], BACKGROUND_COLOR[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        // Uniforms
        shaderProgram.setFloat("timeValue", timeValue);

        // NEW: ACTIVATE TEXTURE UNIT BEFORE BINDING TEXTURE
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, happyFaceTexture);
        vao.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
        VAO::unbind(); // Optional, but safe

        // C. Buffer swap
        windowManager.endDrawing();
    }

    // 6. Clean
    // NOTE: windowManager, vao, vbo, ebo & shaderProgram clean by themselves (RAII).
    glfwTerminate();
    return 0;
}