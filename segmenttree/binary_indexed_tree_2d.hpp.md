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
  bundledCode: "#line 2 \"segmenttree/binary_indexed_tree_2d.hpp\"\n#include <array>\n\
    \n// 2-dimensional 1-indexed BIT (i : [1, lenX][1, lenY])\ntemplate <typename\
    \ T, int lenX, int lenY> struct BIT_2D {\n    std::array<T, (lenX + 1) * (lenY\
    \ + 1)> val;\n    constexpr static int M = lenY + 1;\n    BIT_2D() {}\n    void\
    \ add(int posx, int posy, T v) noexcept {\n        for (int x = posx; x <= lenX;\
    \ x += x & -x) {\n            for (int y = posy; y <= lenY; y += y & -y) val[x\
    \ * M + y] += v;\n        }\n    }\n    // [1, posx] * [1, posy] \u306E\u548C\n\
    \    T sum(int posx, int posy) const noexcept {\n        T res = 0;\n        for\
    \ (int x = posx; x > 0; x -= x & -x) {\n            for (int y = posy; y > 0;\
    \ y -= y & -y) { res += val[x * M + y]; }\n        }\n        return res;\n  \
    \  }\n    // [xmin, xmax] * [ymin, ymax] \u306E\u548C\uFF08\u9589\u533A\u9593\uFF09\
    \n    T sum(int xmin, int xmax, int ymin, int ymax) const noexcept {\n       \
    \ return sum(xmax, ymax) - sum(xmin - 1, ymax) - sum(xmax, ymin - 1) + sum(xmin\
    \ - 1, ymin - 1);\n    }\n};\n"
  code: "#pragma once\n#include <array>\n\n// 2-dimensional 1-indexed BIT (i : [1,\
    \ lenX][1, lenY])\ntemplate <typename T, int lenX, int lenY> struct BIT_2D {\n\
    \    std::array<T, (lenX + 1) * (lenY + 1)> val;\n    constexpr static int M =\
    \ lenY + 1;\n    BIT_2D() {}\n    void add(int posx, int posy, T v) noexcept {\n\
    \        for (int x = posx; x <= lenX; x += x & -x) {\n            for (int y\
    \ = posy; y <= lenY; y += y & -y) val[x * M + y] += v;\n        }\n    }\n   \
    \ // [1, posx] * [1, posy] \u306E\u548C\n    T sum(int posx, int posy) const noexcept\
    \ {\n        T res = 0;\n        for (int x = posx; x > 0; x -= x & -x) {\n  \
    \          for (int y = posy; y > 0; y -= y & -y) { res += val[x * M + y]; }\n\
    \        }\n        return res;\n    }\n    // [xmin, xmax] * [ymin, ymax] \u306E\
    \u548C\uFF08\u9589\u533A\u9593\uFF09\n    T sum(int xmin, int xmax, int ymin,\
    \ int ymax) const noexcept {\n        return sum(xmax, ymax) - sum(xmin - 1, ymax)\
    \ - sum(xmax, ymin - 1) + sum(xmin - 1, ymin - 1);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/binary_indexed_tree_2d.hpp
  requiredBy: []
  timestamp: '2025-08-24 23:32:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: segmenttree/binary_indexed_tree_2d.hpp
layout: document
redirect_from:
- /library/segmenttree/binary_indexed_tree_2d.hpp
- /library/segmenttree/binary_indexed_tree_2d.hpp.html
title: segmenttree/binary_indexed_tree_2d.hpp
---
