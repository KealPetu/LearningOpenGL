#include "Window.hpp"

int main(){
	initializeGLFW(3, 3);
	initializeWindow(800, 600, "02_Triangle");
	while (!windowShouldClose()) {
		glClearColor(245.f / 255.f, 245.f / 255.f, 245.f / 255.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		endDrawing();
	}
	destroyWindow();
	glfwTerminate();
	return 0;
}