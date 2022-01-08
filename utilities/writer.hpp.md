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
  bundledCode: "#line 2 \"utilities/writer.hpp\"\n#include <cstdio>\n\ntemplate <typename\
    \ T> void wt_integer(T x, char delim) {\n    if (x == 0) {\n        putchar('0'),\
    \ putchar(delim);\n        return;\n    }\n    if (x < 0) putchar('-'), x = -x;\n\
    \    static char cache[20];\n    char *head = cache;\n    while (x) *head = '0'\
    \ + x % 10, head++, x /= 10;\n    while (head != cache) putchar(*(--head));\n\
    \    putchar(delim);\n}\n"
  code: "#pragma once\n#include <cstdio>\n\ntemplate <typename T> void wt_integer(T\
    \ x, char delim) {\n    if (x == 0) {\n        putchar('0'), putchar(delim);\n\
    \        return;\n    }\n    if (x < 0) putchar('-'), x = -x;\n    static char\
    \ cache[20];\n    char *head = cache;\n    while (x) *head = '0' + x % 10, head++,\
    \ x /= 10;\n    while (head != cache) putchar(*(--head));\n    putchar(delim);\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/writer.hpp
  requiredBy: []
  timestamp: '2022-01-09 00:24:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/writer.hpp
layout: document
title: "\u6A19\u6E96\u51FA\u529B"
---

おまじないつきの `std::cout` 等より若干高速な整数標準出力．
