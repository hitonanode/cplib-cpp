#pragma once
#include <cassert>
#include <list>
#include <utility>

// CUT begin
// Convex Hull Trick for monotone increasing queries, monotone decreasing slopes
// Each operation is amortized O(1)
// - is_minimizer: if true, calculates min. Otherwise, calculates max.
// - add_line(a, b): Add `y = ax + b`, a must be monotone decreasing (if is_minimizer == true) / increasing (otherwise)
// - add_convex_parabola(c, a, b): Add `y = c(x - a)^2 + b`, c is constant, a is monotone increasing (if is_minimizer == true) / decreasing (otherwise)
// - get(x): Calculate min/max. value of `y = ax + b`'s at point x, x must be monotone increasing FOR BOTH CASES.
// - parabola_get(c, x): Caclculate min/max. value of `y = c(x - a)^2 + b`'s, x must be monotone increasing FOR BOTH CASES.
// - If you need random access, change `std::list` to `std::deque`
// Verified: <https://yukicoder.me/submissions/409156>
template <bool is_minimizer, typename T_CHT = long long, typename T_MP = __int128, T_CHT INF = 1LL << 61>
struct MonotoneConvexHullTrick : std::list<std::pair<T_CHT, T_CHT>> // (a, b) means `y = ax + b`
{
    MonotoneConvexHullTrick() = default;
    void add_line(T_CHT a, T_CHT b) { // Add y = ax + b
        if (!is_minimizer) a = -a, b = -b;
        assert(this->empty() or this->back().first >= a);
        while (this->size() > 1u) {
            if (this->back().first == a) {
                if (this->back().second <= b) {
                    return;
                } else {
                    this->pop_back();
                    continue;
                }
            }
            auto ill = std::prev(this->end(), 2);
            auto l = (T_MP)(this->back().second - ill->second) * (this->back().first - a); // Overflow might occur here.
            auto r = (T_MP)(b - this->back().second) * (ill->first - this->back().first);
            if (l < r) break;
            this->pop_back();
        }
        this->emplace_back(a, b);
    }
    T_CHT get(T_CHT x) {
        while (this->size() > 1u and
               this->begin()->first * x + this->begin()->second >= (++this->begin())->first * x + (++this->begin())->second)
            this->pop_front();
        return (this->empty() ? INF : this->begin()->first * x + this->begin()->second) * (is_minimizer ? 1 : -1);
    }
    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) { add_line(c * a * (-2), c * a * a + b); }
    T_CHT parabola_get(T_CHT c, T_CHT x) { return get(x) + c * x * x; }

    static MonotoneConvexHullTrick merge(const MonotoneConvexHullTrick &cht1, const MonotoneConvexHullTrick &cht2) {
        MonotoneConvexHullTrick ret;
        auto i1 = cht1.begin(), i2 = cht2.begin();
        static const T_CHT sgn = is_minimizer ? 1 : -1;
        T_CHT a = 0, b = 0;
        while (i1 != cht1.end() and i2 != cht2.end()) {
            if (i1->first == i2->first) {
                a = i1->first, b = std::min(i1->second, i2->second);
                i1++, i2++;
            } else if (i1->first > i2->first) {
                a = i1->first, b = i1->second, i1++;
            } else {
                a = i2->first, b = i2->second, i2++;
            }
            ret.add_line(a * sgn, b * sgn);
        }
        while (i1 != cht1.end()) ret.add_line(i1->first * sgn, i1->second * sgn), i1++;
        while (i2 != cht2.end()) ret.add_line(i2->first * sgn, i2->second * sgn), i2++;
        return ret;
    }
};
