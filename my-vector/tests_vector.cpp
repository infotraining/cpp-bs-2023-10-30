#include <catch2/catch_test_macros.hpp>
#include <algorithm>

class Vector
{
private:
    size_t size_;
    int* items_;

public:
    Vector(size_t size)
        : size_{size}
    {
        items_ = new int[size_]; // dynamic allocation

        // fill with zeros
        for(size_t i = 0; i < size_; ++i)
            items_[i] = 0;
    }

    Vector(std::initializer_list<int> lst) : size_{lst.size()}
    {
        items_ = new int[size_];

        std::copy(lst.begin(), lst.end(), items_);
    }

    ~Vector() // destructor
    {
        delete[] items_;
    }

    size_t size() const 
    {
        return size_;
    }

    int& operator[](size_t index) // read-write
    {
        return items_[index];
    }

    const int& operator[](size_t index) const // read-only
    {
        return items_[index];
    }

    bool operator==(const Vector& other) const
    {
        if (size_ != other.size())
            return false;

        for(size_t i = 0; i < size_; ++i)
            if (items_[i] != other[i])
                return false;

        return true;
    }
};

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
