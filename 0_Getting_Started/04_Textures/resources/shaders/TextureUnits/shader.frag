#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float timeValue;

void main()
{
    float factor = sin(timeValue) / 2.f + 0.5f;
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), factor);
}