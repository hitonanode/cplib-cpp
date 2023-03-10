---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/factorize.hpp
    title: "Integer factorization \uFF08\u7D20\u56E0\u6570\u5206\u89E3\uFF09"
  - icon: ':heavy_check_mark:'
    path: number/sieve.hpp
    title: "Linear sieve \uFF08\u7DDA\u5F62\u7BE9\uFF09"
  - icon: ':heavy_check_mark:'
    path: random/xorshift.hpp
    title: random/xorshift.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"number/test/miller-rabin-5e7.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\" // DUMMY\n\
    #line 2 \"random/xorshift.hpp\"\n#include <cstdint>\n\n// CUT begin\nuint32_t\
    \ rand_int() // XorShift random integer generator\n{\n    static uint32_t x =\
    \ 123456789, y = 362436069, z = 521288629, w = 88675123;\n    uint32_t t = x ^\
    \ (x << 11);\n    x = y;\n    y = z;\n    z = w;\n    return w = (w ^ (w >> 19))\
    \ ^ (t ^ (t >> 8));\n}\ndouble rand_double() { return (double)rand_int() / UINT32_MAX;\
    \ }\n#line 3 \"number/factorize.hpp\"\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <numeric>\n#include <vector>\n\nnamespace SPRP {\n\
    // http://miller-rabin.appspot.com/\nconst std::vector<std::vector<__int128>>\
    \ bases{\n    {126401071349994536},                              // < 291831\n\
    \    {336781006125, 9639812373923155},                  // < 1050535501 (1e9)\n\
    \    {2, 2570940, 211991001, 3749873356},               // < 47636622961201 (4e13)\n\
    \    {2, 325, 9375, 28178, 450775, 9780504, 1795265022} // <= 2^64\n};\ninline\
    \ int get_id(long long n) {\n    if (n < 291831) {\n        return 0;\n    } else\
    \ if (n < 1050535501) {\n        return 1;\n    } else if (n < 47636622961201)\n\
    \        return 2;\n    else { return 3; }\n}\n} // namespace SPRP\n\n// Miller-Rabin\
    \ primality test\n// https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%A9%E3%83%BC%E2%80%93%E3%83%A9%E3%83%93%E3%83%B3%E7%B4%A0%E6%95%B0%E5%88%A4%E5%AE%9A%E6%B3%95\n\
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
    \ {\n            for (c = 0; c == 0 or c + 2 == n;) c = rand_int() % n;\n    \
    \        long long x0 = t, m = std::max(n >> 3, 1LL), x, ys, y = x0, r = 1, g,\
    \ q = 1;\n            do {\n                x = y;\n                for (int i\
    \ = r; i--;) y = f(y);\n                long long k = 0;\n                do {\n\
    \                    ys = y;\n                    for (int i = std::min(m, r -\
    \ k); i--;)\n                        y = f(y), q = __int128(q) * std::abs(x -\
    \ y) % n;\n                    g = std::__gcd<long long>(q, n);\n            \
    \        k += m;\n                } while (k < r and g <= 1);\n              \
    \  r <<= 1;\n            } while (g <= 1);\n            if (g == n) {\n      \
    \          do {\n                    ys = f(ys);\n                    g = std::__gcd(std::abs(x\
    \ - ys), n);\n                } while (g <= 1);\n            }\n            if\
    \ (g != n) return g;\n        }\n    }\n\n    std::vector<long long> operator()(long\
    \ long n) {\n        std::vector<long long> ret;\n        while (n > 1) {\n  \
    \          long long f = find_factor(n);\n            if (f < n) {\n         \
    \       auto tmp = operator()(f);\n                ret.insert(ret.end(), tmp.begin(),\
    \ tmp.end());\n            } else\n                ret.push_back(n);\n       \
    \     n /= f;\n        }\n        std::sort(ret.begin(), ret.end());\n       \
    \ return ret;\n    }\n    long long euler_phi(long long n) {\n        long long\
    \ ret = 1, last = -1;\n        for (auto p : this->operator()(n)) ret *= p - (last\
    \ != p), last = p;\n        return ret;\n    }\n} FactorizeLonglong;\n#line 3\
    \ \"number/sieve.hpp\"\n#include <map>\n#line 5 \"number/sieve.hpp\"\n\n// CUT\
    \ begin\n// Linear sieve algorithm for fast prime factorization\n// Complexity:\
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
    \      O(MAXN / log MAXN) (MAXN < x <= MAXN^2)\n    template <class T> std::map<T,\
    \ int> factorize(T x) const {\n        std::map<T, int> ret;\n        assert(x\
    \ > 0 and\n               x <= ((long long)min_factor.size() - 1) * ((long long)min_factor.size()\
    \ - 1));\n        for (const auto &p : primes) {\n            if (x < T(min_factor.size()))\
    \ break;\n            while (!(x % p)) x /= p, ret[p]++;\n        }\n        if\
    \ (x >= T(min_factor.size())) ret[x]++, x = 1;\n        while (x > 1) ret[min_factor[x]]++,\
    \ x /= min_factor[x];\n        return ret;\n    }\n    // Enumerate divisors of\
    \ 1 <= x <= MAXN^2\n    // Be careful of highly composite numbers https://oeis.org/A002182/list\n\
    \    // https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt (n,\
    \ (# of div. of n)):\n    // 45360->100, 735134400(<1e9)->1344, 963761198400(<1e12)->6720\n\
    \    template <class T> std::vector<T> divisors(T x) const {\n        std::vector<T>\
    \ ret{1};\n        for (const auto p : factorize(x)) {\n            int n = ret.size();\n\
    \            for (int i = 0; i < n; i++) {\n                for (T a = 1, d =\
    \ 1; d <= p.second; d++) {\n                    a *= p.first;\n              \
    \      ret.push_back(ret[i] * a);\n                }\n            }\n        }\n\
    \        return ret; // NOT sorted\n    }\n    // Euler phi functions of divisors\
    \ of given x\n    // Verified: ABC212 G https://atcoder.jp/contests/abc212/tasks/abc212_g\n\
    \    // Complexity: O(sqrt(x) + d(x))\n    template <class T> std::map<T, T> euler_of_divisors(T\
    \ x) const {\n        assert(x >= 1);\n        std::map<T, T> ret;\n        ret[1]\
    \ = 1;\n        std::vector<T> divs{1};\n        for (auto p : factorize(x)) {\n\
    \            int n = ret.size();\n            for (int i = 0; i < n; i++) {\n\
    \                ret[divs[i] * p.first] = ret[divs[i]] * (p.first - 1);\n    \
    \            divs.push_back(divs[i] * p.first);\n                for (T a = divs[i]\
    \ * p.first, d = 1; d < p.second; a *= p.first, d++) {\n                    ret[a\
    \ * p.first] = ret[a] * p.first;\n                    divs.push_back(a * p.first);\n\
    \                }\n            }\n        }\n        return ret;\n    }\n   \
    \ // Moebius function Table, (-1)^{# of different prime factors} for square-free\
    \ x\n    // return: [0=>0, 1=>1, 2=>-1, 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0,\
    \ ...] https://oeis.org/A008683\n    std::vector<int> GenerateMoebiusFunctionTable()\
    \ const {\n        std::vector<int> ret(min_factor.size());\n        for (unsigned\
    \ i = 1; i < min_factor.size(); i++) {\n            if (i == 1) {\n          \
    \      ret[i] = 1;\n            } else if ((i / min_factor[i]) % min_factor[i]\
    \ == 0) {\n                ret[i] = 0;\n            } else {\n               \
    \ ret[i] = -ret[i / min_factor[i]];\n            }\n        }\n        return\
    \ ret;\n    }\n    // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)\n    // Note:\
    \ **0^0 == 1**\n    template <class MODINT> std::vector<MODINT> enumerate_kth_pows(long\
    \ long K, int nmax) const {\n        assert(nmax < int(min_factor.size()));\n\
    \        assert(K >= 0);\n        if (K == 0) return std::vector<MODINT>(nmax\
    \ + 1, 1);\n        std::vector<MODINT> ret(nmax + 1);\n        ret[0] = 0, ret[1]\
    \ = 1;\n        for (int n = 2; n <= nmax; n++) {\n            if (min_factor[n]\
    \ == n) {\n                ret[n] = MODINT(n).pow(K);\n            } else {\n\
    \                ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];\n     \
    \       }\n        }\n        return ret;\n    }\n};\n// Sieve sieve((1 << 20));\n\
    #line 5 \"number/test/miller-rabin-5e7.test.cpp\"\n#include <cstdio>\n\nint main()\
    \ {\n    int lim = 5e7;\n    Sieve sieve(lim);\n    for (int x = 1; x <= lim;\
    \ x++) {\n        bool is_prime_1 = (sieve.min_factor[x] == x);\n        bool\
    \ is_prime_2 = is_prime(x);\n        assert(is_prime_1 == is_prime_2);\n    }\n\
    \    puts(\"Hello World\");\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../factorize.hpp\"\n#include \"../sieve.hpp\"\n#include\
    \ <cassert>\n#include <cstdio>\n\nint main() {\n    int lim = 5e7;\n    Sieve\
    \ sieve(lim);\n    for (int x = 1; x <= lim; x++) {\n        bool is_prime_1 =\
    \ (sieve.min_factor[x] == x);\n        bool is_prime_2 = is_prime(x);\n      \
    \  assert(is_prime_1 == is_prime_2);\n    }\n    puts(\"Hello World\");\n}\n"
  dependsOn:
  - number/factorize.hpp
  - random/xorshift.hpp
  - number/sieve.hpp
  isVerificationFile: true
  path: number/test/miller-rabin-5e7.test.cpp
  requiredBy: []
  timestamp: '2023-03-10 18:40:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/miller-rabin-5e7.test.cpp
layout: document
redirect_from:
- /verify/number/test/miller-rabin-5e7.test.cpp
- /verify/number/test/miller-rabin-5e7.test.cpp.html
title: number/test/miller-rabin-5e7.test.cpp
---
