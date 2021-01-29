---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/z_algorithm.hpp
    title: string/z_algorithm.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 2 \"string/z_algorithm.hpp\"\n#include <string>\n#include <vector>\n\
    \n// CUT begin\n// Z algorithm (length of longest common prefix for s[0:N] & s[i:N]\
    \ for each i)\n// Input: std::vector<T> / std::string of length N\n// Output:\
    \ std::vector<int> of size N\n// Complexity: O(N)\n// Sample:\n// - `teletelepathy`\
    \ -> [13, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 0]\n// Reference: <http://snuke.hatenablog.com/entry/2014/12/03/214243>\n\
    template <typename T> std::vector<int> z_algorithm(const std::vector<T> &s) {\n\
    \    const int N = s.size();\n    if (N == 0) return {};\n    std::vector<int>\
    \ ans(N);\n    ans[0] = N;\n    int i = 1, j = 0;\n    while (i < N) {\n     \
    \   while (i + j < N and s[j] == s[i + j]) ++j;\n        ans[i] = j;\n       \
    \ if (!j) {\n            ++i;\n            continue;\n        }\n        int k\
    \ = 1;\n        while (i + k < N and k + ans[k] < j) ans[i + k] = ans[k], ++k;\n\
    \        i += k;\n        j -= k;\n    }\n    return ans;\n}\n\nstd::vector<int>\
    \ z_algorithm(const std::string &s) {\n    const int N = int(s.size());\n    std::vector<int>\
    \ v(N);\n    for (int i = 0; i < N; i++) v[i] = s[i];\n    return z_algorithm(v);\n\
    }\n#line 2 \"string/test/z_algorithm.test.cpp\"\n#include <cstdio>\n#include <iostream>\n\
    #line 5 \"string/test/z_algorithm.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\
    \n\nint main() {\n    std::string S;\n    std::cin >> S;\n    for (auto x : z_algorithm(S))\
    \ printf(\"%d \", x);\n}\n"
  code: "#include \"../z_algorithm.hpp\"\n#include <cstdio>\n#include <iostream>\n\
    #include <string>\n#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\
    \n\nint main() {\n    std::string S;\n    std::cin >> S;\n    for (auto x : z_algorithm(S))\
    \ printf(\"%d \", x);\n}\n"
  dependsOn:
  - string/z_algorithm.hpp
  isVerificationFile: true
  path: string/test/z_algorithm.test.cpp
  requiredBy: []
  timestamp: '2021-01-01 16:52:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/z_algorithm.test.cpp
layout: document
redirect_from:
- /verify/string/test/z_algorithm.test.cpp
- /verify/string/test/z_algorithm.test.cpp.html
title: string/test/z_algorithm.test.cpp
---
