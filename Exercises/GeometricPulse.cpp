#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
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

std::vector<GLfloat> generatePolygonVertices(const int nSides) {
	std::vector<GLfloat> vertices;

	const float angleIncrement { static_cast<float>(2.0f * M_PI / nSides) };

	//Origin vertex (0.0f, 0.0f)
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	for (int i = 0; i < nSides; ++i) {
		const float angle = i * angleIncrement;
		vertices.push_back(cos(angle)); // x coordinate
		vertices.push_back(sin(angle)); // y coordinate
	}

	return vertices;
}

std::vector<GLuint> generatePolygonIndices(const int nSides) {
	std::vector<GLuint> indices;

	for (int i = 1; i <= nSides; ++i) {
		indices.push_back(0);
		indices.push_back(i);

		if (i == nSides) {
			indices.push_back(1);
		} else {
			indices.push_back(i + 1);
		}
	}

	return indices;
}

int main() {
    // 1. SYSTEM INITIALIZATION
    WindowManager windowManager;
    WindowManager::initializeGLFW(3, 3);
    windowManager.initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mi Motor Grafico");

    // 2. SHADERS COMPILATION
    Shader shaderProgram("resources/shaders/pulse.vert", "resources/shaders/pulse.frag");

    // 3. GEOMETRY DEFINITION
    int nSides {};
    std::cout << "Enter the number of sides for the polygon: ";
    std::cin >> nSides;
    std::vector<GLfloat>vertices    { generatePolygonVertices(nSides) };
    std::vector<GLuint> indices     { generatePolygonIndices(nSides) };

    // 4. BUFFERS CONFIGURATION
    const VBO vbo(vertices.data(), static_cast<GLsizeiptr>(sizeof(GLfloat) * vertices.size()));
    const EBO ebo(indices.data(), static_cast<GLsizeiptr>(sizeof(GLuint) * indices.size()));
    VAO vao;

    vao.bind();
    ebo.bind();
    
    // Atribute 0: Position (2 floats)
    vao.linkAttrib(vbo, 0, 2, GL_FLOAT, 2 * sizeof(GLfloat), nullptr);
    
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
        shaderProgram.setFloat("time", timeValue);

        vao.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
        VAO::unbind(); // Optional, but safe

        // C. Buffer swap
        windowManager.endDrawing();
    }

    // 6. Clean
    // NOTE: vao, vbo, ebo & shaderProgram clean by themselves (RAII).
    windowManager.destroyWindow();
    glfwTerminate();
    
    return 0;
}