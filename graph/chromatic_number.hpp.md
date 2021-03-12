---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc187/tasks/abc187_f
    - https://www.slideshare.net/wata_orz/ss-12131479
  bundledCode: "#line 2 \"graph/chromatic_number.hpp\"\n#include <numeric>\n#include\
    \ <vector>\n\n// CUT begin\n// (vertex) chromatic number: \uFF08\u9802\u70B9\uFF09\
    \u5F69\u8272\u6570\n// Verify: https://atcoder.jp/contests/abc187/tasks/abc187_f\n\
    // Reference:\n// [1] A. Bjorklund and T. Husfeldt, \"Inclusion--Exclusion Algorithms\
    \ for Counting Set Partitions,\"\n//     2006 47th Annual IEEE Symposium on Foundations\
    \ of Computer Science (FOCS'06).\n// - https://www.slideshare.net/wata_orz/ss-12131479\n\
    template <typename MODINT, typename Int> int ChromaticNumber(const std::vector<Int>\
    \ &edge) {\n    const int V = edge.size(), S = 1 << V;\n    if (V == 0) return\
    \ 0;\n    std::vector<MODINT> f(S), g(S);\n    for (int s = 0; s < S; s++) g[s]\
    \ = (__builtin_popcount(s) & 1) ? 1 : -1;\n    f[0] = 1;\n    for (int s = 1;\
    \ s < S; s++) {\n        int i = __builtin_ctz(s);\n        f[s] = f[s - (1 <<\
    \ i)] + f[(s - (1 << i)) & ~edge[i]];\n    }\n    for (int k = 1; k < V; k++)\
    \ {\n        for (int s = 0; s < S; s++) g[s] *= f[s];\n        if (std::accumulate(g.begin(),\
    \ g.end(), MODINT(0)).val) return k;\n    }\n    return V;\n};\n"
  code: "#pragma once\n#include <numeric>\n#include <vector>\n\n// CUT begin\n// (vertex)\
    \ chromatic number: \uFF08\u9802\u70B9\uFF09\u5F69\u8272\u6570\n// Verify: https://atcoder.jp/contests/abc187/tasks/abc187_f\n\
    // Reference:\n// [1] A. Bjorklund and T. Husfeldt, \"Inclusion--Exclusion Algorithms\
    \ for Counting Set Partitions,\"\n//     2006 47th Annual IEEE Symposium on Foundations\
    \ of Computer Science (FOCS'06).\n// - https://www.slideshare.net/wata_orz/ss-12131479\n\
    template <typename MODINT, typename Int> int ChromaticNumber(const std::vector<Int>\
    \ &edge) {\n    const int V = edge.size(), S = 1 << V;\n    if (V == 0) return\
    \ 0;\n    std::vector<MODINT> f(S), g(S);\n    for (int s = 0; s < S; s++) g[s]\
    \ = (__builtin_popcount(s) & 1) ? 1 : -1;\n    f[0] = 1;\n    for (int s = 1;\
    \ s < S; s++) {\n        int i = __builtin_ctz(s);\n        f[s] = f[s - (1 <<\
    \ i)] + f[(s - (1 << i)) & ~edge[i]];\n    }\n    for (int k = 1; k < V; k++)\
    \ {\n        for (int s = 0; s < S; s++) g[s] *= f[s];\n        if (std::accumulate(g.begin(),\
    \ g.end(), MODINT(0)).val) return k;\n    }\n    return V;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/chromatic_number.hpp
  requiredBy: []
  timestamp: '2021-03-13 01:45:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/chromatic_number.hpp
layout: document
redirect_from:
- /library/graph/chromatic_number.hpp
- /library/graph/chromatic_number.hpp.html
title: graph/chromatic_number.hpp
---
