#include <iostream>
#include <functional>
#include "unordered_map.h"
// #include <unordered_map>

int main() {
    mylib::unordered_map<int, int> l;
    l.insert(mylib::make_pair(11, 22));
    l.insert(mylib::make_pair(111, 23));
    std::cout << l[111];
   
}