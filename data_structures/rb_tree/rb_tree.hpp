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
    if(current->m_parent && current->m_parent->m_color == RED) {
        if(current->m_parent->m_parent && 
         (current->m_parent->m_right == current) &&
         (current->m_parent->m_parent->m_left == nullptr || 
         current->m_parent->m_parent->m_left->m_color == BLACK)) {
            if(current->m_parent->m_parent)
                current->m_parent->m_color = BLACK;
            current->m_parent->m_parent->m_color = RED;
            left_rotate(current->m_parent->m_parent);
        }
        else if(current->m_parent->m_parent && 
         (current->m_parent->m_left == current) &&
         (current->m_parent->m_parent->m_right == nullptr || 
         current->m_parent->m_parent->m_right->m_color == BLACK)) {
            if(current->m_parent->m_parent)
                current->m_parent->m_color = BLACK;
            current->m_parent->m_parent->m_color = RED;
            right_rotate(current->m_parent->m_parent);
        }
        else if(current->m_parent->m_parent && 
         (current->m_parent->m_left == current) &&
         (current->m_parent->m_parent->m_left == nullptr || 
         current->m_parent->m_parent->m_left->m_color == BLACK)) {
            right_rotate(current->m_parent);
            left_rotate(current->m_parent);
            current->m_color = BLACK;
            current->m_left->m_color = RED;
            current->m_right->m_color = RED;
        }
        else if(current->m_parent->m_parent && 
         (current->m_parent->m_right == current) &&
         (current->m_parent->m_parent->m_right == nullptr || 
         current->m_parent->m_parent->m_right->m_color == BLACK)) {
            left_rotate(current->m_parent);
            right_rotate(current->m_parent);
            current->m_color = BLACK;
            current->m_left->m_color = RED;
            current->m_right->m_color = RED;
        }
        else if(current->m_parent->m_parent && 
         (current->m_parent->m_parent->m_left &&
         current->m_parent->m_parent->m_left->m_color == RED) ||
         (current->m_parent->m_parent->m_right &&
         current->m_parent->m_parent->m_right->m_color == RED)) {
            current->m_parent->m_color = BLACK;
            if(current->m_parent->m_parent->m_left)
                current->m_parent->m_parent->m_left->m_color = BLACK;
            if(current->m_parent->m_parent->m_right)
                current->m_parent->m_parent->m_right->m_color = BLACK;
            if(current->m_parent->m_parent != m_root) {
                current->m_parent->m_parent->m_color = RED;
            }
            
        } 
        if(current->m_parent &&
         current->m_parent->m_color == BLACK &&
         current->m_parent->m_parent && 
         current->m_parent->m_parent != m_root &&
         current->m_parent->m_parent->m_color == RED) {
            balance(current->m_parent->m_parent);
        }
    }
    m_root->m_color = BLACK;
}

template <typename T>
void mylib::rb_tree<T>::left_rotate(node* current)
{
    node* cur_right = current->m_right;
    node* w_node {};
    if(current->m_right->m_left) {
        w_node = current->m_right->m_left;
        w_node->m_parent = current;
    }
    if(current->m_parent) {
        cur_right->m_parent = current->m_parent;
        if(current->m_value < current->m_parent->m_value) {
            current->m_parent->m_left = cur_right;
        } else {
            current->m_parent->m_right = cur_right;
        }
    } else {
        m_root = cur_right;
    }
    cur_right->m_left = current;
    current->m_parent = cur_right;
    current->m_right = w_node;
}

template <typename T>
void mylib::rb_tree<T>::right_rotate(node* current)
{
    node* cur_left = current->m_left;
    node* w_node {};
    if(current->m_left->m_right) {
        w_node = current->m_left->m_right;
        w_node->m_parent = current;
    }
    if(current->m_parent) {
        cur_left->m_parent = current->m_parent;
        if(current->m_value < current->m_parent->m_value) {
            current->m_parent->m_left = cur_left;
        } else {
            current->m_parent->m_right = cur_left;
        }
    } else {
        m_root = cur_left;
    }
    cur_left->m_right = current;
    current->m_parent = cur_left;
    current->m_left = w_node;
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

template <typename T>
void mylib::rb_tree<T>::remove(const value_type& value)
{
    node* current = search(value);
    node* delete_ptr;

    if(!current) {
        return;
    }
    if((current->m_color == RED || current == m_root) &&
     current->m_left == nullptr && current->m_right == nullptr) {
        remove_case_1(current);
    }
    // else if((current->m_color == BLACK) &&
    //  current->m_left == nullptr && current->m_right == nullptr)
    // {
    //     remove_case_5(current);
    // }
    else if(current->m_left || current->m_right) {
        if(current->m_right) {
            delete_ptr = search_in_order_successor(current->m_right);
            current->m_value = delete_ptr->m_value;
        } else {
            delete_ptr = search_in_order_predecessor(current->m_left);
            current->m_value = delete_ptr->m_value;
        }
        if(delete_ptr->m_color == RED && 
        delete_ptr->m_left == nullptr && 
        delete_ptr->m_right == nullptr) {
            remove_case_1(delete_ptr);
        }
        else if((delete_ptr->m_color == BLACK && 
        delete_ptr->m_parent && 
        delete_ptr->m_parent->m_color == RED &&
        delete_ptr->m_parent->m_left == delete_ptr &&
        delete_ptr->m_parent->m_right &&
        delete_ptr->m_parent->m_right->m_color == BLACK) && 
        (!delete_ptr->m_parent->m_right->m_left ||
        delete_ptr->m_parent->m_right->m_left && 
        delete_ptr->m_parent->m_right->m_left->m_color == BLACK) ||
        (!delete_ptr->m_parent->m_right->m_right ||
        delete_ptr->m_parent->m_right->m_right && 
        delete_ptr->m_parent->m_right->m_right->m_color == BLACK)) {
            remove_case_2(delete_ptr);
        }
        else if(delete_ptr->m_color == BLACK && 
        delete_ptr->m_parent && 
        delete_ptr->m_parent->m_color == RED &&
        delete_ptr->m_parent->m_right == delete_ptr &&
        delete_ptr->m_parent->m_left &&
        delete_ptr->m_parent->m_left->m_color == BLACK && 
        (!delete_ptr->m_parent->m_right->m_left ||
        delete_ptr->m_parent->m_left->m_left && 
        delete_ptr->m_parent->m_left->m_left->m_color == BLACK) ||
        (!delete_ptr->m_parent->m_left->m_right ||
        delete_ptr->m_parent->m_left->m_right && 
        delete_ptr->m_parent->m_left->m_right->m_color == BLACK)) {
            remove_case_3(delete_ptr);
        }
        else if(delete_ptr->m_color == BLACK && 
        delete_ptr->m_parent && 
        delete_ptr->m_parent->m_color == BLACK &&
        delete_ptr->m_parent->m_left == delete_ptr &&
        delete_ptr->m_parent->m_right &&
        delete_ptr->m_parent->m_right->m_color == BLACK && 
        (!delete_ptr->m_parent->m_right->m_left ||
        delete_ptr->m_parent->m_right->m_left && 
        delete_ptr->m_parent->m_right->m_left->m_color == BLACK) ||
        (!delete_ptr->m_parent->m_right->m_right ||
        delete_ptr->m_parent->m_right->m_right && 
        delete_ptr->m_parent->m_right->m_right->m_color == BLACK)) {
            remove_case_4(delete_ptr);
        }
        else if(delete_ptr->m_color == BLACK && 
        delete_ptr->m_parent && 
        delete_ptr->m_parent->m_color == BLACK &&
        delete_ptr->m_parent->m_left == delete_ptr &&
        delete_ptr->m_parent->m_right &&
        delete_ptr->m_parent->m_right->m_color == BLACK && 
        (!delete_ptr->m_parent->m_left->m_left ||
        delete_ptr->m_parent->m_left->m_left && 
        delete_ptr->m_parent->m_left->m_left->m_color == BLACK) ||
        (!delete_ptr->m_parent->m_left->m_right ||
        delete_ptr->m_parent->m_left->m_right && 
        delete_ptr->m_parent->m_left->m_right->m_color == BLACK)) {
            remove_case_5(delete_ptr);
        }

        else if(delete_ptr->m_color == BLACK && 
        delete_ptr->m_parent &&
        delete_ptr->m_parent->m_color == BLACK &&
        delete_ptr->m_parent->m_left == delete_ptr &&
        delete_ptr->m_parent->m_right && 
        delete_ptr->m_parent->m_right->m_color == BLACK && 
        (!delete_ptr->m_parent->m_right->m_left ||
        delete_ptr->m_parent->m_right->m_left && 
        delete_ptr->m_parent->m_right->m_left->m_color == BLACK) ||
        (!delete_ptr->m_parent->m_right->m_right ||
        delete_ptr->m_parent->m_right->m_right && 
        delete_ptr->m_parent->m_right->m_right->m_color == BLACK)) {
            remove_case_6(delete_ptr);
        }
        else if(delete_ptr->m_color == BLACK && 
        delete_ptr->m_parent &&
        delete_ptr->m_parent->m_color == BLACK &&
        delete_ptr->m_parent->m_right == delete_ptr &&
        delete_ptr->m_parent->m_left && 
        delete_ptr->m_parent->m_left->m_color == BLACK && 
        (!delete_ptr->m_parent->m_left->m_left ||
        delete_ptr->m_parent->m_left->m_left && 
        delete_ptr->m_parent->m_left->m_left->m_color == BLACK) ||
        (!delete_ptr->m_parent->m_left->m_right ||
        delete_ptr->m_parent->m_left->m_right && 
        delete_ptr->m_parent->m_left->m_right->m_color == BLACK)) {
            remove_case_7(delete_ptr);
        }

    }

    delete_ptr = current;
    if((delete_ptr->m_color == BLACK && 
     delete_ptr->m_parent && 
     delete_ptr->m_parent->m_color == RED &&
     delete_ptr->m_parent->m_left == delete_ptr &&
     delete_ptr->m_parent->m_right &&
     delete_ptr->m_parent->m_right->m_color == BLACK)) {
        remove_case_2(delete_ptr);
    }
    if(delete_ptr->m_color == BLACK && 
     delete_ptr->m_parent &&
     delete_ptr->m_parent->m_color == BLACK &&
     delete_ptr->m_parent->m_left == delete_ptr &&
     delete_ptr->m_parent->m_right && 
     delete_ptr->m_parent->m_right->m_color == BLACK) {    
        remove_case_6(delete_ptr);
    }
}

template <typename T>
typename mylib::rb_tree<T>::node* mylib::rb_tree<T>::search_in_order_successor(node* current)
{
    while(current->m_left) {
        current = current->m_left;
    }
    return current;
}

template <typename T>
typename mylib::rb_tree<T>::node* mylib::rb_tree<T>::search_in_order_predecessor(node* current)
{
    while(current->m_right) {
        current = current->m_right;
    }
    return current;
}

template <typename T>
void mylib::rb_tree<T>::remove_case_1(node* current)
{
    node* current_parent = current->m_parent;
    if(current->m_parent && current_parent->m_left == current) {
        current_parent->m_left = nullptr;
    } else if (current->m_parent && current_parent->m_right == current) {
        current_parent->m_right = nullptr;
    }
    delete current;
    if(current == m_root) {
        m_root = nullptr;
    }
    current = nullptr;
}

template <typename T>
void mylib::rb_tree<T>::remove_case_2(node* current)
{
    if(current->m_right) {
        left_rotate(current);
    }
    current->m_parent->m_color = BLACK;
    current->m_parent->m_left = nullptr;
    delete current;
}

template <typename T>
void mylib::rb_tree<T>::remove_case_3(node* current)
{
    if(current->m_left) {
        right_rotate(current);
    }
    current->m_parent->m_color = BLACK;
    current->m_parent->m_right = nullptr;
    delete current;
}

template <typename T>
void mylib::rb_tree<T>::remove_case_4(node* current)
{
    current->m_parent->m_color = BLACK;
    current->m_parent->m_right->m_color = RED;
    if(current->m_right) {
        left_rotate(current);
    }
    current->m_parent->m_left = nullptr;
    delete current;
}

template <typename T>
void mylib::rb_tree<T>::remove_case_5(node* current)
{
    current->m_parent->m_left->m_color = RED;
    current->m_parent->m_color = BLACK;
    if(current->m_right) {
        left_rotate(current);
    }
    current->m_parent->m_right = nullptr;
    delete current;
}

template <typename T>
void mylib::rb_tree<T>::remove_case_6(node* current)
{
    current->m_parent->m_right->m_color = RED;
    node* current_parent = current->m_parent;
    if(current->m_right) {
        left_rotate(current);
    }
    current->m_parent->m_left = nullptr;
    delete current;
    if(current_parent == m_root) {
        return;
    }
    while(current_parent->m_parent->m_color == BLACK && 
      ((!current_parent->m_parent->m_left ||
      current_parent->m_parent->m_left &&
      current_parent->m_parent->m_left->m_color == BLACK) && 
      current_parent->m_parent->m_left != current_parent) ||
      ((!current_parent->m_parent->m_right ||
      current_parent->m_parent->m_right &&
      current_parent->m_parent->m_right->m_color == BLACK) &&
      current_parent->m_parent->m_right != current_parent)) {
        if(current_parent->m_parent->m_left) {
            current_parent->m_parent->m_left->m_color = RED;
        }
        if(current_parent->m_parent != m_root) {
            current_parent = current_parent->m_parent;
        }
    }
}

template <typename T>
void mylib::rb_tree<T>::remove_case_7(node* current)
{
    current->m_parent->m_left->m_color = RED;
    node* current_parent = current->m_parent;
    if(current->m_left) {
        right_rotate(current);
    }
    current->m_parent->m_right = nullptr;
    delete current;
    if(current_parent == m_root) {
        return;
    }
    while(current_parent->m_parent->m_color == BLACK && 
      ((!current_parent->m_parent->m_left ||
      current_parent->m_parent->m_left &&
      current_parent->m_parent->m_left->m_color == BLACK) && 
      current_parent->m_parent->m_left != current_parent) ||
      ((!current_parent->m_parent->m_right ||
      current_parent->m_parent->m_right &&
      current_parent->m_parent->m_right->m_color == BLACK) &&
      current_parent->m_parent->m_right != current_parent)) {
        if(current_parent->m_parent->m_left) {
            current_parent->m_parent->m_left->m_color = RED;
        }
        if(current_parent->m_parent != m_root) {
            current_parent = current_parent->m_parent;
        }
    }
}


template <typename T>
typename mylib::rb_tree<T>::node* mylib::rb_tree<T>::search(const value_type& value)
{
    node* current = m_root;
    while (current != nullptr) {
        if(current->m_value < value) {
            current = current->m_right;
        } else if(current->m_value == value) {
            return current;
        } else {
            current = current->m_left;
        }
    }
    return nullptr;
}