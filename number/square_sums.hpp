#pragma once
#include <cmath>

#include "sqrt_mod.hpp"

// Fermat's theorem on sums of two squares
// Solve x^2 + y^2 = p for prime p, where p != 3 (mod 4)
template <class Int> std::pair<Int, Int> SumOfTwoSquaresPrime(Int p) {
    if (p == 2) return {1, 1};
    if (p % 4 != 1) return {-1, -1};

    Int r0 = p, r1 = sqrt_mod<Int>(p - 1, p);
    for (const Int limit = std::sqrtl(p); r1 > limit;) {
        Int next_r = r0 % r1;
        r0 = r1, r1 = next_r;
    }

    return std::minmax(r1, (Int)std::sqrtl(p - r1 * r1));
}
