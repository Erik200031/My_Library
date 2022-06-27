#ifndef IS_PRIME_H
#define IS_PRIME_H

#include <iostream>

namespace mylib
{
    bool is_prime(size_t num)
    {
        if(num <= 1) {return false;}
        for(int i = 2; i <= sqrt(num); ++i) {
            if(num % i == 0) {
                return false;
            }
        }
        return true;
    }

} // namespace mylib

#endif //IS_PRIME_H