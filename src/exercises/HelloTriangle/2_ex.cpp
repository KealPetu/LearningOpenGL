#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//2. Now create the same 2 triangles using two different VAOs and VBOs for their data

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = 
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

    unsigned int VBO_1, VAO_1, VBO_2, VAO_2;

    float vertices_1[] = {
        0.5f,  0.5f,
        0.5f, -0.5f,
       -0.5f,  0.5f,
    };

    float vertices_2[] = {
        0.5f, -0.5f,
       -0.5f,  0.5f,
       -0.5f, -0.5f,
    };

    glGenVertexArrays(1, &VAO_1);
    glGenBuffers(1, &VBO_1);

    glBindVertexArray(VAO_1);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glGenVertexArrays(1, &VAO_2);
    glGenBuffers(1, &VBO_2);

    glBindVertexArray(VAO_2);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    
    unsigned int shaderProgram;
    createMyShaderProgram(&shaderProgram);
    glUseProgram(shaderProgram);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Ciclo de renderizado
    while(!glfwWindowShouldClose(window)){

        // Entrada de Usuario
        processInput(window);

        glBindVertexArray(VAO_1);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO_2);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        //verifica y llama los eventos e intercambia los buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO_1);
    glDeleteBuffers(1, &VBO_1);
    glDeleteVertexArrays(1, &VAO_2);
    glDeleteBuffers(1, &VBO_2);
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
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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