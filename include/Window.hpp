#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void initializeWindow(const int width, const int height, const char* name);
void framebuffer_size_callback(GLFWwindow* window, const int WIDTH, const int HEIGHT);
void destroyWindow();
void endDrawing();
bool windowShouldClose();
void initializeGLFW(const int versionMajor, const int versionMinor);