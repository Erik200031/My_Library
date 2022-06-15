#ifndef HASH_H
#define HASH_H

namespace mylib
{
    template <typename Key>
    struct hash
    {
        hash() = default;
        size_t operator()(const Key& key, const int table_size) const
        {
            long long rand_address = (long long)(&key);
            return rand_address % table_size;
        }
    };
    
} // namespace mylib

#endif //HASH_H