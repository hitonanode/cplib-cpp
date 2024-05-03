#pragma once
#include <algorithm>
#include <utility>
#include <vector>

template <class Int> struct f2_vector_space {
    std::vector<Int> basis;

    f2_vector_space() = default;

    Int add(Int x) {
        for (const Int &b : basis) x = std::min(x, x ^ b);

        if (x) {
            basis.push_back(x);
            return x;
        } else {
            return Int(0);
        }
    }
};

std::vector<int> f2_intersection(const std::vector<int> &A, const std::vector<int> &B) {
    f2_vector_space<long long> tmp;
    for (int a : A) tmp.add(((long long)a << 32) + a);

    std::vector<int> ret;

    for (int b : B) {
        long long v = (long long)b << 32;

        auto u = tmp.add(v);
        if (u < (1LL << 32)) ret.push_back(u);
    }

    return ret;
}
