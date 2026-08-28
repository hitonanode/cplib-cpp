#pragma once
#include <cassert>
#include <chrono>
#include <cstdint>
#include <random>

struct RNGMt19937 {
    using lint = long long;
    std::mt19937 mt;
    RNGMt19937(long long seed) : mt(seed) {}
    lint operator()(lint x) { // [0, x)
        assert(x > 0);
        return this->operator()(0, x);
    }
    lint operator()(lint l, lint r) {
        assert(l < r);
        std::uniform_int_distribution<lint> d(l, r - 1);
        return d(mt);
    }
};
// RNGMt19937 rnd(123456789);
// RNGMt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

// Fast random number generator based on xoshiro256++.
struct FastRNG {
    using ull = unsigned long long;
    ull s[4];

    static ull rotl(ull x, int k) { return (x << k) | (x >> (64 - k)); }

    static ull splitmix64(ull &x) {
        ull z = (x += 0x9e3779b97f4a7c15ULL);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
        return z ^ (z >> 31);
    }

    FastRNG(ull seed) {
        for (auto &x : s) x = splitmix64(seed);
    }

    ull next_u64() {
        ull res = rotl(s[0] + s[3], 23) + s[0];
        ull t = s[1] << 17;

        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];

        s[2] ^= t;
        s[3] = rotl(s[3], 45);

        return res;
    }

    uint32_t next_u32() { return next_u64() >> 32; }

    // [0, n)
    uint32_t operator()(uint32_t n) {
        assert(n > 0);
        return (uint64_t(next_u32()) * n) >> 32;
    }

    // [l, r)
    int operator()(int l, int r) {
        assert(l < r);
        uint32_t width = uint64_t(int64_t(r) - int64_t(l));
        return int(int64_t(l) + (*this)(width));
    }

    uint16_t next_u16() { return next_u64() >> 48; }
};
inline FastRNG rnd(123456789);
// FastRNG rnd(std::chrono::steady_clock::now().time_since_epoch().count());
