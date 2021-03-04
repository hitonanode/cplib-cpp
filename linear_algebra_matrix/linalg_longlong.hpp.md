---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_ll_det.test.cpp
    title: linear_algebra_matrix/test/linalg_ll_det.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_longlong.test.cpp
    title: linear_algebra_matrix/test/linalg_longlong.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_longlong_matmul.test.cpp
    title: linear_algebra_matrix/test/linalg_longlong_matmul.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"linear_algebra_matrix/linalg_longlong.hpp\"\n#include <cassert>\n\
    #include <cstdlib>\n#include <vector>\nusing namespace std;\n\n// CUT begin\n\
    using lint = long long int;\n// Solve ax+by=gcd(a, b)\nlint extgcd(lint a, lint\
    \ b, lint &x, lint &y) {\n    lint d = a;\n    if (b != 0)\n        d = extgcd(b,\
    \ a % b, y, x), y -= (a / b) * x;\n    else\n        x = 1, y = 0;\n    return\
    \ d;\n}\n// Calc a^(-1) (MOD m)\nlint mod_inverse(lint a, lint m) {\n    lint\
    \ x, y;\n    extgcd(a, m, x, y);\n    return (m + x % m) % m;\n}\nvector<vector<lint>>\
    \ gauss_jordan(vector<vector<lint>> mtr, lint mod) {\n    // Gauss-Jordan elimination\
    \ \u884C\u57FA\u672C\u5909\u5F62\u306E\u307F\u3092\u7528\u3044\u308B\u30AC\u30A6\
    \u30B9\u6D88\u53BB\u6CD5\n    int H = mtr.size(), W = mtr[0].size(), c = 0;\n\
    \    for (int h = 0; h < H; h++) {\n        if (c == W) break;\n        int piv\
    \ = -1;\n        for (int j = h; j < H; j++)\n            if (mtr[j][c]) {\n \
    \               if (piv == -1 or abs(mtr[j][c]) > abs(mtr[piv][c])) piv = j;\n\
    \            }\n        if (piv == -1) {\n            c++;\n            h--;\n\
    \            continue;\n        }\n        swap(mtr[piv], mtr[h]);\n        if\
    \ (h != piv) {\n            for (int w = 0; w < W; w++) {\n                mtr[piv][w]\
    \ = mtr[piv][w] ? mod - mtr[piv][w] : 0; // To preserve sign of determinant\n\
    \            }\n        }\n        lint pivinv = mod_inverse(mtr[h][c], mod);\n\
    \        for (int hh = 0; hh < H; hh++) {\n            if (hh == h) continue;\n\
    \            lint coeff = mtr[hh][c] * pivinv % mod;\n            for (int w =\
    \ W - 1; w >= c; w--) {\n                mtr[hh][w] = mtr[hh][w] - mtr[h][w] *\
    \ coeff % mod;\n                if (mtr[hh][w] < 0) mtr[hh][w] += mod;\n     \
    \       }\n        }\n        c++;\n    }\n    return mtr;\n}\n\nint rank_gauss_jordan(const\
    \ vector<vector<lint>> &mtr) // Rank of Gauss-Jordan eliminated matrix\n{\n  \
    \  for (int h = (int)mtr.size() - 1; h >= 0; h--) {\n        for (auto v : mtr[h])\n\
    \            if (v) return h + 1;\n    }\n    return 0;\n}\n\nlint mod_determinant(vector<vector<lint>>\
    \ mtr, lint mod) {\n    if (mtr.empty()) return 1 % mod;\n    assert(mtr.size()\
    \ == mtr[0].size());\n    lint ans = 1;\n    mtr = gauss_jordan(mtr, mod);\n \
    \   for (int i = 0; i < (int)mtr.size(); i++) ans = ans * mtr[i][i] % mod;\n \
    \   return ans;\n}\n\nvector<vector<lint>> matmul(const vector<vector<lint>> &A,\
    \ const vector<vector<lint>> &B, lint mod) {\n    int H = A.size(), W = B[0].size(),\
    \ K = B.size();\n    vector<vector<lint>> C(H, vector<lint>(W));\n    for (int\
    \ i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) {\n            for\
    \ (int k = 0; k < K; k++) { (C[i][j] += A[i][k] * B[k][j]) %= mod; }\n       \
    \ }\n    }\n    return C;\n}\n\nvector<lint> matmul(const vector<vector<lint>>\
    \ &A, const vector<lint> &v, lint mod) {\n    vector<lint> res(A.size());\n  \
    \  for (int i = 0; i < (int)A.size(); i++) {\n        for (int j = 0; j < (int)v.size();\
    \ j++) { (res[i] += A[i][j] * v[j]) %= mod; }\n    }\n    return res;\n}\nvector<vector<lint>>\
    \ matpower(vector<vector<lint>> X, lint n, lint mod) {\n    vector<vector<lint>>\
    \ res(X.size(), vector<lint>(X.size()));\n    for (int i = 0; i < (int)res.size();\
    \ i++) res[i][i] = 1;\n    while (n) {\n        if (n & 1) res = matmul(res, X,\
    \ mod);\n        X = matmul(X, X, mod);\n        n >>= 1;\n    }\n    return res;\n\
    }\n"
  code: "#pragma once\n#include <cassert>\n#include <cstdlib>\n#include <vector>\n\
    using namespace std;\n\n// CUT begin\nusing lint = long long int;\n// Solve ax+by=gcd(a,\
    \ b)\nlint extgcd(lint a, lint b, lint &x, lint &y) {\n    lint d = a;\n    if\
    \ (b != 0)\n        d = extgcd(b, a % b, y, x), y -= (a / b) * x;\n    else\n\
    \        x = 1, y = 0;\n    return d;\n}\n// Calc a^(-1) (MOD m)\nlint mod_inverse(lint\
    \ a, lint m) {\n    lint x, y;\n    extgcd(a, m, x, y);\n    return (m + x % m)\
    \ % m;\n}\nvector<vector<lint>> gauss_jordan(vector<vector<lint>> mtr, lint mod)\
    \ {\n    // Gauss-Jordan elimination \u884C\u57FA\u672C\u5909\u5F62\u306E\u307F\
    \u3092\u7528\u3044\u308B\u30AC\u30A6\u30B9\u6D88\u53BB\u6CD5\n    int H = mtr.size(),\
    \ W = mtr[0].size(), c = 0;\n    for (int h = 0; h < H; h++) {\n        if (c\
    \ == W) break;\n        int piv = -1;\n        for (int j = h; j < H; j++)\n \
    \           if (mtr[j][c]) {\n                if (piv == -1 or abs(mtr[j][c])\
    \ > abs(mtr[piv][c])) piv = j;\n            }\n        if (piv == -1) {\n    \
    \        c++;\n            h--;\n            continue;\n        }\n        swap(mtr[piv],\
    \ mtr[h]);\n        if (h != piv) {\n            for (int w = 0; w < W; w++) {\n\
    \                mtr[piv][w] = mtr[piv][w] ? mod - mtr[piv][w] : 0; // To preserve\
    \ sign of determinant\n            }\n        }\n        lint pivinv = mod_inverse(mtr[h][c],\
    \ mod);\n        for (int hh = 0; hh < H; hh++) {\n            if (hh == h) continue;\n\
    \            lint coeff = mtr[hh][c] * pivinv % mod;\n            for (int w =\
    \ W - 1; w >= c; w--) {\n                mtr[hh][w] = mtr[hh][w] - mtr[h][w] *\
    \ coeff % mod;\n                if (mtr[hh][w] < 0) mtr[hh][w] += mod;\n     \
    \       }\n        }\n        c++;\n    }\n    return mtr;\n}\n\nint rank_gauss_jordan(const\
    \ vector<vector<lint>> &mtr) // Rank of Gauss-Jordan eliminated matrix\n{\n  \
    \  for (int h = (int)mtr.size() - 1; h >= 0; h--) {\n        for (auto v : mtr[h])\n\
    \            if (v) return h + 1;\n    }\n    return 0;\n}\n\nlint mod_determinant(vector<vector<lint>>\
    \ mtr, lint mod) {\n    if (mtr.empty()) return 1 % mod;\n    assert(mtr.size()\
    \ == mtr[0].size());\n    lint ans = 1;\n    mtr = gauss_jordan(mtr, mod);\n \
    \   for (int i = 0; i < (int)mtr.size(); i++) ans = ans * mtr[i][i] % mod;\n \
    \   return ans;\n}\n\nvector<vector<lint>> matmul(const vector<vector<lint>> &A,\
    \ const vector<vector<lint>> &B, lint mod) {\n    int H = A.size(), W = B[0].size(),\
    \ K = B.size();\n    vector<vector<lint>> C(H, vector<lint>(W));\n    for (int\
    \ i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) {\n            for\
    \ (int k = 0; k < K; k++) { (C[i][j] += A[i][k] * B[k][j]) %= mod; }\n       \
    \ }\n    }\n    return C;\n}\n\nvector<lint> matmul(const vector<vector<lint>>\
    \ &A, const vector<lint> &v, lint mod) {\n    vector<lint> res(A.size());\n  \
    \  for (int i = 0; i < (int)A.size(); i++) {\n        for (int j = 0; j < (int)v.size();\
    \ j++) { (res[i] += A[i][j] * v[j]) %= mod; }\n    }\n    return res;\n}\nvector<vector<lint>>\
    \ matpower(vector<vector<lint>> X, lint n, lint mod) {\n    vector<vector<lint>>\
    \ res(X.size(), vector<lint>(X.size()));\n    for (int i = 0; i < (int)res.size();\
    \ i++) res[i][i] = 1;\n    while (n) {\n        if (n & 1) res = matmul(res, X,\
    \ mod);\n        X = matmul(X, X, mod);\n        n >>= 1;\n    }\n    return res;\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra_matrix/linalg_longlong.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:06:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/linalg_longlong.test.cpp
  - linear_algebra_matrix/test/linalg_longlong_matmul.test.cpp
  - linear_algebra_matrix/test/linalg_ll_det.test.cpp
documentation_of: linear_algebra_matrix/linalg_longlong.hpp
layout: document
redirect_from:
- /library/linear_algebra_matrix/linalg_longlong.hpp
- /library/linear_algebra_matrix/linalg_longlong.hpp.html
title: linear_algebra_matrix/linalg_longlong.hpp
---
