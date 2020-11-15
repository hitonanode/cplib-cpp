---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: linear_algebra_matrix/linear_recurrence.hpp
    title: linear_algebra_matrix/linear_recurrence.hpp
  - icon: ':question:'
    path: random/rand_nondeterministic.hpp
    title: random/rand_nondeterministic.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
    title: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://yukicoder.me/wiki/black_box_linear_algebra>
  bundledCode: "#line 2 \"linear_algebra_matrix/det_of_sparse_matrix.hpp\"\n#include\
    \ <cassert>\n#include <numeric>\n#include <utility>\n#include <vector>\n\n#line\
    \ 2 \"random/rand_nondeterministic.hpp\"\n#include <chrono>\n#include <random>\n\
    using namespace std;\n\n// CUT begin\nstruct rand_int_\n{\n    using lint = long\
    \ long;\n    mt19937 mt;\n    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)\n\
    \    lint operator()(lint l, lint r) {\n        uniform_int_distribution<lint>\
    \ d(l, r - 1);\n        return d(mt);\n    }\n} rnd;\n#line 2 \"linear_algebra_matrix/linear_recurrence.hpp\"\
    \n#include <algorithm>\n#line 6 \"linear_algebra_matrix/linear_recurrence.hpp\"\
    \n\n// CUT begin\n// Berlekamp\u2013Massey algorithm\n// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>\n\
    // Complexity: O(N^2)\n// input: S = sequence from field K\n// return: L     \
    \     = degree of minimal polynomial,\n//         C_reversed = monic min. polynomial\
    \ (size = L + 1, reversed order, C_reversed[0] = 1))\n// Formula: convolve(S,\
    \ C_reversed)[i] = 0 for i >= L\n// Example:\n// - [1, 2, 4, 8, 16]   -> (1, [1,\
    \ -2])\n// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])\n// - [0, 0, 0, 0, 1]    ->\
    \ (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)\n// - []                 ->\
    \ (0, [1])\n// - [0, 0, 0]          -> (0, [1])\n// - [-2]               -> (1,\
    \ [1, 2])\ntemplate <typename Tfield>\nstd::pair<int, std::vector<Tfield>> linear_recurrence(const\
    \ std::vector<Tfield> &S)\n{\n    int N = S.size();\n    using poly = std::vector<Tfield>;\n\
    \    poly C_reversed{1}, B{1};\n    int L = 0, m = 1;\n    Tfield b = 1;\n\n \
    \   // adjust: C(x) <- C(x) - (d / b) x^m B(x)\n    auto adjust = [](poly C, const\
    \ poly &B, Tfield d, Tfield b, int m) -> poly {\n        C.resize(std::max(C.size(),\
    \ B.size() + m));\n        Tfield a = d / b;\n        for (unsigned i = 0; i <\
    \ B.size(); i++) C[i + m] -= a * B[i];\n        return C;\n    };\n\n    for (int\
    \ n = 0; n < N; n++) {\n        Tfield d = S[n];\n        for (int i = 1; i <=\
    \ L; i++) d += C_reversed[i] * S[n - i];\n\n        if (d == 0) m++;\n       \
    \ else if (2 * L <= n) {\n            poly T = C_reversed;\n            C_reversed\
    \ = adjust(C_reversed, B, d, b, m);\n            L = n + 1 - L;\n            B\
    \ = T;\n            b = d;\n            m = 1;\n        }\n        else C_reversed\
    \ = adjust(C_reversed, B, d, b, m++);\n    }\n    return std::make_pair(L, C_reversed);\n\
    }\n#line 9 \"linear_algebra_matrix/det_of_sparse_matrix.hpp\"\n\n// CUT begin\n\
    // Sparse matrix on ModInt/ModIntRuntime\ntemplate <typename Tp>\nstruct sparse_matrix\n\
    {\n    int H, W;\n    std::vector<std::vector<std::pair<int, Tp>>> vals;\n   \
    \ sparse_matrix(int H = 0, int W = 0) : H(H), W(W), vals(H) {}\n    void add_element(int\
    \ i, int j, Tp val)\n    {\n        assert(i >= 0 and i < H);\n        assert(j\
    \ >= 0 and i < W);\n        vals[i].emplace_back(j, val);\n    }\n    Tp eval_bilinear(const\
    \ std::vector<Tp> &vl, const std::vector<Tp> &vr) const\n    {\n        assert(vl.size()\
    \ == H and vr.size() == W);\n        Tp ret = 0;\n        for (int i = 0; i <\
    \ H; i++)\n        {\n            for (const auto &p : vals[i])\n            {\n\
    \                ret += vl[i] * p.second * vr[p.first];\n            }\n     \
    \   }\n        return ret;\n    }\n    static std::vector<Tp> prod(const sparse_matrix<Tp>\
    \ &M, const std::vector<Tp> &vec)\n    {\n        assert(M.W == int(vec.size()));\n\
    \        std::vector<Tp> ret(M.H);\n        for (int i = 0; i < M.H; i++)\n  \
    \      {\n            for (const auto &p : M.vals[i])\n            {\n       \
    \         ret[i] += p.second * vec[p.first];\n            }\n        }\n     \
    \   return ret;\n    }\n    // Determinant of sparse matrix\n    // Complexity:\
    \ O(NK + N^2) (K: # of non-zero elements in M)\n    // Reference: <https://yukicoder.me/wiki/black_box_linear_algebra>\n\
    \    Tp Determinant() const\n    {\n        assert(H == W);\n        const int\
    \ N = H, hi = Tp::get_mod();\n        std::vector<Tp> b(N), u(N), D(N);\n    \
    \    for (int i = 0; i < N; i++)\n        {\n            b[i] = rnd(1, hi), u[i]\
    \ = rnd(1, hi), D[i] = rnd(1, hi);\n        }\n        std::vector<Tp> uMDib(2\
    \ * N);\n        for (int i = 0; i < 2 * N; i++)\n        {\n            uMDib[i]\
    \ = std::inner_product(u.begin(), u.end(), b.begin(), Tp(0));\n            for\
    \ (int j = 0; j < N; j++)\n            {\n                b[j] *= D[j];\n    \
    \        }\n            b = prod(*this, b);\n        }\n        auto ret = linear_recurrence<Tp>(uMDib);\n\
    \        Tp det = ret.second.back() * (N % 2 ? -1 : 1);\n        Tp ddet = 1;\n\
    \        for (auto d : D) ddet *= d;\n        return det / ddet;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\n#include \"random/rand_nondeterministic.hpp\"\n#include \"\
    linear_algebra_matrix/linear_recurrence.hpp\"\n\n// CUT begin\n// Sparse matrix\
    \ on ModInt/ModIntRuntime\ntemplate <typename Tp>\nstruct sparse_matrix\n{\n \
    \   int H, W;\n    std::vector<std::vector<std::pair<int, Tp>>> vals;\n    sparse_matrix(int\
    \ H = 0, int W = 0) : H(H), W(W), vals(H) {}\n    void add_element(int i, int\
    \ j, Tp val)\n    {\n        assert(i >= 0 and i < H);\n        assert(j >= 0\
    \ and i < W);\n        vals[i].emplace_back(j, val);\n    }\n    Tp eval_bilinear(const\
    \ std::vector<Tp> &vl, const std::vector<Tp> &vr) const\n    {\n        assert(vl.size()\
    \ == H and vr.size() == W);\n        Tp ret = 0;\n        for (int i = 0; i <\
    \ H; i++)\n        {\n            for (const auto &p : vals[i])\n            {\n\
    \                ret += vl[i] * p.second * vr[p.first];\n            }\n     \
    \   }\n        return ret;\n    }\n    static std::vector<Tp> prod(const sparse_matrix<Tp>\
    \ &M, const std::vector<Tp> &vec)\n    {\n        assert(M.W == int(vec.size()));\n\
    \        std::vector<Tp> ret(M.H);\n        for (int i = 0; i < M.H; i++)\n  \
    \      {\n            for (const auto &p : M.vals[i])\n            {\n       \
    \         ret[i] += p.second * vec[p.first];\n            }\n        }\n     \
    \   return ret;\n    }\n    // Determinant of sparse matrix\n    // Complexity:\
    \ O(NK + N^2) (K: # of non-zero elements in M)\n    // Reference: <https://yukicoder.me/wiki/black_box_linear_algebra>\n\
    \    Tp Determinant() const\n    {\n        assert(H == W);\n        const int\
    \ N = H, hi = Tp::get_mod();\n        std::vector<Tp> b(N), u(N), D(N);\n    \
    \    for (int i = 0; i < N; i++)\n        {\n            b[i] = rnd(1, hi), u[i]\
    \ = rnd(1, hi), D[i] = rnd(1, hi);\n        }\n        std::vector<Tp> uMDib(2\
    \ * N);\n        for (int i = 0; i < 2 * N; i++)\n        {\n            uMDib[i]\
    \ = std::inner_product(u.begin(), u.end(), b.begin(), Tp(0));\n            for\
    \ (int j = 0; j < N; j++)\n            {\n                b[j] *= D[j];\n    \
    \        }\n            b = prod(*this, b);\n        }\n        auto ret = linear_recurrence<Tp>(uMDib);\n\
    \        Tp det = ret.second.back() * (N % 2 ? -1 : 1);\n        Tp ddet = 1;\n\
    \        for (auto d : D) ddet *= d;\n        return det / ddet;\n    }\n};\n"
  dependsOn:
  - random/rand_nondeterministic.hpp
  - linear_algebra_matrix/linear_recurrence.hpp
  isVerificationFile: false
  path: linear_algebra_matrix/det_of_sparse_matrix.hpp
  requiredBy: []
  timestamp: '2020-06-06 02:17:41+09:00'
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
