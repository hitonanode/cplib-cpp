#pragma once
#include <bit>
#include <functional>
#include <numeric>
#include <type_traits>

// Calculate next point to check in floating point "binary" search
double bisect_mid_fp(double a, double b) {
    auto encode = [&](double x) -> unsigned long long {
        auto tmp = std::bit_cast<unsigned long long>(x);
        // Give -0.0 and +0.0 the same code, as they compare equal in bisect().
        return (tmp >> 63) ? (0ULL - tmp) : (tmp ^ (1ULL << 63));
    };

    auto decode = [&](unsigned long long x) -> double {
        auto tmp = (x >> 63) ? (x ^ (1ULL << 63)) : (0ULL - x);
        return std::bit_cast<double>(tmp);
    };

    unsigned long long tmp = std::midpoint(encode(a), encode(b));

    return decode(tmp);
}

// Binary search
// Maintain f(ok) = true and f(ng) = false and return (ok, ng)
// Final (ok, ng) satisfies |ok - ng| <= abs_tol
template <class T> auto bisect(T ok, T ng, const std::function<bool(T)> &f, T abs_tol = T()) {
    struct Result {
        T ok, ng;
    };

    while (true) {
        T mid;
        if constexpr (std::is_floating_point<T>::value) {
            mid = bisect_mid_fp(ok, ng);
        } else {
            mid = std::midpoint(ok, ng);
        }
        if (mid == ok or mid == ng) break;
        (f(mid) ? ok : ng) = mid;
        if (ok - ng <= abs_tol and ng - ok <= abs_tol) break;
    }

    return Result{ok, ng};
}
