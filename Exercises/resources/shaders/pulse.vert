#version 330
layout (location = 0) in vec2 aPos;
uniform float time;
float scale;

void main()
{
    scale = sin(time)/4.f + 0.75f;
    gl_Position = vec4(aPos.x * scale, aPos.y * scale, 0.0, 1.0);
}