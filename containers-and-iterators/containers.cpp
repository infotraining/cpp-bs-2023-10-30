#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <deque>
#include <format>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <numeric>

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
} // namespace LegacyCode

namespace ModernCpp
{
    // TODO: Modernize avg function
}

TEST_CASE("avg")
{
    int data_1[10] = {};
    CHECK(LegacyCode::avg(data_1, 10) == 0.0);

    int data_2[] = {1, 2, 3, 4, 5};
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

    for (int* it = data_a; it != data_a + 1'000'000; ++it)
        *it = 0;

    for (int i = 0; i < 1'000'000; ++i)
        data_a[i] = i; // *(data_a + i) = i

    delete[] data_a; // dealloc
}

TEST_CASE("vector")
{
    std::vector<int> data_vec(1'000'000);

    for (int i = 0; i < data_vec.size(); ++i)
        data_vec[i] = i;

    // range-based for
    for (int& item : data_vec)
    {
        item = 0;
    }
}

TEST_CASE("vector - reallocation & shrinking")
{
    SECTION("push_back & reallocation")
    {
        std::vector<int> vec = {1, 2};
        vec.reserve(100);

        std::cout << "vec.size() = " << vec.size() << "; vec.capacity() = " << vec.capacity() << ";\n";

        for (int i = 3; i < 100; ++i)
        {
            vec.push_back(i);
            std::cout << "vec.size() = " << vec.size() << "; vec.capacity() = " << vec.capacity() << ";\n";
        }
    }

    SECTION("shrinking")
    {
        std::vector<int> vec = {1, 2};
        vec.resize(1'000'000);

        //

        vec.clear();
        CHECK(vec.size() == 0);
        CHECK(vec.capacity() >= 1'000'000);

        vec.shrink_to_fit();
        CHECK(vec.size() == 0);
        CHECK(vec.capacity() >= 0);
    }
}

/////////////////////////////////////////////////////////////////
// iterator

TEST_CASE("iterator")
{
    SECTION("pointer is native iterator")
    {
        int tab[] = {1, 2, 3, 4};

        for (int* it = tab; it != tab + 4; ++it)
            *it = 0;
    }

    SECTION("iterator - array")
    {
        std::array<int, 4> vec = {1, 2, 3, 4};

        for (std::array<int, 4>::iterator it = vec.begin(); it != vec.end(); ++it)
            *it = 0;

        for (auto it = vec.begin(); it != vec.end(); ++it)
            *it = 0;

        for (std::array<int, 4>::const_iterator it = vec.begin(); it != vec.end(); ++it)
            std::cout << *it << " ";
        std::cout << "\n";

        for (auto it = vec.cbegin(); it != vec.cend(); ++it)
            std::cout << *it << " ";
        std::cout << "\n";
    }

    SECTION("iterator - vector")
    {
        std::vector<int> vec = {1, 2, 3, 4};

        for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
            *it = 0;

        for (auto it = vec.begin(); it != vec.end(); ++it)
            *it = 0;
    }
}

TEST_CASE("range-based for")
{
    std::vector<std::string> vec = {"1_one", "2_two", "3_three", "4_four"};

    for (const std::string& item : vec)
    {
        std::cout << item << " ";
    }
    std::cout << "\n";

    SECTION("is interpreted as")
    {
        for (auto it = vec.begin(); it != vec.end(); ++it)
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

    // std::vector<int>::iterator pos = std::find(vec.begin(), vec.end(), 0);
    auto pos = std::find(vec.rbegin(), vec.rend(), 0);

    if (pos != vec.rend())
        std::cout << "Found: " << *pos << "\n";
    else
        std::cout << "Not found!\n";

    std::vector<int> empty_vec;
    CHECK(empty_vec.begin() == empty_vec.end());

    std::sort(vec.begin(), vec.end());
    std::reverse(vec.begin(), vec.end());

    for (const auto& item : vec)
        std::cout << item << " ";
    std::cout << "\n";

    for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit)
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

///////////////////////////////////////////////////////////////
// STL containers

TEST_CASE("invalidation of iterators")
{
    std::vector<int> vec = {1, 3, 5, 42, 77, 99};

    auto pos = std::find(vec.begin(), vec.end(), 42);
    int& value = *pos;
    int* ptr_value = &(*pos);
    auto pos_end = vec.end();

    CHECK(pos != vec.end());
    CHECK(*pos == 42);

    vec.push_back(665); // reallocation of buffer - pos, value, ptr_value are invalidated

    // auto evil_value = *pos; // UB!!!
}

TEST_CASE("deque")
{
    std::deque<int> dq = {1, 2, 3, 4, 5, 6};

    dq[3] = 665; // Random Access Iterator

    int& ref_to_third_elem = dq[2];

    auto it = dq.begin() + 2; // Random Access Iterator
    int& ref_to_three = *it;

    dq.push_back(0);
    dq.push_front(665);

    CHECK(ref_to_third_elem == 3);

    dq.resize(1'000'000);

    std::sort(dq.begin(), dq.end());

    dq.clear(); // release memory
}

TEST_CASE("list")
{
    std::list<std::string> words = {"one", "two", "three"};

    // words[1] = "jeden"; // no indexing - Bidirectional Iterator

    for (const auto& item : words)
        std::cout << item << " ";
    std::cout << "\n";

    std::string& first_word = *words.begin();
    auto pos = --words.end();
    CHECK(*pos == "three");

    words.insert(pos, "two & half");
    CHECK(first_word == "one");
    CHECK(*pos == "three");

    words.sort();
    words.reverse();

    for (const auto& item : words)
        std::cout << item << " ";
    std::cout << "\n";
}

////////////////////////////////////////////////////
// STL Associative containers

TEST_CASE("set & multiset")
{
    SECTION("set")
    {
        std::set<int> numbers = {1, 5, 2, 42, 7, 5, 42, 665};

        if (auto [pos, was_inserted] = numbers.insert(9); was_inserted)
			std::cout << *pos << " was inserted into set!\n";
		else
			std::cout << *pos << " was already in set!\n";


        for (const auto& item : numbers)
            std::cout << item << " ";
        std::cout << "\n";

        if (auto pos = numbers.find(42); pos != numbers.end()) // if with initializer - C++17
        {
            std::cout << "Found: " << *pos << "\n";
        }
        else
        {
            std::cout << "Not found!\n";
        }
    }

    SECTION("multiset")
    {
        std::multiset<int> numbers = {1, 5, 2, 42, 7, 5, 42, 665};

        numbers.insert(9);
        numbers.insert(9);
        numbers.insert(9);

        for (const auto& item : numbers)
            std::cout << item << " ";
        std::cout << "\n";
    }
}

TEST_CASE("map & multimap")
{
    std::map<int, std::string> dict = {{1, "one"}, {2, "two"}, {3, "three"}};

    CHECK(dict[1] == "one");
    CHECK(dict[3] == "three");
    CHECK(dict[0] == "");

    if (auto pos = dict.find(0); pos != dict.end())
    {
        pos->second = "zero";
    }

    CHECK(dict.size() == 4);

    SECTION("classic iteration over map")
    {
        for (const auto& key_value : dict)
        {
            std::cout << key_value.first << " - " << key_value.second << "\n";
        }
    }

	SECTION("since C++17 with structured bindings")
	{
		for (const auto& [key, value] : dict)
        {
            std::cout << key << " - " << value << "\n";
        }
	}
}

struct ErrorCode
{
    int errc;
    const char* msg;
};

TEST_CASE("structured bindings")
{
    ErrorCode ec{42, "invalid arg"};

    const auto& [error_code, error_msg] = ec;

    CHECK(error_code == 42);
}


TEST_CASE("std::pair")
{
    std::pair<int, std::string> p1{42, "forty two"};

    CHECK(p1.first == 42);
    CHECK(p1.second == "forty two");

    auto p2 = std::make_pair(665, "less evil"s); // std::pair<int, std::string>
    auto p3 = std::pair(7, "seven"s);

    auto& [id, name] = p1; // structured bindings
    CHECK(id == 42);
    CHECK(name == "forty two");
}

std::tuple<int, int, double> calc_stats(const std::vector<int>& data)
{
	const auto [pos_min, pos_max] = std::minmax_element(data.begin(), data.end());

	double sum = std::accumulate(data.begin(), data.end(), 0.0);

	return std::tuple{*pos_min, *pos_max, sum / data.size()};
}

TEST_CASE("tuples")
{
	std::tuple<int, float, std::string, std::vector<int>> record_1{1, 3.13, "text", {1, 2, 3}};
	CHECK(std::get<0>(record_1) == 1);
	CHECK(std::get<3>(record_1) == std::vector{1, 2, 3});

	std::tuple record_2{1, 3.13f, "text"s, std::vector{1, 2, 3}};

	CHECK(record_1 == record_2);

	const auto& [id, pi, text, vec] = record_2; // Structured Bindings
	CHECK(text == "text");

	std::vector<int> data = {1, 645, 342, 654, 2323, 777};
	
	const auto [min, max, avg] = calc_stats(data);

	CHECK(min == 1);
	CHECK(max == 2323);
}