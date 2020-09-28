---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/eratosthenes.hpp
    title: number/eratosthenes.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
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
    \        }\n        return ret;\n    }\n};\n// SieveOfEratosthenes sieve(100000);\n\
    #line 4 \"number/cyclotomic_polynomials.hpp\"\n\n// CUT begin\n// cyclotomic polynominals\
    \ : \u5186\u5206\u591A\u9805\u5F0F\n// ret[i][j] = [x^j]\\Phi_i(x) for i <= Nmax,\
    \ which are known to be integers\nstd::vector<std::vector<int>> cyclotomic_polynomials(int\
    \ Nmax)\n{\n    std::vector<int> moebius = SieveOfEratosthenes(Nmax).GenerateMoebiusFunctionTable();\n\
    \    std::vector<std::vector<int>> ret(Nmax + 1);\n    auto multiply = [](const\
    \ std::vector<int> &a, const std::vector<int> &b) { // a * b\n        std::vector<int>\
    \ ret(int(a.size() + b.size()) - 1);\n        for (size_t i = 0; i < a.size();\
    \ i++) for (size_t j = 0; j < b.size(); j++) {\n                ret[i + j] +=\
    \ a[i] * b[j];\n        }\n        return ret;\n    };\n    auto divide = [](std::vector<int>\
    \ a, const std::vector<int> &b) { // a / b, abs(b[0]) = 1\n        std::vector<int>\
    \ ret(int(a.size()) - int(b.size()) + 1);\n        for (size_t i = 0; i < ret.size();\
    \ i++) {\n            ret[i] = a[i] / b[0];\n            for (size_t j = 0; j\
    \ < b.size(); j++) a[i + j] -= ret[i] * b[j];\n        }\n        while (ret.size()\
    \ and !ret.back()) ret.pop_back();\n        return ret;\n    };\n\n    for (int\
    \ n = 0; n <= Nmax; n++) {\n        std::vector<std::vector<int>> num, den;\n\
    \        for (int d = 1; d <= n; d++) if (n % d == 0 and moebius[d]) {\n     \
    \       std::vector<int> r(n / d + 1);\n            r[0] = -1, r.back() = 1;\n\
    \            (moebius[d] > 0 ? num : den).push_back(r);\n        }\n        std::vector<int>\
    \ phi{1};\n        for (auto v : num) phi = multiply(phi, v);\n        for (auto\
    \ v : den) phi = divide(phi, v);\n        ret[n] = phi;\n    }\n    return ret;\n\
    }\n"
  code: "#pragma once\n#include \"number/eratosthenes.hpp\"\n#include <vector>\n\n\
    // CUT begin\n// cyclotomic polynominals : \u5186\u5206\u591A\u9805\u5F0F\n//\
    \ ret[i][j] = [x^j]\\Phi_i(x) for i <= Nmax, which are known to be integers\n\
    std::vector<std::vector<int>> cyclotomic_polynomials(int Nmax)\n{\n    std::vector<int>\
    \ moebius = SieveOfEratosthenes(Nmax).GenerateMoebiusFunctionTable();\n    std::vector<std::vector<int>>\
    \ ret(Nmax + 1);\n    auto multiply = [](const std::vector<int> &a, const std::vector<int>\
    \ &b) { // a * b\n        std::vector<int> ret(int(a.size() + b.size()) - 1);\n\
    \        for (size_t i = 0; i < a.size(); i++) for (size_t j = 0; j < b.size();\
    \ j++) {\n                ret[i + j] += a[i] * b[j];\n        }\n        return\
    \ ret;\n    };\n    auto divide = [](std::vector<int> a, const std::vector<int>\
    \ &b) { // a / b, abs(b[0]) = 1\n        std::vector<int> ret(int(a.size()) -\
    \ int(b.size()) + 1);\n        for (size_t i = 0; i < ret.size(); i++) {\n   \
    \         ret[i] = a[i] / b[0];\n            for (size_t j = 0; j < b.size();\
    \ j++) a[i + j] -= ret[i] * b[j];\n        }\n        while (ret.size() and !ret.back())\
    \ ret.pop_back();\n        return ret;\n    };\n\n    for (int n = 0; n <= Nmax;\
    \ n++) {\n        std::vector<std::vector<int>> num, den;\n        for (int d\
    \ = 1; d <= n; d++) if (n % d == 0 and moebius[d]) {\n            std::vector<int>\
    \ r(n / d + 1);\n            r[0] = -1, r.back() = 1;\n            (moebius[d]\
    \ > 0 ? num : den).push_back(r);\n        }\n        std::vector<int> phi{1};\n\
    \        for (auto v : num) phi = multiply(phi, v);\n        for (auto v : den)\
    \ phi = divide(phi, v);\n        ret[n] = phi;\n    }\n    return ret;\n}\n"
  dependsOn:
  - number/eratosthenes.hpp
  isVerificationFile: false
  path: number/cyclotomic_polynomials.hpp
  requiredBy: []
  timestamp: '2020-04-04 22:42:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number/cyclotomic_polynomials.hpp
layout: document
redirect_from:
- /library/number/cyclotomic_polynomials.hpp
- /library/number/cyclotomic_polynomials.hpp.html
title: number/cyclotomic_polynomials.hpp
---
