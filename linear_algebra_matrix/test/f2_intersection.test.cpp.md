---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/f2_linear_space.hpp
    title: "$\\mathbb{F}_{2}$ linear space ($\\mathbb{F}_{2}$ \u7DDA\u5F62\u7A7A\u9593\
      )"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces
    links:
    - https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces
  bundledCode: "#line 1 \"linear_algebra_matrix/test/f2_intersection.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces\"\
    \n#line 2 \"linear_algebra_matrix/f2_linear_space.hpp\"\n#include <algorithm>\n\
    #include <utility>\n#include <vector>\n\ntemplate <class Int> struct f2_vector_space\
    \ {\n    std::vector<Int> basis;\n\n    f2_vector_space() = default;\n\n    Int\
    \ add(Int x) {\n        for (const Int &b : basis) x = std::min(x, x ^ b);\n\n\
    \        if (x) {\n            basis.push_back(x);\n            return x;\n  \
    \      } else {\n            return Int(0);\n        }\n    }\n};\n\nstd::vector<int>\
    \ f2_intersection(const std::vector<int> &A, const std::vector<int> &B) {\n  \
    \  f2_vector_space<long long> tmp;\n    for (int a : A) tmp.add(((long long)a\
    \ << 32) + a);\n\n    std::vector<int> ret;\n\n    for (int b : B) {\n       \
    \ long long v = (long long)b << 32;\n\n        auto u = tmp.add(v);\n        if\
    \ (u < (1LL << 32)) ret.push_back(u);\n    }\n\n    return ret;\n}\n#line 3 \"\
    linear_algebra_matrix/test/f2_intersection.test.cpp\"\n\n#include <iostream>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\
    \n    int T;\n    cin >> T;\n\n    while (T--) {\n        int n;\n        cin\
    \ >> n;\n        vector<int> A(n);\n        for (int &x : A) cin >> x;\n\n   \
    \     int m;\n        cin >> m;\n        vector<int> B(m);\n        for (int &x\
    \ : B) cin >> x;\n\n        auto C = f2_intersection(A, B);\n\n        cout <<\
    \ C.size();\n        for (int x : C) cout << ' ' << x;\n        cout << '\\n';\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces\"\
    \n#include \"../f2_linear_space.hpp\"\n\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\
    \n    int T;\n    cin >> T;\n\n    while (T--) {\n        int n;\n        cin\
    \ >> n;\n        vector<int> A(n);\n        for (int &x : A) cin >> x;\n\n   \
    \     int m;\n        cin >> m;\n        vector<int> B(m);\n        for (int &x\
    \ : B) cin >> x;\n\n        auto C = f2_intersection(A, B);\n\n        cout <<\
    \ C.size();\n        for (int x : C) cout << ' ' << x;\n        cout << '\\n';\n\
    \    }\n}\n"
  dependsOn:
  - linear_algebra_matrix/f2_linear_space.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/f2_intersection.test.cpp
  requiredBy: []
  timestamp: '2024-05-03 14:04:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/f2_intersection.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/f2_intersection.test.cpp
- /verify/linear_algebra_matrix/test/f2_intersection.test.cpp.html
title: linear_algebra_matrix/test/f2_intersection.test.cpp
---
