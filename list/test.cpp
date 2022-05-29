#include <iostream>

#include "list.h"

int main() {
    mylib::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    auto it = lst.begin();
    ++it;
    std::cout << *(lst.erase(lst.begin()));
    std::cout << "\n" << lst;
}