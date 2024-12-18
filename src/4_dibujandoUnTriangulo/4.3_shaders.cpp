#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//Este codigo solo es de expliacion, no existiran cambios visibles en la ventana si se ejecuta.
//GLSL luce muy similar a C
const char *vertexShaderSource = 
    //Cada shader empieza con la declaración de su versión y el perfil que vamos a utilizar
    "#version 330 core\n"
    //Declaramos los atributos de entrada del vertice en el vertex shader con la palabra clave 'in'.
    //Por ahora, solo nos interesan los datos de posicion, asi que solo necesitamos un atributo de vertice.
    //Debido a que cada vertice son coordenadas 3D, creamos una variable de entrada vec3 con el nombre aPos.
    //Tambien especificamos la ubicacion de la variable de entrada a través de layout, luego veremos poruqe necesitamos esa ubicacion.

    //En GLSL, los vectores tienen un tamano maximo de 4, vec.x, vec.y, vec.z y vec.w (division de perspectiva).
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
        //Para configurar la salida del 'vertex shader', debemos asignar los datos de posicion a la variable predefinida gl_Position
        //el cual es un vec 4 detras de escenas.
        //al final de la funcion 'main', cual sea el valor del gl_Position sera utilizado como salida del 'vertex shader'.

        //Debido a que nuestra etrada es solamente un 'vec3', debemos castearlo a 'vec4', Lo hacemos ingresando los valores del vec3 individualmente,
        //y asignando el componente 'w' a 1.0f.
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    //Los colores son representados como un vector de 4 valores: rojo, verde, azul y alpha (opacidad), comunmente abreviados como RGBA.
const char *orangefFragmentShaderSource = 
    "#version 330 core\n"
    //El 'fragment shader' solamente requiere de una variable de salida, y la cual es un vector de tamano de 4. 
    //Podemos declarar la variable de salida con la palabra clave 'out' y la cual llamaremos 'FragColor'
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        //Luego, debemos simplemente asignar los calores de color al vector en cuestion.
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

    //Ahora, queremos crear los vertex y fragment shaders para procesar los datos

    //Vertex Shader
    //OpenGL moderno requiere que construyamos un vertex y fragment shader si queremos hacer algun tipo de renderizado.
    //Lo primero que necesitamos hacer es escribir el vertex shader en el lengueje de GLSL y compilarlo para utiliarlo en nuestra aplicación.

    //(Revisar el principio del programa).

    //Para que OpenGL pueda usar el shader, este debe compilarse de forma dinamica en el tiempo de ejecucion desde el codigo fuente. 

    //Primero necesitamos crear el objeto 'shader', referenciado por un ID.
    unsigned int vertexShader;
    //Entonces almacenamos el 'vertex shader' como un 'unsigned int', creado con la funcion glCreateShader. Y como estamos creando un 'vertex shader', le pasamos el argumento 'GL_VERTEX_SHADER'.
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Ahora conectmos el codigo fuente del Shader con el objeto respectivo.
    glShaderSource(
        vertexShader,       //toma el objeto 'shader' que se va acompilar
        1,                  //Especifica cuantos strings pasamos como codigo fuente, el cual es solo 1              
        &vertexShaderSource,//El codigo fuente del 'vertex shader' 
        NULL                //Un arreglo opcional de valores GLint, que especifican el tamano de cada string en el arreglo de 'String'.
    );

    //Compilamos el shader
    glCompileShader(vertexShader);

    //Ahora comporbamos que la compilacion haya sido exitosa, y si no lo fue, verificar que errores se encontraron.

    //indicador del exito de compilacion del shader
    int success;
    //contenedor para almacenar el mensaje de error
    char infoLog[512];
    //verificamos que la compilacion fue exitosa con glGetShaderiv.
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    //Si la compilacion falla, deberemos impirmir el error con glGetShaderInfoLog
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Fragment Shader
    //El segundo y ultimo shader a crear para renderizar un triangulo.
    //Se encarga de calcular la salida de colores para los pixeles. El fragment shader siempre mostrara un color naranja.

    //(Revisar el principio del programa)

    //El proceso de Compilacion del 'fragment shader' es muy similar al del 'vector shader'

    unsigned int fragmentShader;
    //Esta vez, definimos el tipo de shader que vamos a utilizar a: GL_FRAGMENT_SHADER
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &orangefFragmentShaderSource, NULL);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Con ambos shaders Compilados correctamente, lo unico que queda por hacer es enlazar ambos shaders en un 'shader program' que luego vamos a utilizar para renderizar

    //Shader Program
    //Es la version final de los multiples shaders combinados. Para utilizar los hsaders, es necesario enlazarlos en un objeto 'Shader Program', y activarlo cuando se renderizen los objetos.

    //Creamos el ID para referenciar al programa
    unsigned int shaderProgram;
    //Crea el programa y devuelve el ID de referencia del mismo.
    shaderProgram = glCreateProgram();

    //Ahora debemos conectar los shaders previamente creados, y enlazarlos con glLinkProgram.
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //Luego de conectar los shaders, podemos enlazarlos con glLinkProgram. Esto genera un programa de shaders ejecutable en la GPU.
    glLinkProgram(shaderProgram);

    //Comprobamos que el enlace fue exitoso, y si no lo fue, verificamos que errores se encontraron. Pero en lugar de usar glGetShaderiv y glGetShaderInfoLog, utilizamos:
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //El resultado es un obeto Programa wur podemos activar con la funcion glUseProgram, y enviando como argumento al programa:
    glUseProgram(shaderProgram);

    //Cada shader o renderizado despues de esta linea utilizara este programa objeto (y sus shaders)

    //Y no nos olvidemos de eliminar los objetos shader que hemos enlazado en el programa objeto, pues ya no los necesitamos.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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