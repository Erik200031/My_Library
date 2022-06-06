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
    if(current_parent->m_color == BLACK) {
        return;
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
                current->m_parent->m_parent->m_color = RED;
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
                current->m_parent->m_parent->m_color = RED;
                balance(current->m_parent->m_parent);
            }        
        }
        else if(current->m_parent->m_parent->m_value
         > current->m_parent->m_value  
         && (current->m_parent->m_parent->m_right == nullptr
         || current->m_parent->m_parent->m_right->m_color == BLACK)) {
            left_rotate(current->m_parent);
            right_rotate(current);
            current->m_color = BLACK;
            current->m_right->m_color = RED;
            // if(current->m_parent->m_color == RED && current->m_parent != m_root) {
            //     balance(current->m_parent);
            // }
        }
        else if(current->m_parent->m_parent && current->m_parent->m_parent->m_value
         < current->m_parent->m_value  
         && (current->m_parent->m_parent->m_left == nullptr
         || current->m_parent->m_parent->m_left->m_color == BLACK)) {
           right_rotate(current);
           left_rotate(current->m_parent);
            current->m_color = BLACK;
            current->m_left->m_color = RED;
            // if(current->m_parent->m_color == RED && current->m_parent != m_root) {
            //     balance(current->m_parent);
            // }
        } 
        m_root->m_color = BLACK;
    } 
}

template <typename T>
void mylib::rb_tree<T>::left_rotate(node* current)
{
    node* current_right = current->m_right;
    if(current->m_parent && current->m_parent->m_value > current->m_value) {
        current->m_parent->m_left = current_right;
    } else if(current->m_parent && current->m_parent->m_value < current->m_value) {
        current->m_parent->m_right = current_right;
    }
    current_right->m_parent = current_right->m_parent->m_parent;
    current->m_parent = current_right;
    current->m_right = current_right->m_left;
    if(current_right->m_left) {
        current_right->m_left->m_parent = current;
    }
    current_right->m_left = current;
}

template <typename T>
void mylib::rb_tree<T>::right_rotate(node* current)
{
    if(current->m_parent->m_parent) {
        if(current->m_parent->m_parent->m_value > current->m_value) {
            current->m_parent->m_parent->m_left = current;
        } else {
            current->m_parent->m_parent->m_right = current;
        }
    }
    current->m_right = current->m_parent;
    current->m_parent = current->m_parent->m_parent;
    current->m_right->m_parent = current;
    current->m_right->m_left = nullptr;
}

template <typename T>
void mylib::rb_tree<T>::m_print_in_order(node* root) 
{
    if(!root) {
        return;
    }
    m_print_in_order(root->m_left);
    std::cout << "[" << root->m_color << " " <<root->m_value << "] ";
    m_print_in_order(root->m_right);
}

template <typename T>
void mylib::rb_tree<T>::print_in_order() 
{
    m_print_in_order(m_root);
}