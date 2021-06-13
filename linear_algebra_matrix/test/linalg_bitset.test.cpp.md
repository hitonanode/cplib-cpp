---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/linalg_bitset.hpp
    title: linear_algebra_matrix/linalg_bitset.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624
  bundledCode: "#line 2 \"linear_algebra_matrix/linalg_bitset.hpp\"\n#include <bitset>\n\
    #include <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\nconstexpr int Wmax = 320;\nstd::vector<std::bitset<Wmax>> gauss_jordan(int\
    \ W, std::vector<std::bitset<Wmax>> mtr) {\n    int H = mtr.size(), c = 0;\n \
    \   for (int h = 0; h < H; h++, c++) {\n        if (c == W) break;\n        int\
    \ piv = -1;\n        for (int j = h; j < H; j++)\n            if (mtr[j][c]) {\n\
    \                piv = j;\n                break;\n            }\n        if (piv\
    \ == -1) {\n            h--;\n            continue;\n        }\n        std::swap(mtr[piv],\
    \ mtr[h]);\n        for (int hh = 0; hh < H; hh++) {\n            if (hh != h\
    \ and mtr[hh][c]) mtr[hh] ^= mtr[h];\n        }\n    }\n    return mtr;\n}\n\n\
    int rank_gauss_jordan(int W, const std::vector<std::bitset<Wmax>> &mtr) // Rank\
    \ of Gauss-Jordan eliminated matrix\n{\n    for (int h = (int)mtr.size() - 1;\
    \ h >= 0; h--) {\n        if (mtr[h]._Find_first() < W) return h + 1;\n    }\n\
    \    return 0;\n}\n\nstd::vector<std::bitset<Wmax>> matmul(const std::vector<std::bitset<Wmax>>\
    \ &A, const std::vector<std::bitset<Wmax>> &B) {\n    int H = A.size(), K = B.size();\n\
    \    std::vector<std::bitset<Wmax>> C(H);\n    for (int i = 0; i < H; i++) {\n\
    \        for (int j = 0; j < K; j++) {\n            if (A[i][j]) C[i] ^= B[j];\n\
    \        }\n    }\n    return C;\n}\n\nstd::vector<std::bitset<Wmax>> matpower(std::vector<std::bitset<Wmax>>\
    \ X, long long n) {\n    int D = X.size();\n    std::vector<std::bitset<Wmax>>\
    \ ret(D);\n    for (int i = 0; i < D; i++) ret[i][i] = 1;\n    while (n) {\n \
    \       if (n & 1) ret = matmul(ret, X);\n        X = matmul(X, X), n >>= 1;\n\
    \    }\n    return ret;\n}\n\n// Solve Ax = b on F_2\n// - retval: {true, one\
    \ of the solutions, {freedoms}} (if solution exists)\n//           {false, {},\
    \ {}} (otherwise)\nstd::tuple<bool, std::bitset<Wmax>, std::vector<std::bitset<Wmax>>>\
    \ system_of_linear_equations(std::vector<std::bitset<Wmax>> A, std::bitset<Wmax>\
    \ b, int W) {\n    int H = A.size();\n    assert(W + 1 <= Wmax);\n    assert(H\
    \ <= Wmax);\n\n    std::vector<std::bitset<Wmax>> M = A;\n    for (int i = 0;\
    \ i < H; i++) M[i][W] = b[i];\n    M = gauss_jordan(W + 1, M);\n    std::vector<int>\
    \ ss(W, -1);\n    for (int i = 0; i < H; i++) {\n        int j = M[i]._Find_first();\n\
    \        if (j == W) { return std::make_tuple(false, std::bitset<Wmax>(), std::vector<std::bitset<Wmax>>());\
    \ }\n        if (j < W) ss[j] = i;\n    }\n    std::bitset<Wmax> x;\n    std::vector<std::bitset<Wmax>>\
    \ D;\n    for (int j = 0; j < W; j++) {\n        if (ss[j] == -1) {\n        \
    \    std::bitset<Wmax> d;\n            d[j] = 1;\n            for (int jj = 0;\
    \ jj < W; jj++)\n                if (ss[jj] != -1) d[jj] = M[ss[jj]][j];\n   \
    \         D.emplace_back(d);\n        } else\n            x[j] = M[ss[j]][W];\n\
    \    }\n    return std::make_tuple(true, x, D);\n}\n#line 2 \"linear_algebra_matrix/test/linalg_bitset.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624\"\
    \n#include <iostream>\n#include <numeric>\nusing namespace std;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N, T;\n   \
    \ cin >> N;\n    vector<bitset<Wmax>> A(N);\n    for (int i = 0; i < N; i++) {\n\
    \        for (int j = 0; j < N; j++) {\n            int t;\n            cin >>\
    \ t;\n            A[i][j] = t;\n        }\n    }\n    bitset<Wmax> v(N);\n   \
    \ for (int i = 0; i < N; i++) {\n        int t;\n        cin >> t;\n        v[i]\
    \ = t;\n    }\n\n    cin >> T;\n    A = matpower(A, T);\n    for (int i = 0; i\
    \ < N; i++) A[i][N] = v[i];\n    A = gauss_jordan(N + 1, A);\n\n    for (int i\
    \ = 0; i < N; i++) {\n        if (A[i].count() == 1 and A[i][N]) {\n         \
    \   cout << \"none\\n\";\n            return 0;\n        }\n    }\n    if (!A[N\
    \ - 1][N - 1]) {\n        cout << \"ambiguous\\n\";\n        return 0;\n    }\n\
    \    bitset<Wmax> ret;\n    for (int i = N - 1; i >= 0; i--) {\n        int a\
    \ = 0;\n        for (int j = i + 1; j < N; j++) a ^= ret[j] * A[i][j];\n     \
    \   ret[i] = (a != A[i][N]);\n    }\n    for (int i = 0; i < N; i++) cout << ret[i]\
    \ << (i == N - 1 ? '\\n' : ' ');\n}\n"
  code: "#include \"../linalg_bitset.hpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2624\"\
    \n#include <iostream>\n#include <numeric>\nusing namespace std;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N, T;\n   \
    \ cin >> N;\n    vector<bitset<Wmax>> A(N);\n    for (int i = 0; i < N; i++) {\n\
    \        for (int j = 0; j < N; j++) {\n            int t;\n            cin >>\
    \ t;\n            A[i][j] = t;\n        }\n    }\n    bitset<Wmax> v(N);\n   \
    \ for (int i = 0; i < N; i++) {\n        int t;\n        cin >> t;\n        v[i]\
    \ = t;\n    }\n\n    cin >> T;\n    A = matpower(A, T);\n    for (int i = 0; i\
    \ < N; i++) A[i][N] = v[i];\n    A = gauss_jordan(N + 1, A);\n\n    for (int i\
    \ = 0; i < N; i++) {\n        if (A[i].count() == 1 and A[i][N]) {\n         \
    \   cout << \"none\\n\";\n            return 0;\n        }\n    }\n    if (!A[N\
    \ - 1][N - 1]) {\n        cout << \"ambiguous\\n\";\n        return 0;\n    }\n\
    \    bitset<Wmax> ret;\n    for (int i = N - 1; i >= 0; i--) {\n        int a\
    \ = 0;\n        for (int j = i + 1; j < N; j++) a ^= ret[j] * A[i][j];\n     \
    \   ret[i] = (a != A[i][N]);\n    }\n    for (int i = 0; i < N; i++) cout << ret[i]\
    \ << (i == N - 1 ? '\\n' : ' ');\n}\n"
  dependsOn:
  - linear_algebra_matrix/linalg_bitset.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/linalg_bitset.test.cpp
  requiredBy: []
  timestamp: '2021-06-13 19:08:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/linalg_bitset.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/linalg_bitset.test.cpp
- /verify/linear_algebra_matrix/test/linalg_bitset.test.cpp.html
title: linear_algebra_matrix/test/linalg_bitset.test.cpp
---
