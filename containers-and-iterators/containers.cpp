#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <format>
#include <algorithm>

using namespace std::literals;

static int global_x = 10;

namespace LegacyCode
{
	double avg(const int* data, const int size)
	{
		double sum = 0.0;

		for (const int* ptr_item = data; ptr_item != data + size; ++ptr_item)
			sum += *ptr_item;

		return sum / size;
	}
}

namespace ModernCpp
{
	// TODO: Modernize avg function
}

TEST_CASE("avg")
{
	int data_1[10] = {};
	CHECK(LegacyCode::avg(data_1, 10) == 0.0);

	
	int data_2[] = { 1, 2, 3, 4, 5 };
    CHECK(LegacyCode::avg(data_2, 5) == 3.0);   
}

TEST_CASE("array")
{
	std::array<int, 10> data_1 = {};
	CHECK(LegacyCode::avg(data_1.data(), data_1.size()) == 0.0);

	std::array data_2 = {1, 2, 3, 4, 5}; // since C++17
	CHECK(LegacyCode::avg(data_2.data(), data_2.size()) == 3.0);

	data_2.fill(0);
	CHECK(data_2 == std::array{0, 0, 0, 0, 0});

	// std::array<int, 1'000'000> large_data = { 1, 2, 3 }; // STACK Overflow
}

TEST_CASE("heap")
{
	int* ptr_n = new int(13); // allocate one int on heap
	*ptr_n = 42;
	delete ptr_n; // dealloc
}

TEST_CASE("dynamic array")
{
	int* data_a = new int[1'000'000]; // allocate array of 1mln ints on heap

	for(int* it = data_a; it != data_a + 1'000'000; ++it)
		*it = 0;

	for(int i = 0; i < 1'000'000; ++i)
		data_a[i] = i; // *(data_a + i) = i

	delete[] data_a; // dealloc
}

TEST_CASE("vector")
{
	std::vector<int> data_vec(1'000'000);
	
	for(int i = 0; i < data_vec.size(); ++i)
		data_vec[i] = i;

	// range-based for
	for(int& item : data_vec)
	{
		item = 0;
	}
}

TEST_CASE("vector - resizing")
{
	std::vector<int> vec = {1, 2};
	vec.reserve(100);

	std::cout << "vec.size() = " << vec.size() << "; vec.capacity() = " << vec.capacity() << ";\n";

	for(int i = 3; i < 100; ++i)
	{
		vec.push_back(i);
		std::cout << "vec.size() = " << vec.size() << "; vec.capacity() = " << vec.capacity() << ";\n";
	}
}

/////////////////////////////////////////////////////////////////
// iterator 

TEST_CASE("iterator")
{
	SECTION("pointer is native iterator")
	{
		int tab[] = {1, 2, 3, 4};

		for(int* it = tab; it != tab + 4; ++it)
			*it = 0;
	}

	SECTION("iterator - array")
	{
		std::array<int, 4> vec = {1, 2, 3, 4};

		for(std::array<int, 4>::iterator it = vec.begin(); it != vec.end(); ++it)
			*it = 0;

		for(auto it = vec.begin(); it != vec.end(); ++it)
			*it = 0;

		for(std::array<int, 4>::const_iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
		std::cout << "\n";

		for(auto it = vec.cbegin(); it != vec.cend(); ++it)
			std::cout << *it << " ";
		std::cout << "\n";
	}

	SECTION("iterator - vector")
	{
		std::vector<int> vec = {1, 2, 3, 4};

		for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
			*it = 0;
		
		for(auto it = vec.begin(); it != vec.end(); ++it)
			*it = 0;
	}
}

TEST_CASE("range-based for")
{
	std::vector<std::string> vec = {"1_one", "2_two", "3_three", "4_four"};

	for(const std::string& item : vec)
	{
		std::cout << item << " ";
	}
	std::cout << "\n";

	SECTION("is interpreted as")
	{
		for(auto it = vec.begin(); it != vec.end(); ++it)
		{
			const std::string& item = *it;

			std::cout << item << " ";
		}
		std::cout << "\n";
	}
}

/////////////////////////////////////////////////////////////////
// Algorithm = Container + Iterator

TEST_CASE("algorithms")
{
	std::vector<int> vec = {1, 534, 665, 234, 42, 77, 0, 454};

	CHECK(*(vec.begin() + 2) == 665);
	CHECK(*(vec.end() - 1) == 454);

	//std::vector<int>::iterator pos = std::find(vec.begin(), vec.end(), 0);
	auto pos = std::find(vec.rbegin(), vec.rend(), 0);

	if (pos != vec.rend())
		std::cout << "Found: " << *pos << "\n";
	else
		std::cout << "Not found!\n";

	std::vector<int> empty_vec;
	CHECK(empty_vec.begin() == empty_vec.end());

	std::sort(vec.begin(), vec.end());
	std::reverse(vec.begin(), vec.end());

	for(const auto& item : vec)
		std::cout << item << " ";
	std::cout << "\n";

	for(auto rit = vec.rbegin(); rit != vec.rend(); ++rit)
	{
		std::cout << *rit << " ";
	}
	std::cout << "\n";
}

TEST_CASE("native array")
{
	int numbers[] = {1, 2, 76, 42, 665, 0, 77};

	std::sort(numbers, numbers + 7); 
	std::sort(numbers, numbers + std::size(numbers)); 
	std::sort(std::begin(numbers), std::end(numbers)); 

	CHECK(std::is_sorted(std::begin(numbers), std::end(numbers)));
}
