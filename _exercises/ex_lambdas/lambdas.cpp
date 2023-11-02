#include <algorithm>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
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
    vector<int> data = {1, 6, 3, 5, 8, 9, 13, 12, 10, 45};

    SECTION("count even numbers")
    {
        auto evens_count = std::count_if(data.begin(), data.end(), [](int n) { return n % 2 == 0; });

        REQUIRE(evens_count == 4);
    }

    SECTION("copy evens to vector")
    {
        vector<int> evens;

        // std::for_each(data.begin(), data.end(), [&evens](int n) { if( n % 2 == 0) evens.push_back(n); });

        std::copy_if(data.begin(), data.end(), std::back_inserter(evens), [](int n) { return n % 2 == 0; });

        REQUIRE_THAT(evens, Catch::Matchers::Equals(vector<int>{6, 8, 12, 10}));
    }

    SECTION("create container with squares")
    {
        SECTION("ver_1")
        {
            vector<int> squares(data.size());
            std::transform(data.begin(), data.end(), squares.begin(), [](int n) { return n * n; });

            REQUIRE_THAT(squares, Catch::Matchers::Equals(vector<int>{1, 36, 9, 25, 64, 81, 169, 144, 100, 2025}));
        }

        SECTION("ver_2")
        {
            vector<int> squares;
            std::transform(data.begin(), data.end(), std::back_inserter(squares), [](int n) { return n * n; });

            REQUIRE_THAT(squares, Catch::Matchers::Equals(vector<int>{1, 36, 9, 25, 64, 81, 169, 144, 100, 2025}));
        }
    }

    SECTION("calculate average")
    {
        auto sum = 0.0;
        double avg{};

        avg = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
        REQUIRE(avg == Catch::Approx(11.2));

        SECTION("find first greater than avg")
        {
            auto pos = std::find_if(data.begin(), data.end(), [avg](int n) { return n > avg; });
            CHECK(*pos == 13);
        }
    }
}
