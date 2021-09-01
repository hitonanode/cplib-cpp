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
  bundledCode: "#line 2 \"combinatorial_opt/matroids/partition_matroid.hpp\"\n#include\
    \ <cassert>\n#include <vector>\n\n// Partition matroid (partitional matroid) :\
    \ direct sum of uniform matroids\nclass PartitionMatroid {\n    using Element\
    \ = int;\n    int M;\n    std::vector<std::vector<Element>> parts;\n    std::vector<int>\
    \ belong;\n    std::vector<int> R;\n    std::vector<int> cnt;\n    std::vector<std::vector<Element>>\
    \ circuits;\n\npublic:\n    // parts: partition of [0, 1, ..., M - 1]\n    //\
    \ R: only R[i] elements from parts[i] can be chosen for each i.\n    PartitionMatroid(int\
    \ M, const std::vector<std::vector<int>> &parts_, const std::vector<int> &R_)\n\
    \        : M(M), parts(parts_), belong(M, -1), R(R_) {\n        assert(parts.size()\
    \ == R.size());\n        for (int i = 0; i < int(parts.size()); i++) {\n     \
    \       for (Element e : parts[i]) belong[e] = i;\n        }\n        for (Element\
    \ e = 0; e < M; e++) {\n            // assert(belong[e] != -1);\n            if\
    \ (belong[e] == -1) {\n                belong[e] = parts.size();\n           \
    \     parts.push_back({e});\n                R.push_back(1);\n            }\n\
    \        }\n    }\n    int size() const { return M; }\n\n    template <class State>\
    \ void set(const State &I) {\n        cnt = R;\n        for (int e = 0; e < M;\
    \ e++) {\n            if (I[e]) cnt[belong[e]]--;\n        }\n        circuits.assign(cnt.size(),\
    \ {});\n        for (int e = 0; e < M; e++) {\n            if (I[e] and cnt[belong[e]]\
    \ == 0) circuits[belong[e]].push_back(e);\n        }\n    }\n\n    std::vector<Element>\
    \ circuit(const Element e) const {\n        assert(0 <= e and e < M);\n      \
    \  int p = belong[e];\n        if (cnt[p] == 0) {\n            auto ret = circuits[p];\n\
    \            ret.push_back(e);\n            return ret;\n        }\n        return\
    \ {};\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// Partition matroid\
    \ (partitional matroid) : direct sum of uniform matroids\nclass PartitionMatroid\
    \ {\n    using Element = int;\n    int M;\n    std::vector<std::vector<Element>>\
    \ parts;\n    std::vector<int> belong;\n    std::vector<int> R;\n    std::vector<int>\
    \ cnt;\n    std::vector<std::vector<Element>> circuits;\n\npublic:\n    // parts:\
    \ partition of [0, 1, ..., M - 1]\n    // R: only R[i] elements from parts[i]\
    \ can be chosen for each i.\n    PartitionMatroid(int M, const std::vector<std::vector<int>>\
    \ &parts_, const std::vector<int> &R_)\n        : M(M), parts(parts_), belong(M,\
    \ -1), R(R_) {\n        assert(parts.size() == R.size());\n        for (int i\
    \ = 0; i < int(parts.size()); i++) {\n            for (Element e : parts[i]) belong[e]\
    \ = i;\n        }\n        for (Element e = 0; e < M; e++) {\n            // assert(belong[e]\
    \ != -1);\n            if (belong[e] == -1) {\n                belong[e] = parts.size();\n\
    \                parts.push_back({e});\n                R.push_back(1);\n    \
    \        }\n        }\n    }\n    int size() const { return M; }\n\n    template\
    \ <class State> void set(const State &I) {\n        cnt = R;\n        for (int\
    \ e = 0; e < M; e++) {\n            if (I[e]) cnt[belong[e]]--;\n        }\n \
    \       circuits.assign(cnt.size(), {});\n        for (int e = 0; e < M; e++)\
    \ {\n            if (I[e] and cnt[belong[e]] == 0) circuits[belong[e]].push_back(e);\n\
    \        }\n    }\n\n    std::vector<Element> circuit(const Element e) const {\n\
    \        assert(0 <= e and e < M);\n        int p = belong[e];\n        if (cnt[p]\
    \ == 0) {\n            auto ret = circuits[p];\n            ret.push_back(e);\n\
    \            return ret;\n        }\n        return {};\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroids/partition_matroid.hpp
  requiredBy: []
  timestamp: '2021-09-01 23:53:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/matroids/partition_matroid.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/matroids/partition_matroid.hpp
- /library/combinatorial_opt/matroids/partition_matroid.hpp.html
title: combinatorial_opt/matroids/partition_matroid.hpp
---
