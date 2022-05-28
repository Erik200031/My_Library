#include <iostream>

#include "list.h"

int main() {
    mylib::list<int> lst;
    lst.push_back(10);
    lst.push_back(11);
     lst.push_front(99);
     mylib::list<int> lst1(std::move(lst));
     lst1.pop_back();
        std::cout << lst1 << " ";
      // std::cout << lst << " ";
}