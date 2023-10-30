#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std::literals;

TEST_CASE("integers")
{
    SECTION("raw types")
    {
        int a = -1;
        unsigned int b = 42;
        char c = 7;
        long long l = 1'000'000;
    }

    SECTION("aliases")
    {
        int32_t a = -1;
        uint32_t b = 42;
        int8_t c = 7;
        int64_t l = 1'000'000LL;
    }
}

TEST_CASE("floating points")
{
    float fl_pi = 3.14f;
    double pi = 3.14;
}

TEST_CASE("boolean values")
{
    bool flag = true;
    flag = false;

    CHECK(flag == false);
}

TEST_CASE("strings")
{
    SECTION("c-string")
    {
        const char* c_txt = "Text";
        const char* other_c_txt = "Text";
        CHECK(std::strcmp(c_txt, other_c_txt) == 0);

        auto a_txt = "Hello"; // const char*
    }

    SECTION("std::string")
    {
        std::string txt = "Text";
        std::string long_txt = txt + "!!!";

        CHECK(long_txt == "Text!!!");

        auto a_txt = "Hello"s; // std::string
    }

    SECTION("raw-string")
    {
        std::string path_1 = "c:\\nasz\\tekst";
        std::string path_2 = R"(c:\nasz\tekst)";

        CHECK(path_1 == path_2);
    }
}

TEST_CASE("vector")
{
    std::vector<int32_t> numbers = {1, 2, 3, 4, 5};

    CHECK(numbers.size() == 5);

    SECTION("classic for with index")
    {
        for (size_t i = 0; i < numbers.size(); ++i)
            std::cout << numbers[i] << " ";
        std::cout << "\n";
    }

    numbers.push_back(6);
    numbers.push_back(7);

    CHECK(numbers.size() == 7);

    SECTION("since C++11 - ranges-based for")
    {
        for (const auto& item : numbers)
            std::cout << item << " ";
        std::cout << "\n";
    }
}

TEST_CASE("const")
{
    const int cx = 10;
    //cx = 14;

    const std::vector<int> vec = {1, 2, 3};
    //vec.push_back(7);
}

TEST_CASE("pointer types")
{
    int x = 10;
    int* ptr_x = nullptr;
    CHECK(ptr_x == nullptr);
    ptr_x = &x;

    CHECK(*ptr_x == 10);

    SECTION("pointer to const")
    {
        const int* ptr_to_const_obj = &x;
        //*ptr_to_const_obj = 76;

        int y = 665;
        ptr_to_const_obj = &y; // OK
        //*ptr_to_const_obj = 99;
    }
    
    SECTION("const pointer")
    {
        int* const const_ptr = &x;
        *const_ptr = 665;

        int y = 665; 
        //const_ptr = &y; // ERROR
    }

    SECTION("const pointer to const")
    {
        const int* const const_ptr_to_const_obj = &x;

        //*const_ptr_to_const_obj = 665; // ERROR
        int y = 665; 
        //const_ptr_to_const_obj = &y; // ERROR
    }
}

TEST_CASE("reference types")
{
    int x = 10;

    int& ref_x = x;
    ref_x = 42;

    CHECK(x == 42);

    std::vector<int> vec = {1, 2, 3};

    std::vector<int>& ref_vec = vec;
    ref_vec.push_back(4);

    CHECK(vec == std::vector{1, 2, 3, 4});

    SECTION("const ref")
    {
        const int& const_ref_x = x;
        //const_ref_x = 665; // ERROR
    }
}

//typedef int& RefInt;
using RefInt = int&;