---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: formal_power_series/linear_recurrence.hpp
    title: "\u7DDA\u5F62\u6F38\u5316\u5F0F\u306E\u767A\u898B\u30FB\u7B2C $N$ \u9805\
      \u63A8\u5B9A"
  - icon: ':x:'
    path: random/rand_nondeterministic.hpp
    title: random/rand_nondeterministic.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
    title: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://yukicoder.me/wiki/black_box_linear_algebra
  bundledCode: "#line 2 \"linear_algebra_matrix/det_of_sparse_matrix.hpp\"\n#include\
    \ <cassert>\n#include <numeric>\n#include <utility>\n#include <vector>\n\n#line\
    \ 2 \"formal_power_series/linear_recurrence.hpp\"\n#include <algorithm>\n#line\
    \ 6 \"formal_power_series/linear_recurrence.hpp\"\n\n// CUT begin\n// Berlekamp\u2013\
    Massey algorithm\n// https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm\n\
    // Complexity: O(N^2)\n// input: S = sequence from field K\n// return: L     \
    \     = degree of minimal polynomial,\n//         C_reversed = monic min. polynomial\
    \ (size = L + 1, reversed order, C_reversed[0] = 1))\n// Formula: convolve(S,\
    \ C_reversed)[i] = 0 for i >= L\n// Example:\n// - [1, 2, 4, 8, 16]   -> (1, [1,\
    \ -2])\n// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])\n// - [0, 0, 0, 0, 1]    ->\
    \ (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)\n// - []                 ->\
    \ (0, [1])\n// - [0, 0, 0]          -> (0, [1])\n// - [-2]               -> (1,\
    \ [1, 2])\ntemplate <typename Tfield> std::pair<int, std::vector<Tfield>> find_linear_recurrence(const\
    \ std::vector<Tfield> &S) {\n    int N = S.size();\n    using poly = std::vector<Tfield>;\n\
    \    poly C_reversed{1}, B{1};\n    int L = 0, m = 1;\n    Tfield b = 1;\n\n \
    \   // adjust: C(x) <- C(x) - (d / b) x^m B(x)\n    auto adjust = [](poly C, const\
    \ poly &B, Tfield d, Tfield b, int m) -> poly {\n        C.resize(std::max(C.size(),\
    \ B.size() + m));\n        Tfield a = d / b;\n        for (unsigned i = 0; i <\
    \ B.size(); i++) C[i + m] -= a * B[i];\n        return C;\n    };\n\n    for (int\
    \ n = 0; n < N; n++) {\n        Tfield d = S[n];\n        for (int i = 1; i <=\
    \ L; i++) d += C_reversed[i] * S[n - i];\n\n        if (d == 0)\n            m++;\n\
    \        else if (2 * L <= n) {\n            poly T = C_reversed;\n          \
    \  C_reversed = adjust(C_reversed, B, d, b, m);\n            L = n + 1 - L;\n\
    \            B = T;\n            b = d;\n            m = 1;\n        } else\n\
    \            C_reversed = adjust(C_reversed, B, d, b, m++);\n    }\n    return\
    \ std::make_pair(L, C_reversed);\n}\n\n// Calculate $x^N \\bmod f(x)$\n// Known\
    \ as `Kitamasa method`\n// Input: f_reversed: monic, reversed (f_reversed[0] =\
    \ 1)\n// Complexity: $O(K^2 \\log N)$ ($K$: deg. of $f$)\n// Example: (4, [1,\
    \ -1, -1]) -> [2, 3]\n//          ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2\
    \ )\n// Reference: http://misawa.github.io/others/fast_kitamasa_method.html\n\
    //            http://sugarknri.hatenablog.com/entry/2017/11/18/233936\ntemplate\
    \ <typename Tfield>\nstd::vector<Tfield> monomial_mod_polynomial(long long N,\
    \ const std::vector<Tfield> &f_reversed) {\n    assert(!f_reversed.empty() and\
    \ f_reversed[0] == 1);\n    int K = f_reversed.size() - 1;\n    if (!K) return\
    \ {};\n    int D = 64 - __builtin_clzll(N);\n    std::vector<Tfield> ret(K, 0);\n\
    \    ret[0] = 1;\n    auto self_conv = [](std::vector<Tfield> x) -> std::vector<Tfield>\
    \ {\n        int d = x.size();\n        std::vector<Tfield> ret(d * 2 - 1);\n\
    \        for (int i = 0; i < d; i++) {\n            ret[i * 2] += x[i] * x[i];\n\
    \            for (int j = 0; j < i; j++) ret[i + j] += x[i] * x[j] * 2;\n    \
    \    }\n        return ret;\n    };\n    for (int d = D; d--;) {\n        ret\
    \ = self_conv(ret);\n        for (int i = 2 * K - 2; i >= K; i--) {\n        \
    \    for (int j = 1; j <= K; j++) ret[i - j] -= ret[i] * f_reversed[j];\n    \
    \    }\n        ret.resize(K);\n        if ((N >> d) & 1) {\n            std::vector<Tfield>\
    \ c(K);\n            c[0] = -ret[K - 1] * f_reversed[K];\n            for (int\
    \ i = 1; i < K; i++) { c[i] = ret[i - 1] - ret[K - 1] * f_reversed[K - i]; }\n\
    \            ret = c;\n        }\n    }\n    return ret;\n}\n\n// Guess k-th element\
    \ of the sequence, assuming linear recurrence\n// initial_elements: 0-ORIGIN\n\
    // Verify: abc198f https://atcoder.jp/contests/abc198/submissions/21837815\ntemplate\
    \ <typename Tfield> Tfield guess_kth_term(const std::vector<Tfield> &initial_elements,\
    \ long long k) {\n    assert(k >= 0);\n    if (k < static_cast<long long>(initial_elements.size()))\
    \ return initial_elements[k];\n    const auto f = find_linear_recurrence<Tfield>(initial_elements).second;\n\
    \    const auto g = monomial_mod_polynomial<Tfield>(k, f);\n    Tfield ret = 0;\n\
    \    for (unsigned i = 0; i < g.size(); i++) ret += g[i] * initial_elements[i];\n\
    \    return ret;\n}\n#line 2 \"random/rand_nondeterministic.hpp\"\n#include <chrono>\n\
    #include <random>\nusing namespace std;\n\n// CUT begin\nstruct rand_int_ {\n\
    \    using lint = long long;\n    mt19937 mt;\n    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)\n\
    \    lint operator()(lint l, lint r) {\n        uniform_int_distribution<lint>\
    \ d(l, r - 1);\n        return d(mt);\n    }\n} rnd;\n#line 9 \"linear_algebra_matrix/det_of_sparse_matrix.hpp\"\
    \n\n// CUT begin\n// Sparse matrix on ModInt/ModIntRuntime\ntemplate <typename\
    \ Tp> struct sparse_matrix {\n    int H, W;\n    std::vector<std::vector<std::pair<int,\
    \ Tp>>> vals;\n    sparse_matrix(int H = 0, int W = 0) : H(H), W(W), vals(H) {}\n\
    \    void add_element(int i, int j, Tp val) {\n        assert(i >= 0 and i < H);\n\
    \        assert(j >= 0 and i < W);\n        vals[i].emplace_back(j, val);\n  \
    \  }\n    Tp eval_bilinear(const std::vector<Tp> &vl, const std::vector<Tp> &vr)\
    \ const {\n        assert(vl.size() == H and vr.size() == W);\n        Tp ret\
    \ = 0;\n        for (int i = 0; i < H; i++) {\n            for (const auto &p\
    \ : vals[i]) { ret += vl[i] * p.second * vr[p.first]; }\n        }\n        return\
    \ ret;\n    }\n    static std::vector<Tp> prod(const sparse_matrix<Tp> &M, const\
    \ std::vector<Tp> &vec) {\n        assert(M.W == int(vec.size()));\n        std::vector<Tp>\
    \ ret(M.H);\n        for (int i = 0; i < M.H; i++) {\n            for (const auto\
    \ &p : M.vals[i]) { ret[i] += p.second * vec[p.first]; }\n        }\n        return\
    \ ret;\n    }\n    // Determinant of sparse matrix\n    // Complexity: O(NK +\
    \ N^2) (K: # of non-zero elements in M)\n    // Reference: https://yukicoder.me/wiki/black_box_linear_algebra\n\
    \    Tp Determinant() const {\n        assert(H == W);\n        const int N =\
    \ H, hi = Tp::mod();\n        std::vector<Tp> b(N), u(N), D(N);\n        for (int\
    \ i = 0; i < N; i++) { b[i] = rnd(1, hi), u[i] = rnd(1, hi), D[i] = rnd(1, hi);\
    \ }\n        std::vector<Tp> uMDib(2 * N);\n        for (int i = 0; i < 2 * N;\
    \ i++) {\n            uMDib[i] = std::inner_product(u.begin(), u.end(), b.begin(),\
    \ Tp(0));\n            for (int j = 0; j < N; j++) { b[j] *= D[j]; }\n       \
    \     b = prod(*this, b);\n        }\n        auto ret = find_linear_recurrence<Tp>(uMDib);\n\
    \        Tp det = ret.second.back() * (N % 2 ? -1 : 1);\n        Tp ddet = 1;\n\
    \        for (auto d : D) ddet *= d;\n        return det / ddet;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\n#include \"../formal_power_series/linear_recurrence.hpp\"\
    \n#include \"../random/rand_nondeterministic.hpp\"\n\n// CUT begin\n// Sparse\
    \ matrix on ModInt/ModIntRuntime\ntemplate <typename Tp> struct sparse_matrix\
    \ {\n    int H, W;\n    std::vector<std::vector<std::pair<int, Tp>>> vals;\n \
    \   sparse_matrix(int H = 0, int W = 0) : H(H), W(W), vals(H) {}\n    void add_element(int\
    \ i, int j, Tp val) {\n        assert(i >= 0 and i < H);\n        assert(j >=\
    \ 0 and i < W);\n        vals[i].emplace_back(j, val);\n    }\n    Tp eval_bilinear(const\
    \ std::vector<Tp> &vl, const std::vector<Tp> &vr) const {\n        assert(vl.size()\
    \ == H and vr.size() == W);\n        Tp ret = 0;\n        for (int i = 0; i <\
    \ H; i++) {\n            for (const auto &p : vals[i]) { ret += vl[i] * p.second\
    \ * vr[p.first]; }\n        }\n        return ret;\n    }\n    static std::vector<Tp>\
    \ prod(const sparse_matrix<Tp> &M, const std::vector<Tp> &vec) {\n        assert(M.W\
    \ == int(vec.size()));\n        std::vector<Tp> ret(M.H);\n        for (int i\
    \ = 0; i < M.H; i++) {\n            for (const auto &p : M.vals[i]) { ret[i] +=\
    \ p.second * vec[p.first]; }\n        }\n        return ret;\n    }\n    // Determinant\
    \ of sparse matrix\n    // Complexity: O(NK + N^2) (K: # of non-zero elements\
    \ in M)\n    // Reference: https://yukicoder.me/wiki/black_box_linear_algebra\n\
    \    Tp Determinant() const {\n        assert(H == W);\n        const int N =\
    \ H, hi = Tp::mod();\n        std::vector<Tp> b(N), u(N), D(N);\n        for (int\
    \ i = 0; i < N; i++) { b[i] = rnd(1, hi), u[i] = rnd(1, hi), D[i] = rnd(1, hi);\
    \ }\n        std::vector<Tp> uMDib(2 * N);\n        for (int i = 0; i < 2 * N;\
    \ i++) {\n            uMDib[i] = std::inner_product(u.begin(), u.end(), b.begin(),\
    \ Tp(0));\n            for (int j = 0; j < N; j++) { b[j] *= D[j]; }\n       \
    \     b = prod(*this, b);\n        }\n        auto ret = find_linear_recurrence<Tp>(uMDib);\n\
    \        Tp det = ret.second.back() * (N % 2 ? -1 : 1);\n        Tp ddet = 1;\n\
    \        for (auto d : D) ddet *= d;\n        return det / ddet;\n    }\n};\n"
  dependsOn:
  - formal_power_series/linear_recurrence.hpp
  - random/rand_nondeterministic.hpp
  isVerificationFile: false
  path: linear_algebra_matrix/det_of_sparse_matrix.hpp
  requiredBy: []
  timestamp: '2021-06-06 14:54:00+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
documentation_of: linear_algebra_matrix/det_of_sparse_matrix.hpp
layout: document
redirect_from:
- /library/linear_algebra_matrix/det_of_sparse_matrix.hpp
- /library/linear_algebra_matrix/det_of_sparse_matrix.hpp.html
title: linear_algebra_matrix/det_of_sparse_matrix.hpp
---
