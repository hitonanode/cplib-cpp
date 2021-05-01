---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/sieve.hpp
    title: "Linear sieve \uFF08\u7DDA\u5F62\u7BE9\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
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
    \    }\n    // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)\n    template <typename\
    \ MODINT> std::vector<MODINT> enumerate_kth_pows(long long K, int nmax) {\n  \
    \      assert(nmax < int(min_factor.size()));\n        std::vector<MODINT> ret(nmax\
    \ + 1);\n        ret[0] = 0, ret[1] = 1;\n        for (int n = 2; n <= nmax; n++)\
    \ {\n            if (min_factor[n] == n) {\n                ret[n] = MODINT(n).pow(K);\n\
    \            } else {\n                ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];\n\
    \            }\n        }\n        return ret;\n    }\n};\n// Sieve sieve(1 <<\
    \ 15);  // (can factorize n <= 10^9)\n#line 4 \"number/cyclotomic_polynomials.hpp\"\
    \n\n// CUT begin\n// cyclotomic polynominals : \u5186\u5206\u591A\u9805\u5F0F\n\
    // ret[i][j] = [x^j]\\Phi_i(x) for i <= Nmax, which are known to be integers\n\
    std::vector<std::vector<int>> cyclotomic_polynomials(int Nmax) {\n    std::vector<int>\
    \ moebius = Sieve(Nmax).GenerateMoebiusFunctionTable();\n    std::vector<std::vector<int>>\
    \ ret(Nmax + 1);\n    auto multiply = [](const std::vector<int> &a, const std::vector<int>\
    \ &b) { // a * b\n        std::vector<int> ret(int(a.size() + b.size()) - 1);\n\
    \        for (size_t i = 0; i < a.size(); i++)\n            for (size_t j = 0;\
    \ j < b.size(); j++) { ret[i + j] += a[i] * b[j]; }\n        return ret;\n   \
    \ };\n    auto divide = [](std::vector<int> a, const std::vector<int> &b) { //\
    \ a / b, abs(b[0]) = 1\n        std::vector<int> ret(int(a.size()) - int(b.size())\
    \ + 1);\n        for (size_t i = 0; i < ret.size(); i++) {\n            ret[i]\
    \ = a[i] / b[0];\n            for (size_t j = 0; j < b.size(); j++) a[i + j] -=\
    \ ret[i] * b[j];\n        }\n        while (ret.size() and !ret.back()) ret.pop_back();\n\
    \        return ret;\n    };\n\n    for (int n = 0; n <= Nmax; n++) {\n      \
    \  std::vector<std::vector<int>> num, den;\n        for (int d = 1; d <= n; d++)\n\
    \            if (n % d == 0 and moebius[d]) {\n                std::vector<int>\
    \ r(n / d + 1);\n                r[0] = -1, r.back() = 1;\n                (moebius[d]\
    \ > 0 ? num : den).push_back(r);\n            }\n        std::vector<int> phi{1};\n\
    \        for (auto v : num) phi = multiply(phi, v);\n        for (auto v : den)\
    \ phi = divide(phi, v);\n        ret[n] = phi;\n    }\n    return ret;\n}\n"
  code: "#pragma once\n#include \"sieve.hpp\"\n#include <vector>\n\n// CUT begin\n\
    // cyclotomic polynominals : \u5186\u5206\u591A\u9805\u5F0F\n// ret[i][j] = [x^j]\\\
    Phi_i(x) for i <= Nmax, which are known to be integers\nstd::vector<std::vector<int>>\
    \ cyclotomic_polynomials(int Nmax) {\n    std::vector<int> moebius = Sieve(Nmax).GenerateMoebiusFunctionTable();\n\
    \    std::vector<std::vector<int>> ret(Nmax + 1);\n    auto multiply = [](const\
    \ std::vector<int> &a, const std::vector<int> &b) { // a * b\n        std::vector<int>\
    \ ret(int(a.size() + b.size()) - 1);\n        for (size_t i = 0; i < a.size();\
    \ i++)\n            for (size_t j = 0; j < b.size(); j++) { ret[i + j] += a[i]\
    \ * b[j]; }\n        return ret;\n    };\n    auto divide = [](std::vector<int>\
    \ a, const std::vector<int> &b) { // a / b, abs(b[0]) = 1\n        std::vector<int>\
    \ ret(int(a.size()) - int(b.size()) + 1);\n        for (size_t i = 0; i < ret.size();\
    \ i++) {\n            ret[i] = a[i] / b[0];\n            for (size_t j = 0; j\
    \ < b.size(); j++) a[i + j] -= ret[i] * b[j];\n        }\n        while (ret.size()\
    \ and !ret.back()) ret.pop_back();\n        return ret;\n    };\n\n    for (int\
    \ n = 0; n <= Nmax; n++) {\n        std::vector<std::vector<int>> num, den;\n\
    \        for (int d = 1; d <= n; d++)\n            if (n % d == 0 and moebius[d])\
    \ {\n                std::vector<int> r(n / d + 1);\n                r[0] = -1,\
    \ r.back() = 1;\n                (moebius[d] > 0 ? num : den).push_back(r);\n\
    \            }\n        std::vector<int> phi{1};\n        for (auto v : num) phi\
    \ = multiply(phi, v);\n        for (auto v : den) phi = divide(phi, v);\n    \
    \    ret[n] = phi;\n    }\n    return ret;\n}\n"
  dependsOn:
  - number/sieve.hpp
  isVerificationFile: false
  path: number/cyclotomic_polynomials.hpp
  requiredBy: []
  timestamp: '2021-05-01 20:07:58+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number/cyclotomic_polynomials.hpp
layout: document
title: "Cyclotomic polynomials \uFF08\u5186\u5206\u591A\u9805\u5F0F\uFF09"
---

## できること

円分多項式（[Wikipedia (en)](https://en.wikipedia.org/wiki/Cyclotomic_polynomial)）の係数を愚直に計算

## Definition

$\displaystyle
\Phi_n (x) := \prod_{1 \leq k \leq n, gcd(k, n) = 1} \left( x - e^{2 \mathrm{i} \pi k / n} \right)
$

## 使用例

``` cpp
vector<vector<int>> Phi = cyclotomic_polynomials(120); // Phi[i][j] = [x^j]Phi_i(x) for i <= 120
```

- Complexity: $O(n^2)$
- All coefficients are known to be "small" integers.

## 等式

- $\prod_{d \mid n} \Phi_d (x) = x^n - 1$
- $\Phi_n (x) = \prod_{d \mid n} \left(x^{n / d} - 1 \right) ^ {\mu(d)}$
- $\Phi_p (x) = 1 + x + \ldots + x^{p - 1} \ (p : \text{prime})$

## 問題例

- SRM 776 Div.1 Hard
