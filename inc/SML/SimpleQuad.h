#pragma once

#include <vector>

#include "Shape.h"

namespace SML
{

class SimpleQuad : public Shape
{
public:
    SimpleQuad();
    virtual ~SimpleQuad() = default;

private:
    // define vertices for a triangle
    std::vector<float> vertices = {
        // positions // texture coords
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
        -1.0f, 1.0f,  0.0f, 0.0f, 1.0f, // top left
        1.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top right

        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
        1.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top right
        1.0f,  -1.0f, 0.0f, 1.0f, 0.0f  // bottom right
    };
};

} // namespace SML
