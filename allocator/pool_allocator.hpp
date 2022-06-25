#include "pool_allocator.h"

template <typename T>
mylib::Pool_alloc<T>::Pool_alloc(size_t big_block_size = 10, size_t little_block_size = 2)
{
    m_block_count = 0;
    used = 0;
    m_block_size = little_block_size;
    m_chunk = big_block_size;
    m_start = ::operator new(m_chunk);
    m_end = m_start + big_block_size;
    int8_t* tmp = m_start;
    while (tmp != end) {
        m_buffer.push_front(tmp);
        tmp += m_block_size;
        ++m_block_count;
    }
}

template <typename T>
mylib::Pool_alloc<T>::pointer 
mylib::Pool_alloc<T>::allocate(size_t count)
{
    if((count * sizeof(T) > m_chunk) ||
    count * sizeof(T) + used > m_chunk) {
        throw(std::out_of_range);
        exit(0);
    }

    int tmp = ((count * sizeof(T)) / m_block_size) + 
     (bool)(count * sizeof(T)) % m_block_size);
    T* ret = m_buffer.front();
    while (tmp)
    {
        m_buffer.pop_front();
        --tmp;
        --m_block_count;
    }
    return ret;
}

template <typename T>
void mylib::Pool_alloc<T>::deallocate(int8_t* start, size_t count)
{
    if(start < m_start || start >= end) {
        throw(std::out_of_range);
        exit(0);
    }
    int bytes = count * sizeof(T);
    int8_t* cur = m_buffer.front();
    while (start != cur) {
        cur = m_buffer.front();
        m_buffer.push_front(cur);
        cur += m_block_size;
        ++m_block_count;
    }
}