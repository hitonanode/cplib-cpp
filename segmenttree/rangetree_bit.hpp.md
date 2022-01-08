---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: segmenttree/test/rangetree_bit.test.cpp
    title: segmenttree/test/rangetree_bit.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"segmenttree/rangetree_bit.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n\n// CUT begin\n//\
    \ \u9818\u57DF\u6728\ntemplate <class S, void (*opadd)(S &, S), void (*opsub)(S\
    \ &, S), S (*e)(), class Coordinate>\nclass rangetree_bit {\n    int n;\n    std::vector<std::pair<Coordinate,\
    \ Coordinate>> _pts;\n    struct BIT {\n        std::vector<S> data;\n       \
    \ BIT(int len) : data(len, e()) {}\n        void add(int pos, S v) {\n       \
    \     for (pos++; pos and pos <= int(data.size()); pos += pos & -pos)\n      \
    \          opadd(data[pos - 1], v);\n        }\n        S sum(int r) const {\n\
    \            S ret = e();\n            while (r) opadd(ret, data[r - 1]), r -=\
    \ r & -r;\n            return ret;\n        }\n    };\n\n    std::vector<std::vector<Coordinate>>\
    \ _range2ys;\n    std::vector<BIT> bits;\n    void _add_singlenode(int v, Coordinate\
    \ y, S val) {\n        auto i = std::distance(\n            _range2ys[v].begin(),\
    \ std::lower_bound(_range2ys[v].begin(), _range2ys[v].end(), y));\n        bits[v].add(i,\
    \ val);\n    }\n    S _get_singlenode(int v, Coordinate y) const {\n        auto\
    \ i = std::distance(\n            _range2ys[v].begin(), std::lower_bound(_range2ys[v].begin(),\
    \ _range2ys[v].end(), y));\n        return bits[v].sum(i);\n    }\n    S _sum(Coordinate\
    \ xl, Coordinate xr, Coordinate yr) const { // [xl, xr) * (-INF, yr)\n       \
    \ auto compx = [](std::pair<Coordinate, Coordinate> l, std::pair<Coordinate, Coordinate>\
    \ r) {\n            return l.first < r.first;\n        };\n        int l = n +\
    \ std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(),\n   \
    \                                                              std::make_pair(xl,\
    \ yr), compx));\n        int r = n + std::distance(_pts.begin(), std::lower_bound(_pts.begin(),\
    \ _pts.end(),\n                                                              \
    \   std::make_pair(xr, yr), compx));\n        S ret = e();\n        while (l <\
    \ r) {\n            if (l & 1) opadd(ret, _get_singlenode(l++, yr));\n       \
    \     if (r & 1) opadd(ret, _get_singlenode(--r, yr));\n            l >>= 1, r\
    \ >>= 1;\n        }\n        return ret;\n    }\n\npublic:\n    rangetree_bit()\
    \ = default;\n    void add_point(Coordinate x, Coordinate y) noexcept { _pts.emplace_back(x,\
    \ y); }\n    void build() {\n        std::sort(_pts.begin(), _pts.end());\n  \
    \      _pts.erase(std::unique(_pts.begin(), _pts.end()), _pts.end());\n      \
    \  n = _pts.size();\n\n        _range2ys.resize(n * 2);\n        for (int i =\
    \ 0; i < n; i++) _range2ys[n + i] = {_pts[i].second};\n        for (int i = n\
    \ - 1; i > 0; i--) {\n            auto &lch = _range2ys[i * 2];\n            auto\
    \ &rch = _range2ys[i * 2 + 1];\n            std::merge(\n                lch.begin(),\
    \ lch.end(), rch.begin(), rch.end(), std::back_inserter(_range2ys[i]));\n    \
    \        _range2ys[i].erase(\n                std::unique(_range2ys[i].begin(),\
    \ _range2ys[i].end()), _range2ys[i].end());\n        }\n        for (const auto\
    \ &v : _range2ys) bits.push_back(BIT(v.size()));\n    }\n    void add(Coordinate\
    \ x, Coordinate y, S val) {\n        int i = std::distance(\n            _pts.begin(),\
    \ std::lower_bound(_pts.begin(), _pts.end(), std::make_pair(x, y)));\n       \
    \ assert(i < n and _pts[i] == std::make_pair(x, y));\n        for (i += n; i;\
    \ i >>= 1) _add_singlenode(i, y, val);\n    }\n    S sum(Coordinate xl, Coordinate\
    \ xr, Coordinate yl, Coordinate yr) const {\n        auto ret_r = _sum(xl, xr,\
    \ yr);\n        auto ret_l = _sum(xl, xr, yl);\n        opsub(ret_r, ret_l);\n\
    \        return ret_r;\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// \u9818\u57DF\u6728\ntemplate <class S, void\
    \ (*opadd)(S &, S), void (*opsub)(S &, S), S (*e)(), class Coordinate>\nclass\
    \ rangetree_bit {\n    int n;\n    std::vector<std::pair<Coordinate, Coordinate>>\
    \ _pts;\n    struct BIT {\n        std::vector<S> data;\n        BIT(int len)\
    \ : data(len, e()) {}\n        void add(int pos, S v) {\n            for (pos++;\
    \ pos and pos <= int(data.size()); pos += pos & -pos)\n                opadd(data[pos\
    \ - 1], v);\n        }\n        S sum(int r) const {\n            S ret = e();\n\
    \            while (r) opadd(ret, data[r - 1]), r -= r & -r;\n            return\
    \ ret;\n        }\n    };\n\n    std::vector<std::vector<Coordinate>> _range2ys;\n\
    \    std::vector<BIT> bits;\n    void _add_singlenode(int v, Coordinate y, S val)\
    \ {\n        auto i = std::distance(\n            _range2ys[v].begin(), std::lower_bound(_range2ys[v].begin(),\
    \ _range2ys[v].end(), y));\n        bits[v].add(i, val);\n    }\n    S _get_singlenode(int\
    \ v, Coordinate y) const {\n        auto i = std::distance(\n            _range2ys[v].begin(),\
    \ std::lower_bound(_range2ys[v].begin(), _range2ys[v].end(), y));\n        return\
    \ bits[v].sum(i);\n    }\n    S _sum(Coordinate xl, Coordinate xr, Coordinate\
    \ yr) const { // [xl, xr) * (-INF, yr)\n        auto compx = [](std::pair<Coordinate,\
    \ Coordinate> l, std::pair<Coordinate, Coordinate> r) {\n            return l.first\
    \ < r.first;\n        };\n        int l = n + std::distance(_pts.begin(), std::lower_bound(_pts.begin(),\
    \ _pts.end(),\n                                                              \
    \   std::make_pair(xl, yr), compx));\n        int r = n + std::distance(_pts.begin(),\
    \ std::lower_bound(_pts.begin(), _pts.end(),\n                               \
    \                                  std::make_pair(xr, yr), compx));\n        S\
    \ ret = e();\n        while (l < r) {\n            if (l & 1) opadd(ret, _get_singlenode(l++,\
    \ yr));\n            if (r & 1) opadd(ret, _get_singlenode(--r, yr));\n      \
    \      l >>= 1, r >>= 1;\n        }\n        return ret;\n    }\n\npublic:\n \
    \   rangetree_bit() = default;\n    void add_point(Coordinate x, Coordinate y)\
    \ noexcept { _pts.emplace_back(x, y); }\n    void build() {\n        std::sort(_pts.begin(),\
    \ _pts.end());\n        _pts.erase(std::unique(_pts.begin(), _pts.end()), _pts.end());\n\
    \        n = _pts.size();\n\n        _range2ys.resize(n * 2);\n        for (int\
    \ i = 0; i < n; i++) _range2ys[n + i] = {_pts[i].second};\n        for (int i\
    \ = n - 1; i > 0; i--) {\n            auto &lch = _range2ys[i * 2];\n        \
    \    auto &rch = _range2ys[i * 2 + 1];\n            std::merge(\n            \
    \    lch.begin(), lch.end(), rch.begin(), rch.end(), std::back_inserter(_range2ys[i]));\n\
    \            _range2ys[i].erase(\n                std::unique(_range2ys[i].begin(),\
    \ _range2ys[i].end()), _range2ys[i].end());\n        }\n        for (const auto\
    \ &v : _range2ys) bits.push_back(BIT(v.size()));\n    }\n    void add(Coordinate\
    \ x, Coordinate y, S val) {\n        int i = std::distance(\n            _pts.begin(),\
    \ std::lower_bound(_pts.begin(), _pts.end(), std::make_pair(x, y)));\n       \
    \ assert(i < n and _pts[i] == std::make_pair(x, y));\n        for (i += n; i;\
    \ i >>= 1) _add_singlenode(i, y, val);\n    }\n    S sum(Coordinate xl, Coordinate\
    \ xr, Coordinate yl, Coordinate yr) const {\n        auto ret_r = _sum(xl, xr,\
    \ yr);\n        auto ret_l = _sum(xl, xr, yl);\n        opsub(ret_r, ret_l);\n\
    \        return ret_r;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/rangetree_bit.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - segmenttree/test/rangetree_bit.test.cpp
documentation_of: segmenttree/rangetree_bit.hpp
layout: document
title: "Range Tree with binary indexed tree \uFF08\u9818\u57DF\u6728\uFF09"
---

二次元平面における以下のクエリをオンラインで効率的に処理．

- $(x, y)$ に重み $w$ を追加．
- 矩形領域 $\left[x_\mathrm{l}, x_\mathrm{r}\right) \times \left[y_\mathrm{l}, y_\mathrm{r}\right)$ の内側の重みの総和を回答．

ただし，重みを追加する候補となる点は予め列挙しておく必要がある．また，逆元が必要．モノイドを載せたい場合は `rangetree.hpp` を使用する．

## 使用方法

- `rangetree_bit<S, add, sub, e, Int>()` コンストラクタ．`S` は可換な群，`add(S&, S)`, `sub(S&, S)` は `S` 上の加減算，`e()` は `S` の零元を返す．`Int` は座標を表す数値の型．
- `void build()` 時間計算量，空間計算量とも $O(N \log N)$ （$N$ は候補点の個数）．
- `void add(Int x, Int y, S w)` 時間計算量 $O(N (\log N)^2)$．
- `S sum(Int xl, Int xr, Int yl, Int yr)` 時間計算量 $O(N (\log N)^2)$．

## 使用例

```cpp
using S = unsigned long long;
S e() noexcept { return 0; } // 単位元
void opadd(S &l, S r) noexcept { l += r; }
void opsub(S &l, S r) noexcept { l -= r; }

int main() {
    rangetree_bit<S, opadd, opsub, e, long long> tree;
    for (auto [x, y] : points) tree.add_point(x, y);
    tree.build();

    tree.add(x, y, w);

    cout << tree.sum(l, r, d, u) << '\n';
}
```

## 問題例

- [Library Checker: Point Add Rectangle Sum](https://judge.yosupo.jp/problem/point_add_rectangle_sum)
- [Codeforces Round #499 (Div. 1) E. Store](https://codeforces.com/contest/1010/problem/E)
