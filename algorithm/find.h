#ifndef FIND_H
#define FIND_H

namespace mylib
{
    template <typename Iter, typename T>
    Iter find(Iter begin, Iter end, const T& key)
    {
        while(begin != end) {
            if(*begin == key) {
                return begin;
            }
            ++begin;
        }
        return begin;
    }

} // namespace mylib

#endif //FIND_H