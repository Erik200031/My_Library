#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../vector/vector.h"
#include "../algorithm/algorithm.h"

namespace mylib
{
    template <class T, class Container = mylib::vector<T>,
    class Compare = std::less<typename Container::value_type>>
    class priority_queue
    {
    public:
        typedef Container container_type;
        typedef Compare value_compare;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;	
        typedef typename Container::const_reference const_reference;

        priority_queue() : m_cmp{}, m_cont{} {}
        explicit priority_queue(const Compare& compare) 
         : m_cmp {compare}, m_cont{} {}
        priority_queue(const Compare& compare, const Container& cont)
         : m_cmp {compare}, m_cont{cont} 
         {mylib::make_heap(cont.begin(), cont.end());}
        priority_queue(const Compare& compare, Container&& cont)
         : m_cmp {compare}, m_cont{cont} 
         {mylib::make_heap(cont.begin(), cont.end());}
        priority_queue(const priority_queue& rhs) 
         : m_cmp {rhs.m_cmp}, m_cont {rhs.m_cont} {}
        priority_queue(priority_queue&& rhs) noexcept 
         : m_cmp {rhs.m_cmp}, m_cont {rhs.m_cont} {}
        priority_queue& operator=(const priority_queue& rhs);
        priority_queue& operator=(priority_queue&& rhs) noexcept;
        const_reference top() const;
        [[nodiscard]] bool empty() const;
        size_type size() const;
        void push(const value_type& value);
        void push(value_type&& value);
        template <class... Args>
        void emplace(Args&&... args);
        void pop();
        void swap(priority_queue& rhs) noexcept;

    private:
        Compare m_cmp;
        Container m_cont;
    };

} // namespace mylib

#include "priority_queue.hpp"

#endif //PRIORITY_QUEUE_H