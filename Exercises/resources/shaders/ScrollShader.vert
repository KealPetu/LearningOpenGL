#version 330

layout (Location = 0) in vec2 vertexPosition;
layout (Location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(vertexPosition, 0.0, 1.0);
    TexCoords = aTexCoords;
}