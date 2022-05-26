#ifndef FORWARD_LIST_
#define FORWARD_LIST_

#include <iterator>
#include <iostream>

namespace mylib {
    template <class T>
    class Forward_list;

    template <class T>
    class Node 
    {
    public:
        Node() : m_data{}, m_next{} {}
        Node(const T& data, Node* ptr) : m_data{data}, m_next{ptr} {}
        ~Node() = default;
    private:
        template <class U>
        friend class Forward_list;
        T m_data;
        Node* m_next;
    };

    template <class U>
    class Forward_list
    {
    public:
        typedef U value_type;
        typedef size_t size_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;

    public:
        class Iterator : public std::iterator<std::forward_iterator_tag, U>
        {
        public:
            Iterator(): it{m_head} {}
            Iterator(const Iterator& rhs) : it {rhs.it} {}
            Iterator(Iterator&& rhs) : it {rhs.it} {}
        public:
            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator=(const Iterator& rhs);
            Iterator& operator=(Iterator&& rhs);
            bool operator==(const Iterator& rhs);
            bool operator!=(const Iterator& rhs);
            U& operator*();
            U* operator->();
        private:
            friend class Forward_list;
            Node<U>* it;
        };

        class Const_Iterator : public std::iterator<std::forward_iterator_tag, U>
        {
        public:
            Const_Iterator(): it{m_head} {}
            Const_Iterator(const Const_Iterator& rhs) : it {rhs.it} {}
            Const_Iterator(Const_Iterator&& rhs) : it {rhs.it} {}
            Const_Iterator(const Iterator& rhs) : it {rhs.it} {}
            Const_Iterator(Iterator&& rhs) : it {rhs.it} {}
        public:
            Const_Iterator& operator=(const Const_Iterator& rhs);
            Const_Iterator& operator=(Const_Iterator&& rhs);
            bool operator==(const Const_Iterator& rhs);
            bool operator!=(const Const_Iterator& rhs);
            Const_Iterator& operator++();
            Const_Iterator operator++(int);
            const U& operator*() const;
            U* operator->();
        private:
            friend class Forward_list;
            const Node<U>* it;
        };

    public:
        Forward_list();
        ~Forward_list();
        Forward_list(const Forward_list&);
        Forward_list(Forward_list&&) noexcept;
        Forward_list& operator=(const Forward_list&);
        Forward_list& operator=(Forward_list&&) noexcept;
        Forward_list(int count);

    public:
        void push_front(const U& element);
        U& front();
        const U& front() const;
        bool is_empty() const;
        void pop_front();
        void clear();
        Iterator insert_after(Const_Iterator pos, const U& element);
        Iterator erase_after(Const_Iterator pos);
        //void swap(int index1, int index2);
        //void sort();
        void reverse();
        //void merge(const Forward_list<U>&);
        Iterator begin() const;
        Iterator end() const;
        Const_Iterator cbegin() const;
        Const_Iterator cend() const;
        Iterator befor_begin() const;

    public:
        bool operator==(const Forward_list<U>& rhs) const;
        bool operator!=(const Forward_list<U>& rhs) const;  
        bool operator<(const Forward_list<U>& rhs) const;      
        bool operator>(const Forward_list<U>& rhs) const;      
        bool operator<=(const Forward_list<U>& rhs) const;      
        bool operator>=(const Forward_list<U>& rhs) const; 
        friend std::ostream& operator<<(std::ostream& os, const Forward_list<U>& lst) {
            for(int i {}; i < lst.size(); ++i) {
                os << lst[i] << " ";
            }
            return os;
        } 

    private:
        U& operator[](int index) const;
        Node<U>* m_head;
    };
}

#include "forward_list.hpp"

#endif //FORWARD_LIST_