#pragma once
#include <array>

// Nimber (64 bit)
// Reference:
// - https://judge.yosupo.jp/submission/4542 (Original implementation idea)
// - https://en.wikipedia.org/wiki/Nimber
// - https://kyopro-friends.hatenablog.com/entry/2020/04/07/195850
struct Nimber {
    using ull = unsigned long long;
    ull v;
    const static std::array<std::array<unsigned, 256>, 256> small_table;
    const static std::array<std::array<std::array<ull, 256>, 8>, 8> precalc;

    explicit operator bool() const { return v != 0; }
    Nimber(ull val = 0) : v(val) {}
    Nimber operator+(const Nimber &x) const { return Nimber(v ^ x.v); }
    Nimber operator-(const Nimber &x) const { return Nimber(v ^ x.v); }
    Nimber operator-() const { return *this; }
    Nimber &operator+=(const Nimber &x) { return *this = *this + x; }
    Nimber &operator-=(const Nimber &x) { return *this = *this + x; }
    template <class IStream> friend IStream &operator>>(IStream &is, Nimber &x) {
        ull v;
        return is >> v, x = Nimber(v), is;
    }
    template <class OStream> friend OStream &operator<<(OStream &os, const Nimber &x) {
        return os << x.v;
    }
    bool operator==(const Nimber &x) const { return v == x.v; }
    bool operator!=(const Nimber &x) const { return v != x.v; }
    bool operator<(const Nimber &x) const { return v < x.v; }

    static ull _rec(ull x, ull y) {
        if (x == 0 or y == 0) return 0;
        if (x < y) x ^= y, y ^= x, x ^= y; // Make x >= y
        if (y == 1) return x;
        for (int shift = 64 / 2;; shift >>= 1) {
            ull mask = (1ULL << shift) - 1;
            if (y >> shift) {
                ull v00 = _rec(x & mask, y & mask);
                ull v01 = _rec(x & mask, y >> shift);
                ull v10 = _rec(x >> shift, y & mask);
                ull v11 = _rec(x >> shift, y >> shift);
                return v00 ^ ((v01 ^ v10 ^ v11) << shift) ^ _rec(v11, 1ULL << (shift - 1));
            } else if (x >> shift) {
                return (_rec(x >> shift, y) << shift) ^ _rec(x & mask, y);
            }
        }
    }
    Nimber operator*(const Nimber &x) const {
        ull ret = 0;
        for (int d = 0; d < 8; ++d) {
            for (int e = 0; e < 8; ++e) {
                ret ^= precalc[d][e][small_table[(v >> (d * 8)) & 255][(x.v >> (e * 8)) & 255]];
            }
        }
        return Nimber(ret);
    }
    Nimber &operator*=(const Nimber &x) { return *this = *this * x; }
};

const std::array<std::array<unsigned, 256>, 256> Nimber::small_table = []() {
    std::array<std::array<unsigned, 256>, 256> ret;
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) ret[i][j] = _rec(i, j);
    }
    return ret;
}();
const std::array<std::array<std::array<unsigned long long, 256>, 8>, 8> Nimber::precalc = []() {
    std::array<std::array<std::array<unsigned long long, 256>, 8>, 8> ret;
    for (int d = 0; d < 8; ++d) {
        for (int e = 0; e < 8; ++e) {
            ull p = _rec(1ULL << (8 * d), 1ULL << (8 * e));
            for (int i = 0; i < 256; ++i) ret[d][e][i] = _rec(p, i);
        }
    }
    return ret;
}();
