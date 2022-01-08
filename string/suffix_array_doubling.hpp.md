---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/lcp.test.cpp
    title: string/test/lcp.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/suffix_array.test.cpp
    title: string/test/suffix_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/suffix_array_doubling.hpp\"\n#include <algorithm>\n\
    #include <numeric>\n#include <vector>\n\n// CUT begin\n// Suffix Array / Longest\
    \ Common Prefix Array Construction\n// Comlexity: O(N(log N)^2)\ntemplate <typename\
    \ T> struct [[deprecated(\"use ACL based suffix array\")]] SuffixArray {\n   \
    \ T S;                   // size: N\n    std::vector<int> SA;   // Suffix Array\
    \ (size: N + 1, SA[0] == N) SA[i] means S[SA[i]:]\n    std::vector<int> rank;\
    \ // Rank (inverse of SA) (size: N + 1, rank[N] == 0)\n    std::vector<int> lcp;\
    \  // Longest Common Prefix Array (size: N) betw. S[SA[i]:] & S[SA[i + 1]:]\n\n\
    \    SuffixArray(const T &str, bool gen_lcp = true) : S(str) {\n        int N\
    \ = S.size();\n        SA.resize(N + 1);\n        std::iota(SA.begin(), SA.end(),\
    \ 0);\n        rank.assign(N + 1, -1);\n        for (int i = 0; i < N; i++) rank[i]\
    \ = S[i];\n        int _ord_mm = 1;\n\n        auto _comp_suffarr = [&](int i,\
    \ int j) {\n            if (rank[i] != rank[j]) return rank[i] < rank[j];\n  \
    \          int ri = i + _ord_mm < (int)rank.size() ? rank[i + _ord_mm] : -1;\n\
    \            int rj = j + _ord_mm < (int)rank.size() ? rank[j + _ord_mm] : -1;\n\
    \            return ri < rj;\n        };\n        std::vector<int> tmp(N + 1);\n\
    \        for (_ord_mm = 1; _ord_mm <= N; _ord_mm *= 2) {\n            std::sort(SA.begin(),\
    \ SA.end(), _comp_suffarr);\n            tmp[SA[0]] = 0;\n            for (int\
    \ i = 1; i <= N; i++) { tmp[SA[i]] = tmp[SA[i - 1]] + _comp_suffarr(SA[i - 1],\
    \ SA[i]); }\n            rank = tmp;\n        }\n        if (!gen_lcp) return;\n\
    \n        lcp.assign(N, 0);\n        int h = 0;\n        for (int i = 0; i < N;\
    \ i++) {\n            int j = SA[rank[i] - 1];\n            if (h) h--;\n    \
    \        for (; j + h < N and i + h < N; h++)\n                if (S[j + h] !=\
    \ S[i + h]) break;\n            lcp[rank[i] - 1] = h;\n        }\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <numeric>\n#include <vector>\n\
    \n// CUT begin\n// Suffix Array / Longest Common Prefix Array Construction\n//\
    \ Comlexity: O(N(log N)^2)\ntemplate <typename T> struct [[deprecated(\"use ACL\
    \ based suffix array\")]] SuffixArray {\n    T S;                   // size: N\n\
    \    std::vector<int> SA;   // Suffix Array (size: N + 1, SA[0] == N) SA[i] means\
    \ S[SA[i]:]\n    std::vector<int> rank; // Rank (inverse of SA) (size: N + 1,\
    \ rank[N] == 0)\n    std::vector<int> lcp;  // Longest Common Prefix Array (size:\
    \ N) betw. S[SA[i]:] & S[SA[i + 1]:]\n\n    SuffixArray(const T &str, bool gen_lcp\
    \ = true) : S(str) {\n        int N = S.size();\n        SA.resize(N + 1);\n \
    \       std::iota(SA.begin(), SA.end(), 0);\n        rank.assign(N + 1, -1);\n\
    \        for (int i = 0; i < N; i++) rank[i] = S[i];\n        int _ord_mm = 1;\n\
    \n        auto _comp_suffarr = [&](int i, int j) {\n            if (rank[i] !=\
    \ rank[j]) return rank[i] < rank[j];\n            int ri = i + _ord_mm < (int)rank.size()\
    \ ? rank[i + _ord_mm] : -1;\n            int rj = j + _ord_mm < (int)rank.size()\
    \ ? rank[j + _ord_mm] : -1;\n            return ri < rj;\n        };\n       \
    \ std::vector<int> tmp(N + 1);\n        for (_ord_mm = 1; _ord_mm <= N; _ord_mm\
    \ *= 2) {\n            std::sort(SA.begin(), SA.end(), _comp_suffarr);\n     \
    \       tmp[SA[0]] = 0;\n            for (int i = 1; i <= N; i++) { tmp[SA[i]]\
    \ = tmp[SA[i - 1]] + _comp_suffarr(SA[i - 1], SA[i]); }\n            rank = tmp;\n\
    \        }\n        if (!gen_lcp) return;\n\n        lcp.assign(N, 0);\n     \
    \   int h = 0;\n        for (int i = 0; i < N; i++) {\n            int j = SA[rank[i]\
    \ - 1];\n            if (h) h--;\n            for (; j + h < N and i + h < N;\
    \ h++)\n                if (S[j + h] != S[i + h]) break;\n            lcp[rank[i]\
    \ - 1] = h;\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/suffix_array_doubling.hpp
  requiredBy: []
  timestamp: '2021-01-02 00:51:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/lcp.test.cpp
  - string/test/suffix_array.test.cpp
documentation_of: string/suffix_array_doubling.hpp
layout: document
redirect_from:
- /library/string/suffix_array_doubling.hpp
- /library/string/suffix_array_doubling.hpp.html
title: string/suffix_array_doubling.hpp
---
