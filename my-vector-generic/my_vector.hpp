#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <algorithm>
#include <iostream>

namespace Training
{
    template <typename T>
    class Vector
    {
    private:
        size_t size_;
        T* items_;

    public:
        using iterator = T*; // typedef int* iterator;
        using const_iterator = const T*;
        using reference = T&;
        using const_reference = const T&;

        Vector(size_t size)
            : size_{size}
            , items_{new T[size_]} // acquisition of resource
        {
            std::fill_n(begin(), size_, T{});
        }

        Vector(std::initializer_list<T> lst)
            : size_{lst.size()}
            , items_{new T[size_]}
        {
            std::copy(lst.begin(), lst.end(), items_);
        }

        // copy constructor
        Vector(const Vector& source)
            : size_{source.size()}
            , items_{new T[source.size()]}
        {
            std::copy(source.begin(), source.end(), items_);
        }

        // copy assignment
        Vector& operator=(const Vector& source)
        {
            if (this != &source) // avoiding self-assignment
            {
                // alloc new array & copy all items from source
                T* items_temp = new T[source.size()];
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
            delete[] items_; // release is resource
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

        reference operator[](size_t index) // read-write
        {
            return items_[index];
        }

        const_reference operator[](size_t index) const // read-only
        {
            return items_[index];
        }

        reference at(size_t index)
        {
            if (index >= size_)
                throw std::out_of_range("Index out of range");

            return items_[index];
        }

        const_reference at(size_t index) const
        {
            if (index >= size_)
                throw std::out_of_range("Index out of range");

            return items_[index];
        }

        bool operator==(const Vector& other) const
        {
            return size_ == other.size_ && std::equal(items_, items_ + size_, other.items_);
        }

        void push_back(const T& new_item)
        {
            T* temp_items_ = new T[size_ + 1];
            std::copy(begin(), end(), temp_items_);
            temp_items_[size_] = new_item;
            delete[] items_;
            items_ = temp_items_;
            size_ = size_ + 1;
        }
    };
} // namespace Training

#endif