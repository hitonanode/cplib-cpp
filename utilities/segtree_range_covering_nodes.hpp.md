---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/segtree_range_covering_nodes.hpp\"\n#include <algorithm>\n\
    #include <vector>\n\n// CUT begin\n// Enumerate nodes of nonrecursive segtree\
    \ which cover [l, r)\nstd::vector<int> segtree_range_covering_nodes(int N, int\
    \ l, int r) {\n    std::vector<int> ret, ret_rev;\n    l += N, r += N;\n    while\
    \ (l < r) {\n        if (l & 1) ret.push_back(l++);\n        if (r & 1) ret_rev.push_back(--r);\n\
    \        l >>= 1, r >>= 1;\n    }\n    std::reverse(ret_rev.begin(), ret_rev.end());\n\
    \    ret.insert(ret.end(), ret_rev.begin(), ret_rev.end());\n    return ret;\n\
    }\n"
  code: "#pragma once\n#include <algorithm>\n#include <vector>\n\n// CUT begin\n//\
    \ Enumerate nodes of nonrecursive segtree which cover [l, r)\nstd::vector<int>\
    \ segtree_range_covering_nodes(int N, int l, int r) {\n    std::vector<int> ret,\
    \ ret_rev;\n    l += N, r += N;\n    while (l < r) {\n        if (l & 1) ret.push_back(l++);\n\
    \        if (r & 1) ret_rev.push_back(--r);\n        l >>= 1, r >>= 1;\n    }\n\
    \    std::reverse(ret_rev.begin(), ret_rev.end());\n    ret.insert(ret.end(),\
    \ ret_rev.begin(), ret_rev.end());\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/segtree_range_covering_nodes.hpp
  requiredBy: []
  timestamp: '2021-05-03 20:32:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/segtree_range_covering_nodes.hpp
layout: document
title: "\u975E\u518D\u5E30\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\u3067\u533A\u9593\u306B\
  \u5BFE\u5FDC\u3059\u308B\u9802\u70B9\u756A\u53F7\u306E\u5217\u6319"
---

長さ $N$ の列を管理する非再帰セグメント木のよく知られた実装において，区間 $[l, r)$ をカバーする頂点番号の列を，区間が管理する要素の位置順に出力する．セグメント木上に複雑なデータ構造を載せ（例：Convex Hull Trick），区間更新や取得を行う際などに使用機会がある．

なお，長さ $N$ の列のうち $i$ 番目の**要素を含む**全ての頂点を列挙するには，
```cpp
i += N;
whlie (i) { do_something(i), i >>= 1; }
```
とすればよい．

## 使用例

```cpp
vector<ConvexHullTrick<__int128>> chts(N * 2, true); // 長さ N の列に対して，区間を管理する CHT を 2N 個生成

for (auto i : segtree_range_covering_nodes(N, l, r)) {
    chts[i].add_convex_parabola(1, x, y0);
}
```

## リンク

- [非再帰セグ木サイコー！ 一番すきなセグ木です](https://hcpc-hokudai.github.io/archive/structure_segtree_001.pdf)
  - 非再帰セグメント木の解説．
- [使用例（早稲田大学プログラミングコンテスト2019 I - Ramen）](https://atcoder.jp/contests/wupc2019/submissions/22283489)
  - セグメント木に Convex Hull Trick を載せる．
