

template <class Key, class T,
 class Hash, class KeyEqual>
mylib::unordered_map<Key, T, Hash, KeyEqual>& 
mylib::unordered_map<Key, T, Hash, KeyEqual>::operator=(const unordered_map& rhs)
{

}

template <class Key, class T,
 class Hash, class KeyEqual>
mylib::unordered_map<Key, T, Hash, KeyEqual>& 
mylib::unordered_map<Key, T, Hash, KeyEqual>::operator=(unordered_map&& rhs) noexcept
{
    
}

template <class Key, class T,
 class Hash, class KeyEqual>
[[nodiscard]] bool 
mylib::unordered_map<Key, T, Hash, KeyEqual>::empty() const noexcept
{
    return m_map.empty();
}

template <class Key, class T,
 class Hash, class KeyEqual>
typename mylib::unordered_map<Key, T, Hash, KeyEqual>::size_type 
mylib::unordered_map<Key, T, Hash, KeyEqual>::size() const
{
    return m_size;
}
template <class Key, class T,
 class Hash, class KeyEqual>
typename mylib::unordered_map<Key, T, Hash, KeyEqual>::size_type 
mylib::unordered_map<Key, T, Hash, KeyEqual>::bucket_count() const
{
    return m_map.size();
}

template <class Key, class T,
 class Hash, class KeyEqual>
void mylib::unordered_map<Key, T, Hash, KeyEqual>::insert(value_type&& value)
{
    ++m_size;
    // if(load_factor() > max_load_factor()) {
    //     auto tmp_map = m_map;
    //     m_map.clear();
    // }
    m_map[m_hasher(value.first, bucket_count())].push_front(value);
}

template <class Key, class T,
 class Hash, class KeyEqual>
void mylib::unordered_map<Key, T, Hash, KeyEqual>::insert(const value_type& value)
{
    ++m_size;
    if(load_factor() > max_load_factor()) {
        auto tmp_map = m_map;
        m_map.clear();
    }
    m_map[m_hasher(value.first, bucket_count())].push_front(value);
}

template <class Key, class T,
 class Hash, class KeyEqual>
float mylib::unordered_map<Key, T, Hash, KeyEqual>::load_factor() const
{
    return (m_map.size() / m_size);
}

template <class Key, class T,
 class Hash, class KeyEqual>
float mylib::unordered_map<Key, T, Hash, KeyEqual>::max_load_factor() const
{
    return m_max_load_factor;
}

template <class Key, class T,
 class Hash, class KeyEqual>
T& mylib::unordered_map<Key, T, Hash, KeyEqual>::operator[](Key&& key)
{
    auto& lst = m_map[m_hasher(key, bucket_count())];
    if(lst.empty()) {
        insert(mylib::make_pair(key, T{}));
        return (*this)[std::move(key)];
    }
    if(!lst.empty() && lst.front().first != key) {
        auto it = lst.begin();
        while (it.get() != nullptr && (*it).first != key) {
            ++it;
        }
        if(it == lst.end()) {
            insert(mylib::make_pair(key, T{}));
            return (*this)[std::move(key)];
        }
       return (*it).second;
    }
    return m_map[m_hasher(key, bucket_count())].front().second;
}

template <class Key, class T,
 class Hash, class KeyEqual>
T& mylib::unordered_map<Key, T, Hash, KeyEqual>::operator[](const Key& key)
{
    auto& lst = m_map[m_hasher(key, bucket_count())];
    if(lst.empty()) {
        insert(mylib::make_pair(key, T{}));
        return (*this)[key];
    }
    if(!lst.empty() && lst.front().first != key) {
        auto it = lst.begin();
        while (it.get() != nullptr && (*it).first != key) {
            ++it;
        }
        if(it == lst.end()) {
            insert(mylib::make_pair(key, T{}));
            return (*this)[key];
        }
       return (*it).second;
    }
    return m_map[m_hasher(key, bucket_count())].front().second;
}

template <class Key, class T,
 class Hash, class KeyEqual>
typename mylib::unordered_map<Key, T, Hash, KeyEqual>::Iterator& 
mylib::unordered_map<Key, T, Hash, KeyEqual>::Iterator::operator++()
{
    if(++m_forw_itr) {return m_forw_itr;}
    ++m_rand_itr;
    return (*(m_rand_itr)).begin();
}

template <class Key, class T,
 class Hash, class KeyEqual>
mylib::pair<Key, T>& 
mylib::unordered_map<Key, T, Hash, KeyEqual>::Iterator::operator*()
{
    return Iterator(m_map_ref);
}

template <class Key, class T,
 class Hash, class KeyEqual>
auto& mylib::unordered_map<Key, T, Hash, KeyEqual>::m_pre_incr(size_t index)
{
    // return m_map[index].begin();
}

template <class Key, class T,
 class Hash, class KeyEqual>
void mylib::unordered_map<Key, T, Hash, KeyEqual>::print( ) {
    for (int i = 0; i < m_map.size(); ++i) {
        for (auto &&it : m_map[i]) {
            std::cout << (it).second << " ";
        }
    }
}

template <class Key, class T,
 class Hash, class KeyEqual>
typename mylib::unordered_map<Key, T, Hash, KeyEqual>::Iterator
 mylib::unordered_map<Key, T, Hash, KeyEqual>::begin()
{
    return (m_map[0]).begin();
}

// template <class Key, class T,
//  class Hash, class KeyEqual>
// mylib::unordered_map<Key, T, Hash, KeyEqual>::
// Iterator_helper::Iterator_helper(hash_map& map)
// : m_rand_itr {map.begin()}, m_forw_itr {map[0].begin()} {}
