#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <iterator>

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
        typedef typename mylib::vector<mylib::forward_list<mylib::pair<Key, T>>>::iterator rand_iter;
        typedef typename mylib::forward_list<mylib::pair<Key, T>>::Iterator forw_iter;
        typedef mylib::vector<mylib::forward_list<mylib::pair<Key, T>>> hash_map;
    //     class Iterator;
    // private:
    //     class Iterator_helper 
    //     {
    //         Iterator_helper(hash_map& map);
    //         rand_iter m_rand_itr;
    //         forw_iter m_forw_itr;
    //         friend class Iterator;
    //         friend class unordered_map;
    //     };
    public:
        class Iterator 
         : public std::iterator<std::forward_iterator_tag, mylib::pair<Key, T>>
        {
        public:
            // Iterator(hash_map& map) : m_map_ref(map)
            //  {m_rand_itr = m_map_ref.begin();
            //  m_forw_itr = m_map_ref[0].begin();}
             Iterator(const hash_map& map) 
             {}
            // Iterator(forw_iter it, hash_map& map) : m_map_ref(map)
            //  {m_rand_itr = m_map_ref.begin();
            //  m_forw_itr = m_map_ref[0].begin();}
            // Iterator(const Iterator& rhs) {}
            // Iterator(Iterator&& rhs) {}
        public:
            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator=(const Iterator& rhs);
            Iterator& operator=(Iterator&& rhs);
            bool operator==(Iterator& rhs);
            bool operator!=(Iterator& rhs);
            mylib::pair<Key, T>& operator*();
            mylib::pair<Key, T>* operator->();
        private:
            // const hash_map& m_map_ref;
            rand_iter m_rand_itr;
            forw_iter m_forw_itr;
        };

        unordered_map() : m_map(DEFAULT_BUCKET_COUNT), m_hasher {}, 
         m_size {}, m_max_load_factor {MAX_LOAD_FACTOR} {}
        unordered_map(size_type bucket_count) : m_map(bucket_count), m_hasher {},
         m_size {}, m_max_load_factor{MAX_LOAD_FACTOR} {}
        unordered_map(size_type bucket_count, const Hash& hash) 
        : m_map(bucket_count), m_hasher {hash}, m_size {},
         m_max_load_factor{MAX_LOAD_FACTOR} {}
        unordered_map(const unordered_map& rhs) 
         : m_map {rhs.m_map}, m_hasher {rhs.m_hasher}, m_size{rhs.m_size},
          m_max_load_factor{rhs.m_max_load_factor} {}
        unordered_map(unordered_map&& rhs) noexcept 
         : m_map {std::move(rhs.m_map)}, m_hasher {rhs.m_hasher}, m_size{rhs.m_size},
          m_max_load_factor{rhs.m_max_load_factor} {}
        unordered_map& operator=(const unordered_map& rhs);
        unordered_map& operator=(unordered_map&& rhs) noexcept;
        T& operator[](Key&& key);
        T& operator[](const Key& key);

        [[nodiscard]] bool empty() const noexcept;
        size_type size() const;
        float load_factor() const;
        float max_load_factor() const;
        // mylib::pair<iterator,bool> 
        void insert(value_type&& value);
        void insert(const value_type& value);
        size_type bucket_count() const;
        void print();

        Iterator begin();
    private:
        // static get_local_iter() {return m_local_itr;}
    private:
        auto& m_pre_incr(size_t index);
        hash_map m_map;
        Hash m_hasher;
        size_type m_size;
        float m_max_load_factor;
        // static Iterator_helper m_local_itr;
    };
    
} // namespace mylib

#include "unordered_map.hpp"

#endif //UNORDERED_MAP_H