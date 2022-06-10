#include <iostream>

#include "rb_tree.h"

int main() {
    mylib::rb_tree<int> rb;

    rb.insert(10);
    rb.insert(7);
    rb.insert(20);
    rb.insert(15);
    rb.remove(20);   

std::cout << '\n';

   
        rb.print_in_order();



}