#version 330

in vec2 TexCoords;
out vec4 FragColor;
uniform sampler2D texture1;
uniform float timeValue;

void main()
{
    float scrollSpeed = 0.2; // Adjust this value to change the scrolling speed
    FragColor = texture(texture1, vec2(TexCoords.x + timeValue * scrollSpeed, TexCoords.y));
}