template<int K, int S, int M>
struct Unit {
    double value;

    explicit Unit(double v) : value(v) {}

    template<int K2, int S2, int M2>
    Unit& operator+=(const Unit<K2, S2, M2>& rhs) {
        static_assert(K==K2 && S==S2 && M==M2, "Units must match for `+=`");
        value += rhs.value;
        return *this;
    }

    template<int K2, int S2, int M2>
    Unit<K2, S2, M2> operator+(const Unit<K2, S2, M2>& rhs) const {
        static_assert(K == K2 && S == S2 && M == M2, "Units must match for `+`");
        Unit<K,S,M> tmp{value};
        tmp.value += rhs.value;
        return tmp;
    }

    template<int K2, int S2, int M2>
    Unit& operator-=(const Unit<K2, S2, M2>& rhs) {
        static_assert(K==K2 && S==S2 && M==M2, "Units must match for `-=`");
        value -= rhs.value;
        return *this;
    }

    template<int K2, int S2, int M2>
    Unit<K2, S2, M2> operator-(const Unit<K2, S2, M2>& rhs) const {
        static_assert(K == K2 && S == S2 && M == M2, "Units must match for `-`");
        Unit<K,S,M> tmp{value};
        tmp.value -= rhs.value;
        return tmp;
    }

    static void print_unit() {
        std::cout << K << " " << S << " " << M << "\n";
    }
};

template<int K1,int S1,int M1>
Unit<K1,S1,M1> operator*(const Unit<K1,S1,M1>& a, const double value) {
    return Unit<K1,S1,M1>(a.value * value);
}

template<int K1,int S1,int M1>
Unit<K1,S1,M1> operator/(const Unit<K1,S1,M1>& a, const double value) {
    return Unit<K1,S1,M1>(a.value / value);
}

template<int K1,int S1,int M1>
Unit<K1,S1,M1> operator*(const double value, const Unit<K1,S1,M1>& a) {
    return Unit<K1,S1,M1>(a.value * value);
}

template<int K1,int S1,int M1>
Unit<-K1,-S1,-M1> operator/(const double value, const Unit<K1,S1,M1>& a) {
    return Unit<-K1,-S1,-M1>(a.value / value);
}


template<int K1,int S1,int M1,int K2,int S2,int M2>
Unit<K1-K2, S1-S2, M1-M2> operator/(const Unit<K1,S1,M1>& a, const Unit<K2,S2,M2>& b) {
    return Unit<K1-K2, S1-S2, M1-M2>(a.value / b.value);
}

template<int K1,int S1,int M1,int K2,int S2,int M2>
Unit<K1+K2, S1+S2, M1+M2> operator*(const Unit<K1,S1,M1>& a, const Unit<K2,S2,M2>& b) {
    return Unit<K1+K2, S1+S2, M1+M2>(a.value * b.value);
}


using Kilogram = Unit<1,0,0>;
using Second   = Unit<0,1,0>;
using Meter    = Unit<0,0,1>;

Kilogram operator"" _kg(unsigned long long x) {
    return Kilogram(x);
}

Second operator"" _s(unsigned long long x) {
    return Second(x);
}

Meter operator"" _m(unsigned long long x) {
    return Meter(x);
}