#version 330

in vec2 TexCoords;
in vec3 ourColor;
out vec4 FragColor;
uniform sampler2D texture1;
uniform float timeValue;

void main()
{
    FragColor = texture(texture1, vec2(TexCoords.x, TexCoords.y)) * vec4(ourColor, 1.0);
}