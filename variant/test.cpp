#include <iostream>
#include <string>

#include "variant.h"

template <size_t i, typename Variant, typename T>
constexpr auto get_pack_(Variant& t) {
    if constexpr(i == 0) {
        return t;
    }
    return get_pack_<i - 1, decltype(t.get_pack()), decltype(t.get_pack().get_val())>(t.get_pack());
}

    template <size_t i, typename Variant, typename T>
  constexpr auto get(Variant& t) {
        
        return get_pack_<i, Variant, T>(t).get_val();
    }

int main() {
    mylib::variant<int, std::string, int, std::string> v(11, "helanq", 33, "n");
    std::cout << get<2, decltype(v), int>(v);
}