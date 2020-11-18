#pragma once
#include <cassert>
#include <deque>
#include <utility>

// CUT begin
// Convex Hull Trick for monotone increasing queries, monotone decreasing slopes
// Each operation is amortized O(1)
// - add_line(a, b): Add `y = ax + b`, a must be monotone decreasing (if is_minimizer == true) / increasing (otherwise)
// - add_convex_parabola(c, a, b): Add `y = c(x - a)^2 + b`, c is constant, a is monotone increasing (if is_minimizer == true) / decreasing (otherwise)
// - get(x): Calculate min/max. value of `y = ax + b`'s at point x, x must be monotone increasing FOR BOTH CASES.
// - parabola_get(c, x): Caclculate min/max. value of `y = c(x - a)^2 + b`'s, x must be monotone increasing FOR BOTH CASES.
// Verified: <https://yukicoder.me/submissions/409156>
// template<typename T_CHT>
using T_CHT = long long int;
struct MonotoneConvexHullTrick : std::deque<std::pair<T_CHT, T_CHT>> // (a, b) means `y = ax + b`
{
    using T_MP = __int128_t;
    bool is_minimizer; // If true, this instance calculates min. Otherwise, calculates max.
    MonotoneConvexHullTrick(bool is_minimizer) : is_minimizer(is_minimizer) {}
    void add_line(T_CHT a, T_CHT b) { // Add y = ax + b
        if (!is_minimizer) a = -a, b = -b;
        assert(this->empty() or this->back().first > a);
        while (this->size() > 1u) {
            int sz = this->size();
            T_MP l = (T_MP)(this->back().second - (*this)[sz - 2].second) * (this->back().first - a); // Overflow might occur here.
            T_MP r = (T_MP)(b - this->back().second) * ((*this)[sz - 2].first - this->back().first);
            if (l < r) break;
            this->pop_back();
        }
        this->emplace_back(a, b);
    }
    T_CHT get(T_CHT x) {
        while (this->size() > 1u and (*this)[0].first * x + (*this)[0].second >= (*this)[1].first * x + (*this)[1].second) { this->pop_front(); }
        return ((*this)[0].first * x + (*this)[0].second) * (is_minimizer ? 1 : -1);
    }
    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) { add_line(c * a * (-2), c * a * a + b); } // Add y = c(x - a)^2 + b
    T_CHT parabola_get(T_CHT c, T_CHT x) { return get(x) + c * x * x; }
};
