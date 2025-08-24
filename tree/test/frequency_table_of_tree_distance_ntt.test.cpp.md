---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: number/bare_mod_algebra.hpp
    title: number/bare_mod_algebra.hpp
  - icon: ':heavy_check_mark:'
    path: tree/centroid_decomposition.hpp
    title: "Centroid decomposition \uFF08\u68EE\u306E\u91CD\u5FC3\u5206\u89E3\uFF09"
  - icon: ':heavy_check_mark:'
    path: tree/frequency_table_of_tree_distance.hpp
    title: Frequency table of tree distance
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
    links:
    - https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
  bundledCode: "#line 2 \"modint.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <set>\n#include <vector>\n\ntemplate <int md> struct ModInt {\n    using\
    \ lint = long long;\n    constexpr static int mod() { return md; }\n    static\
    \ int get_primitive_root() {\n        static int primitive_root = 0;\n       \
    \ if (!primitive_root) {\n            primitive_root = [&]() {\n             \
    \   std::set<int> fac;\n                int v = md - 1;\n                for (lint\
    \ i = 2; i * i <= v; i++)\n                    while (v % i == 0) fac.insert(i),\
    \ v /= i;\n                if (v > 1) fac.insert(v);\n                for (int\
    \ g = 1; g < md; g++) {\n                    bool ok = true;\n               \
    \     for (auto i : fac)\n                        if (ModInt(g).pow((md - 1) /\
    \ i) == 1) {\n                            ok = false;\n                      \
    \      break;\n                        }\n                    if (ok) return g;\n\
    \                }\n                return -1;\n            }();\n        }\n\
    \        return primitive_root;\n    }\n    int val_;\n    int val() const noexcept\
    \ { return val_; }\n    constexpr ModInt() : val_(0) {}\n    constexpr ModInt\
    \ &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n    constexpr\
    \ ModInt(lint v) { _setval(v % md + md); }\n    constexpr explicit operator bool()\
    \ const { return val_ != 0; }\n    constexpr ModInt operator+(const ModInt &x)\
    \ const {\n        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    constexpr\
    \ ModInt operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
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
    \        } else {\n            return this->pow(md - 2);\n        }\n    }\n \
    \   constexpr ModInt fac() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val_];\n    }\n\
    \    constexpr ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    constexpr ModInt doublefac() const {\n        lint k = (this->val_ +\
    \ 1) / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n\n    constexpr ModInt nCr(int r) const {\n        if (r < 0 or this->val_\
    \ < r) return ModInt(0);\n        return this->fac() * (*this - r).facinv() *\
    \ ModInt(r).facinv();\n    }\n\n    constexpr ModInt nPr(int r) const {\n    \
    \    if (r < 0 or this->val_ < r) return ModInt(0);\n        return this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    static ModInt binom(int n, int r) {\n\
    \        static long long bruteforce_times = 0;\n\n        if (r < 0 or n < r)\
    \ return ModInt(0);\n        if (n <= bruteforce_times or n < (int)facs.size())\
    \ return ModInt(n).nCr(r);\n\n        r = std::min(r, n - r);\n\n        ModInt\
    \ ret = ModInt(r).facinv();\n        for (int i = 0; i < r; ++i) ret *= n - i;\n\
    \        bruteforce_times += r;\n\n        return ret;\n    }\n\n    // Multinomial\
    \ coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)\n    // Complexity:\
    \ O(sum(ks))\n    template <class Vec> static ModInt multinomial(const Vec &ks)\
    \ {\n        ModInt ret{1};\n        int sum = 0;\n        for (int k : ks) {\n\
    \            assert(k >= 0);\n            ret *= ModInt(k).facinv(), sum += k;\n\
    \        }\n        return ret * ModInt(sum).fac();\n    }\n\n    // Catalan number,\
    \ C_n = binom(2n, n) / (n + 1)\n    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4\
    \ = 14, ...\n    // https://oeis.org/A000108\n    // Complexity: O(n)\n    static\
    \ ModInt catalan(int n) {\n        if (n < 0) return ModInt(0);\n        return\
    \ ModInt(n * 2).fac() * ModInt(n + 1).facinv() * ModInt(n).facinv();\n    }\n\n\
    \    ModInt sqrt() const {\n        if (val_ == 0) return 0;\n        if (md ==\
    \ 2) return val_;\n        if (pow((md - 1) / 2) != 1) return 0;\n        ModInt\
    \ b = 1;\n        while (b.pow((md - 1) / 2) == 1) b += 1;\n        int e = 0,\
    \ m = md - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j\
    \ - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val_, md - x.val_));\n    }\n};\ntemplate <int\
    \ md> std::vector<ModInt<md>> ModInt<md>::facs = {1};\ntemplate <int md> std::vector<ModInt<md>>\
    \ ModInt<md>::facinvs = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::invs\
    \ = {0};\n\nusing ModInt998244353 = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n\
    // using mint = ModInt<1000000007>;\n#line 3 \"convolution/ntt.hpp\"\n\n#include\
    \ <algorithm>\n#include <array>\n#line 7 \"convolution/ntt.hpp\"\n#include <tuple>\n\
    #line 9 \"convolution/ntt.hpp\"\n\n// CUT begin\n// Integer convolution for arbitrary\
    \ mod\n// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime class.\n\
    // We skip Garner's algorithm if `skip_garner` is true or mod is in `nttprimes`.\n\
    // input: a (size: n), b (size: m)\n// return: vector (size: n + m - 1)\ntemplate\
    \ <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT>\
    \ b, bool skip_garner);\n\nconstexpr int nttprimes[3] = {998244353, 167772161,\
    \ 469762049};\n\n// Integer FFT (Fast Fourier Transform) for ModInt class\n//\
    \ (Also known as Number Theoretic Transform, NTT)\n// is_inverse: inverse transform\n\
    // ** Input size must be 2^n **\ntemplate <typename MODINT> void ntt(std::vector<MODINT>\
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
    \            }\n        }\n        int n_inv = MODINT(n).inv().val();\n      \
    \  for (auto &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
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
    \ b, false);\n}\n#line 5 \"number/bare_mod_algebra.hpp\"\n#include <utility>\n\
    #line 7 \"number/bare_mod_algebra.hpp\"\n\n// CUT begin\n// Solve ax+by=gcd(a,\
    \ b)\ntemplate <class Int> Int extgcd(Int a, Int b, Int &x, Int &y) {\n    Int\
    \ d = a;\n    if (b != 0) {\n        d = extgcd(b, a % b, y, x), y -= (a / b)\
    \ * x;\n    } else {\n        x = 1, y = 0;\n    }\n    return d;\n}\n// Calculate\
    \ a^(-1) (MOD m) s if gcd(a, m) == 1\n// Calculate x s.t. ax == gcd(a, m) MOD\
    \ m\ntemplate <class Int> Int mod_inverse(Int a, Int m) {\n    Int x, y;\n   \
    \ extgcd<Int>(a, m, x, y);\n    x %= m;\n    return x + (x < 0) * m;\n}\n\n//\
    \ Require: 1 <= b\n// return: (g, x) s.t. g = gcd(a, b), xa = g MOD b, 0 <= x\
    \ < b/g\ntemplate <class Int> /* constexpr */ std::pair<Int, Int> inv_gcd(Int\
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
    \ < 0 ? r + m : r), m);\n}\n\ntemplate <class Int = int, class Long = long long>\
    \ Int pow_mod(Int x, long long n, Int md) {\n    static_assert(sizeof(Int) * 2\
    \ <= sizeof(Long), \"Watch out for overflow\");\n    if (md == 1) return 0;\n\
    \    Int ans = 1;\n    while (n > 0) {\n        if (n & 1) ans = (Long)ans * x\
    \ % md;\n        x = (Long)x * x % md;\n        n >>= 1;\n    }\n    return ans;\n\
    }\n#line 5 \"tree/centroid_decomposition.hpp\"\n\n// Centroid Decomposition\n\
    // Verification: https://yukicoder.me/problems/no/2892\n// find_current_centroids(int\
    \ r, int conn_size): Enumerate centroid(s) of the subtree which `r` belongs to.\n\
    struct CentroidDecomposition {\n    int V;\n    std::vector<std::vector<int>>\
    \ to;\n\nprivate:\n    std::vector<int> is_alive;\n    std::vector<int> subtree_size;\n\
    \n    template <class F> void decompose(int r, int conn_size, F callback) {\n\n\
    \        const int c = find_current_centroids(r, conn_size).first;\n        is_alive.at(c)\
    \ = 0;\n\n        callback(c);\n\n        for (int nxt : to.at(c)) {\n       \
    \     if (!is_alive.at(nxt)) continue;\n            int next_size = subtree_size.at(nxt);\n\
    \            if (subtree_size.at(nxt) > subtree_size.at(c))\n                next_size\
    \ = subtree_size.at(r) - subtree_size.at(c);\n            decompose(nxt, next_size,\
    \ callback);\n        }\n    }\n\npublic:\n    CentroidDecomposition(int v = 0)\
    \ : V(v), to(v), is_alive(v, 1), subtree_size(v) {}\n\n    CentroidDecomposition(int\
    \ v, const std::vector<std::pair<int, int>> &tree_edges)\n        : CentroidDecomposition(v)\
    \ {\n        for (auto e : tree_edges) add_edge(e.first, e.second);\n    }\n\n\
    \    void add_edge(int v1, int v2) {\n        assert(0 <= v1 and v1 < V and 0\
    \ <= v2 and v2 < V);\n        assert(v1 != v2);\n        to.at(v1).push_back(v2),\
    \ to.at(v2).emplace_back(v1);\n    }\n\n    std::pair<int, int> find_current_centroids(int\
    \ r, int conn_size) {\n        assert(is_alive.at(r));\n\n        const int thres\
    \ = conn_size / 2;\n\n        int c1 = -1, c2 = -1;\n\n        auto rec_search\
    \ = [&](auto &&self, int now, int prv) -> void {\n            bool is_centroid\
    \ = true;\n            subtree_size.at(now) = 1;\n            for (int nxt : to.at(now))\
    \ {\n                if (nxt == prv or !is_alive.at(nxt)) continue;\n        \
    \        self(self, nxt, now);\n                subtree_size.at(now) += subtree_size.at(nxt);\n\
    \                if (subtree_size.at(nxt) > thres) is_centroid = false;\n    \
    \        }\n            if (conn_size - subtree_size.at(now) > thres) is_centroid\
    \ = false;\n\n            if (is_centroid) (c1 < 0 ? c1 : c2) = now;\n       \
    \ };\n        rec_search(rec_search, r, -1);\n\n        return {c1, c2};\n   \
    \ }\n\n    template <class F> void run(int r, F callback) {\n        int conn_size\
    \ = 0;\n\n        auto rec = [&](auto &&self, int now, int prv) -> void {\n  \
    \          ++conn_size;\n            is_alive.at(now) = 1;\n\n            for\
    \ (int nxt : to.at(now)) {\n                if (nxt == prv) continue;\n      \
    \          self(self, nxt, now);\n            }\n        };\n        rec(rec,\
    \ r, -1);\n\n        decompose(r, conn_size, callback);\n    }\n\n    std::vector<int>\
    \ centroid_decomposition(int r) {\n        std::vector<int> res;\n        run(r,\
    \ [&](int v) { res.push_back(v); });\n        return res;\n    }\n};\n#line 5\
    \ \"tree/frequency_table_of_tree_distance.hpp\"\n\nstruct frequency_table_of_tree_distance\
    \ {\n    std::vector<std::vector<int>> tos;\n    std::vector<int> cd;\n    std::vector<std::pair<int,\
    \ int>> tmp;\n    std::vector<int> alive;\n\n    void _dfs(int now, int prv, int\
    \ depth) {\n        // if (int(tmp.size()) <= depth) tmp.resize(depth + 1, 0);\n\
    \        // tmp[depth]++;\n        tmp.emplace_back(now, depth);\n        for\
    \ (auto nxt : tos[now]) {\n            if (alive[nxt] and nxt != prv) _dfs(nxt,\
    \ now, depth + 1);\n        }\n    }\n    std::vector<std::pair<int, int>> cnt_dfs(int\
    \ root) {\n        return tmp.clear(), _dfs(root, -1, 0), tmp;\n    }\n    frequency_table_of_tree_distance(const\
    \ std::vector<std::vector<int>> &to) {\n        tos = to;\n\n        CentroidDecomposition\
    \ c(to.size());\n        for (int i = 0; i < int(to.size()); i++) {\n        \
    \    for (int j : to[i]) {\n                if (i < j) c.add_edge(i, j);\n   \
    \         }\n        }\n\n        cd = c.centroid_decomposition(0);\n    }\n \
    \   template <class S, std::vector<S> (*conv)(const std::vector<S> &, const std::vector<S>\
    \ &)>\n    std::vector<S> solve(const std::vector<S> &weight) {\n        alive.assign(tos.size(),\
    \ 1);\n        std::vector<S> ret(tos.size());\n        std::vector<S> v;\n  \
    \      for (auto root : cd) {\n            std::vector<std::vector<S>> vv;\n \
    \           alive[root] = 0;\n            for (auto nxt : tos[root]) {\n     \
    \           if (!alive[nxt]) continue;\n                v.clear();\n         \
    \       for (auto p : cnt_dfs(nxt)) {\n                    while (int(v.size())\
    \ <= p.second) v.push_back(S(0));\n                    v[p.second] += weight[p.first];\n\
    \                }\n                for (int i = 0; i < int(v.size()); i++) ret[i\
    \ + 1] += v[i] * weight[root];\n                vv.emplace_back(v);\n        \
    \    }\n            std::sort(vv.begin(), vv.end(), [&](const std::vector<S> &l,\
    \ const std::vector<S> &r) {\n                return l.size() < r.size();\n  \
    \          });\n            for (size_t j = 1; j < vv.size(); j++) {\n       \
    \         const std::vector<S> c = conv(vv[j - 1], vv[j]);\n                for\
    \ (size_t i = 0; i < c.size(); i++) ret[i + 2] += c[i];\n                for (size_t\
    \ i = 0; i < vv[j - 1].size(); i++) vv[j][i] += vv[j - 1][i];\n            }\n\
    \            tos[root].clear();\n        }\n        return ret;\n    }\n};\n#line\
    \ 7 \"tree/test/frequency_table_of_tree_distance_ntt.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\nusing\
    \ namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n    vector<vector<int>> to(N);\n    for (int i =\
    \ 0; i < N - 1; i++) {\n        int s, t;\n        cin >> s >> t;\n        to[s].emplace_back(t),\
    \ to[t].emplace_back(s);\n    }\n\n    frequency_table_of_tree_distance solver(to);\n\
    \n    using mint1 = ModInt<998244353>;\n    using mint2 = ModInt<167772161>;\n\
    \    const vector<mint1> ret1 =\n        frequency_table_of_tree_distance(to).solve<mint1,\
    \ nttconv<mint1>>(std::vector<mint1>(N, 1));\n    const vector<mint2> ret2 =\n\
    \        frequency_table_of_tree_distance(to).solve<mint2, nttconv<mint2>>(std::vector<mint2>(N,\
    \ 1));\n    for (int i = 1; i < N; i++) {\n        auto v = crt<long long>({ret1[i].val(),\
    \ ret2[i].val()}, {mint1::mod(), mint2::mod()});\n        cout << v.first << '\
    \ ';\n    }\n    cout << '\\n';\n}\n"
  code: "#include \"../../convolution/ntt.hpp\"\n#include \"../../modint.hpp\"\n#include\
    \ \"../../number/bare_mod_algebra.hpp\"\n#include \"../frequency_table_of_tree_distance.hpp\"\
    \n#include <iostream>\n#include <vector>\n#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n    vector<vector<int>> to(N);\n    for (int i =\
    \ 0; i < N - 1; i++) {\n        int s, t;\n        cin >> s >> t;\n        to[s].emplace_back(t),\
    \ to[t].emplace_back(s);\n    }\n\n    frequency_table_of_tree_distance solver(to);\n\
    \n    using mint1 = ModInt<998244353>;\n    using mint2 = ModInt<167772161>;\n\
    \    const vector<mint1> ret1 =\n        frequency_table_of_tree_distance(to).solve<mint1,\
    \ nttconv<mint1>>(std::vector<mint1>(N, 1));\n    const vector<mint2> ret2 =\n\
    \        frequency_table_of_tree_distance(to).solve<mint2, nttconv<mint2>>(std::vector<mint2>(N,\
    \ 1));\n    for (int i = 1; i < N; i++) {\n        auto v = crt<long long>({ret1[i].val(),\
    \ ret2[i].val()}, {mint1::mod(), mint2::mod()});\n        cout << v.first << '\
    \ ';\n    }\n    cout << '\\n';\n}\n"
  dependsOn:
  - convolution/ntt.hpp
  - modint.hpp
  - number/bare_mod_algebra.hpp
  - tree/frequency_table_of_tree_distance.hpp
  - tree/centroid_decomposition.hpp
  isVerificationFile: true
  path: tree/test/frequency_table_of_tree_distance_ntt.test.cpp
  requiredBy: []
  timestamp: '2024-09-25 00:42:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/frequency_table_of_tree_distance_ntt.test.cpp
layout: document
redirect_from:
- /verify/tree/test/frequency_table_of_tree_distance_ntt.test.cpp
- /verify/tree/test/frequency_table_of_tree_distance_ntt.test.cpp.html
title: tree/test/frequency_table_of_tree_distance_ntt.test.cpp
---
