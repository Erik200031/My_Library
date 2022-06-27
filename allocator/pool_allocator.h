#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <iostream>
#include "../forward_list/forward_list.h"
#include <exception>

namespace mylib
{
    template <class T>
    class Pool_alloc
    {   
    public:
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        Pool_alloc(size_t big_block_size = 1000000, size_t little_block_size = sizeof(T));
        template <typename U>
        Pool_alloc(const Pool_alloc<U>& rhs) 
        : m_chunk {rhs.get_chunk()} , m_block_count {rhs.get_block_count()}, 
        m_block_size {rhs.get_block_size()}, m_free_size {rhs.get_free_size()}
        {
            m_buffer = rhs.get_buffer();
            m_start = (int8_t*)::operator new(m_chunk);
            m_end = m_start + m_chunk;
        } 
        pointer allocate(size_t count);
        void deallocate(T* in_start, size_t count);
        void free();
        size_t get_chunk() const {return m_chunk;}
        size_t get_block_count() const {return m_block_count;}
        size_t get_block_size() const {return m_block_size;}
        size_t get_free_size() const {return m_free_size;}
        auto get_buffer() const {return m_buffer;}
    private:
        size_t m_chunk;
        size_t m_block_count;
        size_t m_block_size;
        size_t m_free_size;
        int8_t* m_start;
        int8_t* m_end;

        mylib::forward_list<int8_t*> m_buffer;
    };
    
} // namespace mylib

#include "pool_allocator.hpp"

#endif //POOL_ALLOCATOR_H