#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

struct Point {
    int x;
    int y;
};

uniform mat4 model;
uniform mat4 projection;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * model * vec4(aPos.xy, 0.0, 1.0);
}
