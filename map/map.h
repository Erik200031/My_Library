#ifndef MAP_H
#define MAP_H

#include <functional>

#include "../data_structures/rb_tree/rb_tree.h"


namespace mylib
{
    template <typename Key, typename T, typename Compare = std::less<T>>    
    class map
    {

    public:
        map() = default;
        ~map() = default;
        void insert(const Key& key, const T& value) { 
            
        }


    private:
        mylib::rb_tree<std::pair<Key, T>> m_tree;
    };



} // namespace mylib

#include "map.hpp"

#endif //MAP_H