//
// Created by Keal on 4/13/2026.
//
#include "WindowManager.hpp"

constexpr int WINDOW_WIDTH	{ 800 };
constexpr int WINDOW_HEIGHT	{ 450 };

GLfloat backgroundColor[4] { 20.4f / 255.f, 20.4f / 255.f, 25.5f / 255.f, 1.f };

int main(){
	WindowManager windowManager;
	WindowManager::initializeGLFW(3, 3);
	windowManager.initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Triangles 3");

	//Shader Program creation

	//Vertex Shader
	static constexpr const char* vertexShaderSource { R"glsl(
		#version 330 core
		layout (location = 0) in vec2 aPos;
		layout (location = 1) in vec3 aColor;

		out vec3 ourColor;

		void main()
		{
			gl_Position = vec4(aPos, 0.0, 1.0);
			ourColor = aColor;
		}
	)glsl"};

	const GLuint vertexShader { glCreateShader(GL_VERTEX_SHADER)};

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
	static constexpr const char* fragmentShaderSource { R"glsl(
		#version 330 core
		in vec3 ourColor;
		out vec4 FragColor;
		void main()
		{
		   FragColor = vec4(ourColor, 1.0f);
		}
	)glsl" };

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

	//Vertices
	constexpr GLfloat vertices[] {
		//Triangle 1	//rgb Colors
		-0.5f,  0.5f,	0.2f, 0.6f, 0.8f,
		-0.25f, -0.5f,	0.2f, 0.6f, 0.8f,
		-0.75f, -0.5f,	0.2f, 0.6f, 0.8f,
		//Triangle 2
		0.5f,  0.5f,	0.8, 0.4, 0.2,
		0.75f, -0.5f,	0.8, 0.4, 0.2,
		0.25f, -0.5f,	0.8, 0.4, 0.2
	};

	constexpr GLuint indexes[] {
		0, 1, 2,
		3, 4, 5
	};

	//Vertex Buffer Object (VBO), Vertex Array Object (VAO)
	GLuint VBO {};
	GLuint VAO {};
	GLuint EBO {};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void *>(nullptr));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	glBindVertexArray(NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	glBindVertexArray(VAO);
	while (!windowManager.windowShouldClose()) {
		glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw the triangle
		glUseProgram(shaderProgram);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		windowManager.endDrawing();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	windowManager.destroyWindow();
	glfwTerminate();
	return 0;
}