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

    //To draw a Triangle, first we need the vertices of it. OpenGL recognises normalized device coordinates (NDC) 
    //so everything will be visible if we draw stuff inside this range (-1, 1).

    GLfloat triangleVertices[] = {
        -0.5f,  -0.5f,  //lower left
        0.5f,   -0.5f,  //lower right
        0.0f,   0.5f    //upper center
    };

    //Vertex Buffer Object (VBO) and Vertex Array Object (VAO) are used to store the vertex data and its attributes.
    //VBO stores the vertex data in GPU memory, while VAO stores the state of the vertex attributes.
    GLuint VBO;
    GLuint VAO;

    // Generate and bind the VBO and VAO
    // glGenBuffers generates buffer objects and returns their IDs.
    glGenBuffers(1, &VBO);
    // glGenVertexArrays generates vertex array objects and returns their IDs.
    glGenVertexArrays(1, &VAO);

    // Bind the VAO first, then bind and set the VBO
    // glBindVertexArray binds the VAO, which stores the state of the vertex attributes
    glBindVertexArray(VAO);
    // glBindBuffer binds the VBO to the GL_ARRAY_BUFFER target, which is used for vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData uploads the vertex data to the GPU memory
    // The first parameter specifies the target (GL_ARRAY_BUFFER), the second parameter specifies the size
    // of the data in bytes, the third parameter is a pointer to the data, and the fourth parameter specifies the usage pattern of the data.
    // GL_STATIC_DRAW indicates that the data will not change often, so it can be optimized for static usage.
    // The data is copied to the GPU memory, and the VBO is now ready to use.
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    // Now we need to specify the vertex attributes
    // glVertexAttribPointer specifies the layout of the vertex data in the VBO.
    // The first parameter is the index of the vertex attribute (0 in this case), the second parameter is the size of the attribute (2 for 2D coordinates),
    // the third parameter is the data type of the attribute (GL_FLOAT for floating-point values),
    // the fourth parameter specifies whether the attribute should be normalized (GL_FALSE means it won't be normalized),
    // the fifth parameter is the stride (the byte offset between consecutive attributes, 2 * sizeof(GLfloat)
    // in this case, since we have two floats per vertex), and the last parameter is a pointer to the first component of the vertex data (0 means the data starts at the beginning of the buffer).
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    // glEnableVertexAttribArray enables the vertex attribute at index 0, which allows OpenGL to use the vertex data.
    // This tells OpenGL to use the vertex data stored in the VBO for the vertex attribute at index 0.
    // The vertex attribute index corresponds to the layout(location = 0) in the vertex shader.
    // This is necessary to tell OpenGL how to interpret the vertex data.
    glEnableVertexAttribArray(0);

    // Unbind the VBO and VAO
    // It's a good practice to unbind the VBO and VAO after setting them up
    // This prevents accidental modifications to the VBO and VAO later in the code.
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO
    glBindVertexArray(0); // Unbind the VAO

    // Now we can create the shaders
    // Shaders are small programs that run on the GPU to process vertex and fragment data.
    // The vertex shader processes each vertex and outputs its position in clip space.
    const GLchar *VERTEX_SHADER_SOURCE =
    "#version 460 core\n"                                   // OpenGL version 4.6 core profile
    "layout (location = 0) in vec2 aPos;\n"                 // Input vertex attribute at location 0 (2D position)
    "void main(){\n"
    "    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);\n" // Set the output position of the vertex in clip space
    "}\0";

    // Create the vertex shader
    // glCreateShader creates a shader object of the specified type (GL_VERTEX_SHADER in this case).
    // The shader object is identified by a GLuint, which is an unsigned integer type.
    // The shader source code is provided as a string, and it needs to be compiled before it can be used.
    // The shader source code is written in GLSL (OpenGL Shading Language),
    // which is a C-like language used to write shaders.
    // The vertex shader takes the vertex position as input and outputs the position in clip space.
    // The gl_Position variable is a built-in variable in the vertex shader that specifies the position
    // of the vertex in clip space, which is the coordinate system used by OpenGL for rendering.
    // The layout(location = 0) specifies that this attribute corresponds to the first vertex attribute
    // (index 0) in the vertex array object (VAO).
    // The main function is the entry point of the vertex shader, and it is called for each vertex processed by the shader.
    // The gl_Position variable is set to a vec4 that contains the x and y coordinates
    // from the input vertex attribute (aPos) and sets the z coordinate to 0.0f and the w coordinate to 1.0f.
    // The w coordinate is used for homogeneous coordinates, which allows OpenGL to perform perspective division later in the rendering pipeline.
    GLuint vertexShader;
    // glCreateShader creates a shader object of the specified type (GL_VERTEX_SHADER in this case).
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // glShaderSource sets the source code of the shader object.
    // The first parameter is the shader object, the second parameter is the number of strings in the source code (1 in this case),
    // the third parameter is a pointer to the source code strings, and the last parameter is a pointer to an array of lengths of each string (NULL
    // means the strings are null-terminated).
    glShaderSource(vertexShader, 1, &VERTEX_SHADER_SOURCE, NULL);
    // glCompileShader compiles the shader source code into machine code that can be executed by the GPU.
    // This step is necessary before linking the shader into a shader program.
    glCompileShader(vertexShader);

    // Check for compilation errors
    int success;
    char infoLog[512];

    // glGetShaderiv retrieves information about the shader object.
    // The first parameter is the shader object, the second parameter is the parameter to retrieve (GL_COMPILE_STATUS in this case),
    // and the third parameter is a pointer to an integer where the result will be stored.
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // If the compilation was not successful, we retrieve the error log using glGetShaderInfoLog.
    if (!success)
    {
        // glGetShaderInfoLog retrieves the information log for the shader object.
        // The first parameter is the shader object, the second parameter is the size of the buffer
        // to store the log (512 in this case), the third parameter is a pointer to an integer where the length of the log will be stored (NULL in this case),
        // and the last parameter is a pointer to a character array where the log will be stored.
        // The infoLog array will contain the error message if the compilation failed.
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        // If the compilation failed, we print the error message to the console.
        std::cout << "\nERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return EXIT_FAILURE;
    }

    // Now we can create the fragment shader
    // The fragment shader is responsible for determining the color of each pixel in the rendered image.
    // It takes the output from the vertex shader and processes it to produce the final color.
    // The fragment shader is also written in GLSL and is executed for each pixel that is rasterized.
    // The fragment shader outputs a vec4 color value, which represents the red, green, blue, and alpha (transparency) components of the color.
    // The output color is assigned to the built-in variable FragColor, which is used by OpenGL to determine the final color of the pixel.
    // The main function is the entry point of the fragment shader, and it is called for each pixel processed by the shader.
    // In this case, we set the FragColor to a constant color value of (1.0f, 0.5f, 0.2f, 1.0f), which is an orange color.
    const GLchar *FRAGMENT_SHADER_SOURCE =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    // Create the fragment shader
    // Similar to the vertex shader, we create a shader object for the fragment shader and set its source code.
    // The fragment shader is created with glCreateShader(GL_FRAGMENT_SHADER), and
    // the source code is set using glShaderSource.
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

    // Now we can link the vertex and fragment shaders into a shader program
    // A shader program is a combination of one or more shaders that can be used to render objects in OpenGL.
    // The shader program is created with glCreateProgram.
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    // glAttachShader attaches the vertex and fragment shaders to the shader program.
    // This step is necessary before linking the shaders into a program.
    // The vertex shader processes the vertex data, and the fragment shader determines the color of each
    // pixel in the rendered image.
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // glLinkProgram links the attached shaders into a shader program.
    // This step combines the vertex and fragment shaders into a single program that can be used for rendering.
    // The shader program is identified by the shaderProgram variable, which is a GLuint.
    // After linking, the shader program can be used to render objects in OpenGL.
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "\nERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return EXIT_FAILURE;
    }

    // After linking, we can delete the shader objects as they are no longer needed
    // glDeleteShader deletes the shader object, freeing up resources.
    // This is a good practice to avoid memory leaks, as the shader objects are no longer needed after linking them into a program.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Now we can use the shader program to render the triangle
    // glUseProgram sets the current shader program to be used for rendering.
    // This tells OpenGL to use the specified shader program for subsequent rendering operations.
    glUseProgram(shaderProgram);
    // Bind the VAO before rendering
    // The VAO stores the state of the vertex attributes, so we need to bind it
    // before rendering to ensure that OpenGL uses the correct vertex data.
    glBindVertexArray(VAO);
    while(!glfwWindowShouldClose(window)){

        // User Input
        processInput(window);
        glClearColor(0.5f, 0.1f, 0.9f, 1.0f);

        // Render
        glClear(GL_COLOR_BUFFER_BIT);
        // glDrawArrays draws the triangle using the vertex data stored in the VAO.
        // The first parameter specifies the primitive type (GL_TRIANGLES in this case),
        // the second parameter is the starting index of the vertex data (0 in this case),
        // and the third parameter is the number of vertices to draw (3 in this case,
        // since we have 3 vertices for the triangle).
        // This function processes the vertex data and uses the vertex and fragment shaders to render the triangle
        // to the screen. The vertex shader processes each vertex, and the fragment shader determines the
        // color of each pixel in the triangle.
        // The triangle is drawn using the vertex data stored in the VAO, which contains the vertex positions.
        // The glDrawArrays function is called within the rendering loop to draw the triangle
        // every frame. This allows for dynamic rendering, where the triangle can be updated or animated
        // by changing the vertex data or shader parameters.
        // In this case, we are drawing a static triangle with the specified vertex positions.
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Cleanup
    // Unbind the VAO to avoid accidental modifications later
    glBindVertexArray(0);
    // Delete the VBO, VAO, and shader program to free up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteProgram deletes the shader program, freeing up resources.
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