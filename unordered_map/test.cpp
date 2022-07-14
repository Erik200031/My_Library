#include <iostream>
// #include <functional>
// #include "unordered_map.h"
// #include <vector>
// // #include <unordered_map>
// #include <iterator>

// #include "../allocator/pool_allocator.h"
// #include <initializer_list>


int main() {
    mylib::unordered_map<int, int, mylib::hash<int>, mylib::equal_to<int>> l;
    l.insert(mylib::make_pair(11, 55));
    l.insert(mylib::make_pair(10, 23));
    l.print();
    mylib::unordered_map<int, int>::Iterator it(l);
}