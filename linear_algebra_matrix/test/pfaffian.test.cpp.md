---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/pfaffian.hpp
    title: "Pfaffian of skew-symmetric matrix \uFF08\u6B6A\u5BFE\u79F0\u884C\u5217\
      \u306E\u30D1\u30D5\u30A3\u30A2\u30F3\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/pfaffian_of_matrix
    links:
    - https://judge.yosupo.jp/problem/pfaffian_of_matrix
  bundledCode: "#line 1 \"linear_algebra_matrix/test/pfaffian.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/pfaffian_of_matrix\"\n\n#line 2 \"\
    linear_algebra_matrix/pfaffian.hpp\"\n\n#include <utility>\n#include <vector>\n\
    \n// Calculate Pfaffian of Matrix\n// requirement: T is field, M is skew-symmetric\n\
    // Complexity: O(n^3)\n// Implementation is based on Nachia-san's submission https://judge.yosupo.jp/submission/278787\n\
    template <class T> T Pfaffian(const std::vector<std::vector<T>> &M) {\n    const\
    \ int n = M.size();\n    if (n % 2) return T{};\n\n    auto mat = M;\n    T res{1};\n\
    \n    for (int s = 0; s < n; s += 2) {\n        {\n            int t = s + 1;\n\
    \            while (t < n and mat[s][t] == T{}) ++t;\n            if (t == n)\
    \ return T{};\n\n            if (t != s + 1) {\n                for (int i = s;\
    \ i < n; ++i) std::swap(mat[s + 1][i], mat[t][i]);\n                for (int i\
    \ = s; i < n; ++i) std::swap(mat[i][s + 1], mat[i][t]);\n                res =\
    \ -res;\n            }\n        }\n\n        res *= mat[s][s + 1];\n\n       \
    \ const T w = mat[s][s + 1].inv();\n\n        for (int i = s + 1; i < n; ++i)\
    \ mat[s][i] *= w;\n        for (int i = s + 1; i < n; ++i) mat[i][s] *= w;\n\n\
    \        // mat[s+2:, s+2:] += mat[:, s] ^ mat[s + 1, :]\n        for (int i =\
    \ s + 2; i < n; ++i) {\n            for (int j = s + 2; j < n; ++j) {\n      \
    \          // mat[i][j] += mat[i][s] * mat[s + 1][j] - mat[i][s + 1] * mat[s][j];\n\
    \                mat[i][j] += mat[s + 1][i] * mat[s][j] - mat[s][i] * mat[s +\
    \ 1][j];\n            }\n        }\n    }\n\n    return res;\n}\n#line 4 \"linear_algebra_matrix/test/pfaffian.test.cpp\"\
    \n\n#include <iostream>\n#line 7 \"linear_algebra_matrix/test/pfaffian.test.cpp\"\
    \n\n#include <atcoder/modint>\n\nusing namespace std;\nusing mint = atcoder::modint998244353;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int\
    \ N;\n    cin >> N;\n    vector A(N * 2, vector<mint>(N * 2));\n    for (auto\
    \ &v : A) {\n        for (auto &x : v) {\n            int tmp;\n            cin\
    \ >> tmp;\n            x = tmp;\n        }\n    }\n\n    cout << Pfaffian(A).val()\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/pfaffian_of_matrix\"\n\n\
    #include \"../pfaffian.hpp\"\n\n#include <iostream>\n#include <vector>\n\n#include\
    \ <atcoder/modint>\n\nusing namespace std;\nusing mint = atcoder::modint998244353;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int\
    \ N;\n    cin >> N;\n    vector A(N * 2, vector<mint>(N * 2));\n    for (auto\
    \ &v : A) {\n        for (auto &x : v) {\n            int tmp;\n            cin\
    \ >> tmp;\n            x = tmp;\n        }\n    }\n\n    cout << Pfaffian(A).val()\
    \ << '\\n';\n}\n"
  dependsOn:
  - linear_algebra_matrix/pfaffian.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/pfaffian.test.cpp
  requiredBy: []
  timestamp: '2025-08-10 23:51:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/pfaffian.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/pfaffian.test.cpp
- /verify/linear_algebra_matrix/test/pfaffian.test.cpp.html
title: linear_algebra_matrix/test/pfaffian.test.cpp
---
