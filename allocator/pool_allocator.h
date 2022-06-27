#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <iostream>
// #include "../forward_list/forward_list.h"
#include <exception>
#include <forward_list>
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
        pointer allocate(size_t count);
        void deallocate(T* in_start, size_t count);
        void free();
    private:
        size_t m_chunk;
        size_t m_block_count;
        size_t m_block_size;
        size_t m_free_size;
        int8_t* m_start;
        int8_t* m_end;

        std::forward_list<int8_t*> m_buffer;
    };
    
} // namespace mylib

#include "pool_allocator.hpp"

#endif //POOL_ALLOCATOR_H