#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//3. Create two shader programs where the second program uses a different fragment shader that outputs the color yellow; draw both triangles again where one outputs the color yellow

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

const char *yellowFragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}";


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void createMyShaderProgram(unsigned int *orangeShaderProgram, unsigned int *yellowShaderProgram);

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


    float vertices[] = {
        0.5f,  0.5f,
        0.5f, -0.5f,
        -0.5f,  0.5f,
        0.5f, -0.5f,
        -0.5f,  0.5f,
        -0.5f, -0.5f,
    };

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    unsigned int orangeShaderProgram, yellowShaderProgram;
    createMyShaderProgram(&orangeShaderProgram, &yellowShaderProgram);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glBindVertexArray(VAO);

    // Ciclo de renderizado
    while(!glfwWindowShouldClose(window)){

        // Entrada de Usuario
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(orangeShaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(yellowShaderProgram);
        glDrawArrays(GL_TRIANGLES, 3, 6);

        //verifica y llama los eventos e intercambia los buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(orangeShaderProgram);
    glDeleteProgram(yellowShaderProgram);

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

void createMyShaderProgram(unsigned int *orangeShaderProgram, unsigned int *yellowShaderProgram){

    unsigned int vertexShader, orangeFragmentShader, yellowFragmentShader;
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilationErrors(&vertexShader, 0);

    orangeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(orangeFragmentShader, 1, &orangeFragmentShaderSource, NULL);
    glCompileShader(orangeFragmentShader);
    checkShaderCompilationErrors(&orangeFragmentShader, 1);

    yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, NULL);
    glCompileShader(yellowFragmentShader);
    checkShaderCompilationErrors(&yellowFragmentShader, 1);

    *orangeShaderProgram = glCreateProgram();
    glAttachShader(*orangeShaderProgram, vertexShader);
    glAttachShader(*orangeShaderProgram, orangeFragmentShader);
    glLinkProgram(*orangeShaderProgram);
    checkShaderProgramLinkingErrors(orangeShaderProgram);

    *yellowShaderProgram = glCreateProgram();
    glAttachShader(*yellowShaderProgram, vertexShader);
    glAttachShader(*yellowShaderProgram, yellowFragmentShader);
    glLinkProgram(*yellowShaderProgram);
    checkShaderProgramLinkingErrors(yellowShaderProgram);


    glDeleteShader(vertexShader);
    glDeleteShader(orangeFragmentShader);
    glDeleteShader(yellowFragmentShader);
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