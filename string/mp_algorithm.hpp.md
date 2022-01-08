---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/manacher_mp.test.cpp
    title: string/test/manacher_mp.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://snuke.hatenablog.com/entry/2014/12/01/235807>
  bundledCode: "#line 2 \"string/mp_algorithm.hpp\"\n#include <string>\n#include <vector>\n\
    \n// CUT begin\n// MP (Morris-Pratt) algorithm (length of longest nontrivial matching\
    \ for\n// prefix & suffix of s[0:i] for each i)\n// Input: std::string of length\
    \ N\n// Output: std::vector<int> of size N + 1\n// Complexity: O(N)\n// Sample:\n\
    // - `teletelepathy` -> [-1, 0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 1, 0, 0]\n// Reference:\
    \ <https://snuke.hatenablog.com/entry/2014/12/01/235807>\nstd::vector<int> mp_algorithm(std::string\
    \ s) {\n    int N = s.length();\n    std::vector<int> ret(N + 1, -1);\n    int\
    \ j = -1;\n    for (int i = 0; i < N; i++) {\n        while (j >= 0 and s[i] !=\
    \ s[j]) j = ret[j];\n        ret[i + 1] = ++j;\n    }\n    return ret;\n}\n"
  code: "#pragma once\n#include <string>\n#include <vector>\n\n// CUT begin\n// MP\
    \ (Morris-Pratt) algorithm (length of longest nontrivial matching for\n// prefix\
    \ & suffix of s[0:i] for each i)\n// Input: std::string of length N\n// Output:\
    \ std::vector<int> of size N + 1\n// Complexity: O(N)\n// Sample:\n// - `teletelepathy`\
    \ -> [-1, 0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 1, 0, 0]\n// Reference: <https://snuke.hatenablog.com/entry/2014/12/01/235807>\n\
    std::vector<int> mp_algorithm(std::string s) {\n    int N = s.length();\n    std::vector<int>\
    \ ret(N + 1, -1);\n    int j = -1;\n    for (int i = 0; i < N; i++) {\n      \
    \  while (j >= 0 and s[i] != s[j]) j = ret[j];\n        ret[i + 1] = ++j;\n  \
    \  }\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/mp_algorithm.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/manacher_mp.test.cpp
documentation_of: string/mp_algorithm.hpp
layout: document
redirect_from:
- /library/string/mp_algorithm.hpp
- /library/string/mp_algorithm.hpp.html
title: string/mp_algorithm.hpp
---
