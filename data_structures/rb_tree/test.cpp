#include <iostream>

#include "rb_tree.h"

int main() {
  mylib::rb_tree<int> rb;
for(int i = 1; i < 9; ++i) {
  rb.insert(i);
}
   rb.print_in_order();
  std::cout << "\n\n";

  for(int i = 1; i < 9; ++i) {
    if(i%2 == 0) {
       rb.print_in_order();
  std::cout << "\n\n";

      rb.remove(i);

    }
  }
 //rb.remove(6);


  
  std::cout << "\n\n";
 

 rb.print_in_order();
 
    std::cout << "\n\n";





}