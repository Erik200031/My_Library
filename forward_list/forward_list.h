#ifndef FORWARD_LIST_
#define FORWARD_LIST_

#include <iterator>
#include <iostream>
#include <unordered_set>

namespace mylib {

    template <class T>
    class Forward_list;

    template <class T>
    class Node 
    {
    public:
        Node() : m_data{}, m_next{} {}
        Node(const T& data, Node* ptr) : m_data{data}, m_next{ptr} {}
        Node(const Node& rhs) : m_data {rhs.m_data}, m_next{rhs.m_next} {}
        Node(Node && rhs) noexcept = default;
        Node& operator=(const Node& rhs) = default;
        Node& operator=(Node&& rhs) = default;
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
            Iterator(): it{} {}
            Iterator(const Iterator& rhs) : it {rhs.it} {}
            Iterator(Iterator&& rhs) : it {rhs.it} {}
        public:
            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator=(const Iterator& rhs);
            Iterator& operator=(Iterator&& rhs);
            bool operator==(Iterator& rhs);
            bool operator!=(Iterator& rhs);
            U& operator*();
            U* operator->();
            Node<U>*& get() {return it;}
        private:
            friend class Forward_list;
            Node<U>* it;
        };

        class Const_Iterator : public std::iterator<std::forward_iterator_tag, U>
        {
        public:
            Const_Iterator(): it{} {}
            Const_Iterator(const Const_Iterator& rhs) : it {rhs.it} {}
            Const_Iterator(Const_Iterator&& rhs) : it {rhs.it} {}
            Const_Iterator(const Iterator& rhs) : it {rhs.it} {}
            Const_Iterator(Iterator&& rhs) : it {rhs.it} {}
        public:
            Const_Iterator& operator=(const Const_Iterator& rhs);
            Const_Iterator& operator=(Const_Iterator&& rhs);
            bool operator==(Const_Iterator& rhs);
            bool operator!=(Const_Iterator& rhs);
            Const_Iterator& operator++();
            Const_Iterator operator++(int);
            const U& operator*() const;
            U* operator->();
            const Node<U>*& get() const {return it;}
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
        Forward_list(int count, const U& element);
    public:
        void push_front(const U& element);
        U& front();
        const U& front() const;
        bool is_empty() const;
        void pop_front();
        void clear();
        Iterator insert_after(Iterator pos, const U& element);
        Iterator erase_after(Iterator pos);
        void swap(int index1, int index2);
        void sort();
        void reverse();
        mylib::Node<U>* do_reverse(Node<U>* head);
        void merge(Forward_list<U>& rhs);
        bool is_sorted_list() const;
        void unique();
        Iterator begin();
        Iterator end();
        Const_Iterator cbegin() const;
        Const_Iterator cend() const;
        Iterator before_begin() const;

    public:
        bool operator==(const Forward_list<U>& rhs) const;
        bool operator!=(const Forward_list<U>& rhs) const;  
        bool operator<(const Forward_list<U>& rhs) const;      
        bool operator>(const Forward_list<U>& rhs) const;      
        bool operator<=(const Forward_list<U>& rhs) const;      
        bool operator>=(const Forward_list<U>& rhs) const; 
        friend std::ostream& operator<<(std::ostream& os, Forward_list<U>& lst) 
        {
            for(auto it : lst) {
                os << it << " ";
            }
            return os;
        } 

    private:
        U& operator[](int index) const;
        void mergeSort(int begin, int end);
        void merge_for_sort(int left, int mid, int right);
        Node<U>* m_head;
    };
}

#include "forward_list.hpp"

#endif //FORWARD_LIST_