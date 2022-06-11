#ifndef MAP_H
#define MAP_H

#include <functional>
#include <utility>

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
            m_tree.insert(std::make_pair(key, value));
            m_tree.print_in_order();
        }


    private:
        mylib::rb_tree<std::pair<Key, T>> m_tree;
    };



} // namespace mylib

#include "map.hpp"

#endif //MAP_H