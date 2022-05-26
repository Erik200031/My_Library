#include <iostream>
#include "forward_list.h"

int main() {

    mylib::Forward_list<int> lst(1);
    lst.push_front(1);
        lst.push_front(2);
    lst.push_front(3);
    lst.push_front(4);
        lst.push_front(5);
    std::cout << lst <<"\n";
    auto it = lst.begin();
    it++;
    it++;
    std::cout << *it << "\n";
    lst.erase_after(it);

    
    std::cout << lst;

}