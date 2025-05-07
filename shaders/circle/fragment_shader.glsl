#version 330 core

in vec2 ndcPos;

out vec4 FragColor;

uniform vec4 color;
uniform float innerRadius;

void main()
{
    float distance = length(ndcPos);

    if (distance > 0.5 || distance < innerRadius)
        discard;

    FragColor = vec4(color);
}
