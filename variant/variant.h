#ifndef VARIANT_H
#define VARIANT_H

#include <type_traits>

namespace mylib
{
    template <typename... Types>
    class variant;
   
    template <typename T, typename... Types>
    class variant <T, Types...>
    {
    public:
        typedef T value_type;
        constexpr variant() = default;
        explicit constexpr variant(const T& val, const Types&... types) : value (val), pack(types...) {}
        variant(const variant<T, Types...>& rhs) = default;
        variant(variant<T, Types...>&& rhs) = default;
        variant<T, Types...>& operator=(const variant<T, Types...>& rhs) = default;
        variant<T, Types...>& operator=(variant<T, Types...>&& rhs) = default;
        variant(const variant<T>& rhs) : value(rhs.value) {}
        template <typename U>
        variant(const variant<U>& rhs) : value(rhs.value) {}
        template <typename U>
        variant(variant<U>& rhs) : value(rhs.value) {}
        template <typename U, typename... UTypes>
        variant(variant<U, UTypes...>& rhs) : value(rhs.value), pack (rhs.pack) {}
        template <typename U, typename... UTypes>
        variant(const variant<U, UTypes...>& rhs) : value(rhs.value), pack (rhs.pack) {}        
        template <typename U, typename... UTypes>
        variant(variant<U, UTypes...>&& rhs) :  value(std::move(rhs.value)), pack(std::move(rhs.pack)) {}
        template <typename U, typename... UTypes>
        variant<T, Types...>& operator=(const variant<U, UTypes...>& rhs) {
            value = rhs.value;
            if constexpr(sizeof...(UTypes) > 1){
                pack = rhs.pack;
            }
            return *this;
        }
        template <typename U, typename... UTypes>
        variant<T, Types...>& operator=(variant<U, UTypes...>&& rhs) {
            value = std::move(rhs.value);
            pack = std::move(rhs.pack);
            return *this;
        }
        
        T& operator[](size_t index) {
            if(index == 0) {
                return value;
            }
           return pack[--index];
        }
        const T& operator[](size_t index) const {
            if(index == 0) {
                return value;
            }
            return pack[--index];
        }
        
        auto& get_val() {return value;}
        constexpr auto& get_pack() {return pack;}
        template <typename U>
        U& operator[](size_t index) 
        {
            if(index == 0) {
                return value;
            }
           return pack[--index];
        }
        template <typename U>
        const U& operator[](size_t index) const
        {
            if(index == 0) {
                return value;
            }
            return pack[--index];
        }

        void swap(variant& rhs)
        {
            variant tmp = std::move(*this);
            *this = std::move(rhs);
            rhs = std::move(tmp);
        }
         
        ~variant() = default;
    public:
        T value;
        variant<Types...> pack; 
    };

    template <typename T>
    class variant <T>
    {
    public:
        typedef T value_type;
        constexpr variant() = default;
        explicit constexpr variant(T val) : value {val} {}
        variant(const variant<T>& rhs) = default;
        variant(variant<T>&& rhs) = default;
        variant<T>& operator=(const variant<T>& rhs) = default;
        variant<T>& operator=(variant<T>&& rhs) = default;
        template <typename U>
        variant(const variant<U>& rhs) : value(rhs.value) {}
        template <typename U>
        variant(variant<U>&& rhs) :  value(std::move(rhs.value)) {}
        template <typename U>
        variant<T>& operator=(const variant<U>& rhs) {
            value = rhs.value;
            return *this;
        }
        template <typename U>
        variant<T>& operator=(variant<U>&& rhs) {
            value = std::move(rhs.value);
            return *this;
        }
        auto& operator[](size_t index) {return value;}
        const auto& operator[](size_t index) const 
        {
            return value;
        }
        auto& get_val() {return value;}
        void swap(variant& rhs)
        {
            variant tmp = std::move(*this);
            *this = std::move(rhs);
            rhs = std::move(tmp);
        }
        ~variant() = default;
    public:
        T value;
    };

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

} // namespace mylib

#endif //VARIANT_H