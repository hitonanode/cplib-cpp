---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/arc060/submissions/7039451>
  bundledCode: "#line 2 \"binary_lifting(doubling)/doubling.hpp\"\n#include <cstdlib>\n\
    #include <vector>\n\n// CUT begin\n// Binary lifting / `Doubling`\n// Complexity:\
    \ O(NlogN) precalculation / O(logN) per query\n// <https://atcoder.jp/contests/arc060/submissions/7039451>\n\
    struct BinaryLifting\n{\n    int N, INVALID, lgD;\n    std::vector<std::vector<int>>\
    \ mat;\n    BinaryLifting() : N(0), lgD(0) {}\n    BinaryLifting(const std::vector<int>\
    \ &vec_nxt, int INVALID = -1, int lgd = 0) : N(vec_nxt.size()), INVALID(INVALID),\
    \ lgD(lgd)\n    {\n        while ((1LL << lgD) < N) lgD++;\n        mat.assign(lgD,\
    \ std::vector<int>(N, INVALID));\n        mat[0] = vec_nxt;\n        for (int\
    \ i = 0; i < N; i++) if (mat[0][i] < 0 or mat[0][i] >= N) mat[0][i] = INVALID;\n\
    \        for (int d = 0; d < lgD - 1; d++) {\n            for (int i = 0; i <\
    \ N; i++) if (mat[d][i] != INVALID) mat[d + 1][i] = mat[d][mat[d][i]];\n     \
    \   }\n    }\n    int kth_next(int now, long long k)\n    {\n        if (k >=\
    \ (1LL << lgD)) exit(8);\n        for (int d = 0; k and now != INVALID; d++, k\
    \ >>= 1) if (k & 1) now = mat[d][now];\n        return now;\n    }\n\n    // Distance\
    \ from l to [r, \\infty)\n    // Requirement: mat[0][i] > i for all i (monotone\
    \ increasing)\n    int distance(int l, int r)\n    {\n        if (l >= r) return\
    \ 0;\n        int ret = 0;\n        for (int d = lgD - 1; d >= 0; d--) {\n   \
    \         if (mat[d][l] < r and mat[d][l] != INVALID) ret += 1 << d, l = mat[d][l];\n\
    \        }\n        if (mat[0][l] == INVALID or mat[0][l] >= r) return ret + 1;\n\
    \        else return -1; // Unable to reach\n    }\n};\n"
  code: "#pragma once\n#include <cstdlib>\n#include <vector>\n\n// CUT begin\n// Binary\
    \ lifting / `Doubling`\n// Complexity: O(NlogN) precalculation / O(logN) per query\n\
    // <https://atcoder.jp/contests/arc060/submissions/7039451>\nstruct BinaryLifting\n\
    {\n    int N, INVALID, lgD;\n    std::vector<std::vector<int>> mat;\n    BinaryLifting()\
    \ : N(0), lgD(0) {}\n    BinaryLifting(const std::vector<int> &vec_nxt, int INVALID\
    \ = -1, int lgd = 0) : N(vec_nxt.size()), INVALID(INVALID), lgD(lgd)\n    {\n\
    \        while ((1LL << lgD) < N) lgD++;\n        mat.assign(lgD, std::vector<int>(N,\
    \ INVALID));\n        mat[0] = vec_nxt;\n        for (int i = 0; i < N; i++) if\
    \ (mat[0][i] < 0 or mat[0][i] >= N) mat[0][i] = INVALID;\n        for (int d =\
    \ 0; d < lgD - 1; d++) {\n            for (int i = 0; i < N; i++) if (mat[d][i]\
    \ != INVALID) mat[d + 1][i] = mat[d][mat[d][i]];\n        }\n    }\n    int kth_next(int\
    \ now, long long k)\n    {\n        if (k >= (1LL << lgD)) exit(8);\n        for\
    \ (int d = 0; k and now != INVALID; d++, k >>= 1) if (k & 1) now = mat[d][now];\n\
    \        return now;\n    }\n\n    // Distance from l to [r, \\infty)\n    //\
    \ Requirement: mat[0][i] > i for all i (monotone increasing)\n    int distance(int\
    \ l, int r)\n    {\n        if (l >= r) return 0;\n        int ret = 0;\n    \
    \    for (int d = lgD - 1; d >= 0; d--) {\n            if (mat[d][l] < r and mat[d][l]\
    \ != INVALID) ret += 1 << d, l = mat[d][l];\n        }\n        if (mat[0][l]\
    \ == INVALID or mat[0][l] >= r) return ret + 1;\n        else return -1; // Unable\
    \ to reach\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: binary_lifting(doubling)/doubling.hpp
  requiredBy: []
  timestamp: '2020-05-10 23:20:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: binary_lifting(doubling)/doubling.hpp
layout: document
redirect_from:
- /library/binary_lifting(doubling)/doubling.hpp
- /library/binary_lifting(doubling)/doubling.hpp.html
title: binary_lifting(doubling)/doubling.hpp
---
