#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

constexpr int WINDOW_WIDTH {800};
constexpr int WINDOW_HEIGHT {600};
const char* WINDOW_NAME {"01_Window"};

void Log(const char* message){
    std::cout << message << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window {
        glfwCreateWindow(
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            WINDOW_NAME,
            nullptr,
            nullptr
        )
    };

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        Log("Failed to initialize glad. Bailing out!");
        return -1;
    };

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glClearColor(245/255, 245/255, 245/255, 1.0f);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}