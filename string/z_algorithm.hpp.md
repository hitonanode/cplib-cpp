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
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - http://snuke.hatenablog.com/entry/2014/12/03/214243>
  bundledCode: "#line 2 \"string/z_algorithm.hpp\"\n#include <string>\n#include <vector>\n\
    \n// CUT begin\n// Z algorithm (length of longest common prefix for s[0:N] & s[i:N]\
    \ for each i)\n// Complexity: O(N)\n// <http://snuke.hatenablog.com/entry/2014/12/03/214243>\n\
    std::vector<int> z_algorithm(const std::string &s) {\n    std::vector<int> ans(s.size());\n\
    \    ans[0] = s.size();\n    int i = 1, j = 0;\n    while (i < (int)s.size())\
    \ {\n        while (i + j < (int)s.size() && s[j] == s[i + j]) ++j;\n        ans[i]\
    \ = j;\n        if (!j) {\n            ++i;\n            continue;\n        }\n\
    \        int k = 1;\n        while (i + k < (int)s.size() && k + ans[k] < j) ans[i\
    \ + k] = ans[k], ++k;\n        i += k;\n        j -= k;\n    }\n    return ans;\n\
    }\n"
  code: "#pragma once\n#include <string>\n#include <vector>\n\n// CUT begin\n// Z\
    \ algorithm (length of longest common prefix for s[0:N] & s[i:N] for each i)\n\
    // Complexity: O(N)\n// <http://snuke.hatenablog.com/entry/2014/12/03/214243>\n\
    std::vector<int> z_algorithm(const std::string &s) {\n    std::vector<int> ans(s.size());\n\
    \    ans[0] = s.size();\n    int i = 1, j = 0;\n    while (i < (int)s.size())\
    \ {\n        while (i + j < (int)s.size() && s[j] == s[i + j]) ++j;\n        ans[i]\
    \ = j;\n        if (!j) {\n            ++i;\n            continue;\n        }\n\
    \        int k = 1;\n        while (i + k < (int)s.size() && k + ans[k] < j) ans[i\
    \ + k] = ans[k], ++k;\n        i += k;\n        j -= k;\n    }\n    return ans;\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2020-04-18 21:15:29+09:00'
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
