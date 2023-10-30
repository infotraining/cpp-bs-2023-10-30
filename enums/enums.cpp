#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

enum DayOfWeek : uint8_t { Mon = 1, Tue, Wed, Thd, Fri, Sat, Sun };

TEST_CASE("enums")
{
	static_assert(sizeof(DayOfWeek) == 1);

	DayOfWeek day = Mon;

	int day_index = day; // implicit conversion to int
	CHECK(day_index == 1);

	day = static_cast<DayOfWeek>(7);
	CHECK(day == Sun);
}

enum class Month { Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };

TEST_CASE("scoped enumerations")
{
	Month month = Month::Oct;

	int month_index = static_cast<int>(month);
	CHECK(month_index == 10);

	month = static_cast<Month>(11);
}