---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/bare_mod_algebra.hpp
    title: number/bare_mod_algebra.hpp
  - icon: ':heavy_check_mark:'
    path: number/combination.hpp
    title: "Combination \uFF08${}_n \\mathrm{C}_r \\bmod{m}$\uFF0CLucas \u306E\u5B9A\
      \u7406\u306E\u62E1\u5F35\uFF09"
  - icon: ':heavy_check_mark:'
    path: number/sieve.hpp
    title: "Linear sieve \uFF08\u7DDA\u5F62\u7BE9\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/binomial_coefficient
    links:
    - https://judge.yosupo.jp/problem/binomial_coefficient
  bundledCode: "#line 1 \"number/test/combination.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\
    \n#line 2 \"number/bare_mod_algebra.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <tuple>\n#include <utility>\n#include <vector>\n\n// CUT begin\n// Solve\
    \ ax+by=gcd(a, b)\ntemplate <class Int> Int extgcd(Int a, Int b, Int &x, Int &y)\
    \ {\n    Int d = a;\n    if (b != 0) {\n        d = extgcd(b, a % b, y, x), y\
    \ -= (a / b) * x;\n    } else {\n        x = 1, y = 0;\n    }\n    return d;\n\
    }\n// Calculate a^(-1) (MOD m) s if gcd(a, m) == 1\n// Calculate x s.t. ax ==\
    \ gcd(a, m) MOD m\ntemplate <class Int> Int mod_inverse(Int a, Int m) {\n    Int\
    \ x, y;\n    extgcd<Int>(a, m, x, y);\n    x %= m;\n    return x + (x < 0) * m;\n\
    }\n\n// Require: 1 <= b\n// return: (g, x) s.t. g = gcd(a, b), xa = g MOD b, 0\
    \ <= x < b/g\ntemplate <class Int> /* constexpr */ std::pair<Int, Int> inv_gcd(Int\
    \ a, Int b) {\n    a %= b;\n    if (a < 0) a += b;\n    if (a == 0) return {b,\
    \ 0};\n    Int s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n        Int u =\
    \ s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp = s;\n        s\
    \ = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0 < 0) m0 += b /\
    \ s;\n    return {s, m0};\n}\n\ntemplate <class Int>\n/* constexpr */ std::pair<Int,\
    \ Int> crt(const std::vector<Int> &r, const std::vector<Int> &m) {\n    assert(r.size()\
    \ == m.size());\n    int n = int(r.size());\n    // Contracts: 0 <= r0 < m0\n\
    \    Int r0 = 0, m0 = 1;\n    for (int i = 0; i < n; i++) {\n        assert(1\
    \ <= m[i]);\n        Int r1 = r[i] % m[i], m1 = m[i];\n        if (r1 < 0) r1\
    \ += m1;\n        if (m0 < m1) {\n            std::swap(r0, r1);\n           \
    \ std::swap(m0, m1);\n        }\n        if (m0 % m1 == 0) {\n            if (r0\
    \ % m1 != r1) return {0, 0};\n            continue;\n        }\n        Int g,\
    \ im;\n        std::tie(g, im) = inv_gcd<Int>(m0, m1);\n\n        Int u1 = m1\
    \ / g;\n        if ((r1 - r0) % g) return {0, 0};\n\n        Int x = (r1 - r0)\
    \ / g % u1 * im % u1;\n        r0 += x * m0;\n        m0 *= u1;\n        if (r0\
    \ < 0) r0 += m0;\n    }\n    return {r0, m0};\n}\n\n// \u87FB\u672C P.262\n//\
    \ \u4E2D\u56FD\u5270\u4F59\u5B9A\u7406\u3092\u5229\u7528\u3057\u3066\uFF0C\u8272\
    \u3005\u306A\u7D20\u6570\u3067\u5272\u3063\u305F\u4F59\u308A\u304B\u3089\u5143\
    \u306E\u5024\u3092\u5FA9\u5143\n// \u9023\u7ACB\u7DDA\u5F62\u5408\u540C\u5F0F\
    \ A * x = B mod M \u306E\u89E3\n// Requirement: M[i] > 0\n// Output: x = first\
    \ MOD second (if solution exists), (0, 0) (otherwise)\ntemplate <class Int>\n\
    std::pair<Int, Int>\nlinear_congruence(const std::vector<Int> &A, const std::vector<Int>\
    \ &B, const std::vector<Int> &M) {\n    Int r = 0, m = 1;\n    assert(A.size()\
    \ == M.size());\n    assert(B.size() == M.size());\n    for (int i = 0; i < (int)A.size();\
    \ i++) {\n        assert(M[i] > 0);\n        const Int ai = A[i] % M[i];\n   \
    \     Int a = ai * m, b = B[i] - ai * r, d = std::__gcd(M[i], a);\n        if\
    \ (b % d != 0) {\n            return std::make_pair(0, 0); // \u89E3\u306A\u3057\
    \n        }\n        Int t = b / d * mod_inverse<Int>(a / d, M[i] / d) % (M[i]\
    \ / d);\n        r += m * t;\n        m *= M[i] / d;\n    }\n    return std::make_pair((r\
    \ < 0 ? r + m : r), m);\n}\n\nint pow_mod(int x, long long n, int md) {\n    if\
    \ (md == 1) return 0;\n    long long ans = 1;\n    while (n > 0) {\n        if\
    \ (n & 1) ans = ans * x % md;\n        x = (long long)x * x % md;\n        n >>=\
    \ 1;\n    }\n    return ans;\n}\n#line 5 \"number/combination.hpp\"\n\n// nCr\
    \ mod m = p^q (p: prime, q >= 1)\n// Can be used for n, r <= 1e18, m <= 1e7\n\
    // Complexity: O(m) (construction), O(log(n)) (per query)\n// https://ferin-tech.hatenablog.com/entry/2018/01/17/010829\n\
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
    };\n#line 3 \"number/sieve.hpp\"\n#include <map>\n#line 5 \"number/sieve.hpp\"\
    \n\n// CUT begin\n// Linear sieve algorithm for fast prime factorization\n// Complexity:\
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
    #line 4 \"number/test/combination.test.cpp\"\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int T, m;\n    cin >> T >> m;\n    combination nCr(Sieve(1 << 15).factorize(m));\n\
    \    while (T--) {\n        long long n, r;\n        cin >> n >> r;\n        cout\
    \ << nCr(n, r) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\n\
    #include \"../combination.hpp\"\n#include \"../sieve.hpp\"\n#include <iostream>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int T, m;\n    cin >> T >> m;\n    combination nCr(Sieve(1 << 15).factorize(m));\n\
    \    while (T--) {\n        long long n, r;\n        cin >> n >> r;\n        cout\
    \ << nCr(n, r) << '\\n';\n    }\n}\n"
  dependsOn:
  - number/combination.hpp
  - number/bare_mod_algebra.hpp
  - number/sieve.hpp
  isVerificationFile: true
  path: number/test/combination.test.cpp
  requiredBy: []
  timestamp: '2021-10-30 11:40:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/combination.test.cpp
layout: document
redirect_from:
- /verify/number/test/combination.test.cpp
- /verify/number/test/combination.test.cpp.html
title: number/test/combination.test.cpp
---
