#pragma once

#include <vector>

#include "Shape.h"

namespace SML
{

class TexturedQuad : public Shape
{
public:
    TexturedQuad();
    virtual ~TexturedQuad() = default;

private:
    // define vertices for a triangle
    std::vector<float> vertices = {
        // positions // texture coords
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right

        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f  // bottom right
    };
};

} // namespace SML
