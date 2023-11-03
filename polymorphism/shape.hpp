#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "point.hpp"

namespace Drawing
{
    class Shape
    {
        Point coord_;

    public:
        Shape(int x = 0, int y = 0)
            : coord_{x, y}
        {
        }

        Shape(Point pt)
            : coord_{pt}
        {
        }

        void move(int dx, int dy)
        {
            coord_.translate(dx, dy);
        }

        void draw() const;

        Point coord() const
        {
            return coord_;
        }
    };

    class Rectangle : public Shape // is-a-kind-of
    {
        uint32_t width_, height_;
    public:
        Rectangle(int x = 0, int y = 0, uint32_t w = 0, uint32_t h = 0)
            : Shape(x, y) // base-class constructor
            , width_(w)
            , height_(h)
        {}

        Rectangle(Point pt, uint32_t w, uint32_t h)
            : Shape(pt)
            , width_(w)
            , height_(h)
        {}

        uint32_t width() const
        {
            return width_;
        }

        void set_width(uint32_t w)
        {
            width_ = w;
        }

        uint32_t height() const
        {
            return height_;
        }

        void set_height(uint32_t h)
        {
            height_ = h;
        }

        void draw() const 
        {
            std::cout << "Drawing Rectangle at " << coord() 
                      << " with width: " << width_
                      << " with height: " << height_ << "\n";
        }
    };

} // namespace Drawing

#endif // SHAPE_HPP