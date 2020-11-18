---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/manacher_mp.test.cpp
    title: string/test/manacher_mp.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/mp_algorithm.hpp\"\n#include <string>\n#include <vector>\n\
    \n// CUT begin\nstd::vector<int> mp_algorithm(std::string s) {\n    int N = s.length();\n\
    \    std::vector<int> ret(N + 1, -1);\n    int j = -1;\n    for (int i = 0; i\
    \ < N; i++) {\n        while (j >= 0 and s[i] != s[j]) j = ret[j];\n        ret[i\
    \ + 1] = ++j;\n    }\n    return ret;\n}\n"
  code: "#pragma once\n#include <string>\n#include <vector>\n\n// CUT begin\nstd::vector<int>\
    \ mp_algorithm(std::string s) {\n    int N = s.length();\n    std::vector<int>\
    \ ret(N + 1, -1);\n    int j = -1;\n    for (int i = 0; i < N; i++) {\n      \
    \  while (j >= 0 and s[i] != s[j]) j = ret[j];\n        ret[i + 1] = ++j;\n  \
    \  }\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/mp_algorithm.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
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
