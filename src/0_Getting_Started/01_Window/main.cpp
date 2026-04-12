#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

constexpr int WINDOW_WIDTH  { 800 };
constexpr int WINDOW_HEIGHT { 600 };
auto WINDOW_NAME            { "01_Window" };

static void Log(const char* message){
    std::cout << message << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, const int WIDTH, const int HEIGHT){
    glViewport(0, 0, WIDTH, HEIGHT);
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window {
        glfwCreateWindow(
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            WINDOW_NAME,
            nullptr,
            nullptr
        )
    };

    if (window == nullptr) {
        Log("Failed to create GLFW window. Bailing out!");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))){
        Log("Failed to initialize glad. Bailing out!");
        return -1;
    };

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    while(!glfwWindowShouldClose(window)){
        glClearColor(245.f/255.f, 245.f/255.f, 245.f/255.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}