---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/formal_power_series.hpp
    title: formal_power_series/formal_power_series.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/multipoint_evaluation.hpp
    title: formal_power_series/multipoint_evaluation.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
    title: Sum of exponential times polynomial limit ($\sum_{i=0}^\infty r^i f(i)$)
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit
    links:
    - https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit
  bundledCode: "#line 1 \"formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\"\
    \n#line 2 \"formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\"\
    \n#include <cassert>\n#include <vector>\n\n// CUT begin\n// $d$ \u6B21\u4EE5\u4E0B\
    \u306E\u591A\u9805\u5F0F $f(x)$ \u3068\u5B9A\u6570 $r$ \u306B\u3064\u3044\u3066\
    \uFF0C\n// $\\sum_{i=0}^\\infty r^i f(i)$ \u306E\u5024\u3092 $[f(0), ..., f(d\
    \ - 1), f(d)]$ \u306E\u5024\u304B\u3089 $O(d)$ \u3067\u8A08\u7B97\uFF0E\n// Requirement:\
    \ r != 1\n// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\n\
    // Document: https://hitonanode.github.io/cplib-cpp/formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\n\
    template <typename MODINT>\nMODINT sum_of_exponential_times_polynomial_limit(MODINT\
    \ r, std::vector<MODINT> init) {\n    assert(r != 1);\n    if (init.empty()) return\
    \ 0;\n    if (init.size() == 1) return init[0] / (1 - r);\n    auto &bs = init;\n\
    \    const int d = int(bs.size()) - 1;\n    MODINT rp = 1;\n    for (int i = 1;\
    \ i <= d; i++) rp *= r, bs[i] = bs[i] * rp + bs[i - 1];\n    MODINT ret = 0;\n\
    \    rp = 1;\n    for (int i = 0; i <= d; i++) {\n        ret += bs[d - i] * MODINT(d\
    \ + 1).nCr(i) * rp;\n        rp *= -r;\n    }\n    return ret / MODINT(1 - r).pow(d\
    \ + 1);\n};\n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#line\
    \ 5 \"modint.hpp\"\n\n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus\
    \ >= 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using\
    \ lint = long long;\n    MDCONST static int mod() { return md; }\n    static int\
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
    \ primitive_root;\n    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n   \
    \ MDCONST ModInt &_setval(lint v) { return val = (v >= md ? v - md : v), *this;\
    \ }\n    MDCONST ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit\
    \ operator bool() const { return val != 0; }\n    MDCONST ModInt operator+(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val + x.val); }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val\
    \ - x.val + md);\n    }\n    MDCONST ModInt operator*(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val * x.val % md);\n    }\n    MDCONST\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val\
    \ * x.inv() % md);\n    }\n    MDCONST ModInt operator-() const { return ModInt()._setval(md\
    \ - val); }\n    MDCONST ModInt &operator+=(const ModInt &x) { return *this =\
    \ *this + x; }\n    MDCONST ModInt &operator-=(const ModInt &x) { return *this\
    \ = *this - x; }\n    MDCONST ModInt &operator*=(const ModInt &x) { return *this\
    \ = *this * x; }\n    MDCONST ModInt &operator/=(const ModInt &x) { return *this\
    \ = *this / x; }\n    friend MDCONST ModInt operator+(lint a, const ModInt &x)\
    \ {\n        return ModInt()._setval(a % md + x.val);\n    }\n    friend MDCONST\
    \ ModInt operator-(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md - x.val + md);\n    }\n    friend MDCONST ModInt operator*(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.val % md);\n    }\n\
    \    friend MDCONST ModInt operator/(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md * x.inv() % md);\n    }\n    MDCONST bool operator==(const\
    \ ModInt &x) const { return val == x.val; }\n    MDCONST bool operator!=(const\
    \ ModInt &x) const { return val != x.val; }\n    MDCONST bool operator<(const\
    \ ModInt &x) const {\n        return val < x.val;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val;\n    }\n    MDCONST ModInt pow(lint n) const {\n     \
    \   ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n & 1)\
    \ ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return ans;\n\
    \    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n    MDCONST\
    \ lint inv() const {\n        if (this->val < std::min(md >> 1, 1 << 21)) {\n\
    \            while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val].val;\n        } else {\n         \
    \   return this->pow(md - 2).val;\n        }\n    }\n    MDCONST ModInt fac()\
    \ const {\n        while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facs[this->val];\n    }\n    MDCONST ModInt facinv() const\
    \ {\n        while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facinvs[this->val];\n    }\n    MDCONST ModInt doublefac()\
    \ const {\n        lint k = (this->val + 1) / 2;\n        return (this->val &\
    \ 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n          \
    \                     : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST\
    \ ModInt nCr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST ModInt\
    \ nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0 : this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val\
    \ == 0) return 0;\n        if (md == 2) return val;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
    \ md - x.val));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 3 \"number/sieve.hpp\"\
    \n#include <map>\n#line 5 \"number/sieve.hpp\"\n\n// CUT begin\n// Linear sieve\
    \ algorithm for fast prime factorization\n// Complexity: O(N) time, O(N) space:\n\
    // - MAXN = 10^7:  ~44 MB,  80~100 ms (Codeforces / AtCoder GCC, C++17)\n// -\
    \ MAXN = 10^8: ~435 MB, 810~980 ms (Codeforces / AtCoder GCC, C++17)\n// Reference:\n\
    // [1] D. Gries, J. Misra, \"A Linear Sieve Algorithm for Finding Prime Numbers,\"\
    \n//     Communications of the ACM, 21(12), 999-1003, 1978.\n// - https://cp-algorithms.com/algebra/prime-sieve-linear.html\n\
    // - https://37zigen.com/linear-sieve/\nstruct Sieve {\n    std::vector<int> min_factor;\n\
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
    #line 3 \"convolution/ntt.hpp\"\n\n#include <algorithm>\n#include <array>\n#line\
    \ 7 \"convolution/ntt.hpp\"\n#include <tuple>\n#line 9 \"convolution/ntt.hpp\"\
    \n\n// CUT begin\n// Integer convolution for arbitrary mod\n// with NTT (and Garner's\
    \ algorithm) for ModInt / ModIntRuntime class.\n// We skip Garner's algorithm\
    \ if `skip_garner` is true or mod is in `nttprimes`.\n// input: a (size: n), b\
    \ (size: m)\n// return: vector (size: n + m - 1)\ntemplate <typename MODINT>\n\
    std::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool\
    \ skip_garner);\n\nconstexpr int nttprimes[3] = {998244353, 167772161, 469762049};\n\
    \n// Integer FFT (Fast Fourier Transform) for ModInt class\n// (Also known as\
    \ Number Theoretic Transform, NTT)\n// is_inverse: inverse transform\n// ** Input\
    \ size must be 2^n **\ntemplate <typename MODINT> void ntt(std::vector<MODINT>\
    \ &a, bool is_inverse = false) {\n    int n = a.size();\n    if (n == 1) return;\n\
    \    static const int mod = MODINT::mod();\n    static const MODINT root = MODINT::get_primitive_root();\n\
    \    assert(__builtin_popcount(n) == 1 and (mod - 1) % n == 0);\n\n    static\
    \ std::vector<MODINT> w{1}, iw{1};\n    for (int m = w.size(); m < n / 2; m *=\
    \ 2) {\n        MODINT dw = root.pow((mod - 1) / (4 * m)), dwinv = 1 / dw;\n \
    \       w.resize(m * 2), iw.resize(m * 2);\n        for (int i = 0; i < m; i++)\
    \ w[m + i] = w[i] * dw, iw[m + i] = iw[i] * dwinv;\n    }\n\n    if (!is_inverse)\
    \ {\n        for (int m = n; m >>= 1;) {\n            for (int s = 0, k = 0; s\
    \ < n; s += 2 * m, k++) {\n                for (int i = s; i < s + m; i++) {\n\
    \                    MODINT x = a[i], y = a[i + m] * w[k];\n                 \
    \   a[i] = x + y, a[i + m] = x - y;\n                }\n            }\n      \
    \  }\n    } else {\n        for (int m = 1; m < n; m *= 2) {\n            for\
    \ (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n                for (int i = s;\
    \ i < s + m; i++) {\n                    MODINT x = a[i], y = a[i + m];\n    \
    \                a[i] = x + y, a[i + m] = (x - y) * iw[k];\n                }\n\
    \            }\n        }\n        int n_inv = MODINT(n).inv();\n        for (auto\
    \ &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
    \ nttconv_(const std::vector<int> &a, const std::vector<int> &b) {\n    int sz\
    \ = a.size();\n    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n\
    \    std::vector<ModInt<MOD>> ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++)\
    \ ap[i] = a[i], bp[i] = b[i];\n    ntt(ap, false);\n    if (a == b)\n        bp\
    \ = ap;\n    else\n        ntt(bp, false);\n    for (int i = 0; i < sz; i++) ap[i]\
    \ *= bp[i];\n    ntt(ap, true);\n    return ap;\n}\nlong long garner_ntt_(int\
    \ r0, int r1, int r2, int mod) {\n    using mint2 = ModInt<nttprimes[2]>;\n  \
    \  static const long long m01 = 1LL * nttprimes[0] * nttprimes[1];\n    static\
    \ const long long m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv();\n    static\
    \ const long long m01_inv_m2 = mint2(m01).inv();\n\n    int v1 = (m0_inv_m1 *\
    \ (r1 + nttprimes[1] - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2) - r0 - mint2(nttprimes[0])\
    \ * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0] * v1 + m01 % mod *\
    \ v2.val) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT>\
    \ a, std::vector<MODINT> b, bool skip_garner) {\n    if (a.empty() or b.empty())\
    \ return {};\n    int sz = 1, n = a.size(), m = b.size();\n    while (sz < n +\
    \ m) sz <<= 1;\n    if (sz <= 16) {\n        std::vector<MODINT> ret(n + m - 1);\n\
    \        for (int i = 0; i < n; i++) {\n            for (int j = 0; j < m; j++)\
    \ ret[i + j] += a[i] * b[j];\n        }\n        return ret;\n    }\n    int mod\
    \ = MODINT::mod();\n    if (skip_garner or\n        std::find(std::begin(nttprimes),\
    \ std::end(nttprimes), mod) != std::end(nttprimes)) {\n        a.resize(sz), b.resize(sz);\n\
    \        if (a == b) {\n            ntt(a, false);\n            b = a;\n     \
    \   } else {\n            ntt(a, false), ntt(b, false);\n        }\n        for\
    \ (int i = 0; i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n\
    \ + m - 1);\n    } else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val;\n        for (int i = 0; i < m; i++)\
    \ bi[i] = b[i].val;\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n   \
    \     auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\n\
    \            a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);\n\
    \    }\n    return a;\n}\n\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(const\
    \ std::vector<MODINT> &a, const std::vector<MODINT> &b) {\n    return nttconv<MODINT>(a,\
    \ b, false);\n}\n#line 6 \"formal_power_series/formal_power_series.hpp\"\n\n//\
    \ Formal Power Series (\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570) based on ModInt<mod>\
    \ / ModIntRuntime\n// Reference: https://ei1333.github.io/luzhiled/snippets/math/formal-power-series.html\n\
    template <typename T> struct FormalPowerSeries : std::vector<T> {\n    using std::vector<T>::vector;\n\
    \    using P = FormalPowerSeries;\n\n    void shrink() {\n        while (this->size()\
    \ and this->back() == T(0)) this->pop_back();\n    }\n\n    P operator+(const\
    \ P &r) const { return P(*this) += r; }\n    P operator+(const T &v) const { return\
    \ P(*this) += v; }\n    P operator-(const P &r) const { return P(*this) -= r;\
    \ }\n    P operator-(const T &v) const { return P(*this) -= v; }\n    P operator*(const\
    \ P &r) const { return P(*this) *= r; }\n    P operator*(const T &v) const { return\
    \ P(*this) *= v; }\n    P operator/(const P &r) const { return P(*this) /= r;\
    \ }\n    P operator/(const T &v) const { return P(*this) /= v; }\n    P operator%(const\
    \ P &r) const { return P(*this) %= r; }\n\n    P &operator+=(const P &r) {\n \
    \       if (r.size() > this->size()) this->resize(r.size());\n        for (int\
    \ i = 0; i < (int)r.size(); i++) (*this)[i] += r[i];\n        shrink();\n    \
    \    return *this;\n    }\n    P &operator+=(const T &v) {\n        if (this->empty())\
    \ this->resize(1);\n        (*this)[0] += v;\n        shrink();\n        return\
    \ *this;\n    }\n    P &operator-=(const P &r) {\n        if (r.size() > this->size())\
    \ this->resize(r.size());\n        for (int i = 0; i < (int)r.size(); i++) (*this)[i]\
    \ -= r[i];\n        shrink();\n        return *this;\n    }\n    P &operator-=(const\
    \ T &v) {\n        if (this->empty()) this->resize(1);\n        (*this)[0] -=\
    \ v;\n        shrink();\n        return *this;\n    }\n    P &operator*=(const\
    \ T &v) {\n        for (auto &x : (*this)) x *= v;\n        shrink();\n      \
    \  return *this;\n    }\n    P &operator*=(const P &r) {\n        if (this->empty()\
    \ || r.empty())\n            this->clear();\n        else {\n            auto\
    \ ret = nttconv(*this, r);\n            *this = P(ret.begin(), ret.end());\n \
    \       }\n        return *this;\n    }\n    P &operator%=(const P &r) {\n   \
    \     *this -= *this / r * r;\n        shrink();\n        return *this;\n    }\n\
    \    P operator-() const {\n        P ret = *this;\n        for (auto &v : ret)\
    \ v = -v;\n        return ret;\n    }\n    P &operator/=(const T &v) {\n     \
    \   assert(v != T(0));\n        for (auto &x : (*this)) x /= v;\n        return\
    \ *this;\n    }\n    P &operator/=(const P &r) {\n        if (this->size() < r.size())\
    \ {\n            this->clear();\n            return *this;\n        }\n      \
    \  int n = (int)this->size() - r.size() + 1;\n        return *this = (reversed().pre(n)\
    \ * r.reversed().inv(n)).pre(n).reversed(n);\n    }\n    P pre(int sz) const {\n\
    \        P ret(this->begin(), this->begin() + std::min((int)this->size(), sz));\n\
    \        ret.shrink();\n        return ret;\n    }\n    P operator>>(int sz) const\
    \ {\n        if ((int)this->size() <= sz) return {};\n        return P(this->begin()\
    \ + sz, this->end());\n    }\n    P operator<<(int sz) const {\n        if (this->empty())\
    \ return {};\n        P ret(*this);\n        ret.insert(ret.begin(), sz, T(0));\n\
    \        return ret;\n    }\n\n    P reversed(int deg = -1) const {\n        assert(deg\
    \ >= -1);\n        P ret(*this);\n        if (deg != -1) ret.resize(deg, T(0));\n\
    \        reverse(ret.begin(), ret.end());\n        ret.shrink();\n        return\
    \ ret;\n    }\n\n    P differential() const { // formal derivative (differential)\
    \ of f.p.s.\n        const int n = (int)this->size();\n        P ret(std::max(0,\
    \ n - 1));\n        for (int i = 1; i < n; i++) ret[i - 1] = (*this)[i] * T(i);\n\
    \        return ret;\n    }\n\n    P integral() const {\n        const int n =\
    \ (int)this->size();\n        P ret(n + 1);\n        ret[0] = T(0);\n        for\
    \ (int i = 0; i < n; i++) ret[i + 1] = (*this)[i] / T(i + 1);\n        return\
    \ ret;\n    }\n\n    P inv(int deg) const {\n        assert(deg >= -1);\n    \
    \    assert(this->size() and ((*this)[0]) != T(0)); // Requirement: F(0) != 0\n\
    \        const int n = this->size();\n        if (deg == -1) deg = n;\n      \
    \  P ret({T(1) / (*this)[0]});\n        for (int i = 1; i < deg; i <<= 1) {\n\
    \            ret = (ret + ret - ret * ret * pre(i << 1)).pre(i << 1);\n      \
    \  }\n        ret = ret.pre(deg);\n        ret.shrink();\n        return ret;\n\
    \    }\n\n    P log(int deg = -1) const {\n        assert(deg >= -1);\n      \
    \  assert(this->size() and ((*this)[0]) == T(1)); // Requirement: F(0) = 1\n \
    \       const int n = (int)this->size();\n        if (deg == 0) return {};\n \
    \       if (deg == -1) deg = n;\n        return (this->differential() * this->inv(deg)).pre(deg\
    \ - 1).integral();\n    }\n\n    P sqrt(int deg = -1) const {\n        assert(deg\
    \ >= -1);\n        const int n = (int)this->size();\n        if (deg == -1) deg\
    \ = n;\n        if (this->empty()) return {};\n        if ((*this)[0] == T(0))\
    \ {\n            for (int i = 1; i < n; i++)\n                if ((*this)[i] !=\
    \ T(0)) {\n                    if ((i & 1) or deg - i / 2 <= 0) return {};\n \
    \                   return (*this >> i).sqrt(deg - i / 2) << (i / 2);\n      \
    \          }\n            return {};\n        }\n        T sqrtf0 = (*this)[0].sqrt();\n\
    \        if (sqrtf0 == T(0)) return {};\n\n        P y = (*this) / (*this)[0],\
    \ ret({T(1)});\n        T inv2 = T(1) / T(2);\n        for (int i = 1; i < deg;\
    \ i <<= 1) ret = (ret + y.pre(i << 1) * ret.inv(i << 1)) * inv2;\n        return\
    \ ret.pre(deg) * sqrtf0;\n    }\n\n    P exp(int deg = -1) const {\n        assert(deg\
    \ >= -1);\n        assert(this->empty() or ((*this)[0]) == T(0)); // Requirement:\
    \ F(0) = 0\n        const int n = (int)this->size();\n        if (deg == -1) deg\
    \ = n;\n        P ret({T(1)});\n        for (int i = 1; i < deg; i <<= 1) {\n\
    \            ret = (ret * (pre(i << 1) + T(1) - ret.log(i << 1))).pre(i << 1);\n\
    \        }\n        return ret.pre(deg);\n    }\n\n    P pow(long long k, int\
    \ deg = -1) const {\n        assert(deg >= -1);\n        const int n = (int)this->size();\n\
    \        if (deg == -1) deg = n;\n        for (int i = 0; i < n; i++) {\n    \
    \        if ((*this)[i] != T(0)) {\n                T rev = T(1) / (*this)[i];\n\
    \                P C = (*this) * rev, D(n - i);\n                for (int j =\
    \ i; j < n; j++) D[j - i] = C.coeff(j);\n                D = (D.log(deg) * T(k)).exp(deg)\
    \ * (*this)[i].pow(k);\n                if (k * (i > 0) > deg or k * i > deg)\
    \ return {};\n                P E(deg);\n                long long S = i * k;\n\
    \                for (int j = 0; j + S < deg and j < (int)D.size(); j++) E[j +\
    \ S] = D[j];\n                E.shrink();\n                return E;\n       \
    \     }\n        }\n        return *this;\n    }\n\n    // Calculate f(X + c)\
    \ from f(X), O(NlogN)\n    P shift(T c) const {\n        const int n = (int)this->size();\n\
    \        P ret = *this;\n        for (int i = 0; i < n; i++) ret[i] *= T(i).fac();\n\
    \        std::reverse(ret.begin(), ret.end());\n        P exp_cx(n, 1);\n    \
    \    for (int i = 1; i < n; i++) exp_cx[i] = exp_cx[i - 1] * c / i;\n        ret\
    \ = (ret * exp_cx), ret.resize(n);\n        std::reverse(ret.begin(), ret.end());\n\
    \        for (int i = 0; i < n; i++) ret[i] /= T(i).fac();\n        return ret;\n\
    \    }\n\n    T coeff(int i) const {\n        if ((int)this->size() <= i or i\
    \ < 0) return T(0);\n        return (*this)[i];\n    }\n\n    T eval(T x) const\
    \ {\n        T ret = 0, w = 1;\n        for (auto &v : *this) ret += w * v, w\
    \ *= x;\n        return ret;\n    }\n};\n#line 5 \"formal_power_series/multipoint_evaluation.hpp\"\
    \n\n// CUT begin\n// multipoint polynomial evaluation\n// input: xs = [x_0, ...,\
    \ x_{N - 1}]: points to evaluate\n//        f = \\sum_i^M f_i x^i\n// Complexity:\
    \ O(N (lgN)^2) building, O(N (lgN)^2 + M lg M) evaluation\ntemplate <typename\
    \ Tfield> struct MultipointEvaluation {\n    int nx;\n    using polynomial = FormalPowerSeries<Tfield>;\n\
    \    std::vector<polynomial> segtree;\n    MultipointEvaluation(const std::vector<Tfield>\
    \ &xs) : nx(xs.size()) {\n        segtree.resize(nx * 2 - 1);\n        for (int\
    \ i = 0; i < nx; i++) { segtree[nx - 1 + i] = {-xs[i], 1}; }\n        for (int\
    \ i = nx - 2; i >= 0; i--) { segtree[i] = segtree[2 * i + 1] * segtree[2 * i +\
    \ 2]; }\n    }\n    std::vector<Tfield> ret;\n    void _eval_rec(polynomial f,\
    \ int now) {\n        f %= segtree[now];\n        if (now - (nx - 1) >= 0) {\n\
    \            ret[now - (nx - 1)] = f.coeff(0);\n            return;\n        }\n\
    \        _eval_rec(f, 2 * now + 1);\n        _eval_rec(f, 2 * now + 2);\n    }\n\
    \    std::vector<Tfield> evaluate_polynomial(const polynomial &f) {\n        ret.resize(nx);\n\
    \        _eval_rec(f, 0);\n        return ret;\n    }\n    std::vector<Tfield>\
    \ evaluate_polynomial(const std::vector<Tfield> &f) {\n        return evaluate_polynomial(polynomial(f.begin(),\
    \ f.end()));\n    }\n\n    std::vector<Tfield> _interpolate_coeffs;\n    polynomial\
    \ _rec_interpolation(int now, const std::vector<Tfield> &ys) const {\n       \
    \ int i = now - (nx - 1);\n        if (i >= 0) return {ys[i]};\n        auto retl\
    \ = _rec_interpolation(2 * now + 1, ys);\n        auto retr = _rec_interpolation(2\
    \ * now + 2, ys);\n        return retl * segtree[2 * now + 2] + retr * segtree[2\
    \ * now + 1];\n    }\n    std::vector<Tfield> polynomial_interpolation(std::vector<Tfield>\
    \ ys) {\n        assert(nx == int(ys.size()));\n        if (_interpolate_coeffs.empty())\
    \ {\n            _interpolate_coeffs = evaluate_polynomial(segtree[0].differential());\n\
    \            for (auto &x : _interpolate_coeffs) x = x.inv();\n        }\n   \
    \     for (int i = 0; i < nx; i++) ys[i] *= _interpolate_coeffs[i];\n        return\
    \ _rec_interpolation(0, ys);\n    }\n};\n#line 8 \"formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp\"\
    \nusing namespace std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    int\
    \ r, d;\n    cin >> r >> d;\n    mint::_precalculation(d + 10);\n    auto initial_terms\
    \ = Sieve(d).enumerate_kth_pows<mint>(d, d);\n    if (d > 0 and d <= 100000) {\n\
    \        vector<mint> xs(d + 1);\n        for (int i = 0; i <= d; i++) xs[i] =\
    \ i;\n        vector<mint> f(d + 1);\n        f[d] = 1;\n        assert(MultipointEvaluation<mint>(xs).evaluate_polynomial(f)\
    \ == initial_terms);\n    }\n    cout << sum_of_exponential_times_polynomial_limit<mint>(r,\
    \ initial_terms) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\"\
    \n#include \"../sum_of_exponential_times_polynomial_limit.hpp\"\n#include \"../../modint.hpp\"\
    \n#include \"../../number/sieve.hpp\"\n#include \"../multipoint_evaluation.hpp\"\
    \n#include <cassert>\n#include <iostream>\nusing namespace std;\nusing mint =\
    \ ModInt<998244353>;\n\nint main() {\n    int r, d;\n    cin >> r >> d;\n    mint::_precalculation(d\
    \ + 10);\n    auto initial_terms = Sieve(d).enumerate_kth_pows<mint>(d, d);\n\
    \    if (d > 0 and d <= 100000) {\n        vector<mint> xs(d + 1);\n        for\
    \ (int i = 0; i <= d; i++) xs[i] = i;\n        vector<mint> f(d + 1);\n      \
    \  f[d] = 1;\n        assert(MultipointEvaluation<mint>(xs).evaluate_polynomial(f)\
    \ == initial_terms);\n    }\n    cout << sum_of_exponential_times_polynomial_limit<mint>(r,\
    \ initial_terms) << '\\n';\n}\n"
  dependsOn:
  - formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
  - modint.hpp
  - number/sieve.hpp
  - formal_power_series/multipoint_evaluation.hpp
  - formal_power_series/formal_power_series.hpp
  isVerificationFile: true
  path: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
  requiredBy: []
  timestamp: '2022-05-01 12:00:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
layout: document
redirect_from:
- /verify/formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
- /verify/formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp.html
title: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
---
