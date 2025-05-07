#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

struct Point {
    int x;
    int y;
};

// uniform Point screenSize;
// uniform Point objectPosition;
// uniform Point objectSize;
// uniform Point objectCenter;

uniform mat4 model;
uniform mat4 projection;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * model * vec4(aPos.xy, 0.0, 1.0);
}

// void main()
// {
//     float x = aPos.x;
//     float y = aPos.y;
//
//     x = -1.0 + ((float(objectPosition.x) / float(screenSize.x)) * 2.0);
//     y = 1.0 - (float(objectPosition.y) / float(screenSize.y / 2.0));
//
//     x += ((float(objectSize.x) * (aPos.x + 1.0)) / float(screenSize.x)) * 1.0;
//     y += ((float(objectSize.y) * (aPos.y - 1.0)) / float(screenSize.y)) * 1.0;
//
//     gl_Position = vec4(x, y, aPos.z, 1.0);
//     TexCoords = aTexCoords;
// }
