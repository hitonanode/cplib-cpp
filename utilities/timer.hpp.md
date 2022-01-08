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
  bundledCode: "#line 2 \"utilities/timer.hpp\"\n#include <chrono>\n\n// CUT begin\n\
    auto START = std::chrono::system_clock::now();\nint64_t spent_ms =\n    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()\
    \ - START)\n        .count();\n"
  code: "#pragma once\n#include <chrono>\n\n// CUT begin\nauto START = std::chrono::system_clock::now();\n\
    int64_t spent_ms =\n    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()\
    \ - START)\n        .count();\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/timer.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/timer.hpp
layout: document
redirect_from:
- /library/utilities/timer.hpp
- /library/utilities/timer.hpp.html
title: utilities/timer.hpp
---
