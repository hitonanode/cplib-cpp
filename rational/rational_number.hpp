#pragma once
#include <iostream>

// CUT begin
// Rational number + {infinity(1 / 0), -infiity(-1 / 0)} （有理数）
struct Rational {
    using Int = long long int; // __int128
    Int num, den;
    static Int my_gcd(Int a, Int b) {
        // return __gcd(a, b);
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (a and b) {
            if (a > b) a %= b;
            else b %= a;
        }
        return a + b;
    }
    Rational(Int num = 0, Int den = 1) : num(num), den(den) { normalize(); }
    void normalize() { // reduction and making denominator nonnegative
        Int g = my_gcd(num, den); num /= g, den /= g;
        if (den < 0) num = -num, den = -den;
    }
    Rational operator+(const Rational &r) const { return Rational(num * r.den + den * r.num, den * r.den); }
    Rational operator-(const Rational &r) const { return Rational(num * r.den - den * r.num, den * r.den); }
    Rational operator*(const Rational &r) const { return Rational(num * r.num, den * r.den); }
    Rational operator/(const Rational &r) const { return Rational(num * r.den, den * r.num); }
    Rational &operator+=(const Rational &r) { return *this = *this + r; }
    Rational &operator-=(const Rational &r) { return *this = *this - r; }
    Rational &operator*=(const Rational &r) { return *this = *this * r; }
    Rational &operator/=(const Rational &r) { return *this = *this / r; }
    Rational operator-() const { return Rational(-num, den); }
    Rational abs() const { return Rational(num > 0 ? num : -num, den); }
    bool operator==(const Rational &r) const { return num == r.num and den == r.den; }
    bool operator!=(const Rational &r) const { return num != r.num or den != r.den; }
    bool operator<(const Rational &r) const {
        if (den == 0 and r.den == 0) return num < r.num;
        else if (den == 0) return num < 0;
        else if (r.den == 0) return r.num > 0;
        else return num * r.den < den * r.num;
    }
    bool operator<=(const Rational &r) const { return (*this == r) or (*this < r); }
    bool operator>(const Rational &r) const { return r < *this; }
    explicit operator double() const { return (double)num / (double)den; }
    explicit operator long double() const { return (long double)num / (long double)den; }
    friend std::ostream &operator<<(std::ostream &os, const Rational &x) { os << x.num << '/' << x.den; return os; }
};
