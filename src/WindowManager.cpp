#include "WindowManager.hpp"

WindowManager::WindowManager() : m_window(nullptr) {}

WindowManager::~WindowManager() {
    if (m_window) {
        destroyWindow();
    }
}

void WindowManager::Log(const char *message){
    std::cout << message << std::endl;
}

void WindowManager::framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
    // Recovers our class from the window's user pointer and updates the width and height values.
    if (WindowManager* instance { static_cast<WindowManager*>(glfwGetWindowUserPointer(window)) }) {
        instance->m_width = width;
        instance->m_height = height;
    }
}

void WindowManager::initializeGLFW(const int versionMajor, const int versionMinor) {

    if (!glfwInit()) {
        Log("Failed to initialize GLFW. Bailing out!");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    const std::string glfwVersionMessage = "GLFW " + std::to_string(major) + "." + std::to_string(minor) + "." +
        std::to_string(revision) + " Initialized";
    Log(glfwVersionMessage.c_str());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void WindowManager::initializeWindow(const int width, const int height, const char* name) {
    m_width = width;
    m_height = height;
    m_window = glfwCreateWindow(
        m_width,
        m_height,
        name,
        nullptr,
        nullptr
    );

    if (!m_window) {
        Log("Failed to create GLFW window. Bailing out!");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    const std::string windowMessage = "Window created: \"" + std::string(name) +
                                "\" " + std::to_string(width) + "x" +
                                std::to_string(height) + "@" + std::to_string(mode->refreshRate) + "Hz";
    Log(windowMessage.c_str());

    glfwSetWindowUserPointer(m_window, this); // Connects the window to this class' object.
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    toggleVsync(true);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        Log("Failed to initialize glad. Bailing out!");
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    };

    const std::string glInfoMessage = "OpenGL version: " +
                std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))) + " | GLSL " +
                std::string(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
    Log(glInfoMessage.c_str());

    glViewport(0, 0, m_width, m_height);
}

void WindowManager::beginDrawing()
{
    m_currentTime = static_cast<float>(glfwGetTime());
    m_deltaTime = m_currentTime - m_lastTime;
}

void WindowManager::endDrawing()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    m_lastTime = m_currentTime;
}

void WindowManager::destroyWindow() const {
    glfwDestroyWindow(m_window);
}

bool WindowManager::windowShouldClose() const{
    return glfwWindowShouldClose(m_window);
}

GLFWwindow* WindowManager::getWindow() const {
    return m_window;
}

void WindowManager::toggleVsync(bool vsyncEnabled)
{
    glfwSwapInterval(vsyncEnabled ? 1 : 0);
}