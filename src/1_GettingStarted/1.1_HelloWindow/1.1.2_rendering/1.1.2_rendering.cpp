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

    while(!glfwWindowShouldClose(window)){

        // User Input
        processInput(window);

        //Rendering commands here...

        /*
        To veryfy that everything works correctly, we'll color the screen with a color of our choice.
        At the begining of each fotogram we want to clear the window, otherwise we would only see data from the previous fotogram.
        We can clear the screen's color buffer using glClear whwere we pass in buffer bits to specify which buffer we would like to clear.
        The possible bits we can set are:
        - GL_COLOR_BUFFER_BIT
        - GL_DEPTH_BUFFER_BIT
        - GL_STENCIL_BUFFER_BIT
        
        For now, we're only interested in the color values, so we'll only clean the values of our color buffer.
        */

        //glClearColor is a state-setting function that defines a specific color on the screen.
        glClearColor(
            0.5f,   //Red value (0 - 1)
            0.1f,   //Green value (0 - 1)
            0.9f,   //Blue value (0 - 1)
            1.0f    //Alpha (Transparency) (0 - 1)
        );

        //glClear function clears the set buffer, the entire color buffer will be filled with the color configured previously.
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
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