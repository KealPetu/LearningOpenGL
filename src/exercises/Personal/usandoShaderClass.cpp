#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <Shader.h>

const int WIDTH = 512, HEIGHT = 512;
float aspect = (float)WIDTH/HEIGHT;
float wValue = 1.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

int main(int argc, char *argv[]){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);

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

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    unsigned int VBO, VAO, EBO;

    float vertices[] = {
        //coordenadas   //colores
        //x    y        r     g     b
        0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,   1.0f, 1.0f, 1.0f
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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Shader myShaderProgram("../../../src/shaders/usandoShaderClass/vshader.vs", "../../../src/shaders/usandoShaderClass/fshader.fs"); 
    myShaderProgram.use();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glBindVertexArray(VAO);

    // Ciclo de renderizado
    while(!glfwWindowShouldClose(window)){

        myShaderProgram.setFloat("wValue", wValue);
        myShaderProgram.setFloat("aspect", aspect);

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
    myShaderProgram.deleteShaderProgram();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);
    aspect = (float)width/height;
}

void processInput(GLFWwindow *window){

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        wValue -= 0.01f;

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        wValue += 0.01f;
}