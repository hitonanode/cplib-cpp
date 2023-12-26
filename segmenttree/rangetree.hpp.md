---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/acl_segtree.hpp
    title: segmenttree/acl_segtree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/rangetree.test.cpp
    title: segmenttree/test/rangetree.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/rangetree.yuki1625.test.cpp
    title: segmenttree/test/rangetree.yuki1625.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.12.1/x64/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.1/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.12.1/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.1/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_segtree.hpp: line 37: found codes out of include guard\n"
  code: "#pragma once\n#include \"acl_segtree.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <utility>\n#include <vector>\n\n// CUT begin\n// \u9006\u5143\
    \u3092\u8981\u6C42\u3057\u306A\u3044\u9818\u57DF\u6728\ntemplate <class S, S (*op)(S,\
    \ S), S (*e)(), class Coordinate> class rangetree {\n    int n;\n    using Pt\
    \ = std::pair<Coordinate, Coordinate>;\n    std::vector<Pt> _pts;\n    std::vector<std::vector<Pt>>\
    \ _range2yxs;\n    std::vector<atcoder::segtree<S, op, e>> segtrees;\n    void\
    \ _set(int v, Pt p, S val) {\n        auto i = std::distance(\n            _range2yxs[v].begin(),\n\
    \            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{p.second,\
    \ p.first}));\n        segtrees[v].set(i, val);\n    }\n    void _add(int v, Pt\
    \ p, S val) {\n        auto i = std::distance(\n            _range2yxs[v].begin(),\n\
    \            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{p.second,\
    \ p.first}));\n        segtrees[v].set(i, op(segtrees[v].get(i), val));\n    }\n\
    \    S _prod(int v, Coordinate yl, Coordinate yr) const {\n        auto comp =\
    \ [&](const Pt &l, const Pt &r) { return l.first < r.first; };\n        auto il\
    \ = std::distance(\n            _range2yxs[v].begin(),\n            std::lower_bound(_range2yxs[v].begin(),\
    \ _range2yxs[v].end(), Pt{yl, yl}, comp));\n        auto ir = std::distance(\n\
    \            _range2yxs[v].begin(),\n            std::lower_bound(_range2yxs[v].begin(),\
    \ _range2yxs[v].end(), Pt{yr, yr}, comp));\n        return segtrees[v].prod(il,\
    \ ir);\n    }\n\npublic:\n    rangetree() = default;\n    void add_point(Coordinate\
    \ x, Coordinate y) noexcept { _pts.emplace_back(x, y); }\n    void build() {\n\
    \        std::sort(_pts.begin(), _pts.end());\n        _pts.erase(std::unique(_pts.begin(),\
    \ _pts.end()), _pts.end());\n        n = _pts.size();\n\n        _range2yxs.resize(n\
    \ * 2);\n        for (int i = 0; i < n; i++) _range2yxs[n + i] = {{_pts[i].second,\
    \ _pts[i].first}};\n        for (int i = n - 1; i > 0; i--) {\n            auto\
    \ &lch = _range2yxs[i * 2];\n            auto &rch = _range2yxs[i * 2 + 1];\n\
    \            std::merge(\n                lch.begin(), lch.end(), rch.begin(),\
    \ rch.end(), std::back_inserter(_range2yxs[i]));\n            _range2yxs[i].erase(\n\
    \                std::unique(_range2yxs[i].begin(), _range2yxs[i].end()), _range2yxs[i].end());\n\
    \        }\n        for (const auto &v : _range2yxs) segtrees.emplace_back(v.size());\n\
    \    }\n    void set(Coordinate x, Coordinate y, S val) {\n        int i = std::distance(_pts.begin(),\
    \ std::lower_bound(_pts.begin(), _pts.end(), Pt{x, y}));\n        assert(i < n\
    \ and _pts[i] == std::make_pair(x, y));\n        for (i += n; i; i >>= 1) _set(i,\
    \ {x, y}, val);\n    }\n    void add(Coordinate x, Coordinate y, S val) {\n  \
    \      int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(),\
    \ Pt{x, y}));\n        assert(i < n and _pts[i] == std::make_pair(x, y));\n  \
    \      for (i += n; i; i >>= 1) _add(i, {x, y}, val);\n    }\n    S prod(Coordinate\
    \ xl, Coordinate xr, Coordinate yl, Coordinate yr) const {\n        auto comp\
    \ = [](const Pt &l, const Pt &r) { return l.first < r.first; };\n        int l\
    \ = n + std::distance(_pts.begin(),\n                                  std::lower_bound(_pts.begin(),\
    \ _pts.end(), Pt{xl, yr}, comp));\n        int r = n + std::distance(_pts.begin(),\n\
    \                                  std::lower_bound(_pts.begin(), _pts.end(),\
    \ Pt{xr, yr}, comp));\n        S ret = e();\n        while (l < r) {\n       \
    \     if (l & 1) ret = op(ret, _prod(l++, yl, yr));\n            if (r & 1) ret\
    \ = op(ret, _prod(--r, yl, yr));\n            l >>= 1, r >>= 1;\n        }\n \
    \       return ret;\n    }\n    S get(Coordinate x, Coordinate y) const { return\
    \ prod(x, x + 1, y, y + 1); }\n};\n"
  dependsOn:
  - segmenttree/acl_segtree.hpp
  isVerificationFile: false
  path: segmenttree/rangetree.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/rangetree.yuki1625.test.cpp
  - segmenttree/test/rangetree.test.cpp
documentation_of: segmenttree/rangetree.hpp
layout: document
title: "Range Tree \uFF08\u9818\u57DF\u6728\uFF09"
---

二次元平面における以下のクエリをオンラインで効率的に処理．

- $(x, y)$ に値 $v$ を加算．
- $(x, y)$ の値を $v$ に更新．
- 矩形領域 $\left[x_\mathrm{l}, x_\mathrm{r}\right) \times \left[y_\mathrm{l}, y_\mathrm{r}\right)$ の内側の値の総和を回答．

ただし，重みを追加する候補となる点は予め列挙しておく必要がある．値 $v$ たちは可換でなければならない（逆元は不要）．

## 使用方法

- `rangetree<S, op, e, Int>()` コンストラクタ．`S` は可換な群，`S op(S, S)`, は `S` 上の可換な演算，`e()` は `S` の零元を返す．`Int` は座標を表す数値の型．
- `void build()` 時間計算量，空間計算量とも $O(N \log N)$ （$N$ は候補点の個数）．
- `void add(Int x, Int y, S w)`, `void set(Int x, Int y, S w)` 時間計算量 $O(N (\log N)^2)$．
- `S prod(Int xl, Int xr, Int yl, Int yr)` 時間計算量 $O(N (\log N)^2)$．

## 使用例

```cpp
using S = unsigned long long;
S e() noexcept { return 0; } // 単位元
S op(S l, S r) noexcept { return l + r; }

int main() {
    rangetree<S, op, e, long long> tree;
    for (auto [x, y] : points) tree.add_point(x, y);
    tree.build();

    tree.add(x, y, w);

    cout << tree.sum(l, r, d, u) << '\n';
}
```

## 問題例

- [技術室奥プログラミングコンテスト#6 Day1 N - Jump and Walk](https://atcoder.jp/contests/tkppc6-1/tasks/tkppc6_1_n)
- [Library Checker: Point Add Rectangle Sum](https://judge.yosupo.jp/problem/point_add_rectangle_sum)
- [Codeforces Round #499 (Div. 1) E. Store](https://codeforces.com/contest/1010/problem/E)
