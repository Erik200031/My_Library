#ifndef HASH_H
#define HASH_H

namespace mylib
{
    template <typename Key>
    struct hash
    {
        hash() = default;
        size_t operator()(const Key& key, const int& table_size) const
        {
            long long rand_address_1 = reinterpret_cast<long long>(&key);
            int sum_1 {};
            while(rand_address_1) {
                sum_1 += rand_address_1 % 10;
                rand_address_1 /= 10;
            }
            long long rand_address_2 = reinterpret_cast<long long>(&table_size);
            int sum_2 {};
            while(rand_address_2) {
                sum_2 += rand_address_2 % 10;
                rand_address_2 /= 10;
            }
            sum_2 += table_size;
            sum_1 += sum_2;
            return sum_1 % table_size;
        }
    };
    
} // namespace mylib




#endif //HASH_H