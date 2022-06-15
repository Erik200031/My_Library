#ifndef EQUAL_TO_H
#define EQUAL_TO_H

namespace mylib
{
    template <typename T>
    struct equal_to
    {
        bool operator()(const T& first, const T& second) {
            return first == second;
        }
    };
    
} // namespace mylib

#endif //EQUAL_TO_H
