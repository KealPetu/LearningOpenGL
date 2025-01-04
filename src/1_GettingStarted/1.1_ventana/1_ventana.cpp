#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int argc, char *argv[])
{
    glfwInit(); //Funcion Para inicializar la libreria de GLFW

    glfwWindowHint( //Funcion que se puede utilizar para configurar una caracteristica de la ventana
        GLFW_CONTEXT_VERSION_MAJOR, //La caracteristica que queremos modificar es la Version de OpenGL mayor que vamos a utilizar
        3   //En este caso Queremos utilizar OpenGL 3.3, por los que damos el valor entero de 3 a la configuracion
        );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR, //La version de OpenGL menor
        3   //Open GL 3.3
        );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE, //EL perfil de OpenGL que vamos a utlizar al crear una ventana
        GLFW_OPENGL_CORE_PROFILE    //Solo vamos a utilizar el Perfil 'Core' de OpenGL
                                    //Lo que significa que no vamos a tener acceso a funciones depreciadas
        );

    // Ahora, creamos la el objeto de la Ventana
    // El objeto contiene todos los datos del ventanaje, que son requeridos para la mayor parte de las funciones de GLFW
    GLFWwindow* window = glfwCreateWindow(
        800,    //Ancho de la ventana en pixeles
        600,    //Alto de la ventana en pixeles
        "LearnOpenGL",  //Nombre de la ventana
        NULL,   //El monitor a usar para la ventana, NULL si se va a usar el monitor primario
        NULL);  //La ventana con la que va a compartir recursos, NULL si es una nueva ventana

    if (window == NULL) //SI no existe la ventana
    {
        std::cout << "Failed to create GLFW window" << std::endl;   //Imprime el error de la creacion de la ventana
        glfwTerminate();    //Termina el programa
        return -1;  //Devuelve -1 como error
    }

    glfwMakeContextCurrent(window); //Funcion utilizada para intercalar diferentes contextos de OpenGL
                                    //permitiendo utilizar diferentes ventanas o configuraciones de renderizado
    //Todo lo de Aqui abajo se renderizara en "window"
    //glfwMakeContextCurrent(window2)
    //Todo lo de Aqui abajo se renderizara en "window2"

    //Antes de ejecutar cualquier funcion de OpenGL, debemos incializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Inicializa la API de OpenGL usando glfw como el loader
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    //Definimos la region en la ventana en la cual se va a renderizar.
    glViewport(
        0,      //La ubicacion x desde donde se genera el ViewPort: 0 = Izquierda en la ventana
        0,      //La ubicacion y desde donde se genera el ViewPort: 0 = Abajo en la vente
        800,    //Tamaño de ancho del ViewPort en Pixeles
        600);   //Tamaño en altura del ViewPort en Pixeles

    //Le decimos a GLFW que queremos utilizar esta funcion en cada ventana al registrarla:
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1); // Habilitamos Sincronización vertical

    //Ahora, no queremos que la aplicacion dibuje e inmediatamente se cierre, queremos que la aplicacion siga
    //dibujando imagenes y maneje entradas del usuario hasta que se diga al programa de foma explicita que cierre
    //Por esta razón, creamos el ciclo de renderizado o 'render loop':
    
    while(!glfwWindowShouldClose(window))   //Verifica al inicio de cada iteración si GLFW ha sido instruido en cerrarse.
                                            //Si ese es el caso, la funcion devuelve 'true' y el ciclo finaliza
    {
        glfwSwapBuffers(window);    //Verifica si algun evento fue activado (como teclado o mouse), actualiza el estado de la ventana
                                    //y llama las funciones correspondientes (que pueden ser registradas por medio de callbacks)
        glfwPollEvents();   //Cambiara el color del Buffer (Un largo buffer 2d que contiene los valores de colores de cada pixel)
                            //que es utilizado para renderizar y mostrarlo como salida en la pantalla
    }

    glfwTerminate();    //Tan pronto como salgamos del ciclo de renderizado, debemos eliminar/limpiar todos los recursos de     
                        //GLFW que hemos asignado 
    return 0;
}


//Cada vez que el usuario cambie el tamaño de la ventana, el ViewPort debería cambiar también.
//Registramos una función 'callback' en la ventana que es llamada cada vez que la ventana cambia de dimensiones.
//La funcion frambuffer toma un GLFWwindow como primer argumento y 2 enteros indicando las nuevas dimensiones de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
