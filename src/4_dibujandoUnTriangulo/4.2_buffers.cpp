#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//Este codigo solo es de expliacion, no existiran cambios visibles en la ventana si se ejecuta.
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

    //Manejamos la memoria de los vertices via un Vertex Buffer Object (VBO), que permite almacenar una gran cantidad de vertices en la memoria de la GPU.
    //La ventaja de estos buffers, es que nos permiten grandes cantidades de datos a la GPU, y mantenerlos ahi si existe suficiente memoria, sin tener que enviar datos de los vertices individualmente.
    //Una vez los datos están en la GPU, el vertex shader tiene  acceso casi instantaneo  a los vértices, haciendolo extremadamente rápido.
    unsigned int VBO;
    glGenBuffers(1, &VBO); //Generamos un buffer para los vertices

    //OpenGL tiene muchos tipos de buffers, y el tipo de buffer del VBO es GL_ARRAY_BUFFER. OpenGL nos permite enlazar varios buffers a la vez, en tanto tengamos diferentes tipos de buffers.
    //Podemos enlazar el buffer creado con la funcion glBindBuffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //A partir de este punto, todas las llamadas que hagamos al buffer GL_ARRAY_BUFFER, serán utilizadas para configurar al buffer actualmente enlazado, el cual es VBO.
    //Entonces podemos hacer una llamada a la función glBufferData que copia los datos de vertices previamente definidos a la memoria del Buffer.

    //glBufferData es una función que se encarga de copiar datos definidos por el usuario hacia el buffer actualmente enlazado.
    glBufferData(
        //El primer argumento es el tipo de buffer al que queremos copiar los datos: el VBO enlazado al GL_ARRAY_BUFFER. 
        GL_ARRAY_BUFFER, 
        //El segundo argumento es el tamaño de los datos en bytes.
        sizeof(vertices), 
        //El tercer argumento son los datos que vamos a enviar.
        vertices, 
        //El cuarto argumento especifica como queremos que la GPU maneje los datos. Puede tener 3 formas:
        // - GL_STREAM_DRAW: los datos son configurados una vez y usados por la GPU como maximo unas cuantas veces.
        // - GL_STATIC_DRAW: los datos son configurados una vez y usados muchas veces.
        // - GL_DYNAMIC_DRAW: los datos cambian muchas veces y son usados muchas veces.

        //Como los datos del triangulo no cambian, se usan muchas veces y se mantienen igual por cada llamada del renderizador, es mejor utilizar GL_STATIC_DRAW.
        GL_STATIC_DRAW
    );

    /*Mas contenido en el codigo con etiqueta 4.3*/

    // Ciclo de renderizado
    while(!glfwWindowShouldClose(window)){

        // Entrada de Usuario
        processInput(window);

        //comandos de Renderizado aquí
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

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