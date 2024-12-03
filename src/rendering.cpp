#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

    // Ciclo de renderizado
    while(!glfwWindowShouldClose(window)){

        // Entrada de Usuario
        processInput(window);

        //comandos de Renderizado aquí
        //...


        //Para verificar que todo funcione correctamente, quieremos colorear la pantalla con un color
        //de nuestra elección
        //Queremos limpiar la ventana al inicio del fotograma, de otra forma veriamos datos del fotograma
        //anterior.
        //Utilizamos glClear en el que pasamos bits de buffer para especificar en que buffer 
        //queremos limpiar.
        //Los bits posible que podemos pasar son:
        //GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT y GL_STENCIL_BUFFER_BIT.
        //Por ahora solo nos interesan los valores de color, por lo que solo limpiaremos los valores
        //del buffer de color.

        //glClearColor es una funcion 'state-setting', que se encarga de definir el color en especifico 
        //de la pantalla
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear es una funcion 'state-using', que utiliza el estado actual para recuperar el color de limpie 
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