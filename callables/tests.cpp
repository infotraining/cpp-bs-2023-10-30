#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std::literals;

bool is_even(uint64_t n)
{
    return n % 2 == 0;
}

struct IsEven
{
    bool operator()(uint64_t n) const
    {
        return n % 2 == 0;
    }
};

struct GreaterThen
{
    int threshold;

    GreaterThen(int threshold)
        : threshold{threshold}
    { }

    bool operator()(int x) const
    {
        return x > threshold;
    }
};

TEST_CASE("callables")
{
    SECTION("function")
    {
        CHECK(is_even(4) == true); // function call
    }

    SECTION("function objects - functor")
    {
        IsEven is_even_obj; // instance of IsEven class

        CHECK(is_even_obj(4) == true); // function call

        GreaterThen gt100(100);

        CHECK(gt100(99) == false);
        CHECK(gt100(101) == true);
    }
}

TEST_CASE("function objects + algorithms")
{
    std::vector<int> vec = {1, 65, 665, 42, 99, 543, 236};

    auto pos = std::find_if(vec.begin(), vec.end(), is_even); // algorithm with function as predicate
    CHECK(*pos == 42);

    pos = std::find_if(vec.begin(), vec.end(), IsEven{}); // algorithm with function object as predicate
    CHECK(*pos == 42);

    pos = std::find_if(vec.begin(), vec.end(), GreaterThen{100});
    CHECK(*pos == 665);

    CHECK(std::count_if(vec.begin(), vec.end(), GreaterThen{200}) == 3);
}

struct GreaterSize
{
    bool operator()(const std::string& a, const std::string& b) const
    {
        return a.size() < b.size();
    }
};

TEST_CASE("sorting")
{
    std::vector<std::string> words = {"forty-two", "one", "two", "three", "four", "six"};

    std::sort(words.begin(), words.end(), std::greater{});

    for (const auto& w : words)
        std::cout << w << " ";
    std::cout << "\n";

    std::sort(words.begin(), words.end(), GreaterSize{});

    for (const auto& w : words)
        std::cout << w << " ";
    std::cout << "\n";
}

TEST_CASE("std function objects")
{
    std::equal_to eq;
    CHECK(eq(100, 100));

    std::greater gt;
    CHECK(gt(100, 99));
}

//////////////////////////////////////////////////////////////
// lambda expressions

// closure class
struct Lambda_4237645276345764
{
    auto operator()(int n) const { return n % 2 == 0; }
};

TEST_CASE("lambdas")
{
    auto lambda_is_even // closure object
        = [](int n) {
              return n % 2 == 0;
          }; // lambda expression

    SECTION("is interpreted as")
    {
        auto lambda_is_even = Lambda_4237645276345764{}; // closure object
    }

    CHECK(lambda_is_even(4) == true);
    CHECK(lambda_is_even(5) == false);
}

TEST_CASE("lambda + algorithms")
{
    std::vector<int> vec = {1, 65, 665, 42, 99, 543, 236};

    auto is_even_lambda = [](int n) {
        return n % 2 == 0;
    };

    auto pos = std::find_if(vec.begin(), vec.end(), is_even_lambda); // algorithm with lambda as predicate
    CHECK(*pos == 42);

    pos = std::find_if(vec.begin(), vec.end(), [](int n) { return n > 100; });
    CHECK(*pos == 665);

    CHECK(std::count_if(vec.begin(), vec.end(), [](int n) { return n > 200; }) == 3);
}

////////////////////////////////////////////////////////////////////////
// captures

struct Lambda_324796519349467976
{
    const int threshold;

    Lambda_324796519349467976(int t)
        : threshold(t)
    { }

    auto operator()(int n) const { return n > threshold; }
};

TEST_CASE("captures")
{
    std::vector<int> vec = {1, 65, 665, 42, 99, 543, 236};
    
	SECTION("by value")
    {
        int threshold = 200;
        auto pos = std::find_if(vec.begin(), vec.end(), [threshold](int n) { return n > threshold; });
        //auto pos = std::find_if(vec.begin(), vec.end(), [=](int n) { return n > threshold; }); // [=] - all by value

        CHECK(*pos == 665);
    }

    SECTION("by reference")
    {
		std::vector<int> vec_gt_100;

		std::for_each(vec.begin(), vec.end(), [&vec_gt_100](int n) { if (n > 100) vec_gt_100.push_back(n); });
		//std::for_each(vec.begin(), vec.end(), [&](int n) { if (n > 100) vec_gt_100.push_back(n); }); // [&] - all by ref

		CHECK(vec_gt_100 == std::vector{665, 543, 236});
    }

	SECTION("by value & by reference")
    {
		int threshold = 200;
		std::vector<int> vec_gt_threshold;

		std::for_each(vec.begin(), vec.end(), [&vec_gt_threshold, threshold](int n) { if (n > threshold) vec_gt_threshold.push_back(n); });
		//std::for_each(vec.begin(), vec.end(), [&, threshold](int n) { if (n > threshold) vec_gt_threshold.push_back(n); });
		//std::for_each(vec.begin(), vec.end(), [=, &vec_gt_threshold](int n) { if (n > threshold) vec_gt_threshold.push_back(n); });

		CHECK(vec_gt_threshold == std::vector{665, 543, 236});
    }
}

TEST_CASE("lambda - complex case")
{
    float f = 0.5;

    auto lambda_complex = [f](int a, int b, int c) {
        float fa = f * a;

        if (fa > 10.0)
            return fa + b;

        return fa + c;
    };
}

////////////////////////////////////////////////////////////////

TEST_CASE("storing callables")
{
	SECTION("auto")
	{
		auto is_even = [](int n) { return n % 2 == 0; };

		CHECK(is_even(10));
	}	

	SECTION("function pointer")
	{
		bool(*f)(int) = nullptr;

		f = [](int n) { return n % 2 == 0; }; // [] - empty capture clause -> conversion to function pointer

		// int k = 2;
		// f = [k](int n) { return n % k == 0; };

		CHECK(f(10));
	}

	SECTION("std::function")
	{
		std::function<bool(int)> is_even_f;

		is_even_f = ::is_even;
		CHECK(is_even_f(10));

		is_even_f = IsEven{};
		CHECK(is_even_f(10));

		is_even_f = [](int n) { return n % 2 == 0; };
		CHECK(is_even_f(10));

		int k = 2;
		is_even_f = [k](int n) { return n % k == 0; };
		CHECK(is_even_f(10));
	}
}

///////////////////////////////////////////////////////////////////
// Generic lambdas

TEST_CASE("generic lambdas")
{
	auto cmp_by_size = [](const auto& a, const auto& b) { return a.size() < b.size(); };

	std::vector vec_a{1, 2, 3};
	std::vector vec_b{1, 2};
	CHECK(cmp_by_size(vec_a, vec_b) == false);

	CHECK(cmp_by_size(vec_b, std::string("abcd")));


	std::vector<std::string> words = { "one", "two", "fourty-two", "zero", "1" };

	std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) { return a.size() > b.size(); });
	
	for (const auto& w : words)
        std::cout << w << " ";
    std::cout << "\n";
}