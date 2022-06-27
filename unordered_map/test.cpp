#include <iostream>
#include <functional>
#include <map>
#include "unordered_map.h"
#include "../allocator/pool_allocator.h"

int main() {
    mylib::unordered_map<int, int> l;
    l.insert(mylib::make_pair(11, 22));
    l.insert(mylib::make_pair(10, 2));
    std::cout << l[10];
   


}