#include <vector>
#include <iostream>

#include "WindowManager.hpp"
#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

// --- GLOBAL CONFIGURATION ---
constexpr unsigned int WINDOW_WIDTH  { 800 };
constexpr unsigned int WINDOW_HEIGHT { 600 };
constexpr GLfloat BACKGROUND_COLOR[4] { 0.1f, 0.1f, 0.15f, 1.0f }; // Elegant dark gray

int main() {
    // 1. SYSTEM INITIALIZATION
    WindowManager windowManager;
    WindowManager::initializeGLFW(3, 3);
    windowManager.initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mi Motor Grafico");

    // 2. SHADERS COMPILATION
    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

    // 3. GEOMETRY DEFINITION
    // X, Y Coordinates  |  R, G, B Colors
    std::vector<GLfloat> vertices {
         0.5f,  0.5f,    1.0f, 0.0f, 0.0f, // Up Right (Red)
         0.5f, -0.5f,    0.0f, 1.0f, 0.0f, // Down Right (Green)
        -0.5f, -0.5f,    0.0f, 0.0f, 1.0f, // Down Left (Blue)
        -0.5f,  0.5f,    1.0f, 1.0f, 0.0f  // Up Left (Yellow)
    };

    std::vector<GLuint> indices {
        0, 1, 3,
        1, 2, 3
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

    // 5. CORE LOOP (Game Loop)
    while (!windowManager.windowShouldClose()) {
        // A. Logic / State Updates (Inputs, Physics, etc.)
        float timeValue = static_cast<float>(glfwGetTime());

        // B. Rendering
        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], BACKGROUND_COLOR[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        
        // (Optional) Uniforms
        // shaderProgram.setFloat("time", timeValue);

        vao.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
        VAO::unbind(); // Opcional, pero seguro

        // C. Buffer swap
        windowManager.endDrawing();
    }

    // 6. Clean
    // NOTA: vao, vbo, ebo & shaderProgram clean by themselves (RAII).
    windowManager.destroyWindow();
    glfwTerminate();
    
    return 0;
}