#include <iostream>

#include "rb_tree.h"

int main() {
  mylib::rb_tree<int> rb;

  rb.insert(10);
  rb.insert(3);
  rb.insert(20);
  rb.insert(15);
  rb.insert(30);
  rb.insert(16);
  rb.remove(16);
  rb.insert(7);
  rb.insert(1);
  rb.insert(2);
  rb.remove(2);
   rb.insert(4);
     rb.insert(8);

  rb.insert(5);
   rb.remove(5);
   rb.remove(4);
  
  
  rb.print_in_order();
  std::cout<<std::endl;
  //rb.insert(15);
  //rb.insert(50);
  //rb.insert(38);
 // rb.insert(2);

  //rb.insert(50);
  //rb.insert(38);
  
 // rb.print_in_order();


   rb.remove(15);   

  std::cout << '\n';   
  rb.print_in_order();



}