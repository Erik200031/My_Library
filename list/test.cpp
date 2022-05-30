#include <iostream>

#include "list.h"
#include <list>

int main() {
    mylib::list<int> lst{1, 32, 5, 5, 985, 7, 9, 1};
    mylib::list<int> lst1{1, 32, 52, 5, 35, 7, 9};

    std::cout << "\n" << lst;
    std::cout << "\n" << lst1 << "\n";
    lst1.sort();
    lst.sort();
         std::cout << "\n" << lst << "\n";
     std::cout << "\n" << lst1 << "\n";
     lst.merge(lst1);

    std::cout << "\n" << lst << "\n";
}