#include <iostream>

#include "list.h"
#include <list>

int main() {
    mylib::list<int> lst;
    lst.push_back(9);
    lst.push_back(8);
    lst.push_back(7);
    lst.push_back(5);
    lst.push_back(1);

    std::cout << *lst.crbegin();

    std::cout << "\n" << lst << "\n";
}