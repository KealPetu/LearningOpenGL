#version 330

layout (Location = 0) in vec2 vertexPosition;
layout (Location = 1) in vec3 aColor;
layout (Location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 ourColor;

void main()
{
    gl_Position = vec4(vertexPosition, 0.0, 1.0);
    TexCoords = aTexCoords;
    ourColor = aColor;
}