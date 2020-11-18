---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: string/suffix_array.hpp
    title: string/suffix_array.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/number_of_substrings
    links:
    - https://judge.yosupo.jp/problem/number_of_substrings
  bundledCode: "#line 2 \"string/suffix_array.hpp\"\n#include <algorithm>\n#include\
    \ <numeric>\n#include <vector>\n\n// CUT begin\n// Suffix Array / Longest Common\
    \ Prefix Array Construction\n// Comlexity: O(N(log N)^2)\ntemplate <typename T>\
    \ struct SuffixArray {\n    T S;                   // size: N\n    std::vector<int>\
    \ SA;   // Suffix Array (size: N + 1, SA[0] == N) SA[i] means S[SA[i]:]\n    std::vector<int>\
    \ rank; // Rank (inverse of SA) (size: N + 1, rank[N] == 0)\n    std::vector<int>\
    \ lcp;  // Longest Common Prefix Array (size: N) betw. S[SA[i]:] & S[SA[i + 1]:]\n\
    \n    SuffixArray(const T &str, bool gen_lcp = true) : S(str) {\n        int N\
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
    \ S[i + h]) break;\n            lcp[rank[i] - 1] = h;\n        }\n    }\n};\n\
    #line 2 \"string/test/lcp.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\
    \n#include <iostream>\n#include <string>\n\nint main() {\n    std::string S;\n\
    \    std::cin >> S;\n    SuffixArray<decltype(S)> sa(S, true);\n\n    int N =\
    \ S.length();\n    long long int ret = 0;\n    for (int i = 0; i < N; i++) ret\
    \ += N - sa.SA[i + 1] - sa.lcp[i];\n    std::cout << ret << std::endl;\n}\n"
  code: "#include \"string/suffix_array.hpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\
    \n#include <iostream>\n#include <string>\n\nint main() {\n    std::string S;\n\
    \    std::cin >> S;\n    SuffixArray<decltype(S)> sa(S, true);\n\n    int N =\
    \ S.length();\n    long long int ret = 0;\n    for (int i = 0; i < N; i++) ret\
    \ += N - sa.SA[i + 1] - sa.lcp[i];\n    std::cout << ret << std::endl;\n}\n"
  dependsOn:
  - string/suffix_array.hpp
  isVerificationFile: true
  path: string/test/lcp.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: string/test/lcp.test.cpp
layout: document
redirect_from:
- /verify/string/test/lcp.test.cpp
- /verify/string/test/lcp.test.cpp.html
title: string/test/lcp.test.cpp
---
