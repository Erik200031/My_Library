template <class U>
mylib::forward_list<U>::forward_list() : m_head{} {}

template <class U>
mylib::forward_list<U>::~forward_list()
{
    if(!empty())
    clear();
}

template <class U>
void mylib::forward_list<U>::push_front(const U& element)
{
    m_head = new Node(element, m_head);
}

template <class U>
U& mylib::forward_list<U>::front()
{
    return m_head->m_data;
}

template <class U>
const U& mylib::forward_list<U>::front() const
{
    return m_head->m_data;
}

template <class U>
bool mylib::forward_list<U>::empty() const 
{
    return m_head == nullptr;
}

template <class U>
void mylib::forward_list<U>::pop_front() 
{
    if(m_head == nullptr) {
        return;
    }
    if(m_head->m_next != nullptr) {
        Node<U>* tmp = m_head;
        m_head = m_head->m_next;
        delete tmp;
        tmp = nullptr;
    } else if (m_head->m_next == nullptr) {
        delete m_head;
        m_head = nullptr;
    }
}

template <class U>
mylib::forward_list<U>::forward_list(int count) : m_head {}
{
    while (count)
    {
       push_front(U{});
        --count;
    }
}

template <class U>
mylib::forward_list<U>::forward_list(int count, const U& element) : m_head {}
{
    while (count)
    {
       push_front(element);
        --count;
    }
}

template <class U>
mylib::forward_list<U>::forward_list(std::initializer_list<U> ilist)
{
        m_head = nullptr;

    auto cur = ilist.begin();
    while(cur != ilist.end()) {
        push_front(*cur);
        ++cur;
    }
    reverse();
}

template <class U>
U& mylib::forward_list<U>::operator[](int index) const 
{
    Node<U>* current  = m_head;
    while(index) {
        current = current->m_next;
        --index;
    }
    return current->m_data;
}

template <class U>
void mylib::forward_list<U>::clear() 
{
    if(!empty()) {
        while (m_head)
        {
            this->pop_front();
        }
    }
}

template <class U>
mylib::forward_list<U>::forward_list(const forward_list& rhs)
{
    m_head = nullptr;
    for (Const_Iterator it = rhs.cbegin(); it != rhs.cend(); ++it)
    {
        push_front(*it);
    }
    reverse();
}

template <class U>
mylib::forward_list<U>::forward_list(forward_list&& rhs) noexcept 
{
    m_head = rhs.m_head;
    rhs.m_head = nullptr;
}

template <class U>
mylib::forward_list<U>& mylib::forward_list<U>::operator=(const forward_list<U>& rhs) 
{
    if(this == &rhs) {
        return *this;
    }
    if(m_head != nullptr)
    clear();
    Const_Iterator it = rhs.cbegin();
    int i {};
    while(it != rhs.cend()) {
        this->push_front(rhs[i]);
        ++i;
        ++it;
    }
    return *this;
}

template <class U>
mylib::forward_list<U>& mylib::forward_list<U>::operator=(forward_list<U>&& rhs) noexcept 
{
    if(this == &rhs) {
        return *this;
    }
    if(!empty())
        clear();
    this->m_head = rhs.m_head;
    rhs.m_head = nullptr;
    return *this;
}

template <class U>
typename mylib::forward_list<U>::Iterator mylib::forward_list<U>::insert_after
(mylib::forward_list<U>::Iterator pos, const U& element) 
{
    if(pos == before_begin()) {
        push_front(element);
        return begin();
    }
    pos.get()->m_next = new Node<U> (element, pos.get()->m_next);
    return pos++;
}

template <class U>
template <class... Args>
typename mylib::forward_list<U>::Iterator mylib::forward_list<U>::emplace_after
(mylib::forward_list<U>::Iterator pos, Args&&... args) 
{
    if (pos == before_begin()) {
        push_front(U{args...});
        return begin();
    }
    pos.get()->m_next = new Node<U> (U{args...}, pos.get()->m_next);
    return pos++;
}

template <class U>
void mylib::forward_list<U>::assign(size_t count, const U& element)
{
    if(m_head != nullptr) {
        clear();
    }
    while (count) {
       push_front(element);
        --count;
    }
}

template <class U>
template <typename InputIter>
void mylib::forward_list<U>::assign(InputIter first, InputIter last)
{
    if(first >= last) {
        return;
    }
    if(m_head != nullptr) {
        clear();
    }
    InputIter& cur = first;
    while(cur != last) {
        push_front(*first);
        ++cur;
    }
    reverse();
}

template <class U>
void mylib::forward_list<U>::assign(std::initializer_list<U> ilist)
{
    if(m_head != nullptr) {
        clear();
    }
    auto cur = ilist.begin();
    while(cur != ilist.end()) {
        push_front(*cur);
        ++cur;
    }
    reverse();
}

template <class U>
typename mylib::forward_list<U>::Iterator mylib::forward_list<U>::erase_after
(mylib::forward_list<U>::Iterator pos) 
{
    if(pos == before_begin()) {
        pop_front();
        return begin();
    }
    Node<U>* tmp = pos.get()->m_next;
    pos.get()->m_next = tmp->m_next;
    delete tmp;
    return ++pos;
}

template <class U>
void mylib::forward_list<U>::swap(int index1, int index2)
{
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

template <class U>
void mylib::forward_list<U>::merge_for_sort(int left, int mid, int right)
{
    int  sub_list_one = mid - left + 1;
    int  sub_list_two = right - mid;
    mylib::forward_list<U> left_list(sub_list_one);
    mylib::forward_list<U> right_list(sub_list_two);
    for (auto i = 0; i < sub_list_one; i++)
        left_list[i] = (*this)[left + i];
    for (auto j = 0; j < sub_list_two; j++)
        right_list[j] = (*this)[mid + 1 + j];
    int index_of_sub_list_one = 0;
    int index_of_sub_list_two = 0;
    int index_of_merged = left; 
    while (index_of_sub_list_one < sub_list_one && index_of_sub_list_two < sub_list_two) {
        if (left_list[index_of_sub_list_one] <= right_list[index_of_sub_list_two]) {
            (*this)[index_of_merged] = left_list[index_of_sub_list_one];
            index_of_sub_list_one++;
        }
        else {
            (*this)[index_of_merged] = right_list[index_of_sub_list_two];
            index_of_sub_list_two++;
        }
        index_of_merged++;
    }
    while (index_of_sub_list_one < sub_list_one) {
        (*this)[index_of_merged] = left_list[index_of_sub_list_one];
        index_of_sub_list_one++;
        index_of_merged++;
    }
    while (index_of_sub_list_two < sub_list_two) {
        (*this)[index_of_merged] = right_list[index_of_sub_list_two];
        index_of_sub_list_two++;
        index_of_merged++;
    }
} 

template <class U>
bool mylib::forward_list<U>::is_sorted_list() const
{
    Node<U>* cur = m_head;
    Node<U>* after_cur = cur->m_next;
    while(cur != nullptr && cur->m_next != nullptr && after_cur->m_next != nullptr) {
        if(cur->m_data > after_cur->m_data) {
            return false;
        }
        cur = cur->m_next;
        after_cur = after_cur->m_next;
    }
    return true;
}

template <class U>
void mylib::forward_list<U>::mergeSort(int begin, int end)
{
    if (begin >= end)
        return;
  
    auto mid = begin + (end - begin) / 2;
    mergeSort(begin, mid);
    mergeSort(mid + 1, end);
    merge_for_sort(begin, mid, end);
}

template <class U>
void mylib::forward_list<U>::sort()
{
    int end {};
    for(auto it: *this) {
        ++end;
    }
    
    mergeSort(0, end - 1);
}

template <class U>
mylib::Node<U>* mylib::forward_list<U>::do_reverse(mylib::Node<U>* head) 
{
    if (head == nullptr || head->m_next == nullptr)
        return head;
    Node<U>* tmp = do_reverse(head->m_next);
    head->m_next->m_next = head;
    head->m_next = nullptr;
    return tmp;
}

template <class U>
void mylib::forward_list<U>::reverse()
{
    m_head =  do_reverse(m_head);
}

template <class U>
void mylib::forward_list<U>::merge(forward_list<U>& rhs) 
{
    if(is_sorted_list() && rhs.is_sorted_list()) {
        Node<U>* cur = m_head;
        while(cur != nullptr && cur->m_next != nullptr) {
            cur = cur->m_next;
        }
        cur->m_next = rhs.m_head;
        sort();
    } else {
        std::cout << "These lists are not sorted!\n";
    }
}

template <class U>
typename mylib::forward_list<U>::Iterator mylib::forward_list<U>::begin()
{
    Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::forward_list<U>::Const_Iterator mylib::forward_list<U>::cbegin() const 
{
    Const_Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::forward_list<U>::Iterator mylib::forward_list<U>::before_begin() const 
{
    Iterator tmp;
    tmp.it = m_head - 1;
    return tmp;
}

template <class U>
typename mylib::forward_list<U>::Iterator mylib::forward_list<U>::end()
{
    Iterator tmp;
    tmp.it = m_head;
    while(tmp.it != nullptr) {
       ++tmp;
    }
    return tmp;
}

template <class U>
typename mylib::forward_list<U>::Const_Iterator mylib::forward_list<U>::cend() const 
{
    Const_Iterator tmp;
    tmp.it = m_head;
    while(tmp.it != nullptr) {
       ++tmp;
    }
    return tmp;
}

template <class U>
bool mylib::forward_list<U>::operator==(const mylib::forward_list<U>& rhs) const 
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
bool mylib::forward_list<U>::operator!=(const mylib::forward_list<U>& rhs) const 
{
    return !(*this == rhs);
}

template <class U>
bool mylib::forward_list<U>::operator<(const mylib::forward_list<U>& rhs) const 
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
bool mylib::forward_list<U>::operator>(const mylib::forward_list<U>& rhs) const 
{
    return !(*this <= rhs);
}

template <class U>
bool mylib::forward_list<U>::operator<=(const mylib::forward_list<U>& rhs) const 
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
bool mylib::forward_list<U>::operator>=(const mylib::forward_list<U>& rhs) const 
{
    return !(*this < rhs);
}

template <class U>
typename mylib::forward_list<U>::Iterator& 
mylib::forward_list<U>::Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::forward_list<U>::Iterator 
mylib::forward_list<U>::Iterator::operator++(int) 
{
    Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
bool mylib::forward_list<U>::Iterator::operator==(Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::forward_list<U>::Iterator::operator!=(Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::forward_list<U>::Iterator& 
mylib::forward_list<U>::Iterator::operator=(const Iterator& rhs) 
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
typename mylib::forward_list<U>::Iterator& 
mylib::forward_list<U>::Iterator::operator=(Iterator&& rhs) 
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
U& mylib::forward_list<U>::Iterator::operator*() 
{
    return it->m_data;
}

template <class U>
U* mylib::forward_list<U>::Iterator::operator->()
{
    return it;
}

template <class U>
typename mylib::forward_list<U>::Const_Iterator&
mylib::forward_list<U>::Const_Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::forward_list<U>::Const_Iterator 
mylib::forward_list<U>::Const_Iterator::operator++(int) 
{
    Const_Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
bool mylib::forward_list<U>::Const_Iterator::operator==(Const_Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::forward_list<U>::Const_Iterator::operator!=(Const_Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::forward_list<U>::Const_Iterator& 
mylib::forward_list<U>::Const_Iterator::operator=(const Const_Iterator& rhs) 
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
typename mylib::forward_list<U>::Const_Iterator& 
mylib::forward_list<U>::Const_Iterator::operator=(Const_Iterator&& rhs) 
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
const U& mylib::forward_list<U>::Const_Iterator::operator*() const
{
    return it->m_data;
}

template <class U>
U* mylib::forward_list<U>::Const_Iterator::operator->()
{
    return &(*it);
}

template <class U>
size_t mylib::forward_list<U>::unique()
{
    size_t count = -1;
    if(m_head == nullptr) {
        return count;
    }
    count = 0;
    Iterator j = begin();
    ++j;
    for(Iterator i = begin(); j != end();) {
        if(*i == *j) {
            erase_after(i);
            ++count;
            ++j;
            continue;
        }
        ++i;
        ++j;  
    }
    return count;
}