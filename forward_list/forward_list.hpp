template <class U>
mylib::Forward_list<U>::Forward_list() : m_head{} {}

template <class U>
mylib::Forward_list<U>::~Forward_list()
{
    clear();
}

template <class U>
void mylib::Forward_list<U>::push_front(const U& element)
{
    m_head = new Node(element, m_head);
}

template <class U>
U& mylib::Forward_list<U>::front()
{
    return m_head->m_data;
}

template <class U>
const U& mylib::Forward_list<U>::front() const
{
    return m_head->m_data;
}

template <class U>
bool mylib::Forward_list<U>::is_empty() const 
{
    return m_head == nullptr;
}

template <class U>
void mylib::Forward_list<U>::pop_front() 
{
    if(m_head == nullptr) {
        return;
    }
    if(m_head->m_next != nullptr) {
        Node<U>* tmp = m_head;
        m_head = m_head->m_next;
        delete tmp;
    } else if (m_head->m_next == nullptr) {
        delete m_head;
        m_head = nullptr;
    }
}

template <class U>
mylib::Forward_list<U>::Forward_list(int count) : m_head {}
{
    while (count)
    {
       push_front(U{});
        --count;
    }
}

template <class U>
U& mylib::Forward_list<U>::operator[](int index) const 
{
    Node<U>* current  = m_head;
    while(index) {
        current = current->m_next;
        --index;
    }
    return current->m_data;
}

template <class U>
void mylib::Forward_list<U>::clear() 
{
    if(is_empty()) {
        while (m_head->m_next)
        {
            this->pop_front();
        }
    }
}

template <class U>
mylib::Forward_list<U>::Forward_list(const Forward_list& rhs)
{
    Iterator it = begin();
    int i{};
    while(it != end()) {
        this->push_front(rhs[i]);
        ++i;
    }
}

template <class U>
mylib::Forward_list<U>::Forward_list(Forward_list&& rhs) noexcept 
{
    m_head = rhs.m_head;
    rhs.m_head = nullptr;
}

template <class U>
mylib::Forward_list<U>& mylib::Forward_list<U>::operator=(const Forward_list<U>& rhs) 
{
    if(this == &rhs) {
        return *this;
    }
    clear();
    Iterator it = begin();
    int i{};
    while(it != end()) {
        this->push_front(rhs[i]);
        ++i;
    }
    return *this;
}

template <class U>
mylib::Forward_list<U>& mylib::Forward_list<U>::operator=(Forward_list<U>&& rhs) noexcept 
{
    if(this == &rhs) {
        return *this;
    }
    clear();
    this->m_head = rhs.m_head;
    rhs.m_head = nullptr;
    return *this;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::insert_after
(mylib::Forward_list<U>::Const_Iterator pos, const U& element) 
{
    if(pos == befor_begin()) {
        push_front(element);
        return begin();
    } else {
        pos->m_next = new Node<U> (element, pos->m_next);
    }
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::erase_after
(mylib::Forward_list<U>::Const_Iterator pos) 
{
    if(pos == befor_begin()) {
        pop_front();
        return begin();
    } else {
        Node<U>* tmp = pos.it->next;
        pos.it->m_next = tmp->m_next;
        delete tmp;
        return pos.it->next;
    }
}

// template <class U>
// void mylib::Forward_list<U>::swap(int index1, int index2) // change
// {
//     if(index1 != index2 && (index1 >= 0 && index1 < m_size) && (index2 >= 0 && index2 < m_size)) {
//         Node<U>* cur_1 = m_head;
//         Node<U>* cur_2 = m_head;
//         while(index1) {
//             cur_1 = cur_1->m_next;
//             --index1;
//         }
//         while(index2) {
//             cur_2 = cur_2->m_next;
//             --index2;
//         }
//         U tmp = std::move(cur_1->m_data);
//         cur_1->m_data = std::move(cur_2->m_data);
//         cur_2->m_data = std::move(tmp);
//     }
// }

// template <class U>
// void mylib::Forward_list<U>::sort() //change
// {
//     //Bubble sort

//     for (int i {}; i < m_size-1; i++){     
//         for (int j {}; j < m_size-i-1; j++) {
//             if ((*this)[j] > (*this)[j+1]) {
//                 swap(j, j+1);
//             }
//         } 
//     }
// } 

// template <class U>
// void mylib::Forward_list<U>::reverse() 
// {
//     if(m_size <= 1) {
//         return;
//     }
//     else if(m_size == 2) {
//         swap(0,1);
//         return;
//     }
//     int start_pos = m_size-1;
//     Node<U>* start = m_head;
//     Node<U>* cur_1 = m_head;
//     Node<U>* cur_2 = m_head;
//     int tmp_size = m_size-1;
//     int tmp_index = m_size-1;
//     int tmp_index1 = tmp_index-1;

//     while(start_pos) {
//         start = start->m_next;
//         --start_pos;
//     }
//     while(tmp_size) {
//         int tmp_tmp_index = tmp_index;
//         int tmp_tmp_index1 = tmp_index1;
//         cur_2 = m_head;
//         cur_1 = m_head;
//         while(tmp_tmp_index){
//             cur_1 = cur_1->m_next;
//             --tmp_tmp_index;
//         }
//         while(tmp_tmp_index1){
//             cur_2 = cur_2->m_next;
//             --tmp_tmp_index1;
//         }
//         cur_1->m_next = cur_2;
//         tmp_index--;
//         tmp_index1--;
//         --tmp_size;        
//     }
//     cur_2->m_next = nullptr;
//     m_head = start;
// }

template <class U>
void mylib::Forward_list<U>::reverse() 
{

}

// template <class U>
// void mylib::Forward_list<U>::merge(const Forward_list<U>& rhs) 
// {
    
//     for(int i{}; i < rhs.m_size; i++) {
//         push_front(rhs[i]);
//     }
//     sort();    
// }

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::begin() const 
{
    Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator mylib::Forward_list<U>::cbegin() const 
{
    Const_Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::befor_begin() const 
{
    Iterator tmp;
    tmp.it = m_head - 1;
    return tmp;
}

template <class U>
typename mylib::Forward_list<U>::Iterator mylib::Forward_list<U>::end() const 
{
    Iterator tmp;
    tmp.it = m_head;
    while(tmp.it != nullptr) {
       ++tmp;
    }
    return tmp;
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator mylib::Forward_list<U>::cend() const 
{
    Const_Iterator tmp;
    tmp.it = m_head;
    while(tmp.it != nullptr) {
       ++tmp;
    }
    return tmp;
}

template <class U>
bool mylib::Forward_list<U>::operator==(const mylib::Forward_list<U>& rhs) const 
{
    Const_Iterator it = cbegin();
    int i{};
    while(it != cend()) {
        if(*this[i] != rhs[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

template <class U>
bool mylib::Forward_list<U>::operator!=(const mylib::Forward_list<U>& rhs) const 
{
    return !(*this == rhs);
}

template <class U>
bool mylib::Forward_list<U>::operator<(const mylib::Forward_list<U>& rhs) const 
{
   Const_Iterator it = cbegin();
    int i{};
    while(it != cend()) {
        if(*this[i] > rhs[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

template <class U>
bool mylib::Forward_list<U>::operator>(const mylib::Forward_list<U>& rhs) const 
{
    return !(*this <= rhs);
}

template <class U>
bool mylib::Forward_list<U>::operator<=(const mylib::Forward_list<U>& rhs) const 
{
    Const_Iterator it = cbegin();
    int i{};
    while(it != cend()) {
        if(*this[i] >= rhs[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

template <class U>
bool mylib::Forward_list<U>::operator>=(const mylib::Forward_list<U>& rhs) const 
{
    return !(*this < rhs);
}

template <class U>
typename mylib::Forward_list<U>::Iterator& 
mylib::Forward_list<U>::Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::Forward_list<U>::Iterator 
mylib::Forward_list<U>::Iterator::operator++(int) 
{
    Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
bool mylib::Forward_list<U>::Iterator::operator==(Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::Forward_list<U>::Iterator::operator!=(Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::Forward_list<U>::Iterator& 
mylib::Forward_list<U>::Iterator::operator=(const Iterator& rhs) 
{
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
typename mylib::Forward_list<U>::Iterator& 
mylib::Forward_list<U>::Iterator::operator=(Iterator&& rhs) 
{
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
U& mylib::Forward_list<U>::Iterator::operator*() 
{
    return it->m_data;
}

template <class U>
U* mylib::Forward_list<U>::Iterator::operator->()
{
    return &(*it);
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator&
mylib::Forward_list<U>::Const_Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator 
mylib::Forward_list<U>::Const_Iterator::operator++(int) 
{
    Const_Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
bool mylib::Forward_list<U>::Const_Iterator::operator==(Const_Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::Forward_list<U>::Const_Iterator::operator!=(Const_Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::Forward_list<U>::Const_Iterator& 
mylib::Forward_list<U>::Const_Iterator::operator=(const Const_Iterator& rhs) 
{
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
typename mylib::Forward_list<U>::Const_Iterator& 
mylib::Forward_list<U>::Const_Iterator::operator=(Const_Iterator&& rhs) 
{
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
const U& mylib::Forward_list<U>::Const_Iterator::operator*() const
{
    return it->m_data;
}

template <class U>
U* mylib::Forward_list<U>::Const_Iterator::operator->()
{
    return &(*it);
}