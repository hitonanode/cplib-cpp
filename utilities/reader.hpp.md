---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp
    title: combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/matrix_product.test.cpp
    title: linear_algebra_matrix/test/matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/sa_count_keyword.reader.test.cpp
    title: string/test/sa_count_keyword.reader.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/reader.hpp\"\n#include <cstdio>\n#include <string>\n\
    \n// CUT begin\ntemplate <typename T> T rd_integer() {\n    T ret = 0;\n    bool\
    \ minus = false;\n\n    char c = getchar_unlocked();\n    while (!isdigit(c))\
    \ minus |= (c == '-'), c = getchar_unlocked();\n    while (isdigit(c)) ret = (ret\
    \ << 1) + (ret << 3) + (c ^ 48), c = getchar_unlocked();\n\n    return minus ?\
    \ -ret : ret;\n}\nint rdi() { return rd_integer<int>(); }\nlong long rdll() {\
    \ return rd_integer<long long>(); }\nstd::string rdstr() {\n    std::string ret;\n\
    \    char c = getchar_unlocked();\n    while (!isgraph(c)) c = getchar_unlocked();\n\
    \    while (isgraph(c)) ret += c, c = getchar_unlocked();\n    return ret;\n}\n"
  code: "#pragma once\n#include <cstdio>\n#include <string>\n\n// CUT begin\ntemplate\
    \ <typename T> T rd_integer() {\n    T ret = 0;\n    bool minus = false;\n\n \
    \   char c = getchar_unlocked();\n    while (!isdigit(c)) minus |= (c == '-'),\
    \ c = getchar_unlocked();\n    while (isdigit(c)) ret = (ret << 1) + (ret << 3)\
    \ + (c ^ 48), c = getchar_unlocked();\n\n    return minus ? -ret : ret;\n}\nint\
    \ rdi() { return rd_integer<int>(); }\nlong long rdll() { return rd_integer<long\
    \ long>(); }\nstd::string rdstr() {\n    std::string ret;\n    char c = getchar_unlocked();\n\
    \    while (!isgraph(c)) c = getchar_unlocked();\n    while (isgraph(c)) ret +=\
    \ c, c = getchar_unlocked();\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/reader.hpp
  requiredBy: []
  timestamp: '2021-08-01 21:42:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/sa_count_keyword.reader.test.cpp
  - linear_algebra_matrix/test/matrix_product.test.cpp
  - combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp
documentation_of: utilities/reader.hpp
layout: document
title: "\u9AD8\u901F\u6A19\u6E96\u5165\u529B"
---

`std::cin` より高速な標準入力．

```cpp
int n = rdi();
long long m = rdll();
string s = rdstr();
```
