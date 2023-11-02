#include "my_vector.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace Training;

TEST_CASE("vector - indexing")
{
    const Vector vec(5); // acquire

    for (size_t i = 0; i < vec.size(); ++i)
        CHECK(vec[i] == 0);
} // vec.~Vector() - release

TEST_CASE("vector - init with {}")
{
    Vector vec = {1, 2, 3, 4, 5}; // std::initializer_list<int>

    CHECK(vec.size() == 5);
    // CHECK(vec[0] == 1);
    // CHECK(vec[1] == 2);
    // CHECK(vec[2] == 3);
    // CHECK(vec[3] == 4);
    // CHECK(vec[4] == 5);

    CHECK(vec == Vector{1, 2, 3, 4, 5});
}

TEST_CASE("vector - range-based for")
{
    const Vector vec = {1, 2, 3, 4, 5};

    for (const auto& item : vec)
        std::cout << item << " ";
    std::cout << "\n";
}

TEST_CASE("vector - push_back")
{
    Vector vec = {1, 2, 3, 4};

    vec.push_back(5);
    vec.push_back(6);

    CHECK(vec.size() == 7);
    CHECK(vec == Vector{1, 2, 3, 4, 5, 6, 7});
}
