---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: number/modint_runtime.hpp
    title: number/modint_runtime.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod_1000000007
    links:
    - https://judge.yosupo.jp/problem/convolution_mod_1000000007
  bundledCode: "#line 1 \"convolution/test/ntt_arbitrary_mod.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\n#line 2 \"modint.hpp\"\
    \n#include <iostream>\n#include <set>\n#include <vector>\n\n// CUT begin\ntemplate\
    \ <int md> struct ModInt {\n#if __cplusplus >= 201402L\n#define MDCONST constexpr\n\
    #else\n#define MDCONST\n#endif\n    using lint = long long;\n    MDCONST static\
    \ int mod() { return md; }\n    static int get_primitive_root() {\n        static\
    \ int primitive_root = 0;\n        if (!primitive_root) {\n            primitive_root\
    \ = [&]() {\n                std::set<int> fac;\n                int v = md -\
    \ 1;\n                for (lint i = 2; i * i <= v; i++)\n                    while\
    \ (v % i == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n\
    \                for (int g = 1; g < md; g++) {\n                    bool ok =\
    \ true;\n                    for (auto i : fac)\n                        if (ModInt(g).pow((md\
    \ - 1) / i) == 1) {\n                            ok = false;\n               \
    \             break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root;\n    }\n    int val;\n    MDCONST ModInt()\
    \ : val(0) {}\n    MDCONST ModInt &_setval(lint v) { return val = (v >= md ? v\
    \ - md : v), *this; }\n    MDCONST ModInt(lint v) { _setval(v % md + md); }\n\
    \    MDCONST explicit operator bool() const { return val != 0; }\n    MDCONST\
    \ ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ + x.val); }\n    MDCONST ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
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
    \ return a;\n}\n\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(const\
    \ std::vector<MODINT> &a, const std::vector<MODINT> &b) {\n    return nttconv<MODINT>(a,\
    \ b, false);\n}\n#line 5 \"number/modint_runtime.hpp\"\n\n// CUT begin\nstruct\
    \ ModIntRuntime {\nprivate:\n    static int md;\n\npublic:\n    using lint = long\
    \ long;\n    static int mod() { return md; }\n    int val;\n    static std::vector<ModIntRuntime>\
    \ &facs() {\n        static std::vector<ModIntRuntime> facs_;\n        return\
    \ facs_;\n    }\n    static int &get_primitive_root() {\n        static int primitive_root_\
    \ = 0;\n        if (!primitive_root_) {\n            primitive_root_ = [&]() {\n\
    \                std::set<int> fac;\n                int v = md - 1;\n       \
    \         for (lint i = 2; i * i <= v; i++)\n                    while (v % i\
    \ == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n  \
    \              for (int g = 1; g < md; g++) {\n                    bool ok = true;\n\
    \                    for (auto i : fac)\n                        if (ModIntRuntime(g).power((md\
    \ - 1) / i) == 1) {\n                            ok = false;\n               \
    \             break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root_;\n    }\n    static void set_mod(const int\
    \ &m) {\n        if (md != m) facs().clear();\n        md = m;\n        get_primitive_root()\
    \ = 0;\n    }\n    ModIntRuntime &_setval(lint v) {\n        val = (v >= md ?\
    \ v - md : v);\n        return *this;\n    }\n    ModIntRuntime() : val(0) {}\n\
    \    ModIntRuntime(lint v) { _setval(v % md + md); }\n    explicit operator bool()\
    \ const { return val != 0; }\n    ModIntRuntime operator+(const ModIntRuntime\
    \ &x) const {\n        return ModIntRuntime()._setval((lint)val + x.val);\n  \
    \  }\n    ModIntRuntime operator-(const ModIntRuntime &x) const {\n        return\
    \ ModIntRuntime()._setval((lint)val - x.val + md);\n    }\n    ModIntRuntime operator*(const\
    \ ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val\
    \ * x.val % md);\n    }\n    ModIntRuntime operator/(const ModIntRuntime &x) const\
    \ {\n        return ModIntRuntime()._setval((lint)val * x.inv() % md);\n    }\n\
    \    ModIntRuntime operator-() const { return ModIntRuntime()._setval(md - val);\
    \ }\n    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this = *this\
    \ + x; }\n    ModIntRuntime &operator-=(const ModIntRuntime &x) { return *this\
    \ = *this - x; }\n    ModIntRuntime &operator*=(const ModIntRuntime &x) { return\
    \ *this = *this * x; }\n    ModIntRuntime &operator/=(const ModIntRuntime &x)\
    \ { return *this = *this / x; }\n    friend ModIntRuntime operator+(lint a, const\
    \ ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md + x.val);\n\
    \    }\n    friend ModIntRuntime operator-(lint a, const ModIntRuntime &x) {\n\
    \        return ModIntRuntime()._setval(a % md - x.val + md);\n    }\n    friend\
    \ ModIntRuntime operator*(lint a, const ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a\
    \ % md * x.val % md);\n    }\n    friend ModIntRuntime operator/(lint a, const\
    \ ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md * x.inv()\
    \ % md);\n    }\n    bool operator==(const ModIntRuntime &x) const { return val\
    \ == x.val; }\n    bool operator!=(const ModIntRuntime &x) const { return val\
    \ != x.val; }\n    bool operator<(const ModIntRuntime &x) const { return val <\
    \ x.val; } // To use std::map<ModIntRuntime, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModIntRuntime &x) {\n        lint t;\n        return is >> t, x = ModIntRuntime(t),\
    \ is;\n    }\n    friend std::ostream &operator<<(std::ostream &os, const ModIntRuntime\
    \ &x) { return os << x.val; }\n\n    lint power(lint n) const {\n        lint\
    \ ans = 1, tmp = this->val;\n        while (n) {\n            if (n & 1) ans =\
    \ ans * tmp % md;\n            tmp = tmp * tmp % md;\n            n /= 2;\n  \
    \      }\n        return ans;\n    }\n    ModIntRuntime pow(lint n) const { return\
    \ power(n); }\n    lint inv() const { return this->power(md - 2); }\n\n    ModIntRuntime\
    \ fac() const {\n        int l0 = facs().size();\n        if (l0 > this->val)\
    \ return facs()[this->val];\n\n        facs().resize(this->val + 1);\n       \
    \ for (int i = l0; i <= this->val; i++)\n            facs()[i] = (i == 0 ? ModIntRuntime(1)\
    \ : facs()[i - 1] * ModIntRuntime(i));\n        return facs()[this->val];\n  \
    \  }\n\n    ModIntRuntime doublefac() const {\n        lint k = (this->val + 1)\
    \ / 2;\n        return (this->val & 1) ? ModIntRuntime(k * 2).fac() / (ModIntRuntime(2).pow(k)\
    \ * ModIntRuntime(k).fac())\n                               : ModIntRuntime(k).fac()\
    \ * ModIntRuntime(2).pow(k);\n    }\n\n    ModIntRuntime nCr(const ModIntRuntime\
    \ &r) const {\n        return (this->val < r.val) ? ModIntRuntime(0) : this->fac()\
    \ / ((*this - r).fac() * r.fac());\n    }\n\n    ModIntRuntime sqrt() const {\n\
    \        if (val == 0) return 0;\n        if (md == 2) return val;\n        if\
    \ (power((md - 1) / 2) != 1) return 0;\n        ModIntRuntime b = 1;\n       \
    \ while (b.power((md - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n\
    \        while (m % 2 == 0) m >>= 1, e++;\n        ModIntRuntime x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModIntRuntime\
    \ z = b.power(m);\n        while (y != 1) {\n            int j = 0;\n        \
    \    ModIntRuntime t = y;\n            while (t != 1) j++, t *= t;\n         \
    \   z = z.power(1LL << (e - j - 1));\n            x *= z, z *= z, y *= z;\n  \
    \          e = j;\n        }\n        return ModIntRuntime(std::min(x.val, md\
    \ - x.val));\n    }\n};\nint ModIntRuntime::md = 1;\n#line 6 \"convolution/test/ntt_arbitrary_mod.test.cpp\"\
    \nusing namespace std;\n\nconstexpr int MOD = 1000000007;\nusing mint = ModInt<MOD>;\n\
    using mintr = ModIntRuntime;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    mintr::set_mod(MOD);\n    int N, M;\n    cin >> N >> M;\n    vector<mint>\
    \ A(N), B(M);\n    vector<mintr> Ar(N), Br(M);\n    for (int i = 0; i < N; i++)\
    \ cin >> A[i], Ar[i] = A[i].val;\n    for (int i = 0; i < M; i++) cin >> B[i],\
    \ Br[i] = B[i].val;\n\n    vector<mint> ret = nttconv(A, B);\n    vector<mintr>\
    \ retr = nttconv(Ar, Br);\n\n    for (int i = 0; i < N + M - 1; i++) {\n     \
    \   assert(ret[i].val == retr[i].val);\n        cout << ret[i].val << ' ';\n \
    \   }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\
    \n#include \"convolution/ntt.hpp\"\n#include \"modint.hpp\"\n#include \"number/modint_runtime.hpp\"\
    \n#include <iostream>\nusing namespace std;\n\nconstexpr int MOD = 1000000007;\n\
    using mint = ModInt<MOD>;\nusing mintr = ModIntRuntime;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    mintr::set_mod(MOD);\n    int N, M;\n  \
    \  cin >> N >> M;\n    vector<mint> A(N), B(M);\n    vector<mintr> Ar(N), Br(M);\n\
    \    for (int i = 0; i < N; i++) cin >> A[i], Ar[i] = A[i].val;\n    for (int\
    \ i = 0; i < M; i++) cin >> B[i], Br[i] = B[i].val;\n\n    vector<mint> ret =\
    \ nttconv(A, B);\n    vector<mintr> retr = nttconv(Ar, Br);\n\n    for (int i\
    \ = 0; i < N + M - 1; i++) {\n        assert(ret[i].val == retr[i].val);\n   \
    \     cout << ret[i].val << ' ';\n    }\n}\n"
  dependsOn:
  - convolution/ntt.hpp
  - modint.hpp
  - number/modint_runtime.hpp
  isVerificationFile: true
  path: convolution/test/ntt_arbitrary_mod.test.cpp
  requiredBy: []
  timestamp: '2021-09-04 00:38:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: convolution/test/ntt_arbitrary_mod.test.cpp
layout: document
redirect_from:
- /verify/convolution/test/ntt_arbitrary_mod.test.cpp
- /verify/convolution/test/ntt_arbitrary_mod.test.cpp.html
title: convolution/test/ntt_arbitrary_mod.test.cpp
---
