#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <algorithm>
#include <iostream>

namespace Training
{
    class Vector
    {
    private:
        size_t size_;
        int* items_;

    public:
        using iterator = int*; // typedef int* iterator;
        using const_iterator = const int*;

        Vector(size_t size)
            : size_{size}
            , items_{new int[size_]}
        {
            std::fill_n(begin(), size_, 0);
        }

        Vector(std::initializer_list<int> lst)
            : size_{lst.size()}
            , items_{new int[size_]}
        {
            std::copy(lst.begin(), lst.end(), items_);

            std::cout << "Vector({ ";
            for(const auto& item : *this)
                std::cout << item << " ";
            std::cout << "})\n";
        }

        // copy constructor
        Vector(const Vector& source)
            : size_{source.size()}
            , items_{new int[source.size()]}
        {
            std::copy(source.begin(), source.end(), items_);

            std::cout << "Vector(cc: { ";
            for(const auto& item : *this)
                std::cout << item << " ";
            std::cout << "})\n";
        }

        // copy assignment
        Vector& operator=(const Vector& source)
        {
            if (this != &source) // avoiding self-assignment
            {
                // alloc new array & copy all items from source
                int* items_temp = new int[source.size()];
                std::copy(source.begin(), source.end(), items_temp);

                delete[] items_;       // release old array
                items_ = items_temp;   // assign new array
                size_ = source.size(); // assign new size
            }

            return *this;
        }

        // move-constructor - C++11
        Vector(Vector&& source)
            : size_{source.size()}, items_{source.items_}
        {
            source.size_ = 0;
            source.items_ = nullptr;

            std::cout << "Vector(mv: { ";
            for(const auto& item : *this)
                std::cout << item << " ";
            std::cout << "})\n";
        }

        // move-assignment - C++11
        Vector& operator=(Vector&& source)
        {
            if (this != &source)
            {
                size_ = source.size_;
                items_ = source.items_;

                source.size_ = 0;
                source.items_ = nullptr;
            }

            return *this;
        }

        ~Vector() // destructor
        {
            delete[] items_;
        }

        size_t size() const
        {
            return size_;
        }

        iterator begin()
        {
            return items_;
        }

        iterator end()
        {
            return items_ + size_;
        }

        const_iterator begin() const
        {
            return items_;
        }

        const_iterator end() const
        {
            return items_ + size_;
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
            // if (size_ != other.size())
            //     return false;

            // for(size_t i = 0; i < size_; ++i)
            //     if (items_[i] != other[i])
            //         return false;

            // return true;

            return size_ == other.size_ && std::equal(items_, items_ + size_, other.items_);
        }

        void push_back(int new_item)
        {
            int* temp_items_ = new int[size_ + 1];
            std::copy(begin(), end(), temp_items_);
            temp_items_[size_] = new_item;
            delete[] items_;
            items_ = temp_items_;
            size_ = size_ + 1;
        }
    };
} // namespace Training

#endif