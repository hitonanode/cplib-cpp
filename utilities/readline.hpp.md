---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/gym/100162/problem/G
  bundledCode: "#line 2 \"utilities/readline.hpp\"\n#include <iostream>\n#include\
    \ <sstream>\n#include <string>\n#include <vector>\n\n// Single line reading functions\
    \ for multi-case & NO final case notification inputs\n// Verified: https://codeforces.com/gym/100162/problem/G\n\
    std::vector<int> read_ints() {\n    std::string s;\n    std::getline(std::cin,\
    \ s);\n    if (s.empty()) return {};\n    std::stringstream ss(s);\n    std::vector<int>\
    \ ret;\n    while (!ss.eof()) {\n        int t;\n        ss >> t;\n        ret.push_back(t);\n\
    \    }\n    return ret;\n}\n\nstd::string read_str() {\n    std::string s;\n \
    \   std::getline(std::cin, s);\n    return s;\n}\n"
  code: "#pragma once\n#include <iostream>\n#include <sstream>\n#include <string>\n\
    #include <vector>\n\n// Single line reading functions for multi-case & NO final\
    \ case notification inputs\n// Verified: https://codeforces.com/gym/100162/problem/G\n\
    std::vector<int> read_ints() {\n    std::string s;\n    std::getline(std::cin,\
    \ s);\n    if (s.empty()) return {};\n    std::stringstream ss(s);\n    std::vector<int>\
    \ ret;\n    while (!ss.eof()) {\n        int t;\n        ss >> t;\n        ret.push_back(t);\n\
    \    }\n    return ret;\n}\n\nstd::string read_str() {\n    std::string s;\n \
    \   std::getline(std::cin, s);\n    return s;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/readline.hpp
  requiredBy: []
  timestamp: '2022-01-09 00:24:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/readline.hpp
layout: document
title: "\u4E00\u884C\u5165\u529B"
---

標準入力で与えられる行数が不明の場合に使える標準入力．最終行では空の結果を返す．
