#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include "../vector/vector.h"
#include "../forward_list/forward_list.h"
#include "../utility/utility.h"
#include "../algorithm/equal_to.h"
#include "hash.h"

namespace mylib
{
    template <class Key, class T,
    class Hash = mylib::hash<Key>,
    class KeyEqual = mylib::equal_to<Key>> 
    class unordered_map
    {
    public:


    private:
        std::vector<std::forward_list<std::pair<Key, T>>> m_map;
    };
    
} // namespace mylib





#endif //UNORDERED_MAP_H