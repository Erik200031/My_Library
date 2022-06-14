#ifndef HASH_H
#define HASH_H

namespace mylib
{
    template <typename Key>
    struct hash
    {
        hash() = default;
        size_t operator()(Key key, size_t table_size) const
        {
            long long rand_address = reinterpret_cast<long long>(&key);
            
        }
    };
    
} // namespace mylib




#endif //HASH_H