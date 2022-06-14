#ifndef SWAP_H
#define SWAP_H

namespace mylib
{
    template <typename T>
    void swap(T& element1 , T& element2) 
    {
        T tmp = std::move(element1);
        element1 = std::move(element2);
        element2 = std::move(tmp);
    } 

} // namespace mylib

#endif //SWAP_H