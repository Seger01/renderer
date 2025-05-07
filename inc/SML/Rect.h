/**
 * @file Rect.h
 * @brief Defines the Rect struct.
 */

#ifndef RECT_H
#define RECT_H

namespace SML
{

/**
 * @struct Rect
 * @brief Defines a rectangle.
 */
class Rect
{
public:
    Rect() = default;

    Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

    // Function to check if this triangle intersects with another triangle
    bool intersects(const Rect& other) const
    {
        return x < other.x + other.w && x + w > other.x && y < other.y + other.h && y + h > other.y;
    }

    // overload the == operator for Rect
    bool operator==(const Rect& other) const { return x == other.x && y == other.y && w == other.w && h == other.h; }

    int x = 0, y = 0;
    int w = 0, h = 0;
};

} // namespace SML

#endif
