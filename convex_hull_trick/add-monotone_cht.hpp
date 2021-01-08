#pragma once
#include <deque>
#include <utility>

// CUT begin
// Convex Hull Trick for monotone insertions
// - is_minimizer: if true, calculates min. Otherwise, calculates max.
// - add_line(a, b): Add `y = ax + b`, O(1) if `a` must be largest or smallest, or do nothing otherwise.
// - add_convex_parabola(c, a, b): Add `y = c(x - a)^2 + b`, c is constant
// - get(x): Calculate min/max. value of `y = ax + b`'s at point x, O(logN)
// - parabola_get(c, x): Caclculate min/max. value of `y = c(x - a)^2 + b`'s
// - merge(): merge two CHTs in linear time
// Verified: <https://codeforces.com/gym/101806/problem/R>
//           <https://atcoder.jp/contests/pakencamp-2020-day2/submissions/19262614>
template <bool is_minimizer, typename T_CHT = long long, typename T_MP = __int128, T_CHT INF = 1LL << 61>
struct AddMonotoneConvexHullTrick {
    std::deque<std::pair<T_CHT, T_CHT>> q; // [(a0, b0), ..., (ai, bi), ...], a0 > a1 > a2 > ...
    AddMonotoneConvexHullTrick() {}
    void add_line(T_CHT a, T_CHT b) { // Add y = ax + b
        if (!is_minimizer) a = -a, b = -b;
        if (q.empty()) {
            q.emplace_back(a, b);
        } else if (q.size() == 1) {
            if (q.front().first == a) {
                if (b < q.front().second) q.front().second = b;
            } else if (q.front().first > a) {
                q.emplace_back(a, b);
            } else {
                q.emplace_front(a, b);
            }
        } else if (q.back().first >= a) {
            while (q.size() > 1u) {
                if (q.back().first == a and q.back().second <= b) return;
                int sz = q.size();
                T_MP l = (T_MP)(q.back().second - q[sz - 2].second) * (q.back().first - a); // Overflow might occur here.
                T_MP r = (T_MP)(b - q.back().second) * (q[sz - 2].first - q.back().first);
                if (l < r) break;
                q.pop_back();
            }
            q.emplace_back(a, b);
        } else if (q[0].first <= a) {
            while (q.size() > 1u) {
                if (q[0].first == a and q[0].second <= b) return;
                T_MP l = (T_MP)(q[0].second - q[1].second) * (q[0].first - a);
                T_MP r = (T_MP)(b - q[0].second) * (q[1].first - q[0].first);
                if (l > r) break;
                q.pop_front();
            }
            q.emplace_front(a, b);
        }
    }

    T_CHT _get_idx(int i, T_CHT x) const { return q[i].first * x + q[i].second; }

    T_CHT get(T_CHT x) const {
        if (q.empty()) return INF * (is_minimizer ? 1 : -1);
        int l = 0, r = q.size();
        while (l + 1 < r) {
            int c = (l + r) / 2, clo = c - 1;
            (_get_idx(clo, x) >= _get_idx(c, x) ? l : r) = c;
        }
        return _get_idx(l, x) * (is_minimizer ? 1 : -1);
    }

    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) { add_line(c * a * (-2), c * a * a + b); }
    T_CHT parabola_get(T_CHT c, T_CHT x) const { return get(x) + c * x * x; }

    static AddMonotoneConvexHullTrick merge(const AddMonotoneConvexHullTrick &cht1, const AddMonotoneConvexHullTrick &cht2) {
        AddMonotoneConvexHullTrick ret;
        auto i1 = cht1.q.begin(), i2 = cht2.q.begin();
        static const T_CHT sgn = is_minimizer ? 1 : -1;
        T_CHT a = 0, b = 0;
        while (i1 != cht1.q.end() and i2 != cht2.q.end()) {
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
        while (i1 != cht1.q.end()) ret.add_line(i1->first * sgn, i1->second * sgn), i1++;
        while (i2 != cht2.q.end()) ret.add_line(i2->first * sgn, i2->second * sgn), i2++;
        return ret;
    }
};
