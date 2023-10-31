#include "vector2d.hpp"

namespace MyMath
{
    Vector2D Vector2D::unit_x_(1.0, 0.0);
    Vector2D Vector2D::unit_y_(0.0, 1.0);

    Vector2D::Vector2D(double x, double y) 
        : x_(x), y_(y)
    {
    }

    double Vector2D::length() const
    {
        return sqrt(pow(x_, 2) + pow(y_, 2));
    }

} // namespace MyMath