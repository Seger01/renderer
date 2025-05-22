R"(
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
    float u = TexCoords.x;
    float v = TexCoords.y;
    if (flipX == 1) u = 1.0 - u;
    if (flipY == 1) v = 1.0 - v;

    float textureCoordX = (source.z * u) + source.x;
    float textureCoordY = (source.w * v) + source.y;

    FragColor = texture(texture1, vec2(textureCoordX, textureCoordY)) * colorFilter;
}
)"
