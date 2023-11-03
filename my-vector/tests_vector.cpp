#include "my_vector.hpp"

#include <catch2/catch_test_macros.hpp>
#include <exception>
#include <stdexcept>

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
    Vector vec = {1, 2, 3, 4, 5};

    vec.push_back(6);
    vec.push_back(7);

    CHECK(vec.size() == 7);
    CHECK(vec == Vector{1, 2, 3, 4, 5, 6, 7});
}

TEST_CASE("vector - copy")
{
    Vector vec = {1, 2, 3, 4, 5};

    SECTION("copy constructor")
    {
        Vector backup = vec; // copy-constructor
        //Vector backup(vec);  // copy-constructor

        CHECK(vec == Vector{1, 2, 3, 4, 5});
        CHECK(backup == Vector{1, 2, 3, 4, 5});
    }

    SECTION("copy assignment")
    {
        Vector temp = {100, 101};

        vec = temp; // copy-assignment

        CHECK(vec == temp);

        vec = vec; // self-assignment
    }
}

TEST_CASE("vector - move")
{
    Vector vec = {1, 2, 3, 4, 5};

    SECTION("move constructor")
    {
        Vector target = std::move(vec); // move-constructor

        CHECK(vec.size() == 0);
        CHECK(target == Vector{1, 2, 3, 4, 5});
    }

    SECTION("move assignment")
    {
        Vector temp = {100, 101};

        vec = std::move(temp); // move-assignment

        CHECK(temp.size() == 0);
        CHECK(vec == Vector{100, 101});
    }
}

std::string full_name(const std::string& fn, const std::string& ln)
{
    return fn + " " + ln;
}

TEST_CASE("lvalue-ref vs. rvalue-ref")
{
    std::string str = "text";

    SECTION("lvalue-ref - C++98")
    {
        std::string& lv_ref = str;
        const std::string& name = full_name("Jan", "Kowalski");
        std::cout << name << "\n";
        //name[0] = 'P';
    }

    SECTION("rvalue-ref - C++11")
    {
        //std::string&& rv_ref = str; // ERROR

        std::string&& name = full_name("Jan", "Kowalski");
        name[0] = 'P';
        std::cout << name << "\n";
    }
}

void foo(const Vector& v)
{
    std::vector<Vector> data;

    data.push_back(v); // copy
}

void foo(Vector&& v)
{
    std::vector<Vector> data;

    data.push_back(std::move(v)); // move
}

TEST_CASE("using const& and &&")
{
    SECTION("copy")
    {
        Vector v{1, 2, 3};
        foo(v);
    }

    SECTION("move")
    {
        Vector v{1, 2, 3};

        Vector temp{55, 66};
        v = std::move(temp); // move-assignment
        CHECK(temp.size() == 0);

        foo(std::move(v));
        CHECK(v.size() == 0);
    }
}

///////////////////////////////////////
Vector create_large_vec()
{
    Vector vec(1'000'000);

    for(size_t i = 0; i < vec.size(); ++i)
        vec[i] = i;

    return vec;
}

TEST_CASE("large vec")
{   
    //           r-value  
    Vector vec = create_large_vec(); 

    CHECK(vec.size() == 1'000'000);
}

class Data
{
    std::string name;
    Vector vec;

public:
    Data(const std::string& n, const Vector& v)
        : name{n}, vec{v}
    {}

    void print() const
    {
        std::cout << name << " : { ";
        for(const auto& item : vec)
            std::cout << item << " ";
        std::cout << "}\n";
    }
};

TEST_CASE("Data")
{
    Data d1{"d1", {1, 2, 3, 4}};

    d1.print();
}

////////////////////////////////////////////////////////////////////
// Exceptions

int divide(int a, int b)
{
    if (b == 0)
        throw std::invalid_argument("Division by zero");

    std::cout << "divide(" << a << ", " << b << ")\n";

    return a / b;
}

void wrapper()
{
    int result = divide(1, 0);

    std::cout << "result: " << result << "\n";
}

TEST_CASE("exceptions")
{   
    try
    {
         wrapper();
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }   
    catch(const std::exception& e)
    {
        std::cerr << "std::exception: " << e.what() << '\n';
    }
    catch(...)
    {
        std::cout << "Caught an error!!!\n";
    }
}

TEST_CASE("vector - exceptions")
{
    SECTION("std::vector")
    {
        std::vector<int> vec = {1, 2, 3};

        try
        {
            int& item = vec.at(10);
        }
        catch(const std::out_of_range& e)
        {
            std::cerr << e.what() << '\n';
        }                        
    }

    SECTION("Vector")
    {
        const Vector vec = {1, 2, 3};

        CHECK_THROWS_AS(vec.at(10), std::out_of_range);
    }
}