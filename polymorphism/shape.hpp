#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <memory>

#include "point.hpp"

namespace Drawing
{
    // abstract class - interface
    class Shape
    {
    public:
        virtual ~Shape() = default;
        virtual void move(int dx, int dy) = 0;
        virtual void draw() const = 0;
    };

    class ShapeBase : public Shape // class abstract
    {
        Point coord_;

    public:
        ShapeBase(int x = 0, int y = 0)
            : coord_{x, y}
        {
        }

        ShapeBase(Point pt)
            : coord_{pt}
        {
        }

        void move(int dx, int dy) override
        {
            coord_.translate(dx, dy);
        }

        Point coord() const
        {
            return coord_;
        }
    };

    class Rectangle : public ShapeBase // is-a-kind-of
    {
        uint32_t width_, height_;

    public:
        Rectangle(int x = 0, int y = 0, uint32_t w = 0, uint32_t h = 0)
            : ShapeBase(x, y) // base-class constructor
            , width_(w)
            , height_(h)
        { }

        Rectangle(Point pt, uint32_t w, uint32_t h)
            : ShapeBase(pt)
            , width_(w)
            , height_(h)
        { }

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

        void draw() const override
        {
            std::cout << "Drawing Rectangle at " << coord()
                      << " with width: " << width_
                      << " with height: " << height_ << "\n";
        }
    };

    class Circle : public ShapeBase
    {
        uint32_t radius_;

    public:
        Circle(int x = 0, int y = 0, uint32_t r = 0)
            : ShapeBase(x, y)
            , radius_(r)
        { }

        Circle(Point pt, uint32_t r)
            : ShapeBase(pt)
            , radius_(r)
        { }

        void draw() const override
        {
            std::cout << "Drawing Circle at " << coord()
                      << " with radius: " << radius_ << "\n";
        }

        uint32_t radius() const
        {
            return radius_;
        }

        void set_radius(uint32_t r)
        {
            radius_ = r;
        }
    };

    class Line : public ShapeBase
    {
        Point end_coord_;

    public:
        Line(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)
            : ShapeBase(x1, y1)
            , end_coord_{x2, y2}
        { }

        Line(Point start, Point end)
            : Line(start.x, start.y, end.x, end.y) // delegating constructors - C++11
        {}

        void draw() const override
        {
            std::cout << "Drawing Line from " << coord() << " to " << end_coord_ << "\n";
        }

        void move(int dx, int dy) override
        {
            ShapeBase::move(dx, dy); // call of move from base class
            end_coord_.translate(dx, dy);
        }
    };

    class GraphicsDocument
    {
        std::vector<std::unique_ptr<Shape>> shapes_;
    public:
        GraphicsDocument() = default;

        void add_shape(std::unique_ptr<Shape> shp)
        {
            shapes_.push_back(std::move(shp));
        }

        void render() const
        {
            for(const auto& shp : shapes_)
                shp->draw();
        }
    };

} // namespace Drawing

#endif // SHAPE_HPP