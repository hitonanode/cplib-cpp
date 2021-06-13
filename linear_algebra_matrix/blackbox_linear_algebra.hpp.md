---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/linear_recurrence.hpp
    title: "\u7DDA\u5F62\u6F38\u5316\u5F0F\u306E\u767A\u898B\u30FB\u7B2C $N$ \u9805\
      \u63A8\u5B9A"
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus\
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
    \ ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + md); }\n    MDCONST ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % md); }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % md); }\n  \
    \  MDCONST ModInt operator-() const { return ModInt()._setval(md - val); }\n \
    \   MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % md + x.val); }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x)\
    \ { return ModInt()._setval(a % md - x.val + md); }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) { return ModInt()._setval(a % md * x.val\
    \ % md); }\n    friend MDCONST ModInt operator/(lint a, const ModInt &x) {\n \
    \       return ModInt()._setval(a % md * x.inv() % md);\n    }\n    MDCONST bool\
    \ operator==(const ModInt &x) const { return val == x.val; }\n    MDCONST bool\
    \ operator!=(const ModInt &x) const { return val != x.val; }\n    MDCONST bool\
    \ operator<(const ModInt &x) const { return val < x.val; } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { return\
    \ os << x.val; }\n    MDCONST ModInt pow(lint n) const {\n        ModInt ans =\
    \ 1, tmp = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n \
    \           tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n  \
    \  static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static void _precalculation(int\
    \ N) {\n        int l0 = facs.size();\n        if (N > md) N = md;\n        if\
    \ (N <= l0) return;\n        facs.resize(N), facinvs.resize(N), invs.resize(N);\n\
    \        for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i;\n        facinvs[N\
    \ - 1] = facs.back().pow(md - 2);\n        for (int i = N - 2; i >= l0; i--) facinvs[i]\
    \ = facinvs[i + 1] * (i + 1);\n        for (int i = N - 1; i >= l0; i--) invs[i]\
    \ = facinvs[i] * facs[i - 1];\n    }\n    MDCONST lint inv() const {\n       \
    \ if (this->val < std::min(md >> 1, 1 << 21)) {\n            while (this->val\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val].val;\n\
    \        } else {\n            return this->pow(md - 2).val;\n        }\n    }\n\
    \    MDCONST ModInt fac() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val];\n    }\n\
    \    MDCONST ModInt facinv() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val];\n    }\n\
    \    MDCONST ModInt doublefac() const {\n        lint k = (this->val + 1) / 2;\n\
    \        return (this->val & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n\
    \                               : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n\
    \    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val <\
    \ r.val) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST\
    \ ModInt nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n\
    \        if (val == 0) return 0;\n        if (md == 2) return val;\n        if\
    \ (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md\
    \ - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m %\
    \ 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x\
    \ * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while (y\
    \ != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
    \ md - x.val));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 3 \"convolution/ntt.hpp\"\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <tuple>\n\
    #line 9 \"convolution/ntt.hpp\"\n\n// CUT begin\n// Integer convolution for arbitrary\
    \ mod\n// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime class.\n\
    // We skip Garner's algorithm if `skip_garner` is true or mod is in `nttprimes`.\n\
    // input: a (size: n), b (size: m)\n// return: vector (size: n + m - 1)\ntemplate\
    \ <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT>\
    \ b, bool skip_garner = false);\n\nconstexpr int nttprimes[3] = {998244353, 167772161,\
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
    \            }\n        }\n        int n_inv = MODINT(n).inv();\n        for (auto\
    \ &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD> std::vector<ModInt<MOD>> nttconv_(const\
    \ std::vector<int> &a, const std::vector<int> &b) {\n    int sz = a.size();\n\
    \    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n    std::vector<ModInt<MOD>>\
    \ ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++) ap[i] = a[i], bp[i] = b[i];\n\
    \    ntt(ap, false);\n    if (a == b)\n        bp = ap;\n    else\n        ntt(bp,\
    \ false);\n    for (int i = 0; i < sz; i++) ap[i] *= bp[i];\n    ntt(ap, true);\n\
    \    return ap;\n}\nlong long garner_ntt_(int r0, int r1, int r2, int mod) {\n\
    \    using mint2 = ModInt<nttprimes[2]>;\n    static const long long m01 = 1LL\
    \ * nttprimes[0] * nttprimes[1];\n    static const long long m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv();\n\
    \    static const long long m01_inv_m2 = mint2(m01).inv();\n\n    int v1 = (m0_inv_m1\
    \ * (r1 + nttprimes[1] - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2) - r0 -\
    \ mint2(nttprimes[0]) * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0]\
    \ * v1 + m01 % mod * v2.val) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT>\
    \ nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool skip_garner) {\n\
    \    if (a.empty() or b.empty()) return {};\n    int sz = 1, n = a.size(), m =\
    \ b.size();\n    while (sz < n + m) sz <<= 1;\n    if (sz <= 16) {\n        std::vector<MODINT>\
    \ ret(n + m - 1);\n        for (int i = 0; i < n; i++) {\n            for (int\
    \ j = 0; j < m; j++) ret[i + j] += a[i] * b[j];\n        }\n        return ret;\n\
    \    }\n    int mod = MODINT::mod();\n    if (skip_garner or std::find(std::begin(nttprimes),\
    \ std::end(nttprimes), mod) != std::end(nttprimes)) {\n        a.resize(sz), b.resize(sz);\n\
    \        if (a == b) {\n            ntt(a, false);\n            b = a;\n     \
    \   } else {\n            ntt(a, false), ntt(b, false);\n        }\n        for\
    \ (int i = 0; i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n\
    \ + m - 1);\n    } else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val;\n        for (int i = 0; i < m; i++)\
    \ bi[i] = b[i].val;\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n   \
    \     auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\
    \ a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);\n    }\n   \
    \ return a;\n}\n#line 4 \"formal_power_series/linear_recurrence.hpp\"\n#include\
    \ <utility>\n#line 6 \"formal_power_series/linear_recurrence.hpp\"\n\n// CUT begin\n\
    // Berlekamp\u2013Massey algorithm\n// https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm\n\
    // Complexity: O(N^2)\n// input: S = sequence from field K\n// return: L     \
    \     = degree of minimal polynomial,\n//         C_reversed = monic min. polynomial\
    \ (size = L + 1, reversed order, C_reversed[0] = 1))\n// Formula: convolve(S,\
    \ C_reversed)[i] = 0 for i >= L\n// Example:\n// - [1, 2, 4, 8, 16]   -> (1, [1,\
    \ -2])\n// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])\n// - [0, 0, 0, 0, 1]    ->\
    \ (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)\n// - []                 ->\
    \ (0, [1])\n// - [0, 0, 0]          -> (0, [1])\n// - [-2]               -> (1,\
    \ [1, 2])\ntemplate <typename Tfield> std::pair<int, std::vector<Tfield>> find_linear_recurrence(const\
    \ std::vector<Tfield> &S) {\n    int N = S.size();\n    using poly = std::vector<Tfield>;\n\
    \    poly C_reversed{1}, B{1};\n    int L = 0, m = 1;\n    Tfield b = 1;\n\n \
    \   // adjust: C(x) <- C(x) - (d / b) x^m B(x)\n    auto adjust = [](poly C, const\
    \ poly &B, Tfield d, Tfield b, int m) -> poly {\n        C.resize(std::max(C.size(),\
    \ B.size() + m));\n        Tfield a = d / b;\n        for (unsigned i = 0; i <\
    \ B.size(); i++) C[i + m] -= a * B[i];\n        return C;\n    };\n\n    for (int\
    \ n = 0; n < N; n++) {\n        Tfield d = S[n];\n        for (int i = 1; i <=\
    \ L; i++) d += C_reversed[i] * S[n - i];\n\n        if (d == 0)\n            m++;\n\
    \        else if (2 * L <= n) {\n            poly T = C_reversed;\n          \
    \  C_reversed = adjust(C_reversed, B, d, b, m);\n            L = n + 1 - L;\n\
    \            B = T;\n            b = d;\n            m = 1;\n        } else\n\
    \            C_reversed = adjust(C_reversed, B, d, b, m++);\n    }\n    return\
    \ std::make_pair(L, C_reversed);\n}\n\n// Calculate $x^N \\bmod f(x)$\n// Known\
    \ as `Kitamasa method`\n// Input: f_reversed: monic, reversed (f_reversed[0] =\
    \ 1)\n// Complexity: $O(K^2 \\log N)$ ($K$: deg. of $f$)\n// Example: (4, [1,\
    \ -1, -1]) -> [2, 3]\n//          ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2\
    \ )\n// Reference: http://misawa.github.io/others/fast_kitamasa_method.html\n\
    //            http://sugarknri.hatenablog.com/entry/2017/11/18/233936\ntemplate\
    \ <typename Tfield>\nstd::vector<Tfield> monomial_mod_polynomial(long long N,\
    \ const std::vector<Tfield> &f_reversed) {\n    assert(!f_reversed.empty() and\
    \ f_reversed[0] == 1);\n    int K = f_reversed.size() - 1;\n    if (!K) return\
    \ {};\n    int D = 64 - __builtin_clzll(N);\n    std::vector<Tfield> ret(K, 0);\n\
    \    ret[0] = 1;\n    auto self_conv = [](std::vector<Tfield> x) -> std::vector<Tfield>\
    \ {\n        int d = x.size();\n        std::vector<Tfield> ret(d * 2 - 1);\n\
    \        for (int i = 0; i < d; i++) {\n            ret[i * 2] += x[i] * x[i];\n\
    \            for (int j = 0; j < i; j++) ret[i + j] += x[i] * x[j] * 2;\n    \
    \    }\n        return ret;\n    };\n    for (int d = D; d--;) {\n        ret\
    \ = self_conv(ret);\n        for (int i = 2 * K - 2; i >= K; i--) {\n        \
    \    for (int j = 1; j <= K; j++) ret[i - j] -= ret[i] * f_reversed[j];\n    \
    \    }\n        ret.resize(K);\n        if ((N >> d) & 1) {\n            std::vector<Tfield>\
    \ c(K);\n            c[0] = -ret[K - 1] * f_reversed[K];\n            for (int\
    \ i = 1; i < K; i++) { c[i] = ret[i - 1] - ret[K - 1] * f_reversed[K - i]; }\n\
    \            ret = c;\n        }\n    }\n    return ret;\n}\n\n// Guess k-th element\
    \ of the sequence, assuming linear recurrence\n// initial_elements: 0-ORIGIN\n\
    // Verify: abc198f https://atcoder.jp/contests/abc198/submissions/21837815\ntemplate\
    \ <typename Tfield> Tfield guess_kth_term(const std::vector<Tfield> &initial_elements,\
    \ long long k) {\n    assert(k >= 0);\n    if (k < static_cast<long long>(initial_elements.size()))\
    \ return initial_elements[k];\n    const auto f = find_linear_recurrence<Tfield>(initial_elements).second;\n\
    \    const auto g = monomial_mod_polynomial<Tfield>(k, f);\n    Tfield ret = 0;\n\
    \    for (unsigned i = 0; i < g.size(); i++) ret += g[i] * initial_elements[i];\n\
    \    return ret;\n}\n#line 6 \"linear_algebra_matrix/blackbox_linear_algebra.hpp\"\
    \n#include <chrono>\n#include <numeric>\n#include <random>\n#line 11 \"linear_algebra_matrix/blackbox_linear_algebra.hpp\"\
    \n\ntemplate <typename ModInt> std::vector<ModInt> gen_random_vector(int len)\
    \ {\n    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    static std::uniform_int_distribution<int> rnd(1, ModInt::mod() - 1);\n  \
    \  std::vector<ModInt> ret(len);\n    for (auto &x : ret) x = rnd(mt);\n    return\
    \ ret;\n};\n\n// Sparse matrix\ntemplate <typename Tp> struct sparse_matrix {\n\
    \    int H, W;\n    std::vector<std::vector<std::pair<int, Tp>>> vals;\n    sparse_matrix(int\
    \ H = 0, int W = 0) : H(H), W(W), vals(H) {}\n    int height() const { return\
    \ H; }\n    int width() const { return W; }\n    void add_element(int i, int j,\
    \ Tp val) {\n        assert(i >= 0 and i < H);\n        assert(j >= 0 and i <\
    \ W);\n        vals[i].emplace_back(j, val);\n    }\n    std::vector<Tp> prod(const\
    \ std::vector<Tp> &vec) const {\n        assert(W == int(vec.size()));\n     \
    \   std::vector<Tp> ret(H);\n        for (int i = 0; i < H; i++) {\n         \
    \   for (const auto &p : vals[i]) ret[i] += p.second * vec[p.first];\n       \
    \ }\n        return ret;\n    }\n    std::vector<Tp> prod_left(const std::vector<Tp>\
    \ &vec) const {\n        assert(H == int(vec.size()));\n        std::vector<Tp>\
    \ ret(W);\n        for (int i = 0; i < H; i++) {\n            for (const auto\
    \ &p : vals[i]) ret[p.first] += p.second * vec[i];\n        }\n        return\
    \ ret;\n    }\n    std::vector<std::vector<Tp>> dense() const {\n        std::vector<std::vector<Tp>>\
    \ ret(H, std::vector<Tp>(W));\n        for (int i = 0; i < H; i++) {\n       \
    \     for (auto p : vals[i]) ret[i][p.first] += p.second;\n        }\n       \
    \ return ret;\n    }\n};\n\n// Toeplitz matrix\n// M = [\n// [ vw_0 vw_1 vw_2\
    \ ... ]\n// [ vh_1 ...           ]\n// [ vh_2 ...           ]\n// [ ...      \
    \          ] (vw_0 == vh_0)\n// prod() / prod_left() : O((H + W) log (H + W))\n\
    template <typename NTTModInt> struct toeplitz {\n    int _h, _w;\n    int _len_pow2;\n\
    \    std::vector<NTTModInt> ts, ntt_ts;\n    toeplitz(const std::vector<NTTModInt>\
    \ &vh, const std::vector<NTTModInt> &vw)\n        : _h(vh.size()), _w(vw.size())\
    \ {\n        assert(vh.size() and vw.size() and vh[0] == vw[0]);\n        ts.resize(_h\
    \ + _w - 1);\n        for (int i = 0; i < _w; i++) ts[i] = vw[_w - 1 - i];\n \
    \       for (int j = 0; j < _h; j++) ts[_w - 1 + j] = vh[j];\n        _len_pow2\
    \ = 1;\n        while (_len_pow2 < int(ts.size()) + std::max(_h, _w) - 1) _len_pow2\
    \ *= 2;\n        ntt_ts = ts;\n        ntt_ts.resize(_len_pow2);\n        ntt(ntt_ts,\
    \ false);\n    }\n    int height() const { return _h; }\n    int width() const\
    \ { return _w; }\n    std::vector<NTTModInt> prod(std::vector<NTTModInt> b) const\
    \ {\n        assert(int(b.size()) == _w);\n        b.resize(_len_pow2);\n    \
    \    ntt(b, false);\n        for (int i = 0; i < _len_pow2; i++) b[i] *= ntt_ts[i];\n\
    \        ntt(b, true);\n        b.erase(b.begin(), b.begin() + _w - 1);\n    \
    \    b.resize(_h);\n        return b;\n    }\n    std::vector<NTTModInt> prod_left(std::vector<NTTModInt>\
    \ b) const {\n        assert(int(b.size()) == _h);\n        std::reverse(b.begin(),\
    \ b.end());\n        b.resize(_len_pow2);\n        ntt(b, false);\n        for\
    \ (int i = 0; i < _len_pow2; i++) b[i] *= ntt_ts[i];\n        ntt(b, true);\n\
    \        b.erase(b.begin(), b.begin() + _h - 1);\n        b.resize(_w);\n    \
    \    std::reverse(b.begin(), b.end());\n        return b;\n    }\n    std::vector<std::vector<NTTModInt>>\
    \ dense() const {\n        std::vector<std::vector<NTTModInt>> ret(_h, std::vector<NTTModInt>(_w));\n\
    \        for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ ret[i][j] = ts[i - j + _w - 1];\n        }\n        return ret;\n    }\n};\n\
    \n// Square Toeplitz matrix\n// M = [\n// [ t_(N-1) t_(N-2) ... t_1 t_0     ]\n\
    // [ t_N     t_(N-1) ... t_2 t_1     ]\n// [ ...                             ]\n\
    // [ t_(N*2-2)       ...     t_(N-1) ]]\n// prod() / prod_left() : O(N log N)\n\
    template <typename NTTModInt> struct square_toeplitz {\n    int _dim;\n    int\
    \ _len_pow2;\n    std::vector<NTTModInt> ts;\n    std::vector<NTTModInt> ntt_ts;\n\
    \    square_toeplitz(const std::vector<NTTModInt> &t) : _dim(t.size() / 2 + 1),\
    \ ts(t) {\n        assert(t.size() % 2);\n        _len_pow2 = 1;\n        while\
    \ (_len_pow2 < int(ts.size()) + _dim - 1) _len_pow2 *= 2;\n        ntt_ts = ts;\n\
    \        ntt_ts.resize(_len_pow2);\n        ntt(ntt_ts, false);\n    }\n    int\
    \ height() const { return _dim; }\n    int width() const { return _dim; }\n\n\
    \    // Calculate A * b\n    std::vector<NTTModInt> prod(std::vector<NTTModInt>\
    \ b) const {\n        assert(int(b.size()) == _dim);\n        b.resize(_len_pow2);\n\
    \        ntt(b, false);\n        for (int i = 0; i < _len_pow2; i++) b[i] *= ntt_ts[i];\n\
    \        ntt(b, true);\n        b.erase(b.begin(), b.begin() + _dim - 1);\n  \
    \      b.resize(_dim);\n        return b;\n    }\n    // Calculate bT * A\n  \
    \  std::vector<NTTModInt> prod_left(std::vector<NTTModInt> b) const {\n      \
    \  std::reverse(b.begin(), b.end());\n        b = prod(b);\n        std::reverse(b.begin(),\
    \ b.end());\n        return b;\n    }\n    std::vector<std::vector<NTTModInt>>\
    \ dense() const {\n        std::vector<std::vector<NTTModInt>> ret(_dim, std::vector<NTTModInt>(_dim));\n\
    \        for (int i = 0; i < _dim; i++) {\n            for (int j = 0; j < _dim;\
    \ j++) ret[i][j] = ts[i - j + _dim - 1];\n        }\n        return ret;\n   \
    \ }\n};\n\n// Probabilistic algorithm to find a solution of linear equation Ax\
    \ = b if exists.\n// Complexity: O(n T(n) + n^2)\n// Reference:\n// [1] W. Eberly,\
    \ E. Kaltofen, \"On randomized Lanczos algorithms,\" Proc. of international symposium\
    \ on\n//     Symbolic and algebraic computation, 176-183, 1997.\ntemplate <typename\
    \ Matrix, typename T>\nstd::vector<T> linear_system_solver_lanczos(const Matrix\
    \ &A, const std::vector<T> &b) {\n    assert(A.height() == int(b.size()));\n \
    \   const int M = A.height(), N = A.width();\n\n    const std::vector<T> D1 =\
    \ gen_random_vector<T>(N), D2 = gen_random_vector<T>(M), v = gen_random_vector<T>(N);\n\
    \    auto applyD1 = [&D1](std::vector<T> v) {\n        for (int i = 0; i < int(v.size());\
    \ i++) v[i] *= D1[i];\n        return v;\n    };\n    auto applyD2 = [&D2](std::vector<T>\
    \ v) {\n        for (int i = 0; i < int(v.size()); i++) v[i] *= D2[i];\n     \
    \   return v;\n    };\n    auto applyAtilde = [&](std::vector<T> v) -> std::vector<T>\
    \ {\n        v = applyD1(v);\n        v = A.prod(v);\n        v = applyD2(v);\n\
    \        v = A.prod_left(v);\n        v = applyD1(v);\n        return v;\n   \
    \ };\n    auto dot = [&](const std::vector<T> &vl, const std::vector<T> &vr) ->\
    \ T {\n        return std::inner_product(vl.begin(), vl.end(), vr.begin(), T(0));\n\
    \    };\n    auto scalar_vec = [&](const T &x, std::vector<T> vec) -> std::vector<T>\
    \ {\n        for (auto &v : vec) v *= x;\n        return vec;\n    };\n\n    auto\
    \ btilde1 = applyD1(A.prod_left(applyD2(b))), btilde2 = applyAtilde(v);\n    std::vector<T>\
    \ btilde(N);\n    for (int i = 0; i < N; i++) btilde[i] = btilde1[i] + btilde2[i];\n\
    \n    std::vector<T> w0 = btilde, v1 = applyAtilde(w0);\n    std::vector<T> wm1(w0.size()),\
    \ v0(v1.size());\n    T t0 = dot(v1, w0), gamma = dot(btilde, w0) / t0, tm1 =\
    \ 1;\n    std::vector<T> x = scalar_vec(gamma, w0);\n    while (true) {\n    \
    \    if (!t0 or !std::count_if(w0.begin(), w0.end(), [](T x) { return x != T(0);\
    \ })) break;\n        T alpha = dot(v1, v1) / t0, beta = dot(v1, v0) / tm1;\n\
    \        std::vector<T> w1(N);\n        for (int i = 0; i < N; i++) w1[i] = v1[i]\
    \ - alpha * w0[i] - beta * wm1[i];\n        std::vector<T> v2 = applyAtilde(w1);\n\
    \        T t1 = dot(w1, v2);\n        gamma = dot(btilde, w1) / t1;\n        for\
    \ (int i = 0; i < N; i++) x[i] += gamma * w1[i];\n\n        wm1 = w0, w0 = w1;\n\
    \        v0 = v1, v1 = v2;\n        tm1 = t0, t0 = t1;\n    }\n    for (int i\
    \ = 0; i < N; i++) x[i] -= v[i];\n    return applyD1(x);\n}\n\n// Probabilistic\
    \ algorithm to calculate determinant of matrices\n// Complexity: O(n T(n) + n^2)\n\
    // Reference:\n// [1] D. H. Wiedmann, \"Solving sparse linear equations over finite\
    \ fields,\"\n//     IEEE Trans. on Information Theory, 32(1), 54-62, 1986.\ntemplate\
    \ <class Matrix, class Tp> Tp blackbox_determinant(const Matrix &M) {\n    assert(M.height()\
    \ == M.width());\n    const int N = M.height();\n    std::vector<Tp> b = gen_random_vector<Tp>(N),\
    \ u = gen_random_vector<Tp>(N), D = gen_random_vector<Tp>(N);\n    std::vector<Tp>\
    \ uMDib(2 * N);\n    for (int i = 0; i < 2 * N; i++) {\n        uMDib[i] = std::inner_product(u.begin(),\
    \ u.end(), b.begin(), Tp(0));\n        for (int j = 0; j < N; j++) b[j] *= D[j];\n\
    \        b = M.prod(b);\n    }\n    auto ret = find_linear_recurrence<Tp>(uMDib);\n\
    \    Tp det = ret.second.back() * (N % 2 ? -1 : 1);\n    Tp ddet = 1;\n    for\
    \ (auto d : D) ddet *= d;\n    return det / ddet;\n}\n"
  code: "#pragma once\n#include \"../convolution/ntt.hpp\"\n#include \"../formal_power_series/linear_recurrence.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <chrono>\n#include <numeric>\n\
    #include <random>\n#include <utility>\n#include <vector>\n\ntemplate <typename\
    \ ModInt> std::vector<ModInt> gen_random_vector(int len) {\n    static std::mt19937\
    \ mt(std::chrono::steady_clock::now().time_since_epoch().count());\n    static\
    \ std::uniform_int_distribution<int> rnd(1, ModInt::mod() - 1);\n    std::vector<ModInt>\
    \ ret(len);\n    for (auto &x : ret) x = rnd(mt);\n    return ret;\n};\n\n// Sparse\
    \ matrix\ntemplate <typename Tp> struct sparse_matrix {\n    int H, W;\n    std::vector<std::vector<std::pair<int,\
    \ Tp>>> vals;\n    sparse_matrix(int H = 0, int W = 0) : H(H), W(W), vals(H) {}\n\
    \    int height() const { return H; }\n    int width() const { return W; }\n \
    \   void add_element(int i, int j, Tp val) {\n        assert(i >= 0 and i < H);\n\
    \        assert(j >= 0 and i < W);\n        vals[i].emplace_back(j, val);\n  \
    \  }\n    std::vector<Tp> prod(const std::vector<Tp> &vec) const {\n        assert(W\
    \ == int(vec.size()));\n        std::vector<Tp> ret(H);\n        for (int i =\
    \ 0; i < H; i++) {\n            for (const auto &p : vals[i]) ret[i] += p.second\
    \ * vec[p.first];\n        }\n        return ret;\n    }\n    std::vector<Tp>\
    \ prod_left(const std::vector<Tp> &vec) const {\n        assert(H == int(vec.size()));\n\
    \        std::vector<Tp> ret(W);\n        for (int i = 0; i < H; i++) {\n    \
    \        for (const auto &p : vals[i]) ret[p.first] += p.second * vec[i];\n  \
    \      }\n        return ret;\n    }\n    std::vector<std::vector<Tp>> dense()\
    \ const {\n        std::vector<std::vector<Tp>> ret(H, std::vector<Tp>(W));\n\
    \        for (int i = 0; i < H; i++) {\n            for (auto p : vals[i]) ret[i][p.first]\
    \ += p.second;\n        }\n        return ret;\n    }\n};\n\n// Toeplitz matrix\n\
    // M = [\n// [ vw_0 vw_1 vw_2 ... ]\n// [ vh_1 ...           ]\n// [ vh_2 ...\
    \           ]\n// [ ...                ] (vw_0 == vh_0)\n// prod() / prod_left()\
    \ : O((H + W) log (H + W))\ntemplate <typename NTTModInt> struct toeplitz {\n\
    \    int _h, _w;\n    int _len_pow2;\n    std::vector<NTTModInt> ts, ntt_ts;\n\
    \    toeplitz(const std::vector<NTTModInt> &vh, const std::vector<NTTModInt> &vw)\n\
    \        : _h(vh.size()), _w(vw.size()) {\n        assert(vh.size() and vw.size()\
    \ and vh[0] == vw[0]);\n        ts.resize(_h + _w - 1);\n        for (int i =\
    \ 0; i < _w; i++) ts[i] = vw[_w - 1 - i];\n        for (int j = 0; j < _h; j++)\
    \ ts[_w - 1 + j] = vh[j];\n        _len_pow2 = 1;\n        while (_len_pow2 <\
    \ int(ts.size()) + std::max(_h, _w) - 1) _len_pow2 *= 2;\n        ntt_ts = ts;\n\
    \        ntt_ts.resize(_len_pow2);\n        ntt(ntt_ts, false);\n    }\n    int\
    \ height() const { return _h; }\n    int width() const { return _w; }\n    std::vector<NTTModInt>\
    \ prod(std::vector<NTTModInt> b) const {\n        assert(int(b.size()) == _w);\n\
    \        b.resize(_len_pow2);\n        ntt(b, false);\n        for (int i = 0;\
    \ i < _len_pow2; i++) b[i] *= ntt_ts[i];\n        ntt(b, true);\n        b.erase(b.begin(),\
    \ b.begin() + _w - 1);\n        b.resize(_h);\n        return b;\n    }\n    std::vector<NTTModInt>\
    \ prod_left(std::vector<NTTModInt> b) const {\n        assert(int(b.size()) ==\
    \ _h);\n        std::reverse(b.begin(), b.end());\n        b.resize(_len_pow2);\n\
    \        ntt(b, false);\n        for (int i = 0; i < _len_pow2; i++) b[i] *= ntt_ts[i];\n\
    \        ntt(b, true);\n        b.erase(b.begin(), b.begin() + _h - 1);\n    \
    \    b.resize(_w);\n        std::reverse(b.begin(), b.end());\n        return\
    \ b;\n    }\n    std::vector<std::vector<NTTModInt>> dense() const {\n       \
    \ std::vector<std::vector<NTTModInt>> ret(_h, std::vector<NTTModInt>(_w));\n \
    \       for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ ret[i][j] = ts[i - j + _w - 1];\n        }\n        return ret;\n    }\n};\n\
    \n// Square Toeplitz matrix\n// M = [\n// [ t_(N-1) t_(N-2) ... t_1 t_0     ]\n\
    // [ t_N     t_(N-1) ... t_2 t_1     ]\n// [ ...                             ]\n\
    // [ t_(N*2-2)       ...     t_(N-1) ]]\n// prod() / prod_left() : O(N log N)\n\
    template <typename NTTModInt> struct square_toeplitz {\n    int _dim;\n    int\
    \ _len_pow2;\n    std::vector<NTTModInt> ts;\n    std::vector<NTTModInt> ntt_ts;\n\
    \    square_toeplitz(const std::vector<NTTModInt> &t) : _dim(t.size() / 2 + 1),\
    \ ts(t) {\n        assert(t.size() % 2);\n        _len_pow2 = 1;\n        while\
    \ (_len_pow2 < int(ts.size()) + _dim - 1) _len_pow2 *= 2;\n        ntt_ts = ts;\n\
    \        ntt_ts.resize(_len_pow2);\n        ntt(ntt_ts, false);\n    }\n    int\
    \ height() const { return _dim; }\n    int width() const { return _dim; }\n\n\
    \    // Calculate A * b\n    std::vector<NTTModInt> prod(std::vector<NTTModInt>\
    \ b) const {\n        assert(int(b.size()) == _dim);\n        b.resize(_len_pow2);\n\
    \        ntt(b, false);\n        for (int i = 0; i < _len_pow2; i++) b[i] *= ntt_ts[i];\n\
    \        ntt(b, true);\n        b.erase(b.begin(), b.begin() + _dim - 1);\n  \
    \      b.resize(_dim);\n        return b;\n    }\n    // Calculate bT * A\n  \
    \  std::vector<NTTModInt> prod_left(std::vector<NTTModInt> b) const {\n      \
    \  std::reverse(b.begin(), b.end());\n        b = prod(b);\n        std::reverse(b.begin(),\
    \ b.end());\n        return b;\n    }\n    std::vector<std::vector<NTTModInt>>\
    \ dense() const {\n        std::vector<std::vector<NTTModInt>> ret(_dim, std::vector<NTTModInt>(_dim));\n\
    \        for (int i = 0; i < _dim; i++) {\n            for (int j = 0; j < _dim;\
    \ j++) ret[i][j] = ts[i - j + _dim - 1];\n        }\n        return ret;\n   \
    \ }\n};\n\n// Probabilistic algorithm to find a solution of linear equation Ax\
    \ = b if exists.\n// Complexity: O(n T(n) + n^2)\n// Reference:\n// [1] W. Eberly,\
    \ E. Kaltofen, \"On randomized Lanczos algorithms,\" Proc. of international symposium\
    \ on\n//     Symbolic and algebraic computation, 176-183, 1997.\ntemplate <typename\
    \ Matrix, typename T>\nstd::vector<T> linear_system_solver_lanczos(const Matrix\
    \ &A, const std::vector<T> &b) {\n    assert(A.height() == int(b.size()));\n \
    \   const int M = A.height(), N = A.width();\n\n    const std::vector<T> D1 =\
    \ gen_random_vector<T>(N), D2 = gen_random_vector<T>(M), v = gen_random_vector<T>(N);\n\
    \    auto applyD1 = [&D1](std::vector<T> v) {\n        for (int i = 0; i < int(v.size());\
    \ i++) v[i] *= D1[i];\n        return v;\n    };\n    auto applyD2 = [&D2](std::vector<T>\
    \ v) {\n        for (int i = 0; i < int(v.size()); i++) v[i] *= D2[i];\n     \
    \   return v;\n    };\n    auto applyAtilde = [&](std::vector<T> v) -> std::vector<T>\
    \ {\n        v = applyD1(v);\n        v = A.prod(v);\n        v = applyD2(v);\n\
    \        v = A.prod_left(v);\n        v = applyD1(v);\n        return v;\n   \
    \ };\n    auto dot = [&](const std::vector<T> &vl, const std::vector<T> &vr) ->\
    \ T {\n        return std::inner_product(vl.begin(), vl.end(), vr.begin(), T(0));\n\
    \    };\n    auto scalar_vec = [&](const T &x, std::vector<T> vec) -> std::vector<T>\
    \ {\n        for (auto &v : vec) v *= x;\n        return vec;\n    };\n\n    auto\
    \ btilde1 = applyD1(A.prod_left(applyD2(b))), btilde2 = applyAtilde(v);\n    std::vector<T>\
    \ btilde(N);\n    for (int i = 0; i < N; i++) btilde[i] = btilde1[i] + btilde2[i];\n\
    \n    std::vector<T> w0 = btilde, v1 = applyAtilde(w0);\n    std::vector<T> wm1(w0.size()),\
    \ v0(v1.size());\n    T t0 = dot(v1, w0), gamma = dot(btilde, w0) / t0, tm1 =\
    \ 1;\n    std::vector<T> x = scalar_vec(gamma, w0);\n    while (true) {\n    \
    \    if (!t0 or !std::count_if(w0.begin(), w0.end(), [](T x) { return x != T(0);\
    \ })) break;\n        T alpha = dot(v1, v1) / t0, beta = dot(v1, v0) / tm1;\n\
    \        std::vector<T> w1(N);\n        for (int i = 0; i < N; i++) w1[i] = v1[i]\
    \ - alpha * w0[i] - beta * wm1[i];\n        std::vector<T> v2 = applyAtilde(w1);\n\
    \        T t1 = dot(w1, v2);\n        gamma = dot(btilde, w1) / t1;\n        for\
    \ (int i = 0; i < N; i++) x[i] += gamma * w1[i];\n\n        wm1 = w0, w0 = w1;\n\
    \        v0 = v1, v1 = v2;\n        tm1 = t0, t0 = t1;\n    }\n    for (int i\
    \ = 0; i < N; i++) x[i] -= v[i];\n    return applyD1(x);\n}\n\n// Probabilistic\
    \ algorithm to calculate determinant of matrices\n// Complexity: O(n T(n) + n^2)\n\
    // Reference:\n// [1] D. H. Wiedmann, \"Solving sparse linear equations over finite\
    \ fields,\"\n//     IEEE Trans. on Information Theory, 32(1), 54-62, 1986.\ntemplate\
    \ <class Matrix, class Tp> Tp blackbox_determinant(const Matrix &M) {\n    assert(M.height()\
    \ == M.width());\n    const int N = M.height();\n    std::vector<Tp> b = gen_random_vector<Tp>(N),\
    \ u = gen_random_vector<Tp>(N), D = gen_random_vector<Tp>(N);\n    std::vector<Tp>\
    \ uMDib(2 * N);\n    for (int i = 0; i < 2 * N; i++) {\n        uMDib[i] = std::inner_product(u.begin(),\
    \ u.end(), b.begin(), Tp(0));\n        for (int j = 0; j < N; j++) b[j] *= D[j];\n\
    \        b = M.prod(b);\n    }\n    auto ret = find_linear_recurrence<Tp>(uMDib);\n\
    \    Tp det = ret.second.back() * (N % 2 ? -1 : 1);\n    Tp ddet = 1;\n    for\
    \ (auto d : D) ddet *= d;\n    return det / ddet;\n}\n"
  dependsOn:
  - convolution/ntt.hpp
  - modint.hpp
  - formal_power_series/linear_recurrence.hpp
  isVerificationFile: false
  path: linear_algebra_matrix/blackbox_linear_algebra.hpp
  requiredBy: []
  timestamp: '2021-06-13 04:24:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: linear_algebra_matrix/blackbox_linear_algebra.hpp
layout: document
redirect_from:
- /library/linear_algebra_matrix/blackbox_linear_algebra.hpp
- /library/linear_algebra_matrix/blackbox_linear_algebra.hpp.html
title: linear_algebra_matrix/blackbox_linear_algebra.hpp
---
