//
// Created by Keal on 4/13/2026.
//

#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "WindowManager.hpp"

constexpr GLfloat BACKGROUND_COLOR[4]   { 20.4f / 255.f, 20.4f / 255.f, 25.5f / 255.f, 1.f };
constexpr unsigned int WINDOW_WIDTH	    { 800 };
constexpr unsigned int WINDOW_HEIGHT	{ 450 };

std::vector<GLfloat> generatePolygonVertices(const int nSides, const float size) {
	constexpr float MAX_SIZE {100};
	std::vector<GLfloat> vertices;

	const float angleIncrement { static_cast<float>(2.0f * M_PI / nSides) };
	const float normalizedSize { size / MAX_SIZE };

	//Origin vertex (0.0f, 0.0f)
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	for (int i = 0; i < nSides; ++i) {
		const float angle = i * angleIncrement;
		vertices.push_back(normalizedSize * cos(angle)); // x coordinate
		vertices.push_back(normalizedSize * sin(angle)); // y coordinate
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
    WindowManager windowManager;
    WindowManager::initializeGLFW(3, 3);
    windowManager.initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Polygon");

    //Shader Program creation

    //Vertex Shader
    static constexpr const char* vertexShaderSource { R"glsl(
		#version 330 core
		layout (location = 0) in vec2 aPos;
		void main()
		{
		   gl_Position = vec4(aPos, 0.0, 1.0);
		}
	)glsl"};

    const GLuint vertexShader { glCreateShader(GL_VERTEX_SHADER) };

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success {};
    char infoLog[512] {};

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Fragment Shader
    static constexpr const char* fragmentShaderSource{ R"(
		#version 330 core
		out vec4 FragColor;
		void main()
		{
		   FragColor = vec4(0.2f, 0.6f, 0.8f, 1.0f);
		}
	)" };

    const GLuint fragmentShader { glCreateShader(GL_FRAGMENT_SHADER) };

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Shader Program
    const GLuint shaderProgram { glCreateProgram() };

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::cout << "|========== Polygon Playground! ==========|" << std::endl;
    std::cout << "Enter the number of sides you want your polygon to have (starting from 3): ";
    int nSides {};
    std::cin >> nSides;
    std::cout << "Enter the size that you want your polygon to have (from 0 to 100): ";
    float size {};
    std::cin >> size;

	// Vertices & indices
	std::vector vertices {generatePolygonVertices(nSides, size)};
	std::vector indices {generatePolygonIndices(nSides)};

	//VBO, VAO & EBO
	const VBO vbo {vertices.data(), static_cast<GLsizeiptr>(sizeof(GLfloat) * vertices.size())};
	const EBO ebo {indices.data(), static_cast<GLsizeiptr>(sizeof(GLuint) * indices.size())};
	VAO vao {};

	vao.bind();
	ebo.bind();
	vao.linkAttrib(vbo, 0, 2, GL_FLOAT, 2 * sizeof(GLfloat), nullptr);
	VAO::unbind();
	EBO::unbind();

    // Wireframe mode -----
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// --------------------
	while (!windowManager.windowShouldClose()) {
        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], BACKGROUND_COLOR[3]);
        glClear(GL_COLOR_BUFFER_BIT);

    	glUseProgram(shaderProgram);
    	vao.bind();
    	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
        windowManager.endDrawing();
    }

	glDeleteProgram(shaderProgram);
    windowManager.destroyWindow();
    glfwTerminate();
    return 0;
}
