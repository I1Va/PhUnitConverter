#include <concepts>
#include <cmath>

#include "utils.hpp"

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<int... Dimensions>
struct Unit {
    double value;

    template<Arithmetic T>
    explicit Unit(T v) : value(v) {}

    static void print_dimensions() {
        std::cout << "Dimensions: ";
        ((std::cout << Dimensions << " "), ...);
        std::cout << std::endl;
    }
};

template<typename T, typename U>
struct are_dimensions_compatible;

template<int... D1, int... D2>
struct are_dimensions_compatible<Unit<D1...>, Unit<D2...>> {
    static constexpr bool value = (sizeof...(D1) == sizeof...(D2)) && 
                                  ((D1 == D2) && ...); 
};

template<typename T, typename U>
struct add_dimensions;

template<int... D1, int... D2>
struct add_dimensions<Unit<D1...>, Unit<D2...>> {
     static_assert(sizeof...(D1) == sizeof...(D2), 
                  "Units must have same number of dimensions");

    using type = Unit<(D1 + D2)...>;
};

template<typename T, typename U>
struct subtract_dimensions;

template<int... D1, int... D2>
struct subtract_dimensions<Unit<D1...>, Unit<D2...>> {
    static_assert(sizeof...(D1) == sizeof...(D2), 
                  "Units must have same number of dimensions");
    
    using type = Unit<(D1 - D2)...>; 
};

template<int... D1, int... D2>
auto operator+(const Unit<D1...>& a, const Unit<D2...>& b) {
    static_assert(are_dimensions_compatible<Unit<D1...>, Unit<D2...>>::value,
                  "Units must have same dimensions for '+'");
    return Unit<D1...>{a.value + b.value};
}

template<int... D1, int... D2>
auto operator-(const Unit<D1...>& a, const Unit<D2...>& b) {
    static_assert(are_dimensions_compatible<Unit<D1...>, Unit<D2...>>::value,
                  "Units must have same dimensions for '-'");
    return Unit<D1...>{a.value - b.value};
}

template<int... D1, int... D2>
auto operator*(const Unit<D1...>& a, const Unit<D2...>& b) {
    using result_type = typename add_dimensions<Unit<D1...>, Unit<D2...>>::type;
    return result_type{a.value * b.value};
}

template<int... D1, int... D2>
auto operator/(const Unit<D1...>& a, const Unit<D2...>& b) {
    using result_type = typename subtract_dimensions<Unit<D1...>, Unit<D2...>>::type;
    return result_type{a.value / b.value};
}

// Unit op Scalar
template<int... D>
auto operator*(const Unit<D...>& a, const double value) {
    return Unit<D...>{a.value * value};
}

template<int... D, int Value>
auto operator^(const Unit<D...>& a, std::integral_constant<int, Value> value) {
    return Unit<(D + value)...>{a.value};
}

template<int... D>
auto operator/(const Unit<D...>& a, const double value) {
    return Unit<D...>{a.value / value};
}


// Scalar op Unit
template<int... D>
auto operator*(const double value, const Unit<D...>& a) {
    return Unit<D...>{a.value * value};
}

template<int... D>
auto operator/(const double value, const Unit<D...>& a) {
    return Unit<(-D)...>{value / a.value};
}


using Kilogram = Unit<1,0,0,0>;
using Second   = Unit<0,1,0,0>;
using Meter    = Unit<0,0,1,0>;
using Ampere   = Unit<0,0,0,1>;

template<int N> 
constexpr auto scalar = std::integral_constant<int, N>{};

Kilogram operator"" _kg(unsigned long long x) {
    return Kilogram(x);
}

Second operator"" _s(unsigned long long x) {
    return Second(x);
}

Meter operator"" _m(unsigned long long x) {
    return Meter(x);
}

Ampere operator"" _A(unsigned long long x) {
    return Ampere(x);
}