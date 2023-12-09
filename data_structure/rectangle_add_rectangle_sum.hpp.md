---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/binary_indexed_tree.hpp
    title: "Binary indexed tree / Fenwick tree \uFF08BIT\u30FB\u30D5\u30A7\u30CB\u30C3\
      \u30AF\u6728\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/rectangle_add_rectangle_sum.point.test.cpp
    title: data_structure/test/rectangle_add_rectangle_sum.point.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/rectangle_add_rectangle_sum.test.cpp
    title: data_structure/test/rectangle_add_rectangle_sum.test.cpp
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
    \    }\n};\n#line 4 \"data_structure/rectangle_add_rectangle_sum.hpp\"\n#include\
    \ <tuple>\n#line 6 \"data_structure/rectangle_add_rectangle_sum.hpp\"\n\n// Static\
    \ rectangle add rectangle sum\n// Calculate sums of rectangular weights inside\
    \ the given rectangles\n// Complexity: O(q log q), q = # of rectangles / queries\n\
    template <class Int, class T> class RectangleAddRectangleSum {\n    struct AddQuery\
    \ {\n        Int xl, xr, yl, yr;\n        T val;\n    };\n    struct SumQuery\
    \ {\n        Int xl, xr, yl, yr;\n    };\n    std::vector<AddQuery> add_queries;\n\
    \    std::vector<SumQuery> sum_queries;\n\npublic:\n    RectangleAddRectangleSum()\
    \ = default;\n\n    // A[x][y] += val for (x, y) in [xl, xr) * [yl, yr)\n    void\
    \ add_rectangle(Int xl, Int xr, Int yl, Int yr, T val) {\n        add_queries.push_back(AddQuery{xl,\
    \ xr, yl, yr, val});\n    }\n\n    // Get sum of A[x][y] for (x, y) in [xl, xr)\
    \ * [yl, yr)\n    void add_query(Int xl, Int xr, Int yl, Int yr) {\n        sum_queries.push_back(SumQuery{xl,\
    \ xr, yl, yr});\n    }\n\n    std::vector<T> solve() const {\n        std::vector<Int>\
    \ ys;\n        for (const auto &a : add_queries) {\n            ys.push_back(a.yl);\n\
    \            ys.push_back(a.yr);\n        }\n        std::sort(ys.begin(), ys.end());\n\
    \        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n\n        const\
    \ int Y = ys.size();\n\n        std::vector<std::tuple<Int, int, int>> ops;\n\
    \        for (int q = 0; q < int(sum_queries.size()); ++q) {\n            ops.emplace_back(sum_queries[q].xl,\
    \ 0, q);\n            ops.emplace_back(sum_queries[q].xr, 1, q);\n        }\n\
    \        for (int q = 0; q < int(add_queries.size()); ++q) {\n            ops.emplace_back(add_queries[q].xl,\
    \ 2, q);\n            ops.emplace_back(add_queries[q].xr, 3, q);\n        }\n\
    \        std::sort(ops.begin(), ops.end());\n\n        BIT<T> b00(Y), b01(Y),\
    \ b10(Y), b11(Y);\n        std::vector<T> ret(sum_queries.size());\n        for\
    \ (auto o : ops) {\n            int qtype = std::get<1>(o), q = std::get<2>(o);\n\
    \            if (qtype >= 2) {\n                const AddQuery &query = add_queries.at(q);\n\
    \                int i = std::lower_bound(ys.begin(), ys.end(), query.yl) - ys.begin();\n\
    \                int j = std::lower_bound(ys.begin(), ys.end(), query.yr) - ys.begin();\n\
    \                T x = std::get<0>(o);\n                T yi = query.yl, yj =\
    \ query.yr;\n                if (qtype & 1) std::swap(i, j), std::swap(yi, yj);\n\
    \n                b00.add(i, x * yi * query.val);\n                b01.add(i,\
    \ -x * query.val);\n                b10.add(i, -yi * query.val);\n           \
    \     b11.add(i, query.val);\n                b00.add(j, -x * yj * query.val);\n\
    \                b01.add(j, x * query.val);\n                b10.add(j, yj * query.val);\n\
    \                b11.add(j, -query.val);\n            } else {\n             \
    \   const SumQuery &query = sum_queries.at(q);\n                int i = std::lower_bound(ys.begin(),\
    \ ys.end(), query.yl) - ys.begin();\n                int j = std::lower_bound(ys.begin(),\
    \ ys.end(), query.yr) - ys.begin();\n                T x = std::get<0>(o);\n \
    \               T yi = query.yl, yj = query.yr;\n                if (qtype & 1)\
    \ std::swap(i, j), std::swap(yi, yj);\n\n                ret[q] += b00.sum(i)\
    \ + b01.sum(i) * yi + b10.sum(i) * x + b11.sum(i) * x * yi;\n                ret[q]\
    \ -= b00.sum(j) + b01.sum(j) * yj + b10.sum(j) * x + b11.sum(j) * x * yj;\n  \
    \          }\n        }\n        return ret;\n    }\n};\n"
  code: "#pragma once\n#include \"../segmenttree/binary_indexed_tree.hpp\"\n#include\
    \ <algorithm>\n#include <tuple>\n#include <vector>\n\n// Static rectangle add\
    \ rectangle sum\n// Calculate sums of rectangular weights inside the given rectangles\n\
    // Complexity: O(q log q), q = # of rectangles / queries\ntemplate <class Int,\
    \ class T> class RectangleAddRectangleSum {\n    struct AddQuery {\n        Int\
    \ xl, xr, yl, yr;\n        T val;\n    };\n    struct SumQuery {\n        Int\
    \ xl, xr, yl, yr;\n    };\n    std::vector<AddQuery> add_queries;\n    std::vector<SumQuery>\
    \ sum_queries;\n\npublic:\n    RectangleAddRectangleSum() = default;\n\n    //\
    \ A[x][y] += val for (x, y) in [xl, xr) * [yl, yr)\n    void add_rectangle(Int\
    \ xl, Int xr, Int yl, Int yr, T val) {\n        add_queries.push_back(AddQuery{xl,\
    \ xr, yl, yr, val});\n    }\n\n    // Get sum of A[x][y] for (x, y) in [xl, xr)\
    \ * [yl, yr)\n    void add_query(Int xl, Int xr, Int yl, Int yr) {\n        sum_queries.push_back(SumQuery{xl,\
    \ xr, yl, yr});\n    }\n\n    std::vector<T> solve() const {\n        std::vector<Int>\
    \ ys;\n        for (const auto &a : add_queries) {\n            ys.push_back(a.yl);\n\
    \            ys.push_back(a.yr);\n        }\n        std::sort(ys.begin(), ys.end());\n\
    \        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n\n        const\
    \ int Y = ys.size();\n\n        std::vector<std::tuple<Int, int, int>> ops;\n\
    \        for (int q = 0; q < int(sum_queries.size()); ++q) {\n            ops.emplace_back(sum_queries[q].xl,\
    \ 0, q);\n            ops.emplace_back(sum_queries[q].xr, 1, q);\n        }\n\
    \        for (int q = 0; q < int(add_queries.size()); ++q) {\n            ops.emplace_back(add_queries[q].xl,\
    \ 2, q);\n            ops.emplace_back(add_queries[q].xr, 3, q);\n        }\n\
    \        std::sort(ops.begin(), ops.end());\n\n        BIT<T> b00(Y), b01(Y),\
    \ b10(Y), b11(Y);\n        std::vector<T> ret(sum_queries.size());\n        for\
    \ (auto o : ops) {\n            int qtype = std::get<1>(o), q = std::get<2>(o);\n\
    \            if (qtype >= 2) {\n                const AddQuery &query = add_queries.at(q);\n\
    \                int i = std::lower_bound(ys.begin(), ys.end(), query.yl) - ys.begin();\n\
    \                int j = std::lower_bound(ys.begin(), ys.end(), query.yr) - ys.begin();\n\
    \                T x = std::get<0>(o);\n                T yi = query.yl, yj =\
    \ query.yr;\n                if (qtype & 1) std::swap(i, j), std::swap(yi, yj);\n\
    \n                b00.add(i, x * yi * query.val);\n                b01.add(i,\
    \ -x * query.val);\n                b10.add(i, -yi * query.val);\n           \
    \     b11.add(i, query.val);\n                b00.add(j, -x * yj * query.val);\n\
    \                b01.add(j, x * query.val);\n                b10.add(j, yj * query.val);\n\
    \                b11.add(j, -query.val);\n            } else {\n             \
    \   const SumQuery &query = sum_queries.at(q);\n                int i = std::lower_bound(ys.begin(),\
    \ ys.end(), query.yl) - ys.begin();\n                int j = std::lower_bound(ys.begin(),\
    \ ys.end(), query.yr) - ys.begin();\n                T x = std::get<0>(o);\n \
    \               T yi = query.yl, yj = query.yr;\n                if (qtype & 1)\
    \ std::swap(i, j), std::swap(yi, yj);\n\n                ret[q] += b00.sum(i)\
    \ + b01.sum(i) * yi + b10.sum(i) * x + b11.sum(i) * x * yi;\n                ret[q]\
    \ -= b00.sum(j) + b01.sum(j) * yj + b10.sum(j) * x + b11.sum(j) * x * yj;\n  \
    \          }\n        }\n        return ret;\n    }\n};\n"
  dependsOn:
  - segmenttree/binary_indexed_tree.hpp
  isVerificationFile: false
  path: data_structure/rectangle_add_rectangle_sum.hpp
  requiredBy: []
  timestamp: '2022-07-05 20:49:30+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/rectangle_add_rectangle_sum.point.test.cpp
  - data_structure/test/rectangle_add_rectangle_sum.test.cpp
documentation_of: data_structure/rectangle_add_rectangle_sum.hpp
layout: document
title: "Static rectangle add rectangle sum \uFF08\u77E9\u5F62\u4E00\u69D8\u52A0\u7B97\
  \u30FB\u77E9\u5F62\u7DCF\u548C\u53D6\u5F97\uFF09"
---

以下の処理を $O(n \log n)$ （$n$ は総クエリ数）で行う．

- 事前矩形加算クエリ：$x\_l \le x < x\_r, y\_l \le y < y\_r$ を満たす各格子点 $(x, y)$ に重み $v$ を加算する．
- 矩形和取得クエリ：$x\_l \le x < x\_r, y\_l \le y < y\_r$ を満たす各格子点 $(x, y)$ の重みの総和を取得する．

## 原理

単一の矩形和取得クエリ $(x\_l, x\_r, y\_l, y\_r)$ によって得られる値を $f(x\_l, x\_r, y\_l, y\_r)$ と表記すると，


$\displaystyle
    f(x\_l, x\_r, y\_l, y\_r) = f(-\infty, x\_r, -\infty, y\_r) - f(-\infty, x\_l, -\infty, y\_r) - f(-\infty, x\_r, -\infty, y\_l) + f(-\infty, x\_l, -\infty, y\_l)
$

が成立する．よって，矩形和取得クエリとして $x\_l = y\_l = -\infty$ のものにだけ対応できればよい．

同様に，$(x\_l, x\_r, y\_l, y\_r)$ 型の矩形加算クエリも，$(x\_*, \infty, y\_*, \infty)$ 型のクエリの重ね合わせとして表現できる．

$(x\_a, \infty, y\_a, \infty)$ 型の矩形加算クエリの，$(-\infty, x\_s, -\infty, y\_s)$ 型の矩形和取得クエリへの寄与を考えたい．この寄与は $x\_a < x\_s$ または $y\_a < y\_s$ を満たさない場合ゼロとなる．両方を満たす場合は重みの寄与は $(x\_s - x\_a)(y\_s - y\_a)$ 倍される．

$y$ 軸方向のデータの管理に Fenwick tree を使用して $x$ 軸方向に平面走査を行うことで，$x\_a < x\_s$ 及び $y\_a < y\_s$ の制約の考慮が可能である．各矩形加算クエリに対して Fenwick tree を更新し，矩形和取得クエリ $(x\_s, y\_s)$ に対して Fenwick tree の和を求めればよい．このとき，取得すべき重みは $x\_s, y\_s$ についてそれぞれ $1$ 次の項と $0$ 次の項に展開できるから，それぞれの項を管理する $2^2 = 4$ 本の Fenwick tree を持つことで $x\_s, y\_s$ に関する多項式の形をした重みの寄与が適切に計算できる．

## 使用方法

```cpp
RectangleAddRectangleSum<int, mint> rect_sum;

rect_sum.add_rectangle(xl, xr, yl, yr, mint(w));  // Add w to each of [xl, xr) * [yl, yr)

rect_sum.add_query(l, r, d, u); // Get sum of [l, r) * [d, u)

vector<mint> ret = rect_sum.solve();
```

## 問題例

- [Codeforces Round #789 (Div. 1) E. Tokitsukaze and Beautiful Subsegments](https://codeforces.com/contest/1677/problem/E)
