#include <iostream>

#include "rb_tree.h"

int main() {
    mylib::rb_tree<int> rb;

    rb.insert(7);
    rb.insert(10);
    rb.insert(8);
    rb.insert(9);
        rb.print_in_order();
          rb.remove(10);
std::cout << '\n';

   
        rb.print_in_order();



}