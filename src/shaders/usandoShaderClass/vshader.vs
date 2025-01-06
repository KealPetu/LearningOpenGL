#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
uniform float wValue;
uniform float aspect;
out vec4 vertexColor;
void main()
{
   gl_Position = vec4(aPos.x/aspect, aPos.y, 0.0f, wValue);
   vertexColor = vec4(aColor, 1.0f);
}