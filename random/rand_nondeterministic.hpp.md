---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/chromatic_number.test.cpp
    title: graph/test/chromatic_number.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"random/rand_nondeterministic.hpp\"\n#include <chrono>\n\
    #include <random>\n\nstruct rand_int_ {\n    using lint = long long;\n    std::mt19937\
    \ mt;\n    // rand_int_() : mt(42) {}\n    rand_int_() : mt(std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)\n\
    \    lint operator()(lint l, lint r) {\n        std::uniform_int_distribution<lint>\
    \ d(l, r - 1);\n        return d(mt);\n    }\n} rnd;\n"
  code: "#pragma once\n#include <chrono>\n#include <random>\n\nstruct rand_int_ {\n\
    \    using lint = long long;\n    std::mt19937 mt;\n    // rand_int_() : mt(42)\
    \ {}\n    rand_int_() : mt(std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)\n\
    \    lint operator()(lint l, lint r) {\n        std::uniform_int_distribution<lint>\
    \ d(l, r - 1);\n        return d(mt);\n    }\n} rnd;\n"
  dependsOn: []
  isVerificationFile: false
  path: random/rand_nondeterministic.hpp
  requiredBy: []
  timestamp: '2025-08-05 22:50:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/chromatic_number.test.cpp
documentation_of: random/rand_nondeterministic.hpp
layout: document
redirect_from:
- /library/random/rand_nondeterministic.hpp
- /library/random/rand_nondeterministic.hpp.html
title: random/rand_nondeterministic.hpp
---
