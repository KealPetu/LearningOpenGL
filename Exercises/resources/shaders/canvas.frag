#version 330
out vec4 FragColor;
uniform vec2 resolution;
void main()
{
    FragColor = vec4(gl_FragCoord.x / resolution.x, gl_FragCoord.y / resolution.y, .8f, 1.0f);
}