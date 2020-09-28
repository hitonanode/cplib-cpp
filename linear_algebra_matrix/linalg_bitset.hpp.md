---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_bitset.test.cpp
    title: linear_algebra_matrix/test/linalg_bitset.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"linear_algebra_matrix/linalg_bitset.hpp\"\n#include <bitset>\n\
    #include <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\nconstexpr int Wmax = 320;\nstd::vector<std::bitset<Wmax>> gauss_jordan(int\
    \ W, std::vector<std::bitset<Wmax>> mtr)\n{\n    int H = mtr.size(), c = 0;\n\
    \    for (int h = 0; h < H; h++, c++)\n    {\n        if (c == W) break;\n   \
    \     int piv = -1;\n        for (int j = h; j < H; j++) if (mtr[j][c]) {\n  \
    \              piv = j; break;\n        }\n        if (piv == -1) { h--; continue;\
    \ }\n        std::swap(mtr[piv], mtr[h]);\n        for (int hh = 0; hh < H; hh++)\
    \ {\n            if (hh != h and mtr[hh][c]) mtr[hh] ^= mtr[h];\n        }\n \
    \   }\n    return mtr;\n}\n\nint rank_gauss_jordan(int W, const std::vector<std::bitset<Wmax>>\
    \ &mtr) // Rank of Gauss-Jordan eliminated matrix\n{\n    for (int h = (int)mtr.size()\
    \ - 1; h >= 0; h--) {\n        if (mtr[h]._Find_first() < W) return h + 1;\n \
    \   }\n    return 0;\n}\n\nstd::vector<std::bitset<Wmax>> matmul(const std::vector<std::bitset<Wmax>>\
    \ &A, const std::vector<std::bitset<Wmax>> &B)\n{\n    int H = A.size(), K = B.size();\n\
    \    std::vector<std::bitset<Wmax>> C(H);\n    for (int i = 0; i < H; i++) {\n\
    \        for (int j = 0; j < K; j++) {\n            if (A[i][j]) C[i] ^= B[j];\n\
    \        }\n    }\n    return C;\n}\n\nstd::vector<std::bitset<Wmax>> matpower(std::vector<std::bitset<Wmax>>\
    \ X, long long n)\n{\n    int D = X.size();\n    std::vector<std::bitset<Wmax>>\
    \ ret(D);\n    for (int i = 0; i < D; i++) ret[i][i] = 1;\n    while (n)\n   \
    \ {\n        if (n & 1) ret = matmul(ret, X);\n        X = matmul(X, X), n >>=\
    \ 1;\n    }\n    return ret;\n}\n\n// Solve Ax = b on F_2\n// - retval: {true,\
    \ one of the solutions, {freedoms}} (if solution exists)\n//           {false,\
    \ {}, {}} (otherwise)\nstd::tuple<bool, std::bitset<Wmax>, std::vector<std::bitset<Wmax>>>\n\
    system_of_linear_equations(std::vector<std::bitset<Wmax>> A, std::bitset<Wmax>\
    \ b, int W)\n{\n    int H = A.size();\n    assert(W + 1 <= Wmax);\n    assert(H\
    \ <= Wmax);\n\n    std::vector<std::bitset<Wmax>> M = A;\n    for (int i = 0;\
    \ i < H; i++) M[i][W] = b[i];\n    M = gauss_jordan(W + 1, M);\n    std::vector<int>\
    \ ss(W, -1);\n    for (int i = 0; i < H; i++)\n    {\n        int j = M[i]._Find_first();\n\
    \        if (j == W)\n        {\n            return std::make_tuple(false, std::bitset<Wmax>(),\
    \ std::vector<std::bitset<Wmax>>());\n        }\n        if (j < W) ss[j] = i;\n\
    \    }\n    std::bitset<Wmax> x;\n    std::vector<std::bitset<Wmax>> D;\n    for\
    \ (int j = 0; j < W; j++)\n    {\n        if (ss[j] == -1)\n        {\n      \
    \      std::bitset<Wmax> d;\n            d[j] = 1;\n            for (int jj =\
    \ 0; jj < W; jj++) if (ss[jj] != -1) d[jj] = M[ss[jj]][j];\n            D.emplace_back(d);\n\
    \        }\n        else x[j] = M[ss[j]][W];\n    }\n    return std::make_tuple(true,\
    \ x, D);\n}\n"
  code: "#pragma once\n#include <bitset>\n#include <cassert>\n#include <tuple>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\nconstexpr int Wmax = 320;\nstd::vector<std::bitset<Wmax>>\
    \ gauss_jordan(int W, std::vector<std::bitset<Wmax>> mtr)\n{\n    int H = mtr.size(),\
    \ c = 0;\n    for (int h = 0; h < H; h++, c++)\n    {\n        if (c == W) break;\n\
    \        int piv = -1;\n        for (int j = h; j < H; j++) if (mtr[j][c]) {\n\
    \                piv = j; break;\n        }\n        if (piv == -1) { h--; continue;\
    \ }\n        std::swap(mtr[piv], mtr[h]);\n        for (int hh = 0; hh < H; hh++)\
    \ {\n            if (hh != h and mtr[hh][c]) mtr[hh] ^= mtr[h];\n        }\n \
    \   }\n    return mtr;\n}\n\nint rank_gauss_jordan(int W, const std::vector<std::bitset<Wmax>>\
    \ &mtr) // Rank of Gauss-Jordan eliminated matrix\n{\n    for (int h = (int)mtr.size()\
    \ - 1; h >= 0; h--) {\n        if (mtr[h]._Find_first() < W) return h + 1;\n \
    \   }\n    return 0;\n}\n\nstd::vector<std::bitset<Wmax>> matmul(const std::vector<std::bitset<Wmax>>\
    \ &A, const std::vector<std::bitset<Wmax>> &B)\n{\n    int H = A.size(), K = B.size();\n\
    \    std::vector<std::bitset<Wmax>> C(H);\n    for (int i = 0; i < H; i++) {\n\
    \        for (int j = 0; j < K; j++) {\n            if (A[i][j]) C[i] ^= B[j];\n\
    \        }\n    }\n    return C;\n}\n\nstd::vector<std::bitset<Wmax>> matpower(std::vector<std::bitset<Wmax>>\
    \ X, long long n)\n{\n    int D = X.size();\n    std::vector<std::bitset<Wmax>>\
    \ ret(D);\n    for (int i = 0; i < D; i++) ret[i][i] = 1;\n    while (n)\n   \
    \ {\n        if (n & 1) ret = matmul(ret, X);\n        X = matmul(X, X), n >>=\
    \ 1;\n    }\n    return ret;\n}\n\n// Solve Ax = b on F_2\n// - retval: {true,\
    \ one of the solutions, {freedoms}} (if solution exists)\n//           {false,\
    \ {}, {}} (otherwise)\nstd::tuple<bool, std::bitset<Wmax>, std::vector<std::bitset<Wmax>>>\n\
    system_of_linear_equations(std::vector<std::bitset<Wmax>> A, std::bitset<Wmax>\
    \ b, int W)\n{\n    int H = A.size();\n    assert(W + 1 <= Wmax);\n    assert(H\
    \ <= Wmax);\n\n    std::vector<std::bitset<Wmax>> M = A;\n    for (int i = 0;\
    \ i < H; i++) M[i][W] = b[i];\n    M = gauss_jordan(W + 1, M);\n    std::vector<int>\
    \ ss(W, -1);\n    for (int i = 0; i < H; i++)\n    {\n        int j = M[i]._Find_first();\n\
    \        if (j == W)\n        {\n            return std::make_tuple(false, std::bitset<Wmax>(),\
    \ std::vector<std::bitset<Wmax>>());\n        }\n        if (j < W) ss[j] = i;\n\
    \    }\n    std::bitset<Wmax> x;\n    std::vector<std::bitset<Wmax>> D;\n    for\
    \ (int j = 0; j < W; j++)\n    {\n        if (ss[j] == -1)\n        {\n      \
    \      std::bitset<Wmax> d;\n            d[j] = 1;\n            for (int jj =\
    \ 0; jj < W; jj++) if (ss[jj] != -1) d[jj] = M[ss[jj]][j];\n            D.emplace_back(d);\n\
    \        }\n        else x[j] = M[ss[j]][W];\n    }\n    return std::make_tuple(true,\
    \ x, D);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra_matrix/linalg_bitset.hpp
  requiredBy: []
  timestamp: '2020-06-06 02:17:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/linalg_bitset.test.cpp
documentation_of: linear_algebra_matrix/linalg_bitset.hpp
layout: document
redirect_from:
- /library/linear_algebra_matrix/linalg_bitset.hpp
- /library/linear_algebra_matrix/linalg_bitset.hpp.html
title: linear_algebra_matrix/linalg_bitset.hpp
---
