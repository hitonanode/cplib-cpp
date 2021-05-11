#pragma once
#include <cassert>
#include <utility>
#include <vector>

// ax^2 + bx + c (convex), lb <= x <= ub
struct Quadratic {
    using Int = long long;
    Int a, b, c, lb, ub;
    Quadratic(Int a, Int b, Int c, Int lb, Int ub) : a(a), b(b), c(c), lb(lb), ub(ub) {}
    Int slope(Int s) const noexcept {
        if (a == 0) return b <= s ? ub : lb;
        auto ret = (s + a - b) / (a * 2);
        return ret > ub ? ub : ret < lb ? lb : ret;
    }
    Int eval(Int x) const noexcept { return (a * x + b) * x + c; }
    // f(x) - f(x - 1)
    Int next_cost(Int x) const noexcept { return 2 * a * x - a + b; }
};

// x^3 - ax, x \geq 0 (convex)
struct Cubic {
    int a, lb, ub;
    Cubic(int a, int ub) : a(a), lb(0), ub(ub) {}
    int slope(long long s) const noexcept {
        int lo = lb, hi = ub + 1;
        while (hi - lo > 1) {
            int x = (lo + hi) / 2;
            (next_cost(x) <= s ? lo : hi) = x;
        }
        return lo;
    }
    long long eval(long long x) const noexcept { return (x * x - a) * x; }
    // f(x) - f(x - 1)
    long long next_cost(long long x) const noexcept { return 3 * x * x - 3 * x + 1 - a; }
};

// \minimize $\sum_i \sum_j^{k_i} f_i(x_{ij})$
// https://codeforces.com/contest/1344/problem/D
// https://yukicoder.me/problems/no/1495
// return: (y, [[(x_i, # of such x_i), ... ], ...])
template <typename F, typename Int, Int INF>
std::pair<Int, std::vector<std::vector<std::pair<Int, Int>>>> MinConvexSumUnderLinearConstraint(const std::vector<Int> &k, const std::vector<F> &f, Int C) {
    assert(k.size() == f.size());
    assert(k.size() > 0);
    Int lbsum = 0, ubsum = 0;
    for (auto func : f) lbsum += func.lb, ubsum += func.ub;
    if (lbsum > C or ubsum < C) return {};

    const int N = k.size();
    Int few = -INF, enough = INF;
    while (enough - few > 1) {
        auto slope = few + (enough - few) / 2;
        Int cnt = 0;
        for (int i = 0; i < N; i++) {
            auto tmp = f[i].slope(slope);
            cnt += tmp * k[i];
            if (cnt >= C) break;
        }
        (cnt >= C ? enough : few) = slope;
    }

    std::vector<std::vector<std::pair<Int, Int>>> ret(N);
    std::vector<int> additional;
    Int ctmp = 0;
    Int sol = 0;
    for (int i = 0; i < N; i++) {
        auto xlo = f[i].slope(few);
        auto xhi = f[i].slope(few + 1);
        ctmp += k[i] * xlo;
        ret[i].emplace_back(xlo, k[i]);
        if (xlo < xhi) additional.push_back(i);
        sol += k[i] * f[i].eval(xlo);
    }
    sol += (C - ctmp) * (few + 1);
    while (additional.size()) {
        int i = additional.back();
        additional.pop_back();
        Int add = C - ctmp > k[i] ? k[i] : C - ctmp;
        auto x = ret[i][0].first;
        if (add) {
            ret[i][0].second -= add;
            if (ret[i][0].second == 0) ret[i].pop_back();
            ret[i].emplace_back(x + 1, add);
            ctmp += add;
        }
    }
    return {sol, ret};
}
