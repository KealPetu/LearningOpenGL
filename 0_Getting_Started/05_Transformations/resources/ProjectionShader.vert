#version 330 core
layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 ourColor;

uniform mat4 transform;
uniform mat4 projection; // <-- NUEVA MATRIZ

void main()
{
    // El orden IMPORTA: projection * transform * vertexPosition
    gl_Position = projection * transform * vec4(vertexPosition, 0.0, 1.0);

    TexCoords = aTexCoords;
    ourColor = aColor;
}