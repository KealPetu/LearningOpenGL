#version 330

in vec2 TexCoords;
in vec3 ourColor;
out vec4 FragColor;
uniform sampler2D texture1;
uniform float timeValue;

void main()
{
    float scrollSpeed = -0.2;
    FragColor = texture(texture1, vec2(TexCoords.x + timeValue * scrollSpeed, TexCoords.y)) * vec4(ourColor, 1.0);
}