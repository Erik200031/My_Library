#include <iostream>
#include "forward_list.h"

int main() {

    mylib::Forward_list<int> lst;
    lst.push_front(111);
    lst.push_front(3);
    lst.push_front(53);
    lst.push_front(44);
        lst.push_front(3);

    lst.push_front(589);
       lst.push_front(44);
    lst.push_front(3);
    mylib::Forward_list<int> lst1;
    lst1 = lst;
    std::cout << lst1 << "\n";
    //lst.unique();
    //std::cout << "\n" <<lst;
}