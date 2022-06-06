#include <iostream>

#include "rb_tree.h"

int main() {
    mylib::rb_tree<int> rb;
    rb.insert(10);    
    rb.insert(18);    
    rb.insert(7);    
    rb.insert(15);    
    rb.insert(16);    
    rb.insert(30);    
    rb.insert(25);   
    rb.insert(40);   


    rb.print_in_order();


}