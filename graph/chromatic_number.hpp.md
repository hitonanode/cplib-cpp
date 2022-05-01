---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/chromatic_number.test.cpp
    title: graph/test/chromatic_number.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc187/tasks/abc187_f
    - https://judge.yosupo.jp/problem/chromatic_number,
    - https://www.slideshare.net/wata_orz/ss-12131479
  bundledCode: "#line 2 \"graph/chromatic_number.hpp\"\n#include <numeric>\n#include\
    \ <vector>\n\n// CUT begin\n// (vertex) chromatic number: \uFF08\u9802\u70B9\uFF09\
    \u5F69\u8272\u6570\n// Verified: https://judge.yosupo.jp/problem/chromatic_number,\
    \ https://atcoder.jp/contests/abc187/tasks/abc187_f\n// Reference:\n// [1] A.\
    \ Bjorklund and T. Husfeldt, \"Inclusion--Exclusion Algorithms for Counting Set\
    \ Partitions,\"\n//     2006 47th Annual IEEE Symposium on Foundations of Computer\
    \ Science (FOCS'06).\n// - https://www.slideshare.net/wata_orz/ss-12131479\ntemplate\
    \ <typename MODINT, typename Int> int ChromaticNumber(const std::vector<Int> &edge)\
    \ {\n    const int V = edge.size(), S = 1 << V;\n    if (V == 0) return 0;\n \
    \   std::vector<MODINT> f(S), g(S);\n    for (int s = 0; s < S; s++) g[s] = (__builtin_popcount(s)\
    \ & 1) ? 1 : -1;\n    f[0] = 1;\n    for (int s = 1; s < S; s++) {\n        int\
    \ i = __builtin_ctz(s);\n        f[s] = f[s - (1 << i)] + f[(s - (1 << i)) & ~edge[i]];\n\
    \    }\n    for (int k = 1; k < V; k++) {\n        for (int s = 0; s < S; s++)\
    \ g[s] *= f[s];\n        if (std::accumulate(g.begin(), g.end(), MODINT()).val())\
    \ return k;\n    }\n    return V;\n};\n"
  code: "#pragma once\n#include <numeric>\n#include <vector>\n\n// CUT begin\n// (vertex)\
    \ chromatic number: \uFF08\u9802\u70B9\uFF09\u5F69\u8272\u6570\n// Verified: https://judge.yosupo.jp/problem/chromatic_number,\
    \ https://atcoder.jp/contests/abc187/tasks/abc187_f\n// Reference:\n// [1] A.\
    \ Bjorklund and T. Husfeldt, \"Inclusion--Exclusion Algorithms for Counting Set\
    \ Partitions,\"\n//     2006 47th Annual IEEE Symposium on Foundations of Computer\
    \ Science (FOCS'06).\n// - https://www.slideshare.net/wata_orz/ss-12131479\ntemplate\
    \ <typename MODINT, typename Int> int ChromaticNumber(const std::vector<Int> &edge)\
    \ {\n    const int V = edge.size(), S = 1 << V;\n    if (V == 0) return 0;\n \
    \   std::vector<MODINT> f(S), g(S);\n    for (int s = 0; s < S; s++) g[s] = (__builtin_popcount(s)\
    \ & 1) ? 1 : -1;\n    f[0] = 1;\n    for (int s = 1; s < S; s++) {\n        int\
    \ i = __builtin_ctz(s);\n        f[s] = f[s - (1 << i)] + f[(s - (1 << i)) & ~edge[i]];\n\
    \    }\n    for (int k = 1; k < V; k++) {\n        for (int s = 0; s < S; s++)\
    \ g[s] *= f[s];\n        if (std::accumulate(g.begin(), g.end(), MODINT()).val())\
    \ return k;\n    }\n    return V;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/chromatic_number.hpp
  requiredBy: []
  timestamp: '2022-05-01 16:11:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/chromatic_number.test.cpp
documentation_of: graph/chromatic_number.hpp
layout: document
title: "Chromatic number of undirected graph \uFF08\u7121\u5411\u30B0\u30E9\u30D5\u306E\
  \u5F69\u8272\u6570\uFF09"
---

$N$ 頂点のグラフの彩色数（隣り合う頂点を異なる色で全頂点を塗るときに要する最小の色の数）を求める確率的アルゴリズム．時間計算量 $O(N 2^N)$．

コード中の $f(S)$ は頂点集合 $S$ に関する部分グラフ上の（空集合を含む）独立集合の個数．各要素を $k$ 乗した $f^k(S)$ にメビウス変換を施したもの $h(S)$ は，「集合 $S$ を $k$ 個の独立集合で被覆する方法の総数」となるので，全頂点に関するこの個数が非零になるまで $k$ を増やしていけばよい．本コードでは $\bmod p$ で計算を行うが，初めて非零になったときの組合せの個数がたまたま $p$ の倍数になったときに動作が失敗することに注意．

## 使用方法

```cpp
vector<int> to(N);
while (M--) {
    int u, v;
    cin >> u >> v;
    to[u] |= 1 << v;
    to[v] |= 1 << u;
}
cout << ChromaticNumber<ModIntRuntime>(to) << '\n';
```

## 問題例

- [Library Checker - Chromatic Number](https://judge.yosupo.jp/problem/chromatic_number)
- [AtCoder Beginner Contest 187 F - Close Group](https://atcoder.jp/contests/abc187/tasks/abc187_f)
