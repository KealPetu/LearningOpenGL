#version 330

out vec4 FragColor;
in vec2 ourPos;
uniform float timeValue;

void main()
{
    float circleRadius = 0.5 + 0.5 * sin(timeValue);
    float myDistance = distance(ourPos, vec2(0.0, 0.0));
    float myStep = step(circleRadius, myDistance);
    FragColor = vec4(myDistance, myStep, myStep, 1.0);
}