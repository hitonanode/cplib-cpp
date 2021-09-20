#pragma once
#include <cassert>
#include <list>
#include <utility>

// CUT begin
// Convex Hull Trick for monotone increasing queries, monotone decreasing slopes
// Each operation is amortized O(1)
// - is_minimizer: if true, calculates min. Otherwise, calculates max.
// - insert_line(a, b): Insert `y = ax + b`,
//   a must be monotone decreasing (if is_minimizer == true) / increasing (otherwise)
// - add_convex_parabola(c, a, b): Add `y = c(x - a)^2 + b`, c is constant, a is monotone
//   increasing (if is_minimizer == true) / decreasing (otherwise)
// - get(x): Calculate min/max. value of `y = ax + b`'s at point x, x must be monotone
//   increasing FOR BOTH CASES.
// - parabola_get(c, x): Caclculate min/max. value of `y = c(x - a)^2 + b`'s, x must be monotone
//   increasing FOR BOTH CASES.
// - If you need random access, change `std::list` to `std::deque`
// Verified: https://yukicoder.me/submissions/409156
template <bool is_minimizer, class T = long long, class T_MP = __int128, T INF = 1LL << 61>
class MonotoneConvexHullTrick : std::list<std::pair<T, T>> {
    // (a, b) means `y = ax + b`
    T_MP _eval(typename std::list<std::pair<T, T>>::const_iterator itr, T x) {
        return T_MP(itr->first) * x + itr->second;
    }

public:
    MonotoneConvexHullTrick() { static_assert(INF > 0, "INF must be positive."); }
    void insert_line(T a, T b) { // Add y = ax + b
        if (!is_minimizer) a = -a, b = -b;
        assert(this->empty() or this->back().first >= a);
        while (this->size() > 1u) {
            if (this->back().first == a) {
                if (this->back().second <= b) return;
                this->pop_back();
                continue;
            }
            auto ill = std::prev(this->end(), 2);
            auto l = (T_MP)(this->back().second - ill->second) * (this->back().first - a);
            auto r = (T_MP)(b - this->back().second) * (ill->first - this->back().first);
            if (l < r) break;
            this->pop_back();
        }
        this->emplace_back(a, b);
    }

    struct Ret {
        T line_a, line_b;
        bool is_valid;
        T_MP val;
    };
    Ret get(T x) {
        if (this->empty()) return {0, 0, false, is_minimizer ? INF : -INF};
        while (this->size() > 1 and _eval(this->begin(), x) >= _eval(std::next(this->begin()), x)) {
            this->pop_front();
        }
        T_MP val = _eval(this->begin(), x) * (is_minimizer ? 1 : -1);
        return {(is_minimizer ? 1 : -1) * this->begin()->first,
                (is_minimizer ? 1 : -1) * this->begin()->second, true, val};
    }
    void insert_convex_parabola(T c, T a, T b) { insert_line(c * a * (-2), c * a * a + b); }
    T_MP parabola_get(T c, T x) { return get(x).val + c * x * x; }

    static MonotoneConvexHullTrick
    merge(const MonotoneConvexHullTrick &cht1, const MonotoneConvexHullTrick &cht2) {
        MonotoneConvexHullTrick ret;
        auto i1 = cht1.begin(), i2 = cht2.begin();
        static const T sgn = is_minimizer ? 1 : -1;
        T a = 0, b = 0;
        while (i1 != cht1.end() and i2 != cht2.end()) {
            if (i1->first == i2->first) {
                a = i1->first, b = std::min(i1->second, i2->second);
                ++i1, ++i2;
            } else if (i1->first > i2->first) {
                a = i1->first, b = i1->second, ++i1;
            } else {
                a = i2->first, b = i2->second, ++i2;
            }
            ret.insert_line(a * sgn, b * sgn);
        }
        while (i1 != cht1.end()) ret.insert_line(i1->first * sgn, i1->second * sgn), ++i1;
        while (i2 != cht2.end()) ret.insert_line(i2->first * sgn, i2->second * sgn), ++i2;
        return ret;
    }
};
