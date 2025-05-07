#version 330 core

uniform sampler2D glyph;

in vec2 TexCoords;

out vec4 FragColor;

uniform vec4 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(glyph, TexCoords).r);
    FragColor = textColor * sampled;
}
