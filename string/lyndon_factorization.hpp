#pragma once
#include <algorithm>
#include <cassert>
#include <functional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
// Lyndon factorization based on Duval's algorithm
// **NOT VERIFIED YET**
// Reference:
// [1] K. T. Chen, R. H. Fox, R. C. Lyndon,
//     "Free Differential Calculus, IV. The Quotient Groups of the Lower Central Series,"
//     Annals of Mathematics, 68(1), 81-95, 1958.
// [2] J. P. Duval, "Factorizing words over an ordered alphabet,"
//     Journal of Algorithms, 4(4), 363-381, 1983.
// - https://cp-algorithms.com/string/lyndon_factorization.html
// - https://qiita.com/nakashi18/items/66882bd6e0127174267a
template <typename T>
std::vector<std::pair<int, int>> lyndon_factorization(const std::vector<T> &S) {
    const int N = S.size();
    std::vector<std::pair<int, int>> ret;
    for (int l = 0; l < N;) {
        int i = l, j = i + 1;
        while (j < N and S[i] <= S[j]) i = (S[i] == S[j] ? i + 1 : l), j++;
        int n = (j - l) / (j - i);
        for (int t = 0; t < n; t++) ret.emplace_back(l, j - i), l += j - i;
    }
    return ret;
}

std::vector<std::pair<int, int>> lyndon_factorization(const std::string &s) {
    const int N = int(s.size());
    std::vector<int> v(N);
    for (int i = 0; i < N; i++) v[i] = s[i];
    return lyndon_factorization<int>(v);
}

// Compute the longest Lyndon prefix for each suffix s[i:N]
// (Our implementation is $O(N \cdot (complexity of lcplen()))$)
// Example:
// - `teletelepathy` -> [1,4,1,2,1,4,1,2,1,4,1,2,1]
// Reference:
// [1] H. Bannai et al., "The "Runs" Theorem,"
//     SIAM Journal on Computing, 46(5), 1501-1514, 2017.
template <typename String, typename LCPLENCallable>
std::vector<int> longest_lyndon_prefixes(const String &s, const LCPLENCallable &lcp) {
    const int N = s.size();
    std::vector<std::pair<int, int>> st{{N, N}};
    std::vector<int> ret(N);
    for (int i = N - 1, j = i; i >= 0; i--, j = i) {
        while (st.size() > 1) {
            int iv = st.back().first, jv = st.back().second;
            int l = lcp.lcplen(i, iv);
            if (!(iv + l < N and s[i + l] < s[iv + l])) break;
            j = jv;
            st.pop_back();
        }
        st.emplace_back(i, j);
        ret[i] = j - i + 1;
    }
    return ret;
}

// Compute all runs in given string
// Complexity: $O(N \cdot (complexity of lcplen()))$ in this implementation
// (Theoretically $O(N)$ achievable)
// N = 2e5 -> ~120 ms
// Reference:
// [1] H. Bannai et al., "The "Runs" Theorem,"
//     SIAM Journal on Computing, 46(5), 1501-1514, 2017.
template <typename LCPLENCallable, typename String>
std::vector<std::tuple<int, int, int>> run_enumerate(String s) {
    if (s.empty()) return {};
    LCPLENCallable lcp(s);
    std::reverse(s.begin(), s.end());
    LCPLENCallable revlcp(s);
    std::reverse(s.begin(), s.end());
    auto t = s;
    auto lo = *std::min_element(s.begin(), s.end()), hi = *std::max_element(s.begin(), s.end());
    for (auto &c : t) c = hi - (c - lo);
    auto l1 = longest_lyndon_prefixes(s, lcp), l2 = longest_lyndon_prefixes(t, lcp);
    int N = s.size();
    std::vector<std::tuple<int, int, int>> ret;
    for (int i = 0; i < N; i++) {
        int j = i + l1[i], L = i - revlcp.lcplen(N - i, N - j), R = j + lcp.lcplen(i, j);
        if (R - L >= (j - i) * 2) ret.emplace_back(j - i, L, R);

        if (l1[i] != l2[i]) {
            j = i + l2[i], L = i - revlcp.lcplen(N - i, N - j), R = j + lcp.lcplen(i, j);
            if (R - L >= (j - i) * 2) ret.emplace_back(j - i, L, R);
        }
    }
    std::sort(ret.begin(), ret.end());
    ret.erase(std::unique(ret.begin(), ret.end()), ret.end());
    return ret;
}

// Enumerate Lyndon words up to length n in lexical order
// https://github.com/bqi343/USACO/blob/master/Implementations/content/combinatorial%20(11.2)/DeBruijnSeq.h
// Example: k=2, n=4 => [[0,],[0,0,0,1,],[0,0,1,],[0,0,1,1,],[0,1,],[0,1,1,],[0,1,1,1,],[1,],]
// Verified: https://codeforces.com/gym/102001/problem/C / https://codeforces.com/gym/100162/problem/G
std::vector<std::vector<int>> enumerate_lyndon_words(int k, int n) {
    assert(k > 0);
    assert(n > 0);
    std::vector<std::vector<int>> ret;
    std::vector<int> aux(n + 1);

    std::function<void(int, int)> gen = [&](int t, int p) {
        // t: current length
        // p: current min cycle length
        if (t == n) {
            std::vector<int> tmp(aux.begin() + 1, aux.begin() + p + 1);
            ret.push_back(std::move(tmp));
        } else {
            ++t;
            aux[t] = aux[t - p];
            gen(t, p);
            while (++aux[t] < k) gen(t, t);
        }
    };
    gen(0, 1);
    return ret;
}
