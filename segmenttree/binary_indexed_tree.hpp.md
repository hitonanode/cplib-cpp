---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/range_kth_smallest_offline.hpp
    title: data_structure/range_kth_smallest_offline.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/rectangle_sum.hpp
    title: data_structure/rectangle_sum.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/range_kth_smallest_offline.test.cpp
    title: data_structure/test/range_kth_smallest_offline.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/rectange_sum.test.cpp
    title: data_structure/test/rectange_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/binary_indexed_tree.test.cpp
    title: segmenttree/test/binary_indexed_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/point-add-range-sum.test.cpp
    title: segmenttree/test/point-add-range-sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"segmenttree/binary_indexed_tree.hpp\"\n#include <algorithm>\n\
    #include <iostream>\n#include <vector>\n\n// CUT begin\n// 0-indexed BIT (binary\
    \ indexed tree / Fenwick tree) (i : [0, len))\ntemplate <typename T> struct BIT\
    \ {\n    int n;\n    std::vector<T> data;\n    BIT(int len = 0) : n(len), data(len)\
    \ {}\n    void reset() { std::fill(data.begin(), data.end(), T(0)); }\n    void\
    \ add(int pos, T v) { // a[pos] += v\n        pos++;\n        while (pos > 0 and\
    \ pos <= n) data[pos - 1] += v, pos += pos & -pos;\n    }\n    T sum(int k) const\
    \ { // a[0] + ... + a[k - 1]\n        T res = 0;\n        while (k > 0) res +=\
    \ data[k - 1], k -= k & -k;\n        return res;\n    }\n\n    T sum(int l, int\
    \ r) const { return sum(r) - sum(l); } // a[l] + ... + a[r - 1]\n\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const BIT &bit) {\n        T prv\
    \ = 0;\n        os << '[';\n        for (int i = 1; i <= bit.n; i++) {\n     \
    \       T now = bit.sum(i);\n            os << now - prv << ',', prv = now;\n\
    \        }\n        return os << ']';\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <iostream>\n#include <vector>\n\
    \n// CUT begin\n// 0-indexed BIT (binary indexed tree / Fenwick tree) (i : [0,\
    \ len))\ntemplate <typename T> struct BIT {\n    int n;\n    std::vector<T> data;\n\
    \    BIT(int len = 0) : n(len), data(len) {}\n    void reset() { std::fill(data.begin(),\
    \ data.end(), T(0)); }\n    void add(int pos, T v) { // a[pos] += v\n        pos++;\n\
    \        while (pos > 0 and pos <= n) data[pos - 1] += v, pos += pos & -pos;\n\
    \    }\n    T sum(int k) const { // a[0] + ... + a[k - 1]\n        T res = 0;\n\
    \        while (k > 0) res += data[k - 1], k -= k & -k;\n        return res;\n\
    \    }\n\n    T sum(int l, int r) const { return sum(r) - sum(l); } // a[l] +\
    \ ... + a[r - 1]\n\n    friend std::ostream &operator<<(std::ostream &os, const\
    \ BIT &bit) {\n        T prv = 0;\n        os << '[';\n        for (int i = 1;\
    \ i <= bit.n; i++) {\n            T now = bit.sum(i);\n            os << now -\
    \ prv << ',', prv = now;\n        }\n        return os << ']';\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/binary_indexed_tree.hpp
  requiredBy:
  - data_structure/rectangle_sum.hpp
  - data_structure/range_kth_smallest_offline.hpp
  timestamp: '2020-12-29 19:26:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/binary_indexed_tree.test.cpp
  - segmenttree/test/point-add-range-sum.test.cpp
  - data_structure/test/range_kth_smallest_offline.test.cpp
  - data_structure/test/rectange_sum.test.cpp
documentation_of: segmenttree/binary_indexed_tree.hpp
layout: document
redirect_from:
- /library/segmenttree/binary_indexed_tree.hpp
- /library/segmenttree/binary_indexed_tree.hpp.html
title: segmenttree/binary_indexed_tree.hpp
---
