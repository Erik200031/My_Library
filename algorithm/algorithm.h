#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <functional>

namespace mylib
{
    template <typename RandomIt, class Compare = std::less<typename RandomIt::value_type>>
    constexpr void make_heap(RandomIt first, RandomIt last, 
    Compare cmp = std::less<typename RandomIt::value_type>())
    {
        if(first == last) {
            return;
        }
        auto size = std::distance(first, last);
        for(int i = 0; i < size - 2; ++i) {
            if((2 * i) + 1 < size && !cmp(first[(2 * i) + 1], first[i])) {
                std::swap(first[(2 * i) + 1], first[i]);
                int j = i;
                while (!cmp(first[j], first[(j - 2) / 2]) && j > 0)
                {
                    std::swap(first[(j - 2) / 2], first[j]);
                    j = (j - 2) / 2;
                }
            }
            if((2 * i) + 2 < size && !cmp(first[(2 * i) + 2], first[i])) {
                std::swap(first[(2 * i) + 2], first[i]);
                int j = i;
                while (!cmp(first[j], first[(j - 2) / 2]) && j > 0)
                {
                    std::swap(first[(j - 2) / 2], first[j]);
                    j = (j - 2) / 2;
                }   
            }
        }
    }

    template<class RandomIt>
    constexpr void pop_heap(RandomIt first, RandomIt last)
    {
        std::swap(*first, *(last - 1));
    }

} // namespace mylib

#endif //ALGORITHM_H