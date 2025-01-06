#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <Shader.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int WIDTH = 512, HEIGHT = 512;
float aspect = (float)WIDTH/HEIGHT;
float wValue = 1.0f, xValue = 0.0f, yValue = 0.0f;

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

    unsigned int VBO, VAO, EBO,

    texture;

    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("../../images/container.jpg", &width, &height, &nrChannels, 0); 

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    float vertices[] = {
    // positions    // colors           // texture coords
     0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // top right
     0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // bottom right
    -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   // bottom left
    -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2); 

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Shader myShaderProgram("../../shaders/shadersContenedor/vshader.vs", "../../shaders/shadersContenedor/fshader.fs"); 
    myShaderProgram.use();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);

    // Ciclo de renderizado
    while(!glfwWindowShouldClose(window)){

        myShaderProgram.setFloat("wValue", wValue);
        myShaderProgram.setFloat("xValue", xValue);
        myShaderProgram.setFloat("yValue", yValue);
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
        yValue -= 0.01f;

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        yValue += 0.01f;

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        xValue += 0.01f;

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        xValue -= 0.01f;

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) 
        wValue += 0.01f;

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) 
        wValue -= 0.01f;
}

