#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int argc, char *argv[])
{
    //Function to initialize the GLFW library
    glfwInit();

    //Function used to configure a feature to the window
    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR, //On this field we tell OpenGL wich feature we want to modify, in this case, we want to modify the major version of OpenGL
        3   //We want to use the version 3.3, so we set the value as 3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR, //Minor version of OpenGL
        3   //OpenGL 3.3
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,    //Here, we specify the OpenGL profile we are going to use.
        GLFW_OPENGL_CORE_PROFILE//When configuring the glad.c file, I only chose the COre version, so we are not going to have access to deprecated functions.
    );

    //Now, we are going to create the Window object.
    //This object contains all the windowing parameters, which are required for most of the functions of GLFW.
    GLFWwindow* window = glfwCreateWindow(
        800,            //We set the window width in pixels
        600,            //Window height
        "LearnOpenGL",  //Name of the window
        NULL,           //Which monitor is the window going to use. If left NULL, we will use the default primary monitor.
        NULL            //If there's another window, we set in this field wich window is it going to share resources with.
    );

    //If the window doesn't exist
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;   //Prints message error.
        glfwTerminate();                                            //Uses this function to end the program.
        return -1;                                                  //Returns -1 as error.
    }

    
    //This function allows us to intercalate between different OpenGL contexts (windows), allowing us to utiliza different windows or rendering settings.
    glfwMakeContextCurrent(window);
    //Everything under here will be rendered on "window"
    //...

    //If we create another window

    //glfwMakeContextCurrent(window2)
    //Everything under here will be rendered on "window2"
    //...

    //Before using any OpenGL function, we need to load them by using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //We initilalize the OpenGL API using GLFW.
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    //We define the region of the window where is going to be rendered
    glViewport(
        0,      //X location from where the viewport is generated: 0 = left from the window.
        0,      //Y location from where the viewport is generated: 0 = base from the window.
        800,    //Width of the ViewPort in pixels.
        600);   //Height of the ViewPort in pixels.

    //With this method, can set callbacks, fucntions that get triggered whenever the framebuffer (area where the window is rendered) of a specified window changes.
    //We want the viewport and window size to be the same everytime, so we create the "framebuffer_size_callback" function and tell glfw to use it whenever we change the window size.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1); // Habilitamos Sincronización vertical
    
    //We don't want our program open and close immediately, we want it to keep drawing images and manages user inputs until we explicitly tell the program to close.
    //For this reason, we create this "render loop".

    //It verifies if GLFW has been set to close the window
    //If that's the case, the function returns 'true' and the render loop ends.
    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);//This event verifies if there has been any input, and changes the window state, then, calls the fucntions(that could've been registered in the callbacks).
        glfwPollEvents();       //Changes the color buffer (a long 2d buffer that contains the color value of each pixel) that is then used to render and shown to the monitor.
    }

    //As soon as we exit the render loop, we must clean the assigned GLFW resources.
    glfwTerminate(); 
    return 0;
}

//Function we set that, each time the user changes the window size, the Viewport shall change too. The frambuffer functioon takes a GLFWwindow (the window) and 2 integers (new window dimensions).
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
