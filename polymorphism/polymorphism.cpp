#include "shape.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

TEST_CASE("polymorphism")
{
    Drawing::Shape shp{10, 20};
    shp.draw();
    shp.move(12, 55);
    shp.draw();

    Drawing::Rectangle rect{100, 200, 30, 80};
    rect.draw();
    rect.set_height(500);
    rect.move(10, 44);
    rect.draw();

    Drawing::Circle crc{100, 200, 50};
    crc.draw();
    crc.set_radius(100);
    crc.move(100, 300);
    crc.draw();
}