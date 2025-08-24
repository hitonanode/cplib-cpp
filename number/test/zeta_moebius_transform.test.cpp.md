---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: number/sieve.hpp
    title: "Linear sieve \uFF08\u7DDA\u5F62\u7BE9\uFF09"
  - icon: ':heavy_check_mark:'
    path: number/zeta_moebius_transform.hpp
    title: "Zeta transform / Moebius transform \uFF08\u7D04\u6570\u5305\u9664\uFF09"
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
  bundledCode: "#line 1 \"number/test/zeta_moebius_transform.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\" // DUMMY\n\
    #line 2 \"number/sieve.hpp\"\n#include <cassert>\n#include <map>\n#include <vector>\n\
    \n// CUT begin\n// Linear sieve algorithm for fast prime factorization\n// Complexity:\
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
    #line 3 \"number/zeta_moebius_transform.hpp\"\n#include <algorithm>\n#line 5 \"\
    number/zeta_moebius_transform.hpp\"\n#include <utility>\n#line 7 \"number/zeta_moebius_transform.hpp\"\
    \n\n// f[n] \u306B\u5BFE\u3057\u3066\u3001\u5168\u3066\u306E n \u306E\u500D\u6570\
    \ n*i \u306B\u5BFE\u3059\u308B f[n*i] \u306E\u548C\u304C\u51FA\u3066\u304F\u308B\
    \ \u8A08\u7B97\u91CF O(N loglog N)\n// \u7D20\u6570p\u6BCE\u306B\u51E6\u7406\u3059\
    \u308B\u9AD8\u901F\u30BC\u30FC\u30BF\u5909\u63DB\n// \u4F7F\u7528\u4F8B https://yukicoder.me/submissions/385043\n\
    template <class T> void multiple_zeta(std::vector<T> &f) {\n    int N = int(f.size())\
    \ - 1;\n    std::vector<int> is_prime(N + 1, 1);\n    for (int p = 2; p <= N;\
    \ p++) {\n        if (is_prime[p]) {\n            for (int q = p * 2; q <= N;\
    \ q += p) is_prime[q] = 0;\n            for (int j = N / p; j > 0; --j) f[j] +=\
    \ f[j * p];\n        }\n    }\n}\n\n// inverse of multiple_zeta O(N loglog N)\n\
    // \u4F7F\u7528\u4F8B https://yukicoder.me/submissions/385120\ntemplate <class\
    \ T> void multiple_moebius(std::vector<T> &f) {\n    int N = int(f.size()) - 1;\n\
    \    std::vector<int> is_prime(N + 1, 1);\n    for (int p = 2; p <= N; p++) {\n\
    \        if (is_prime[p]) {\n            for (int q = p * 2; q <= N; q += p) is_prime[q]\
    \ = 0;\n            for (int j = 1; j * p <= N; ++j) f[j] -= f[j * p];\n     \
    \   }\n    }\n}\n\n// f[n] \u306B\u95A2\u3057\u3066\u3001\u5168\u3066\u306E n\
    \ \u306E\u7D04\u6570 m \u306B\u5BFE\u3059\u308B f[m] \u306E\u7DCF\u548C\u304C\u51FA\
    \u3066\u304F\u308B \u8A08\u7B97\u91CF O(N loglog N)\ntemplate <class T> void divisor_zeta(std::vector<T>\
    \ &f) {\n    int N = int(f.size()) - 1;\n    std::vector<int> is_prime(N + 1,\
    \ 1);\n    for (int p = 2; p <= N; ++p) {\n        if (is_prime[p]) {\n      \
    \      for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;\n            for (int\
    \ j = 1; j * p <= N; ++j) f[j * p] += f[j];\n        }\n    }\n}\n// inverse of\
    \ divisor_zeta()\n// Verified: https://codeforces.com/contest/1630/problem/E\n\
    template <class T> void divisor_moebius(std::vector<T> &f) {\n    int N = int(f.size())\
    \ - 1;\n    std::vector<int> is_prime(N + 1, 1);\n    for (int p = 2; p <= N;\
    \ ++p) {\n        if (is_prime[p]) {\n            for (int q = p * 2; q <= N;\
    \ q += p) is_prime[q] = 0;\n            for (int j = N / p; j > 0; --j) f[j *\
    \ p] -= f[j];\n        }\n    }\n}\n\n// GCD convolution\n// ret[k] = \\sum_{gcd(i,\
    \ j) = k} f[i] * g[j]\ntemplate <class T> std::vector<T> gcdconv(std::vector<T>\
    \ f, std::vector<T> g) {\n    assert(f.size() == g.size());\n    multiple_zeta(f);\n\
    \    multiple_zeta(g);\n    for (int i = 0; i < int(g.size()); ++i) f[i] *= g[i];\n\
    \    multiple_moebius(f);\n    return f;\n}\n\n// LCM convolution\n// ret[k] =\
    \ \\sum_{lcm(i, j) = k} f[i] * g[j]\ntemplate <class T> std::vector<T> lcmconv(std::vector<T>\
    \ f, std::vector<T> g) {\n    assert(f.size() == g.size());\n    divisor_zeta(f);\n\
    \    divisor_zeta(g);\n    for (int i = 0; i < int(g.size()); ++i) f[i] *= g[i];\n\
    \    divisor_moebius(f);\n    return f;\n}\n\n// fast_integer_moebius \u306E\u9AD8\
    \u901F\u5316\uFF08\u767B\u5834\u3057\u306A\u3044\u7D20\u56E0\u6570\u304C\u591A\
    \u3051\u308C\u3070\u8A08\u7B97\u91CF\u6539\u5584\uFF09\n// Requirement: f \u306E\
    \ key \u3068\u3057\u3066\u767B\u5834\u3059\u308B\u6B63\u6574\u6570\u306E\u5168\
    \u3066\u306E\u7D04\u6570\u304C key \u3068\u3057\u3066\u767B\u5834\n// Verified:\
    \ https://toph.co/p/height-of-the-trees\ntemplate <typename Int, typename Val>\n\
    void sparse_fast_integer_moebius(std::vector<std::pair<Int, Val>> &f, const Sieve\
    \ &sieve) {\n    if (f.empty()) return;\n    std::sort(f.begin(), f.end());\n\
    \    assert(f.back().first < Int(sieve.min_factor.size()));\n    std::vector<Int>\
    \ primes;\n    for (auto p : f) {\n        if (sieve.min_factor[p.first] == p.first)\
    \ primes.push_back(p.first);\n    }\n    std::vector<std::vector<int>> p2is(primes.size());\n\
    \    for (int i = 0; i < int(f.size()); i++) {\n        Int a = f[i].first, pold\
    \ = 0;\n        int k = 0;\n        while (a > 1) {\n            auto p = sieve.min_factor[a];\n\
    \            if (p != pold) {\n                while (primes[k] != p) k++;\n \
    \               p2is[k].emplace_back(i);\n            }\n            pold = p,\
    \ a /= p;\n        }\n    }\n    for (int d = 0; d < int(primes.size()); d++)\
    \ {\n        Int p = primes[d];\n        for (auto i : p2is[d]) {\n          \
    \  auto comp = [](const std::pair<Int, Val> &l, const std::pair<Int, Val> &r)\
    \ {\n                return l.first < r.first;\n            };\n            auto\
    \ itr = std::lower_bound(f.begin(), f.end(), std::make_pair(f[i].first / p, 0),\
    \ comp);\n            itr->second -= f[i].second;\n        }\n    }\n}\n#line\
    \ 3 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#line 6 \"modint.hpp\"\
    \n\ntemplate <int md> struct ModInt {\n    static_assert(md > 1);\n    using lint\
    \ = long long;\n    constexpr static int mod() { return md; }\n    static int\
    \ get_primitive_root() {\n        static int primitive_root = 0;\n        if (!primitive_root)\
    \ {\n            primitive_root = [&]() {\n                std::set<int> fac;\n\
    \                int v = md - 1;\n                for (lint i = 2; i * i <= v;\
    \ i++)\n                    while (v % i == 0) fac.insert(i), v /= i;\n      \
    \          if (v > 1) fac.insert(v);\n                for (int g = 1; g < md;\
    \ g++) {\n                    bool ok = true;\n                    for (auto i\
    \ : fac)\n                        if (ModInt(g).pow((md - 1) / i) == 1) {\n  \
    \                          ok = false;\n                            break;\n \
    \                       }\n                    if (ok) return g;\n           \
    \     }\n                return -1;\n            }();\n        }\n        return\
    \ primitive_root;\n    }\n    int val_;\n    int val() const noexcept { return\
    \ val_; }\n    constexpr ModInt() : val_(0) {}\n    constexpr ModInt &_setval(lint\
    \ v) { return val_ = (v >= md ? v - md : v), *this; }\n    constexpr ModInt(lint\
    \ v) { _setval(v % md + md); }\n    constexpr explicit operator bool() const {\
    \ return val_ != 0; }\n    constexpr ModInt operator+(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    constexpr ModInt\
    \ operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ - x.val_ + md);\n    }\n    constexpr ModInt operator*(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    constexpr\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.inv().val() % md);\n    }\n    constexpr ModInt operator-() const { return\
    \ ModInt()._setval(md - val_); }\n    constexpr ModInt &operator+=(const ModInt\
    \ &x) { return *this = *this + x; }\n    constexpr ModInt &operator-=(const ModInt\
    \ &x) { return *this = *this - x; }\n    constexpr ModInt &operator*=(const ModInt\
    \ &x) { return *this = *this * x; }\n    constexpr ModInt &operator/=(const ModInt\
    \ &x) { return *this = *this / x; }\n    friend constexpr ModInt operator+(lint\
    \ a, const ModInt &x) { return ModInt(a) + x; }\n    friend constexpr ModInt operator-(lint\
    \ a, const ModInt &x) { return ModInt(a) - x; }\n    friend constexpr ModInt operator*(lint\
    \ a, const ModInt &x) { return ModInt(a) * x; }\n    friend constexpr ModInt operator/(lint\
    \ a, const ModInt &x) { return ModInt(a) / x; }\n    constexpr bool operator==(const\
    \ ModInt &x) const { return val_ == x.val_; }\n    constexpr bool operator!=(const\
    \ ModInt &x) const { return val_ != x.val_; }\n    constexpr bool operator<(const\
    \ ModInt &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    constexpr\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n\n    constexpr ModInt pow(lint n) const {\n\
    \        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n\
    \ & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static constexpr int cache_limit = std::min(md, 1 << 21);\n\
    \    static std::vector<ModInt> facs, facinvs, invs;\n\n    constexpr static void\
    \ _precalculation(int N) {\n        const int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n\n    constexpr\
    \ ModInt inv() const {\n        if (this->val_ < cache_limit) {\n            if\
    \ (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n            while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val_];\n\
    \        } else {\n            return this->pow(md - 2);\n        }\n    }\n\n\
    \    constexpr static ModInt fac(int n) {\n        assert(n >= 0);\n        if\
    \ (n >= md) return ModInt(0);\n        while (n >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facs[n];\n    }\n\n    constexpr static ModInt facinv(int\
    \ n) {\n        assert(n >= 0);\n        if (n >= md) return ModInt(0);\n    \
    \    while (n >= int(facs.size())) _precalculation(facs.size() * 2);\n       \
    \ return facinvs[n];\n    }\n\n    constexpr static ModInt doublefac(int n) {\n\
    \        assert(n >= 0);\n        if (n >= md) return ModInt(0);\n        long\
    \ long k = (n + 1) / 2;\n        return (n & 1) ? ModInt::fac(k * 2) / (ModInt(2).pow(k)\
    \ * ModInt::fac(k))\n                       : ModInt::fac(k) * ModInt(2).pow(k);\n\
    \    }\n\n    constexpr static ModInt nCr(int n, int r) {\n        assert(n >=\
    \ 0);\n        if (r < 0 or n < r) return ModInt(0);\n        return ModInt::fac(n)\
    \ * ModInt::facinv(r) * ModInt::facinv(n - r);\n    }\n\n    constexpr static\
    \ ModInt nPr(int n, int r) {\n        assert(n >= 0);\n        if (r < 0 or n\
    \ < r) return ModInt(0);\n        return ModInt::fac(n) * ModInt::facinv(n - r);\n\
    \    }\n\n    static ModInt binom(int n, int r) {\n        static long long bruteforce_times\
    \ = 0;\n\n        if (r < 0 or n < r) return ModInt(0);\n        if (n <= bruteforce_times\
    \ or n < (int)facs.size()) return ModInt::nCr(n, r);\n\n        r = std::min(r,\
    \ n - r);\n\n        ModInt ret = ModInt::facinv(r);\n        for (int i = 0;\
    \ i < r; ++i) ret *= n - i;\n        bruteforce_times += r;\n\n        return\
    \ ret;\n    }\n\n    // Multinomial coefficient, (k_1 + k_2 + ... + k_m)! / (k_1!\
    \ k_2! ... k_m!)\n    // Complexity: O(sum(ks))\n    template <class Vec> static\
    \ ModInt multinomial(const Vec &ks) {\n        ModInt ret{1};\n        int sum\
    \ = 0;\n        for (int k : ks) {\n            assert(k >= 0);\n            ret\
    \ *= ModInt::facinv(k), sum += k;\n        }\n        return ret * ModInt::fac(sum);\n\
    \    }\n    template <class... Args> static ModInt multinomial(Args... args) {\n\
    \        int sum = (0 + ... + args);\n        ModInt result = (1 * ... * ModInt::facinv(args));\n\
    \        return ModInt::fac(sum) * result;\n    }\n\n    // Catalan number, C_n\
    \ = binom(2n, n) / (n + 1) = # of Dyck words of length 2n\n    // C_0 = 1, C_1\
    \ = 1, C_2 = 2, C_3 = 5, C_4 = 14, ...\n    // https://oeis.org/A000108\n    //\
    \ Complexity: O(n)\n    static ModInt catalan(int n) {\n        if (n < 0) return\
    \ ModInt(0);\n        return ModInt::fac(n * 2) * ModInt::facinv(n + 1) * ModInt::facinv(n);\n\
    \    }\n\n    ModInt sqrt() const {\n        if (val_ == 0) return 0;\n      \
    \  if (md == 2) return val_;\n        if (pow((md - 1) / 2) != 1) return 0;\n\
    \        ModInt b = 1;\n        while (b.pow((md - 1) / 2) == 1) b += 1;\n   \
    \     int e = 0, m = md - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n     \
    \   ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n\
    \        ModInt z = b.pow(m);\n        while (y != 1) {\n            int j = 0;\n\
    \            ModInt t = y;\n            while (t != 1) j++, t *= t;\n        \
    \    z = z.pow(1LL << (e - j - 1));\n            x *= z, z *= z, y *= z;\n   \
    \         e = j;\n        }\n        return ModInt(std::min(x.val_, md - x.val_));\n\
    \    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\ntemplate\
    \ <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 7 \"number/test/zeta_moebius_transform.test.cpp\"\nusing namespace std;\n\
    \nusing mint = ModInt<1000000007>;\n\nlong long state = 1;\nmint rndgen() {\n\
    \    state = (state * 1234567 + 890123) % mint::mod();\n    return mint(state);\n\
    }\nvector<mint> vecgen(int n) {\n    vector<mint> ret(n + 1);\n    for (int i\
    \ = 1; i <= n; ++i) ret[i] = rndgen();\n    return ret;\n}\n\nvoid test_divisor_zeta()\
    \ {\n    for (int n = 1; n <= 100; ++n) {\n        for (int iter = 0; iter < 10;\
    \ ++iter) {\n            vector<mint> x = vecgen(n), y(n + 1);\n            for\
    \ (int i = 1; i <= n; ++i) {\n                for (int j = 1; j <= i; ++j) {\n\
    \                    if (i % j == 0) y[i] += x[j];\n                }\n      \
    \      }\n            divisor_zeta(x);\n            assert(x == y);\n        }\n\
    \    }\n}\n\nvoid test_divisor_moebius() {\n    for (int n = 1; n <= 100; ++n)\
    \ {\n        for (int iter = 0; iter < 10; ++iter) {\n            vector<mint>\
    \ x = vecgen(n), y = x;\n            divisor_zeta(x);\n            divisor_moebius(x);\n\
    \            assert(x == y);\n        }\n    }\n}\n\nvoid test_multiple_zeta()\
    \ {\n    for (int n = 1; n <= 100; ++n) {\n        for (int iter = 0; iter < 10;\
    \ ++iter) {\n            vector<mint> x = vecgen(n), y(n + 1);\n            for\
    \ (int i = 1; i <= n; ++i) {\n                for (int j = i; j <= n; ++j) {\n\
    \                    if (j % i == 0) y[i] += x[j];\n                }\n      \
    \      }\n            multiple_zeta(x);\n            assert(x == y);\n       \
    \ }\n    }\n}\n\nvoid test_multiple_moebius() {\n    for (int n = 1; n <= 100;\
    \ ++n) {\n        for (int iter = 0; iter < 10; ++iter) {\n            vector<mint>\
    \ x = vecgen(n), y = x;\n            multiple_zeta(x);\n            multiple_moebius(x);\n\
    \            assert(x == y);\n        }\n    }\n}\n\nvoid test_gcdconv() {\n \
    \   for (int n = 1; n <= 100; ++n) {\n        for (int iter = 0; iter < 10; ++iter)\
    \ {\n            vector<mint> x = vecgen(n), y = vecgen(n), z(n + 1);\n      \
    \      auto conv = gcdconv(x, y);\n            for (int i = 1; i <= n; ++i) {\n\
    \                for (int j = 1; j <= n; ++j) z[__gcd(i, j)] += x[i] * y[j];\n\
    \            }\n            assert(conv == z);\n        }\n    }\n}\n\nvoid test_lcmconv()\
    \ {\n    for (int n = 1; n <= 100; ++n) {\n        for (int iter = 0; iter < 10;\
    \ ++iter) {\n            vector<mint> x = vecgen(n), y = vecgen(n), z(n + 1);\n\
    \            auto conv = lcmconv(x, y);\n            for (int i = 1; i <= n; ++i)\
    \ {\n                for (int j = 1; j <= n; ++j) {\n                    int l\
    \ = i * j / __gcd(i, j);\n                    if (l <= n) z[l] += x[i] * y[j];\n\
    \                }\n            }\n            assert(conv == z);\n        }\n\
    \    }\n}\n\nint main() {\n    test_divisor_zeta();\n    test_divisor_moebius();\n\
    \    test_multiple_zeta();\n    test_multiple_moebius();\n    test_gcdconv();\n\
    \    test_lcmconv();\n    cout << \"Hello World\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../zeta_moebius_transform.hpp\"\n#include \"../../modint.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <vector>\nusing namespace\
    \ std;\n\nusing mint = ModInt<1000000007>;\n\nlong long state = 1;\nmint rndgen()\
    \ {\n    state = (state * 1234567 + 890123) % mint::mod();\n    return mint(state);\n\
    }\nvector<mint> vecgen(int n) {\n    vector<mint> ret(n + 1);\n    for (int i\
    \ = 1; i <= n; ++i) ret[i] = rndgen();\n    return ret;\n}\n\nvoid test_divisor_zeta()\
    \ {\n    for (int n = 1; n <= 100; ++n) {\n        for (int iter = 0; iter < 10;\
    \ ++iter) {\n            vector<mint> x = vecgen(n), y(n + 1);\n            for\
    \ (int i = 1; i <= n; ++i) {\n                for (int j = 1; j <= i; ++j) {\n\
    \                    if (i % j == 0) y[i] += x[j];\n                }\n      \
    \      }\n            divisor_zeta(x);\n            assert(x == y);\n        }\n\
    \    }\n}\n\nvoid test_divisor_moebius() {\n    for (int n = 1; n <= 100; ++n)\
    \ {\n        for (int iter = 0; iter < 10; ++iter) {\n            vector<mint>\
    \ x = vecgen(n), y = x;\n            divisor_zeta(x);\n            divisor_moebius(x);\n\
    \            assert(x == y);\n        }\n    }\n}\n\nvoid test_multiple_zeta()\
    \ {\n    for (int n = 1; n <= 100; ++n) {\n        for (int iter = 0; iter < 10;\
    \ ++iter) {\n            vector<mint> x = vecgen(n), y(n + 1);\n            for\
    \ (int i = 1; i <= n; ++i) {\n                for (int j = i; j <= n; ++j) {\n\
    \                    if (j % i == 0) y[i] += x[j];\n                }\n      \
    \      }\n            multiple_zeta(x);\n            assert(x == y);\n       \
    \ }\n    }\n}\n\nvoid test_multiple_moebius() {\n    for (int n = 1; n <= 100;\
    \ ++n) {\n        for (int iter = 0; iter < 10; ++iter) {\n            vector<mint>\
    \ x = vecgen(n), y = x;\n            multiple_zeta(x);\n            multiple_moebius(x);\n\
    \            assert(x == y);\n        }\n    }\n}\n\nvoid test_gcdconv() {\n \
    \   for (int n = 1; n <= 100; ++n) {\n        for (int iter = 0; iter < 10; ++iter)\
    \ {\n            vector<mint> x = vecgen(n), y = vecgen(n), z(n + 1);\n      \
    \      auto conv = gcdconv(x, y);\n            for (int i = 1; i <= n; ++i) {\n\
    \                for (int j = 1; j <= n; ++j) z[__gcd(i, j)] += x[i] * y[j];\n\
    \            }\n            assert(conv == z);\n        }\n    }\n}\n\nvoid test_lcmconv()\
    \ {\n    for (int n = 1; n <= 100; ++n) {\n        for (int iter = 0; iter < 10;\
    \ ++iter) {\n            vector<mint> x = vecgen(n), y = vecgen(n), z(n + 1);\n\
    \            auto conv = lcmconv(x, y);\n            for (int i = 1; i <= n; ++i)\
    \ {\n                for (int j = 1; j <= n; ++j) {\n                    int l\
    \ = i * j / __gcd(i, j);\n                    if (l <= n) z[l] += x[i] * y[j];\n\
    \                }\n            }\n            assert(conv == z);\n        }\n\
    \    }\n}\n\nint main() {\n    test_divisor_zeta();\n    test_divisor_moebius();\n\
    \    test_multiple_zeta();\n    test_multiple_moebius();\n    test_gcdconv();\n\
    \    test_lcmconv();\n    cout << \"Hello World\\n\";\n}\n"
  dependsOn:
  - number/zeta_moebius_transform.hpp
  - number/sieve.hpp
  - modint.hpp
  isVerificationFile: true
  path: number/test/zeta_moebius_transform.test.cpp
  requiredBy: []
  timestamp: '2025-08-25 00:44:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/zeta_moebius_transform.test.cpp
layout: document
redirect_from:
- /verify/number/test/zeta_moebius_transform.test.cpp
- /verify/number/test/zeta_moebius_transform.test.cpp.html
title: number/test/zeta_moebius_transform.test.cpp
---
