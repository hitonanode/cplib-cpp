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
  bundledCode: '#line 2 "utilities/timer.hpp"

    #include <chrono>


    // CUT begin

    auto START = std::chrono::system_clock::now();

    int64_t spent_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
    - START).count();

    '
  code: '#pragma once

    #include <chrono>


    // CUT begin

    auto START = std::chrono::system_clock::now();

    int64_t spent_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
    - START).count();

    '
  dependsOn: []
  isVerificationFile: false
  path: utilities/timer.hpp
  requiredBy: []
  timestamp: '2020-09-30 21:22:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/timer.hpp
layout: document
redirect_from:
- /library/utilities/timer.hpp
- /library/utilities/timer.hpp.html
title: utilities/timer.hpp
---
