---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/range_kth_smallest_offline.hpp
    title: data_structure/range_kth_smallest_offline.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/rectangle_sum.hpp
    title: data_structure/rectangle_sum.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/range_kth_smallest_offline.test.cpp
    title: data_structure/test/range_kth_smallest_offline.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/rectange_sum.test.cpp
    title: data_structure/test/rectange_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/binary_indexed_tree.test.cpp
    title: segmenttree/test/binary_indexed_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/point-add-range-sum.test.cpp
    title: segmenttree/test/point-add-range-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"segmenttree/binary_indexed_tree.hpp\"\n#include <algorithm>\n\
    #include <vector>\n\n// CUT begin\n// 0-indexed BIT (binary indexed tree / Fenwick\
    \ tree) (i : [0, len))\ntemplate <class T> struct BIT {\n    int n;\n    std::vector<T>\
    \ data;\n    BIT(int len = 0) : n(len), data(len) {}\n    void reset() { std::fill(data.begin(),\
    \ data.end(), T(0)); }\n    void add(int pos, T v) { // a[pos] += v\n        pos++;\n\
    \        while (pos > 0 and pos <= n) data[pos - 1] += v, pos += pos & -pos;\n\
    \    }\n    T sum(int k) const { // a[0] + ... + a[k - 1]\n        T res = 0;\n\
    \        while (k > 0) res += data[k - 1], k -= k & -k;\n        return res;\n\
    \    }\n\n    T sum(int l, int r) const { return sum(r) - sum(l); } // a[l] +\
    \ ... + a[r - 1]\n\n    template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const BIT &bit) {\n        T prv = 0;\n        os << '[';\n        for\
    \ (int i = 1; i <= bit.n; i++) {\n            T now = bit.sum(i);\n          \
    \  os << now - prv << ',', prv = now;\n        }\n        return os << ']';\n\
    \    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <vector>\n\n// CUT begin\n//\
    \ 0-indexed BIT (binary indexed tree / Fenwick tree) (i : [0, len))\ntemplate\
    \ <class T> struct BIT {\n    int n;\n    std::vector<T> data;\n    BIT(int len\
    \ = 0) : n(len), data(len) {}\n    void reset() { std::fill(data.begin(), data.end(),\
    \ T(0)); }\n    void add(int pos, T v) { // a[pos] += v\n        pos++;\n    \
    \    while (pos > 0 and pos <= n) data[pos - 1] += v, pos += pos & -pos;\n   \
    \ }\n    T sum(int k) const { // a[0] + ... + a[k - 1]\n        T res = 0;\n \
    \       while (k > 0) res += data[k - 1], k -= k & -k;\n        return res;\n\
    \    }\n\n    T sum(int l, int r) const { return sum(r) - sum(l); } // a[l] +\
    \ ... + a[r - 1]\n\n    template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const BIT &bit) {\n        T prv = 0;\n        os << '[';\n        for\
    \ (int i = 1; i <= bit.n; i++) {\n            T now = bit.sum(i);\n          \
    \  os << now - prv << ',', prv = now;\n        }\n        return os << ']';\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/binary_indexed_tree.hpp
  requiredBy:
  - data_structure/rectangle_sum.hpp
  - data_structure/range_kth_smallest_offline.hpp
  timestamp: '2021-11-06 11:36:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/rectange_sum.test.cpp
  - data_structure/test/range_kth_smallest_offline.test.cpp
  - segmenttree/test/point-add-range-sum.test.cpp
  - segmenttree/test/binary_indexed_tree.test.cpp
documentation_of: segmenttree/binary_indexed_tree.hpp
layout: document
title: "Binary indexed tree / Fenwick tree \uFF08BIT\u30FB\u30D5\u30A7\u30CB\u30C3\
  \u30AF\u6728\uFF09"
---

BIT の実装．テンプレート引数として渡すクラス $S$ は加算について結合法則を満たし，また逆元が取れる必要がある．

- `BIT<S> bit(n)` : コンストラクタ．長さ $n$ の数列 $A$ を $A\_0 = \dots = A\_{n - 1} = S()$ で初期化．計算量は $O(n)$．
- `sum(l, r)` : $A\_l + \dots + A\_{r - 1}$ を計算．計算量は $O(\log n)$．
- `sum(k)` : `sum(0, k)` と同じ．計算量は $O(\log n)$．
- `add(x, v)`: $A\_x$ に $v$ を加算．計算量は $O(\log n)$．

## Example

```cpp
BIT<int> bit(N);
bit.add(2, 5);

bit.sum(1, 6);
```

## 問題例

- [AOJ DSL_2_B: Range Sum Query (RSQ)](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B)
