---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/z_algorithm.hpp
    title: string/z_algorithm.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 2 \"string/z_algorithm.hpp\"\n#include <string>\n#include <vector>\n\
    \n// CUT begin\n// Z algorithm (length of longest common prefix for s[0:N] & s[i:N]\
    \ for each i)\n// Complexity: O(N)\n// <http://snuke.hatenablog.com/entry/2014/12/03/214243>\n\
    std::vector<int> z_algorithm(const std::string &s) {\n    std::vector<int> ans(s.size());\n\
    \    ans[0] = s.size();\n    int i = 1, j = 0;\n    while (i < (int)s.size())\
    \ {\n        while (i + j < (int)s.size() && s[j] == s[i + j]) ++j;\n        ans[i]\
    \ = j;\n        if (!j) {\n            ++i;\n            continue;\n        }\n\
    \        int k = 1;\n        while (i + k < (int)s.size() && k + ans[k] < j) ans[i\
    \ + k] = ans[k], ++k;\n        i += k;\n        j -= k;\n    }\n    return ans;\n\
    }\n#line 2 \"string/test/z_algorithm.test.cpp\"\n#include <cstdio>\n#include <iostream>\n\
    #line 5 \"string/test/z_algorithm.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\
    \n\nint main()\n{\n    std::string S;\n    std::cin >> S;\n    for (auto x : z_algorithm(S))\n\
    \    {\n        printf(\"%d \", x);\n    }\n}\n"
  code: "#include \"string/z_algorithm.hpp\"\n#include <cstdio>\n#include <iostream>\n\
    #include <string>\n#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\
    \n\nint main()\n{\n    std::string S;\n    std::cin >> S;\n    for (auto x : z_algorithm(S))\n\
    \    {\n        printf(\"%d \", x);\n    }\n}\n"
  dependsOn:
  - string/z_algorithm.hpp
  isVerificationFile: true
  path: string/test/z_algorithm.test.cpp
  requiredBy: []
  timestamp: '2020-04-18 21:15:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/z_algorithm.test.cpp
layout: document
redirect_from:
- /verify/string/test/z_algorithm.test.cpp
- /verify/string/test/z_algorithm.test.cpp.html
title: string/test/z_algorithm.test.cpp
---
