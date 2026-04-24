#version 330

layout (location = 0) in vec2 aPos;
out vec2 ourPos;
uniform float timeValue;

void main()
{
    float scale = sin(timeValue)/4.f + 0.75f;
    gl_Position = vec4(aPos.x * scale, aPos.y * scale, 0.0, 1.0);
    ourPos = aPos;
}