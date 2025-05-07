#version 330 core

uniform sampler2D texture1;

in vec2 TexCoords;

out vec4 FragColor;

uniform vec4 source;
uniform vec4 colorFilter;

uniform int flipX;
uniform int flipY;

void main()
{
    FragColor = texture(texture1, vec2((TexCoords.x * flipX * source.z) + source.x, (TexCoords.y * flipY * source.w) + source.y)) * colorFilter;
}
