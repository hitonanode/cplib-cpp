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
// Verifyed: <https://codeforces.com/gym/101806/problem/R>
template <bool is_minimizer, typename T_CHT = long long, typename T_MP = __int128, T_CHT INF = 1LL << 61>
struct AddMonotoneConvexHullTrick // (a, b) means `y = ax + b`
{
    std::deque<std::pair<T_CHT, T_CHT>> q;
    AddMonotoneConvexHullTrick() {}
    void add_line(T_CHT a, T_CHT b) { // Add y = ax + b
        if (!is_minimizer) a = -a, b = -b;
        if (q.empty())
            q.emplace_back(a, b);
        else if (q.back().first >= a) {
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
    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) { add_line(c * a * (-2), c * a * a + b); } // Add y = c(x - a)^2 + b
    T_CHT parabola_get(T_CHT c, T_CHT x) const { return get(x) + c * x * x; }
};
