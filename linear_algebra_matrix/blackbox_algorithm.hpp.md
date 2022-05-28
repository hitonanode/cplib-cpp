---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/linear_recurrence.hpp
    title: "\u7DDA\u5F62\u6F38\u5316\u5F0F\u306E\u767A\u898B\u30FB\u7B2C $N$ \u9805\
      \u63A8\u5B9A"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp
    title: linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/det_of_blackbox_matrix.test.cpp
    title: linear_algebra_matrix/test/det_of_blackbox_matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"formal_power_series/linear_recurrence.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n\n// CUT begin\n//\
    \ Berlekamp\u2013Massey algorithm\n// https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm\n\
    // Complexity: O(N^2)\n// input: S = sequence from field K\n// return: L     \
    \     = degree of minimal polynomial,\n//         C_reversed = monic min. polynomial\
    \ (size = L + 1, reversed order, C_reversed[0] = 1))\n// Formula: convolve(S,\
    \ C_reversed)[i] = 0 for i >= L\n// Example:\n// - [1, 2, 4, 8, 16]   -> (1, [1,\
    \ -2])\n// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])\n// - [0, 0, 0, 0, 1]    ->\
    \ (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)\n// - []                 ->\
    \ (0, [1])\n// - [0, 0, 0]          -> (0, [1])\n// - [-2]               -> (1,\
    \ [1, 2])\ntemplate <typename Tfield>\nstd::pair<int, std::vector<Tfield>> find_linear_recurrence(const\
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
    \ <typename Tfield>\nTfield guess_kth_term(const std::vector<Tfield> &initial_elements,\
    \ long long k) {\n    assert(k >= 0);\n    if (k < static_cast<long long>(initial_elements.size()))\
    \ return initial_elements[k];\n    const auto f = find_linear_recurrence<Tfield>(initial_elements).second;\n\
    \    const auto g = monomial_mod_polynomial<Tfield>(k, f);\n    Tfield ret = 0;\n\
    \    for (unsigned i = 0; i < g.size(); i++) ret += g[i] * initial_elements[i];\n\
    \    return ret;\n}\n#line 3 \"linear_algebra_matrix/blackbox_algorithm.hpp\"\n\
    #include <chrono>\n#include <random>\n#line 6 \"linear_algebra_matrix/blackbox_algorithm.hpp\"\
    \n\ntemplate <typename ModInt> std::vector<ModInt> gen_random_vector(int len)\
    \ {\n    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    static std::uniform_int_distribution<int> rnd(1, ModInt::mod() - 1);\n  \
    \  std::vector<ModInt> ret(len);\n    for (auto &x : ret) x = rnd(mt);\n    return\
    \ ret;\n};\n\n// Probabilistic algorithm to find a solution of linear equation\
    \ Ax = b if exists.\n// Complexity: O(n T(n) + n^2)\n// Reference:\n// [1] W.\
    \ Eberly, E. Kaltofen, \"On randomized Lanczos algorithms,\" Proc. of international\
    \ symposium on\n//     Symbolic and algebraic computation, 176-183, 1997.\ntemplate\
    \ <typename Matrix, typename T>\nstd::vector<T> linear_system_solver_lanczos(const\
    \ Matrix &A, const std::vector<T> &b) {\n    assert(A.height() == int(b.size()));\n\
    \    const int M = A.height(), N = A.width();\n\n    const std::vector<T> D1 =\
    \ gen_random_vector<T>(N), D2 = gen_random_vector<T>(M),\n                   \
    \      v = gen_random_vector<T>(N);\n    auto applyD1 = [&D1](std::vector<T> v)\
    \ {\n        for (int i = 0; i < int(v.size()); i++) v[i] *= D1[i];\n        return\
    \ v;\n    };\n    auto applyD2 = [&D2](std::vector<T> v) {\n        for (int i\
    \ = 0; i < int(v.size()); i++) v[i] *= D2[i];\n        return v;\n    };\n   \
    \ auto applyAtilde = [&](std::vector<T> v) -> std::vector<T> {\n        v = applyD1(v);\n\
    \        v = A.prod(v);\n        v = applyD2(v);\n        v = A.prod_left(v);\n\
    \        v = applyD1(v);\n        return v;\n    };\n    auto dot = [&](const\
    \ std::vector<T> &vl, const std::vector<T> &vr) -> T {\n        return std::inner_product(vl.begin(),\
    \ vl.end(), vr.begin(), T(0));\n    };\n    auto scalar_vec = [&](const T &x,\
    \ std::vector<T> vec) -> std::vector<T> {\n        for (auto &v : vec) v *= x;\n\
    \        return vec;\n    };\n\n    auto btilde1 = applyD1(A.prod_left(applyD2(b))),\
    \ btilde2 = applyAtilde(v);\n    std::vector<T> btilde(N);\n    for (int i = 0;\
    \ i < N; i++) btilde[i] = btilde1[i] + btilde2[i];\n\n    std::vector<T> w0 =\
    \ btilde, v1 = applyAtilde(w0);\n    std::vector<T> wm1(w0.size()), v0(v1.size());\n\
    \    T t0 = dot(v1, w0), gamma = dot(btilde, w0) / t0, tm1 = 1;\n    std::vector<T>\
    \ x = scalar_vec(gamma, w0);\n    while (true) {\n        if (!t0 or !std::count_if(w0.begin(),\
    \ w0.end(), [](T x) { return x != T(0); })) break;\n        T alpha = dot(v1,\
    \ v1) / t0, beta = dot(v1, v0) / tm1;\n        std::vector<T> w1(N);\n       \
    \ for (int i = 0; i < N; i++) w1[i] = v1[i] - alpha * w0[i] - beta * wm1[i];\n\
    \        std::vector<T> v2 = applyAtilde(w1);\n        T t1 = dot(w1, v2);\n \
    \       gamma = dot(btilde, w1) / t1;\n        for (int i = 0; i < N; i++) x[i]\
    \ += gamma * w1[i];\n\n        wm1 = w0, w0 = w1;\n        v0 = v1, v1 = v2;\n\
    \        tm1 = t0, t0 = t1;\n    }\n    for (int i = 0; i < N; i++) x[i] -= v[i];\n\
    \    return applyD1(x);\n}\n\n// Probabilistic algorithm to calculate determinant\
    \ of matrices\n// Complexity: O(n T(n) + n^2)\n// Reference:\n// [1] D. H. Wiedmann,\
    \ \"Solving sparse linear equations over finite fields,\"\n//     IEEE Trans.\
    \ on Information Theory, 32(1), 54-62, 1986.\ntemplate <class Matrix, class Tp>\
    \ Tp blackbox_determinant(const Matrix &M) {\n    assert(M.height() == M.width());\n\
    \    const int N = M.height();\n    std::vector<Tp> b = gen_random_vector<Tp>(N),\
    \ u = gen_random_vector<Tp>(N),\n                    D = gen_random_vector<Tp>(N);\n\
    \    std::vector<Tp> uMDib(2 * N);\n    for (int i = 0; i < 2 * N; i++) {\n  \
    \      uMDib[i] = std::inner_product(u.begin(), u.end(), b.begin(), Tp(0));\n\
    \        for (int j = 0; j < N; j++) b[j] *= D[j];\n        b = M.prod(b);\n \
    \   }\n    auto ret = find_linear_recurrence<Tp>(uMDib);\n    Tp det = ret.second.back()\
    \ * (N % 2 ? -1 : 1);\n    Tp ddet = 1;\n    for (auto d : D) ddet *= d;\n   \
    \ return det / ddet;\n}\n"
  code: "#pragma once\n#include \"../formal_power_series/linear_recurrence.hpp\"\n\
    #include <chrono>\n#include <random>\n#include <vector>\n\ntemplate <typename\
    \ ModInt> std::vector<ModInt> gen_random_vector(int len) {\n    static std::mt19937\
    \ mt(std::chrono::steady_clock::now().time_since_epoch().count());\n    static\
    \ std::uniform_int_distribution<int> rnd(1, ModInt::mod() - 1);\n    std::vector<ModInt>\
    \ ret(len);\n    for (auto &x : ret) x = rnd(mt);\n    return ret;\n};\n\n// Probabilistic\
    \ algorithm to find a solution of linear equation Ax = b if exists.\n// Complexity:\
    \ O(n T(n) + n^2)\n// Reference:\n// [1] W. Eberly, E. Kaltofen, \"On randomized\
    \ Lanczos algorithms,\" Proc. of international symposium on\n//     Symbolic and\
    \ algebraic computation, 176-183, 1997.\ntemplate <typename Matrix, typename T>\n\
    std::vector<T> linear_system_solver_lanczos(const Matrix &A, const std::vector<T>\
    \ &b) {\n    assert(A.height() == int(b.size()));\n    const int M = A.height(),\
    \ N = A.width();\n\n    const std::vector<T> D1 = gen_random_vector<T>(N), D2\
    \ = gen_random_vector<T>(M),\n                         v = gen_random_vector<T>(N);\n\
    \    auto applyD1 = [&D1](std::vector<T> v) {\n        for (int i = 0; i < int(v.size());\
    \ i++) v[i] *= D1[i];\n        return v;\n    };\n    auto applyD2 = [&D2](std::vector<T>\
    \ v) {\n        for (int i = 0; i < int(v.size()); i++) v[i] *= D2[i];\n     \
    \   return v;\n    };\n    auto applyAtilde = [&](std::vector<T> v) -> std::vector<T>\
    \ {\n        v = applyD1(v);\n        v = A.prod(v);\n        v = applyD2(v);\n\
    \        v = A.prod_left(v);\n        v = applyD1(v);\n        return v;\n   \
    \ };\n    auto dot = [&](const std::vector<T> &vl, const std::vector<T> &vr) ->\
    \ T {\n        return std::inner_product(vl.begin(), vl.end(), vr.begin(), T(0));\n\
    \    };\n    auto scalar_vec = [&](const T &x, std::vector<T> vec) -> std::vector<T>\
    \ {\n        for (auto &v : vec) v *= x;\n        return vec;\n    };\n\n    auto\
    \ btilde1 = applyD1(A.prod_left(applyD2(b))), btilde2 = applyAtilde(v);\n    std::vector<T>\
    \ btilde(N);\n    for (int i = 0; i < N; i++) btilde[i] = btilde1[i] + btilde2[i];\n\
    \n    std::vector<T> w0 = btilde, v1 = applyAtilde(w0);\n    std::vector<T> wm1(w0.size()),\
    \ v0(v1.size());\n    T t0 = dot(v1, w0), gamma = dot(btilde, w0) / t0, tm1 =\
    \ 1;\n    std::vector<T> x = scalar_vec(gamma, w0);\n    while (true) {\n    \
    \    if (!t0 or !std::count_if(w0.begin(), w0.end(), [](T x) { return x != T(0);\
    \ })) break;\n        T alpha = dot(v1, v1) / t0, beta = dot(v1, v0) / tm1;\n\
    \        std::vector<T> w1(N);\n        for (int i = 0; i < N; i++) w1[i] = v1[i]\
    \ - alpha * w0[i] - beta * wm1[i];\n        std::vector<T> v2 = applyAtilde(w1);\n\
    \        T t1 = dot(w1, v2);\n        gamma = dot(btilde, w1) / t1;\n        for\
    \ (int i = 0; i < N; i++) x[i] += gamma * w1[i];\n\n        wm1 = w0, w0 = w1;\n\
    \        v0 = v1, v1 = v2;\n        tm1 = t0, t0 = t1;\n    }\n    for (int i\
    \ = 0; i < N; i++) x[i] -= v[i];\n    return applyD1(x);\n}\n\n// Probabilistic\
    \ algorithm to calculate determinant of matrices\n// Complexity: O(n T(n) + n^2)\n\
    // Reference:\n// [1] D. H. Wiedmann, \"Solving sparse linear equations over finite\
    \ fields,\"\n//     IEEE Trans. on Information Theory, 32(1), 54-62, 1986.\ntemplate\
    \ <class Matrix, class Tp> Tp blackbox_determinant(const Matrix &M) {\n    assert(M.height()\
    \ == M.width());\n    const int N = M.height();\n    std::vector<Tp> b = gen_random_vector<Tp>(N),\
    \ u = gen_random_vector<Tp>(N),\n                    D = gen_random_vector<Tp>(N);\n\
    \    std::vector<Tp> uMDib(2 * N);\n    for (int i = 0; i < 2 * N; i++) {\n  \
    \      uMDib[i] = std::inner_product(u.begin(), u.end(), b.begin(), Tp(0));\n\
    \        for (int j = 0; j < N; j++) b[j] *= D[j];\n        b = M.prod(b);\n \
    \   }\n    auto ret = find_linear_recurrence<Tp>(uMDib);\n    Tp det = ret.second.back()\
    \ * (N % 2 ? -1 : 1);\n    Tp ddet = 1;\n    for (auto d : D) ddet *= d;\n   \
    \ return det / ddet;\n}\n"
  dependsOn:
  - formal_power_series/linear_recurrence.hpp
  isVerificationFile: false
  path: linear_algebra_matrix/blackbox_algorithm.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/det_of_blackbox_matrix.test.cpp
  - linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp
documentation_of: linear_algebra_matrix/blackbox_algorithm.hpp
layout: document
redirect_from:
- /library/linear_algebra_matrix/blackbox_algorithm.hpp
- /library/linear_algebra_matrix/blackbox_algorithm.hpp.html
title: linear_algebra_matrix/blackbox_algorithm.hpp
---
