#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform float aspect;
uniform float wValue;
uniform float xValue;
uniform float yValue;

void main()
{
    gl_Position = vec4((aPos.x + xValue)/aspect, aPos.y + yValue, 0.0, wValue);
    ourColor = aColor;
    TexCoord = aTexCoord;
}