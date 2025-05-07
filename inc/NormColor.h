#pragma once

namespace SML
{

class Color;

class NormColor
{
public:
    NormColor();

    NormColor(float r, float g, float b);

    NormColor(float r, float g, float b, float a);

    Color denormalize() const;

    float r, g, b, a;
};

} // namespace SML
