#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float timeValue;

void main()
{
    float factor = sin(timeValue) / 2.f + 0.5f;
    FragColor = mix(texture(ourTexture, TexCoord), vec4(ourColor, 1.0), factor);
}