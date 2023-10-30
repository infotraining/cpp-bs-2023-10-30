#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "square.hpp"

using namespace std::literals;
using namespace MyMath;
using namespace std;

TEST_CASE("square")
{
	CHECK(square(10) == 100);
}

void value_passed_by_copy(int x)
{
	x = 665;

	std::cout << "param x: " << x << "\n";
}

TEST_CASE("passing by value")
{
	int x = 42;

	value_passed_by_copy(x);

	CHECK(x == 42);
}

void value_passed_by_ref(int& ref_x)
{
	ref_x = 665;

	std::cout << "param ref_x: " << ref_x << "\n";
}

TEST_CASE("passing by ref")
{
	int x = 42;

	value_passed_by_ref(x);

	CHECK(x == 665);
}

void print(double n, const std::string& desc)
{
	std::cout << desc << " - double: " << n << "\n";
}

void print(const std::vector<int>& vec, const std::string& desc)
{
	std::cout << desc << " = { ";
	for(const auto& item : vec)
	{
		std::cout << item << " ";
	}
	std::cout << "}\n";
}

TEST_CASE("print vector")
{
	std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};

	print(vec, "vec");
	print(3.14, "pi");
}

auto add(int a, int b)
{
	return a + b;
}

auto get_name(int id)
{
	if (id == 1)
		return "SuperGadget"s; // std::string
	return std::string("Gadget"); // std::string
}

TEST_CASE("functions with auto")
{
	int x = 10;
	double y = 2.6;

	std::cout << add(x, y) << "\n";
}

TEST_CASE("namespaces")
{
	using namespace OtherMath;
	double x = OtherMath::square_root(9);
}