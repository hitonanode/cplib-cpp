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
    - https://take44444.github.io/Algorithm-Book/range/mo/main.html#mos-algorithm
  bundledCode: "#line 2 \"other_algorithms/hilbert_order_mos.hpp\"\n#include <algorithm>\n\
    #include <numeric>\n#include <utility>\n#include <vector>\n\n// Hilbert order\
    \ of given 2D point (x, y)\n// constraints: 0 <= x, y < 2^32\n// Reference: https://take44444.github.io/Algorithm-Book/range/mo/main.html#mos-algorithm\n\
    unsigned long long hilbert_order(unsigned x, unsigned y) {\n    unsigned long\
    \ long ret = 0;\n    for (unsigned s = 1U << 31; s; s >>= 1) {\n        unsigned\
    \ rx = (x & s) > 0, ry = (y & s) > 0;\n        ret += (unsigned long long)s *\
    \ s * ((3 * rx) ^ ry);\n\n        if (ry == 0) {\n            if (rx == 1) {\n\
    \                x = -x - 1;\n                y = -y - 1;\n            }\n   \
    \         std::swap(x, y);\n        }\n    }\n\n    return ret;\n}\n\n// Given\
    \ queries of 2D points, return the indices sorted by Hilbert order\n// Can be\
    \ used for Mo's algorithm\ntemplate <class Int>\nstd::vector<int> sort_by_hilbert_order(const\
    \ std::vector<std::pair<Int, Int>> &points) {\n    static_assert(std::is_integral<Int>::value,\
    \ \"Int must be integral\");\n    static_assert(sizeof(Int) <= 4, \"Int must be\
    \ 32-bit integer\");\n\n    if (points.empty()) return {};\n\n    // Int min_x\
    \ = points[0].first, min_y = points[0].second;\n    Int min_x = Int(), min_y =\
    \ Int();\n    for (auto [x, y] : points) {\n        if (x < min_x) min_x = x;\n\
    \        if (y < min_y) min_y = y;\n    }\n\n    std::vector<unsigned long long>\
    \ hilbert_values(points.size());\n    for (int i = 0; i < (int)points.size();\
    \ ++i) {\n        hilbert_values[i] = hilbert_order(points[i].first - min_x, points[i].second\
    \ - min_y);\n    }\n\n    std::vector<int> indices(points.size());\n    std::iota(indices.begin(),\
    \ indices.end(), 0);\n    std::sort(indices.begin(), indices.end(),\n        \
    \      [&](int i, int j) { return hilbert_values[i] < hilbert_values[j]; });\n\
    \n    return indices;\n}\n\n// Mo's algorithm with Hilbert order\n// - add(x,\
    \ y) : Add (x, y) as query.\n// - run(IncX, DecX, IncY, DecY, Query) : run Mo's\
    \ algorithm.\n// - run(Add, Remove, Query) : run Mo's algorithm with Add, Remove,\
    \ and Query functions. add(x, y) means [x, y).\nstruct MosAlgorithmHilbertOrder\
    \ {\n    int cx, cy;\n    std::vector<std::pair<int, int>> queries;\n\n    MosAlgorithmHilbertOrder(int\
    \ x_init, int y_init) : cx(x_init), cy(y_init) {}\n\n    void add(int x, int y)\
    \ { queries.emplace_back(x, y); }\n\n    template <class IncX, class DecX, class\
    \ IncY, class DecY, class Query>\n    void run(IncX inc_x, DecX dec_x, IncY inc_y,\
    \ DecY dec_y, Query query) {\n\n        std::vector<int> indices = sort_by_hilbert_order(queries);\n\
    \        int x = cx, y = cy;\n\n        for (int q : indices) {\n            while\
    \ (y < queries[q].second) inc_y(y, y + 1), ++y;\n            while (x > queries[q].first)\
    \ dec_x(x, x - 1), --x;\n            while (y > queries[q].second) dec_y(y, y\
    \ - 1), --y;\n            while (x < queries[q].first) inc_x(x, x + 1), ++x;\n\
    \            query(q);\n        }\n    }\n\n    template <typename F1, typename\
    \ F3, typename F5> void run(F1 Add, F3 Remove, F5 Query) {\n        run([&](int\
    \ x, int) { Remove(x); }, [&](int, int x) { Add(x); },\n            [&](int y,\
    \ int) { Add(y); }, [&](int, int y) { Remove(y); }, Query);\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\n// Hilbert order of given 2D point (x, y)\n// constraints:\
    \ 0 <= x, y < 2^32\n// Reference: https://take44444.github.io/Algorithm-Book/range/mo/main.html#mos-algorithm\n\
    unsigned long long hilbert_order(unsigned x, unsigned y) {\n    unsigned long\
    \ long ret = 0;\n    for (unsigned s = 1U << 31; s; s >>= 1) {\n        unsigned\
    \ rx = (x & s) > 0, ry = (y & s) > 0;\n        ret += (unsigned long long)s *\
    \ s * ((3 * rx) ^ ry);\n\n        if (ry == 0) {\n            if (rx == 1) {\n\
    \                x = -x - 1;\n                y = -y - 1;\n            }\n   \
    \         std::swap(x, y);\n        }\n    }\n\n    return ret;\n}\n\n// Given\
    \ queries of 2D points, return the indices sorted by Hilbert order\n// Can be\
    \ used for Mo's algorithm\ntemplate <class Int>\nstd::vector<int> sort_by_hilbert_order(const\
    \ std::vector<std::pair<Int, Int>> &points) {\n    static_assert(std::is_integral<Int>::value,\
    \ \"Int must be integral\");\n    static_assert(sizeof(Int) <= 4, \"Int must be\
    \ 32-bit integer\");\n\n    if (points.empty()) return {};\n\n    // Int min_x\
    \ = points[0].first, min_y = points[0].second;\n    Int min_x = Int(), min_y =\
    \ Int();\n    for (auto [x, y] : points) {\n        if (x < min_x) min_x = x;\n\
    \        if (y < min_y) min_y = y;\n    }\n\n    std::vector<unsigned long long>\
    \ hilbert_values(points.size());\n    for (int i = 0; i < (int)points.size();\
    \ ++i) {\n        hilbert_values[i] = hilbert_order(points[i].first - min_x, points[i].second\
    \ - min_y);\n    }\n\n    std::vector<int> indices(points.size());\n    std::iota(indices.begin(),\
    \ indices.end(), 0);\n    std::sort(indices.begin(), indices.end(),\n        \
    \      [&](int i, int j) { return hilbert_values[i] < hilbert_values[j]; });\n\
    \n    return indices;\n}\n\n// Mo's algorithm with Hilbert order\n// - add(x,\
    \ y) : Add (x, y) as query.\n// - run(IncX, DecX, IncY, DecY, Query) : run Mo's\
    \ algorithm.\n// - run(Add, Remove, Query) : run Mo's algorithm with Add, Remove,\
    \ and Query functions. add(x, y) means [x, y).\nstruct MosAlgorithmHilbertOrder\
    \ {\n    int cx, cy;\n    std::vector<std::pair<int, int>> queries;\n\n    MosAlgorithmHilbertOrder(int\
    \ x_init, int y_init) : cx(x_init), cy(y_init) {}\n\n    void add(int x, int y)\
    \ { queries.emplace_back(x, y); }\n\n    template <class IncX, class DecX, class\
    \ IncY, class DecY, class Query>\n    void run(IncX inc_x, DecX dec_x, IncY inc_y,\
    \ DecY dec_y, Query query) {\n\n        std::vector<int> indices = sort_by_hilbert_order(queries);\n\
    \        int x = cx, y = cy;\n\n        for (int q : indices) {\n            while\
    \ (y < queries[q].second) inc_y(y, y + 1), ++y;\n            while (x > queries[q].first)\
    \ dec_x(x, x - 1), --x;\n            while (y > queries[q].second) dec_y(y, y\
    \ - 1), --y;\n            while (x < queries[q].first) inc_x(x, x + 1), ++x;\n\
    \            query(q);\n        }\n    }\n\n    template <typename F1, typename\
    \ F3, typename F5> void run(F1 Add, F3 Remove, F5 Query) {\n        run([&](int\
    \ x, int) { Remove(x); }, [&](int, int x) { Add(x); },\n            [&](int y,\
    \ int) { Add(y); }, [&](int, int y) { Remove(y); }, Query);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/hilbert_order_mos.hpp
  requiredBy: []
  timestamp: '2025-05-12 22:55:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other_algorithms/hilbert_order_mos.hpp
layout: document
title: "Mo's algorithm by Hilbert order \uFF08Hilbert order \u306B\u3088\u308B\u533A\
  \u9593\u30AF\u30A8\u30EA\u5E73\u65B9\u5206\u5272\uFF09"
---

Mo's algorithm の一種で，2 次元平面上の点として表現可能なクエリ群を Hilbert 曲線上の順序に従って処理する． $x, y$ 座標の値の範囲が $N$ でクエリが $Q$ 個のときの計算量は $O(N \sqrt{Q})$.

## 使用方法

### 一般の 2 次元平面上の点クエリの場合

```cpp
vector<Result> ret(Q); // 答えを格納する領域
int x_init = 0, y_init = 0;

MosAlgorithmHilbertOrder mo(x_init, y_init);
for (int q = 0; q < Q; q++) {
    mo.add(X[q], Y[q]);
}
auto inc_x = [&](int old_x, int new_x) -> void { /* x 座標が 1 増えて old_x から new_x になったときの処理 */ };
auto dec_x = [&](int old_x, int new_x) -> void { /* x 座標が 1 減って old_x から new_x になったときの処理 */ };
auto inc_y = [&](int old_y, int new_y) -> void { /* y 座標が 1 増えて old_y から new_y になったときの処理 */ };
auto dec_y = [&](int old_y, int new_y) -> void { /* y 座標が 1 減って old_y から new_y になったときの処理 */ };
auto solve = [&](int q) -> void { ret[q] = f(q); /* q 個目のクエリを解く処理 */ };

mo.run(inc_x, dec_x, inc_y, dec_y, solve);

for (auto ans : ret) cout << ans << '\n';
```

### 特に半開区間 $[l, r)$ クエリで区間の左右の伸張・収縮が同一の関数で書ける場合

```cpp
MosAlgorithmHilbertOrder mos(0, 0);
for (auto [l, r] : queries) {
    mos.add(l, r);
}

mos.run(
    [&](int i) { /* Add i */ },
    [&](int i) { /* Remove i */ },
    [&](int q) { /* ret.at(q) = get_solution(); */ }
);
```

## 問題例

- [AtCoder Beginner Contest 384 G - Abs Sum](https://atcoder.jp/contests/abc384/tasks/abc384_g)
- [AtCoder Beginner Contest 405 G - Range Shuffle Query](https://atcoder.jp/contests/abc405/tasks/abc405_g)

## Links

- [An alternative sorting order for Mo's algorithm - Codeforces](https://codeforces.com/blog/entry/61203)
- [Mo's algorithm - アルゴリズムとデータ構造大全](https://take44444.github.io/Algorithm-Book/range/mo/main.html)
