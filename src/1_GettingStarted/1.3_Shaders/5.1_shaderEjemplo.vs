//Shaders estan escritos en un lenguaje simmilar a C.

//Loos shaders siempre empiezan con la declaracion de una version seguida con la declaracion de variables de enetrada y salida, uniforms y la funcion main.
#version version_number

in type in_variable_name;
in type in_variable_name;

out type out_variable_name;
  
uniform type uniform_name;
  
void main()
{
  // process input(s) and do some weird graphics stuff
  ...
  // output processed stuff to output variable
  out_variable_name = weird_stuff_we_processed;
}