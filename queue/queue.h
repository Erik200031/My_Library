#ifndef QUEUE_H
#define QUEUE_H

#include "../list/list.h"

namespace mylib
{
    template <typename T, typename Container = mylib::list<T>>
    class queue
    {
    public:
        typedef T value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;
        typedef Container container_type;
    public:
        queue() : m_cont() {}
        explicit queue(const Container& cont) : m_cont {cont} {}
        explicit queue(Container&& cont) : m_cont {cont} {}
        queue(const queue& rhs) = default;
        queue(queue&& rhs) noexcept = default;
        queue& operator=(const queue& rhs) = default;
        queue& operator=(queue&& rhs) noexcept = default;
        ~queue() = default;
    public:
        reference front() {return m_cont.front();}
        const_reference front() const {return m_cont.front();}
        reference back() {return m_cont.back();}
        const_reference back() const {return m_cont.back();}
        [[nodiscard]] bool empty() const { return m_cont.empty();} 
        size_type size() const {return m_cont.size();}
        void push(const value_type& value) {m_cont.push_back(value);}
        void push(value_type&& value) {m_cont.push_back(value);}
        template <typename... Args>
        decltype(auto) emplace(Args&&... args) {m_cont.emplace_back(args...);}
        void pop (){m_cont.pop_front();}
        void swap(stack& rhs) noexcept(std::is_nothrow_swappable_v<Container>)
        {
            stack tmp = std::move(*this);
            *this = std::move(rhs);
            rhs = std::move(tmp);
        }
        friend bool operator==(const stack& first, const stack& second) 
        {
            return first.m_cont == second.m_cont;
        }
        friend bool operator!=(const stack& first, const stack& second) 
        {
            return first.m_cont != second.m_cont;
        }
        friend bool operator<(const stack& first, const stack& second) 
        {
            return first.m_cont < second.m_cont;
        }
        friend bool operator>(const stack& first, const stack& second) 
        {
            return first.m_cont > second.m_cont;
        }
        friend bool operator<=(const stack& first, const stack& second) 
        {
            return first.m_cont <= second.m_cont;
        }
        friend bool operator>=(const stack& first, const stack& second) 
        {
            return first.m_cont >= second.m_cont;
        }
    protected:
        Container m_cont;
    };
        
} // namespace mylib

#endif //QUEUE_H