#pragma once

#include <stdint.h>

#include "NormColor.h"

namespace SML
{

class Color
{
public:
    Color() : r(255), g(255), b(255), a(255) {}

    Color(unsigned int r, unsigned int g, unsigned int b) : r(r), g(g), b(b), a(255) {}

    Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a) : r(r), g(g), b(b), a(a) {}

    NormColor normalize() const { return NormColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f); }

    uint8_t r, g, b, a;
};

} // namespace SML
