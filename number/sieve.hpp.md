---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: number/cyclotomic_polynomials.hpp
    title: "Cyclotomic polynomials \uFF08\u5186\u5206\u591A\u9805\u5F0F\uFF09"
  - icon: ':warning:'
    path: number/zeta_moebius_transform.hpp
    title: number/zeta_moebius_transform.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
    title: formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
    title: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/enumerate_primes.test.cpp
    title: number/test/enumerate_primes.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/gen_primes.test.cpp
    title: number/test/gen_primes.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/prime_factorization.test.cpp
    title: number/test/prime_factorization.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://37zigen.com/linear-sieve/
    - https://cp-algorithms.com/algebra/prime-sieve-linear.html
    - https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt
    - https://oeis.org/A002182/list
    - https://oeis.org/A008683
  bundledCode: "#line 2 \"number/sieve.hpp\"\n#include <cassert>\n#include <map>\n\
    #include <vector>\n\n// CUT begin\n// Linear sieve algorithm for fast prime factorization\n\
    // Complexity: O(N) time, O(N) space:\n// - MAXN = 10^7:  ~44 MB,  80~100 ms (Codeforces\
    \ / AtCoder GCC, C++17)\n// - MAXN = 10^8: ~435 MB, 810~980 ms (Codeforces / AtCoder\
    \ GCC, C++17)\n// Reference:\n// [1] D. Gries, J. Misra, \"A Linear Sieve Algorithm\
    \ for Finding Prime Numbers,\"\n//     Communications of the ACM, 21(12), 999-1003,\
    \ 1978.\n// - https://cp-algorithms.com/algebra/prime-sieve-linear.html\n// -\
    \ https://37zigen.com/linear-sieve/\nstruct Sieve {\n    std::vector<int> min_factor;\n\
    \    std::vector<int> primes;\n    Sieve(int MAXN) : min_factor(MAXN + 1) {\n\
    \        for (int d = 2; d <= MAXN; d++) {\n            if (!min_factor[d]) {\n\
    \                min_factor[d] = d;\n                primes.emplace_back(d);\n\
    \            }\n            for (const auto &p : primes) {\n                if\
    \ (p > min_factor[d] or d * p > MAXN) break;\n                min_factor[d * p]\
    \ = p;\n            }\n        }\n    }\n    // Prime factorization for 1 <= x\
    \ <= MAXN^2\n    // Complexity: O(log x)           (x <= MAXN)\n    //       \
    \      O(MAXN / log MAXN) (MAXN < x <= MAXN^2)\n    template <typename T> std::map<T,\
    \ int> factorize(T x) {\n        std::map<T, int> ret;\n        assert(x > 0 and\
    \ x <= ((long long)min_factor.size() - 1) * ((long long)min_factor.size() - 1));\n\
    \        for (const auto &p : primes) {\n            if (x < T(min_factor.size()))\
    \ break;\n            while (!(x % p)) x /= p, ret[p]++;\n        }\n        if\
    \ (x >= T(min_factor.size())) ret[x]++, x = 1;\n        while (x > 1) ret[min_factor[x]]++,\
    \ x /= min_factor[x];\n        return ret;\n    }\n    // Enumerate divisors of\
    \ 1 <= x <= MAXN^2\n    // Be careful of highly composite numbers https://oeis.org/A002182/list\
    \ https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt\n    //\
    \ (n, (# of div. of n)): 45360->100, 735134400(<1e9)->1344, 963761198400(<1e12)->6720\n\
    \    template <typename T> std::vector<T> divisors(T x) {\n        std::vector<T>\
    \ ret{1};\n        for (const auto p : factorize(x)) {\n            int n = ret.size();\n\
    \            for (int i = 0; i < n; i++) {\n                for (T a = 1, d =\
    \ 1; d <= p.second; d++) {\n                    a *= p.first;\n              \
    \      ret.push_back(ret[i] * a);\n                }\n            }\n        }\n\
    \        return ret; // NOT sorted\n    }\n    // Moebius function Table, (-1)^{#\
    \ of different prime factors} for square-free x\n    // return: [0=>0, 1=>1, 2=>-1,\
    \ 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0, ...] https://oeis.org/A008683\n    std::vector<int>\
    \ GenerateMoebiusFunctionTable() {\n        std::vector<int> ret(min_factor.size());\n\
    \        for (unsigned i = 1; i < min_factor.size(); i++) {\n            if (i\
    \ == 1)\n                ret[i] = 1;\n            else if ((i / min_factor[i])\
    \ % min_factor[i] == 0)\n                ret[i] = 0;\n            else\n     \
    \           ret[i] = -ret[i / min_factor[i]];\n        }\n        return ret;\n\
    \    }\n    // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)\n    // Note: **0^0\
    \ == 1**\n    template <typename MODINT> std::vector<MODINT> enumerate_kth_pows(long\
    \ long K, int nmax) {\n        assert(nmax < int(min_factor.size()));\n      \
    \  assert(K >= 0);\n        if (K == 0) return std::vector<MODINT>(nmax + 1, 1);\n\
    \        std::vector<MODINT> ret(nmax + 1);\n        ret[0] = 0, ret[1] = 1;\n\
    \        for (int n = 2; n <= nmax; n++) {\n            if (min_factor[n] == n)\
    \ {\n                ret[n] = MODINT(n).pow(K);\n            } else {\n      \
    \          ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];\n           \
    \ }\n        }\n        return ret;\n    }\n};\n// Sieve sieve(1 << 15);  // (can\
    \ factorize n <= 10^9)\n"
  code: "#pragma once\n#include <cassert>\n#include <map>\n#include <vector>\n\n//\
    \ CUT begin\n// Linear sieve algorithm for fast prime factorization\n// Complexity:\
    \ O(N) time, O(N) space:\n// - MAXN = 10^7:  ~44 MB,  80~100 ms (Codeforces /\
    \ AtCoder GCC, C++17)\n// - MAXN = 10^8: ~435 MB, 810~980 ms (Codeforces / AtCoder\
    \ GCC, C++17)\n// Reference:\n// [1] D. Gries, J. Misra, \"A Linear Sieve Algorithm\
    \ for Finding Prime Numbers,\"\n//     Communications of the ACM, 21(12), 999-1003,\
    \ 1978.\n// - https://cp-algorithms.com/algebra/prime-sieve-linear.html\n// -\
    \ https://37zigen.com/linear-sieve/\nstruct Sieve {\n    std::vector<int> min_factor;\n\
    \    std::vector<int> primes;\n    Sieve(int MAXN) : min_factor(MAXN + 1) {\n\
    \        for (int d = 2; d <= MAXN; d++) {\n            if (!min_factor[d]) {\n\
    \                min_factor[d] = d;\n                primes.emplace_back(d);\n\
    \            }\n            for (const auto &p : primes) {\n                if\
    \ (p > min_factor[d] or d * p > MAXN) break;\n                min_factor[d * p]\
    \ = p;\n            }\n        }\n    }\n    // Prime factorization for 1 <= x\
    \ <= MAXN^2\n    // Complexity: O(log x)           (x <= MAXN)\n    //       \
    \      O(MAXN / log MAXN) (MAXN < x <= MAXN^2)\n    template <typename T> std::map<T,\
    \ int> factorize(T x) {\n        std::map<T, int> ret;\n        assert(x > 0 and\
    \ x <= ((long long)min_factor.size() - 1) * ((long long)min_factor.size() - 1));\n\
    \        for (const auto &p : primes) {\n            if (x < T(min_factor.size()))\
    \ break;\n            while (!(x % p)) x /= p, ret[p]++;\n        }\n        if\
    \ (x >= T(min_factor.size())) ret[x]++, x = 1;\n        while (x > 1) ret[min_factor[x]]++,\
    \ x /= min_factor[x];\n        return ret;\n    }\n    // Enumerate divisors of\
    \ 1 <= x <= MAXN^2\n    // Be careful of highly composite numbers https://oeis.org/A002182/list\
    \ https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt\n    //\
    \ (n, (# of div. of n)): 45360->100, 735134400(<1e9)->1344, 963761198400(<1e12)->6720\n\
    \    template <typename T> std::vector<T> divisors(T x) {\n        std::vector<T>\
    \ ret{1};\n        for (const auto p : factorize(x)) {\n            int n = ret.size();\n\
    \            for (int i = 0; i < n; i++) {\n                for (T a = 1, d =\
    \ 1; d <= p.second; d++) {\n                    a *= p.first;\n              \
    \      ret.push_back(ret[i] * a);\n                }\n            }\n        }\n\
    \        return ret; // NOT sorted\n    }\n    // Moebius function Table, (-1)^{#\
    \ of different prime factors} for square-free x\n    // return: [0=>0, 1=>1, 2=>-1,\
    \ 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0, ...] https://oeis.org/A008683\n    std::vector<int>\
    \ GenerateMoebiusFunctionTable() {\n        std::vector<int> ret(min_factor.size());\n\
    \        for (unsigned i = 1; i < min_factor.size(); i++) {\n            if (i\
    \ == 1)\n                ret[i] = 1;\n            else if ((i / min_factor[i])\
    \ % min_factor[i] == 0)\n                ret[i] = 0;\n            else\n     \
    \           ret[i] = -ret[i / min_factor[i]];\n        }\n        return ret;\n\
    \    }\n    // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)\n    // Note: **0^0\
    \ == 1**\n    template <typename MODINT> std::vector<MODINT> enumerate_kth_pows(long\
    \ long K, int nmax) {\n        assert(nmax < int(min_factor.size()));\n      \
    \  assert(K >= 0);\n        if (K == 0) return std::vector<MODINT>(nmax + 1, 1);\n\
    \        std::vector<MODINT> ret(nmax + 1);\n        ret[0] = 0, ret[1] = 1;\n\
    \        for (int n = 2; n <= nmax; n++) {\n            if (min_factor[n] == n)\
    \ {\n                ret[n] = MODINT(n).pow(K);\n            } else {\n      \
    \          ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];\n           \
    \ }\n        }\n        return ret;\n    }\n};\n// Sieve sieve(1 << 15);  // (can\
    \ factorize n <= 10^9)\n"
  dependsOn: []
  isVerificationFile: false
  path: number/sieve.hpp
  requiredBy:
  - number/cyclotomic_polynomials.hpp
  - number/zeta_moebius_transform.hpp
  timestamp: '2021-05-03 18:16:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/gen_primes.test.cpp
  - number/test/prime_factorization.test.cpp
  - number/test/enumerate_primes.test.cpp
  - formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
  - formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
documentation_of: number/sieve.hpp
layout: document
title: "Linear sieve \uFF08\u7DDA\u5F62\u7BE9\uFF09"
---

線形篩．構築 $O(N)$．自然数 $K \leq N$ の素因数分解は $O(\log K)$．

## 使用例

```cpp
Sieve sieve(1 << 20); // 2^20 以下の全素数や，各整数の最小素因数を計算．

// 素数判定
bool is_prime = (sieve.min_factor[x] == x);

// 素因数分解
map<lint, int> mp = sieve.factorize(x);

// 約数列挙（昇順とは限らない）
vector<lint> divs = sieve.divisors(x);

// i = 0, 1, ..., n について i^k を格納した配列を生成． O(n)
vector vs = enumerate_kth_pows<ModInt<998244353>>(3, 10); // v = [0,1,8,27,64,125,216,343,512,729,1000,]
```

## 文献・リンク

- [1] D. Gries, J. Misra, "A Linear Sieve Algorithm for Finding Prime Numbers," Communications of the ACM, 21(12), 999-1003, 1978.
- https://cp-algorithms.com/algebra/prime-sieve-linear.html
- https://37zigen.com/linear-sieve/
