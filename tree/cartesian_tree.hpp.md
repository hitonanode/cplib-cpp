---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tree/test/cartesian_tree.test.cpp
    title: tree/test/cartesian_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 2 \"tree/cartesian_tree.hpp\"\n#include <functional>\n#include\
    \ <vector>\n\n// Cartesian tree\n// Complexity: O(n)\n// By default, the smaller\
    \ node is nearer to the root\n// Return : -1 (root), parent_idx (otherwise)\n\
    // Example: [1, 0, 2] => [1, -1, 1]\n// Verified: https://judge.yosupo.jp/problem/cartesian_tree\n\
    template <class T, class Cmp = std::less<T>>\nstd::vector<int> cartesian_tree(const\
    \ std::vector<T> &X) {\n    const int n = X.size();\n    Cmp comp;\n    std::vector<int>\
    \ st(n);\n    int sz = 0;\n\n    std::vector<int> par(n, -1);\n\n    for (int\
    \ i = 0; i < n; ++i) {\n        while (sz >= 2 and comp(X[i], X[st[sz - 1]]))\
    \ {\n            par[st[sz - 1]] = comp(X[i], X[st[sz - 2]]) ? st[sz - 2] : i;\n\
    \            --sz;\n        }\n        if (sz == 1 and comp(X[i], X[st[sz - 1]]))\
    \ par[st[--sz]] = i;\n        st[sz++] = i;\n    }\n    for (; sz > 1; --sz) par[st[sz\
    \ - 1]] = st[sz - 2];\n    return par;\n};\n"
  code: "#pragma once\n#include <functional>\n#include <vector>\n\n// Cartesian tree\n\
    // Complexity: O(n)\n// By default, the smaller node is nearer to the root\n//\
    \ Return : -1 (root), parent_idx (otherwise)\n// Example: [1, 0, 2] => [1, -1,\
    \ 1]\n// Verified: https://judge.yosupo.jp/problem/cartesian_tree\ntemplate <class\
    \ T, class Cmp = std::less<T>>\nstd::vector<int> cartesian_tree(const std::vector<T>\
    \ &X) {\n    const int n = X.size();\n    Cmp comp;\n    std::vector<int> st(n);\n\
    \    int sz = 0;\n\n    std::vector<int> par(n, -1);\n\n    for (int i = 0; i\
    \ < n; ++i) {\n        while (sz >= 2 and comp(X[i], X[st[sz - 1]])) {\n     \
    \       par[st[sz - 1]] = comp(X[i], X[st[sz - 2]]) ? st[sz - 2] : i;\n      \
    \      --sz;\n        }\n        if (sz == 1 and comp(X[i], X[st[sz - 1]])) par[st[--sz]]\
    \ = i;\n        st[sz++] = i;\n    }\n    for (; sz > 1; --sz) par[st[sz - 1]]\
    \ = st[sz - 2];\n    return par;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/cartesian_tree.hpp
  requiredBy: []
  timestamp: '2021-10-13 23:08:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/cartesian_tree.test.cpp
documentation_of: tree/cartesian_tree.hpp
layout: document
title: Cartesian tree
---

比較可能な要素の列に対し，Cartesian tree を計算．各要素の親となる要素の番号を持った長さ $N$ の `std::vector<int>` を返す．$O(N)$．デフォルトでは小さい要素がより根に近くなるが，テンプレート引数に `std::greater<T>` を与えてやることで逆転可能．

## 使用方法

```cpp
std::vector<int> A(N);
for (auto &x : Ainv) x = -x;
auto ret = cartesian_tree(A);
auto ret2 = cartesian_tree<int, std::greater<int>>(Ainv);
```

## 問題例

- [Library Checker: Cartesian Tree](https://judge.yosupo.jp/problem/cartesian_tree)
- [Codeforces Round #745 (Div. 1) D. Subsequence](https://codeforces.com/contest/1580/problem/D)
