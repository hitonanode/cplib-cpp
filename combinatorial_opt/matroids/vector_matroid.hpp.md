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
  bundledCode: "#line 2 \"combinatorial_opt/matroids/vector_matroid.hpp\"\n#include\
    \ <bitset>\n#include <vector>\n\n// CUT begin\n// Vector matroid on F2 : linearly\
    \ independent vectors\n// VDIM: max. dimension of vector space\n// Verified: SRM526.5\
    \ 1000 (Used only for linear independence check)\ntemplate <int VDIM> class F2VectorMatroid\
    \ {\n    using Element = int;\n    static void chxormin(std::bitset<VDIM> &l,\
    \ const std::bitset<VDIM> &r) {\n        int i = r._Find_first();\n        if\
    \ (i < VDIM and l[i]) l ^= r;\n    }\n    std::vector<std::bitset<VDIM>> mat;\n\
    \    std::vector<Element> Iset;\n    std::vector<std::vector<std::bitset<VDIM>>>\
    \ bs;\n\npublic:\n    F2VectorMatroid() = default;\n    F2VectorMatroid(const\
    \ std::vector<std::bitset<VDIM>> &bitmat) : mat(bitmat) {}\n\n    int size() const\
    \ { return mat.size(); }\n\n    template <class State> void set(const State &I)\
    \ {\n        Iset.clear();\n        for (int e = 0; e < size(); e++) {\n     \
    \       if (I[e]) Iset.push_back(e);\n        }\n        bs.assign(Iset.size()\
    \ + 1, {});\n        for (int i = 0; i < int(Iset.size()); i++) {\n          \
    \  for (int j = i; j < int(Iset.size()); j++) {\n                auto v = mat[Iset[j]];\n\
    \                for (auto b : bs[i]) chxormin(v, b);\n                bs[i].push_back(v);\n\
    \            }\n        }\n    }\n    std::vector<Element> circuit(const Element\
    \ &e) const {\n        std::bitset<VDIM> v = mat[e];\n        for (auto b : bs[0])\
    \ chxormin(v, b);\n        if (v.any()) return {}; // I + {e} is independent\n\
    \n        std::vector<Element> ret{e};\n        v = mat[e];\n        for (int\
    \ i = 0; i < int(Iset.size()); i++) {\n            std::bitset<VDIM> w = v;\n\
    \            for (auto b : bs[i + 1]) chxormin(w, b);\n            if (w.any())\
    \ ret.push_back(Iset[i]);\n            chxormin(v, bs[0][i]);\n        }\n   \
    \     return ret;\n    }\n};\n"
  code: "#pragma once\n#include <bitset>\n#include <vector>\n\n// CUT begin\n// Vector\
    \ matroid on F2 : linearly independent vectors\n// VDIM: max. dimension of vector\
    \ space\n// Verified: SRM526.5 1000 (Used only for linear independence check)\n\
    template <int VDIM> class F2VectorMatroid {\n    using Element = int;\n    static\
    \ void chxormin(std::bitset<VDIM> &l, const std::bitset<VDIM> &r) {\n        int\
    \ i = r._Find_first();\n        if (i < VDIM and l[i]) l ^= r;\n    }\n    std::vector<std::bitset<VDIM>>\
    \ mat;\n    std::vector<Element> Iset;\n    std::vector<std::vector<std::bitset<VDIM>>>\
    \ bs;\n\npublic:\n    F2VectorMatroid() = default;\n    F2VectorMatroid(const\
    \ std::vector<std::bitset<VDIM>> &bitmat) : mat(bitmat) {}\n\n    int size() const\
    \ { return mat.size(); }\n\n    template <class State> void set(const State &I)\
    \ {\n        Iset.clear();\n        for (int e = 0; e < size(); e++) {\n     \
    \       if (I[e]) Iset.push_back(e);\n        }\n        bs.assign(Iset.size()\
    \ + 1, {});\n        for (int i = 0; i < int(Iset.size()); i++) {\n          \
    \  for (int j = i; j < int(Iset.size()); j++) {\n                auto v = mat[Iset[j]];\n\
    \                for (auto b : bs[i]) chxormin(v, b);\n                bs[i].push_back(v);\n\
    \            }\n        }\n    }\n    std::vector<Element> circuit(const Element\
    \ &e) const {\n        std::bitset<VDIM> v = mat[e];\n        for (auto b : bs[0])\
    \ chxormin(v, b);\n        if (v.any()) return {}; // I + {e} is independent\n\
    \n        std::vector<Element> ret{e};\n        v = mat[e];\n        for (int\
    \ i = 0; i < int(Iset.size()); i++) {\n            std::bitset<VDIM> w = v;\n\
    \            for (auto b : bs[i + 1]) chxormin(w, b);\n            if (w.any())\
    \ ret.push_back(Iset[i]);\n            chxormin(v, bs[0][i]);\n        }\n   \
    \     return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroids/vector_matroid.hpp
  requiredBy: []
  timestamp: '2021-09-01 23:53:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/matroids/vector_matroid.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/matroids/vector_matroid.hpp
- /library/combinatorial_opt/matroids/vector_matroid.hpp.html
title: combinatorial_opt/matroids/vector_matroid.hpp
---
