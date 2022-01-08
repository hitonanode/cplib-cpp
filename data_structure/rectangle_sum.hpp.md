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
    path: data_structure/test/rectange_sum.test.cpp
    title: data_structure/test/rectange_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/submission/40312
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
    \    }\n};\n#line 4 \"data_structure/rectangle_sum.hpp\"\n#include <tuple>\n#line\
    \ 6 \"data_structure/rectangle_sum.hpp\"\n\n// CUT begin\n// Rectangle Sum: calculate\
    \ sum of weights inside rectangles\n// Sample: https://judge.yosupo.jp/submission/40312\
    \ (2e5 points, 2e5 rectangles, 566 ms)\n// `add_point(x, y, weight)`: Add point\
    \ at (x, y)\n// `add_query(L, R, D, U)`: Add query rectangle [L, R) x [D, U)\n\
    template <typename Int, typename Weight> struct RectangleSum {\n    RectangleSum()\
    \ = default;\n    struct Rectangle {\n        Int L, R, D, U;\n    };\n    std::vector<Rectangle>\
    \ queries;\n    std::vector<std::tuple<Int, Int, Weight>> points;\n\n    void\
    \ add_point(Int x, Int y, Weight weight) noexcept {\n        points.push_back({x\
    \ + 1, y + 1, weight});\n    }\n    void add_query(Int L, Int R, Int D, Int U)\
    \ noexcept { queries.push_back({L, R, D, U}); }\n\n    std::vector<Weight> solve()\
    \ const {\n        std::vector<Int> xs, ys;\n        for (auto rect : queries)\
    \ {\n            xs.push_back(rect.L);\n            xs.push_back(rect.R);\n  \
    \          ys.push_back(rect.D);\n            ys.push_back(rect.U);\n        }\n\
    \n        std::sort(xs.begin(), xs.end());\n        std::sort(ys.begin(), ys.end());\n\
    \        xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n        ys.erase(std::unique(ys.begin(),\
    \ ys.end()), ys.end());\n\n        std::vector<std::vector<std::tuple<int, int,\
    \ Weight>>> ops(ys.size()); // q, x, weight\n        for (auto p : points) {\n\
    \            int i = std::lower_bound(xs.begin(), xs.end(), std::get<0>(p)) -\
    \ xs.begin();\n            int j = std::lower_bound(ys.begin(), ys.end(), std::get<1>(p))\
    \ - ys.begin();\n            if (j < int(ops.size())) ops[j].push_back({-1, i,\
    \ std::get<2>(p)});\n        }\n\n        for (int q = 0; q < int(queries.size());\
    \ q++) {\n            int il = std::lower_bound(xs.begin(), xs.end(), queries[q].L)\
    \ - xs.begin();\n            int ir = std::lower_bound(xs.begin(), xs.end(), queries[q].R)\
    \ - xs.begin();\n            int jd = std::lower_bound(ys.begin(), ys.end(), queries[q].D)\
    \ - ys.begin();\n            int ju = std::lower_bound(ys.begin(), ys.end(), queries[q].U)\
    \ - ys.begin();\n            ops[jd].push_back({q, il, 1});\n            ops[jd].push_back({q,\
    \ ir, -1});\n            ops[ju].push_back({q, il, -1});\n            ops[ju].push_back({q,\
    \ ir, 1});\n        }\n\n        std::vector<Weight> ret(queries.size());\n  \
    \      BIT<Weight> bit(xs.size());\n        for (auto &&op : ops) {\n        \
    \    for (auto p : op) {\n                const auto q = std::get<0>(p), x = std::get<1>(p);\n\
    \                const auto w = std::get<2>(p);\n                if (q == -1)\
    \ {\n                    bit.add(x, w);\n                } else {\n          \
    \          ret[q] += bit.sum(x + 1) * w;\n                }\n            }\n \
    \       }\n        return ret;\n    }\n};\n"
  code: "#pragma once\n#include \"../segmenttree/binary_indexed_tree.hpp\"\n#include\
    \ <algorithm>\n#include <tuple>\n#include <vector>\n\n// CUT begin\n// Rectangle\
    \ Sum: calculate sum of weights inside rectangles\n// Sample: https://judge.yosupo.jp/submission/40312\
    \ (2e5 points, 2e5 rectangles, 566 ms)\n// `add_point(x, y, weight)`: Add point\
    \ at (x, y)\n// `add_query(L, R, D, U)`: Add query rectangle [L, R) x [D, U)\n\
    template <typename Int, typename Weight> struct RectangleSum {\n    RectangleSum()\
    \ = default;\n    struct Rectangle {\n        Int L, R, D, U;\n    };\n    std::vector<Rectangle>\
    \ queries;\n    std::vector<std::tuple<Int, Int, Weight>> points;\n\n    void\
    \ add_point(Int x, Int y, Weight weight) noexcept {\n        points.push_back({x\
    \ + 1, y + 1, weight});\n    }\n    void add_query(Int L, Int R, Int D, Int U)\
    \ noexcept { queries.push_back({L, R, D, U}); }\n\n    std::vector<Weight> solve()\
    \ const {\n        std::vector<Int> xs, ys;\n        for (auto rect : queries)\
    \ {\n            xs.push_back(rect.L);\n            xs.push_back(rect.R);\n  \
    \          ys.push_back(rect.D);\n            ys.push_back(rect.U);\n        }\n\
    \n        std::sort(xs.begin(), xs.end());\n        std::sort(ys.begin(), ys.end());\n\
    \        xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n        ys.erase(std::unique(ys.begin(),\
    \ ys.end()), ys.end());\n\n        std::vector<std::vector<std::tuple<int, int,\
    \ Weight>>> ops(ys.size()); // q, x, weight\n        for (auto p : points) {\n\
    \            int i = std::lower_bound(xs.begin(), xs.end(), std::get<0>(p)) -\
    \ xs.begin();\n            int j = std::lower_bound(ys.begin(), ys.end(), std::get<1>(p))\
    \ - ys.begin();\n            if (j < int(ops.size())) ops[j].push_back({-1, i,\
    \ std::get<2>(p)});\n        }\n\n        for (int q = 0; q < int(queries.size());\
    \ q++) {\n            int il = std::lower_bound(xs.begin(), xs.end(), queries[q].L)\
    \ - xs.begin();\n            int ir = std::lower_bound(xs.begin(), xs.end(), queries[q].R)\
    \ - xs.begin();\n            int jd = std::lower_bound(ys.begin(), ys.end(), queries[q].D)\
    \ - ys.begin();\n            int ju = std::lower_bound(ys.begin(), ys.end(), queries[q].U)\
    \ - ys.begin();\n            ops[jd].push_back({q, il, 1});\n            ops[jd].push_back({q,\
    \ ir, -1});\n            ops[ju].push_back({q, il, -1});\n            ops[ju].push_back({q,\
    \ ir, 1});\n        }\n\n        std::vector<Weight> ret(queries.size());\n  \
    \      BIT<Weight> bit(xs.size());\n        for (auto &&op : ops) {\n        \
    \    for (auto p : op) {\n                const auto q = std::get<0>(p), x = std::get<1>(p);\n\
    \                const auto w = std::get<2>(p);\n                if (q == -1)\
    \ {\n                    bit.add(x, w);\n                } else {\n          \
    \          ret[q] += bit.sum(x + 1) * w;\n                }\n            }\n \
    \       }\n        return ret;\n    }\n};\n"
  dependsOn:
  - segmenttree/binary_indexed_tree.hpp
  isVerificationFile: false
  path: data_structure/rectangle_sum.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/rectange_sum.test.cpp
documentation_of: data_structure/rectangle_sum.hpp
layout: document
redirect_from:
- /library/data_structure/rectangle_sum.hpp
- /library/data_structure/rectangle_sum.hpp.html
title: data_structure/rectangle_sum.hpp
---
