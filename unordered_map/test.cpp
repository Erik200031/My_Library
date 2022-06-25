#include <iostream>
#include <vector>
// #include <functional>
// #include "unordered_map.h"
#include <math.h>
#include <string>

int foo(const std::vector<int>& f, const std::vector<int>& s) {
    int count{};
    for(int i{}, j{}; i < f.size() && j < f.size();) {
        if(f[i] == s[j]) {
            ++count;
            ++i;
        } else if(f[i] < s[j]) {
            ++i;
        } else {
            ++j;
        }
    }
    return count;
}


int main() {
    std::vector<int> f {13, 27, 35, 40, 49, 55, 59};
    std::vector<int> s {17, 35, 39, 40, 55, 58, 60};
    std::cout << foo(f, s);
}