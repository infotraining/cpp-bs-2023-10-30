#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace Solution
{
    namespace ver_1
    {
        bool is_palindrome(const std::string& text)
        {
            std::string reversed_text(text.rbegin(), text.rend());

            return text == reversed_text;
        }
    } // namespace ver_1

	namespace ver_2
	{
		bool is_palindrome(const std::string& text)
        {
            return std::equal(text.begin(), text.begin() + text.size() / 2, text.rbegin());
        }
	}
} // namespace Solution

TEST_CASE("palindromes")
{
    // uncomment lines below
    //
	using namespace Solution::ver_1;

    SECTION("is palindrome")
    {
        SECTION("empty string")
        {
            REQUIRE(is_palindrome(""));
        }

        SECTION("short")
        {
            std::string str = "potop";
            REQUIRE(is_palindrome(str));
        }

        SECTION("long")
        {
            std::string str = "lapalzakranakanarkazlapal";
            REQUIRE(is_palindrome(str));
        }
    }

    SECTION("is not palindrome")
    {
        std::string str = "mars";

        REQUIRE_FALSE(is_palindrome(str));
    }
}