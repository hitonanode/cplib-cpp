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
  bundledCode: "#line 2 \"utilities/offline_sum_of_linear.hpp\"\n#include <cassert>\n\
    #include <tuple>\n#include <vector>\n\n// CUT begin\n// Offline sum of linear\
    \ segments\ntemplate <class T> struct offline_sum_of_linear {\n    int N;\n  \
    \  std::vector<T> ret;\n    std::vector<std::tuple<int, int, T, T>> upds;\n  \
    \  offline_sum_of_linear(int N_) : N(N_), ret(N_) {}\n\n    // Add f0 + df * (x\
    \ - l) to A[x] for x in [l, r)\n    void add_linear(int l, int r, T f0, T df)\
    \ {\n        assert(0 <= l and l <= r and r <= N);\n        if (l < r) upds.emplace_back(l,\
    \ r, f0, df);\n    }\n    void run() {\n        if (upds.empty()) return;\n  \
    \      std::vector<T> tmp(N + 1);\n        int l, r;\n        T f0, df;\n    \
    \    for (const auto &q : upds) {\n            std::tie(l, r, f0, df) = q;\n \
    \           tmp[l + 1] += df;\n            tmp[r] -= df;\n        }\n        for\
    \ (int i = 0; i < N; i++) tmp[i + 1] += tmp[i];\n        for (const auto &q :\
    \ upds) {\n            std::tie(l, r, f0, df) = q;\n            tmp[l] += f0;\n\
    \            tmp[r] -= f0 + (r - l - 1) * df;\n        }\n        upds.clear();\n\
    \        for (int i = 0; i < N; i++) tmp[i + 1] += tmp[i], ret[i] += tmp[i];\n\
    \    }\n    T operator[](int i) {\n        assert(0 <= i and i < N);\n       \
    \ return run(), ret[i];\n    }\n    std::vector<T> vals() { return run(), ret;\
    \ }\n    int size() const { return N; }\n    template <class OStream>\n    friend\
    \ OStream &operator<<(OStream &os, const offline_sum_of_linear &x) {\n       \
    \ auto y = x;\n        y.run();\n        os << '[';\n        for (auto v : y.ret)\
    \ os << v << ',';\n        return os << ']';\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <tuple>\n#include <vector>\n\n\
    // CUT begin\n// Offline sum of linear segments\ntemplate <class T> struct offline_sum_of_linear\
    \ {\n    int N;\n    std::vector<T> ret;\n    std::vector<std::tuple<int, int,\
    \ T, T>> upds;\n    offline_sum_of_linear(int N_) : N(N_), ret(N_) {}\n\n    //\
    \ Add f0 + df * (x - l) to A[x] for x in [l, r)\n    void add_linear(int l, int\
    \ r, T f0, T df) {\n        assert(0 <= l and l <= r and r <= N);\n        if\
    \ (l < r) upds.emplace_back(l, r, f0, df);\n    }\n    void run() {\n        if\
    \ (upds.empty()) return;\n        std::vector<T> tmp(N + 1);\n        int l, r;\n\
    \        T f0, df;\n        for (const auto &q : upds) {\n            std::tie(l,\
    \ r, f0, df) = q;\n            tmp[l + 1] += df;\n            tmp[r] -= df;\n\
    \        }\n        for (int i = 0; i < N; i++) tmp[i + 1] += tmp[i];\n      \
    \  for (const auto &q : upds) {\n            std::tie(l, r, f0, df) = q;\n   \
    \         tmp[l] += f0;\n            tmp[r] -= f0 + (r - l - 1) * df;\n      \
    \  }\n        upds.clear();\n        for (int i = 0; i < N; i++) tmp[i + 1] +=\
    \ tmp[i], ret[i] += tmp[i];\n    }\n    T operator[](int i) {\n        assert(0\
    \ <= i and i < N);\n        return run(), ret[i];\n    }\n    std::vector<T> vals()\
    \ { return run(), ret; }\n    int size() const { return N; }\n    template <class\
    \ OStream>\n    friend OStream &operator<<(OStream &os, const offline_sum_of_linear\
    \ &x) {\n        auto y = x;\n        y.run();\n        os << '[';\n        for\
    \ (auto v : y.ret) os << v << ',';\n        return os << ']';\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/offline_sum_of_linear.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/offline_sum_of_linear.hpp
layout: document
title: "Offline sum of linear segments \uFF08\u533A\u9593\u4E00\u6B21\u95A2\u6570\u52A0\
  \u7B97\u30AF\u30A8\u30EA\u306E\u7D2F\u7A4D\u548C\u3092\u7528\u3044\u305F\u30AA\u30D5\
  \u30E9\u30A4\u30F3\u51E6\u7406\uFF09"
---

全ての項の値がゼロで初期化された数列 $[A_0, \dots, A_{N -1}]$ に対して以下のクエリを処理．

- $l \le i < r$ を満たす各 $i$ について $A_i$ に $f_0 + (i - l) \cdot df$ を加算．時間計算量 $O(1)$．
- $[A_0, \dots, A_{N - 1}]$ の値を陽に計算・取得．$O(N)$．

## 使用方法

```cpp
offline_sum_of_linear<long long> f(N);
f.add_linear(l, r, f0, df);

long long vi = f[i]; // 特定の項の取得
vector<long long> values = f.vals(); // [f[0], ..., f[N - 1]] の一括取得
```

## 問題例

- [AtCoder Regular Contest 125 E - Snack](https://atcoder.jp/contests/arc125/tasks/arc125_e)
- [AtCoder Grand Contest 052 E - 3 Letters](https://atcoder.jp/contests/agc052/tasks/agc052_e)
