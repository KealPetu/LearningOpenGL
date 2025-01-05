#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//Poodemos enviar valores de un shader a otro con las palabras clave in y out.
const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
    "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
    "}\0";
//En este casoo, del vertex shader recibimos un vec4 que contiene los valores de color que vamos a utilizar en el fragment shader.
const char *orangeFragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 vertexColor;"
    "void main()\n"
    "{\n"
    "   FragColor = vertexColor;\n"
    "}";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void createMyShaderProgram(unsigned int* shaderProgram);

void checkShaderCompilationErrors(unsigned int* shader, int type);

void checkShaderProgramLinkingErrors(unsigned int* shaderProgram);

int main(int argc, char *argv[]){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

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

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    unsigned int VBO, VAO, EBO;

    float vertices[] = {
         0.5f,  0.5f,
         0.5f, -0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

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
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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