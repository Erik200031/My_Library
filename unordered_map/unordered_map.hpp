

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
void mylib::unordered_map<Key, T, Hash, KeyEqual>::insert(const value_type& value)
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
T& mylib::unordered_map<Key, T, Hash, KeyEqual>::operator[](const Key& key)
{
    auto& lst = m_map[m_hasher(key, bucket_count())];
    if(!lst.empty() && lst.front().first != key) {
        auto it = lst.begin();
        while (it.get() != nullptr && (*it).first != key) {
            ++it;
        }
        if(it == lst.end()) {
            std::cout << "D\n";
            insert(mylib::make_pair(key, T{}));
            return (*this)[std::move(key)];
        }
       return (*it).second;
    }
    return m_map[m_hasher(key, bucket_count())].front().second;
}
