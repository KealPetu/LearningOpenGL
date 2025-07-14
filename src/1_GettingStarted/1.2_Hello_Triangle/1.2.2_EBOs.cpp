#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
        -0.5f,  -0.5f,  //lower left    0
        0.5f,   -0.5f,  //lower right   1
        0.5f,   0.5f,    //upper right  2
        -0.5f,  0.5f,   //upper left    3
    };

    // The indices array defines the order of vertices to draw the triangles that make up the square
    // The first triangle is formed by vertices 0, 1, and 2,
    // and the second triangle is formed by vertices 0, 2, and 3
    GLuint indices[]= { 
        0, 1, 2,
        0, 2, 3 
    };

    GLuint VBO;
    GLuint VAO;
    // Create an Element Buffer Object (EBO) to store the indices
    // EBOs are used to define the order in which vertices are drawn.
    // They allow us to reuse vertices and define complex shapes without duplicating vertex data.
    // In this case, we will define a square using two triangles.
    GLuint EBO;

    // Generate and bind the VBO, EBO and VAO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    // Bind the EBO and upload the indices data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO

    // Do NOT unbind the EBO here! The EBO should remain bound to the VAO so that it can be used during rendering.
    // Unbinding the EBO here would prevent OpenGL from knowing which indices to use when drawing the triangles.

    glBindVertexArray(0); // Unbind the VAO

    // It's a good practice to unbind the EBO after setting it up
    // but in this case, we want to keep it bound to the VAO for rendering

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the EBO


    const GLchar *VERTEX_SHADER_SOURCE =
    "#version 460 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main(){\n"
    "    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);\n"
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
    "void main(){\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // Set the polygon mode to fill or line
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) sets the polygon mode to fill
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) sets the polygon mode to line
    // This allows you to see the wireframe of the triangles instead of the filled triangles.
    // Uncomment one of the lines below to change the polygon mode.
    // To see the filled triangles, use GL_FILL
    // To see the wireframe, use GL_LINE
    // Note: GL_POINT can also be used to see the vertices as points.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while(!glfwWindowShouldClose(window)){

        // User Input
        processInput(window);
        glClearColor(0.5f, 0.1f, 0.9f, 1.0f);

        // Render
        glClear(GL_COLOR_BUFFER_BIT);
        // Draw the triangles using the EBO
        // glDrawElements draws the triangles using the indices defined in the EBO.
        // The first parameter specifies the type of primitives to render (GL_TRIANGLES in this case),
        // the second parameter specifies the number of indices to be rendered,
        // the third parameter specifies the type of the indices (GL_UNSIGNED_INT in this case),
        // and the last parameter is a pointer to the first index in the EBO (0 in this case).
        // This allows OpenGL to efficiently render the triangles without duplicating vertex data
        // and using the indices to determine the order of vertices.
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw the triangles using the EBO

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Cleanup
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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