#pragma once
#include "slope_trick.hpp"

// https://maspypy.com/slope-trick-3-slope-trick-%E3%81%AE%E5%87%B8%E5%85%B1%E5%BD%B9
// Verified: https://yukicoder.me/problems/no/2114
template <class T, T INF = std::numeric_limits<T>::max() / 2>
class dual_slope_trick : private slope_trick<T, INF> {
public:
    using Base = slope_trick<T, INF>;

    // Initialize: f(x) = 0 (x == 0), inf (otherwise)
    // Complexity: O(1)
    dual_slope_trick() : Base() {}

    // Get f(0)
    // Complexity: O(1)
    T get_at_zero() const { return -Base::get_min().min; }

    // f(x) <- f(x - d) (Move graph to right by d)
    // Complexity: O(log n)
    dual_slope_trick &shift(int d) {
        while (d > 0) --d, Base::add_relu(-INF).add_const(-INF);
        while (d < 0) ++d, Base::add_irelu(INF).add_const(-INF);
        return *this;
    }

    // f(x) += ax + b
    // Complexity: O(log n)
    dual_slope_trick &add_linear(T a, T b) { return Base::translate(a).add_const(b), *this; }

    // f(x) += max(c(x - a), 0)
    // Complexity: O(|a| log n)
    dual_slope_trick &add_linear_or_zero(T c, int a) {
        shift(-a);
        if (c > T()) Base::move_right_curve(c);
        if (c < T()) Base::move_left_curve(-c);
        return shift(a);
    }

    // f(x) <- min f(x - d), a <= d <= b
    // Complexity: O((|a| + |b|) log n)
    dual_slope_trick &slide_min(int a, int b) {
        assert(a <= b);
        shift(a);
        for (int t = 0; t < b - a; ++t) Base::add_relu(T());
        return *this;
    }
};
