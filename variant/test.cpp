#include <iostream>
#include <string>
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


template <typename Variant, size_t IDX>
struct get_pack_
{
    static auto& help(Variant& v) {
        return get_pack_<decltype(v.get_pack()), IDX - 1>::help(v.get_pack());
    }
};

template <typename Variant>
struct get_pack_<Variant, 1>
{
    static auto& help(Variant& v) {
        return v.get_pack();
    }
};

template <typename Variant>
struct get_pack_<Variant, 0>
{
    static auto help(Variant& v) {
        return v;
    }
};

template <typename Variant, size_t i>
auto& gett(Variant& t) { 
    return get_pack_<Variant, i>::help(t).get_val(); 
}

template <size_t i, typename T>
auto& get(T& t) {  
    return gett<decltype(t), i>(t); 
}


int main() {
    mylib::variant<int, std::string, int, std::string> v(33, "helanq", 999, "n");
    get<1>(v) = "aa";
    std::cout << get<3>(v) << "\n";
}