#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

TEST_CASE("lambda exercise")
{
    using namespace Catch::Matchers;

    vector<int> data = {1, 6, 3, 5, 8, 9, 13, 12, 10, 45};

    SECTION("count even numbers")
    {
        auto evens_count = 0;

        // TODO - count_if
        
        REQUIRE(evens_count == 4);
    }

    SECTION("copy evens to vector")
    {
        vector<int> evens;
        
        // TODO - for_each

        REQUIRE_THAT(evens, Equals(vector<int>{6, 8, 12, 10}));
    }

    SECTION("create container with squares")
    {
        vector<int> squares;
        
        // TODO - transform

        REQUIRE_THAT(squares, Equals(vector<int>{1, 36, 9, 25, 64, 81, 169, 144, 100, 2025}));
    }

    SECTION("calculate average")
    {
        auto sum = 0.0;
        double avg;
            
        // TODO - accumulate
-
        REQUIRE_THAT(avg,  WithinAbs(11.2, 0.001));

        SECTION("find first greater than avg")
        {
            // TODO
        }

    }
}
