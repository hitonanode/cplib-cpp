---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: number/cyclotomic_polynomials.hpp
    title: number/cyclotomic_polynomials.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/gen_primes.test.cpp
    title: number/test/gen_primes.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/prime_factorization.test.cpp
    title: number/test/prime_factorization.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"number/eratosthenes.hpp\"\n#include <cassert>\n#include\
    \ <map>\n#include <numeric>\n#include <vector>\n\n// CUT begin\n// Sieve of Eratosthenes\n\
    // (*this)[i] = (divisor of i, greater than 1)\n// Example: [0, 1, 2, 3, 2, 5,\
    \ 3, 7, 2, 3, 2, 11, ...]\n// Complexity: Space O(MAXN), Time (construction) O(MAXNloglogMAXN)\n\
    struct SieveOfEratosthenes : std::vector<int>\n{\n    std::vector<int> primes;\n\
    \    SieveOfEratosthenes(int MAXN) : std::vector<int>(MAXN + 1) {\n        std::iota(begin(),\
    \ end(), 0);\n        for (int i = 2; i <= MAXN; i++) {\n            if ((*this)[i]\
    \ == i) {\n                primes.push_back(i);\n                for (int j =\
    \ i; j <= MAXN; j += i) (*this)[j] = i;\n            }\n        }\n    }\n   \
    \ using T = long long int;\n    // Prime factorization for x <= MAXN^2\n    //\
    \ Complexity: O(log x)          (x <= MAXN)\n    //             O(MAXN / logMAXN)\
    \ (MAXN < x <= MAXN^2)\n    std::map<T, int> Factorize(T x) {\n        assert(x\
    \ <= 1LL * (int(size()) - 1) * (int(size()) - 1));\n        std::map<T, int> ret;\n\
    \        if (x < int(size())) {\n            while (x > 1) {\n               \
    \ ret[(*this)[x]]++;\n                x /= (*this)[x];\n            }\n      \
    \  }\n        else {\n            for (auto p : primes) {\n                while\
    \ (!(x % p)) x /= p, ret[p]++;\n                if (x == 1) break;\n         \
    \   }\n            if (x > 1) ret[x]++;\n        }\n        return ret;\n    }\n\
    \    std::vector<T> Divisors(T x) {\n        std::vector<T> ret{1};\n        for\
    \ (auto p : Factorize(x)) {\n            int n = ret.size();\n            for\
    \ (int i = 0; i < n; i++) {\n                for (T a = 1, d = 1; d <= p.second;\
    \ d++) {\n                    a *= p.first;\n                    ret.push_back(ret[i]\
    \ * a);\n                }\n            }\n        }\n        return ret; // Not\
    \ sorted\n    }\n    // Moebius function Table\n    // return: [0=>0, 1=>1, 2=>-1,\
    \ 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0, ...]\n    std::vector<int> GenerateMoebiusFunctionTable()\
    \ {\n        std::vector<int> ret(size());\n        for (int i = 1; i < int(size());\
    \ i++) {\n            if (i == 1) ret[i] = 1;\n            else if ((i / (*this)[i])\
    \ % (*this)[i] == 0) ret[i] = 0;\n            else ret[i] = -ret[i / (*this)[i]];\n\
    \        }\n        return ret;\n    }\n};\n// SieveOfEratosthenes sieve(100000);\n"
  code: "#pragma once\n#include <cassert>\n#include <map>\n#include <numeric>\n#include\
    \ <vector>\n\n// CUT begin\n// Sieve of Eratosthenes\n// (*this)[i] = (divisor\
    \ of i, greater than 1)\n// Example: [0, 1, 2, 3, 2, 5, 3, 7, 2, 3, 2, 11, ...]\n\
    // Complexity: Space O(MAXN), Time (construction) O(MAXNloglogMAXN)\nstruct SieveOfEratosthenes\
    \ : std::vector<int>\n{\n    std::vector<int> primes;\n    SieveOfEratosthenes(int\
    \ MAXN) : std::vector<int>(MAXN + 1) {\n        std::iota(begin(), end(), 0);\n\
    \        for (int i = 2; i <= MAXN; i++) {\n            if ((*this)[i] == i) {\n\
    \                primes.push_back(i);\n                for (int j = i; j <= MAXN;\
    \ j += i) (*this)[j] = i;\n            }\n        }\n    }\n    using T = long\
    \ long int;\n    // Prime factorization for x <= MAXN^2\n    // Complexity: O(log\
    \ x)          (x <= MAXN)\n    //             O(MAXN / logMAXN) (MAXN < x <= MAXN^2)\n\
    \    std::map<T, int> Factorize(T x) {\n        assert(x <= 1LL * (int(size())\
    \ - 1) * (int(size()) - 1));\n        std::map<T, int> ret;\n        if (x < int(size()))\
    \ {\n            while (x > 1) {\n                ret[(*this)[x]]++;\n       \
    \         x /= (*this)[x];\n            }\n        }\n        else {\n       \
    \     for (auto p : primes) {\n                while (!(x % p)) x /= p, ret[p]++;\n\
    \                if (x == 1) break;\n            }\n            if (x > 1) ret[x]++;\n\
    \        }\n        return ret;\n    }\n    std::vector<T> Divisors(T x) {\n \
    \       std::vector<T> ret{1};\n        for (auto p : Factorize(x)) {\n      \
    \      int n = ret.size();\n            for (int i = 0; i < n; i++) {\n      \
    \          for (T a = 1, d = 1; d <= p.second; d++) {\n                    a *=\
    \ p.first;\n                    ret.push_back(ret[i] * a);\n                }\n\
    \            }\n        }\n        return ret; // Not sorted\n    }\n    // Moebius\
    \ function Table\n    // return: [0=>0, 1=>1, 2=>-1, 3=>-1, 4=>0, 5=>-1, 6=>1,\
    \ 7=>-1, 8=>0, ...]\n    std::vector<int> GenerateMoebiusFunctionTable() {\n \
    \       std::vector<int> ret(size());\n        for (int i = 1; i < int(size());\
    \ i++) {\n            if (i == 1) ret[i] = 1;\n            else if ((i / (*this)[i])\
    \ % (*this)[i] == 0) ret[i] = 0;\n            else ret[i] = -ret[i / (*this)[i]];\n\
    \        }\n        return ret;\n    }\n};\n// SieveOfEratosthenes sieve(100000);\n"
  dependsOn: []
  isVerificationFile: false
  path: number/eratosthenes.hpp
  requiredBy:
  - number/cyclotomic_polynomials.hpp
  timestamp: '2020-04-04 22:42:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/gen_primes.test.cpp
  - number/test/prime_factorization.test.cpp
documentation_of: number/eratosthenes.hpp
layout: document
redirect_from:
- /library/number/eratosthenes.hpp
- /library/number/eratosthenes.hpp.html
title: number/eratosthenes.hpp
---
