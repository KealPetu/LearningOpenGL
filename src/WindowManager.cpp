#include "WindowManager.hpp"

WindowManager::WindowManager() : window(nullptr) {}

WindowManager::~WindowManager() {
    if (window) {
        destroyWindow();
        Log("Window closed successfully");
    }
}

void WindowManager::Log(const char *message){
    std::cout << message << std::endl;
}

void WindowManager::framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
    // Recovers our class from the window's user pointer and updates the width and height values.
    if (WindowManager* instance { static_cast<WindowManager*>(glfwGetWindowUserPointer(window)) }) {
        instance->mWidth = width;
        instance->mHeight = height;
    }
}

void WindowManager::initializeGLFW(const int versionMajor, const int versionMinor) {

    if (!glfwInit()) {
        Log("Failed to initialize GLFW. Bailing out!");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    const std::string initMessage = "GLFW initialized - OpenGL version: " +
                              std::to_string(versionMajor) + "." +
                              std::to_string(versionMinor) + " Core Profile";
    Log(initMessage.c_str());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void WindowManager::initializeWindow(const int width, const int height, const char* name) {
    mWidth = width;
    mHeight = height;
    window = glfwCreateWindow(
        mWidth,
        mHeight,
        name,
        nullptr,
        nullptr
    );

    if (!window) {
        Log("Failed to create GLFW window. Bailing out!");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    std::string windowMessage = "Window created: \"" + std::string(name) +
                                "\" (" + std::to_string(width) + "x" +
                                std::to_string(height) + ")";
    Log(windowMessage.c_str());

    glfwSetWindowUserPointer(window, this); // Connects the window to this class' object.
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        Log("Failed to initialize glad. Bailing out!");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    };

    glViewport(0, 0, width, height);
}

void WindowManager::endDrawing() const {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void WindowManager::destroyWindow() const {
    glfwDestroyWindow(window);
}

bool WindowManager::windowShouldClose() const{
    return glfwWindowShouldClose(window);
}

GLFWwindow* WindowManager::getWindow() const {
    return window;
}