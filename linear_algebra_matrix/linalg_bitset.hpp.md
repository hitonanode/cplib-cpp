---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_bitset.test.cpp
    title: linear_algebra_matrix/test/linalg_bitset.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp
    title: linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_bitset_det.test.cpp
    title: linear_algebra_matrix/test/linalg_bitset_det.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_bitset_mul.test.cpp
    title: linear_algebra_matrix/test/linalg_bitset_mul.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"linear_algebra_matrix/linalg_bitset.hpp\"\n#include <bitset>\n\
    #include <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    // Gauss-Jordan elimination of n * m matrix M\n// Complexity: O(nm + nm rank(M)\
    \ / 64)\n// Verified: abc276_h (2000 x 8000)\ntemplate <int Wmax>\nstd::vector<std::bitset<Wmax>>\
    \ f2_gauss_jordan(int W, std::vector<std::bitset<Wmax>> M) {\n    assert(W <=\
    \ Wmax);\n    int H = M.size(), c = 0;\n    for (int h = 0; h < H and c < W; ++h,\
    \ ++c) {\n        int piv = -1;\n        for (int j = h; j < H; ++j) {\n     \
    \       if (M[j][c]) {\n                piv = j;\n                break;\n   \
    \         }\n        }\n        if (piv == -1) {\n            --h;\n         \
    \   continue;\n        }\n        std::swap(M[piv], M[h]);\n        for (int hh\
    \ = 0; hh < H; ++hh) {\n            if (hh != h and M[hh][c]) M[hh] ^= M[h];\n\
    \        }\n    }\n    return M;\n}\n\n// Rank of Gauss-Jordan eliminated matrix\n\
    template <int Wmax> int f2_rank_gauss_jordan(int W, const std::vector<std::bitset<Wmax>>\
    \ &M) {\n    assert(W <= Wmax);\n    for (int h = (int)M.size() - 1; h >= 0; h--)\
    \ {\n        int j = 0;\n        while (j < W and !M[h][j]) ++j;\n        if (j\
    \ < W) return h + 1;\n    }\n    return 0;\n}\n\n// determinant of F2 matrix.\n\
    // Return 0 if the matrix is singular, otherwise return 1.\n// Complexity: O(W^3\
    \ / 64)\ntemplate <int Wmax> int f2_determinant(const std::vector<std::bitset<Wmax>>\
    \ &M) {\n    const int H = M.size();\n    if (H > Wmax) return 0;\n\n    auto\
    \ tmp = M;\n    for (int h = 0; h < H; ++h) {\n        int piv = -1;\n       \
    \ for (int j = h; j < H; ++j) {\n            if (tmp.at(j).test(h)) {\n      \
    \          piv = j;\n                break;\n            }\n        }\n      \
    \  if (piv == -1) return 0; // singular\n\n        if (piv != h) std::swap(tmp.at(piv),\
    \ tmp.at(h));\n        for (int hh = h + 1; hh < H; ++hh) {\n            if (tmp.at(hh).test(h))\
    \ tmp.at(hh) ^= tmp.at(h);\n        }\n    }\n\n    return 1; // nonsingular\n\
    }\n\ntemplate <int W1, int W2>\nstd::vector<std::bitset<W2>>\nf2_matmul(const\
    \ std::vector<std::bitset<W1>> &A, const std::vector<std::bitset<W2>> &B) {\n\
    \    int H = A.size(), K = B.size();\n    std::vector<std::bitset<W2>> C(H);\n\
    \    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < K; j++) {\n  \
    \          if (A.at(i).test(j)) C.at(i) ^= B.at(j);\n        }\n    }\n    return\
    \ C;\n}\n\ntemplate <int Wmax>\nstd::vector<std::bitset<Wmax>> f2_matpower(std::vector<std::bitset<Wmax>>\
    \ X, long long n) {\n    int D = X.size();\n    std::vector<std::bitset<Wmax>>\
    \ ret(D);\n    for (int i = 0; i < D; i++) ret[i][i] = 1;\n    while (n) {\n \
    \       if (n & 1) ret = f2_matmul<Wmax, Wmax>(ret, X);\n        X = f2_matmul<Wmax,\
    \ Wmax>(X, X), n >>= 1;\n    }\n    return ret;\n}\n\n// Solve Ax = b on F_2\n\
    // - retval: {true, one of the solutions, {freedoms}} (if solution exists)\n//\
    \           {false, {}, {}} (otherwise)\n// Complexity: O(HW + HW rank(A) / 64\
    \ + W^2 len(freedoms))\ntemplate <int Wmax, class Vec>\nstd::tuple<bool, std::bitset<Wmax>,\
    \ std::vector<std::bitset<Wmax>>>\nf2_system_of_linear_equations(std::vector<std::bitset<Wmax>>\
    \ A, Vec b, int W) {\n    int H = A.size();\n    assert(W <= Wmax);\n    assert(A.size()\
    \ == b.size());\n\n    std::vector<std::bitset<Wmax + 1>> M(H);\n    for (int\
    \ i = 0; i < H; ++i) {\n        for (int j = 0; j < W; ++j) M[i][j] = A[i][j];\n\
    \        M[i][W] = b[i];\n    }\n    M = f2_gauss_jordan<Wmax + 1>(W + 1, M);\n\
    \    std::vector<int> ss(W, -1);\n    std::vector<int> ss_nonneg_js;\n    for\
    \ (int i = 0; i < H; i++) {\n        int j = 0;\n        while (j <= W and !M[i][j])\
    \ ++j;\n        if (j == W) return {false, 0, {}};\n        if (j < W) {\n   \
    \         ss_nonneg_js.push_back(j);\n            ss[j] = i;\n        }\n    }\n\
    \    std::bitset<Wmax> x;\n    std::vector<std::bitset<Wmax>> D;\n    for (int\
    \ j = 0; j < W; ++j) {\n        if (ss[j] == -1) {\n            // This part may\
    \ require W^2 space complexity in output\n            std::bitset<Wmax> d;\n \
    \           d[j] = 1;\n            for (int jj : ss_nonneg_js) d[jj] = M[ss[jj]][j];\n\
    \            D.emplace_back(d);\n        } else {\n            x[j] = M[ss[j]][W];\n\
    \        }\n    }\n    return std::make_tuple(true, x, D);\n}\n"
  code: "#pragma once\n#include <bitset>\n#include <cassert>\n#include <tuple>\n#include\
    \ <utility>\n#include <vector>\n\n// Gauss-Jordan elimination of n * m matrix\
    \ M\n// Complexity: O(nm + nm rank(M) / 64)\n// Verified: abc276_h (2000 x 8000)\n\
    template <int Wmax>\nstd::vector<std::bitset<Wmax>> f2_gauss_jordan(int W, std::vector<std::bitset<Wmax>>\
    \ M) {\n    assert(W <= Wmax);\n    int H = M.size(), c = 0;\n    for (int h =\
    \ 0; h < H and c < W; ++h, ++c) {\n        int piv = -1;\n        for (int j =\
    \ h; j < H; ++j) {\n            if (M[j][c]) {\n                piv = j;\n   \
    \             break;\n            }\n        }\n        if (piv == -1) {\n   \
    \         --h;\n            continue;\n        }\n        std::swap(M[piv], M[h]);\n\
    \        for (int hh = 0; hh < H; ++hh) {\n            if (hh != h and M[hh][c])\
    \ M[hh] ^= M[h];\n        }\n    }\n    return M;\n}\n\n// Rank of Gauss-Jordan\
    \ eliminated matrix\ntemplate <int Wmax> int f2_rank_gauss_jordan(int W, const\
    \ std::vector<std::bitset<Wmax>> &M) {\n    assert(W <= Wmax);\n    for (int h\
    \ = (int)M.size() - 1; h >= 0; h--) {\n        int j = 0;\n        while (j <\
    \ W and !M[h][j]) ++j;\n        if (j < W) return h + 1;\n    }\n    return 0;\n\
    }\n\n// determinant of F2 matrix.\n// Return 0 if the matrix is singular, otherwise\
    \ return 1.\n// Complexity: O(W^3 / 64)\ntemplate <int Wmax> int f2_determinant(const\
    \ std::vector<std::bitset<Wmax>> &M) {\n    const int H = M.size();\n    if (H\
    \ > Wmax) return 0;\n\n    auto tmp = M;\n    for (int h = 0; h < H; ++h) {\n\
    \        int piv = -1;\n        for (int j = h; j < H; ++j) {\n            if\
    \ (tmp.at(j).test(h)) {\n                piv = j;\n                break;\n  \
    \          }\n        }\n        if (piv == -1) return 0; // singular\n\n    \
    \    if (piv != h) std::swap(tmp.at(piv), tmp.at(h));\n        for (int hh = h\
    \ + 1; hh < H; ++hh) {\n            if (tmp.at(hh).test(h)) tmp.at(hh) ^= tmp.at(h);\n\
    \        }\n    }\n\n    return 1; // nonsingular\n}\n\ntemplate <int W1, int\
    \ W2>\nstd::vector<std::bitset<W2>>\nf2_matmul(const std::vector<std::bitset<W1>>\
    \ &A, const std::vector<std::bitset<W2>> &B) {\n    int H = A.size(), K = B.size();\n\
    \    std::vector<std::bitset<W2>> C(H);\n    for (int i = 0; i < H; i++) {\n \
    \       for (int j = 0; j < K; j++) {\n            if (A.at(i).test(j)) C.at(i)\
    \ ^= B.at(j);\n        }\n    }\n    return C;\n}\n\ntemplate <int Wmax>\nstd::vector<std::bitset<Wmax>>\
    \ f2_matpower(std::vector<std::bitset<Wmax>> X, long long n) {\n    int D = X.size();\n\
    \    std::vector<std::bitset<Wmax>> ret(D);\n    for (int i = 0; i < D; i++) ret[i][i]\
    \ = 1;\n    while (n) {\n        if (n & 1) ret = f2_matmul<Wmax, Wmax>(ret, X);\n\
    \        X = f2_matmul<Wmax, Wmax>(X, X), n >>= 1;\n    }\n    return ret;\n}\n\
    \n// Solve Ax = b on F_2\n// - retval: {true, one of the solutions, {freedoms}}\
    \ (if solution exists)\n//           {false, {}, {}} (otherwise)\n// Complexity:\
    \ O(HW + HW rank(A) / 64 + W^2 len(freedoms))\ntemplate <int Wmax, class Vec>\n\
    std::tuple<bool, std::bitset<Wmax>, std::vector<std::bitset<Wmax>>>\nf2_system_of_linear_equations(std::vector<std::bitset<Wmax>>\
    \ A, Vec b, int W) {\n    int H = A.size();\n    assert(W <= Wmax);\n    assert(A.size()\
    \ == b.size());\n\n    std::vector<std::bitset<Wmax + 1>> M(H);\n    for (int\
    \ i = 0; i < H; ++i) {\n        for (int j = 0; j < W; ++j) M[i][j] = A[i][j];\n\
    \        M[i][W] = b[i];\n    }\n    M = f2_gauss_jordan<Wmax + 1>(W + 1, M);\n\
    \    std::vector<int> ss(W, -1);\n    std::vector<int> ss_nonneg_js;\n    for\
    \ (int i = 0; i < H; i++) {\n        int j = 0;\n        while (j <= W and !M[i][j])\
    \ ++j;\n        if (j == W) return {false, 0, {}};\n        if (j < W) {\n   \
    \         ss_nonneg_js.push_back(j);\n            ss[j] = i;\n        }\n    }\n\
    \    std::bitset<Wmax> x;\n    std::vector<std::bitset<Wmax>> D;\n    for (int\
    \ j = 0; j < W; ++j) {\n        if (ss[j] == -1) {\n            // This part may\
    \ require W^2 space complexity in output\n            std::bitset<Wmax> d;\n \
    \           d[j] = 1;\n            for (int jj : ss_nonneg_js) d[jj] = M[ss[jj]][j];\n\
    \            D.emplace_back(d);\n        } else {\n            x[j] = M[ss[j]][W];\n\
    \        }\n    }\n    return std::make_tuple(true, x, D);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra_matrix/linalg_bitset.hpp
  requiredBy: []
  timestamp: '2024-05-03 14:40:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/linalg_bitset_mul.test.cpp
  - linear_algebra_matrix/test/linalg_bitset.test.cpp
  - linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp
  - linear_algebra_matrix/test/linalg_bitset_det.test.cpp
documentation_of: linear_algebra_matrix/linalg_bitset.hpp
layout: document
title: "Linear algebra on $\\mathbb{F}_{2}$ using std::bitset (std::bitset \u3092\u4F7F\
  \u7528\u3057\u305F $\\mathbb{F}_{2}$ \u7DDA\u5F62\u4EE3\u6570)"
---

`std::bitset<>` を使用した $\mathbb{F}_{2}$ 用線形代数演算．64 倍程度の定数倍高速化が見込まれる．

## 使用方法

### 線形方程式系

```cpp
int W;
vector<bitset<Wmax>> A;
vector<bool> b;

// Solve Ax = b (x: F_2^W)
auto [feasible, x0, freedoms] = f2_system_of_linear_equations<Wmax, vector<bool>>(A, b, W);

// Calc determinant (or check whether A is regular)
int det = f2_determinant<dim>(mat);
```

## 問題例

- [AOJ 2624: Graph Automata Player](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624)
- [No.1421 国勢調査 (Hard) - yukicoder](https://yukicoder.me/problems/no/1421)
- [AtCoder Beginner Contest 276 Ex - Construct a Matrix](https://atcoder.jp/contests/abc276/tasks/abc276_h) $2000 \times 8000$ 行列の線型方程式を解く．
- [Library Checker: Determinant of Matrix (Mod 2)](https://judge.yosupo.jp/problem/matrix_det_mod_2)
