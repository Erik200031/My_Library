#include <iostream>
#include <string>
#include "../tuple/tuple.h"


int main() {
    mylib::tuple<int, std::string, int, std::string> v(33, "helanq", 999, "n");
    std::cout << mylib::get<2>(v) << '\n';
    mylib::get<2>(v) = 87;
    std::cout << mylib::get<2>(v) << "\n";
}