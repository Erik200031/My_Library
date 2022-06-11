#include <iostream>

#include "rb_tree.h"

int main() {
  mylib::rb_tree<int> rb;
  rb.insert(7);
  rb.insert(4);
  rb.insert(2);
  rb.insert(71);
  rb.insert(30);
  rb.insert(34);
  rb.insert(35);
  rb.insert(72);
  



  
    rb.print_in_order();
  std::cout << "\n\n";
  // rb.remove(7);
  rb.print_in_order();
    std::cout << "\n\n";
auto it = rb.begin();
++it;
++it;
++it;
++it;
++it;
++it;
++it;
--it;
--it;
--it;
--it;
--it;
--it;
--it;


  std::cout << *it;


}