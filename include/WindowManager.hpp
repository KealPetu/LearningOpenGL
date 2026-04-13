#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>

class WindowManager {
private:
    GLFWwindow *window;

    static void Log(const char* message);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    WindowManager();
    ~WindowManager();

    void initializeGLFW(int versionMajor, int versionMinor);
    void initializeWindow(int width, int height, const char *name);
    void endDrawing();
    void destroyWindow();
    bool windowShouldClose() const;

    GLFWwindow* getWindow() const;
};