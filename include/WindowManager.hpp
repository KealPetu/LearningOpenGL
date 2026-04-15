#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>

class WindowManager {
private:
    GLFWwindow *window;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    WindowManager();
    ~WindowManager();

    static void Log(const char* message);
    static void initializeGLFW(int versionMajor, int versionMinor);
    void initializeWindow(int width, int height, const char *name);
    void endDrawing() const;
    void destroyWindow() const;

    bool windowShouldClose() const;
    GLFWwindow* getWindow() const;
};