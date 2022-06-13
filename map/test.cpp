#include <iostream>

#include "map.h"


int main() {

    mylib::map<int, int> l;
   l.insert(mylib::make_pair(1, 99));
//         l.insert(mylib::make_pair(12, 7));
    l.insert(mylib::make_pair(13, 1200));
    l.print();
    std::cout << l.at(13);
//  auto itr = l.begin();
//  ++itr;
//     std::cout << (*itr).first;

}