#pragma once

#include <iostream>

template <typename T>
struct is_integral {
    static const bool value = false;
};

#define BUILD_INTEGRAL_SPECIALIZATION(type, val) \
template <> struct is_integral<type>           { static const bool value = val; };
BUILD_INTEGRAL_SPECIALIZATION(bool, true)

BUILD_INTEGRAL_SPECIALIZATION(char, true)
BUILD_INTEGRAL_SPECIALIZATION(signed char, true)
BUILD_INTEGRAL_SPECIALIZATION(unsigned char, true)

BUILD_INTEGRAL_SPECIALIZATION(short, true)
BUILD_INTEGRAL_SPECIALIZATION(unsigned short, true)

BUILD_INTEGRAL_SPECIALIZATION(int, true)
BUILD_INTEGRAL_SPECIALIZATION(unsigned int, true)

BUILD_INTEGRAL_SPECIALIZATION(long, true)
BUILD_INTEGRAL_SPECIALIZATION(unsigned long, true)

BUILD_INTEGRAL_SPECIALIZATION(long long, true)
BUILD_INTEGRAL_SPECIALIZATION(unsigned long long, true)
#undef BUILD_INTEGRAL_SPECIALIZATION


template <bool Cond, typename T = void>
struct my_enable_if {};

template <typename T>
struct my_enable_if<true, T> {
    typedef T type;
};


template <typename T, typename U> 
typename my_enable_if<is_integral<T>::value && is_integral<U>::value, T>::type 
integer_pow(T base, U exponent) {
    if (exponent < 0) {
        throw std::invalid_argument("Negative exponents not supported for integer power");
    }
    
    T result = 1;
    T current = base;
    
    while (exponent > 0) {
        if (exponent & 1) {  
            result *= current;
        }
        current *= current;
        exponent >>= 1; 
    }
    
    return result;
}
