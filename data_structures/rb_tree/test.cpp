#include <iostream>

#include "rb_tree.h"

int main() {
  mylib::rb_tree<int> rb;

  rb.insert(8);
  rb.insert(89);
  rb.insert(81);
  rb.insert(82);
  rb.insert(38);
  rb.insert(128);
  rb.insert(834);
  rb.insert(876);
  rb.insert(8454);
  rb.insert(834342);
  rb.insert(228);
  rb.print_in_order();


}