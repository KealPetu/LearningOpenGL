//
// Created by Keal on 4/13/2026.
//

#include "WindowManager.hpp"

constexpr GLfloat BACKGROUND_COLOR[4]   { 20.4f / 255.f, 20.4f / 255.f, 25.5f / 255.f, 1.f };
constexpr unsigned int WINDOW_WIDTH	    { 800 };
constexpr unsigned int WINDOW_HEIGHT	{ 450 };

int main() {
    WindowManager windowManager;
    WindowManager::initializeGLFW(3, 3);
    windowManager.initializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Polygon");
    while (!windowManager.windowShouldClose()) {
        glClearColor(BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], BACKGROUND_COLOR[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        windowManager.endDrawing();
    }
    windowManager.destroyWindow();
    glfwTerminate();
    return 0;
}
