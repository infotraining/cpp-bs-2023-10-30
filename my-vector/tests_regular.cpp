#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

TEST_CASE("regular types")
{
    SECTION("int")
    {
        int a{};       // int a = 0;
        int b = a;     // copyable
        CHECK(a == b); // equality comparable
    }

    SECTION("string")
    {
        std::string str1;
        str1 = "abc";

        std::string str2 = str1;
        CHECK(str1 == str2);
    }

    SECTION("vector")
    {
        std::vector<int> vec1;
        vec1 = {1, 2, 3};

        std::vector<int> vec2 = vec1;
        CHECK(vec1 == vec2);
    }
}

std::string read_line()
{
	std::string line = "some line";
	return line;
}

TEST_CASE("move semantics")
{
    std::vector<int> vec = {1, 2, 3, 4, 5};

    SECTION("copy")
    {
        std::vector<int> backup = vec; // cc

        CHECK(vec == std::vector{1, 2, 3, 4, 5});
        CHECK(backup == std::vector{1, 2, 3, 4, 5});
    }

	SECTION("move")
    {
        std::vector<int> target = std::move(vec); // move

        CHECK(vec.size() == 0);
        CHECK(target == std::vector{1, 2, 3, 4, 5});
    }

	SECTION("life")
	{
		std::vector<std::string> words;

		std::string line1 = "line1";
		std::string line2 = "line2";

		words.push_back(line1); // cc
		words.push_back(std::move(line2)); //mv
		words.push_back(read_line()); // implicit move
	}
}