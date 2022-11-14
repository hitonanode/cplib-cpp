---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: number/primitive_root.hpp
    title: "Primitive root modulo $n$ \uFF08\u539F\u59CB\u6839\u306E\u767A\u898B\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/chromatic_number.test.cpp
    title: graph/test/chromatic_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/factorize_aoj.test.cpp
    title: number/test/factorize_aoj.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/factorize_longlong.test.cpp
    title: number/test/factorize_longlong.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/miller-rabin-5e7.test.cpp
    title: number/test/miller-rabin-5e7.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/miller-rabin.test.cpp
    title: number/test/miller-rabin.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/primitive_root.test.cpp
    title: number/test/primitive_root.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/primitive_root_1e18.test.cpp
    title: number/test/primitive_root_1e18.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://miller-rabin.appspot.com/
    - https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%A9%E3%83%BC%E2%80%93%E3%83%A9%E3%83%93%E3%83%B3%E7%B4%A0%E6%95%B0%E5%88%A4%E5%AE%9A%E6%B3%95
  bundledCode: "#line 2 \"number/factorize.hpp\"\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\nnamespace SPRP {\n// http://miller-rabin.appspot.com/\n\
    const std::vector<std::vector<__int128>> bases{\n    {126401071349994536},   \
    \                           // < 291831\n    {336781006125, 9639812373923155},\
    \                  // < 1050535501 (1e9)\n    {2, 2570940, 211991001, 3749873356},\
    \               // < 47636622961201 (4e13)\n    {2, 325, 9375, 28178, 450775,\
    \ 9780504, 1795265022} // <= 2^64\n};\ninline int get_id(long long n) {\n    if\
    \ (n < 291831) {\n        return 0;\n    } else if (n < 1050535501) {\n      \
    \  return 1;\n    } else if (n < 47636622961201)\n        return 2;\n    else\
    \ { return 3; }\n}\n} // namespace SPRP\n\n// Miller-Rabin primality test\n//\
    \ https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%A9%E3%83%BC%E2%80%93%E3%83%A9%E3%83%93%E3%83%B3%E7%B4%A0%E6%95%B0%E5%88%A4%E5%AE%9A%E6%B3%95\n\
    // Complexity: O(lg n) per query\nstruct {\n    long long modpow(__int128 x, __int128\
    \ n, long long mod) noexcept {\n        __int128 ret = 1;\n        for (x %= mod;\
    \ n; x = x * x % mod, n >>= 1) ret = (n & 1) ? ret * x % mod : ret;\n        return\
    \ ret;\n    }\n    bool operator()(long long n) noexcept {\n        if (n < 2)\
    \ return false;\n        if (n % 2 == 0) return n == 2;\n        int s = __builtin_ctzll(n\
    \ - 1);\n\n        for (__int128 a : SPRP::bases[SPRP::get_id(n)]) {\n       \
    \     if (a % n == 0) continue;\n            a = modpow(a, (n - 1) >> s, n);\n\
    \            bool may_composite = true;\n            if (a == 1) continue;\n \
    \           for (int r = s; r--; a = a * a % n) {\n                if (a == n\
    \ - 1) may_composite = false;\n            }\n            if (may_composite) return\
    \ false;\n        }\n        return true;\n    }\n} is_prime;\n\nstruct {\n  \
    \  // Pollard's rho algorithm: find factor greater than 1\n    long long find_factor(long\
    \ long n) {\n        assert(n > 1);\n        if (n % 2 == 0) return 2;\n     \
    \   if (is_prime(n)) return n;\n        long long c = 1;\n        auto f = [&](__int128\
    \ x) -> long long { return (x * x + c) % n; };\n\n        for (int t = 1;; t++)\
    \ {\n            long long x0 = t, m = std::max(n >> 3, 1LL), x, ys, y = x0, r\
    \ = 1, g, q = 1;\n            do {\n                x = y;\n                for\
    \ (int i = r; i--;) y = f(y);\n                long long k = 0;\n            \
    \    do {\n                    ys = y;\n                    for (int i = std::min(m,\
    \ r - k); i--;)\n                        y = f(y), q = __int128(q) * std::abs(x\
    \ - y) % n;\n                    g = std::__gcd<long long>(q, n);\n          \
    \          k += m;\n                } while (k < r and g <= 1);\n            \
    \    r <<= 1;\n            } while (g <= 1);\n            if (g == n) {\n    \
    \            do {\n                    ys = f(ys);\n                    g = std::__gcd(std::abs(x\
    \ - ys), n);\n                } while (g <= 1);\n            }\n            if\
    \ (g != n) return g;\n        }\n    }\n\n    std::vector<long long> operator()(long\
    \ long n) {\n        std::vector<long long> ret;\n        while (n > 1) {\n  \
    \          long long f = find_factor(n);\n            if (f < n) {\n         \
    \       auto tmp = operator()(f);\n                ret.insert(ret.end(), tmp.begin(),\
    \ tmp.end());\n            } else\n                ret.push_back(n);\n       \
    \     n /= f;\n        }\n        std::sort(ret.begin(), ret.end());\n       \
    \ return ret;\n    }\n    long long euler_phi(long long n) {\n        long long\
    \ ret = 1, last = -1;\n        for (auto p : this->operator()(n)) ret *= p - (last\
    \ != p), last = p;\n        return ret;\n    }\n} FactorizeLonglong;\n"
  code: "#pragma once\n#include <algorithm>\n#include <array>\n#include <cassert>\n\
    #include <vector>\n\n// CUT begin\nnamespace SPRP {\n// http://miller-rabin.appspot.com/\n\
    const std::vector<std::vector<__int128>> bases{\n    {126401071349994536},   \
    \                           // < 291831\n    {336781006125, 9639812373923155},\
    \                  // < 1050535501 (1e9)\n    {2, 2570940, 211991001, 3749873356},\
    \               // < 47636622961201 (4e13)\n    {2, 325, 9375, 28178, 450775,\
    \ 9780504, 1795265022} // <= 2^64\n};\ninline int get_id(long long n) {\n    if\
    \ (n < 291831) {\n        return 0;\n    } else if (n < 1050535501) {\n      \
    \  return 1;\n    } else if (n < 47636622961201)\n        return 2;\n    else\
    \ { return 3; }\n}\n} // namespace SPRP\n\n// Miller-Rabin primality test\n//\
    \ https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%A9%E3%83%BC%E2%80%93%E3%83%A9%E3%83%93%E3%83%B3%E7%B4%A0%E6%95%B0%E5%88%A4%E5%AE%9A%E6%B3%95\n\
    // Complexity: O(lg n) per query\nstruct {\n    long long modpow(__int128 x, __int128\
    \ n, long long mod) noexcept {\n        __int128 ret = 1;\n        for (x %= mod;\
    \ n; x = x * x % mod, n >>= 1) ret = (n & 1) ? ret * x % mod : ret;\n        return\
    \ ret;\n    }\n    bool operator()(long long n) noexcept {\n        if (n < 2)\
    \ return false;\n        if (n % 2 == 0) return n == 2;\n        int s = __builtin_ctzll(n\
    \ - 1);\n\n        for (__int128 a : SPRP::bases[SPRP::get_id(n)]) {\n       \
    \     if (a % n == 0) continue;\n            a = modpow(a, (n - 1) >> s, n);\n\
    \            bool may_composite = true;\n            if (a == 1) continue;\n \
    \           for (int r = s; r--; a = a * a % n) {\n                if (a == n\
    \ - 1) may_composite = false;\n            }\n            if (may_composite) return\
    \ false;\n        }\n        return true;\n    }\n} is_prime;\n\nstruct {\n  \
    \  // Pollard's rho algorithm: find factor greater than 1\n    long long find_factor(long\
    \ long n) {\n        assert(n > 1);\n        if (n % 2 == 0) return 2;\n     \
    \   if (is_prime(n)) return n;\n        long long c = 1;\n        auto f = [&](__int128\
    \ x) -> long long { return (x * x + c) % n; };\n\n        for (int t = 1;; t++)\
    \ {\n            long long x0 = t, m = std::max(n >> 3, 1LL), x, ys, y = x0, r\
    \ = 1, g, q = 1;\n            do {\n                x = y;\n                for\
    \ (int i = r; i--;) y = f(y);\n                long long k = 0;\n            \
    \    do {\n                    ys = y;\n                    for (int i = std::min(m,\
    \ r - k); i--;)\n                        y = f(y), q = __int128(q) * std::abs(x\
    \ - y) % n;\n                    g = std::__gcd<long long>(q, n);\n          \
    \          k += m;\n                } while (k < r and g <= 1);\n            \
    \    r <<= 1;\n            } while (g <= 1);\n            if (g == n) {\n    \
    \            do {\n                    ys = f(ys);\n                    g = std::__gcd(std::abs(x\
    \ - ys), n);\n                } while (g <= 1);\n            }\n            if\
    \ (g != n) return g;\n        }\n    }\n\n    std::vector<long long> operator()(long\
    \ long n) {\n        std::vector<long long> ret;\n        while (n > 1) {\n  \
    \          long long f = find_factor(n);\n            if (f < n) {\n         \
    \       auto tmp = operator()(f);\n                ret.insert(ret.end(), tmp.begin(),\
    \ tmp.end());\n            } else\n                ret.push_back(n);\n       \
    \     n /= f;\n        }\n        std::sort(ret.begin(), ret.end());\n       \
    \ return ret;\n    }\n    long long euler_phi(long long n) {\n        long long\
    \ ret = 1, last = -1;\n        for (auto p : this->operator()(n)) ret *= p - (last\
    \ != p), last = p;\n        return ret;\n    }\n} FactorizeLonglong;\n"
  dependsOn: []
  isVerificationFile: false
  path: number/factorize.hpp
  requiredBy:
  - number/primitive_root.hpp
  timestamp: '2022-11-15 00:34:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/factorize_aoj.test.cpp
  - number/test/primitive_root_1e18.test.cpp
  - number/test/factorize_longlong.test.cpp
  - number/test/miller-rabin-5e7.test.cpp
  - number/test/miller-rabin.test.cpp
  - number/test/primitive_root.test.cpp
  - graph/test/chromatic_number.test.cpp
documentation_of: number/factorize.hpp
layout: document
redirect_from:
- /library/number/factorize.hpp
- /library/number/factorize.hpp.html
title: number/factorize.hpp
---
