#include <catch2/catch_test_macros.hpp>
#include <iostream>

namespace Operators
{
    inline namespace OutsideClass
    {
        struct Number
        {
            int value;

            Number(int v)
                : value(v)
            { }

            Number& operator++() // pre-incrementation
            {
                ++value;
                return *this;
            }

            Number operator++(int) // post-incrementation
            {
                Number old{*this};
                ++value;
                return old;
            }

            bool operator==(const Number& n) const = default; // C++20

            friend std::ostream& operator<<(std::ostream& out, const Number& n)
            {
                return out << "Number{" << n.value << "}";
            }
        };

        Number operator+(Number a, Number b)
        {
            return Number{a.value + b.value};
        }

        Number operator-(Number a, Number b)
        {
            return Number{a.value - b.value};
        }

        Number operator-(Number n)
        {
            return Number{-n.value};
        }

        // bool operator==(Number a, Number b)
        // {
        //     return a.value == b.value;
        // }

        // bool operator!=(Number a, Number b)
        // {
        //     return !(a == b);
        // }

    }; // namespace OutsideClass

    namespace InsideClass
    {
        struct Number
        {
            int value;

            Number(int v)
                : value(v)
            { }

            Number operator+(Number other) const
            {
                return Number{value + other.value};
            }

            Number operator-(Number other) const
            {
                return Number{value - other.value};
            }

            Number operator-() const
            {
                return -value;
            }

            bool operator==(Number other) const
            {
                return value == other.value;
            }

            bool operator!=(Number other) const
            {
                return value == other.value;
            }
        };
    } // namespace InsideClass
} // namespace Operators

TEST_CASE("overloading operators")
{
    using namespace Operators;

    Number n1{5};

    CHECK(n1 + Number{7} == Number{12});

    CHECK(n1 - Number{1} == Number{4}); // binary -

    CHECK(-n1 == Number{-5}); // unary -

    CHECK(n1 - 5 == 0);

    CHECK(5 + n1 == Number{10});

    CHECK(InsideClass::Number{6} + 2 == InsideClass::Number{8});
}

TEST_CASE("operators ++ and --")
{
    using namespace Operators;

    Number n{10};

    SECTION("pre-incrementation")
    {
        CHECK(++n == Number{11});
    }

    SECTION("post-incrementation")
    {
        CHECK(n++ == Number{10});
        CHECK(n == Number{11});
    }
}

TEST_CASE("operator << - streams")
{
    using namespace Operators;

    Number n{10};

    std::cout << n << "\n";
}

namespace A
{
    namespace B
    {
        namespace C
        {
            void foo()
            { }
        } // namespace C
    }     // namespace B
} // namespace A

TEST_CASE("nested namespaces")
{
    A::B::C::foo();

    using namespace A::B;

    C::foo();
}