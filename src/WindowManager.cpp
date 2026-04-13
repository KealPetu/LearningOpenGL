#include "WindowManager.hpp"

WindowManager::WindowManager() : window(nullptr) {}

WindowManager::~WindowManager() {
    if (window) {
        destroyWindow();
    }
}

void WindowManager::Log(const char *message){
    std::cout << message << std::endl;
}

void WindowManager::framebuffer_size_callback(GLFWwindow *window, const int WIDTH, const int HEIGHT) {
    glViewport(0, 0, WIDTH, HEIGHT);
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

void WindowManager::initializeWindow(int width, int height, const char* name) {
    window = glfwCreateWindow(
        width,
        height,
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

void WindowManager::endDrawing() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void WindowManager::destroyWindow() {
    glfwDestroyWindow(window);
    Log("Window closed successfully");
}

bool WindowManager::windowShouldClose() const{
    return glfwWindowShouldClose(window);
}

GLFWwindow* WindowManager::getWindow() const {
    return window;
}
