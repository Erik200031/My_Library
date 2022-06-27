#include <iostream>
#include <functional>
#include <set>
#include "unordered_map.h"
#include "../allocator/pool_allocator.h"

int main() {
    // mylib::unordered_map<int, int> l;
    // // l.insert(mylib::make_pair(11, 22));
    // l.insert(mylib::make_pair(10, 2));
    // std::cout << l[10];
//    std::set<int, std::less<int>, mylib::Pool_alloc<int>> m {1,2,3,4,5};
//    for (auto &&i : m)
//    {
//        std::cout << i << " ";
//    }
    mylib::Pool_alloc<int> p;
    mylib::Pool_alloc<float> t(p);


}