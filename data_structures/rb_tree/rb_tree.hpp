#include "rb_tree.h"

template <typename T>
mylib::rb_tree<T>::rb_tree() : m_root{} {}

template <typename T>
mylib::rb_tree<T>::rb_tree(const rb_tree<T>& rhs) : m_root{} 
{

}

template <typename T>
mylib::rb_tree<T>::rb_tree(rb_tree<T>&& rhs) noexcept : m_root{} 
{
    
}

template <typename T>
mylib::rb_tree<T>& mylib::rb_tree<T>::operator=(const rb_tree<T>& rhs) 
{

}

template <typename T>
mylib::rb_tree<T>& mylib::rb_tree<T>::operator=(rb_tree<T>&& rhs) noexcept
{

}

template <typename T>
bool mylib::rb_tree<T>::empty() const
{
    return m_root == nullptr;
}

template <typename T>
void mylib::rb_tree<T>::insert(const value_type& value)
{
    node* current_parent = nullptr;
    if(empty()) {
        m_root = new node(nullptr, nullptr, nullptr, BLACK, value);
        return;
    }
    node* current = m_root;
    while (current != nullptr)
    {
        current_parent = current;
        if(current && current->m_value > value) {
            current = current->m_left;
        } else if(current && current->m_value < value) {
            current = current->m_right;
        }
    }
    current = new node(current_parent, nullptr, nullptr, RED, value); 
    if(current_parent->m_value < value) {
        current_parent->m_right = current;
    } else {
        current_parent->m_left = current;
    }
    balance(current);
}

template <typename T>
void mylib::rb_tree<T>::balance(node* current)
{
    if(current->m_parent->m_color == RED
     && current->m_parent->m_parent) {
        if(current->m_parent->m_parent->m_value 
         < current->m_parent->m_value
         && current->m_parent->m_parent->m_left
         && current->m_parent->m_parent->m_left->m_color == RED) 
        {
            current->m_parent->m_color = BLACK;
            current->m_parent->m_parent->m_left->m_color = BLACK;
            if(current->m_parent->m_parent != m_root) {
                balance(current->m_parent->m_parent);
            }
        }
        else if(current->m_parent->m_parent->m_value 
         > current->m_parent->m_value
         && current->m_parent->m_parent->m_right
         && current->m_parent->m_parent->m_right->m_color == RED)
        {
            current->m_parent->m_color = BLACK;
            current->m_parent->m_parent->m_right->m_color = BLACK;
            if(current->m_parent->m_parent != m_root) {
                balance(current->m_parent->m_parent);
            }        
        }
    }
     
}

template <typename T>
void mylib::rb_tree<T>::left_rotate(node* current)
{
    node* current_right = current->m_right;
}

template <typename T>
void mylib::rb_tree<T>::m_print_in_order(node* root) 
{
    if(!root) {
        return;
    }
    m_print_in_order(root->m_left);
    std::cout << root->m_value << " ";
    m_print_in_order(root->m_right);
}

template <typename T>
void mylib::rb_tree<T>::print_in_order() 
{
    m_print_in_order(m_root);
}