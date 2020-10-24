---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: '#line 2 "random/shuffle_container.hpp"

    #include <algorithm>

    #include <chrono>

    #include <random>


    // CUT begin

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    // std::shuffle(v.begin(), v.end(), rng);

    '
  code: '#pragma once

    #include <algorithm>

    #include <chrono>

    #include <random>


    // CUT begin

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    // std::shuffle(v.begin(), v.end(), rng);

    '
  dependsOn: []
  isVerificationFile: false
  path: random/shuffle_container.hpp
  requiredBy: []
  timestamp: '2020-10-17 02:47:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: random/shuffle_container.hpp
layout: document
redirect_from:
- /library/random/shuffle_container.hpp
- /library/random/shuffle_container.hpp.html
title: random/shuffle_container.hpp
---
