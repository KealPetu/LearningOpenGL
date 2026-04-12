#include "Window.hpp"
#include <cstdlib>

GLFWwindow* window {};

static void log(const char* message) {
    std::cout << message << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, const int WIDTH, const int HEIGHT) {
    glViewport(0, 0, WIDTH, HEIGHT);
}

void initializeGLFW(const int versionMajor, const int versionMinor) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void initializeWindow(const int width, const int height, const char* name) {
    window = glfwCreateWindow(
            width,
            height,
            name,
            nullptr,
            nullptr
        );

    if (window == nullptr) {
        log("Failed to create GLFW window. Bailing out!");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        log("Failed to initialize glad. Bailing out!");
		glfwTerminate();
        std::exit(EXIT_FAILURE);
    };

    glViewport(0, 0, width, height);
}

void endDrawing() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void destroyWindow() {
    glfwDestroyWindow(window);
}

bool windowShouldClose() {
    return glfwWindowShouldClose(window);
}