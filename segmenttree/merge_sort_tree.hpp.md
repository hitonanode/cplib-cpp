---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/merge_sort_tree.aoj2426.test.cpp
    title: segmenttree/test/merge_sort_tree.aoj2426.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://codeforces.com/contest/1288/submission/68865506
  bundledCode: "#line 2 \"segmenttree/merge_sort_tree.hpp\"\n#include <algorithm>\n\
    #include <vector>\n\n// CUT begin\n// Count elements in $[A_\\mathrm{begin}, ...,\
    \ A_{\\mathrm{end}-1}]$ which satisfy $A_i < \\mathrm{query}$\n// Complexity:\
    \ $O(N \\log N)$ for initialization, $O(\\log^2 N)$ for each query\n// Verified:\
    \ https://codeforces.com/contest/1288/submission/68865506\ntemplate <typename\
    \ T> struct merge_sort_tree {\n    int N;\n    std::vector<std::vector<T>> x;\n\
    \    merge_sort_tree() = default;\n    merge_sort_tree(const std::vector<T> &vec)\
    \ : N(vec.size()) {\n        x.resize(N * 2);\n        for (int i = 0; i < N;\
    \ i++) x[N + i] = {vec[i]};\n        for (int i = N - 1; i; i--) {\n         \
    \   std::merge(x[i * 2].begin(), x[i * 2].end(), x[i * 2 + 1].begin(), x[i * 2\
    \ + 1].end(), std::back_inserter(x[i]));\n        }\n    }\n    int cntLess(int\
    \ l, int r, T query) const {\n        l += N, r += N;\n        int ret = 0;\n\
    \        while (l < r) {\n            if (l & 1) ret += std::lower_bound(x[l].begin(),\
    \ x[l].end(), query) - x[l].begin(), l++;\n            if (r & 1) r--, ret +=\
    \ std::lower_bound(x[r].begin(), x[r].end(), query) - x[r].begin();\n        \
    \    l >>= 1, r >>= 1;\n        }\n        return ret;\n    }\n    int cntLesseq(int\
    \ l, int r, T query) const {\n        l += N, r += N;\n        int ret = 0;\n\
    \        while (l < r) {\n            if (l & 1) ret += std::upper_bound(x[l].begin(),\
    \ x[l].end(), query) - x[l].begin(), l++;\n            if (r & 1) r--, ret +=\
    \ std::upper_bound(x[r].begin(), x[r].end(), query) - x[r].begin();\n        \
    \    l >>= 1, r >>= 1;\n        }\n        return ret;\n    }\n    int cntMore(int\
    \ begin, int end, T query) const {\n        int tot = std::max(0, std::min(end,\
    \ N) - std::max(begin, 0));\n        return tot - cntLesseq(begin, end, query);\n\
    \    }\n    int cntMoreeq(int begin, int end, T query) const {\n        int tot\
    \ = std::max(0, std::min(end, N) - std::max(begin, 0));\n        return tot -\
    \ cntLess(begin, end, query);\n    }\n\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const merge_sort_tree &clt) {\n        os << '[';\n\
    \        for (int i = 0; i < clt.N; i++) os << clt.x[clt.N + i][0] << ',';\n \
    \       return os << ']';\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <vector>\n\n// CUT begin\n//\
    \ Count elements in $[A_\\mathrm{begin}, ..., A_{\\mathrm{end}-1}]$ which satisfy\
    \ $A_i < \\mathrm{query}$\n// Complexity: $O(N \\log N)$ for initialization, $O(\\\
    log^2 N)$ for each query\n// Verified: https://codeforces.com/contest/1288/submission/68865506\n\
    template <typename T> struct merge_sort_tree {\n    int N;\n    std::vector<std::vector<T>>\
    \ x;\n    merge_sort_tree() = default;\n    merge_sort_tree(const std::vector<T>\
    \ &vec) : N(vec.size()) {\n        x.resize(N * 2);\n        for (int i = 0; i\
    \ < N; i++) x[N + i] = {vec[i]};\n        for (int i = N - 1; i; i--) {\n    \
    \        std::merge(x[i * 2].begin(), x[i * 2].end(), x[i * 2 + 1].begin(), x[i\
    \ * 2 + 1].end(), std::back_inserter(x[i]));\n        }\n    }\n    int cntLess(int\
    \ l, int r, T query) const {\n        l += N, r += N;\n        int ret = 0;\n\
    \        while (l < r) {\n            if (l & 1) ret += std::lower_bound(x[l].begin(),\
    \ x[l].end(), query) - x[l].begin(), l++;\n            if (r & 1) r--, ret +=\
    \ std::lower_bound(x[r].begin(), x[r].end(), query) - x[r].begin();\n        \
    \    l >>= 1, r >>= 1;\n        }\n        return ret;\n    }\n    int cntLesseq(int\
    \ l, int r, T query) const {\n        l += N, r += N;\n        int ret = 0;\n\
    \        while (l < r) {\n            if (l & 1) ret += std::upper_bound(x[l].begin(),\
    \ x[l].end(), query) - x[l].begin(), l++;\n            if (r & 1) r--, ret +=\
    \ std::upper_bound(x[r].begin(), x[r].end(), query) - x[r].begin();\n        \
    \    l >>= 1, r >>= 1;\n        }\n        return ret;\n    }\n    int cntMore(int\
    \ begin, int end, T query) const {\n        int tot = std::max(0, std::min(end,\
    \ N) - std::max(begin, 0));\n        return tot - cntLesseq(begin, end, query);\n\
    \    }\n    int cntMoreeq(int begin, int end, T query) const {\n        int tot\
    \ = std::max(0, std::min(end, N) - std::max(begin, 0));\n        return tot -\
    \ cntLess(begin, end, query);\n    }\n\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const merge_sort_tree &clt) {\n        os << '[';\n\
    \        for (int i = 0; i < clt.N; i++) os << clt.x[clt.N + i][0] << ',';\n \
    \       return os << ']';\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/merge_sort_tree.hpp
  requiredBy: []
  timestamp: '2021-08-28 13:42:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/merge_sort_tree.aoj2426.test.cpp
documentation_of: segmenttree/merge_sort_tree.hpp
layout: document
title: "Merge sort tree \uFF08\u9759\u7684\u306A\u5217\u306E\u90E8\u5206\u5217\u306B\
  \u542B\u307E\u308C\u308B\u95BE\u5024\u4EE5\u4E0B\u306E\u8981\u7D20\u6570\u30AF\u30A8\
  \u30EA\uFF09"
---

静的な列 $[A_0, \dots, A_{N - 1}]$ について，以下のクエリを処理：


- `int cntLess(int l, int r, T query)` : $[l, r)$ に含まれる `query` 未満の要素数を計算．
- `int cntLesseq(int l, int r, T query)` : $[l, r)$ に含まれる `query` 以下の要素数を計算．
- `int cntMore(int l, int r, T query)` : $[l, r)$ に含まれる `query` より大きい要素数を計算．
- `int cntMoreeq(int l, int r, T query)` : $[l, r)$ に含まれる `query` 以上の要素数を計算．

計算量は構築 $O(N \log N)$，クエリ $O(N (\log N)^2)$，空間 $O(N \log N)$．

## Example

```cpp
vector<long long> ys;
merge_sort_tree<long long> tree(ys);
int ret = tree.cntLess(l, r, ylim) << '\n';
```

## 問題例

- [Educational Codeforces Round 80 (Rated for Div. 2) E. Messenger Simulator](https://codeforces.com/contest/1288/problem/E)
- [Japanese Alumni Group Summer Camp 2018 Day 3 Prefix Suffix Search](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2907)
