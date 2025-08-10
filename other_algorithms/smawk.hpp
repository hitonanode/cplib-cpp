#pragma once
#include <cassert>
#include <functional>
#include <numeric>
#include <utility>
#include <vector>

// SMAWK: finding minima of totally monotone function f(i, j) (0 <= i < N, 0 <= j < M) for each i
// Constraints: every submatrix of f(i, j) is monotone.
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

// Concave max-plus convolution
// b must be concave
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

    bool a_concave = is_concave(a), b_concave = is_concave(b);
    assert(a_concave or b_concave);
    if (!b_concave) return concave_max_plus_convolution<S, INF>(b, a);

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
