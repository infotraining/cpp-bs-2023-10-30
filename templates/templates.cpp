#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

static int id_gen = 0; // name id_gen is visible only in this file

namespace
{
    int id_gen_2 = 0; // name id_gen_2 is visible only in this file
}

void foo()
{
    static int counter = 0;

    std::cout << "foo() called " << ++counter << " times.\n";
}

TEST_CASE("modifiers")
{
    int x = 10;
    const int cx = 10;
    //++cx;

    std::cout << ++id_gen << "\n";
    std::cout << ++id_gen_2 << "\n";

    foo();
    foo();
    foo();
    foo();

    volatile double temp = 10;

    std::cout << "current temp: " << temp << "\n";
    std::cout << "current temp: " << temp << "\n";
    std::cout << "current temp: " << temp << "\n";
}

template <typename T>
T max_value(T a, T b)
{
    return a < b ? b : a;
}

template <typename T>
T max_value(T* a, T* b)
{
    assert(a != nullptr);
    assert(b != nullptr);

    return *a < *b ? *b : *a;
}

const char* max_value(const char* a, const char* b)
{
    return std::strcmp(a, b) < 0 ? b : a;
}

namespace Alternative
{
    template <typename T1, typename T2>
    auto max_value(T1 a, T2 b)
    {
        return a < b ? b : a;
    }
} // namespace Alternative

TEST_CASE("template functions")
{
    CHECK(max_value(5, 10) == 10);
    CHECK(max_value(3.14, 3.0) == 3.14);

    std::string txt1 = "abc";
    std::string txt2 = "def";

    CHECK(max_value(txt1, txt2) == "def"s);

    std::vector v1{1, 2, 3};
    std::vector v2{1, 2, 4};
    CHECK(max_value(v1, v2) == v2);

    CHECK(max_value(static_cast<double>(4), 4.15) == 4.15);
    CHECK(max_value<double>(4, 4.15) == 4.15);

    CHECK(Alternative::max_value(3, 4.15) == 4.15);

    std::string* ptr1 = &txt1;
    std::string* ptr2 = &txt2;

    CHECK(max_value(ptr1, ptr2) == "def"s);

    const char* ctxt1 = "txt1";
    const char* ctxt2 = "txt2";
    CHECK(max_value(ctxt1, ctxt2) == "txt2"s);
}

template <typename InputIterator, typename T>
InputIterator my_find(InputIterator begin, InputIterator end, const T& val)
{
    for (InputIterator it = begin; it != end; ++it)
    {
        if (*it == val)
            return it;
    }

    return end;
}

TEST_CASE("my_find")
{
    std::vector<int> vec = {1, 2, 3, 42, 5, 6};

    auto pos = my_find(vec.begin(), vec.end(), 42);
    CHECK(pos != vec.end());
    CHECK(*pos == 42);

    pos = my_find(vec.begin(), vec.end(), 665);
    CHECK(pos == vec.end());

    int tab[] = {1, 2, 3, 42, 665};
    int* it = my_find(std::begin(tab), std::end(tab), 42);
    CHECK(*it == 42);
}

template <typename InputIterator, typename Predicate>
InputIterator my_find_if(InputIterator begin, InputIterator end, Predicate predicate)
{
    for (InputIterator it = begin; it != end; ++it)
    {
        if (predicate(*it))
            return it;
    }

    return end;
}

namespace Cpp20
{
    auto my_find_if(auto begin, auto end, auto predicate)
    {
        for (auto it = begin; it != end; ++it)
        {
            if (predicate(*it))
                return it;
        }

        return end;
    }
} // namespace Cpp20

TEST_CASE("my_find_if")
{
    std::vector<int> vec = {1, 2, 3, 42, 5, 6};

    auto pos = my_find_if(vec.begin(), vec.end(), [](int n) { return n > 30; });
}

/////////////////////////////////////////////////////////
// class templates

template <typename T1, typename T2>
struct Pair
{
    T1 first;
    T2 second;

    Pair(T1 f, T2 s)
        : first(std::move(f))
        , second(std::move(s))
    { }

	void print() const;
};

template <typename T1, typename T2>
Pair<T1, T2> my_make_pair(T1 f, T2 s)
{
	return Pair<T1, T2>(f, s);
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const Pair<T1, T2>& p)
{
	return out << "Pair{" << p.first << ", " << p.second << "}";	
}

template <typename T1, typename T2>
void Pair<T1, T2>::print() const
{
	std::cout << "Pair(" << first << ", " << second << ")\n";
}

TEST_CASE("class templates")
{
	Pair<int, double> p1{1, 3.14};

	CHECK(p1.first == 1);
	CHECK(p1.second == 3.14);

	p1.print();

	Pair<std::string, int> p2{"abc"s, 1};

	auto p3 = my_make_pair(1, 3.14);;

	// since C++17
	Pair p4{1, 3.14};

	std::cout << "p4: " << p4 << "\n";
}
