#pragma once
#include <cassert>
#include <limits>

// Rational number + {infinity(1 / 0), -infiity(-1 / 0), nan(0 / 0)} （有理数）
// Verified: Yandex Cup 2022 Final E https://contest.yandex.com/contest/42710/problems/K
template <class Int, bool AutoReduce = false> struct Rational {
    Int num, den; // den >= 0

    static constexpr Int my_gcd(Int a, Int b) {
        // return __gcd(a, b);
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (a and b) {
            if (a > b) {
                a %= b;
            } else {
                b %= a;
            }
        }
        return a + b;
    }

    constexpr Rational(Int num = 0, Int den = 1) : num(num), den(den) { normalize(); }
    constexpr void normalize() noexcept {
        if constexpr (AutoReduce) { // reduction
            Int g = my_gcd(num, den);
            if (g) num /= g, den /= g;
        } else {
            if (den == 0) {
                if (num > 1) num = 1;
                if (num < -1) num = -1;
            }
        }
        if (den < 0) num = -num, den = -den; // denominator >= 0
    }

    constexpr bool is_finite() const noexcept { return den != 0; }
    constexpr bool is_infinite_or_nan() const noexcept { return den == 0; }

    constexpr Rational operator+(const Rational &r) const noexcept {
        if (is_infinite_or_nan() and r.is_infinite_or_nan()) return Rational(num + r.num, 0);
        return Rational(num * r.den + den * r.num, den * r.den);
    }
    constexpr Rational operator-(const Rational &r) const noexcept {
        if (is_infinite_or_nan() and r.is_infinite_or_nan()) return Rational(num - r.num, 0);
        return Rational(num * r.den - den * r.num, den * r.den);
    }
    constexpr Rational operator*(const Rational &r) const noexcept {
        return Rational(num * r.num, den * r.den);
    }
    constexpr Rational operator/(const Rational &r) const noexcept {
        return Rational(num * r.den, den * r.num);
    }
    constexpr Rational &operator+=(const Rational &r) noexcept { return *this = *this + r; }
    constexpr Rational &operator-=(const Rational &r) noexcept { return *this = *this - r; }
    constexpr Rational &operator*=(const Rational &r) noexcept { return *this = *this * r; }
    constexpr Rational &operator/=(const Rational &r) noexcept { return *this = *this / r; }
    constexpr Rational operator-() const noexcept { return Rational(-num, den); }
    constexpr Rational abs() const noexcept { return Rational(num > 0 ? num : -num, den); }

    constexpr Int floor() const {
        assert(is_finite());
        if (num > 0) {
            return num / den;
        } else {
            return -((-num + den - 1) / den);
        }
    }

    constexpr bool operator==(const Rational &r) const noexcept {
        if (is_infinite_or_nan() or r.is_infinite_or_nan()) {
            return num == r.num and den == r.den;
        } else {
            return num * r.den == r.num * den;
        }
    }

    constexpr bool operator!=(const Rational &r) const noexcept { return !(*this == r); }

    constexpr bool operator<(const Rational &r) const noexcept {
        if (is_infinite_or_nan() and r.is_infinite_or_nan())
            return num < r.num;
        else if (is_infinite_or_nan()) {
            return num < 0;
        } else if (r.is_infinite_or_nan()) {
            return r.num > 0;
        } else {
            return num * r.den < den * r.num;
        }
    }
    constexpr bool operator<=(const Rational &r) const noexcept {
        return (*this == r) or (*this < r);
    }
    constexpr bool operator>(const Rational &r) const noexcept { return r < *this; }
    constexpr bool operator>=(const Rational &r) const noexcept {
        return (r == *this) or (r < *this);
    }

    constexpr explicit operator double() const noexcept { return (double)num / (double)den; }
    constexpr explicit operator long double() const noexcept {
        return (long double)num / (long double)den;
    }
    template <class OStream> constexpr friend OStream &operator<<(OStream &os, const Rational &x) {
        return os << x.num << '/' << x.den;
    }
};

template <class Int> struct std::numeric_limits<Rational<Int, false>> {
    static constexpr Rational<Int, false> max() noexcept {
        return std::numeric_limits<Int>::max();
    }
    static constexpr Rational<Int, false> min() noexcept {
        return std::numeric_limits<Int>::min();
    }
    static constexpr Rational<Int, false> lowest() noexcept {
        return std::numeric_limits<Int>::lowest();
    }
};
