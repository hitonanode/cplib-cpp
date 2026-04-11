---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/factorize.hpp
    title: "Integer factorization \uFF08\u7D20\u56E0\u6570\u5206\u89E3\uFF09"
  - icon: ':heavy_check_mark:'
    path: number/pow_mod.hpp
    title: "Modular exponentiation \uFF08\u3079\u304D\u4E57 mod\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
    - http://kirika-comp.hatenablog.com/entry/2018/03/12/210446
    - https://community.topcoder.com/stat?c=problem_statement&pm=17877
    - https://en.wikipedia.org/wiki/Primitive_root_modulo_n)
    - https://judge.yosupo.jp/problem/primitive_root
    - https://yukicoder.me/submissions/405938
  bundledCode: "#line 2 \"number/factorize.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <numeric>\n#include <vector>\n\nnamespace SPRP {\n\
    // http://miller-rabin.appspot.com/\nconst std::vector<std::vector<__int128>>\
    \ bases{\n    {126401071349994536},                              // < 291831\n\
    \    {336781006125, 9639812373923155},                  // < 1050535501 (1e9)\n\
    \    {2, 2570940, 211991001, 3749873356},               // < 47636622961201 (4e13)\n\
    \    {2, 325, 9375, 28178, 450775, 9780504, 1795265022} // <= 2^64\n};\ninline\
    \ int get_id(long long n) {\n    if (n < 291831) {\n        return 0;\n    } else\
    \ if (n < 1050535501) {\n        return 1;\n    } else if (n < 47636622961201)\n\
    \        return 2;\n    else { return 3; }\n}\n} // namespace SPRP\n\n// Miller-Rabin\
    \ primality test\n// https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%A9%E3%83%BC%E2%80%93%E3%83%A9%E3%83%93%E3%83%B3%E7%B4%A0%E6%95%B0%E5%88%A4%E5%AE%9A%E6%B3%95\n\
    // Complexity: O(lg n) per query\ninline struct {\n    long long modpow(__int128\
    \ x, __int128 n, long long mod) noexcept {\n        __int128 ret = 1;\n      \
    \  for (x %= mod; n; x = x * x % mod, n >>= 1) ret = (n & 1) ? ret * x % mod :\
    \ ret;\n        return ret;\n    }\n    bool operator()(long long n) noexcept\
    \ {\n        if (n < 2) return false;\n        if (n % 2 == 0) return n == 2;\n\
    \        int s = __builtin_ctzll(n - 1);\n\n        for (__int128 a : SPRP::bases[SPRP::get_id(n)])\
    \ {\n            if (a % n == 0) continue;\n            a = modpow(a, (n - 1)\
    \ >> s, n);\n            bool may_composite = true;\n            if (a == 1) continue;\n\
    \            for (int r = s; r--; a = a * a % n) {\n                if (a == n\
    \ - 1) may_composite = false;\n            }\n            if (may_composite) return\
    \ false;\n        }\n        return true;\n    }\n} is_prime;\n\ninline struct\
    \ {\n    static uint32_t xorshift() noexcept {\n        static uint32_t x = 123456789;\n\
    \        static uint32_t y = 362436069;\n        static uint32_t z = 521288629;\n\
    \        static uint32_t w = 88675123;\n        uint32_t t = x ^ (x << 11);\n\
    \        x = y;\n        y = z;\n        z = w;\n        return w = (w ^ (w >>\
    \ 19)) ^ (t ^ (t >> 8));\n    }\n\n    // Pollard's rho algorithm: find factor\
    \ greater than 1\n    long long find_factor(long long n) {\n        assert(n >\
    \ 1);\n        if (n % 2 == 0) return 2;\n        if (is_prime(n)) return n;\n\
    \        long long c = 1;\n        auto f = [&](__int128 x) -> long long { return\
    \ (x * x + c) % n; };\n\n        for (int t = 1;; t++) {\n            for (c =\
    \ 0; c == 0 or c + 2 == n;) c = xorshift() % n;\n            long long x0 = t,\
    \ m = std::max(n >> 3, 1LL), x, ys, y = x0, r = 1, g, q = 1;\n            do {\n\
    \                x = y;\n                for (int i = r; i--;) y = f(y);\n   \
    \             long long k = 0;\n                do {\n                    ys =\
    \ y;\n                    for (int i = std::min(m, r - k); i--;)\n           \
    \             y = f(y), q = __int128(q) * std::abs(x - y) % n;\n             \
    \       g = std::gcd<long long>(q, n);\n                    k += m;\n        \
    \        } while (k < r and g <= 1);\n                r <<= 1;\n            }\
    \ while (g <= 1);\n            if (g == n) {\n                do {\n         \
    \           ys = f(ys);\n                    g = std::gcd(std::abs(x - ys), n);\n\
    \                } while (g <= 1);\n            }\n            if (g != n) return\
    \ g;\n        }\n    }\n\n    std::vector<long long> operator()(long long n) {\n\
    \        std::vector<long long> ret;\n        while (n > 1) {\n            long\
    \ long f = find_factor(n);\n            if (f < n) {\n                auto tmp\
    \ = operator()(f);\n                ret.insert(ret.end(), tmp.begin(), tmp.end());\n\
    \            } else\n                ret.push_back(n);\n            n /= f;\n\
    \        }\n        std::sort(ret.begin(), ret.end());\n        return ret;\n\
    \    }\n    long long euler_phi(long long n) {\n        long long ret = 1, last\
    \ = -1;\n        for (auto p : this->operator()(n)) ret *= p - (last != p), last\
    \ = p;\n        return ret;\n    }\n} FactorizeLonglong;\n#line 3 \"number/pow_mod.hpp\"\
    \n#include <type_traits>\n\ntemplate <class Int> Int pow_mod(Int x, long long\
    \ n, Int md) {\n    using Long =\n        std::conditional_t<std::is_same_v<Int,\
    \ int>, long long,\n                           std::conditional_t<std::is_same_v<Int,\
    \ long long>, __int128, void>>;\n    assert(n >= 0 and md > 0);\n    if (md ==\
    \ 1) return 0;\n    if (n == 0) return 1;\n\n    x = (x % md + md) % md;\n   \
    \ Int ans = 1;\n    while (n > 0) {\n        if (n & 1) ans = (Long)ans * x %\
    \ md;\n        x = (Long)x * x % md;\n        n >>= 1;\n    }\n    return ans;\n\
    }\n#line 4 \"number/primitive_root.hpp\"\n\n// Find smallest primitive root for\
    \ given number n \uFF08\u6700\u5C0F\u306E\u539F\u59CB\u6839\u63A2\u7D22\uFF09\n\
    // n must be 2 / 4 / p^k / 2p^k (p: odd prime, k > 0)\n// (https://en.wikipedia.org/wiki/Primitive_root_modulo_n)\n\
    //\n// Complexity: maybe O(sqrt(n)), if n is\n// prime Algorithm: http://kirika-comp.hatenablog.com/entry/2018/03/12/210446\
    \ Verified:\n// - https://yukicoder.me/submissions/405938\n// - https://judge.yosupo.jp/problem/primitive_root\n\
    // - SRM 840 Div.1 900 https://community.topcoder.com/stat?c=problem_statement&pm=17877\n\
    // Sample:\n//  - 998244353 ( = (119 << 23) + 1 ) -> 3\n//  - 163577857 ( = (39\
    \ << 22) + 1 ) -> 23\n//  - 2 -> 1\n//  - 1 -> -1\ninline long long find_smallest_primitive_root(long\
    \ long n) {\n    std::vector<long long> fac;\n    const long long phi = FactorizeLonglong.euler_phi(n);\n\
    \    for (long long q : FactorizeLonglong(phi)) {\n        if (fac.empty() or\
    \ fac.back() != q) fac.push_back(q);\n    }\n\n    for (long long g = 1; g < n;\
    \ g++) {\n        if (std::gcd(n, g) != 1) continue;\n        if (pow_mod(g, phi,\
    \ n) != 1) return -1;\n        bool ok = true;\n        for (auto pp : fac) {\n\
    \            if (pow_mod(g, phi / pp, n) == 1) {\n                ok = false;\n\
    \                break;\n            }\n        }\n        if (ok) return g;\n\
    \    }\n    return -1;\n}\n"
  code: "#pragma once\n#include \"factorize.hpp\"\n#include \"pow_mod.hpp\"\n\n//\
    \ Find smallest primitive root for given number n \uFF08\u6700\u5C0F\u306E\u539F\
    \u59CB\u6839\u63A2\u7D22\uFF09\n// n must be 2 / 4 / p^k / 2p^k (p: odd prime,\
    \ k > 0)\n// (https://en.wikipedia.org/wiki/Primitive_root_modulo_n)\n//\n// Complexity:\
    \ maybe O(sqrt(n)), if n is\n// prime Algorithm: http://kirika-comp.hatenablog.com/entry/2018/03/12/210446\
    \ Verified:\n// - https://yukicoder.me/submissions/405938\n// - https://judge.yosupo.jp/problem/primitive_root\n\
    // - SRM 840 Div.1 900 https://community.topcoder.com/stat?c=problem_statement&pm=17877\n\
    // Sample:\n//  - 998244353 ( = (119 << 23) + 1 ) -> 3\n//  - 163577857 ( = (39\
    \ << 22) + 1 ) -> 23\n//  - 2 -> 1\n//  - 1 -> -1\ninline long long find_smallest_primitive_root(long\
    \ long n) {\n    std::vector<long long> fac;\n    const long long phi = FactorizeLonglong.euler_phi(n);\n\
    \    for (long long q : FactorizeLonglong(phi)) {\n        if (fac.empty() or\
    \ fac.back() != q) fac.push_back(q);\n    }\n\n    for (long long g = 1; g < n;\
    \ g++) {\n        if (std::gcd(n, g) != 1) continue;\n        if (pow_mod(g, phi,\
    \ n) != 1) return -1;\n        bool ok = true;\n        for (auto pp : fac) {\n\
    \            if (pow_mod(g, phi / pp, n) == 1) {\n                ok = false;\n\
    \                break;\n            }\n        }\n        if (ok) return g;\n\
    \    }\n    return -1;\n}\n"
  dependsOn:
  - number/factorize.hpp
  - number/pow_mod.hpp
  isVerificationFile: false
  path: number/primitive_root.hpp
  requiredBy: []
  timestamp: '2026-04-11 14:52:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/primitive_root.test.cpp
  - number/test/primitive_root_1e18.test.cpp
documentation_of: number/primitive_root.hpp
layout: document
title: "Primitive root modulo $n$ \uFF08\u539F\u59CB\u6839\u306E\u767A\u898B\uFF09"
---

与えられた整数 $n$ に対して，乗法群 $\mathbb{Z}^{\times}\_{n}$ に原始根が存在する場合に最小の原始根を計算する．$n \le 10^{18}$ を想定．

## 乗法群の原始根とは

$\mod n$ 上の整数のうち，乗法の逆元が存在するもののみをとって作る群を乗法群 $\mathbb{Z}^{\times}\_{n}$ と呼ぶ．

乗法群 $\mathbb{Z}^{\times}\_{n}$ の元 $r$ について，$r^0, r^1, r^2, \dots$ の集合が $\mathbb{Z}^{\times}\_{n}$ と（集合として）一致するとき，$r$ を乗法群の原始根と呼ぶ．

$\mathbb{Z}^\times\_{n}$ に原始根が存在するような $n$ は限られている．具体的には，$n = 2, 4, p^k, 2p^k$ のみである（$p$ は奇素数，$k$ は正の整数）．

## 最小の原始根について

本コードの
```cpp
    for (long long g = 1; g < n; g++) {
```
の部分について，`g` をインクリメンタルに調べることで最小の原始根を見つけている．$n$ が素数でかつ $10^{16}$ 以下の範囲では， $n = 6525032504501281$ のとき最小の原始根が $417$ となってこれが最大という（参考文献 [2]）．

上記のようなケースに対して，$g$ について乱択すれば（「最小の」原始根を諦める代わりに）実用上の高速化が可能と思われる [3]．

## 問題例

- [No.931 Multiplicative Convolution - yukicoder](https://yukicoder.me/problems/no/931)

## 参考文献・リンク

- [1] [整数論テクニック集 - kirika_compのブログ](https://kirika-comp.hatenablog.com/entry/2018/03/12/210446)
- [2] [[2206.14193] Computation of the least primitive root](https://arxiv.org/abs/2206.14193)
- [3] [原始根のアルゴリズム – 37zigenのHP](https://37zigen.com/primitive-root/)
- [4] [Primitive root modulo n - Wikipedia](https://en.wikipedia.org/wiki/Primitive_root_modulo_n)
