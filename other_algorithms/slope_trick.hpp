#pragma once
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <utility>

// CUT begin
// Slope trick: fast operations for convex piecewise-linear functions
//
// Implementation idea:
// - https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8
// - https://ei1333.github.io/library/structure/others/slope-trick.cpp
template <class T, T INF = std::numeric_limits<T>::max() / 2> class slope_trick {
    T min_f;
    T displacement_l, displacement_r;
    std::priority_queue<T, std::vector<T>, std::less<T>> L;
    std::priority_queue<T, std::vector<T>, std::greater<T>> R;
    void pushR(const T &a) { R.push(a - displacement_r); }
    T topR() const { return R.empty() ? INF : R.top() + displacement_r; }
    T popR() {
        auto ret = topR();
        if (R.size()) R.pop();
        return ret;
    }
    void pushL(const T &a) { L.push(a + displacement_l); }
    T topL() const { return L.empty() ? -INF : L.top() - displacement_l; }
    T popL() {
        auto ret = topL();
        if (L.size()) L.pop();
        return ret;
    }
    int size() const { return L.size() + R.size8(); }

public:
    // Initialize: f(x) = 0
    slope_trick() : min_f(0), displacement_l(0), displacement_r(0) {
        static_assert(INF > 0, "INF must be greater than 0");
    }
    int sizeL() const { return L.size(); }
    int sizeR() const { return R.size(); }
    // argmin f(x), min f(x)
    using Q = struct { T min, lo, hi; };
    Q get_min() const { return {min_f, topL(), topR()}; }
    // f(x) += b
    void add_const(const T &b) { min_f += b; }
    // f(x) += max(x - a, 0)  _/
    void add_relu(const T &a) { min_f += std::max(T(0), topL() - a), pushL(a), pushR(popL()); }
    // f(x) += max(a - x, 0)  \_
    void add_irelu(const T &a) { min_f += std::max(T(0), a - topR()), pushR(a), pushL(popR()); }
    // f(x) += |x - a|  \/
    void add_abs(const T &a) { add_relu(a), add_irelu(a); }
    // f(x) <- min_{0 <= y <= w} f(x + y)  .\ -> \_
    void move_left_curve(const T &w) { assert(w >= 0), displacement_l += w; }
    // f(x) <- min_{0 <= y <= w} f(x - y)  /. -> _/
    void move_right_curve(const T &w) { assert(w >= 0), displacement_r += w; }
    // f(x) <- f(x - dx) \/. -> .\/
    void translate(const T &dx) { displacement_l -= dx, displacement_r += dx; }
    // return f(x), f destructive
    T get_destructive(const T &x) {
        T ret = get_min().min;
        while (L.size()) ret += std::max(T(0), popL() - x);
        while (R.size()) ret += std::max(T(0), x - popR());
        return ret;
    }
    // f(x) += g(x), g destructive
    void merge_destructive(slope_trick<T, INF> &g) {
        if (sizeL() + sizeR() > g.sizeL() + g.sizeR()) {
            std::swap(min_f, g.min_f);
            std::swap(displacement_l, g.displacement_l);
            std::swap(displacement_r, g.displacement_r);
            std::swap(L, g.L);
            std::swap(R, g.R);
        }
        min_f += g.get_min().min;
        while (g.L.size()) add_irelu(g.popL());
        while (g.R.size()) add_relu(g.popR());
    }
};
