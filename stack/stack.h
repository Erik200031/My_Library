#ifndef STACK_H
#define STACK_H

#include <type_traits>

#include "../list/list.h"

namespace mylib
{
    template <typename T, typename Container = mylib::list<T>>
    class stack
    {
    public:
        typedef T value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef size_t size_type;
    public:
        stack() : m_cont() {}
        explicit stack(const Container& cont) : m_cont {cont} {}
        explicit stack(Container&& cont) : m_cont {cont} {}
        stack(const stack& rhs) = default;
        stack(stack&& rhs) noexcept = default;
        stack& operator=(const stack& rhs) = default;
        stack& operator=(stack&& rhs) noexcept = default;
        ~stack() = default;
    public:
        reference top() {return m_cont.back();}
        const_reference top() const {return m_cont.back();}
        [[nodiscard]] bool empty() const { return m_cont.empty();} 
        size_type size() const {return m_cont.size();}
        void push(const value_type& value) {m_cont.push_back(value);}
        void push(value_type&& value) {m_cont.push_back(value);}
        template <typename... Args>
        decltype(auto) emplace(Args&&... args) {m_cont.emplace_back(args...);}
        void pop (){m_cont.pop_back();}
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

#endif //STACK_H