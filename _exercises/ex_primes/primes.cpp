#include "primes.hpp"

namespace MyMath
{
    bool is_prime(uintmax_t number)
    {
        if (number < 2)
            return false;

        for (uintmax_t i = 2; i * i <= number; i++)
            if (number % i == 0)
                return false;
        return true;
    }

    std::vector<uintmax_t> primes(uintmax_t max_range)
    {
        std::vector<uintmax_t> prime_numbers;

        for (int j = 2; j <= max_range; j++)
            if (MyMath::is_prime(j))
                prime_numbers.push_back(j);

        return prime_numbers;
    }
} // namespace MyMath