---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/bs_sieve.test.cpp
    title: number/test/bs_sieve.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/bs_sieve.hpp\"\n#include <algorithm>\n#include <bitset>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Complexity: O(N log\
    \ log N):\n// - N = 10^7:  8 /  6 MB,   62 /  81 ms (Codeforces / AtCoder, GCC\
    \ C++17)\n// - N = 10^8: 61 / 44 MB, 1481 / 866 ms (Codeforces / AtCoder, GCC\
    \ C++17)\ntemplate <int LIMN> struct BitsetSieve {\n    std::vector<int> primes;\n\
    \    std::bitset<LIMN + 1> is_prime;\n    const int maxN;\n    BitsetSieve(int\
    \ MAXN = LIMN) : maxN(MAXN) {\n        is_prime.set();\n        is_prime.reset(0),\
    \ is_prime.reset(1);\n        for (int p = 2; p <= MAXN; p++) {\n            if\
    \ (is_prime[p]) {\n                primes.push_back(p);\n                for (int\
    \ j = p * 2; j <= MAXN; j += p) is_prime[j] = 0;\n            }\n        }\n \
    \   }\n    // Count primes less than or equal to x\n    int prime_counting(int\
    \ x) {\n        assert(x <= maxN);\n        return std::distance(primes.begin(),\
    \ std::upper_bound(primes.begin(), primes.end(), x));\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <bitset>\n#include <cassert>\n\
    #include <vector>\n\n// CUT begin\n// Complexity: O(N log log N):\n// - N = 10^7:\
    \  8 /  6 MB,   62 /  81 ms (Codeforces / AtCoder, GCC C++17)\n// - N = 10^8:\
    \ 61 / 44 MB, 1481 / 866 ms (Codeforces / AtCoder, GCC C++17)\ntemplate <int LIMN>\
    \ struct BitsetSieve {\n    std::vector<int> primes;\n    std::bitset<LIMN + 1>\
    \ is_prime;\n    const int maxN;\n    BitsetSieve(int MAXN = LIMN) : maxN(MAXN)\
    \ {\n        is_prime.set();\n        is_prime.reset(0), is_prime.reset(1);\n\
    \        for (int p = 2; p <= MAXN; p++) {\n            if (is_prime[p]) {\n \
    \               primes.push_back(p);\n                for (int j = p * 2; j <=\
    \ MAXN; j += p) is_prime[j] = 0;\n            }\n        }\n    }\n    // Count\
    \ primes less than or equal to x\n    int prime_counting(int x) {\n        assert(x\
    \ <= maxN);\n        return std::distance(primes.begin(), std::upper_bound(primes.begin(),\
    \ primes.end(), x));\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: number/bs_sieve.hpp
  requiredBy: []
  timestamp: '2021-01-12 02:12:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/bs_sieve.test.cpp
documentation_of: number/bs_sieve.hpp
layout: document
redirect_from:
- /library/number/bs_sieve.hpp
- /library/number/bs_sieve.hpp.html
title: number/bs_sieve.hpp
---
