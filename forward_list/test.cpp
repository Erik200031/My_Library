#include <iostream>
#include "forward_list.h"

int main() {

    mylib::Forward_list<int> lst;
    lst.push_front(9);
    lst.push_front(3);
    std::cout << lst;

}