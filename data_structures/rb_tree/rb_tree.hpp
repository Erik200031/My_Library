#include "rb_tree.h"

template <typename Key, typename T>
mylib::rb_tree<Key, T>::rb_tree() : m_root{} {}

template <typename Key, typename T>
mylib::rb_tree<Key, T>::rb_tree(const rb_tree<Key, T>& rhs) : m_root{} 
{

}

template <typename Key, typename T>
mylib::rb_tree<Key, T>::rb_tree(rb_tree<Key, T>&& rhs) noexcept : m_root{} 
{
    
}

template <typename Key, typename T>
mylib::rb_tree<Key, T>& mylib::rb_tree<Key, T>::operator=(const rb_tree<Key, T>& rhs) 
{

}

template <typename Key, typename T>
mylib::rb_tree<Key, T>& mylib::rb_tree<Key, T>::operator=(rb_tree<Key, T>&& rhs) noexcept
{

}

template <typename Key, typename T>
bool mylib::rb_tree<Key, T>::empty() const
{
    return m_root == nullptr;
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::insert(const value_type& value)
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
        if(current && current->m_value.first > value.first) {
            current = current->m_left;
        } else if(current && current->m_value.first < value.first) {
            current = current->m_right;
        }
    }
    current = new node(current_parent, nullptr, nullptr, RED, value); 
    if(current_parent->m_value.first < value.first) {
        current_parent->m_right = current;
    } else {
        current_parent->m_left = current;
    }
    if(current_parent->m_color == BLACK) {
        return;
    }
    balance(current);
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::balance(node* current)
{
    if(current->m_parent && current->m_parent->m_color == RED) {
        if(current->m_parent->m_parent && 
         (current->m_parent->m_right == current) &&
         (current->m_parent->m_parent->m_left == nullptr || 
         current->m_parent->m_parent->m_left &&
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
         current->m_parent->m_parent && 
         current->m_parent->m_parent != m_root &&
         current->m_parent->m_parent->m_color == RED && 
         current->m_parent->m_parent->m_parent &&
         current->m_parent->m_parent->m_parent->m_color == RED) {
            m_root->m_color = BLACK;
            balance(current->m_parent->m_parent);
        }
    } 
    m_root->m_color = BLACK;
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::left_rotate(node* current)
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
        cur_right->m_parent = nullptr;
    }
    cur_right->m_left = current;
    current->m_parent = cur_right;
    current->m_right = w_node;
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::right_rotate(node* current)
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

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::m_print_in_order(node* root) 
{
    if(!root) {
        return;
    }
    m_print_in_order(root->m_left);
   std::cout << '[' << root->m_color << ' ' << '{' << root->m_value.first  
   << ", " << root->m_value.second << '}' << "] ";
    m_print_in_order(root->m_right);
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::print_in_order() 
{
    m_print_in_order(m_root);
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::remove(const value_type& value)
{
    node* current = search(value);
    node* delete_ptr;
    if(!current) {
        return;
    }
    if(current->m_left || current->m_right) {
        if(current->m_right) {
            delete_ptr = search_in_order_successor(current->m_right);
            current->m_value = delete_ptr->m_value;
        } else {
            delete_ptr = search_in_order_predecessor(current->m_left);
            current->m_value = delete_ptr->m_value;
        }
    } else {
       delete_ptr = current;
    }
    if(delete_ptr->m_color == RED && 
     delete_ptr->m_left == nullptr && 
     delete_ptr->m_right == nullptr) {
        remove_case_1(delete_ptr);
    }
    else if(delete_ptr->m_color == BLACK && 
     delete_ptr->m_parent && 
     delete_ptr->m_parent->m_color == RED &&
     delete_ptr->m_parent->m_left == delete_ptr &&
     delete_ptr->m_parent->m_right &&
     delete_ptr->m_parent->m_right->m_color == BLACK ||
     delete_ptr->m_parent->m_right == nullptr ) {
        remove_case_2(delete_ptr);
    }
    else if(delete_ptr->m_color == BLACK && 
     delete_ptr->m_parent && 
     delete_ptr->m_parent->m_color == RED &&
     delete_ptr->m_parent->m_right == delete_ptr &&
     delete_ptr->m_parent->m_left &&
     delete_ptr->m_parent->m_left->m_color == BLACK || 
     delete_ptr->m_parent->m_left == nullptr) {
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
     delete_ptr->m_parent->m_right->m_left->m_color == BLACK) &&
     (!delete_ptr->m_parent->m_right->m_right ||
     delete_ptr->m_parent->m_right->m_right && 
     delete_ptr->m_parent->m_right->m_right->m_color == BLACK)
     ) {
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
     delete_ptr->m_parent->m_left->m_left->m_color == BLACK) &&
     (!delete_ptr->m_parent->m_left->m_right ||
     delete_ptr->m_parent->m_left->m_right && 
     delete_ptr->m_parent->m_left->m_right->m_color == BLACK)
     ) {
        remove_case_5(delete_ptr);
    }
    else if(delete_ptr->m_color == BLACK && 
     delete_ptr->m_parent &&
     delete_ptr->m_parent->m_color == BLACK &&
     delete_ptr->m_parent->m_left == delete_ptr &&
     delete_ptr->m_parent->m_right && 
     delete_ptr->m_parent->m_right->m_color == BLACK && 
     ((delete_ptr->m_parent->m_right->m_left == nullptr) ||
     (delete_ptr->m_parent->m_right->m_left && 
     delete_ptr->m_parent->m_right->m_left->m_color == BLACK)) &&
     ((delete_ptr->m_parent->m_right->m_right == nullptr) ||
     (delete_ptr->m_parent->m_right->m_right && 
     delete_ptr->m_parent->m_right->m_right->m_color == BLACK))
     ) {
        remove_case_6(delete_ptr);
    }
    else if((delete_ptr->m_color == BLACK && 
     delete_ptr->m_parent &&
     delete_ptr->m_parent->m_color == BLACK &&
     delete_ptr->m_parent->m_right == delete_ptr &&
     delete_ptr->m_parent->m_left && 
     delete_ptr->m_parent->m_left->m_color == BLACK ||
     delete_ptr->m_parent->m_left == nullptr) && 
     ((delete_ptr->m_parent->m_left && 
     delete_ptr->m_parent->m_left->m_left == nullptr) ||
     (delete_ptr->m_parent->m_left->m_left && 
     delete_ptr->m_parent->m_left->m_left->m_color == BLACK)) &&
     ((delete_ptr->m_parent->m_left->m_right == nullptr) ||
     (delete_ptr->m_parent->m_left->m_right && 
     delete_ptr->m_parent->m_left->m_right->m_color == BLACK))
     ) {
        remove_case_7(delete_ptr);
    }
    else if(delete_ptr->m_color == BLACK && 
     delete_ptr->m_parent &&
     delete_ptr->m_parent->m_color == BLACK &&
     delete_ptr->m_parent->m_left == delete_ptr &&
     delete_ptr->m_parent->m_right && 
     delete_ptr->m_parent->m_right->m_color == RED && 
     ((delete_ptr->m_parent->m_right->m_left == nullptr) ||
     (delete_ptr->m_parent->m_right->m_left && 
     delete_ptr->m_parent->m_right->m_left->m_color == BLACK)) &&
     ((delete_ptr->m_parent->m_right->m_right == nullptr) ||
     (delete_ptr->m_parent->m_right->m_right && 
     delete_ptr->m_parent->m_right->m_right->m_color == BLACK))
     ) {
        remove_case_8(delete_ptr);
    }
    else if(delete_ptr->m_color == BLACK && 
     delete_ptr->m_parent &&
     delete_ptr->m_parent->m_color == BLACK &&
     delete_ptr->m_parent->m_right == delete_ptr &&
     delete_ptr->m_parent->m_left && 
     delete_ptr->m_parent->m_left->m_color == RED && 
     ((delete_ptr->m_parent->m_left->m_left == nullptr) ||
     (delete_ptr->m_parent->m_left->m_left && 
     delete_ptr->m_parent->m_left->m_left->m_color == BLACK)) &&
     ((delete_ptr->m_parent->m_left->m_right == nullptr) ||
     (delete_ptr->m_parent->m_left->m_right && 
     delete_ptr->m_parent->m_left->m_right->m_color == BLACK))) {
        remove_case_9(delete_ptr);
    }
    else if(delete_ptr->m_color == BLACK && 
     delete_ptr->m_parent &&
     delete_ptr->m_parent->m_color == BLACK &&
     delete_ptr->m_parent->m_left == delete_ptr &&
     delete_ptr->m_parent->m_right && 
     delete_ptr->m_parent->m_right->m_color == RED && 
     ((delete_ptr->m_parent->m_right->m_left == nullptr) ||
     (delete_ptr->m_parent->m_right->m_left && 
     delete_ptr->m_parent->m_right->m_left->m_color == BLACK)) &&
     ((delete_ptr->m_parent->m_right->m_right == nullptr) ||
     (delete_ptr->m_parent->m_right->m_right && 
     delete_ptr->m_parent->m_right->m_right->m_color == BLACK))) {
     //   remove_case_7(delete_ptr);
    }
}

template <typename Key, typename T>
typename mylib::rb_tree<Key, T>::node* mylib::rb_tree<Key, T>::search_in_order_successor(node* current)
{
    while(current->m_left) {
        current = current->m_left;
    }
    return current;
}

template <typename Key, typename T>
typename mylib::rb_tree<Key, T>::node* mylib::rb_tree<Key, T>::search_in_order_predecessor(node* current)
{
    while(current->m_right) {
        current = current->m_right;
    }
    return current;
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::remove_case_1(node* current)
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

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::remove_case_2(node* current)
{
    if(((current->m_parent->m_right && 
    current->m_parent->m_right->m_left &&
    current->m_parent->m_right->m_left->m_color == BLACK) || 
     current->m_parent->m_right &&
      current->m_parent->m_right->m_left == nullptr) &&
    ((current->m_parent->m_right->m_right &&
    current->m_parent->m_right->m_right->m_color == BLACK) || 
     current->m_parent->m_right->m_right == nullptr)) {
       current->m_parent->m_right->m_color = RED;
    }
    current->m_parent->m_color = BLACK;
    if(current->m_left) {
        current->m_parent->m_left = current->m_left;
        current->m_parent->m_left->m_color = current->m_color;
    } else {
           current->m_parent->m_left = nullptr;
    }
    delete current;
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::remove_case_3(node* current)
{
    if((current->m_parent->m_left && 
    current->m_parent->m_left->m_left &&
    current->m_parent->m_left->m_left->m_color == BLACK || 
    current->m_parent->m_left && 
     current->m_parent->m_left->m_left == nullptr) &&
    (current->m_parent->m_left->m_right &&
    current->m_parent->m_left->m_right->m_color == BLACK || 
     current->m_parent->m_left->m_right == nullptr)) {
        current->m_parent->m_left->m_color = RED;
    }
    current->m_parent->m_color = BLACK;
    if(current->m_right) {
        current->m_parent->m_right = current->m_right;
        current->m_parent->m_right->m_color = current->m_color;
    } else {
           current->m_parent->m_right = nullptr;
    }
    delete current;
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::remove_case_4(node* current)
{
    current->m_parent->m_color = BLACK;
    current->m_parent->m_right->m_color = RED;
    // if(current->m_right) {
    //     left_rotate(current);
    // }
    current->m_parent->m_left = nullptr;
    delete current;
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::remove_case_5(node* current)
{
    current->m_parent->m_left->m_color = RED;
    current->m_parent->m_color = BLACK;
    // if(current->m_right) {
    //     left_rotate(current);
    // }
    current->m_parent->m_right = nullptr;
    delete current;
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::remove_case_6(node* current)
{
    current->m_parent->m_right->m_color = RED;
    node* current_parent = current->m_parent;
    // if(current->m_right) {
    //     left_rotate(current);
    // }
    current->m_parent->m_left = nullptr;
    delete current;
    if(current_parent == m_root) {
        return;
    }
    while(current_parent->m_parent->m_color == BLACK && 
      ((!current_parent->m_parent->m_left ||
      current_parent->m_parent->m_left &&
      current_parent->m_parent->m_left->m_color == BLACK) && 
      current_parent->m_parent->m_left != current_parent &&
      ((current_parent->m_parent->m_left->m_left == nullptr) ||
      (current_parent->m_parent->m_left->m_left && 
      current_parent->m_parent->m_left->m_left->m_color == BLACK) &&
      (current_parent->m_parent->m_left->m_right == nullptr) ||
      (current_parent->m_parent->m_left->m_right && 
      current_parent->m_parent->m_left->m_right->m_color == BLACK)) || 
      ((!current_parent->m_parent->m_right ||
      current_parent->m_parent->m_right &&
      current_parent->m_parent->m_right->m_color == BLACK) &&
      current_parent->m_parent->m_right != current_parent) &&
      ((current_parent->m_parent->m_left->m_left == nullptr) ||
      (current_parent->m_parent->m_left->m_left && 
      current_parent->m_parent->m_left->m_left->m_color == BLACK) &&
      (current_parent->m_parent->m_left->m_right == nullptr) ||
      (current_parent->m_parent->m_left->m_right && 
      current_parent->m_parent->m_left->m_right->m_color == BLACK)))) {
        if(current_parent->m_parent->m_left && 
        current_parent->m_parent->m_left != current_parent) {
            current_parent->m_parent->m_left->m_color = RED;
        }
        if(current_parent->m_parent->m_right && 
        current_parent->m_parent->m_right != current_parent) {
            current_parent->m_parent->m_left->m_color = RED;
        }
        if(current_parent->m_parent != m_root) {
            current_parent = current_parent->m_parent;
        }
    }
    while(current_parent->m_parent->m_color == BLACK && 
      ((!current_parent->m_parent->m_left ||
      current_parent->m_parent->m_left &&
      current_parent->m_parent->m_left->m_color == BLACK) && 
      current_parent->m_parent->m_left != current_parent &&
      ((current_parent->m_parent->m_left->m_left == nullptr) ||
      (current_parent->m_parent->m_left->m_left && 
      current_parent->m_parent->m_left->m_left->m_color == BLACK) &&
      (current_parent->m_parent->m_left->m_right == nullptr) ||
      (current_parent->m_parent->m_left->m_right && 
      current_parent->m_parent->m_left->m_right->m_color == BLACK)) || 
      ((!current_parent->m_parent->m_right ||
      current_parent->m_parent->m_right &&
      current_parent->m_parent->m_right->m_color == BLACK) &&
      current_parent->m_parent->m_right != current_parent) &&
      ((current_parent->m_parent->m_left->m_left && 
      current_parent->m_parent->m_left->m_left->m_color == RED) &&
      (current_parent->m_parent->m_left->m_right == nullptr) ||
      (current_parent->m_parent->m_left->m_right && 
      current_parent->m_parent->m_left->m_right->m_color == BLACK)))) {
        if(current_parent->m_parent->m_right &&
        current_parent->m_parent->m_right->m_left && 
        current_parent->m_parent->m_right->m_left->m_color == RED) {
            current_parent->m_parent->m_right->m_color = RED;
            current_parent->m_parent->m_right->m_left->m_color = BLACK;
            right_rotate(current_parent->m_parent->m_right);
            bool tmp = current_parent->m_parent->m_color;
            current_parent->m_parent->m_color = current_parent->m_parent->m_right->m_color;
            current_parent->m_parent->m_right->m_color = tmp;
            left_rotate(current_parent->m_parent->m_right);
            current_parent->m_parent->m_parent->m_right->m_color = BLACK;
        }
        if(current_parent->m_parent != m_root) {
            current_parent = current_parent->m_parent;
        }
    }
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::remove_case_7(node* current)
{
    current->m_parent->m_left->m_color = RED;
    node* current_parent = current->m_parent;
    current->m_parent->m_right = nullptr;
    delete current;
    if(current_parent == m_root) {
        return;
    }
    while(current_parent->m_parent->m_color == BLACK && 
      ((!current_parent->m_parent->m_left ||
      current_parent->m_parent->m_left &&
      current_parent->m_parent->m_left->m_color == BLACK) && 
      current_parent->m_parent->m_left != current_parent &&
      ((current_parent->m_parent->m_left->m_left == nullptr) ||
      (current_parent->m_parent->m_left->m_left && 
      current_parent->m_parent->m_left->m_left->m_color == BLACK) &&
      (current_parent->m_parent->m_left->m_right == nullptr) ||
      (current_parent->m_parent->m_left->m_right && 
      current_parent->m_parent->m_left->m_right->m_color == BLACK)) || 
      ((!current_parent->m_parent->m_right ||
      current_parent->m_parent->m_right &&
      current_parent->m_parent->m_right->m_color == BLACK) &&
      current_parent->m_parent->m_right != current_parent) &&
      ((current_parent->m_parent->m_left->m_left == nullptr) ||
      (current_parent->m_parent->m_left->m_left && 
      current_parent->m_parent->m_left->m_left->m_color == BLACK) &&
      (current_parent->m_parent->m_left->m_right == nullptr) ||
      (current_parent->m_parent->m_left->m_right && 
      current_parent->m_parent->m_left->m_right->m_color == BLACK)))) {
        if(current_parent->m_parent->m_left && 
        current_parent->m_parent->m_left != current_parent) {
            current_parent->m_parent->m_left->m_color = RED;
        }
        if(current_parent->m_parent->m_right && 
        current_parent->m_parent->m_right != current_parent) {
            current_parent->m_parent->m_left->m_color = RED;
        }
        if(current_parent->m_parent != m_root) {
            current_parent = current_parent->m_parent;
        }
    }
    while(current_parent->m_parent->m_color == BLACK && 
      ((!current_parent->m_parent->m_left ||
      current_parent->m_parent->m_left &&
      current_parent->m_parent->m_left->m_color == BLACK) && 
      current_parent->m_parent->m_left != current_parent &&
      ((current_parent->m_parent->m_left->m_left == nullptr) ||
      (current_parent->m_parent->m_left->m_left && 
      current_parent->m_parent->m_left->m_left->m_color == BLACK) &&
      ((current_parent->m_parent->m_left->m_right && 
      current_parent->m_parent->m_left->m_right->m_color == RED)) || 
      ((!current_parent->m_parent->m_right ||
      current_parent->m_parent->m_right &&
      current_parent->m_parent->m_right->m_color == BLACK) &&
      current_parent->m_parent->m_right != current_parent) &&
      ((current_parent->m_parent->m_right->m_left && 
      current_parent->m_parent->m_right->m_left->m_color == RED) &&
      (current_parent->m_parent->m_right->m_right == nullptr) ||
      (current_parent->m_parent->m_right->m_right && 
      current_parent->m_parent->m_right->m_right->m_color == BLACK))))) {
        if(current_parent->m_parent->m_right &&
        current_parent->m_parent->m_right->m_left && 
        current_parent->m_parent->m_right->m_left->m_color == RED) {
            current_parent->m_parent->m_right->m_color = RED;
            current_parent->m_parent->m_right->m_left->m_color = BLACK;
            right_rotate(current_parent->m_parent->m_right);
            bool tmp = current_parent->m_parent->m_color;
            current_parent->m_parent->m_color = current_parent->m_parent->m_right->m_color;
            current_parent->m_parent->m_right->m_color = tmp;
            left_rotate(current_parent->m_parent->m_right);
            current_parent->m_parent->m_parent->m_right->m_color = BLACK;
        }
        if(current_parent->m_parent->m_left &&
        current_parent->m_parent->m_left->m_left && 
        current_parent->m_parent->m_left->m_right->m_color == RED) {
            current_parent->m_parent->m_left->m_color = RED;
            current_parent->m_parent->m_left->m_right->m_color = BLACK;
            left_rotate(current_parent->m_parent->m_right);
            bool tmp = current_parent->m_parent->m_color;
            current_parent->m_parent->m_color = current_parent->m_parent->m_left->m_color;
            current_parent->m_parent->m_left->m_color = tmp;
            right_rotate(current_parent->m_parent->m_left);
            current_parent->m_parent->m_parent->m_left->m_color = BLACK;
        }
        if(current_parent->m_parent != m_root) {
            current_parent = current_parent->m_parent;
        }
    }  
    while(current_parent->m_parent->m_color == BLACK && 
      ((!current_parent->m_parent->m_left ||
      current_parent->m_parent->m_left &&
      current_parent->m_parent->m_left->m_color == BLACK) && 
      current_parent->m_parent->m_left != current_parent &&
      ((current_parent->m_parent->m_left->m_right == nullptr) ||
      (current_parent->m_parent->m_left->m_right && 
      current_parent->m_parent->m_left->m_right->m_color == BLACK) &&
      ((current_parent->m_parent->m_left->m_left && 
      current_parent->m_parent->m_left->m_left->m_color == RED)) || 
      ((!current_parent->m_parent->m_right ||
      current_parent->m_parent->m_right &&
      current_parent->m_parent->m_right->m_color == BLACK) &&
      current_parent->m_parent->m_right != current_parent) &&
      ((current_parent->m_parent->m_right->m_right && 
      current_parent->m_parent->m_right->m_right->m_color == RED) &&
      (current_parent->m_parent->m_right->m_left == nullptr) ||
      (current_parent->m_parent->m_right->m_left && 
      current_parent->m_parent->m_right->m_left->m_color == BLACK))))) {
        if(current_parent->m_parent->m_right &&
        current_parent->m_parent->m_right->m_right && 
        current_parent->m_parent->m_right->m_right->m_color == RED) {
            bool tmp = current_parent->m_parent->m_color;
            current_parent->m_parent->m_color = current_parent->m_parent->m_right->m_color;
            current_parent->m_parent->m_right->m_color = tmp;
            left_rotate(current_parent->m_parent->m_right);
            current_parent->m_parent->m_parent->m_right->m_color = BLACK;
        }
        if(current_parent->m_parent->m_left &&
        current_parent->m_parent->m_left->m_left && 
        current_parent->m_parent->m_left->m_left->m_color == RED) {
            bool tmp = current_parent->m_parent->m_color;
            current_parent->m_parent->m_color = current_parent->m_parent->m_left->m_color;
            current_parent->m_parent->m_left->m_color = tmp;
            right_rotate(current_parent->m_parent->m_left);
            current_parent->m_parent->m_parent->m_left->m_color = BLACK;
        }
        if(current_parent->m_parent != m_root) {
            current_parent = current_parent->m_parent;
        }
    }
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::remove_case_8(node* current)
{
   current->m_parent->m_color = RED;
   current->m_parent->m_right->m_color = BLACK;
   remove_case_2(current);
}

template <typename Key, typename T>
void mylib::rb_tree<Key, T>::remove_case_9(node* current)
{
   current->m_parent->m_color = RED;
   current->m_parent->m_left->m_color = BLACK;
   remove_case_3(current);
}

template <typename Key, typename T>
typename mylib::rb_tree<Key, T>::node* mylib::rb_tree<Key, T>::search(const value_type& value)
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

template <typename Key, typename T>
typename mylib::rb_tree<Key, T>::Iterator mylib::rb_tree<Key, T>::begin()
{
    node* tmp = m_root;
    while (tmp->m_left)
    {
        tmp = tmp->m_left;
    }
    return Iterator(tmp);
}

template <typename Key, typename T>
typename mylib::rb_tree<Key, T>::Iterator& mylib::rb_tree<Key, T>::Iterator::operator++()
{
    if(m_node->m_right && m_node->m_right->m_left == nullptr) {
        m_node = m_node->m_right;
    } else if(m_node->m_right == nullptr && m_node->m_parent) {
        while (m_node->m_parent && 
        m_node->m_parent->m_value < m_node->m_value)
        {   
            m_node = m_node->m_parent;
        }
        if (m_node->m_parent)
        {
            m_node = m_node->m_parent;
        }
    }
    else if(m_node->m_right && m_node->m_right->m_left) {
        m_node = m_node->m_right->m_left;
        while (m_node->m_left)
        {
            m_node = m_node->m_left;
        }
        
    }
    return *this;
}

template <typename Key, typename T>
typename mylib::rb_tree<Key, T>::Iterator mylib::rb_tree<Key, T>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++(*this);
    return tmp; 
}

template <typename Key, typename T>
typename mylib::rb_tree<Key, T>::Iterator& mylib::rb_tree<Key, T>::Iterator::operator--()
{
    if(m_node->m_left && m_node->m_left->m_right == nullptr) {
        m_node = m_node->m_left;
    } else if(m_node->m_left == nullptr && m_node->m_parent) {
        while (m_node->m_parent && 
        m_node->m_parent->m_value > m_node->m_value)
        {   
            m_node = m_node->m_parent;
        }
        if (m_node->m_parent)
        {
            m_node = m_node->m_parent;
        }
    }
    else if(m_node->m_left && m_node->m_left->m_right) {
        m_node = m_node->m_left->m_right;
        while (m_node->m_left)
        {
            m_node = m_node->m_left;
        }
    }
    return *this;
}

template <typename Key, typename T>
typename mylib::rb_tree<Key, T>::Iterator mylib::rb_tree<Key, T>::Iterator::operator--(int)
{
    Iterator tmp = *this;
    --(*this);
    return tmp; 
}