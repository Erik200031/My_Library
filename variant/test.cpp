#include <iostream>
#include <string>

#include "variant.h"

 template <size_t i, typename Variant, typename T>
    T& get(Variant& t) {
        // size_t index = i;
        // if(index == 0) {
        //     return t.value;
        // }
        // while(index) {
        //     t.ge
        //     --index;
        // }
        return t.pack_val();
    }
    // template <size_t i, typename Variant, typename T>
    // const T& get(const Variant& t) {
    //     //std::cout << "get";
        
    //     return t[i];
    // }

int main() {
    mylib::variant<int, std::string, int, std::string> v(11, "helanq", 33, "n");
   // v.get_val() = "ban";
    std::cout << v.get_pack_val();
   // sdt::cout << get<0, decltype(v), int>(v);
}