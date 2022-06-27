#ifndef HASH_H
#define HASH_H

#include "../algorithm/is_prime.h"

namespace mylib
{
    template <typename Key>
    struct hash
    {
        hash() = default;
        size_t operator()(const Key& key, const int table_size) const
        {
            Key tmp = abs(key);
            while (!mylib::is_prime(++tmp)) {}
            tmp += key;
            return tmp % table_size;
        }
    };
    
} // namespace mylib

#endif //HASH_H