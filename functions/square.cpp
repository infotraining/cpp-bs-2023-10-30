#include "square.hpp"

#include <cmath>
#include <iostream>

double MyMath::pi = 3.1415; // definition

int MyMath::square(int x) // definition
{
    return x * x;
}

namespace MyMath
{
    float square_root(float x)
    {
        std::cout << "MyMath::sqrt(" << x << ")\n";
        return std::sqrt(x);
    }
} // namespace MyMath

namespace OtherMath
{
    float square_root(float x)
    {
        std::cout << "OtherMath::sqrt(" << x << ")\n";
        return std::sqrt(x);
    }
} // namespace MyMath