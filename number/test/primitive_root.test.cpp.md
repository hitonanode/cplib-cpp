---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
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
    PROBLEM: https://yukicoder.me/problems/no/931
    links:
    - https://yukicoder.me/problems/no/931
  bundledCode: "#line 1 \"number/test/primitive_root.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/931\"\n#line 2 \"number/bare_mod_algebra.hpp\"\
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
    \ 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#line 5 \"modint.hpp\"\
    \n\ntemplate <int md> struct ModInt {\n#if __cplusplus >= 201402L\n#define MDCONST\
    \ constexpr\n#else\n#define MDCONST\n#endif\n    using lint = long long;\n   \
    \ MDCONST static int mod() { return md; }\n    static int get_primitive_root()\
    \ {\n        static int primitive_root = 0;\n        if (!primitive_root) {\n\
    \            primitive_root = [&]() {\n                std::set<int> fac;\n  \
    \              int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n\
    \                    while (v % i == 0) fac.insert(i), v /= i;\n             \
    \   if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((md - 1) / i) == 1) {\n           \
    \                 ok = false;\n                            break;\n          \
    \              }\n                    if (ok) return g;\n                }\n \
    \               return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    MDCONST\
    \ ModInt() : val_(0) {}\n    MDCONST ModInt &_setval(lint v) { return val_ = (v\
    \ >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint v) { _setval(v % md +\
    \ md); }\n    MDCONST explicit operator bool() const { return val_ != 0; }\n \
    \   MDCONST ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    MDCONST ModInt operator-(const ModInt &x) const {\n \
    \       return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    MDCONST\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    MDCONST ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    MDCONST ModInt operator-() const { return ModInt()._setval(md - val_); }\n\
    \    MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md + x.val_);\n    }\n    friend MDCONST ModInt operator-(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md - x.val_ + md);\n\
    \    }\n    friend MDCONST ModInt operator*(lint a, const ModInt &x) {\n     \
    \   return ModInt()._setval(a % md * x.val_ % md);\n    }\n    friend MDCONST\
    \ ModInt operator/(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.inv().val() % md);\n    }\n    MDCONST bool operator==(const ModInt\
    \ &x) const { return val_ == x.val_; }\n    MDCONST bool operator!=(const ModInt\
    \ &x) const { return val_ != x.val_; }\n    MDCONST bool operator<(const ModInt\
    \ &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const {\n    \
    \    ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n & 1)\
    \ ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return ans;\n\
    \    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n    MDCONST\
    \ ModInt inv() const {\n        if (this->val_ < std::min(md >> 1, 1 << 21)) {\n\
    \            if (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n      \
    \      while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \            return invs[this->val_];\n        } else {\n            return this->pow(md\
    \ - 2);\n        }\n    }\n    MDCONST ModInt fac() const {\n        while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n        return facs[this->val_];\n\
    \    }\n    MDCONST ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    MDCONST ModInt doublefac() const {\n        lint k = (this->val_ + 1)\
    \ / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val_\
    \ < r.val_) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n  \
    \  MDCONST ModInt nPr(const ModInt &r) const {\n        return (this->val_ < r.val_)\
    \ ? 0 : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const\
    \ {\n        if (val_ == 0) return 0;\n        if (md == 2) return val_;\n   \
    \     if (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while\
    \ (b.pow((md - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n       \
    \ while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this)\
    \ * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while\
    \ (y != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 3 \"convolution/ntt.hpp\"\n\n#line 9 \"convolution/ntt.hpp\"\n\n// CUT begin\n\
    // Integer convolution for arbitrary mod\n// with NTT (and Garner's algorithm)\
    \ for ModInt / ModIntRuntime class.\n// We skip Garner's algorithm if `skip_garner`\
    \ is true or mod is in `nttprimes`.\n// input: a (size: n), b (size: m)\n// return:\
    \ vector (size: n + m - 1)\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT>\
    \ a, std::vector<MODINT> b, bool skip_garner);\n\nconstexpr int nttprimes[3] =\
    \ {998244353, 167772161, 469762049};\n\n// Integer FFT (Fast Fourier Transform)\
    \ for ModInt class\n// (Also known as Number Theoretic Transform, NTT)\n// is_inverse:\
    \ inverse transform\n// ** Input size must be 2^n **\ntemplate <typename MODINT>\
    \ void ntt(std::vector<MODINT> &a, bool is_inverse = false) {\n    int n = a.size();\n\
    \    if (n == 1) return;\n    static const int mod = MODINT::mod();\n    static\
    \ const MODINT root = MODINT::get_primitive_root();\n    assert(__builtin_popcount(n)\
    \ == 1 and (mod - 1) % n == 0);\n\n    static std::vector<MODINT> w{1}, iw{1};\n\
    \    for (int m = w.size(); m < n / 2; m *= 2) {\n        MODINT dw = root.pow((mod\
    \ - 1) / (4 * m)), dwinv = 1 / dw;\n        w.resize(m * 2), iw.resize(m * 2);\n\
    \        for (int i = 0; i < m; i++) w[m + i] = w[i] * dw, iw[m + i] = iw[i] *\
    \ dwinv;\n    }\n\n    if (!is_inverse) {\n        for (int m = n; m >>= 1;) {\n\
    \            for (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n              \
    \  for (int i = s; i < s + m; i++) {\n                    MODINT x = a[i], y =\
    \ a[i + m] * w[k];\n                    a[i] = x + y, a[i + m] = x - y;\n    \
    \            }\n            }\n        }\n    } else {\n        for (int m = 1;\
    \ m < n; m *= 2) {\n            for (int s = 0, k = 0; s < n; s += 2 * m, k++)\
    \ {\n                for (int i = s; i < s + m; i++) {\n                    MODINT\
    \ x = a[i], y = a[i + m];\n                    a[i] = x + y, a[i + m] = (x - y)\
    \ * iw[k];\n                }\n            }\n        }\n        int n_inv = MODINT(n).inv().val();\n\
    \        for (auto &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
    \ nttconv_(const std::vector<int> &a, const std::vector<int> &b) {\n    int sz\
    \ = a.size();\n    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n\
    \    std::vector<ModInt<MOD>> ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++)\
    \ ap[i] = a[i], bp[i] = b[i];\n    ntt(ap, false);\n    if (a == b)\n        bp\
    \ = ap;\n    else\n        ntt(bp, false);\n    for (int i = 0; i < sz; i++) ap[i]\
    \ *= bp[i];\n    ntt(ap, true);\n    return ap;\n}\nlong long garner_ntt_(int\
    \ r0, int r1, int r2, int mod) {\n    using mint2 = ModInt<nttprimes[2]>;\n  \
    \  static const long long m01 = 1LL * nttprimes[0] * nttprimes[1];\n    static\
    \ const long long m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv().val();\n\
    \    static const long long m01_inv_m2 = mint2(m01).inv().val();\n\n    int v1\
    \ = (m0_inv_m1 * (r1 + nttprimes[1] - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2)\
    \ - r0 - mint2(nttprimes[0]) * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0]\
    \ * v1 + m01 % mod * v2.val()) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT>\
    \ nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool skip_garner) {\n\
    \    if (a.empty() or b.empty()) return {};\n    int sz = 1, n = a.size(), m =\
    \ b.size();\n    while (sz < n + m) sz <<= 1;\n    if (sz <= 16) {\n        std::vector<MODINT>\
    \ ret(n + m - 1);\n        for (int i = 0; i < n; i++) {\n            for (int\
    \ j = 0; j < m; j++) ret[i + j] += a[i] * b[j];\n        }\n        return ret;\n\
    \    }\n    int mod = MODINT::mod();\n    if (skip_garner or\n        std::find(std::begin(nttprimes),\
    \ std::end(nttprimes), mod) != std::end(nttprimes)) {\n        a.resize(sz), b.resize(sz);\n\
    \        if (a == b) {\n            ntt(a, false);\n            b = a;\n     \
    \   } else {\n            ntt(a, false), ntt(b, false);\n        }\n        for\
    \ (int i = 0; i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n\
    \ + m - 1);\n    } else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val();\n        for (int i = 0; i < m;\
    \ i++) bi[i] = b[i].val();\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n\
    \        auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\n\
    \            a[i] = garner_ntt_(ntt0[i].val(), ntt1[i].val(), ntt2[i].val(), mod);\n\
    \    }\n    return a;\n}\n\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(const\
    \ std::vector<MODINT> &a, const std::vector<MODINT> &b) {\n    return nttconv<MODINT>(a,\
    \ b, false);\n}\n#line 7 \"number/test/primitive_root.test.cpp\"\nusing namespace\
    \ std;\n\nusing mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int P;\n    cin >> P;\n    vector<mint> A(P\
    \ - 1), B(P - 1);\n    for (auto &x : A) cin >> x;\n    for (auto &x : B) cin\
    \ >> x;\n    if (P == 2) {\n        cout << A[0] * B[0] << '\\n';\n        return\
    \ 0;\n    }\n    int b = find_smallest_primitive_root(P);\n    vector<long long>\
    \ pp(P, 1), ppinv(P);\n    for (int i = 1; i < P; ++i) pp[i] = pp[i - 1] * b %\
    \ P;\n    for (int i = 0; i < P; ++i) ppinv[pp[i]] = i;\n\n    vector<mint> AS(P),\
    \ BS(P);\n    for (int i = 0; i < P - 1; ++i) AS[ppinv[i + 1]] = A[i];\n    for\
    \ (int i = 0; i < P - 1; ++i) BS[ppinv[i + 1]] = B[i];\n    auto v = nttconv(AS,\
    \ BS);\n    vector<mint> ret(P + 1);\n    for (int i = 1; i < int(v.size()); ++i)\
    \ ret[pow_mod(b, i, P)] += v[i];\n    for (int i = 1; i < P; ++i) cout << ret[i]\
    \ << (i + 1 == P ? '\\n' : ' ');\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/931\"\n#include \"../primitive_root.hpp\"\
    \n#include \"../../convolution/ntt.hpp\"\n#include \"../../modint.hpp\"\n#include\
    \ <iostream>\n#include <vector>\nusing namespace std;\n\nusing mint = ModInt<998244353>;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int P;\n\
    \    cin >> P;\n    vector<mint> A(P - 1), B(P - 1);\n    for (auto &x : A) cin\
    \ >> x;\n    for (auto &x : B) cin >> x;\n    if (P == 2) {\n        cout << A[0]\
    \ * B[0] << '\\n';\n        return 0;\n    }\n    int b = find_smallest_primitive_root(P);\n\
    \    vector<long long> pp(P, 1), ppinv(P);\n    for (int i = 1; i < P; ++i) pp[i]\
    \ = pp[i - 1] * b % P;\n    for (int i = 0; i < P; ++i) ppinv[pp[i]] = i;\n\n\
    \    vector<mint> AS(P), BS(P);\n    for (int i = 0; i < P - 1; ++i) AS[ppinv[i\
    \ + 1]] = A[i];\n    for (int i = 0; i < P - 1; ++i) BS[ppinv[i + 1]] = B[i];\n\
    \    auto v = nttconv(AS, BS);\n    vector<mint> ret(P + 1);\n    for (int i =\
    \ 1; i < int(v.size()); ++i) ret[pow_mod(b, i, P)] += v[i];\n    for (int i =\
    \ 1; i < P; ++i) cout << ret[i] << (i + 1 == P ? '\\n' : ' ');\n}\n"
  dependsOn:
  - number/primitive_root.hpp
  - number/bare_mod_algebra.hpp
  - number/factorize.hpp
  - random/xorshift.hpp
  - convolution/ntt.hpp
  - modint.hpp
  isVerificationFile: true
  path: number/test/primitive_root.test.cpp
  requiredBy: []
  timestamp: '2023-03-10 18:40:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/primitive_root.test.cpp
layout: document
redirect_from:
- /verify/number/test/primitive_root.test.cpp
- /verify/number/test/primitive_root.test.cpp.html
title: number/test/primitive_root.test.cpp
---
