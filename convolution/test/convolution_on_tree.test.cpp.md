---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/convolution_on_tree.hpp
    title: "Convolution on rooted tree \uFF08\u6839\u4ED8\u304D\u6728\u4E0A\u306E\u7573\
      \u307F\u8FBC\u307F\uFF09"
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/2004
    links:
    - https://yukicoder.me/problems/no/2004
  bundledCode: "#line 1 \"convolution/test/convolution_on_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/2004\"\n#line 2 \"convolution/convolution_on_tree.hpp\"\
    \n#include <cassert>\n#include <utility>\n#include <vector>\n\n// ConvolutionOnTree\
    \ : \u6839\u4ED8\u304D\u6728\u4E0A\u3067\u6839\u65B9\u5411\u3078\u7573\u307F\u8FBC\
    \u307F\n// Input:\n// - par_ : \u5404\u9802\u70B9\u306E\u89AA\u306E\u9802\u70B9\
    \u756A\u53F7 \u6839\u306E par_ \u306F -1\n// - f : \u5404\u9802\u70B9\u306E\u521D\
    \u671F\u5024\n// - trans : trans[i] = \u5404\u9802\u70B9\u304B\u3089 i \u4E16\u4EE3\
    \u76EE\u306E\u89AA\u9802\u70B9\u3078\u306E\u9077\u79FB\u4FC2\u6570\n// Verified:\
    \ https://yukicoder.me/problems/no/2004\nstruct ConvolutionOnTree {\n    int N;\n\
    \    int root;\n    std::vector<int> par;\n    std::vector<std::vector<int>> children;\n\
    \n    std::vector<int> depth;\n    std::vector<int> farthest_leaf;\n\n    void\
    \ _rec_build_hld(int now) {\n        farthest_leaf[now] = now;\n        for (int\
    \ nxt : children[now]) {\n            depth[nxt] = depth[now] + 1;\n         \
    \   _rec_build_hld(nxt);\n            if (depth[farthest_leaf[now]] < depth[farthest_leaf[nxt]])\
    \ {\n                farthest_leaf[now] = farthest_leaf[nxt];\n            }\n\
    \        }\n    }\n\n    void _build_hld() {\n        depth.assign(N, 0);\n  \
    \      farthest_leaf.assign(N, -1);\n        _rec_build_hld(root);\n    }\n\n\
    \    ConvolutionOnTree(std::vector<int> par_) : N(par_.size()), par(par_), children(par.size())\
    \ {\n        root = -1;\n        for (int i = 0; i < N; ++i) {\n            if\
    \ (par[i] >= 0 and par[i] < N) {\n                children[par[i]].push_back(i);\n\
    \            } else {\n                assert(root == -1);\n                par[i]\
    \ = -1;\n                root = i;\n            }\n        }\n        assert(root\
    \ != -1);\n\n        _build_hld();\n    }\n\n    template <class T, class F>\n\
    \    std::vector<T> _run_rec(const int r, int h, std::vector<T> &ret, const std::vector<T>\
    \ &f,\n                            const std::vector<T> &trans, F convolver) {\n\
    \        const int leaf = farthest_leaf[r], d = depth[leaf] - depth[r] + 1;\n\
    \        std::vector<T> g;\n        std::vector<int> ids;\n        g.reserve(d),\
    \ ids.reserve(d);\n\n        for (int cur = leaf, prv = -1;; prv = cur, cur =\
    \ par[cur]) {\n            ids.push_back(cur);\n            g.push_back(f[cur]);\n\
    \n            for (int nxt : children[cur]) {\n                if (nxt == prv)\
    \ continue;\n                int nxtlen = depth[farthest_leaf[nxt]] - depth[cur];\n\
    \                std::vector<T> gchild =\n                    _run_rec(nxt, ids.at(int(ids.size())\
    \ - nxtlen - 1), ret, f, trans, convolver);\n                for (int i = 0; i\
    \ < int(gchild.size()); ++i) {\n                    g.at(int(g.size()) - int(gchild.size())\
    \ - 1 + i) += gchild[i];\n                }\n            }\n\n            if (cur\
    \ == r) break;\n        }\n\n        std::vector<T> trans_sub(trans.begin(), trans.begin()\
    \ + std::min(trans.size(), g.size()));\n        // trans_sub = nttconv(g, trans_sub);\n\
    \        trans_sub = convolver(g, trans_sub);\n\n        for (int cur = leaf,\
    \ i = 0;; cur = par[cur], ++i, h = h >= 0 ? par[h] : h) {\n            ret.at(cur)\
    \ += trans_sub.at(i);\n            if (h >= 0) ret.at(h) -= trans_sub.at(i);\n\
    \            if (cur == r) break;\n        }\n        return g;\n    }\n\n   \
    \ template <class T, class F>\n    std::vector<T> run(const std::vector<T> &f,\
    \ const std::vector<T> &trans, F convolver) {\n        std::vector<T> ret(N, T());\n\
    \        _run_rec<T, F>(root, -1, ret, f, trans, convolver);\n        return ret;\n\
    \    }\n};\n/* example:\nConvolutionOnTree tree(par);\n\nauto convolve = [&](vector<mint>\
    \ &l, vector<mint> &r) { return nttconv(l, r); };\nauto ret = tree.run(A, trans,\
    \ convolve);\n*/\n#line 3 \"modint.hpp\"\n#include <iostream>\n#include <set>\n\
    #line 6 \"modint.hpp\"\n\ntemplate <int md> struct ModInt {\n    static_assert(md\
    \ > 1);\n    using lint = long long;\n    constexpr static int mod() { return\
    \ md; }\n    static int get_primitive_root() {\n        static int primitive_root\
    \ = 0;\n        if (!primitive_root) {\n            primitive_root = [&]() {\n\
    \                std::set<int> fac;\n                int v = md - 1;\n       \
    \         for (lint i = 2; i * i <= v; i++)\n                    while (v % i\
    \ == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n  \
    \              for (int g = 1; g < md; g++) {\n                    bool ok = true;\n\
    \                    for (auto i : fac)\n                        if (ModInt(g).pow((md\
    \ - 1) / i) == 1) {\n                            ok = false;\n               \
    \             break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root;\n    }\n    int val_;\n    int val() const\
    \ noexcept { return val_; }\n    constexpr ModInt() : val_(0) {}\n    constexpr\
    \ ModInt &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n \
    \   constexpr ModInt(lint v) { _setval(v % md + md); }\n    constexpr explicit\
    \ operator bool() const { return val_ != 0; }\n    constexpr ModInt operator+(const\
    \ ModInt &x) const {\n        return ModInt()._setval((lint)val_ + x.val_);\n\
    \    }\n    constexpr ModInt operator-(const ModInt &x) const {\n        return\
    \ ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    constexpr ModInt operator*(const\
    \ ModInt &x) const {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n\
    \    }\n    constexpr ModInt operator/(const ModInt &x) const {\n        return\
    \ ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n    constexpr ModInt\
    \ operator-() const { return ModInt()._setval(md - val_); }\n    constexpr ModInt\
    \ &operator+=(const ModInt &x) { return *this = *this + x; }\n    constexpr ModInt\
    \ &operator-=(const ModInt &x) { return *this = *this - x; }\n    constexpr ModInt\
    \ &operator*=(const ModInt &x) { return *this = *this * x; }\n    constexpr ModInt\
    \ &operator/=(const ModInt &x) { return *this = *this / x; }\n    friend constexpr\
    \ ModInt operator+(lint a, const ModInt &x) { return ModInt(a) + x; }\n    friend\
    \ constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt(a) - x;\
    \ }\n    friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt(a)\
    \ * x; }\n    friend constexpr ModInt operator/(lint a, const ModInt &x) { return\
    \ ModInt(a) / x; }\n    constexpr bool operator==(const ModInt &x) const { return\
    \ val_ == x.val_; }\n    constexpr bool operator!=(const ModInt &x) const { return\
    \ val_ != x.val_; }\n    constexpr bool operator<(const ModInt &x) const {\n \
    \       return val_ < x.val_;\n    } // To use std::map<ModInt, T>\n    friend\
    \ std::istream &operator>>(std::istream &is, ModInt &x) {\n        lint t;\n \
    \       return is >> t, x = ModInt(t), is;\n    }\n    constexpr friend std::ostream\
    \ &operator<<(std::ostream &os, const ModInt &x) {\n        return os << x.val_;\n\
    \    }\n\n    constexpr ModInt pow(lint n) const {\n        ModInt ans = 1, tmp\
    \ = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n        \
    \    tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n    static\
    \ constexpr int cache_limit = std::min(md, 1 << 21);\n    static std::vector<ModInt>\
    \ facs, facinvs, invs;\n\n    constexpr static void _precalculation(int N) {\n\
    \        const int l0 = facs.size();\n        if (N > md) N = md;\n        if\
    \ (N <= l0) return;\n        facs.resize(N), facinvs.resize(N), invs.resize(N);\n\
    \        for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i;\n        facinvs[N\
    \ - 1] = facs.back().pow(md - 2);\n        for (int i = N - 2; i >= l0; i--) facinvs[i]\
    \ = facinvs[i + 1] * (i + 1);\n        for (int i = N - 1; i >= l0; i--) invs[i]\
    \ = facinvs[i] * facs[i - 1];\n    }\n\n    constexpr ModInt inv() const {\n \
    \       if (this->val_ < cache_limit) {\n            if (facs.empty()) facs =\
    \ {1}, facinvs = {1}, invs = {0};\n            while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n            return invs[this->val_];\n  \
    \      } else {\n            return this->pow(md - 2);\n        }\n    }\n\n \
    \   constexpr static ModInt fac(int n) {\n        assert(n >= 0);\n        if\
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
    \ b, false);\n}\n#line 5 \"convolution/test/convolution_on_tree.test.cpp\"\n\n\
    #line 7 \"convolution/test/convolution_on_tree.test.cpp\"\nusing namespace std;\n\
    using mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N;\n    long long K;\n    cin >> N >> K;\n    vector<mint> A(N + 1);\n\
    \    vector<int> par(N);\n    for (auto &x : A) cin >> x;\n    for (auto &p :\
    \ par) cin >> p;\n    par.insert(par.begin(), -1);\n\n    vector<mint> trans(N\
    \ + 1);\n    mint tmp = 1;\n    for (int i = 0; i < int(trans.size()); ++i) {\n\
    \        trans[i] = tmp;\n        tmp = tmp * (mint(K) - i) / (i + 1);\n    }\n\
    \    while (trans.size() and trans.back() == mint()) trans.pop_back();\n\n   \
    \ auto convolve = [&](vector<mint> &l, vector<mint> &r) { return nttconv(l, r);\
    \ };\n\n    for (auto x : ConvolutionOnTree(par).run(A, trans, convolve)) cout\
    \ << x << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2004\"\n#include \"../convolution_on_tree.hpp\"\
    \n#include \"../../modint.hpp\"\n#include \"../ntt.hpp\"\n\n#include <iostream>\n\
    using namespace std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N;\n    long long K;\n    cin >> N >>\
    \ K;\n    vector<mint> A(N + 1);\n    vector<int> par(N);\n    for (auto &x :\
    \ A) cin >> x;\n    for (auto &p : par) cin >> p;\n    par.insert(par.begin(),\
    \ -1);\n\n    vector<mint> trans(N + 1);\n    mint tmp = 1;\n    for (int i =\
    \ 0; i < int(trans.size()); ++i) {\n        trans[i] = tmp;\n        tmp = tmp\
    \ * (mint(K) - i) / (i + 1);\n    }\n    while (trans.size() and trans.back()\
    \ == mint()) trans.pop_back();\n\n    auto convolve = [&](vector<mint> &l, vector<mint>\
    \ &r) { return nttconv(l, r); };\n\n    for (auto x : ConvolutionOnTree(par).run(A,\
    \ trans, convolve)) cout << x << '\\n';\n}\n"
  dependsOn:
  - convolution/convolution_on_tree.hpp
  - modint.hpp
  - convolution/ntt.hpp
  isVerificationFile: true
  path: convolution/test/convolution_on_tree.test.cpp
  requiredBy: []
  timestamp: '2025-08-25 00:44:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: convolution/test/convolution_on_tree.test.cpp
layout: document
redirect_from:
- /verify/convolution/test/convolution_on_tree.test.cpp
- /verify/convolution/test/convolution_on_tree.test.cpp.html
title: convolution/test/convolution_on_tree.test.cpp
---
