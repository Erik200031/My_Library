#include <iostream>
#include <string>
#include <any>
#include "variant.h"


// template <typename Variant, size_t i>
// auto get_pack_(Variant& t) {
//     return get_pack_<decltype(t.get_pack()), i - 1>(t.get_pack());
// }

// // template <typename Variant>
// // auto get_pack_<Variant, 0>(Variant& t) {
// //     return t;
// // }

// template <typename Variant>
// auto get_pack_<Variant, 1>(Variant& t) {
//     return t.get_pack();
// }

template < typename Variant, size_t i>
int get_pack_(Variant t) {
    return 111111;
}

// template <typename Variant>
// auto get_pack_<Variant, 0>(Variant& t) {
//     return t;
// }

template <typename Variant>
 void get_pack_<0>(Variant t) {
     std::cout << "hee";
}





template <typename Variant, size_t i>
std::any gett(Variant& t) {
    
    //return get_pack_<Variant, i>(t).get_val();
    return get_pack_<Variant, i>(t);
}



int main() {
    mylib::variant<int, std::string, int, std::string> v(11, "helanq", 33, "n");
   std::cout <<std::any_cast<int>(gett<decltype(v), 0>(v));
}