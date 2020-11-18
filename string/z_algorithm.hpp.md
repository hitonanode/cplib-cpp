---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/z_algorithm.test.cpp
    title: string/test/z_algorithm.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://snuke.hatenablog.com/entry/2014/12/03/214243>
  bundledCode: "#line 2 \"string/z_algorithm.hpp\"\n#include <string>\n#include <vector>\n\
    \n// CUT begin\n// Z algorithm (length of longest common prefix for s[0:N] & s[i:N]\
    \ for each i)\n// Complexity: O(N)\n// <http://snuke.hatenablog.com/entry/2014/12/03/214243>\n\
    template <typename T> std::vector<int> z_algorithm(const std::vector<T> &s) {\n\
    \    const int N = s.size();\n    if (N == 0) return {};\n    std::vector<int>\
    \ ans(N);\n    ans[0] = N;\n    int i = 1, j = 0;\n    while (i < N) {\n     \
    \   while (i + j < N and s[j] == s[i + j]) ++j;\n        ans[i] = j;\n       \
    \ if (!j) {\n            ++i;\n            continue;\n        }\n        int k\
    \ = 1;\n        while (i + k < N and k + ans[k] < j) ans[i + k] = ans[k], ++k;\n\
    \        i += k;\n        j -= k;\n    }\n    return ans;\n}\n\nstd::vector<int>\
    \ z_algorithm(const std::string &s) {\n    const int N = int(s.size());\n    std::vector<int>\
    \ v(N);\n    for (int i = 0; i < N; i++) v[i] = s[i];\n    return z_algorithm(v);\n\
    }\n"
  code: "#pragma once\n#include <string>\n#include <vector>\n\n// CUT begin\n// Z\
    \ algorithm (length of longest common prefix for s[0:N] & s[i:N] for each i)\n\
    // Complexity: O(N)\n// <http://snuke.hatenablog.com/entry/2014/12/03/214243>\n\
    template <typename T> std::vector<int> z_algorithm(const std::vector<T> &s) {\n\
    \    const int N = s.size();\n    if (N == 0) return {};\n    std::vector<int>\
    \ ans(N);\n    ans[0] = N;\n    int i = 1, j = 0;\n    while (i < N) {\n     \
    \   while (i + j < N and s[j] == s[i + j]) ++j;\n        ans[i] = j;\n       \
    \ if (!j) {\n            ++i;\n            continue;\n        }\n        int k\
    \ = 1;\n        while (i + k < N and k + ans[k] < j) ans[i + k] = ans[k], ++k;\n\
    \        i += k;\n        j -= k;\n    }\n    return ans;\n}\n\nstd::vector<int>\
    \ z_algorithm(const std::string &s) {\n    const int N = int(s.size());\n    std::vector<int>\
    \ v(N);\n    for (int i = 0; i < N; i++) v[i] = s[i];\n    return z_algorithm(v);\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/z_algorithm.test.cpp
documentation_of: string/z_algorithm.hpp
layout: document
redirect_from:
- /library/string/z_algorithm.hpp
- /library/string/z_algorithm.hpp.html
title: string/z_algorithm.hpp
---
