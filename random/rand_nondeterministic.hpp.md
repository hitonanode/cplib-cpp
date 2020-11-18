---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: linear_algebra_matrix/det_of_sparse_matrix.hpp
    title: linear_algebra_matrix/det_of_sparse_matrix.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
    title: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
  - icon: ':x:'
    path: random/test/rolling_hash.test.cpp
    title: random/test/rolling_hash.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"random/rand_nondeterministic.hpp\"\n#include <chrono>\n\
    #include <random>\nusing namespace std;\n\n// CUT begin\nstruct rand_int_ {\n\
    \    using lint = long long;\n    mt19937 mt;\n    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)\n\
    \    lint operator()(lint l, lint r) {\n        uniform_int_distribution<lint>\
    \ d(l, r - 1);\n        return d(mt);\n    }\n} rnd;\n"
  code: "#pragma once\n#include <chrono>\n#include <random>\nusing namespace std;\n\
    \n// CUT begin\nstruct rand_int_ {\n    using lint = long long;\n    mt19937 mt;\n\
    \    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)\n\
    \    lint operator()(lint l, lint r) {\n        uniform_int_distribution<lint>\
    \ d(l, r - 1);\n        return d(mt);\n    }\n} rnd;\n"
  dependsOn: []
  isVerificationFile: false
  path: random/rand_nondeterministic.hpp
  requiredBy:
  - linear_algebra_matrix/det_of_sparse_matrix.hpp
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
  - random/test/rolling_hash.test.cpp
documentation_of: random/rand_nondeterministic.hpp
layout: document
redirect_from:
- /library/random/rand_nondeterministic.hpp
- /library/random/rand_nondeterministic.hpp.html
title: random/rand_nondeterministic.hpp
---
