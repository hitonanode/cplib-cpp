---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/contest/375/submission/114665433
  bundledCode: "#line 2 \"other_algorithms/mos_algorithm.hpp\"\n#include <cassert>\n\
    #include <cmath>\n#include <utility>\n#include <vector>\n\n// Mo's algorithm\n\
    // - add_range(l, r) : Add [l, r) as query.\n// - run(Add, Remove, Query) : run\
    \ Mo's algorithm.\n//   - Add(i) : Add i-th element ([i + 1, r) -> [i, r)).\n\
    //   - Remove(i) : Remove i-th element (Inverse of Add(i)).\n//   - Query(q) :\
    \ Solve q-th problem.\n// Verified: https://codeforces.com/contest/375/submission/114665433\n\
    class MosAlgorithm {\n    static const int INF = 1 << 30;\n    int nmin, nmax;\n\
    \npublic:\n    std::vector<std::pair<int, int>> ranges;\n    MosAlgorithm() :\
    \ nmin(INF), nmax(-INF) {}\n\n    void add_range(int l, int r) {\n        assert(l\
    \ <= r);\n        nmin = std::min(nmin, l);\n        nmax = std::max(nmax, r);\n\
    \        ranges.emplace_back(l, r);\n    }\n    template <typename F1, typename\
    \ F2, typename F3, typename F4, typename F5>\n    void run(F1 AddRight, F2 AddLeft,\
    \ F3 RemoveRight, F4 RemoveLeft, F5 Query) {\n        const int Q = ranges.size();\n\
    \        if (!Q) return;\n        const int nbbucket = std::max(1, std::min<int>(nmax\
    \ - nmin, sqrt(Q)));\n        const int szbucket = (nmax - nmin + nbbucket - 1)\
    \ / nbbucket;\n        std::vector<int> qs(Q);\n        std::iota(qs.begin(),\
    \ qs.end(), 0);\n        std::sort(qs.begin(), qs.end(), [&](int q1, int q2) {\n\
    \            int b1 = (ranges[q1].first - nmin) / szbucket, b2 = (ranges[q2].first\
    \ - nmin) / szbucket;\n            if (b1 != b2)\n                return b1 <\
    \ b2;\n            else {\n                return (b1 & 1) ? (ranges[q1].second\
    \ > ranges[q2].second)\n                                : (ranges[q1].second <\
    \ ranges[q2].second);\n            }\n        });\n\n        int l = ranges[qs[0]].first,\
    \ r = l;\n        for (auto q : qs) {\n            while (r < ranges[q].second)\
    \ AddRight(r++);\n            while (l > ranges[q].first) AddLeft(--l);\n    \
    \        while (r > ranges[q].second) RemoveRight(--r);\n            while (l\
    \ < ranges[q].first) RemoveLeft(l++);\n            assert(l == ranges[q].first\
    \ and r == ranges[q].second);\n            Query(q);\n        }\n    }\n    template\
    \ <typename F1, typename F3, typename F5> void run(F1 Add, F3 Remove, F5 Query)\
    \ {\n        run(Add, Add, Remove, Remove, Query);\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <cmath>\n#include <utility>\n\
    #include <vector>\n\n// Mo's algorithm\n// - add_range(l, r) : Add [l, r) as query.\n\
    // - run(Add, Remove, Query) : run Mo's algorithm.\n//   - Add(i) : Add i-th element\
    \ ([i + 1, r) -> [i, r)).\n//   - Remove(i) : Remove i-th element (Inverse of\
    \ Add(i)).\n//   - Query(q) : Solve q-th problem.\n// Verified: https://codeforces.com/contest/375/submission/114665433\n\
    class MosAlgorithm {\n    static const int INF = 1 << 30;\n    int nmin, nmax;\n\
    \npublic:\n    std::vector<std::pair<int, int>> ranges;\n    MosAlgorithm() :\
    \ nmin(INF), nmax(-INF) {}\n\n    void add_range(int l, int r) {\n        assert(l\
    \ <= r);\n        nmin = std::min(nmin, l);\n        nmax = std::max(nmax, r);\n\
    \        ranges.emplace_back(l, r);\n    }\n    template <typename F1, typename\
    \ F2, typename F3, typename F4, typename F5>\n    void run(F1 AddRight, F2 AddLeft,\
    \ F3 RemoveRight, F4 RemoveLeft, F5 Query) {\n        const int Q = ranges.size();\n\
    \        if (!Q) return;\n        const int nbbucket = std::max(1, std::min<int>(nmax\
    \ - nmin, sqrt(Q)));\n        const int szbucket = (nmax - nmin + nbbucket - 1)\
    \ / nbbucket;\n        std::vector<int> qs(Q);\n        std::iota(qs.begin(),\
    \ qs.end(), 0);\n        std::sort(qs.begin(), qs.end(), [&](int q1, int q2) {\n\
    \            int b1 = (ranges[q1].first - nmin) / szbucket, b2 = (ranges[q2].first\
    \ - nmin) / szbucket;\n            if (b1 != b2)\n                return b1 <\
    \ b2;\n            else {\n                return (b1 & 1) ? (ranges[q1].second\
    \ > ranges[q2].second)\n                                : (ranges[q1].second <\
    \ ranges[q2].second);\n            }\n        });\n\n        int l = ranges[qs[0]].first,\
    \ r = l;\n        for (auto q : qs) {\n            while (r < ranges[q].second)\
    \ AddRight(r++);\n            while (l > ranges[q].first) AddLeft(--l);\n    \
    \        while (r > ranges[q].second) RemoveRight(--r);\n            while (l\
    \ < ranges[q].first) RemoveLeft(l++);\n            assert(l == ranges[q].first\
    \ and r == ranges[q].second);\n            Query(q);\n        }\n    }\n    template\
    \ <typename F1, typename F3, typename F5> void run(F1 Add, F3 Remove, F5 Query)\
    \ {\n        run(Add, Add, Remove, Remove, Query);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/mos_algorithm.hpp
  requiredBy: []
  timestamp: '2024-12-28 06:16:13+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other_algorithms/mos_algorithm.hpp
layout: document
title: "Mo's algorithm \uFF08\u533A\u9593\u30AF\u30A8\u30EA\u306B\u95A2\u3059\u308B\
  \u5E73\u65B9\u5206\u5272\u30C6\u30AF\u30CB\u30C3\u30AF\uFF09"
---

## 使用方法

```cpp
vector<Result> ret(Q); // 答えを格納する領域
MosAlgorithm mo;
for (int q = 0; q < Q; q++) {
    mo.add_range(L[q], R[q]);
}
auto add = [&](int i) -> void { /* 区間を延ばして i 番目の要素を追加したときの処理 */ };
auto remove = [&](int i) -> void { /* 区間を縮めて i 番目の要素を削除したときの処理 */ };
auto solve = [&](int q) -> void { ret[q] = f(q); /* q 個目のクエリを解く処理 */ };

mo.run(add, remove, solve);

for (auto x : ret) cout << x << '\n';
```

## 最適なバケット幅設定

列の長さを $N$, クエリを $Q$ 個とする．バケット幅を $W$ とするとバケット個数は $B = N / W$ 程度．

このとき，Add/Remove 演算は $BN + QW = \frac{N^2}{W} + QW$ 回程度生じる．これを最小にするのは $W = N / \sqrt{Q}$ と設定したときで，全体計算量は $O(N \sqrt{Q} \cdot C_\mathrm{Add/Erase} + Q \cdot C_\mathrm{query})$ となる．

## 問題例

- [Codeforces Round #221 (Div. 1) D. Tree and Queries](https://codeforces.com/contest/375/submission/114665433)
  - 部分木クエリにも使用可能（ただし DSU on tree でもより良い最悪計算量で同様のことが可能）．

## Links

- [Codeforces blog のコメント](https://codeforces.com/blog/entry/20032?#comment-248430) : "Mo's algorithm" の起源に関する議論．
- [Mo's algorithm - ei1333の日記](https://ei1333.hateblo.jp/entry/2017/09/11/211011)
  - 木の部分木クエリやパスクエリに対する Mo's algorithm の応用にも触れられている．
