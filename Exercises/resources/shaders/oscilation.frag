#version 330
out vec4 FragColor;
uniform float time;
void main()
{
    float factor = sin(time) / 2.f + 0.5f;
    vec3 colorA = vec3(1.0f, 0.0f, 0.0f);
    vec3 colorB = vec3(0.0f, 0.0f, 1.0f);
    vec3 color = mix(colorA, colorB, factor);
    FragColor = vec4(color, 1.0f);
}