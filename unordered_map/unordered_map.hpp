

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
mylib::unordered_map<Key, T, Hash, KeyEqual>::size_type 
mylib::unordered_map<Key, T, Hash, KeyEqual>::size() const
{
    return m_size;
}
template <class Key, class T,
 class Hash, class KeyEqual>
mylib::unordered_map<Key, T, Hash, KeyEqual>::size_type 
mylib::unordered_map<Key, T, Hash, KeyEqual>::bucket_count() const
{
    return m_bucket_count;
}

template <class Key, class T,
 class Hash, class KeyEqual>
void mylib::unordered_map<Key, T, Hash, KeyEqual>::insert(value_type&& value)
{
    ++m_size;
    m_map[m_hasher(value.first, m_bucket_count)].push_front(value);
}

template <class Key, class T,
 class Hash, class KeyEqual>
float mylib::unordered_map<Key, T, Hash, KeyEqual>::load_factor() const
{
    
}