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
  bundledCode: "#line 2 \"combinatorial_opt/matroids/binary_matroid.hpp\"\n#include\
    \ <bitset>\n#include <vector>\n\n// CUT begin\n// Binary matroid (vector matroid\
    \ on F2) : linearly independent vectors\n// VDIM: max. dimension of vector space\n\
    // Verified: SRM526.5 1000 (Used only for linear independence check)\n// Verified:\
    \ CF102156D 2019 Petrozavodsk Winter Camp, Yandex Cup D. Pick Your Own Nim\ntemplate\
    \ <int VDIM> class BinaryMatroid {\n    using Element = int;\n    static void\
    \ chxormin(std::bitset<VDIM> &l, const std::bitset<VDIM> &r) {\n        int i\
    \ = r._Find_first();\n        if (i < VDIM and l[i]) l ^= r;\n    }\n    std::vector<std::bitset<VDIM>>\
    \ mat;\n    std::vector<Element> Iset;\n    std::vector<std::vector<std::bitset<VDIM>>>\
    \ bs;\n\npublic:\n    BinaryMatroid() = default;\n    BinaryMatroid(const std::vector<std::bitset<VDIM>>\
    \ &bitmat) : mat(bitmat) {}\n\n    int size() const { return mat.size(); }\n\n\
    \    template <class State> void set(const State &I) {\n        Iset.clear();\n\
    \        for (int e = 0; e < size(); e++) {\n            if (I[e]) Iset.push_back(e);\n\
    \        }\n        bs.assign(Iset.size() + 1, {});\n        for (int i = 0; i\
    \ < int(Iset.size()) + 1; i++) {\n            for (int j = 0; j < int(Iset.size());\
    \ j++) {\n                if (i == j) continue;\n                auto v = mat[Iset[j]];\n\
    \                for (const auto &b : bs[i]) chxormin(v, b);\n               \
    \ if (v.any()) bs[i].push_back(v);\n            }\n        }\n    }\n    std::vector<Element>\
    \ circuit(const Element &e) const {\n        std::bitset<VDIM> v = mat[e];\n \
    \       for (const auto &b : bs.back()) chxormin(v, b);\n        if (v.any())\
    \ return {}; // I + {e} is independent\n\n        std::vector<Element> ret{e};\n\
    \        for (int i = 0; i < int(Iset.size()); i++) {\n            std::bitset<VDIM>\
    \ w = mat[e];\n            for (const auto &b : bs[i]) chxormin(w, b);\n     \
    \       if (w.any()) ret.push_back(Iset[i]);\n        }\n        return ret;\n\
    \    }\n};\n"
  code: "#pragma once\n#include <bitset>\n#include <vector>\n\n// CUT begin\n// Binary\
    \ matroid (vector matroid on F2) : linearly independent vectors\n// VDIM: max.\
    \ dimension of vector space\n// Verified: SRM526.5 1000 (Used only for linear\
    \ independence check)\n// Verified: CF102156D 2019 Petrozavodsk Winter Camp, Yandex\
    \ Cup D. Pick Your Own Nim\ntemplate <int VDIM> class BinaryMatroid {\n    using\
    \ Element = int;\n    static void chxormin(std::bitset<VDIM> &l, const std::bitset<VDIM>\
    \ &r) {\n        int i = r._Find_first();\n        if (i < VDIM and l[i]) l ^=\
    \ r;\n    }\n    std::vector<std::bitset<VDIM>> mat;\n    std::vector<Element>\
    \ Iset;\n    std::vector<std::vector<std::bitset<VDIM>>> bs;\n\npublic:\n    BinaryMatroid()\
    \ = default;\n    BinaryMatroid(const std::vector<std::bitset<VDIM>> &bitmat)\
    \ : mat(bitmat) {}\n\n    int size() const { return mat.size(); }\n\n    template\
    \ <class State> void set(const State &I) {\n        Iset.clear();\n        for\
    \ (int e = 0; e < size(); e++) {\n            if (I[e]) Iset.push_back(e);\n \
    \       }\n        bs.assign(Iset.size() + 1, {});\n        for (int i = 0; i\
    \ < int(Iset.size()) + 1; i++) {\n            for (int j = 0; j < int(Iset.size());\
    \ j++) {\n                if (i == j) continue;\n                auto v = mat[Iset[j]];\n\
    \                for (const auto &b : bs[i]) chxormin(v, b);\n               \
    \ if (v.any()) bs[i].push_back(v);\n            }\n        }\n    }\n    std::vector<Element>\
    \ circuit(const Element &e) const {\n        std::bitset<VDIM> v = mat[e];\n \
    \       for (const auto &b : bs.back()) chxormin(v, b);\n        if (v.any())\
    \ return {}; // I + {e} is independent\n\n        std::vector<Element> ret{e};\n\
    \        for (int i = 0; i < int(Iset.size()); i++) {\n            std::bitset<VDIM>\
    \ w = mat[e];\n            for (const auto &b : bs[i]) chxormin(w, b);\n     \
    \       if (w.any()) ret.push_back(Iset[i]);\n        }\n        return ret;\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroids/binary_matroid.hpp
  requiredBy: []
  timestamp: '2021-09-05 18:41:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/matroids/binary_matroid.hpp
layout: document
title: "Binary matroid \uFF08\u4E8C\u5024\u30DE\u30C8\u30ED\u30A4\u30C9\uFF09"
---

$\mathbb{F}_2$ 上の $N$ 行 $M$ 列の行列 $A$ によって定義されるマトロイド．集合 $I \subset 2^M$ は，$A$ のうち $I$ に含まれる番号の列のみを抜き出した部分行列が列フルランクのとき，およびその時に限り独立集合である．

## 使用例

```cpp
bitset<5> v0, v1, v2, v3;
v0.set(0);
v1.set(1), v1.set(2);
v2.set(0), v2.set(1), v2.set(2);
v3.set(0), v3.set(2);
vector<bitset<5>> mat{v0, v1, v2, v3};
BinaryMatroid<5> M(mat);

vector<bool> I{0, 1, 1, 0};
M.set(I);
assert((M.circuit(0) == vector<int>{0, 1, 2}));
```
