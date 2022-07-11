---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: tree/test/tree_isomorphism.aoj1613.test.cpp
    title: tree/test/tree_isomorphism.aoj1613.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"unionfind/grid_unionfind.hpp\"\n#include <cassert>\n#include\
    \ <iomanip>\n#include <numeric>\n#include <utility>\n#include <vector>\n\n// CUT\
    \ begin\nstruct GridUnionFind {\n    int H, W;\n    std::vector<int> par, cou;\n\
    \    using P = std::pair<int, int>;\n    GridUnionFind(int H_, int W_) : H(H_),\
    \ W(W_), par(H * W), cou(H * W, 1) {\n        std::iota(par.begin(), par.end(),\
    \ 0);\n    }\n    inline int id_(int h, int w) { return h * W + w; }\n    inline\
    \ bool coordinate_valid(int h, int w) { return h >= 0 and h < H and w >= 0 and\
    \ w < W; }\n    int _find(int x) { return (par[x] == x) ? x : (par[x] = _find(par[x]));\
    \ }\n    bool _unite(int x, int y) {\n        x = _find(x), y = _find(y);\n  \
    \      if (x == y) return false;\n        if (cou[x] < cou[y]) std::swap(x, y);\n\
    \        par[y] = x, cou[x] += cou[y];\n        return true;\n    }\n    int find(int\
    \ h, int w) {\n        assert(coordinate_valid(h, w));\n        return _find(id_(h,\
    \ w));\n    }\n    bool unite(int h, int w, int h2, int w2) {\n        assert(coordinate_valid(h,\
    \ w) and coordinate_valid(h2, w2));\n        return _unite(id_(h, w), id_(h2,\
    \ w2));\n    }\n    int count(int h, int w) { return cou[find(h, w)]; }\n    bool\
    \ same(int h, int w, int h2, int w2) { return find(h, w) == find(h2, w2); }\n\n\
    \    int find(P p) { return find(p.first, p.second); }\n    bool unite(P p, P\
    \ p2) { return unite(p.first, p.second, p2.first, p2.second); }\n    int count(P\
    \ p) { return count(p.first, p.second); }\n    bool same(P p, P p2) { return same(p.first,\
    \ p.second, p2.first, p2.second); }\n\n    void merge_outer() {\n        for (int\
    \ h = 0; h < H - 1; h++) unite(h, 0, h + 1, 0), unite(h, W - 1, h + 1, W - 1);\n\
    \        for (int w = 0; w < W - 1; w++) unite(0, w, 0, w + 1), unite(H - 1, w,\
    \ H - 1, w + 1);\n    }\n    template <typename OStream> friend OStream &operator<<(OStream\
    \ &os, GridUnionFind &g) {\n        constexpr int WW = 3;\n        os << \"[(\"\
    \ << g.H << \" * \" << g.W << \" grid)\\n\";\n        for (int i = 0; i < g.H;\
    \ i++) {\n            for (int j = 0; j < g.W - 1; j++) {\n                os\
    \ << std::setw(WW) << g.find(i, j) << (g.same(i, j, i, j + 1) ? '-' : ' ');\n\
    \            }\n            os << std::setw(WW) << g.find(i, g.W - 1) << '\\n';\n\
    \            if (i < g.H - 1) {\n                for (int j = 0; j < g.W; j++)\n\
    \                    os << std::setw(WW + 1) << (g.same(i, j, i + 1, j) ? \"|\
    \ \" : \"  \");\n                os << \"\\n\";\n            }\n        }\n  \
    \      os << \"]\\n\";\n        return os;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <iomanip>\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\nstruct GridUnionFind {\n\
    \    int H, W;\n    std::vector<int> par, cou;\n    using P = std::pair<int, int>;\n\
    \    GridUnionFind(int H_, int W_) : H(H_), W(W_), par(H * W), cou(H * W, 1) {\n\
    \        std::iota(par.begin(), par.end(), 0);\n    }\n    inline int id_(int\
    \ h, int w) { return h * W + w; }\n    inline bool coordinate_valid(int h, int\
    \ w) { return h >= 0 and h < H and w >= 0 and w < W; }\n    int _find(int x) {\
    \ return (par[x] == x) ? x : (par[x] = _find(par[x])); }\n    bool _unite(int\
    \ x, int y) {\n        x = _find(x), y = _find(y);\n        if (x == y) return\
    \ false;\n        if (cou[x] < cou[y]) std::swap(x, y);\n        par[y] = x, cou[x]\
    \ += cou[y];\n        return true;\n    }\n    int find(int h, int w) {\n    \
    \    assert(coordinate_valid(h, w));\n        return _find(id_(h, w));\n    }\n\
    \    bool unite(int h, int w, int h2, int w2) {\n        assert(coordinate_valid(h,\
    \ w) and coordinate_valid(h2, w2));\n        return _unite(id_(h, w), id_(h2,\
    \ w2));\n    }\n    int count(int h, int w) { return cou[find(h, w)]; }\n    bool\
    \ same(int h, int w, int h2, int w2) { return find(h, w) == find(h2, w2); }\n\n\
    \    int find(P p) { return find(p.first, p.second); }\n    bool unite(P p, P\
    \ p2) { return unite(p.first, p.second, p2.first, p2.second); }\n    int count(P\
    \ p) { return count(p.first, p.second); }\n    bool same(P p, P p2) { return same(p.first,\
    \ p.second, p2.first, p2.second); }\n\n    void merge_outer() {\n        for (int\
    \ h = 0; h < H - 1; h++) unite(h, 0, h + 1, 0), unite(h, W - 1, h + 1, W - 1);\n\
    \        for (int w = 0; w < W - 1; w++) unite(0, w, 0, w + 1), unite(H - 1, w,\
    \ H - 1, w + 1);\n    }\n    template <typename OStream> friend OStream &operator<<(OStream\
    \ &os, GridUnionFind &g) {\n        constexpr int WW = 3;\n        os << \"[(\"\
    \ << g.H << \" * \" << g.W << \" grid)\\n\";\n        for (int i = 0; i < g.H;\
    \ i++) {\n            for (int j = 0; j < g.W - 1; j++) {\n                os\
    \ << std::setw(WW) << g.find(i, j) << (g.same(i, j, i, j + 1) ? '-' : ' ');\n\
    \            }\n            os << std::setw(WW) << g.find(i, g.W - 1) << '\\n';\n\
    \            if (i < g.H - 1) {\n                for (int j = 0; j < g.W; j++)\n\
    \                    os << std::setw(WW + 1) << (g.same(i, j, i + 1, j) ? \"|\
    \ \" : \"  \");\n                os << \"\\n\";\n            }\n        }\n  \
    \      os << \"]\\n\";\n        return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: unionfind/grid_unionfind.hpp
  requiredBy: []
  timestamp: '2021-07-30 01:44:42+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - tree/test/tree_isomorphism.aoj1613.test.cpp
documentation_of: unionfind/grid_unionfind.hpp
layout: document
redirect_from:
- /library/unionfind/grid_unionfind.hpp
- /library/unionfind/grid_unionfind.hpp.html
title: unionfind/grid_unionfind.hpp
---
