---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: string/test/manacher_mp.test.cpp
    title: string/test/manacher_mp.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://snuke.hatenablog.com/entry/2014/12/02/235837>
  bundledCode: "#line 2 \"string/manacher.hpp\"\n#include <string>\n#include <vector>\n\
    \n// CUT begin\n// Manacher's Algorithm: radius of palindromes\n// Input: std::string\
    \ of length N\n// Output: std::vector<int> of size N\n// Complexity: O(N)\n//\
    \ Sample:\n// - `sakanakanandaka` -> [1, 1, 2, 1, 4, 1, 4, 1, 2, 2, 1, 1, 1, 2,\
    \ 1]\n// Reference: <https://snuke.hatenablog.com/entry/2014/12/02/235837>\nstd::vector<int>\
    \ manacher(std::string S) {\n    std::vector<int> res(S.length());\n    int i\
    \ = 0, j = 0;\n    while (i < (int)S.size()) {\n        while (i - j >= 0 and\
    \ i + j < (int)S.size() and S[i - j] == S[i + j]) j++;\n        res[i] = j;\n\
    \        int k = 1;\n        while (i - k >= 0 and i + k < (int)S.size() and k\
    \ + res[i - k] < j) res[i + k] = res[i - k], k++;\n        i += k, j -= k;\n \
    \   }\n    return res;\n}\n"
  code: "#pragma once\n#include <string>\n#include <vector>\n\n// CUT begin\n// Manacher's\
    \ Algorithm: radius of palindromes\n// Input: std::string of length N\n// Output:\
    \ std::vector<int> of size N\n// Complexity: O(N)\n// Sample:\n// - `sakanakanandaka`\
    \ -> [1, 1, 2, 1, 4, 1, 4, 1, 2, 2, 1, 1, 1, 2, 1]\n// Reference: <https://snuke.hatenablog.com/entry/2014/12/02/235837>\n\
    std::vector<int> manacher(std::string S) {\n    std::vector<int> res(S.length());\n\
    \    int i = 0, j = 0;\n    while (i < (int)S.size()) {\n        while (i - j\
    \ >= 0 and i + j < (int)S.size() and S[i - j] == S[i + j]) j++;\n        res[i]\
    \ = j;\n        int k = 1;\n        while (i - k >= 0 and i + k < (int)S.size()\
    \ and k + res[i - k] < j) res[i + k] = res[i - k], k++;\n        i += k, j -=\
    \ k;\n    }\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/manacher.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - string/test/manacher_mp.test.cpp
documentation_of: string/manacher.hpp
layout: document
redirect_from:
- /library/string/manacher.hpp
- /library/string/manacher.hpp.html
title: string/manacher.hpp
---
