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


template <typename Variant, size_t IDX>
struct get_pack_
{
    get_pack_(const Variant& t) : ob{t} {}
    auto operator()() {
        return get_pack_<decltype(ob.get_pack()), IDX - 1>(ob.get_pack());
    }
    Variant ob;
};


template <typename Variant>
struct get_pack_<Variant, 1>
{
    get_pack_(const Variant& t) : ob{t} {}
    auto operator()() {
        return ob.get_pack();
    }
    Variant ob;

};
template <typename Variant>
struct get_pack_<Variant, 0>
{
    get_pack_(const Variant& t) : ob{t} {}
    Variant operator()() {
        return ob;
    }
    Variant ob;

};



template <typename Variant, size_t i>
std::any gett(const Variant& t) {
    
    //return get_pack_<Variant, i>(t).get_val();
    return get_pack_<Variant, i>(t).ob.get_val();
}



int main() {
    mylib::variant<int, std::string, int, std::string> v(11, "helanq", 33, "n");
   std::cout <<std::any_cast<int>(gett<decltype(v), 0>(v));
}