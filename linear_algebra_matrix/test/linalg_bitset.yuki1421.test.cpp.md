---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/linalg_bitset.hpp
    title: "Linear algebra on $\\mathbb{F}_{2}$ using std::bitset ($\\mathbb{F}_{2}$\
      \ \u7DDA\u5F62\u4EE3\u6570)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1421
    links:
    - https://yukicoder.me/problems/no/1421
  bundledCode: "#line 1 \"linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1421\"\n#line 2 \"linear_algebra_matrix/linalg_bitset.hpp\"\
    \n#include <bitset>\n#include <cassert>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n// Gauss-Jordan elimination of n * m matrix M\n// Complexity:\
    \ O(nm + nm rank(M) / 64)\n// Verified: abc276_h (2000 x 8000)\ntemplate <int\
    \ Wmax>\nstd::vector<std::bitset<Wmax>> gauss_jordan(int W, std::vector<std::bitset<Wmax>>\
    \ M) {\n    assert(W <= Wmax);\n    int H = M.size(), c = 0;\n    for (int h =\
    \ 0; h < H and c < W; ++h, ++c) {\n        int piv = -1;\n        for (int j =\
    \ h; j < H; ++j) {\n            if (M[j][c]) {\n                piv = j;\n   \
    \             break;\n            }\n        }\n        if (piv == -1) {\n   \
    \         --h;\n            continue;\n        }\n        std::swap(M[piv], M[h]);\n\
    \        for (int hh = 0; hh < H; ++hh) {\n            if (hh != h and M[hh][c])\
    \ M[hh] ^= M[h];\n        }\n    }\n    return M;\n}\n\n// Rank of Gauss-Jordan\
    \ eliminated matrix\ntemplate <int Wmax> int rank_gauss_jordan(int W, const std::vector<std::bitset<Wmax>>\
    \ &M) {\n    assert(W <= Wmax);\n    for (int h = (int)M.size() - 1; h >= 0; h--)\
    \ {\n        int j = 0;\n        while (j < W and !M[h][j]) ++j;\n        if (j\
    \ < W) return h + 1;\n    }\n    return 0;\n}\n\ntemplate <int W1, int W2>\nstd::vector<std::bitset<W2>>\n\
    matmul(const std::vector<std::bitset<W1>> &A, const std::vector<std::bitset<W2>>\
    \ &B) {\n    int H = A.size(), K = B.size();\n    std::vector<std::bitset<W2>>\
    \ C(H);\n    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < K; j++)\
    \ {\n            if (A[i][j]) C[i] ^= B[j];\n        }\n    }\n    return C;\n\
    }\n\ntemplate <int Wmax>\nstd::vector<std::bitset<Wmax>> matpower(std::vector<std::bitset<Wmax>>\
    \ X, long long n) {\n    int D = X.size();\n    std::vector<std::bitset<Wmax>>\
    \ ret(D);\n    for (int i = 0; i < D; i++) ret[i][i] = 1;\n    while (n) {\n \
    \       if (n & 1) ret = matmul<Wmax, Wmax>(ret, X);\n        X = matmul<Wmax,\
    \ Wmax>(X, X), n >>= 1;\n    }\n    return ret;\n}\n\n// Solve Ax = b on F_2\n\
    // - retval: {true, one of the solutions, {freedoms}} (if solution exists)\n//\
    \           {false, {}, {}} (otherwise)\n// Complexity: O(HW + HW rank(A) / 64\
    \ + W^2 len(freedoms))\ntemplate <int Wmax, class Vec>\nstd::tuple<bool, std::bitset<Wmax>,\
    \ std::vector<std::bitset<Wmax>>>\nsystem_of_linear_equations(std::vector<std::bitset<Wmax>>\
    \ A, Vec b, int W) {\n    int H = A.size();\n    assert(W <= Wmax);\n    assert(A.size()\
    \ == b.size());\n\n    std::vector<std::bitset<Wmax + 1>> M(H);\n    for (int\
    \ i = 0; i < H; ++i) {\n        for (int j = 0; j < W; ++j) M[i][j] = A[i][j];\n\
    \        M[i][W] = b[i];\n    }\n    M = gauss_jordan<Wmax + 1>(W + 1, M);\n \
    \   std::vector<int> ss(W, -1);\n    std::vector<int> ss_nonneg_js;\n    for (int\
    \ i = 0; i < H; i++) {\n        int j = 0;\n        while (j <= W and !M[i][j])\
    \ ++j;\n        if (j == W) return {false, 0, {}};\n        if (j < W) {\n   \
    \         ss_nonneg_js.push_back(j);\n            ss[j] = i;\n        }\n    }\n\
    \    std::bitset<Wmax> x;\n    std::vector<std::bitset<Wmax>> D;\n    for (int\
    \ j = 0; j < W; ++j) {\n        if (ss[j] == -1) {\n            // This part may\
    \ require W^2 space complexity in output\n            std::bitset<Wmax> d;\n \
    \           d[j] = 1;\n            for (int jj : ss_nonneg_js) d[jj] = M[ss[jj]][j];\n\
    \            D.emplace_back(d);\n        } else {\n            x[j] = M[ss[j]][W];\n\
    \        }\n    }\n    return std::make_tuple(true, x, D);\n}\n#line 3 \"linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp\"\
    \n#include <iostream>\n#line 6 \"linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp\"\
    \nusing namespace std;\n\ntemplate <typename T> bool chmin(T &m, const T q) {\n\
    \    if (m > q) {\n        m = q;\n        return true;\n    } else\n        return\
    \ false;\n}\n\nvoid bad() {\n    puts(\"-1\");\n    exit(0);\n}\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N, M;\n   \
    \ cin >> N >> M;\n\n    using ull = unsigned long long;\n    vector<pair<ull,\
    \ int>> basis;\n    while (M--) {\n        int a;\n        cin >> a;\n       \
    \ ull mask = 0;\n        while (a--) {\n            int b;\n            cin >>\
    \ b;\n            b--;\n            mask += 1ULL << b;\n        }\n        int\
    \ y;\n        cin >> y;\n        for (auto [v, w] : basis) {\n            if (chmin(mask,\
    \ mask ^ v)) y ^= w;\n        }\n        if (!mask and y) bad();\n        if (mask)\
    \ basis.emplace_back(mask, y);\n    }\n    vector<int> ret(N);\n\n    for (int\
    \ d = 0; d < 30; ++d) {\n        constexpr int Wmax = 320;\n        vector<bitset<Wmax>>\
    \ A;\n        vector<bool> b;\n        for (int i = 0; i < int(basis.size());\
    \ ++i) {\n            b.push_back((basis[i].second >> d) & 1);\n            bitset<Wmax>\
    \ a;\n            a.reset();\n            for (int j = 0; j < N; ++j) {\n    \
    \            if ((basis[i].first >> j) & 1) a[j] = 1;\n            }\n       \
    \     A.emplace_back(a);\n        }\n        auto [ok, solution, freedoms] = system_of_linear_equations<Wmax,\
    \ vector<bool>>(A, b, N);\n        if (!ok) bad();\n        for (int i = 0; i\
    \ < N; ++i) ret[i] += int(solution[i]) << d;\n    }\n    for (auto x : ret) cout\
    \ << x << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1421\"\n#include \"../linalg_bitset.hpp\"\
    \n#include <iostream>\n#include <utility>\n#include <vector>\nusing namespace\
    \ std;\n\ntemplate <typename T> bool chmin(T &m, const T q) {\n    if (m > q)\
    \ {\n        m = q;\n        return true;\n    } else\n        return false;\n\
    }\n\nvoid bad() {\n    puts(\"-1\");\n    exit(0);\n}\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int N, M;\n    cin >> N >> M;\n\n    using\
    \ ull = unsigned long long;\n    vector<pair<ull, int>> basis;\n    while (M--)\
    \ {\n        int a;\n        cin >> a;\n        ull mask = 0;\n        while (a--)\
    \ {\n            int b;\n            cin >> b;\n            b--;\n           \
    \ mask += 1ULL << b;\n        }\n        int y;\n        cin >> y;\n        for\
    \ (auto [v, w] : basis) {\n            if (chmin(mask, mask ^ v)) y ^= w;\n  \
    \      }\n        if (!mask and y) bad();\n        if (mask) basis.emplace_back(mask,\
    \ y);\n    }\n    vector<int> ret(N);\n\n    for (int d = 0; d < 30; ++d) {\n\
    \        constexpr int Wmax = 320;\n        vector<bitset<Wmax>> A;\n        vector<bool>\
    \ b;\n        for (int i = 0; i < int(basis.size()); ++i) {\n            b.push_back((basis[i].second\
    \ >> d) & 1);\n            bitset<Wmax> a;\n            a.reset();\n         \
    \   for (int j = 0; j < N; ++j) {\n                if ((basis[i].first >> j) &\
    \ 1) a[j] = 1;\n            }\n            A.emplace_back(a);\n        }\n   \
    \     auto [ok, solution, freedoms] = system_of_linear_equations<Wmax, vector<bool>>(A,\
    \ b, N);\n        if (!ok) bad();\n        for (int i = 0; i < N; ++i) ret[i]\
    \ += int(solution[i]) << d;\n    }\n    for (auto x : ret) cout << x << '\\n';\n\
    }\n"
  dependsOn:
  - linear_algebra_matrix/linalg_bitset.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp
  requiredBy: []
  timestamp: '2022-11-06 22:51:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp
- /verify/linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp.html
title: linear_algebra_matrix/test/linalg_bitset.yuki1421.test.cpp
---
