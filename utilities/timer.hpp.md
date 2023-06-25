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
  bundledCode: "#line 2 \"utilities/timer.hpp\"\n#include <chrono>\n\nclass timer_\
    \ {\n    std::chrono::system_clock::time_point start_;\n\npublic:\n    timer_()\
    \ : start_(now()) {}\n\n    static std::chrono::system_clock::time_point now()\
    \ { return std::chrono::system_clock::now(); }\n\n    int spent_ms() const {\n\
    \        auto diff = now() - start_;\n        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();\n\
    \    }\n} timer;\n"
  code: "#pragma once\n#include <chrono>\n\nclass timer_ {\n    std::chrono::system_clock::time_point\
    \ start_;\n\npublic:\n    timer_() : start_(now()) {}\n\n    static std::chrono::system_clock::time_point\
    \ now() { return std::chrono::system_clock::now(); }\n\n    int spent_ms() const\
    \ {\n        auto diff = now() - start_;\n        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();\n\
    \    }\n} timer;\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/timer.hpp
  requiredBy: []
  timestamp: '2023-06-26 00:35:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/timer.hpp
layout: document
redirect_from:
- /library/utilities/timer.hpp
- /library/utilities/timer.hpp.html
title: utilities/timer.hpp
---
