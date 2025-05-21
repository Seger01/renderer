/**point
 * @file Point.h
 * @brief This file contains the definition of the Point struct.
 */
#pragma once

namespace SML
{

class SML_Point
{
public:
    SML_Point() : x(0), y(0) {}

    SML_Point(int x = 0, int y = 0) : x(x), y(y) {}

    SML_Point(const SML_Point& other) : x(other.x), y(other.y) {}

    SML_Point& operator=(const SML_Point& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    int x;
    int y;
};

} // namespace SML
