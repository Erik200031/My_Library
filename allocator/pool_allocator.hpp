#include "pool_allocator.h"

template <typename T>
mylib::Pool_alloc<T>::Pool_alloc(size_t big_block_size, size_t little_block_size)
{
    m_block_count = 0;
    m_block_size = little_block_size;
    m_chunk = (big_block_size / little_block_size) * little_block_size;  
    m_free_size = m_chunk;
    m_start = (int8_t*)::operator new(m_chunk);
    m_end = m_start + m_chunk;
    int8_t* tmp = m_start;
    while (tmp != m_end) {
        m_buffer.push_front(tmp);
        tmp += m_block_size;
        ++m_block_count;
    }
}

template <typename T>
typename mylib::Pool_alloc<T>::pointer 
mylib::Pool_alloc<T>::allocate(size_t count)
{
    if(count * sizeof(T) > m_free_size) {
        throw(std::bad_alloc());
        exit(0);
    }
    int tmp = ((count * sizeof(T)) / m_block_size) +
     (bool)((count * sizeof(T)) % m_block_size);
    int8_t* ret = m_buffer.front();
    
    while (tmp >= 0)
    {
        m_buffer.pop_front();
        --tmp;
        --m_block_count;
    }
    m_free_size -= sizeof(T) * count;
    return (T*)ret;
}

template <typename T>
void mylib::Pool_alloc<T>::deallocate(T* in_start, size_t count)
{
    int8_t* start = (int8_t*)in_start;
    if(start < m_start || start >= m_end) {
        throw(std::out_of_range("out of range"));
        exit(0);
    }
    count = (count * sizeof(T)) / m_block_size;
    if(!count) {count = 1;} 

    int8_t* cur = m_buffer.front();
    while (count--)
    {
        m_buffer.push_front(start);
        start += m_block_size;
        ++m_block_count;
    }  
}
