#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <iostream>
#include <forward_list>
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
        Pool_alloc(size_t big_block_size = 10, size_t little_block_size = 2);
        pointer allocate(size_t count);
        void deallocate(int8_t* start, size_t count);
        void free();
    private:
        size_t m_chunk;
        size_t m_block_count;
        size_t m_block_size;
        size_t used;
        int8_t* m_start;
        int8_t* m_end;

        std::forward_list<int8_t*> m_buffer;
    };
    
} // namespace mylib

#endif //POOL_ALLOCATOR_H