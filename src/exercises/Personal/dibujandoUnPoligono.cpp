#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

const int SCR_WIDTH = 840, SCR_HEIGHT = 840;

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
    "}\0";

const char *orangeFragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void createMyShaderProgram(unsigned int* shaderProgram);

void checkShaderCompilationErrors(unsigned int* shader, int type);

void checkShaderProgramLinkingErrors(unsigned int* shaderProgram);

float genVertices(float radio, int lados);

int main(int argc, char *argv[]){
    float radio;
    int lados;
    std::cout<<"Ingresa la cantidad de lados: ";
    std::cin >> lados;
    std::cout<<"Ingresa el radio (valor entre 0-1 en decimales): ";
    std::cin >> radio;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL){

        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); 

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){

        std::cout << "Failed to initialize GLAD" << std::endl;

        return -1;
    }  

    glViewport(0, 0, 840, 840);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    unsigned int VBO, VAO, EBO;


    const int numeroDeVertices = 2 * (lados + 1);
    const int numeroDeIndices = 3 * lados;

    float vertices[numeroDeVertices];

    vertices[0] = 0.0f; vertices[1] = 0.0f;//centro

    for (int i = 0; i < lados; i++)
    {
        float angle = (i * 360.0f/lados) * (float)M_PI / 180; //angulo en radianes entre cada vertice desde el centro
        vertices[(i * 2) + 2] = radio * cos(angle);
        vertices[(i * 2) + 3] = radio * sin(angle);
    }

    unsigned int indices[numeroDeIndices];

    int aux = 0;
    for (int i = 0; i < lados; i++)
    {
        indices[i + aux] = 0;
        aux++;
        indices[i + aux] = i + 1;
        aux++;
        if (i == lados - 1)
        {
            indices[i + aux] = 1;
        }
        else
        {
            indices[i + aux] = i + 2;
        }
    }

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    unsigned int shaderProgram;
    createMyShaderProgram(&shaderProgram);
    glUseProgram(shaderProgram);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glBindVertexArray(VAO);

    // Ciclo de renderizado
    while(!glfwWindowShouldClose(window)){

        // Entrada de Usuario
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);

        //verifica y llama los eventos e intercambia los buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);
}

void createMyShaderProgram(unsigned int *shaderProgram){

    unsigned int vertexShader, fragmentShader;
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilationErrors(&vertexShader, 0);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &orangeFragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilationErrors(&fragmentShader, 1);

    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);
    checkShaderProgramLinkingErrors(shaderProgram);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void checkShaderCompilationErrors(unsigned int* shader, int type){
    int success;
    char infoLog[512];

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(*shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::";
            switch (type)
            {
            case 0:
                std::cout<<"VERTEX";
                break;
            case 1:
                std::cout<<"FRAGMENT";
                break;
            }
            std::cout<<"::COMPILATION_FAILED\n" << infoLog << std::endl;

        }
};

void checkShaderProgramLinkingErrors(unsigned int* shaderProgram){
    int success;
    char infoLog[512];
    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}