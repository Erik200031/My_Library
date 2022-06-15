#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include "../vector/vector.h"
#include "../forward_list/forward_list.h"
#include "../utility/utility.h"
#include "../algorithm/equal_to.h"
#include "hash.h"

#define DEFAULT_BUCKET_COUNT 7
#define MAX_LOAD_FACTOR 1.7

namespace mylib
{
    template <class Key, class T,
    class Hash = mylib::hash<Key>,
    class KeyEqual = mylib::equal_to<Key>> 
    class unordered_map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef mylib::pair<Key, T> value_type;
        typedef size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef Hash hasher;
        typedef KeyEqual key_equal;

        unordered_map() : m_map(DEFAULT_BUCKET_COUNT), m_hasher {}, 
         m_size {}, m_max_load_factor {MAX_LOAD_FACTOR} {}
        unordered_map(size_type bucket_count) : m_map(bucket_count), m_hasher {},
         m_size {}, m_max_load_factor{MAX_LOAD_FACTOR} {}
        unordered_map(size_type bucket_count, const Hash& hash) 
        : m_map(bucket_count), m_hasher {hash},
         m_size {}, m_max_load_factor{MAX_LOAD_FACTOR} {}
        unordered_map(const unordered_map& rhs) 
         : m_map {rhs.m_map}, m_hasher {rhs.m_hasher}, 
         m_size{rhs.m_size}, m_max_load_factor{rhs.m_max_load_factor} {}
        unordered_map(unordered_map&& rhs) noexcept 
         : m_map {std::move(rhs.m_map)}, m_hasher {rhs.m_hasher}, 
         m_size{rhs.m_size}, m_max_load_factor{rhs.m_max_load_factor} {}
        unordered_map& operator=(const unordered_map& rhs);
        unordered_map& operator=(unordered_map&& rhs) noexcept;


        [[nodiscard]] bool empty() const noexcept;
        size_type size() const;
        float load_factor() const;
        float max_load_factor() const;
        // mylib::pair<iterator,bool> 
        void insert(value_type&& value);
        size_type bucket_count() const;
    private:
        mylib::vector<mylib::forward_list<mylib::pair<Key, T>>> m_map;
        Hash m_hasher;
        size_type m_size;
        float m_max_load_factor;
    };
    
} // namespace mylib

#include "unordered_map.hpp"

#endif //UNORDERED_MAP_H