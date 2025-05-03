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

const char *orangeFragmentShaderSource = 
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

    //Rectangulo
    //Ahora queremos dibujar diferentes triangulos, Es necesario escribir cada vertice individualmente? No seria mas facil reutilizar las vertices que comparten estos triangulos?
    float vertices[] = {
    // primer triangulo
     0.5f,  0.5f, 0.0f,  // arriba a la derecha     Vertice 0
     0.5f, -0.5f, 0.0f,  // abajo a la derecha      Vertice 1
    -0.5f,  0.5f, 0.0f,  // arriba a la izquierda   Vertice 2
    // segundo triangulo
//   0.5f, -0.5f, 0.0f,  // abajo a la derecha
    -0.5f, -0.5f, 0.0f,  // abajo a la izquierda    Vertice 3
//  -0.5f,  0.5f, 0.0f   // arriba a la izquierda
    }; 

    //EBO
    //Element Buffer Objects son basicamente la respuesta al problema que tenemos anteriormente
    //Creamos un arreglo de indices que nos puede ayudar a formar los triangulos asignandoles un unico identificador a los vertices que habiamos definido previamente.
    unsigned int indices[] = {  //Cabe recalcar que se empieza desde el 0
        //Primer Triangulo
        0, 1, 2,
        //Segundo Triangulo
        1, 2, 3
    };

    unsigned int VBO, VAO,
    //Creamos el buffer del EBO
    EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Similar al VBO, enlazamos el EBO y copiamos los indices en el buffer con glBufferData
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //El VAO almacena las llamadas a glBindBuffer cuando el objetivo es GL_ELMENT_ARRAY_BUFFER. Lo que siginifica que tambien almacena los llamados de desenlace.
    //Asegurate de Desenlazar el buffer de elementos despues de desenlazar el VAO, de otra manera no tendra un EBO configurado.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
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
    glShaderSource(fragmentShader, 1, &orangeFragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
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

        glBindVertexArray(VAO);
        //Opcional: podemos decirle a openGL en modo wireframe, 
        //glPolygonMode dicta a OpenGL sobre como dibujar sus primitivos
        glPolygonMode(
            //El primer argumento dicta que queremos aplicarlo al frente y atras de todos los triangulos
            GL_FRONT_AND_BACK,
            //Decimos que queremos dibujarlos como lineas
            GL_LINE
        );//cualquier llamada subsuiguiente usara este modo hasta que lo configuremos por defecto: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //Ahora, en luger de usar la funcion anterior, utilizamos glDrawElements para indicar que queremos renderizar triangulos desde un index buffer.
        glDrawElements(
            //Especifica el modo en que queremos dibujar
            GL_TRIANGLES, 
            //Indica la cantidad de elementos que queremos dibujar, especificamos 6 indices, entonces dibujaremos los 6
            6, 
            //El tipo de indices del que habiamos asignado
            GL_UNSIGNED_INT, 
            //Indica el offset en el EBO (o Enviamos un arreglo de indices, pero eso es cuando no estamos usando ebos)
            0
        );
        glBindVertexArray(0);

        //verifica y llama los eventos e intercambia los buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

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