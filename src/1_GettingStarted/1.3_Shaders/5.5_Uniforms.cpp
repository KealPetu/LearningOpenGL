#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "uniform float timeValue;\n"
    "void main()\n"
    "{\n"
    "   float myZPosition = (cos(timeValue)/2.0f) + 1.0f;"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0f, myZPosition);\n"
    "}\0";

const char *orangeFragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    //Los uniforms son otra forma de enviar datos de la CPU a la GPU.
    //Los uniforms son globales, es decir, que son variables unicas por cada shader program.
    //Los uniforms mantendran sus valores hasta que sean reiniciados o actualizados.
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
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

    float greenValue;
    short unsigned int vertexColorLocation;

    // Ciclo de renderizado
    while(!glfwWindowShouldClose(window)){

        //Nuestro uniform se encuentra vacio actualmente, entonces intentemos darle un valor.
        //Vamos a cambiar el valor del cuadrado de oscuro a verde con el tiempo
        //Variemos el color con la funcion seno (recibe valores en radianes)
        greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
        //Ahora, busquemos la ubicacion del uniform en nuestro shader
        vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        int zValueLocation = glGetUniformLocation(shaderProgram, "timeValue");
        //Asignamos el valor al uniform con la siguiente funcion
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glUniform1f(zValueLocation, glfwGetTime());

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