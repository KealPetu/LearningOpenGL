#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//Este codigo solo es de expliacion, no existiran cambios visibles en la ventana si se ejecuta.
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

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

    //Para dibujar un triangulo, configuramos las coordenadas de los vértices en formato NDC
    //Cada punto dentro del arreglo debe ir dentro de este rango para ser visible en la ventana: [-1, 1]. Si los vertices salen de este rango, no estaran dentro de la ventana.
    float vertices[]={
        //X     //Y     //Z
        0.0f,   0.5f,   0.0f,   //Vertice superior
        -0.5f,  -0.5f,  0.0f,   //Vertice inferior izquierda
        0.5f,   -0.5f,  0.0f    //Vertice inferior derecha
    };

    /*Mas contenido en el codigo con etiqueta 4.2*/

    // Ciclo de renderizado
    while(!glfwWindowShouldClose(window)){

        // Entrada de Usuario
        processInput(window);

        //comandos de Renderizado aquí
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        //verifica y llama los eventos e intercambia los buffers
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

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