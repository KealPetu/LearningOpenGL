#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(int argc, char *argv[])
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); 

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window))   
    {
        processInput(window);//Llamamos el proceso en cada iteracion del ciclo
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//GLFW tiene varias fucniones de entrada, en esta ocasón se utilizará la funcion glfwGetKey
//que toma como entrada a la ventana y la tecla presionada.
//Esta función devolverá si una tecla está siendo presionada.
//Estamos creado un proceso de entrada para mantener el codigo organizado
void processInput(GLFWwindow *window)
{
    //Aqui verificamos que el ususario haya presionado una tecla (sino, la funcion deviuelve
    //GLFW_RELEASE)
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        //Si el usuario SI presiono la tecla, cerramos la ventana al conifgurar la funcion
        //WindowShouldClose como 'true'  
        glfwSetWindowShouldClose(window, true);
}