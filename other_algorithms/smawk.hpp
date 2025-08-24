#pragma once
#include <cassert>
#include <functional>
#include <numeric>
#include <utility>
#include <vector>

// SMAWK: finding minima of totally monotone function f(i, j) (0 <= i < N, 0 <= j < M) for each i
// Constraints: every submatrix of f(i, j) is monotone (= totally monotone).
// Complexity: O(N + M)
// Reference:
// https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html
// http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf
// Verify: https://codeforces.com/contest/1423/submission/98368491
template <class T>
std::vector<std::pair<int, T>> SMAWK(int N, int M, const std::function<T(int i, int j)> &weight) {
    std::vector<std::pair<int, T>> minima(N);

    auto rec = [&](auto &&self, const std::vector<int> &js, int ib, int ie, int id) {
        if (ib > ie) return;
        std::vector<int> js2;
        int i = ib;
        for (int j : js) {
            while (!js2.empty() and weight(i, js2.back()) >= weight(i, j)) js2.pop_back(), i -= id;
            if (int(js2.size()) != (ie - ib) / id) js2.push_back(j), i += id;
        }
        self(self, js2, ib + id, ie, id * 2);

        for (int i = ib, q = 0; i <= ie; i += id * 2) {
            const int jt = (i + id <= ie ? minima[i + id].first : js.back());
            T fm = 0;
            bool init = true;
            for (; q < int(js.size()); ++q) {
                const T fq = weight(i, js[q]);
                if (init or fm > fq) fm = fq, minima[i] = std::make_pair(js[q], fq);
                init = false;
                if (js[q] == jt) break;
            }
        }
    };

    std::vector<int> js(M);
    std::iota(js.begin(), js.end(), 0);
    rec(rec, js, 0, N - 1, 1);

    return minima;
}

// Find minima of totally ANTI-monotone function f(i, j) (0 <= i < N, 0 <= j < M) for each i
// Constraints: every submatrix of f(i, j) is anti-monotone.
// Complexity: O(N + M)
template <class T>
std::vector<std::pair<int, T>>
SMAWKAntiMonotone(int N, int M, const std::function<T(int i, int j)> &weight) {
    auto minima = SMAWK<T>(N, M, [&](int i, int j) -> T { return weight(i, M - 1 - j); });
    for (auto &p : minima) p.first = M - 1 - p.first;
    return minima;
}

// Concave max-plus convolution
// **b MUST BE CONCAVE**
// Complexity: O(n + m)
// Verify: https://www.codechef.com/problems/MAXPREFFLIP
template <class S, S INF>
std::vector<S> concave_max_plus_convolution(const std::vector<S> &a, const std::vector<S> &b) {
    const int n = a.size(), m = b.size();

    auto is_concave = [&](const std::vector<S> &u) -> bool {
        for (int i = 1; i + 1 < int(u.size()); ++i) {
            if (u[i - 1] + u[i + 1] > u[i] + u[i]) return false;
        }
        return true;
    };
    assert(is_concave(b));

    auto select = [&](int i, int j) -> S {
        int aidx = j, bidx = i - j;
        if (bidx < 0 or bidx >= m or aidx >= n) return INF;
        return -(a[aidx] + b[bidx]);
    };
    const auto minima = SMAWK<S>(n + m - 1, n, select);
    std::vector<S> ret;
    for (auto x : minima) ret.push_back(-x.second);
    return ret;
}

// Concave min-plus convolution
// **b MUST BE CONCAVE**
// Complexity: O((n + m)log(n + m))
template <class S>
std::vector<S> concave_min_plus_convolution(const std::vector<S> &a, const std::vector<S> &b) {
    const int n = a.size(), m = b.size();

    auto is_concave = [&](const std::vector<S> &u) -> bool {
        for (int i = 1; i + 1 < int(u.size()); ++i) {
            if (u[i - 1] + u[i + 1] > u[i] + u[i]) return false;
        }
        return true;
    };
    assert(is_concave(b));

    std::vector<S> ret(n + m - 1);
    std::vector<int> argmin(n + m - 1, -1);

    // mat[i][j] = a[j] + b[i - j]
    auto is_valid = [&](int i, int j) { return 0 <= i - j and i - j < m; };
    auto has_valid = [&](int il, int ir, int jl, int jr) {
        if (il >= ir or jl >= jr) return false;
        return is_valid(il, jl) or is_valid(il, jr - 1) or is_valid(ir - 1, jl) or
               is_valid(ir - 1, jr - 1);
    };

    auto rec = [&](auto &&self, int il, int ir, int jl, int jr) -> void {
        if (!has_valid(il, ir, jl, jr)) return;

        if (is_valid(il, jr - 1) and is_valid(ir - 1, jl)) {
            auto select = [&](int i, int j) -> S { return a[j + jl] + b[(i + il) - (j + jl)]; };
            const auto res = SMAWKAntiMonotone<S>(ir - il, jr - jl, select);
            for (int idx = 0; idx < ir - il; ++idx) {
                const int i = il + idx;
                if (argmin[i] == -1 or res[idx].second < ret[i]) {
                    ret[i] = res[idx].second;
                    argmin[i] = res[idx].first + jl;
                }
            }
        } else {
            if (const int di = ir - il, dj = jr - jl; di > dj) {
                const int im = (il + ir) / 2;
                self(self, il, im, jl, jr);
                self(self, im, ir, jl, jr);
            } else {
                const int jm = (jl + jr) / 2;
                self(self, il, ir, jl, jm);
                self(self, il, ir, jm, jr);
            }
        }
    };

    rec(rec, 0, n + m - 1, 0, n);

    return ret;
    // return argmin;  // If you want argmin (0 <= argmin[idx] < len(a))
}
