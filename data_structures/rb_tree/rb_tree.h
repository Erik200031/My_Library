#ifndef RB_TREE_H
#define RB_TREE_H

#include <iostream>

#define BLACK 0
#define RED 1

namespace mylib
{
    template <typename T>
    class rb_tree
    {
    public:
        typedef T value_type;
        typedef T& reference;

    private:
        struct node
        {
            node* m_parent;
            node* m_left;
            node* m_right;
            bool m_color;
            const value_type m_value;
            node() : m_parent {}, m_left {}, 
            m_right {}, m_color {} {}
            node(node* parent, node* left,
             node* right, bool color, const value_type& value) 
            : m_parent {parent}, m_left {left}, 
            m_right {right}, m_color {color}, m_value{value} {}
        };

    public:
        rb_tree();
        rb_tree(const rb_tree& rhs);
        rb_tree(rb_tree&& rhs) noexcept;
        rb_tree& operator=(const rb_tree& rhs);
        rb_tree& operator=(rb_tree&& rhs) noexcept;
        void insert(const value_type& value);
        bool empty() const;
        void print_in_order();
    private:
        void m_print_in_order(node* root);
        void balance(node* current);
        void left_rotate(node* current);
        void right_rotate(node* current);
        
    private:
        node* m_root;
    };
    
} // namespace mylib

#include "rb_tree.hpp"

#endif //RB_TREE_H