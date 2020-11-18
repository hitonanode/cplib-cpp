#pragma once
#include <functional>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

// CUT begin
// SMAWK: finding minima of totally monotone function f(i, j) (0 <= i < N, 0 <= j < M) for each i
// Constraints: every submatrix of f(i, j) is monotone.
// Complexity: O(N + M)
// Rererence: <https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html>
//            <http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf>
// Verify: <https://codeforces.com/contest/1423/submission/98368491>
template <typename T> struct SMAWK {
    std::vector<std::pair<int, T>> minima;
    std::function<T(int, int)> oracle;
    std::vector<std::unordered_map<int, T>> memo;
    T _query(int i, int j) {
        if (memo[i].count(j)) {
            return memo[i][j];
        } else {
            return memo[i][j] = oracle(i, j);
        }
    }

    void _smawk_rec(const std::vector<int> &js, int ib, int ie, int id) {
        if (ib > ie) return;
        std::vector<int> js2;
        int i = ib;
        for (auto j : js) {
            while (!js2.empty() and _query(i, js2.back()) >= _query(i, j)) { js2.pop_back(), i -= id; }
            if (int(js2.size()) != (ie - ib) / id) { js2.push_back(j), i += id; }
        }
        _smawk_rec(js2, ib + id, ie, id * 2);

        for (int i = ib, q = 0; i <= ie; i += id * 2) {
            int jt = (i + id <= ie ? minima[i + id].first : js.back());
            T fm = 0;
            bool init = true;
            for (; q < int(js.size()); ++q) {
                T fq = _query(i, js[q]);
                if (init or fm > fq) { fm = fq, minima[i] = std::make_pair(js[q], fq); }
                init = false;
                if (js[q] == jt) { break; }
            }
        }
    }
    SMAWK(int N, int M, std::function<T(int, int)> oracle_) : minima(N), oracle(oracle_), memo(N) {
        std::vector<int> js(M);
        std::iota(js.begin(), js.end(), 0);
        _smawk_rec(js, 0, N - 1, 1);
    }
};
