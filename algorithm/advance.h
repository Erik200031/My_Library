#ifndef ADVANCE_H
#define ADVANCE_H

#include <iterator>

namespace mylib
{
    template <typename Iter>
    constexpr void do_advance(Iter& first, typename std::iterator_traits<Iter>::difference_type n,
    std::input_iterator_tag)
    {
        while (n > 0)
        {
            ++first;
            --n;
        }
    }

    template <typename Iter>
    constexpr void do_advance(Iter& first, typename std::iterator_traits<Iter>::difference_type n,
    std::bidirectional_iterator_tag)
    {
        while (n > 0)
        {
            ++first;
            --n;
        }
        while (n < 0)
        {
            --first;
            ++n;
        }
    }

    template <typename Iter>
    constexpr void do_advance(Iter& first, typename std::iterator_traits<Iter>::difference_type n,
    std::random_access_iterator_tag)
    {
        first += n;
    }

    template <typename Iter, typename Distance>
    constexpr void advance(Iter& first, Distance n) {
        do_advance(first, typename std::iterator_traits<Iter>::difference_type(n), 
        typename std::iterator_traits<Iter>::iterator_category());
    }

} // namespace mylib

#endif //ADVANCE_H