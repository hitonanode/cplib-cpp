---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/cartesian_tree.hpp
    title: Cartesian tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 1 \"tree/test/cartesian_tree.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/cartesian_tree\"\n#line 2 \"tree/cartesian_tree.hpp\"\
    \n#include <functional>\n#include <vector>\n\n// Cartesian tree\n// Complexity:\
    \ O(n)\n// By default, the smaller node is nearer to the root\n// Return : -1\
    \ (root), parent_idx (otherwise)\n// Example: [1, 0, 2] => [1, -1, 1]\n// Verified:\
    \ https://judge.yosupo.jp/problem/cartesian_tree\ntemplate <class T, class Cmp\
    \ = std::less<T>>\nstd::vector<int> cartesian_tree(const std::vector<T> &X) {\n\
    \    const int n = X.size();\n    Cmp comp;\n    std::vector<int> st(n);\n   \
    \ int sz = 0;\n\n    std::vector<int> par(n, -1);\n\n    for (int i = 0; i < n;\
    \ ++i) {\n        while (sz >= 2 and comp(X[i], X[st[sz - 1]])) {\n          \
    \  par[st[sz - 1]] = comp(X[i], X[st[sz - 2]]) ? st[sz - 2] : i;\n           \
    \ --sz;\n        }\n        if (sz == 1 and comp(X[i], X[st[sz - 1]])) par[st[--sz]]\
    \ = i;\n        st[sz++] = i;\n    }\n    for (; sz > 1; --sz) par[st[sz - 1]]\
    \ = st[sz - 2];\n    return par;\n};\n#line 3 \"tree/test/cartesian_tree.test.cpp\"\
    \n#include <cassert>\n#include <iostream>\nusing namespace std;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N;\n    cin >>\
    \ N;\n    std::vector<int> A(N);\n    for (auto &x : A) cin >> x;\n    auto Ainv\
    \ = A;\n    for (auto &x : Ainv) x = -x;\n    auto ret = cartesian_tree(A);\n\
    \    auto ret2 = cartesian_tree<int, std::greater<int>>(Ainv);\n    assert(ret\
    \ == ret2);\n    for (int i = 0; i < N; ++i) cout << (ret[i] < 0 ? i : ret[i])\
    \ << (i + 1 == N ? '\\n' : ' ');\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n#include\
    \ \"../cartesian_tree.hpp\"\n#include <cassert>\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int N;\n    cin >> N;\n    std::vector<int> A(N);\n    for (auto &x : A) cin\
    \ >> x;\n    auto Ainv = A;\n    for (auto &x : Ainv) x = -x;\n    auto ret =\
    \ cartesian_tree(A);\n    auto ret2 = cartesian_tree<int, std::greater<int>>(Ainv);\n\
    \    assert(ret == ret2);\n    for (int i = 0; i < N; ++i) cout << (ret[i] < 0\
    \ ? i : ret[i]) << (i + 1 == N ? '\\n' : ' ');\n}\n"
  dependsOn:
  - tree/cartesian_tree.hpp
  isVerificationFile: true
  path: tree/test/cartesian_tree.test.cpp
  requiredBy: []
  timestamp: '2021-10-13 23:08:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/cartesian_tree.test.cpp
layout: document
redirect_from:
- /verify/tree/test/cartesian_tree.test.cpp
- /verify/tree/test/cartesian_tree.test.cpp.html
title: tree/test/cartesian_tree.test.cpp
---
