#include "NormColor.h"

#include "Color.h"

namespace SML
{

NormColor::NormColor() : r(0), g(0), b(0), a(0) {}

NormColor::NormColor(float r, float g, float b) : r(r), g(g), b(b), a(1) {}

NormColor::NormColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

Color NormColor::denormalize() const { return Color(r * 255, g * 255, b * 255, a * 255); }

} // namespace SML
