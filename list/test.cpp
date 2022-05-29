#include <iostream>

#include "list.h"
#include <list>

int main() {
    mylib::list<int> lst{1, 3, 5, 7, 9, 44};

    std::cout << "\n" << lst;
    
    lst.reverse();
    
    std::cout << "\n" << lst << "\n";

}