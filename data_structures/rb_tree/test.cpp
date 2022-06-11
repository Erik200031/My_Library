#include <iostream>

#include "rb_tree.h"

int main() {
  mylib::rb_tree<int> rb;
  for(int i = 37; i > 20; i-=3) {
      rb.insert(i);
  }
  
    rb.print_in_order();
std::cout << "\n\n";
  rb.remove(22);
  rb.print_in_order();


}