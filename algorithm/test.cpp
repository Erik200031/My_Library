#include <iostream>
#include <vector>
#include "algorithm.h"


int main() {

    std::vector<int> vec {3, 2, 42, 1, 5, 9};
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    mylib::make_heap(vec.begin(), vec.end());
        std::cout << '\n';

            std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));

    mylib::pop_heap(vec.begin(), vec.end());
    std::cout << '\n';
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));


}