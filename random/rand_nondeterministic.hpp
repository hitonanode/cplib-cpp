#pragma once
#include <chrono>
#include <random>

struct rand_int_ {
    using lint = long long;
    std::mt19937 mt;
    // rand_int_() : mt(42) {}
    rand_int_() : mt(std::chrono::steady_clock::now().time_since_epoch().count()) {}
    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)
    lint operator()(lint l, lint r) {
        std::uniform_int_distribution<lint> d(l, r - 1);
        return d(mt);
    }
} rnd;
