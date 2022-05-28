#include <iostream>

#include "list.h"

int main() {
    mylib::list<int> lst;
    lst.push_back(10);
    lst.push_back(11);
     lst.push_back(11);
     lst.push_back(11);
     mylib::list<int> lst1;

    // lst.push_back(110);
    // lst.push_back(111);
    // lst.push_back(111);
    // lst.push_back(111);
     lst1 = lst;
   // lst.pop_front();
    std::cout << lst1 << " ";
}