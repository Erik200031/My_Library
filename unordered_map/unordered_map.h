#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <functional>
#include <vector>
#include <forward_list>
#include <utility>

namespace mylib
{
    template <class Key, class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>> 
    class unordered_map
    {



    private:
        std::vector<std::forward_list<std::pair<Key, T>>> m_map;
    };
    
} // namespace mylib





#endif //UNORDERED_MAP_H