#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

int main(int argc, char *argv[]){

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

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

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSwapInterval(1);
    float vertices[]={
        //X     //Y     //Z
        0.0f,   0.5f,   0.0f,
        -0.5f,  -0.5f,  0.0f,
        0.5f,   -0.5f,  0.0f
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Enlazar atributos de los Vertices
    //Como puede saber OpenGL que datos son de posicion, color o de cualquier otro tipo en el arreglo que definimos previamente?

    //En este caso, solamente hemos definido la posicion de los vertices, por lo que para definir estas ubicaciones tendriamos que realizar este proceso:
    glVertexAttribPointer(
        0,                  //El primer parametro indica que atributo del 'Vertex Shader' queremos configurar, ¿Recuerdas el valor de la variable de entrada que habiamos escrito en el vertex shader? Ahora es el momento en que podemos utilizarla aqui.
        3,                  //Aqui definimos el tamano del atributo. Como el atributo es un vec3, entonces mandamos el valor de 3
        GL_FLOAT,           //Especificamos que tipo de dato es (un vec* consiste de valores flotantes)
        GL_FALSE,           //Especificamos si queremos normalizar los datos.  Si estamos ingresando datos enteros o bytes y especificamos como 'GL_TRUE', entonces los valores seran normalizados a 0 y 1 cunado se convierten en flotantes
        3 * sizeof(float),  //Aqui especificamos el 'stride', en pocas palabras, es la separacion que existe entre cada vertice consecutivo.
        (void*)0            //Este parametro es de tipo void, y requiere un casteo extraño. Basicamente, es el 'offset' de donde los datos de posicion empiezan en el buffer. Debido a que los datos de posicion empiezan al inicio del arreglo, el valor es simplemente de 0.
    );

    //Ahora que hemos dicho a OpenGL como interpretar los datos del arreglo, debemos ahora activar los atributos con glEnableVertexAttribute, dandole como primer argumetno la ubicacion del mismo.
    glEnableVertexAttribArray(0);
    //Y si queremos almacenar estas configuraciones y simplemente enlazarlas con el objeto para restaurar su estado?


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Ciclo de renderizado
    while(!glfwWindowShouldClose(window)){

        // Entrada de Usuario
        processInput(window);

        //comandos de Renderizado aquí
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        //verifica y llama los eventos e intercambia los buffers
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);
}