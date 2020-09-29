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

    #include <random>


    // CUT begin

    std::random_device seed_gen;

    std::mt19937 engine(seed_gen());

    // std::shuffle(v.begin(), v.end(), engine);

    '
  code: '#pragma once

    #include <algorithm>

    #include <random>


    // CUT begin

    std::random_device seed_gen;

    std::mt19937 engine(seed_gen());

    // std::shuffle(v.begin(), v.end(), engine);

    '
  dependsOn: []
  isVerificationFile: false
  path: random/shuffle_container.hpp
  requiredBy: []
  timestamp: '2020-09-29 20:43:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: random/shuffle_container.hpp
layout: document
redirect_from:
- /library/random/shuffle_container.hpp
- /library/random/shuffle_container.hpp.html
title: random/shuffle_container.hpp
---
