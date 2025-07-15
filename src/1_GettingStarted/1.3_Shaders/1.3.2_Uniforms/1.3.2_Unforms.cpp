#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

unsigned short WIDTH = 800;
unsigned short  HEIGHT = 600;

int main(int argc, char *argv[]){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL){

        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); 

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){

        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    GLfloat triangleVertices[] = {
        -0.5f,  -0.5f,  //lower left
        0.5f,   -0.5f,  //lower right
        0.0f,   0.5f    //upper center
    };

    GLuint VBO, VAO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const GLchar *VERTEX_SHADER_SOURCE =
    "#version 460 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos, 0.0f, 1.0f);\n"    //See how we directly give a vec3 to vec4's constructor
    "}\0";
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &VERTEX_SHADER_SOURCE, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "\nERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return EXIT_FAILURE;
    }

    const GLchar *FRAGMENT_SHADER_SOURCE =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"      //Declare a uniform variable to receive the color
    "void main(){\n"
    "    FragColor = ourColor;\n"   //Set the output color to the uniform variable
    "}\0";

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER_SOURCE, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "\nERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return EXIT_FAILURE;
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "\nERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return EXIT_FAILURE;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Uniforms
    // Set up a uniform variable to change the color dynamically
    GLfloat timeValue, geenValue;
    glUseProgram(shaderProgram);
    // Get the location of the uniform variable in the shader program
    // This is where we will set the color dynamically
    // The uniform variable is named "ourColor" in the fragment shader
    // It is important to note that the uniform variable must be set after the shader program is linked
    // and before it is used for rendering
    // The location is an integer that represents the index of the uniform variable in the shader program
    // It is used to set the value of the uniform variable in the shader program
    // The function glGetUniformLocation returns the location of the uniform variable in the shader program
    // If the uniform variable is not found, it returns -1
    // If the uniform variable is found, it returns the index of the uniform variable in the shader program
    // This index is used to set the value of the uniform variable in the shader
    GLint uniformLocation = glGetUniformLocation(shaderProgram, "ourColor");

    while(!glfwWindowShouldClose(window)){

        // User Input
        processInput(window);

        // Render

        glClearColor(0.5f, 0.1f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);

        // Update the uniform variable with a dynamic color value
        // Here we use the sine function to create a dynamic color value that changes over time
        // The sine function returns a value between -1 and 1, so we normalize it
        // to a value between 0 and 1 by dividing by 2 and adding 0.5
        // This will create a smooth transition between colors over time
        // The timeValue variable is updated with the current time in seconds
        // using the glfwGetTime function, which returns the time in seconds since the GLFW library
        // was initialized
        // The geenValue variable is calculated using the sine function to create a dynamic color value
        // that changes over time
        // The glUniform4f function is used to set the value of the uniform variable in the shader program
        // The first parameter is the location of the uniform variable in the shader program
        // The second parameter is the red component of the color, which is set to 0.0f
        // The third parameter is the green component of the color, which is set to the dynamic geenValue
        // The fourth parameter is the blue component of the color, which is set to 0.0f
        // The fifth parameter is the alpha component of the color, which is set to 1.0f (fully opaque)
        timeValue = glfwGetTime();
        geenValue = (sin(timeValue) / 2.0f) + 0.5f; // Normalize to [0, 1]

        std::cout << "Green Value: " << geenValue << std::endl;
        glUniform4f(uniformLocation, 0.0f, geenValue, 0.0f, 1.0f); // Set the uniform color to green
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(0);
        glBindVertexArray(0);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Cleanup
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);
}