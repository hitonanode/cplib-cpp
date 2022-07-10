---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/run_length_encoding.hpp\"\n#include <string>\n\
    #include <utility>\n#include <vector>\n\n// Run length encoding\ntemplate <class\
    \ T> std::vector<std::pair<T, int>> run_length_encoding(const std::vector<T> &v)\
    \ {\n    std::vector<std::pair<T, int>> ret;\n    for (const T &x : v) {\n   \
    \     if (ret.empty() or ret.back().first != x) ret.emplace_back(x, 0);\n    \
    \    ++ret.back().second;\n    }\n    return ret;\n}\n\n// aabaacddd -> [(a, 2),\
    \ (b, 1), (a, 2), (c, 1), (d, 3)]\n// Each character in s must be char\nstd::vector<std::pair<char,\
    \ int>> run_length_encoding(const std::string &s) {\n    std::vector<char> tmp(s.begin(),\
    \ s.end());\n    return run_length_encoding<char>(tmp);\n}\n"
  code: "#pragma once\n#include <string>\n#include <utility>\n#include <vector>\n\n\
    // Run length encoding\ntemplate <class T> std::vector<std::pair<T, int>> run_length_encoding(const\
    \ std::vector<T> &v) {\n    std::vector<std::pair<T, int>> ret;\n    for (const\
    \ T &x : v) {\n        if (ret.empty() or ret.back().first != x) ret.emplace_back(x,\
    \ 0);\n        ++ret.back().second;\n    }\n    return ret;\n}\n\n// aabaacddd\
    \ -> [(a, 2), (b, 1), (a, 2), (c, 1), (d, 3)]\n// Each character in s must be\
    \ char\nstd::vector<std::pair<char, int>> run_length_encoding(const std::string\
    \ &s) {\n    std::vector<char> tmp(s.begin(), s.end());\n    return run_length_encoding<char>(tmp);\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/run_length_encoding.hpp
  requiredBy: []
  timestamp: '2022-07-10 23:01:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/run_length_encoding.hpp
layout: document
title: "Run length encoding \uFF08\u30E9\u30F3\u30EC\u30F3\u30B0\u30B9\u5727\u7E2E\
  \uFF0C\u9023\u9577\u5727\u7E2E\uFF09"
---

与えられた `std::vector<>` や `std::string` のインスタンスに対してランレングス圧縮を行う．

## 問題例

- [AtCoder Beginner Contest 259 C - XX to XXX](https://atcoder.jp/contests/abc259/tasks/abc259_c)
