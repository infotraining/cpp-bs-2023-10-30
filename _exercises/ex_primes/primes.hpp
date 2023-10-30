#ifndef PRIMES_HPP
#define PRIMES_HPP

#include <cstdint>
#include <vector>

namespace MyMath
{
    bool is_prime(uintmax_t number);

    std::vector<uintmax_t> primes(uintmax_t max_range);
} // namespace MyMath


#endif