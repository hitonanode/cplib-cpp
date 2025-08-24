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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ segmenttree/acl_lazysegtree.hpp: line 37: found codes out of include guard\n"
  code: "#pragma once\n#include <algorithm>\n#include <vector>\n\n#include \"segmenttree/acl_lazysegtree.hpp\"\
    \n\ntemplate <class T> class AreaOfUnionOfRectangles {\n    struct Rectangle {\n\
    \        T xl, xr, yl, yr;\n    };\n    std::vector<Rectangle> rectangles;\n\n\
    \    struct S {\n        int min = 1 << 30;\n        T width = T{};\n        T\
    \ min_width = T{};\n        T nonzero_width() const { return width - (min == 0)\
    \ * min_width; }\n    };\n    static S op(S l, S r) {\n        T min_width = (l.min\
    \ <= r.min) * l.min_width + (l.min >= r.min) * r.min_width;\n        return {std::min(l.min,\
    \ r.min), l.width + r.width, min_width};\n    }\n    static S e() { return S{};\
    \ }\n    using F = int;\n    static S mapping(F f, S x) { return {x.min + f, x.width,\
    \ x.min_width}; }\n    static F composition(F f, F g) { return f + g; }\n    static\
    \ F id() { return 0; }\n\npublic:\n    void add_rectangle(T xl, T xr, T yl, T\
    \ yr) { rectangles.push_back(Rectangle{xl, xr, yl, yr}); }\n\n    T solve() const\
    \ {\n        std::vector<T> xs;\n        xs.reserve(rectangles.size() * 2);\n\
    \        for (auto r : rectangles) xs.push_back(r.xl), xs.push_back(r.xr);\n \
    \       std::sort(xs.begin(), xs.end());\n        xs.erase(std::unique(xs.begin(),\
    \ xs.end()), xs.end());\n\n        if (xs.size() <= 1) return T{};\n\n       \
    \ auto seg = [&]() {\n            std::vector<S> inits;\n            inits.reserve((int)xs.size()\
    \ - 1);\n            for (int i = 0; i < (int)xs.size() - 1; ++i) {\n        \
    \        inits.emplace_back(S{0, xs[i + 1] - xs[i], xs[i + 1] - xs[i]});\n   \
    \         }\n            return atcoder::lazy_segtree<S, op, e, F, mapping, composition,\
    \ id>{inits};\n        }();\n\n        std::vector<std::tuple<T, int, int, bool>>\
    \ updates;\n        updates.reserve(rectangles.size() * 2);\n        for (auto\
    \ r : rectangles) {\n            const int ixl = std::lower_bound(xs.begin(),\
    \ xs.end(), r.xl) - xs.begin();\n            const int ixr = std::lower_bound(xs.begin(),\
    \ xs.end(), r.xr) - xs.begin();\n            updates.emplace_back(r.yl, ixl, ixr,\
    \ true);\n            updates.emplace_back(r.yr, ixl, ixr, false);\n        }\n\
    \n        std::sort(updates.begin(), updates.end());\n        T current_y = std::get<0>(updates.front());\n\
    \        T res{0};\n        for (auto [y, il, ir, tp] : updates) {\n         \
    \   if (y != current_y) {\n                res += (y - current_y) * seg.all_prod().nonzero_width();\n\
    \                current_y = y;\n            }\n            seg.apply(il, ir,\
    \ tp ? 1 : -1);\n        }\n\n        return res;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/area_of_union_of_rectangles.hpp
  requiredBy: []
  timestamp: '2025-08-11 22:47:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/area_of_union_of_rectangles.hpp
layout: document
title: "Area of union of rectangles \uFF082 \u6B21\u5143\u5E73\u9762\u4E0A\u306E\u9577\
  \u65B9\u5F62\u305F\u3061\u304C\u8986\u3046\u9762\u7A4D\uFF09"
---

与えられた 2 次元平面上の各辺が $x$ 軸や $y$ 軸に平行な $n$ 個の長方形たちに対して，これらの和集合の面積を $O(n \log n)$ で計算する．

## 使用方法

```cpp
AreaOfUnionOfRectangles<long long> aur;

long long xl, xr, yl, yr;
aur.add_rectangle(xl, xr, yl, yr);

cout << aur.solve() << '\n';
```

## 問題例

- [Library Checker: Area of Union of Rectangles](https://judge.yosupo.jp/problem/area_of_union_of_rectangles)
