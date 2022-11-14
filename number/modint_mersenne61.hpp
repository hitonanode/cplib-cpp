#pragma once
#include <cassert>
#include <chrono>
#include <random>

// F_p, p = 2^61 - 1
// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
class ModIntMersenne61 {
    static const long long md = (1LL << 61) - 1;
    long long _v;

    inline unsigned hi() const noexcept { return _v >> 31; }
    inline unsigned lo() const noexcept { return _v & ((1LL << 31) - 1); }

public:
    static long long mod() { return md; }

    ModIntMersenne61() : _v(0) {}
    // 0 <= x < md * 2
    explicit ModIntMersenne61(long long x) : _v(x >= md ? x - md : x) {}

    long long val() const noexcept { return _v; }

    ModIntMersenne61 operator+(const ModIntMersenne61 &x) const {
        return ModIntMersenne61(_v + x._v);
    }

    ModIntMersenne61 operator-(const ModIntMersenne61 &x) const {
        return ModIntMersenne61(_v + md - x._v);
    }

    ModIntMersenne61 operator*(const ModIntMersenne61 &x) const {
        using ull = unsigned long long;

        ull uu = (ull)hi() * x.hi() * 2;
        ull ll = (ull)lo() * x.lo();
        ull lu = (ull)hi() * x.lo() + (ull)lo() * x.hi();

        ull sum = uu + ll + ((lu & ((1ULL << 30) - 1)) << 31) + (lu >> 30);
        ull reduced = (sum >> 61) + (sum & ull(md));
        return ModIntMersenne61(reduced);
    }

    ModIntMersenne61 pow(long long n) const {
        assert(n >= 0);
        ModIntMersenne61 ans(1), tmp = *this;
        while (n) {
            if (n & 1) ans *= tmp;
            tmp *= tmp, n >>= 1;
        }
        return ans;
    }

    ModIntMersenne61 inv() const { return pow(md - 2); }

    ModIntMersenne61 operator/(const ModIntMersenne61 &x) const { return *this * x.inv(); }

    ModIntMersenne61 operator-() const { return ModIntMersenne61(md - _v); }
    ModIntMersenne61 &operator+=(const ModIntMersenne61 &x) { return *this = *this + x; }
    ModIntMersenne61 &operator-=(const ModIntMersenne61 &x) { return *this = *this - x; }
    ModIntMersenne61 &operator*=(const ModIntMersenne61 &x) { return *this = *this * x; }
    ModIntMersenne61 &operator/=(const ModIntMersenne61 &x) { return *this = *this / x; }

    ModIntMersenne61 operator+(unsigned x) const { return ModIntMersenne61(this->_v + x); }

    bool operator==(const ModIntMersenne61 &x) const { return _v == x._v; }
    bool operator!=(const ModIntMersenne61 &x) const { return _v != x._v; }
    bool operator<(const ModIntMersenne61 &x) const { return _v < x._v; } // To use std::map

    template <class OStream> friend OStream &operator<<(OStream &os, const ModIntMersenne61 &x) {
        return os << x._v;
    }

    static ModIntMersenne61 randgen(bool force_update = false) {
        static ModIntMersenne61 b(0);
        if (b == ModIntMersenne61(0) or force_update) {
            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<long long> d(1, ModIntMersenne61::mod());
            b = ModIntMersenne61(d(mt));
        }
        return b;
    }
};
