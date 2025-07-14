//Create two shader programs where the second program uses a different fragment shader that outputs the color yellow; 
//draw both triangles again where one outputs the color yellow
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

unsigned short WIDTH = 800;
unsigned short  HEIGHT = 600;

void validateShaderCompilation(GLuint shader, GLenum type) {

    GLint success;
    GLchar infoLog[512];

    if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER) {
        std::cerr << "ERROR::SHADER::UNKNOWN_TYPE" << std::endl;
        return;
    }

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "\nERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") 
                  << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
}

void createVertexShader(GLuint &vertexShader, const GLchar *VERTEX_SHADER_SOURCE){

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &VERTEX_SHADER_SOURCE, NULL);
    glCompileShader(vertexShader);

    validateShaderCompilation(vertexShader, GL_VERTEX_SHADER);
}

void createFragmentShader(GLuint &fragmentShader, const GLchar *FRAGMENT_SHADER_SOURCE){
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER_SOURCE, NULL);
    glCompileShader(fragmentShader);

    validateShaderCompilation(fragmentShader, GL_FRAGMENT_SHADER);
}

void validateShaderProgramLinking(GLuint shaderProgram) {

    GLint success;
    GLchar infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "\nERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
}

void createShaderProgram(GLuint &shaderProgram, GLuint vertexShader, GLuint fragmentShader){

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    validateShaderProgramLinking(shaderProgram);
}

void createVBO(GLuint &VBO, GLfloat *vertices, size_t size){
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
}

void configureVAO(GLuint &VAO, GLuint &VBO, GLfloat *vertices, size_t size){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    createVBO(VBO, vertices, size);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
}

void render(GLuint shaderProgram, GLuint shaderProgramYellow, GLuint VAO[]){
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glUseProgram(0);
}

int main(int argc, char *argv[]){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, *argv, NULL, NULL);

    if (window == NULL){

        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){

        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }  

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    GLuint VAO[2], VBO[2];

    GLfloat triangleVertices1[] = {
        -0.1f, -0.5f,
        -0.9f, -0.5f,
        -0.5f, 0.5f
    };
    configureVAO(VAO[0], VBO[0], triangleVertices1, sizeof(triangleVertices1)/sizeof(GLfloat));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLfloat triangleVertices2[] = {
        0.1f, -0.5f,
        0.9f, -0.5f,
        0.5f, 0.5f
    };

    configureVAO(VAO[1], VBO[1], triangleVertices2, sizeof(triangleVertices2)/sizeof(GLfloat));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint vertexShader;
    const GLchar *VERTEX_SHADER_SOURCE =
    "#version 460 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main(){\n"
    "    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);\n"
    "}\0";
    createVertexShader(vertexShader, VERTEX_SHADER_SOURCE);

    GLuint fragmentShader;
    const GLchar *FRAGMENT_SHADER_SOURCE =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
    createFragmentShader(fragmentShader, FRAGMENT_SHADER_SOURCE);

    GLuint fragmentShaderYellow;
    const GLchar *FRAGMENT_SHADER_SOURCE_YELLOW =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "    FragColor = vec4(1.0f, 0.871f, 0.129f, 1.0f);\n"
    "}\0";
    createFragmentShader(fragmentShaderYellow, FRAGMENT_SHADER_SOURCE_YELLOW);

    GLuint shaderProgram;
    createShaderProgram(shaderProgram, vertexShader, fragmentShader);

    GLuint shaderProgramYellow;
    createShaderProgram(shaderProgramYellow, vertexShader, fragmentShaderYellow);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShaderYellow);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    while(!glfwWindowShouldClose(window)){

        // User Input
        processInput(window);
        glClearColor(0.5f, 0.1f, 0.9f, 1.0f);

        // Render
        render(shaderProgram, shaderProgramYellow, VAO);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Cleanup
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO[0]);
    glDeleteBuffers(1, &VBO[0]);
    glDeleteVertexArrays(1, &VAO[1]);
    glDeleteBuffers(1, &VBO[1]);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgramYellow);

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