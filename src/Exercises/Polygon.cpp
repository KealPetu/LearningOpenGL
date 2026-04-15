//
// Created by Keal on 4/13/2026.
//

#include "WindowManager.hpp"

constexpr GLfloat BACKGROUND_COLOR[4]   { 20.4f / 255.f, 20.4f / 255.f, 25.5f / 255.f, 1.f };
constexpr unsigned int WINDOW_WIDTH	    { 800 };
constexpr unsigned int WINDOW_HEIGHT	{ 450 };

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

    while (!windowManager.windowShouldClose()) {
        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], BACKGROUND_COLOR[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        windowManager.endDrawing();
    }

	glDeleteProgram(shaderProgram);
    windowManager.destroyWindow();
    glfwTerminate();
    return 0;
}
