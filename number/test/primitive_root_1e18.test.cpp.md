---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: number/bare_mod_algebra.hpp
    title: number/bare_mod_algebra.hpp
  - icon: ':heavy_check_mark:'
    path: number/factorize.hpp
    title: "Integer factorization \uFF08\u7D20\u56E0\u6570\u5206\u89E3\uFF09"
  - icon: ':heavy_check_mark:'
    path: number/primitive_root.hpp
    title: "Primitive root modulo $n$ \uFF08\u539F\u59CB\u6839\u306E\u767A\u898B\uFF09"
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
    PROBLEM: https://judge.yosupo.jp/problem/primitive_root
    links:
    - https://judge.yosupo.jp/problem/primitive_root
  bundledCode: "#line 1 \"number/test/primitive_root_1e18.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/primitive_root\"\n#line 2 \"number/bare_mod_algebra.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// Solve ax+by=gcd(a, b)\ntemplate <class Int>\
    \ Int extgcd(Int a, Int b, Int &x, Int &y) {\n    Int d = a;\n    if (b != 0)\
    \ {\n        d = extgcd(b, a % b, y, x), y -= (a / b) * x;\n    } else {\n   \
    \     x = 1, y = 0;\n    }\n    return d;\n}\n// Calculate a^(-1) (MOD m) s if\
    \ gcd(a, m) == 1\n// Calculate x s.t. ax == gcd(a, m) MOD m\ntemplate <class Int>\
    \ Int mod_inverse(Int a, Int m) {\n    Int x, y;\n    extgcd<Int>(a, m, x, y);\n\
    \    x %= m;\n    return x + (x < 0) * m;\n}\n\n// Require: 1 <= b\n// return:\
    \ (g, x) s.t. g = gcd(a, b), xa = g MOD b, 0 <= x < b/g\ntemplate <class Int>\
    \ /* constexpr */ std::pair<Int, Int> inv_gcd(Int a, Int b) {\n    a %= b;\n \
    \   if (a < 0) a += b;\n    if (a == 0) return {b, 0};\n    Int s = b, t = a,\
    \ m0 = 0, m1 = 1;\n    while (t) {\n        Int u = s / t;\n        s -= t * u,\
    \ m0 -= m1 * u;\n        auto tmp = s;\n        s = t, t = tmp, tmp = m0, m0 =\
    \ m1, m1 = tmp;\n    }\n    if (m0 < 0) m0 += b / s;\n    return {s, m0};\n}\n\
    \ntemplate <class Int>\n/* constexpr */ std::pair<Int, Int> crt(const std::vector<Int>\
    \ &r, const std::vector<Int> &m) {\n    assert(r.size() == m.size());\n    int\
    \ n = int(r.size());\n    // Contracts: 0 <= r0 < m0\n    Int r0 = 0, m0 = 1;\n\
    \    for (int i = 0; i < n; i++) {\n        assert(1 <= m[i]);\n        Int r1\
    \ = r[i] % m[i], m1 = m[i];\n        if (r1 < 0) r1 += m1;\n        if (m0 < m1)\
    \ {\n            std::swap(r0, r1);\n            std::swap(m0, m1);\n        }\n\
    \        if (m0 % m1 == 0) {\n            if (r0 % m1 != r1) return {0, 0};\n\
    \            continue;\n        }\n        Int g, im;\n        std::tie(g, im)\
    \ = inv_gcd<Int>(m0, m1);\n\n        Int u1 = m1 / g;\n        if ((r1 - r0) %\
    \ g) return {0, 0};\n\n        Int x = (r1 - r0) / g % u1 * im % u1;\n       \
    \ r0 += x * m0;\n        m0 *= u1;\n        if (r0 < 0) r0 += m0;\n    }\n   \
    \ return {r0, m0};\n}\n\n// \u87FB\u672C P.262\n// \u4E2D\u56FD\u5270\u4F59\u5B9A\
    \u7406\u3092\u5229\u7528\u3057\u3066\uFF0C\u8272\u3005\u306A\u7D20\u6570\u3067\
    \u5272\u3063\u305F\u4F59\u308A\u304B\u3089\u5143\u306E\u5024\u3092\u5FA9\u5143\
    \n// \u9023\u7ACB\u7DDA\u5F62\u5408\u540C\u5F0F A * x = B mod M \u306E\u89E3\n\
    // Requirement: M[i] > 0\n// Output: x = first MOD second (if solution exists),\
    \ (0, 0) (otherwise)\ntemplate <class Int>\nstd::pair<Int, Int>\nlinear_congruence(const\
    \ std::vector<Int> &A, const std::vector<Int> &B, const std::vector<Int> &M) {\n\
    \    Int r = 0, m = 1;\n    assert(A.size() == M.size());\n    assert(B.size()\
    \ == M.size());\n    for (int i = 0; i < (int)A.size(); i++) {\n        assert(M[i]\
    \ > 0);\n        const Int ai = A[i] % M[i];\n        Int a = ai * m, b = B[i]\
    \ - ai * r, d = std::__gcd(M[i], a);\n        if (b % d != 0) {\n            return\
    \ std::make_pair(0, 0); // \u89E3\u306A\u3057\n        }\n        Int t = b /\
    \ d * mod_inverse<Int>(a / d, M[i] / d) % (M[i] / d);\n        r += m * t;\n \
    \       m *= M[i] / d;\n    }\n    return std::make_pair((r < 0 ? r + m : r),\
    \ m);\n}\n\ntemplate <class Int = int, class Long = long long> Int pow_mod(Int\
    \ x, long long n, Int md) {\n    static_assert(sizeof(Int) * 2 <= sizeof(Long),\
    \ \"Watch out for overflow\");\n    if (md == 1) return 0;\n    Int ans = 1;\n\
    \    while (n > 0) {\n        if (n & 1) ans = (Long)ans * x % md;\n        x\
    \ = (Long)x * x % md;\n        n >>= 1;\n    }\n    return ans;\n}\n#line 2 \"\
    random/xorshift.hpp\"\n#include <cstdint>\n\n// CUT begin\nuint32_t rand_int()\
    \ // XorShift random integer generator\n{\n    static uint32_t x = 123456789,\
    \ y = 362436069, z = 521288629, w = 88675123;\n    uint32_t t = x ^ (x << 11);\n\
    \    x = y;\n    y = z;\n    z = w;\n    return w = (w ^ (w >> 19)) ^ (t ^ (t\
    \ >> 8));\n}\ndouble rand_double() { return (double)rand_int() / UINT32_MAX; }\n\
    #line 4 \"number/factorize.hpp\"\n#include <array>\n#line 6 \"number/factorize.hpp\"\
    \n#include <numeric>\n#line 8 \"number/factorize.hpp\"\n\nnamespace SPRP {\n//\
    \ http://miller-rabin.appspot.com/\nconst std::vector<std::vector<__int128>> bases{\n\
    \    {126401071349994536},                              // < 291831\n    {336781006125,\
    \ 9639812373923155},                  // < 1050535501 (1e9)\n    {2, 2570940,\
    \ 211991001, 3749873356},               // < 47636622961201 (4e13)\n    {2, 325,\
    \ 9375, 28178, 450775, 9780504, 1795265022} // <= 2^64\n};\ninline int get_id(long\
    \ long n) {\n    if (n < 291831) {\n        return 0;\n    } else if (n < 1050535501)\
    \ {\n        return 1;\n    } else if (n < 47636622961201)\n        return 2;\n\
    \    else { return 3; }\n}\n} // namespace SPRP\n\n// Miller-Rabin primality test\n\
    // https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%A9%E3%83%BC%E2%80%93%E3%83%A9%E3%83%93%E3%83%B3%E7%B4%A0%E6%95%B0%E5%88%A4%E5%AE%9A%E6%B3%95\n\
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
    \ != p), last = p;\n        return ret;\n    }\n} FactorizeLonglong;\n#line 4\
    \ \"number/primitive_root.hpp\"\n\n// Find smallest primitive root for given number\
    \ n \uFF08\u6700\u5C0F\u306E\u539F\u59CB\u6839\u63A2\u7D22\uFF09\n// n must be\
    \ 2 / 4 / p^k / 2p^k (p: odd prime, k > 0)\n// (https://en.wikipedia.org/wiki/Primitive_root_modulo_n)\n\
    //\n// Complexity: maybe O(sqrt(n)), if n is\n// prime Algorithm: http://kirika-comp.hatenablog.com/entry/2018/03/12/210446\
    \ Verified:\n// - https://yukicoder.me/submissions/405938\n// - https://judge.yosupo.jp/problem/primitive_root\n\
    // - SRM 840 Div.1 900 https://community.topcoder.com/stat?c=problem_statement&pm=17877\n\
    // Sample:\n//  - 998244353 ( = (119 << 23) + 1 ) -> 3\n//  - 163577857 ( = (39\
    \ << 22) + 1 ) -> 23\n//  - 2 -> 1\n//  - 1 -> -1\nlong long find_smallest_primitive_root(long\
    \ long n) {\n    std::vector<long long> fac;\n    const long long phi = FactorizeLonglong.euler_phi(n);\n\
    \    for (long long q : FactorizeLonglong(phi)) {\n        if (fac.empty() or\
    \ fac.back() != q) fac.push_back(q);\n    }\n\n    for (long long g = 1; g < n;\
    \ g++) {\n        if (std::__gcd(n, g) != 1) continue;\n        if (pow_mod<long\
    \ long, __int128>(g, phi, n) != 1) return -1;\n        bool ok = true;\n     \
    \   for (auto pp : fac) {\n            if (pow_mod<long long, __int128>(g, phi\
    \ / pp, n) == 1) {\n                ok = false;\n                break;\n    \
    \        }\n        }\n        if (ok) return g;\n    }\n    return -1;\n}\n#line\
    \ 3 \"number/test/primitive_root_1e18.test.cpp\"\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int Q;\n    cin >> Q;\n    while (Q--) {\n        long long p;\n        cin\
    \ >> p;\n        cout << find_smallest_primitive_root(p) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/primitive_root\"\n#include\
    \ \"../primitive_root.hpp\"\n#include <iostream>\nusing namespace std;\n\nint\
    \ main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int Q;\n \
    \   cin >> Q;\n    while (Q--) {\n        long long p;\n        cin >> p;\n  \
    \      cout << find_smallest_primitive_root(p) << '\\n';\n    }\n}\n"
  dependsOn:
  - number/primitive_root.hpp
  - number/bare_mod_algebra.hpp
  - number/factorize.hpp
  - random/xorshift.hpp
  isVerificationFile: true
  path: number/test/primitive_root_1e18.test.cpp
  requiredBy: []
  timestamp: '2023-03-10 18:40:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/primitive_root_1e18.test.cpp
layout: document
redirect_from:
- /verify/number/test/primitive_root_1e18.test.cpp
- /verify/number/test/primitive_root_1e18.test.cpp.html
title: number/test/primitive_root_1e18.test.cpp
---
