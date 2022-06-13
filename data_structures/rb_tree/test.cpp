#include <iostream>

#include "rb_tree.h"

int main() {
  mylib::rb_tree<int , int> rb;
for(int i = 1; i < 9; ++i) {
  rb.insert(mylib::make_pair(i, i+1));
}
   rb.print_in_order();
  std::cout << "\n\n";

 //rb.remove(6);

  std::cout << "\n\n";

 rb.print_in_order(); 
    std::cout << "\n\n";
    
    std::cout << (*rb.begin()).first;





}