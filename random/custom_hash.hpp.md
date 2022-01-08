---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - http://xorshift.di.unimi.it/splitmix64.c
    - https://codeforces.com/blog/entry/62393>
  bundledCode: "#line 2 \"random/custom_hash.hpp\"\n#include <chrono>\n#include <cstdlib>\n\
    using namespace std;\n\n// CUT begin\nstruct custom_hash {\n    // <https://codeforces.com/blog/entry/62393>\n\
    \    static uint64_t splitmix64(uint64_t x) {\n        // http://xorshift.di.unimi.it/splitmix64.c\n\
    \        x += 0x9e3779b97f4a7c15;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n\
    \    }\n\n    size_t operator()(uint64_t x) const {\n        static const uint64_t\
    \ FIXED_RANDOM =\n            std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return splitmix64(x + FIXED_RANDOM);\n    }\n};\n\n// Usage\n#include\
    \ <unordered_map>\nunordered_map<int, int, custom_hash> robust_unordered_map;\n\
    \n#include <ext/pb_ds/assoc_container.hpp>\nusing namespace __gnu_pbds;\ngp_hash_table<int,\
    \ null_type, custom_hash> robust_hash_table; // fast unordered_set / unordered_map\n"
  code: "#pragma once\n#include <chrono>\n#include <cstdlib>\nusing namespace std;\n\
    \n// CUT begin\nstruct custom_hash {\n    // <https://codeforces.com/blog/entry/62393>\n\
    \    static uint64_t splitmix64(uint64_t x) {\n        // http://xorshift.di.unimi.it/splitmix64.c\n\
    \        x += 0x9e3779b97f4a7c15;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n\
    \    }\n\n    size_t operator()(uint64_t x) const {\n        static const uint64_t\
    \ FIXED_RANDOM =\n            std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return splitmix64(x + FIXED_RANDOM);\n    }\n};\n\n// Usage\n#include\
    \ <unordered_map>\nunordered_map<int, int, custom_hash> robust_unordered_map;\n\
    \n#include <ext/pb_ds/assoc_container.hpp>\nusing namespace __gnu_pbds;\ngp_hash_table<int,\
    \ null_type, custom_hash> robust_hash_table; // fast unordered_set / unordered_map\n"
  dependsOn: []
  isVerificationFile: false
  path: random/custom_hash.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: random/custom_hash.hpp
layout: document
redirect_from:
- /library/random/custom_hash.hpp
- /library/random/custom_hash.hpp.html
title: random/custom_hash.hpp
---
