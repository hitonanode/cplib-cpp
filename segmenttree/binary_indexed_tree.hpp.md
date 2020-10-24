---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/binary_indexed_tree.test.cpp
    title: segmenttree/test/binary_indexed_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/point-add-range-sum.test.cpp
    title: segmenttree/test/point-add-range-sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"segmenttree/binary_indexed_tree.hpp\"\n#include <iostream>\n\
    #include <vector>\n\n// CUT begin\n// 1-indexed BIT (i : [1, len])\ntemplate <typename\
    \ T>\nstruct BIT : std::vector<T>\n{\n    BIT(int len = 0) : std::vector<T>(len\
    \ + 1) {}\n    void reset() { fill(this->begin(), this->end(), 0); }\n    void\
    \ add(int pos, T v) {\n        while (pos > 0 and pos < (int)this->size()) (*this)[pos]\
    \ += v, pos += pos & -pos;\n    }\n    T sum(int pos) const { // (0, pos]\n  \
    \      T res = 0;\n        while (pos > 0) res += (*this)[pos], pos -= pos & -pos;\n\
    \        return res;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const BIT &bit) {\n        T prv = 0;\n        os << '[';\n        for\
    \ (int i = 1; i < (int)bit.size(); i++) {\n            T now = bit.sum(i);\n \
    \           os << now - prv << \",\";\n            prv = now;\n        }\n   \
    \     os << ']';\n        return os;\n    }\n};\n"
  code: "#pragma once\n#include <iostream>\n#include <vector>\n\n// CUT begin\n//\
    \ 1-indexed BIT (i : [1, len])\ntemplate <typename T>\nstruct BIT : std::vector<T>\n\
    {\n    BIT(int len = 0) : std::vector<T>(len + 1) {}\n    void reset() { fill(this->begin(),\
    \ this->end(), 0); }\n    void add(int pos, T v) {\n        while (pos > 0 and\
    \ pos < (int)this->size()) (*this)[pos] += v, pos += pos & -pos;\n    }\n    T\
    \ sum(int pos) const { // (0, pos]\n        T res = 0;\n        while (pos > 0)\
    \ res += (*this)[pos], pos -= pos & -pos;\n        return res;\n    }\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const BIT &bit) {\n        T prv\
    \ = 0;\n        os << '[';\n        for (int i = 1; i < (int)bit.size(); i++)\
    \ {\n            T now = bit.sum(i);\n            os << now - prv << \",\";\n\
    \            prv = now;\n        }\n        os << ']';\n        return os;\n \
    \   }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/binary_indexed_tree.hpp
  requiredBy: []
  timestamp: '2020-04-19 16:23:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/point-add-range-sum.test.cpp
  - segmenttree/test/binary_indexed_tree.test.cpp
documentation_of: segmenttree/binary_indexed_tree.hpp
layout: document
redirect_from:
- /library/segmenttree/binary_indexed_tree.hpp
- /library/segmenttree/binary_indexed_tree.hpp.html
title: segmenttree/binary_indexed_tree.hpp
---
