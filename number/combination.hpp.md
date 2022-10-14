---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/bare_mod_algebra.hpp
    title: number/bare_mod_algebra.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/combination.stress.test.cpp
    title: number/test/combination.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/combination.test.cpp
    title: number/test/combination.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://ferin-tech.hatenablog.com/entry/2018/01/17/010829
    - https://judge.yosupo.jp/problem/binomial_coefficient
  bundledCode: "#line 2 \"number/bare_mod_algebra.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n// CUT\
    \ begin\n// Solve ax+by=gcd(a, b)\ntemplate <class Int> Int extgcd(Int a, Int\
    \ b, Int &x, Int &y) {\n    Int d = a;\n    if (b != 0) {\n        d = extgcd(b,\
    \ a % b, y, x), y -= (a / b) * x;\n    } else {\n        x = 1, y = 0;\n    }\n\
    \    return d;\n}\n// Calculate a^(-1) (MOD m) s if gcd(a, m) == 1\n// Calculate\
    \ x s.t. ax == gcd(a, m) MOD m\ntemplate <class Int> Int mod_inverse(Int a, Int\
    \ m) {\n    Int x, y;\n    extgcd<Int>(a, m, x, y);\n    x %= m;\n    return x\
    \ + (x < 0) * m;\n}\n\n// Require: 1 <= b\n// return: (g, x) s.t. g = gcd(a, b),\
    \ xa = g MOD b, 0 <= x < b/g\ntemplate <class Int> /* constexpr */ std::pair<Int,\
    \ Int> inv_gcd(Int a, Int b) {\n    a %= b;\n    if (a < 0) a += b;\n    if (a\
    \ == 0) return {b, 0};\n    Int s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n\
    \        Int u = s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp =\
    \ s;\n        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0\
    \ < 0) m0 += b / s;\n    return {s, m0};\n}\n\ntemplate <class Int>\n/* constexpr\
    \ */ std::pair<Int, Int> crt(const std::vector<Int> &r, const std::vector<Int>\
    \ &m) {\n    assert(r.size() == m.size());\n    int n = int(r.size());\n    //\
    \ Contracts: 0 <= r0 < m0\n    Int r0 = 0, m0 = 1;\n    for (int i = 0; i < n;\
    \ i++) {\n        assert(1 <= m[i]);\n        Int r1 = r[i] % m[i], m1 = m[i];\n\
    \        if (r1 < 0) r1 += m1;\n        if (m0 < m1) {\n            std::swap(r0,\
    \ r1);\n            std::swap(m0, m1);\n        }\n        if (m0 % m1 == 0) {\n\
    \            if (r0 % m1 != r1) return {0, 0};\n            continue;\n      \
    \  }\n        Int g, im;\n        std::tie(g, im) = inv_gcd<Int>(m0, m1);\n\n\
    \        Int u1 = m1 / g;\n        if ((r1 - r0) % g) return {0, 0};\n\n     \
    \   Int x = (r1 - r0) / g % u1 * im % u1;\n        r0 += x * m0;\n        m0 *=\
    \ u1;\n        if (r0 < 0) r0 += m0;\n    }\n    return {r0, m0};\n}\n\n// \u87FB\
    \u672C P.262\n// \u4E2D\u56FD\u5270\u4F59\u5B9A\u7406\u3092\u5229\u7528\u3057\u3066\
    \uFF0C\u8272\u3005\u306A\u7D20\u6570\u3067\u5272\u3063\u305F\u4F59\u308A\u304B\
    \u3089\u5143\u306E\u5024\u3092\u5FA9\u5143\n// \u9023\u7ACB\u7DDA\u5F62\u5408\u540C\
    \u5F0F A * x = B mod M \u306E\u89E3\n// Requirement: M[i] > 0\n// Output: x =\
    \ first MOD second (if solution exists), (0, 0) (otherwise)\ntemplate <class Int>\n\
    std::pair<Int, Int>\nlinear_congruence(const std::vector<Int> &A, const std::vector<Int>\
    \ &B, const std::vector<Int> &M) {\n    Int r = 0, m = 1;\n    assert(A.size()\
    \ == M.size());\n    assert(B.size() == M.size());\n    for (int i = 0; i < (int)A.size();\
    \ i++) {\n        assert(M[i] > 0);\n        const Int ai = A[i] % M[i];\n   \
    \     Int a = ai * m, b = B[i] - ai * r, d = std::__gcd(M[i], a);\n        if\
    \ (b % d != 0) {\n            return std::make_pair(0, 0); // \u89E3\u306A\u3057\
    \n        }\n        Int t = b / d * mod_inverse<Int>(a / d, M[i] / d) % (M[i]\
    \ / d);\n        r += m * t;\n        m *= M[i] / d;\n    }\n    return std::make_pair((r\
    \ < 0 ? r + m : r), m);\n}\n\ntemplate <class Int = int, class Long = long long>\n\
    Int pow_mod(Int x, long long n, Int md) {\n    static_assert(sizeof(Int) * 2 <=\
    \ sizeof(Long), \"Watch out for overflow\");\n    if (md == 1) return 0;\n   \
    \ Int ans = 1;\n    while (n > 0) {\n        if (n & 1) ans = (Long)ans * x %\
    \ md;\n        x = (Long)x * x % md;\n        n >>= 1;\n    }\n    return ans;\n\
    }\n#line 5 \"number/combination.hpp\"\n\n// nCr mod m = p^q (p: prime, q >= 1)\n\
    // Can be used for n, r <= 1e18, m <= 1e7\n// Complexity: O(m) (construction),\
    \ O(log(n)) (per query)\n// https://ferin-tech.hatenablog.com/entry/2018/01/17/010829\n\
    struct combination_prime_pow {\n    int p, q, m;\n    std::vector<int> fac, invfac,\
    \ ppow;\n\n    long long _ej(long long n) const {\n        long long ret = 0;\n\
    \        while (n) ret += n, n /= p;\n        return ret;\n    }\n\n    combination_prime_pow(int\
    \ p_, int q_) : p(p_), q(q_), m(1), ppow{1} {\n        for (int t = 0; t < q;\
    \ ++t) m *= p, ppow.push_back(m);\n        fac.assign(m, 1);\n        invfac.assign(m,\
    \ 1);\n        for (int i = 1; i < m; ++i) fac[i] = (long long)fac[i - 1] * (i\
    \ % p ? i : 1) % m;\n        invfac[m - 1] = fac[m - 1]; // Same as Wilson's theorem\n\
    \        assert(1LL * fac.back() * invfac.back() % m == 1);\n        for (int\
    \ i = m - 1; i; --i) invfac[i - 1] = (long long)invfac[i] * (i % p ? i : 1) %\
    \ m;\n    }\n\n    int nCr(long long n, long long r) const {\n        if (r <\
    \ 0 or n < r) return 0;\n        if (p == 2 and q == 1) return !((~n) & r); //\
    \ Lucas\n        long long k = n - r;\n        long long e0 = _ej(n / p) - _ej(r\
    \ / p) - _ej(k / p);\n        if (e0 >= q) return 0;\n\n        long long ret\
    \ = ppow[e0];\n        if (q == 1) { // Lucas\n            while (n) {\n     \
    \           ret = __int128(ret) * fac[n % p] * invfac[r % p] * invfac[k % p] %\
    \ p;\n                n /= p, r /= p, k /= p;\n            }\n            return\
    \ (int)ret;\n        } else {\n            if ((p > 2 or q < 3) and (_ej(n / m)\
    \ - _ej(r / m) - _ej(k / m)) & 1) ret = m - ret;\n            while (n) {\n  \
    \              ret = __int128(ret) * fac[n % m] * invfac[r % m] * invfac[k % m]\
    \ % m;\n                n /= p, r /= p, k /= p;\n            }\n            return\
    \ (int)ret;\n        }\n    }\n};\n\n// nCr mod m\n// Complexity: O(m) space worst\
    \ (construction), O(log(n) log(m)) (per query)\n// Input: pairs of (prime, degree),\
    \ such as vector<pair<int, int>> and map<int, int>\n// https://judge.yosupo.jp/problem/binomial_coefficient\n\
    struct combination {\n    std::vector<combination_prime_pow> cpps;\n    std::vector<int>\
    \ ms;\n\n    template <class Map> combination(const Map &p2deg) {\n        for\
    \ (auto f : p2deg) {\n            cpps.push_back(combination_prime_pow(f.first,\
    \ f.second));\n            ms.push_back(cpps.back().m);\n        }\n    }\n\n\
    \    int operator()(long long n, long long r) const {\n        if (r < 0 or n\
    \ < r) return 0;\n        std::vector<int> rs;\n        for (const auto &cpp :\
    \ cpps) rs.push_back(cpp.nCr(n, r));\n        return crt(rs, ms).first;\n    }\n\
    };\n"
  code: "#pragma once\n#include \"bare_mod_algebra.hpp\"\n#include <utility>\n#include\
    \ <vector>\n\n// nCr mod m = p^q (p: prime, q >= 1)\n// Can be used for n, r <=\
    \ 1e18, m <= 1e7\n// Complexity: O(m) (construction), O(log(n)) (per query)\n\
    // https://ferin-tech.hatenablog.com/entry/2018/01/17/010829\nstruct combination_prime_pow\
    \ {\n    int p, q, m;\n    std::vector<int> fac, invfac, ppow;\n\n    long long\
    \ _ej(long long n) const {\n        long long ret = 0;\n        while (n) ret\
    \ += n, n /= p;\n        return ret;\n    }\n\n    combination_prime_pow(int p_,\
    \ int q_) : p(p_), q(q_), m(1), ppow{1} {\n        for (int t = 0; t < q; ++t)\
    \ m *= p, ppow.push_back(m);\n        fac.assign(m, 1);\n        invfac.assign(m,\
    \ 1);\n        for (int i = 1; i < m; ++i) fac[i] = (long long)fac[i - 1] * (i\
    \ % p ? i : 1) % m;\n        invfac[m - 1] = fac[m - 1]; // Same as Wilson's theorem\n\
    \        assert(1LL * fac.back() * invfac.back() % m == 1);\n        for (int\
    \ i = m - 1; i; --i) invfac[i - 1] = (long long)invfac[i] * (i % p ? i : 1) %\
    \ m;\n    }\n\n    int nCr(long long n, long long r) const {\n        if (r <\
    \ 0 or n < r) return 0;\n        if (p == 2 and q == 1) return !((~n) & r); //\
    \ Lucas\n        long long k = n - r;\n        long long e0 = _ej(n / p) - _ej(r\
    \ / p) - _ej(k / p);\n        if (e0 >= q) return 0;\n\n        long long ret\
    \ = ppow[e0];\n        if (q == 1) { // Lucas\n            while (n) {\n     \
    \           ret = __int128(ret) * fac[n % p] * invfac[r % p] * invfac[k % p] %\
    \ p;\n                n /= p, r /= p, k /= p;\n            }\n            return\
    \ (int)ret;\n        } else {\n            if ((p > 2 or q < 3) and (_ej(n / m)\
    \ - _ej(r / m) - _ej(k / m)) & 1) ret = m - ret;\n            while (n) {\n  \
    \              ret = __int128(ret) * fac[n % m] * invfac[r % m] * invfac[k % m]\
    \ % m;\n                n /= p, r /= p, k /= p;\n            }\n            return\
    \ (int)ret;\n        }\n    }\n};\n\n// nCr mod m\n// Complexity: O(m) space worst\
    \ (construction), O(log(n) log(m)) (per query)\n// Input: pairs of (prime, degree),\
    \ such as vector<pair<int, int>> and map<int, int>\n// https://judge.yosupo.jp/problem/binomial_coefficient\n\
    struct combination {\n    std::vector<combination_prime_pow> cpps;\n    std::vector<int>\
    \ ms;\n\n    template <class Map> combination(const Map &p2deg) {\n        for\
    \ (auto f : p2deg) {\n            cpps.push_back(combination_prime_pow(f.first,\
    \ f.second));\n            ms.push_back(cpps.back().m);\n        }\n    }\n\n\
    \    int operator()(long long n, long long r) const {\n        if (r < 0 or n\
    \ < r) return 0;\n        std::vector<int> rs;\n        for (const auto &cpp :\
    \ cpps) rs.push_back(cpp.nCr(n, r));\n        return crt(rs, ms).first;\n    }\n\
    };\n"
  dependsOn:
  - number/bare_mod_algebra.hpp
  isVerificationFile: false
  path: number/combination.hpp
  requiredBy: []
  timestamp: '2022-10-14 10:52:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/combination.stress.test.cpp
  - number/test/combination.test.cpp
documentation_of: number/combination.hpp
layout: document
title: "Combination \uFF08${}_n \\mathrm{C}_r \\bmod{m}$\uFF0CLucas \u306E\u5B9A\u7406\
  \u306E\u62E1\u5F35\uFF09"
---

固定された正整数 $m = p\_1^{q\_1} \dots p\_{k}^{q\_k} ( \le 10^7)$ について，$\binom{n}{r} \bmod{m}$ の値を計算する．前計算 $O(\sum_i p\_i^{q\_i})$，クエリ $O(k \mathrm{log}(n))$．

## 原理

$m$ を素因数分解し，各素数冪 $p^q$ を法とした $\binom{n}{r}$ の値を拡張 Lucas の定理を用いて計算し，中国剰余定理を用いて解を復元する．

## 使用方法

コンストラクタには法 $m$ を素因数分解した結果の（素数，次数）の組として（例：`vector<pair<int, int>>`, `map<int, int>` ）与える．例えば $\bmod{60}$ で計算したい場合は `{2, 2}, {3, 1}, {5, 1}` を与えればよい．また，本ライブラリの `Sieve` クラスの `factorize()` が返す結果をそのまま渡してもよい：

```cpp
combination nCr(Sieve(1 << 20).factorize(mod));
cout << nCr(n, r) << '\n';
```

## 問題例

- [Library Checker: Binomial Coefficient](https://judge.yosupo.jp/problem/binomial_coefficient)

## リンク

- [2015 ICL, Finals, Div. 1　J. Ceizenpok’s formula (nCk mod m の求め方) - ferinの競プロ帳](https://ferin-tech.hatenablog.com/entry/2018/01/17/010829)
