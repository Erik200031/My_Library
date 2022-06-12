#include <iostream>

#include "rb_tree.h"

int main() {
  mylib::rb_tree<int> rb;
for(int i = 1; i < 9; ++i) {
  rb.insert(i);
}
  



  
   rb.print_in_order();
  std::cout << "\n\n";
  rb.remove(4);
 rb.print_in_order();
 
    std::cout << "\n\n";





}