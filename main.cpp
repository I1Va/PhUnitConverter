#include <iostream>
#include <units.hpp>

int main() {
    Kilogram kg = 1_kg;
    Second s = 2_s;
    Meter m = 3_m;

    auto kg_s = kg * s;
    std::cout << "kg·s = " << kg_s.value << "\n";

    auto kg_s_m = kg * s * m / 1_m * 1_A;
    kg_s_m.print_dimensions();


    // auto speed = Meter(100) / Second(20) * 1.1;

    // auto a = kg_s_m + kg_s;
    // std::cout << "a = " << a.value << "\n";
    // std::cout << "m/s = " << speed.value << "\n";
}