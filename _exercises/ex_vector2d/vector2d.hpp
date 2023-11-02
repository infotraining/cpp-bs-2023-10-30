#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <format>

namespace MyMath
{
    class Vector2D
    {
        double x_;
        double y_;

        static Vector2D unit_x_;
        static Vector2D unit_y_;

    public:
        Vector2D(double x = 0.0, double y = 0.0);

        double x() const
        {
            return x_;
        }

        double y() const
        {
            return y_;
        }

        double length() const;

        static const Vector2D& unit_x()
        {
            return unit_x_;
        }

        static const Vector2D& unit_y()
        {
            return unit_y_;
        }

        // bool operator==(const Vector2D& other) const
        // {
        //     return x_ == other.x_ && y_ == other.y_;
        // }

        // bool operator!=(const Vector2D& other) const
        // {
        //     return !(*this == other);
        // }

        bool operator==(const Vector2D& other) const = default;

        Vector2D operator-() const
        {
            return Vector2D{-x_, -y_};
        }

        Vector2D operator-(const Vector2D& other) const
        {
            return Vector2D{x_ - other.x_, y_ - other.y_};
        }

        friend std::ostream& operator<<(std::ostream& out, const Vector2D& v)
        {
            //return out << "Vector2D(" << v.x() << ", " << v.y() << ")";
            return out << std::format("Vector2D({:.1f}, {:.1f})", v.x(), v.y());
        }
    };

    inline Vector2D operator*(double a, const Vector2D& v)
    {
        return Vector2D(v.x() * a, v.y() * a);
    }

    inline Vector2D operator*(const Vector2D& v, double a)
    {
        return Vector2D(v.x() * a, v.y() * a);
    }

    inline double operator*(const Vector2D& va, const Vector2D& vb)
    {
        return va.x() * vb.x() + va.y() * vb.y();
    }

} // namespace MyMath

#endif // VECTOR2D_HPP