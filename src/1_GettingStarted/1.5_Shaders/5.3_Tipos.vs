// vecn: vector por defecto de n flootantes.
// bvecn: un vector de n booleanos.
// ivecn: un vector de n enteros.
// uvecn: un vector de n enteros sin simbolos.
// dvecn: un vector de n compoonente doble.

//Swizziling
vec2 someVec;
vec4 differentVec = someVec.xyxx;
vec3 anotherVec = differentVec.zyw;
vec4 otherVec = someVec.xxxx + anotherVec.yxzy;

vec2 vect = vec2(0.5, 0.7);
vec4 result = vec4(vect, 0.0, 0.0);
vec4 otherResult = vec4(result.xyz, 1.0);