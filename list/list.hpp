template <class U>
mylib::list<U>::list() : m_head{}, m_tail{m_head}, m_size{} {}

template <class U>
mylib::list<U>::list(list&& rhs) noexcept : m_head{rhs.m_head}, m_tail{rhs.m_tail}, m_size{rhs.m_size} 
{
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
    rhs.m_size = 0;
}

template <class U>
mylib::list<U>& mylib::list<U>::operator=(const list<U>& rhs) 
{
    if(this == &rhs) {
        return *this;
    }
    if(m_head != nullptr)
        clear();
    Const_Iterator it = rhs.cbegin();
    int i {};
    while(it != rhs.cend()) {
        push_back(rhs[i]);
        ++i;
        ++it;
    }
    return *this;
}

template <class U>
mylib::list<U>::list(const list& rhs)
{
    m_size = rhs.m_size;
    m_head = nullptr;
    m_tail = nullptr;
    for (Const_Iterator it = rhs.cbegin(); it != rhs.cend(); ++it) {
        push_back(*it);
    }
}

template <class U>
mylib::list<U>& mylib::list<U>::operator=(list<U>&& rhs) noexcept 
{
    if(this == &rhs) {
        return *this;
    }
    if(!is_empty()) {
        clear();
    }
    this->m_head = rhs.m_head;
    this->m_tail = rhs.m_tail;
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
    return *this;
}

template <class U>
U& mylib::list<U>::operator[](int index) const 
{
    Node<U>* current  = m_head;
    while(index) {
        current = current->m_next;
        --index;
    }
    return current->m_data;
}

template <class U>
void mylib::list<U>::push_back(const U& element)
{
    if(!m_tail) {
		m_head = m_tail = new Node<U>(element, nullptr, nullptr);
	} else {
		Node<U>* new_node = new Node<U>(element, nullptr, m_tail);
		m_tail->m_next = new_node;
		m_tail = new_node;
	}
    ++m_size;
}

template <class U>
void mylib::list<U>::push_front(const U& element)
{
    if(!m_head) {
		m_head = m_tail = new Node<U>(element, nullptr, nullptr);
	} else {
		Node<U>* new_node = new Node<U>(element, m_head, nullptr);
		m_head = new_node;
        new_node->m_next->m_prev = new_node;
	}
    ++m_size;
}

template <class U>
size_t mylib::list<U>::size() const
{
    return m_size;
}

template <class U>
mylib::list<U>::~list()
{
    if(!is_empty())
    clear();
}

template <class U>
void mylib::list<U>::clear() 
{
    if(!is_empty()) {
        while (m_head)
        {
            this->pop_front();
        }
        m_head = nullptr;
        m_tail = nullptr;
    }
}

template <class U>
bool mylib::list<U>::is_empty() const 
{
    return m_head == nullptr;
}

template <class U>
void mylib::list<U>::pop_front() 
{
    if(m_head == nullptr) {
        return;
    }
    if(m_head->m_next != nullptr) {
        Node<U>* tmp = m_head;
        m_head = tmp->m_next;
        tmp->m_next->m_prev = nullptr;
        delete tmp;
        tmp = nullptr;
    } else if (m_head->m_next == nullptr) {
        delete m_head;
        m_head = nullptr;
    }
}

template <class U>
void mylib::list<U>::pop_back() 
{
    if(m_head == nullptr) {
        return;
    }
    if(m_head->m_next != nullptr) {
        Node<U>* tmp = m_tail;
        m_tail = tmp->m_prev;
        m_tail->m_next = nullptr;
        delete tmp;
        tmp = nullptr;
    } else if (m_head->m_next == nullptr) {
        delete m_head;
        m_head = nullptr;
    }
}

template <class U>
mylib::list<U>::list(size_t count) : m_head {} , m_tail{}
{
    while (count) {
       push_back(U{});
        --count;
    }
}

template <class U>
mylib::list<U>::list(size_t count, const U& element) : m_head {}, m_tail{}
{
    while (count) {
       push_back(element);
        --count;
    }
}

template <class U>
mylib::list<U>::list(std::initializer_list<U> ilist) : m_head {}, m_tail{}
{
    auto cur = ilist.begin();
    while(cur != ilist.end()) {
        push_back(*cur);
        ++cur;
    }
}

template <class U>
typename mylib::list<U>::Iterator mylib::list<U>::insert
(mylib::list<U>::Iterator pos, const U& element) 
{
    if(pos == begin()) {
        push_front(element);
        return begin();
    }
    pos.get()->m_prev->m_next = new Node<U> (element, pos.get(), pos.get()->m_prev);
    pos.get()->m_prev->m_next->m_next->m_prev = pos.get()->m_prev->m_next;
    return --pos;
}

template <class U>
template <class... Args>
typename mylib::list<U>::Iterator mylib::list<U>::emplace
(mylib::list<U>::Iterator pos, Args&&... args) 
{
    if(pos == begin()) {
        push_front(U{args...});
        return begin();
    }
    pos.get()->m_prev->m_next = new Node<U> (U{args...}, pos.get(), pos.get()->m_prev);
    pos.get()->m_prev->m_next->m_next->m_prev = pos.get()->m_prev->m_next;
    return --pos;
}

template <class U>
typename mylib::list<U>::Iterator mylib::list<U>::erase
(mylib::list<U>::Iterator pos) 
{
    if(pos == begin()) {
        pop_front();
        return begin();
    } else if(pos.get()->m_next == nullptr) {
        pop_back();
        return --pos;
    }
    Node<U>* tmp = pos.get();
    pos.get()->m_prev->m_next = pos.get()->m_next;
    pos.get()->m_next->m_prev = pos.get()->m_prev;
    ++pos;
    delete tmp;
    return pos;
}

template <class U>
void mylib::list<U>::swap(list<U>& rhs)
{
    Node<U>* tmp = m_head;
    m_head = rhs.m_head;
    rhs.m_head = tmp;
    tmp = m_tail;
    m_tail = rhs.m_tail;
    rhs.m_tail = tmp;
}

template <class U>
void mylib::list<U>::reverse()
{
    
    
    
}



template <class U>
U& mylib::list<U>::front()
{
    return m_head->m_data;
}

template <class U>
const U& mylib::list<U>::front() const
{
    return m_head->m_data;
}

template <class U>
U& mylib::list<U>::back()
{
    return m_tail->m_data;
}

template <class U>
const U& mylib::list<U>::back() const
{
    return m_tail->m_data;
}

template <class U>
typename mylib::list<U>::Iterator& 
mylib::list<U>::Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::list<U>::Iterator 
mylib::list<U>::Iterator::operator++(int) 
{
    Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
typename mylib::list<U>::Iterator& 
mylib::list<U>::Iterator::operator--() 
{
    it = it->m_prev;
    return (*this);
}

template <class U>
typename mylib::list<U>::Iterator 
mylib::list<U>::Iterator::operator--(int) 
{
    Iterator tmp;
    tmp.it = this->it;
    --(*this);
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Iterator& 
mylib::list<U>::Const_Iterator::operator++() 
{
    it = it->m_next;
    return (*this);
}

template <class U>
typename mylib::list<U>::Const_Iterator 
mylib::list<U>::Const_Iterator::operator++(int) 
{
    Const_Iterator tmp;
    tmp.it = this->it;
    ++(*this);
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Iterator& 
mylib::list<U>::Const_Iterator::operator--() 
{
    it = it->m_prev;
    return (*this);
}

template <class U>
typename mylib::list<U>::Const_Iterator 
mylib::list<U>::Const_Iterator::operator--(int) 
{
    Const_Iterator tmp;
    tmp.it = this->it;
    --(*this);
    return tmp;
}

template <class U>
bool mylib::list<U>::Const_Iterator::operator==(Const_Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::list<U>::Const_Iterator::operator!=(Const_Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::list<U>::Const_Iterator& 
mylib::list<U>::Const_Iterator::operator=(const Const_Iterator& rhs) 
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
typename mylib::list<U>::Const_Iterator& 
mylib::list<U>::Const_Iterator::operator=(Const_Iterator&& rhs) 
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
const U& mylib::list<U>::Const_Iterator::operator*() const
{
    return it->m_data;
}

template <class U>
U* mylib::list<U>::Const_Iterator::operator->()
{
    return &(*it);
}

template <class U>
bool mylib::list<U>::Iterator::operator==(Iterator& rhs)
{
    return (this->it == rhs.it);
}

template <class U>
bool mylib::list<U>::Iterator::operator!=(Iterator& rhs)
{
    return !(this->it == rhs.it);
}

template <class U>
typename mylib::list<U>::Iterator& 
mylib::list<U>::Iterator::operator=(const Iterator& rhs) 
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
typename mylib::list<U>::Iterator& 
mylib::list<U>::Iterator::operator=(Iterator&& rhs) 
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
U& mylib::list<U>::Iterator::operator*() 
{
    return it->m_data;
}

template <class U>
U* mylib::list<U>::Iterator::operator->()
{
    return it;
}

template <class U>
typename mylib::list<U>::Iterator mylib::list<U>::begin()
{
    Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::list<U>::Iterator mylib::list<U>::end()
{
    Iterator tmp;
    tmp.it = m_tail->m_next;
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Iterator mylib::list<U>::cbegin() const 
{
    Const_Iterator tmp;
    tmp.it = m_head;
    return tmp;
}

template <class U>
typename mylib::list<U>::Const_Iterator mylib::list<U>::cend() const 
{
    Const_Iterator tmp;
    tmp.it = m_tail->m_next;
    return tmp;
}