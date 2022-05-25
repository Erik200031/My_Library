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
        class Iterator : public std::iterator<std::forward_iterator_tag, U>
        {
        public:
        Iterator(): it{} {}
        public:
            Iterator& operator++();      //prefix 
            Iterator operator++(int);   //postfix
            Iterator& operator=(const Iterator& rhs);
            U& operator*() const;
        private:
            friend class Forward_list;
            Node<U>* it;
        };

    public:
        Forward_list();
        ~Forward_list();
        Forward_list(const Forward_list&);
        Forward_list(Forward_list&&) noexcept;
        Forward_list& operator=(const Forward_list&);
        Forward_list& operator=(Forward_list&&) noexcept;

    public:
        void push_front(const U& element);
        U& front();
        const U& front() const;
        bool is_empty() const;
        void pop_front();
        void clear();
        void insert_after(int pos, const U& element);
        void erase_after(int pos);
        void swap(int index1, int index2);
        void sort();
        void reverse();
        int size() const;
        void merge(const Forward_list<U>&);
        Iterator begin() const;
        Iterator end() const;

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
        int m_size;
    };
}

template <class U>
mylib::Forward_list<U>::Forward_list() : m_size{}, m_head{} {}

template <class U>
mylib::Forward_list<U>::~Forward_list()
{
    clear();
}

template <class U>
void mylib::Forward_list<U>::push_front(const U& element)
{
    m_head = new Node(element, m_head);
    ++m_size;
}

template <class U>
U& mylib::Forward_list<U>::front() {
    return m_head->m_data;
}

template <class U>
const U& mylib::Forward_list<U>::front() const {
    return m_head->m_data;
}

template <class U>
bool mylib::Forward_list<U>::is_empty() const {
    return !m_size;
}

template <class U>
void mylib::Forward_list<U>::pop_front() {
    Node<U>* tmp = m_head;
    m_head = m_head->m_next;
    delete tmp;
    --m_size;
}

template <class U>
U& mylib::Forward_list<U>::operator[](int index) const {
    Node<U>* current  = m_head;
    while(index) {
        current = current->m_next;
        --index;
    }
    return current->m_data;
}

template <class U>
void mylib::Forward_list<U>::clear() {
    while (m_size)
    {
        this->pop_front();
    }
}

template <class U>
mylib::Forward_list<U>::Forward_list(const Forward_list& rhs) : m_size {} {
    for (int i = rhs.m_size-1; i >= 0 ; i--)
    {
        this->push_front(rhs[i]);
    }
}

template <class U>
mylib::Forward_list<U>::Forward_list(Forward_list&& rhs) noexcept : m_size {} {
    m_head = rhs.m_head;
    rhs.m_head = nullptr;
}

template <class U>
mylib::Forward_list<U>& mylib::Forward_list<U>::operator=(const Forward_list<U>& rhs) {
    if(this == &rhs) {
        return *this;
    }
    clear();
    for (int i = rhs.m_size-1; i >= 0 ; i--)
    {
        this->push_front(rhs[i]);
    }
    return *this;
}

template <class U>
mylib::Forward_list<U>& mylib::Forward_list<U>::operator=(Forward_list<U>&& rhs) noexcept {
    if(this == &rhs) {
        return *this;
    }
    clear();
    this->m_size = rhs.m_size;
    rhs.m_size = 0;
    this->m_head = rhs.m_head;
    rhs.m_head = nullptr;
    return *this;
}

template <class U>
void mylib::Forward_list<U>::insert_after(int pos, const U& element) {
    if(pos == 0) {
        push_front(element);
        return;
    }
    else if(pos > 0 && pos <= m_size) {
        Node<U>* current = m_head;
        while(pos-1 != 0) {
            current = current->m_next;
            --pos;
        }
        current->m_next = new Node<U> (element, current->m_next);
        ++m_size;
    }
}

template <class U>
void mylib::Forward_list<U>::erase_after(int pos) {
    if(pos == 0) {
        pop_front();
    }
    else if(pos > 0 && pos < m_size) {
        Node<U>* current = m_head;
        while(pos-1 != 0) {
            current = current->m_next;
            --pos;
        }
        if(current->m_next->m_next != nullptr) {
            Node<U>* tmp = current->m_next->m_next;
            delete current->m_next;
            current->m_next = tmp;
            --m_size;
        }
        else if(current->m_next->m_next == nullptr) {
            delete current->m_next;
            current->m_next = nullptr;
            --m_size;
        }
    }
}

template <class U>
void mylib::Forward_list<U>::swap(int index1, int index2) {
    if(index1 != index2 && (index1 >= 0 && index1 < m_size) && (index2 >= 0 && index2 < m_size)) {
        Node<U>* cur_1 = m_head;
        Node<U>* cur_2 = m_head;
        while(index1) {
            cur_1 = cur_1->m_next;
            --index1;
        }
        while(index2) {
            cur_2 = cur_2->m_next;
            --index2;
        }
        U tmp = std::move(cur_1->m_data);
        cur_1->m_data = std::move(cur_2->m_data);
        cur_2->m_data = std::move(tmp);
    }
}

template <class U>
void mylib::Forward_list<U>::sort()
{
    //Bubble sort

    for (int i {}; i < m_size-1; i++){     
        for (int j {}; j < m_size-i-1; j++) {
            if ((*this)[j] > (*this)[j+1]) {
                swap(j, j+1);
            }
        } 
    }
} 

template <class U>
void mylib::Forward_list<U>::reverse() {
    if(m_size <= 1) {
        return;
    }
    else if(m_size == 2) {
        swap(0,1);
        return;
    }
    int start_pos = m_size-1;
    Node<U>* start = m_head;
    Node<U>* cur_1 = m_head;
    Node<U>* cur_2 = m_head;
    int tmp_size = m_size-1;
    int tmp_index = m_size-1;
    int tmp_index1 = tmp_index-1;

    while(start_pos) {
        start = start->m_next;
        --start_pos;
    }
    while(tmp_size) {
        int tmp_tmp_index = tmp_index;
        int tmp_tmp_index1 = tmp_index1;
        cur_2 = m_head;
        cur_1 = m_head;
        while(tmp_tmp_index){
            cur_1 = cur_1->m_next;
            --tmp_tmp_index;
        }
        while(tmp_tmp_index1){
            cur_2 = cur_2->m_next;
            --tmp_tmp_index1;
        }
        cur_1->m_next = cur_2;
        tmp_index--;
        tmp_index1--;
        --tmp_size;        
    }
    cur_2->m_next = nullptr;
    m_head = start;
}

template <class U>
int mylib::Forward_list<U>::size() const {
    return m_size;
}

template <class U>
void mylib::Forward_list<U>::merge(const Forward_list<U>& rhs) {
    
    for(int i{}; i < rhs.m_size; i++) {
        push_front(rhs[i]);
    }
    sort();    
}

template <class U>
typename mylib::Forward_list<U>::Iterator& mylib::Forward_list<U>::Iterator::operator++() {
    if(it->m_next != nullptr) {
        it = it->m_next;
        return (*this);
    }
    std::cout << "Out of range";
    return *this;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::Iterator::operator++(int) {
    if(it->m_next != nullptr) {
        Iterator tmp;
        tmp.it = this->it;
        ++(*this);
        return tmp;
    }
    return *this;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::begin() const {
    Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::end() const {
    Iterator tmp;
    tmp.it = m_head;
    int tmp_size = m_size-1;
    while(tmp_size) {
       tmp++;
       --tmp_size;
    }
    return tmp;
}

template <class U>
typename mylib::Forward_list<U>::Iterator& mylib::Forward_list<U>::Iterator::operator=(const Iterator& rhs) {
    if(this == &rhs) {
        return *this;
    }
    if(this != nullptr) {
        delete this;
    }
    this->it = rhs.it;
    return *this;
}

template <class U>
U& mylib::Forward_list<U>::Iterator::operator*() const {
    return it->m_data;
}

template <class U>
bool mylib::Forward_list<U>::operator==(const mylib::Forward_list<U>& rhs) const {
    if(size() != rhs.size()) {
        return false;
    }   
    for(int i {}; i < size(); ++i) {
        if(*this[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template <class U>
bool mylib::Forward_list<U>::operator!=(const mylib::Forward_list<U>& rhs) const {
    return !(*this == rhs);
}

template <class U>
bool mylib::Forward_list<U>::operator<(const mylib::Forward_list<U>& rhs) const {
    if(size() < rhs.size()) {
        return true;
    }
    for(int i {}; i < size(); ++i) {
        if(*this[i] > rhs[i]) {
            return false;
        }
    }
    return true;
}

template <class U>
bool mylib::Forward_list<U>::operator>(const mylib::Forward_list<U>& rhs) const {
    return !(*this <= rhs);
}

template <class U>
bool mylib::Forward_list<U>::operator<=(const mylib::Forward_list<U>& rhs) const {
    if(size() <= rhs.size()) {
        return true;
    }
    for(int i {}; i < size(); ++i) {
        if(*this[i] >= rhs[i]) {
            return false;
        }
    }
    return true;
}

template <class U>
bool mylib::Forward_list<U>::operator>=(const mylib::Forward_list<U>& rhs) const {
    return !(*this < rhs);
}

#endif //FORWARD_LIST_