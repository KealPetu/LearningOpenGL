//
// Created by Keal on 4/13/2026.
//
//Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data.
#include "WindowManager.hpp"

constexpr GLfloat BACKGROUND_COLOR[4]   { 20.4f / 255.f, 20.4f / 255.f, 25.5f / 255.f, 1.f };
constexpr unsigned int WINDOW_WIDTH	    { 800 };
constexpr unsigned int WINDOW_HEIGHT	{ 450 };

int main() {
    WindowManager windowManager;
    WindowManager::initializeGLFW(3, 3);
    windowManager.initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Window");

    //Vertex Shader
	static constexpr const char* vertexShaderSource { R"glsl(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		void main()
		{
		   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)glsl"};

    const GLuint vertexShader { glCreateShader(GL_VERTEX_SHADER) };

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

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
    const GLuint shaderProgram = glCreateProgram();

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

    //Vertices
    constexpr GLfloat vertices[] = {
	    //Triangle 1
    	-0.5f,  0.5f,
		-0.25f, -0.5f,
    	-0.75f, -0.5f,
    	//Triangle 2
    	0.5f,  0.5f,
    	0.75f, -0.5f,
    	0.25f, -0.5f
	};

	//VBO & VAO
	GLuint VAO;
	GLuint VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);

    while (!windowManager.windowShouldClose()) {
        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], BACKGROUND_COLOR[3]);
        glClear(GL_COLOR_BUFFER_BIT);

    	glUseProgram(shaderProgram);
    	glBindVertexArray(VAO);
    	glDrawArrays(GL_TRIANGLES, 0, 6);

        windowManager.endDrawing();
    }

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

    windowManager.destroyWindow();
    glfwTerminate();
    return 0;
}