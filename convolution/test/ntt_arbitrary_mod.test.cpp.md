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
    path: number/modint_runtime.hpp
    title: number/modint_runtime.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod_1000000007
    links:
    - https://judge.yosupo.jp/problem/convolution_mod_1000000007
  bundledCode: "#line 1 \"convolution/test/ntt_arbitrary_mod.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\n#line 2 \"modint.hpp\"\
    \n#include <iostream>\n#include <vector>\n#include <set>\n\n// CUT begin\ntemplate\
    \ <int mod>\nstruct ModInt\n{\n    using lint = long long;\n    static int get_mod()\
    \ { return mod; }\n    static int get_primitive_root() {\n        static int primitive_root\
    \ = 0;\n        if (!primitive_root) {\n            primitive_root = [&](){\n\
    \                std::set<int> fac;\n                int v = mod - 1;\n      \
    \          for (lint i = 2; i * i <= v; i++) while (v % i == 0) fac.insert(i),\
    \ v /= i;\n                if (v > 1) fac.insert(v);\n                for (int\
    \ g = 1; g < mod; g++) {\n                    bool ok = true;\n              \
    \      for (auto i : fac) if (ModInt(g).power((mod - 1) / i) == 1) { ok = false;\
    \ break; }\n                    if (ok) return g;\n                }\n       \
    \         return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val;\n    constexpr ModInt() : val(0) {}\n    constexpr ModInt\
    \ &_setval(lint v) { val = (v >= mod ? v - mod : v); return *this; }\n    constexpr\
    \ ModInt(lint v) { _setval(v % mod + mod); }\n    explicit operator bool() const\
    \ { return val != 0; }\n    constexpr ModInt operator+(const ModInt &x) const\
    \ { return ModInt()._setval((lint)val + x.val); }\n    constexpr ModInt operator-(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val - x.val + mod); }\n   \
    \ constexpr ModInt operator*(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ * x.val % mod); }\n    constexpr ModInt operator/(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.inv() % mod); }\n    constexpr ModInt operator-()\
    \ const { return ModInt()._setval(mod - val); }\n    constexpr ModInt &operator+=(const\
    \ ModInt &x) { return *this = *this + x; }\n    constexpr ModInt &operator-=(const\
    \ ModInt &x) { return *this = *this - x; }\n    constexpr ModInt &operator*=(const\
    \ ModInt &x) { return *this = *this * x; }\n    constexpr ModInt &operator/=(const\
    \ ModInt &x) { return *this = *this / x; }\n    friend constexpr ModInt operator+(lint\
    \ a, const ModInt &x) { return ModInt()._setval(a % mod + x.val); }\n    friend\
    \ constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod - x.val + mod); }\n    friend constexpr ModInt operator*(lint a, const\
    \ ModInt &x) { return ModInt()._setval(a % mod * x.val % mod); }\n    friend constexpr\
    \ ModInt operator/(lint a, const ModInt &x) { return ModInt()._setval(a % mod\
    \ * x.inv() % mod); }\n    constexpr bool operator==(const ModInt &x) const {\
    \ return val == x.val; }\n    constexpr bool operator!=(const ModInt &x) const\
    \ { return val != x.val; }\n    bool operator<(const ModInt &x) const { return\
    \ val < x.val; }  // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) { lint t; is >> t; x = ModInt(t); return is; }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const ModInt &x) { os << x.val;  return os; }\n\
    \    constexpr lint power(lint n) const {\n        lint ans = 1, tmp = this->val;\n\
    \        while (n) {\n            if (n & 1) ans = ans * tmp % mod;\n        \
    \    tmp = tmp * tmp % mod;\n            n /= 2;\n        }\n        return ans;\n\
    \    }\n    constexpr ModInt pow(lint n) const {\n        return power(n);\n \
    \   }\n    constexpr lint inv() const { return this->power(mod - 2); }\n    constexpr\
    \ ModInt operator^(lint n) const { return ModInt(this->power(n)); }\n    constexpr\
    \ ModInt &operator^=(lint n) { return *this = *this ^ n; }\n\n    inline ModInt\
    \ fac() const {\n        static std::vector<ModInt> facs;\n        int l0 = facs.size();\n\
    \        if (l0 > this->val) return facs[this->val];\n\n        facs.resize(this->val\
    \ + 1);\n        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1)\
    \ : facs[i - 1] * ModInt(i));\n        return facs[this->val];\n    }\n\n    ModInt\
    \ doublefac() const {\n        lint k = (this->val + 1) / 2;\n        if (this->val\
    \ & 1) return ModInt(k * 2).fac() / ModInt(2).power(k) / ModInt(k).fac();\n  \
    \      else return ModInt(k).fac() * ModInt(2).power(k);\n    }\n\n    ModInt\
    \ nCr(const ModInt &r) const {\n        if (this->val < r.val) return ModInt(0);\n\
    \        return this->fac() / ((*this - r).fac() * r.fac());\n    }\n\n    ModInt\
    \ sqrt() const {\n        if (val == 0) return 0;\n        if (mod == 2) return\
    \ val;\n        if (power((mod - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n\
    \        while (b.power((mod - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod\
    \ - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.power(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.power(1LL << (e -\
    \ j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val, mod - x.val));\n    }\n};\n// using mint\
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
    // ** Input size must be 2^n **\ntemplate <typename MODINT>\nvoid ntt(std::vector<MODINT>\
    \ &a, bool is_inverse = false)\n{\n    int n = a.size();\n    if (n == 1) return;\n\
    \    static const int mod = MODINT::get_mod();\n    static const MODINT root =\
    \ MODINT::get_primitive_root();\n    assert(__builtin_popcount(n) == 1 and (mod\
    \ - 1) % n == 0);\n\n    static std::vector<MODINT> w{1}, iw{1};\n    for (int\
    \ m = w.size(); m < n / 2; m *= 2) {\n        MODINT dw = root.power((mod - 1)\
    \ / (4 * m)), dwinv = 1 / dw;\n        w.resize(m * 2), iw.resize(m * 2);\n  \
    \      for (int i = 0; i < m; i++) w[m + i] = w[i] * dw, iw[m + i] = iw[i] * dwinv;\n\
    \    }\n\n    if (!is_inverse) {\n        for (int m = n; m >>= 1;) {\n      \
    \      for (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n                for (int\
    \ i = s; i < s + m; i++) {\n                    MODINT x = a[i], y = a[i + m]\
    \ * w[k];\n                    a[i] = x + y, a[i + m] = x - y;\n             \
    \   }\n            }\n        }\n    }\n    else {\n        for (int m = 1; m\
    \ < n; m *= 2) {\n            for (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n\
    \                for (int i = s; i < s + m; i++) {\n                    MODINT\
    \ x = a[i], y = a[i + m];\n                    a[i] = x + y, a[i + m] = (x - y)\
    \ * iw[k];\n                }\n            }\n        }\n        int n_inv = MODINT(n).inv();\n\
    \        for (auto &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
    \ nttconv_(const std::vector<int> &a, const std::vector<int> &b) {\n    int sz\
    \ = a.size();\n    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n\
    \    std::vector<ModInt<MOD>> ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++)\
    \ ap[i] = a[i], bp[i] = b[i];\n    ntt(ap, false);\n    if (a == b) bp = ap;\n\
    \    else ntt(bp, false);\n    for (int i = 0; i < sz; i++) ap[i] *= bp[i];\n\
    \    ntt(ap, true);\n    return ap;\n}\nlong long garner_ntt_(int r0, int r1,\
    \ int r2, int mod)\n{\n    using mint2 = ModInt<nttprimes[2]>;\n    static const\
    \ long long m01 = 1LL * nttprimes[0] * nttprimes[1];\n    static const long long\
    \ m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv();\n    static const long\
    \ long m01_inv_m2 = mint2(m01).inv();\n\n    int v1 = (m0_inv_m1 * (r1 + nttprimes[1]\
    \ - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2) - r0 - mint2(nttprimes[0])\
    \ * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0] * v1 + m01 % mod *\
    \ v2.val) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT>\
    \ a, std::vector<MODINT> b, bool skip_garner)\n{\n    int sz = 1, n = a.size(),\
    \ m = b.size();\n    while (sz < n + m) sz <<= 1;\n    if (sz <= 16) {\n     \
    \   std::vector<MODINT> ret(n + m - 1);\n        for (int i = 0; i < n; i++) {\n\
    \            for (int j = 0; j < m; j++) ret[i + j] += a[i] * b[j];\n        }\n\
    \        return ret;\n    }\n    int mod = MODINT::get_mod();\n    if (skip_garner\
    \ or std::find(std::begin(nttprimes), std::end(nttprimes), mod) != std::end(nttprimes))\n\
    \    {\n        a.resize(sz), b.resize(sz);\n        if (a == b) { ntt(a, false);\
    \ b = a; }\n        else ntt(a, false), ntt(b, false);\n        for (int i = 0;\
    \ i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n + m -\
    \ 1);\n    }\n    else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val;\n        for (int i = 0; i < m; i++)\
    \ bi[i] = b[i].val;\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n   \
    \     auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\
    \ {\n            a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);\n\
    \        }\n    }\n    return a;\n}\n#line 5 \"number/modint_runtime.hpp\"\n\n\
    // CUT begin\nstruct ModIntRuntime\n{\n    using lint = long long int;\n    static\
    \ int get_mod() { return mod; }\n    int val;\n    static int mod;\n    static\
    \ std::vector<ModIntRuntime> &facs()\n    {\n        static std::vector<ModIntRuntime>\
    \ facs_;\n        return facs_;\n    }\n    static int &get_primitive_root() {\n\
    \        static int primitive_root_ = 0;\n        if (!primitive_root_) {\n  \
    \          primitive_root_ = [&](){\n                std::set<int> fac;\n    \
    \            int v = mod - 1;\n                for (lint i = 2; i * i <= v; i++)\
    \ while (v % i == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n\
    \                for (int g = 1; g < mod; g++) {\n                    bool ok\
    \ = true;\n                    for (auto i : fac) if (ModIntRuntime(g).power((mod\
    \ - 1) / i) == 1) { ok = false; break; }\n                    if (ok) return g;\n\
    \                }\n                return -1;\n            }();\n        }\n\
    \        return primitive_root_;\n    }\n    static void set_mod(const int &m)\
    \ {\n        if (mod != m) facs().clear();\n        mod = m;\n        get_primitive_root()\
    \ = 0;\n    }\n    ModIntRuntime &_setval(lint v) { val = (v >= mod ? v - mod\
    \ : v); return *this; }\n    ModIntRuntime() : val(0) {}\n    ModIntRuntime(lint\
    \ v) { _setval(v % mod + mod); }\n    explicit operator bool() const { return\
    \ val != 0; }\n    ModIntRuntime operator+(const ModIntRuntime &x) const { return\
    \ ModIntRuntime()._setval((lint)val + x.val); }\n    ModIntRuntime operator-(const\
    \ ModIntRuntime &x) const { return ModIntRuntime()._setval((lint)val - x.val +\
    \ mod); }\n    ModIntRuntime operator*(const ModIntRuntime &x) const { return\
    \ ModIntRuntime()._setval((lint)val * x.val % mod); }\n    ModIntRuntime operator/(const\
    \ ModIntRuntime &x) const { return ModIntRuntime()._setval((lint)val * x.inv()\
    \ % mod); }\n    ModIntRuntime operator-() const { return ModIntRuntime()._setval(mod\
    \ - val); }\n    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this\
    \ = *this + x; }\n    ModIntRuntime &operator-=(const ModIntRuntime &x) { return\
    \ *this = *this - x; }\n    ModIntRuntime &operator*=(const ModIntRuntime &x)\
    \ { return *this = *this * x; }\n    ModIntRuntime &operator/=(const ModIntRuntime\
    \ &x) { return *this = *this / x; }\n    friend ModIntRuntime operator+(lint a,\
    \ const ModIntRuntime &x) { return ModIntRuntime()._setval(a % mod + x.val); }\n\
    \    friend ModIntRuntime operator-(lint a, const ModIntRuntime &x) { return ModIntRuntime()._setval(a\
    \ % mod - x.val + mod); }\n    friend ModIntRuntime operator*(lint a, const ModIntRuntime\
    \ &x) { return ModIntRuntime()._setval(a % mod * x.val % mod); }\n    friend ModIntRuntime\
    \ operator/(lint a, const ModIntRuntime &x) { return ModIntRuntime()._setval(a\
    \ % mod * x.inv() % mod); }\n    bool operator==(const ModIntRuntime &x) const\
    \ { return val == x.val; }\n    bool operator!=(const ModIntRuntime &x) const\
    \ { return val != x.val; }\n    bool operator<(const ModIntRuntime &x) const {\
    \ return val < x.val; }  // To use std::map<ModIntRuntime, T>\n    friend std::istream\
    \ &operator>>(std::istream &is, ModIntRuntime &x) { lint t; is >> t; x = ModIntRuntime(t);\
    \ return is; }\n    friend std::ostream &operator<<(std::ostream &os, const ModIntRuntime\
    \ &x) { os << x.val;  return os; }\n \n    lint power(lint n) const {\n      \
    \  lint ans = 1, tmp = this->val;\n        while (n) {\n            if (n & 1)\
    \ ans = ans * tmp % mod;\n            tmp = tmp * tmp % mod;\n            n /=\
    \ 2;\n        }\n        return ans;\n    }\n    ModIntRuntime pow(lint n) const\
    \ {\n        return power(n);\n    }\n    lint inv() const { return this->power(mod\
    \ - 2); }\n    ModIntRuntime operator^(lint n) const { return ModIntRuntime(this->power(n));\
    \ }\n    ModIntRuntime &operator^=(lint n) { return *this = *this ^ n; }\n \n\
    \    ModIntRuntime fac() const {\n        int l0 = facs().size();\n        if\
    \ (l0 > this->val) return facs()[this->val];\n \n        facs().resize(this->val\
    \ + 1);\n        for (int i = l0; i <= this->val; i++) facs()[i] = (i == 0 ? ModIntRuntime(1)\
    \ : facs()[i - 1] * ModIntRuntime(i));\n        return facs()[this->val];\n  \
    \  }\n \n    ModIntRuntime doublefac() const {\n        lint k = (this->val +\
    \ 1) / 2;\n        if (this->val & 1) return ModIntRuntime(k * 2).fac() / ModIntRuntime(2).power(k)\
    \ / ModIntRuntime(k).fac();\n        else return ModIntRuntime(k).fac() * ModIntRuntime(2).power(k);\n\
    \    }\n \n    ModIntRuntime nCr(const ModIntRuntime &r) const {\n        if (this->val\
    \ < r.val) return ModIntRuntime(0);\n        return this->fac() / ((*this - r).fac()\
    \ * r.fac());\n    }\n\n    ModIntRuntime sqrt() const {\n        if (val == 0)\
    \ return 0;\n        if (mod == 2) return val;\n        if (power((mod - 1) /\
    \ 2) != 1) return 0;\n        ModIntRuntime b = 1;\n        while (b.power((mod\
    \ - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod - 1;\n        while (m %\
    \ 2 == 0) m >>= 1, e++;\n        ModIntRuntime x = power((m - 1) / 2), y = (*this)\
    \ * x * x;\n        x *= (*this);\n        ModIntRuntime z = b.power(m);\n   \
    \     while (y != 1) {\n            int j = 0;\n            ModIntRuntime t =\
    \ y;\n            while (t != 1) j++, t *= t;\n            z = z.power(1LL <<\
    \ (e - j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n   \
    \     }\n        return ModIntRuntime(std::min(x.val, mod - x.val));\n    }\n\
    };\nint ModIntRuntime::mod = 1;\n#line 6 \"convolution/test/ntt_arbitrary_mod.test.cpp\"\
    \nusing namespace std;\n\nconstexpr int MOD = 1000000007;\nusing mint = ModInt<MOD>;\n\
    using mintr = ModIntRuntime;\n\nint main()\n{\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
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
    using mint = ModInt<MOD>;\nusing mintr = ModIntRuntime;\n\nint main()\n{\n   \
    \ cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    mintr::set_mod(MOD);\n\
    \    int N, M;\n    cin >> N >> M;\n    vector<mint> A(N), B(M);\n    vector<mintr>\
    \ Ar(N), Br(M);\n    for (int i = 0; i < N; i++) cin >> A[i], Ar[i] = A[i].val;\n\
    \    for (int i = 0; i < M; i++) cin >> B[i], Br[i] = B[i].val;\n\n    vector<mint>\
    \ ret = nttconv(A, B);\n    vector<mintr> retr = nttconv(Ar, Br);\n\n    for (int\
    \ i = 0; i < N + M - 1; i++) {\n        assert(ret[i].val == retr[i].val);\n \
    \       cout << ret[i].val << ' ';\n    }\n}\n"
  dependsOn:
  - convolution/ntt.hpp
  - modint.hpp
  - number/modint_runtime.hpp
  isVerificationFile: true
  path: convolution/test/ntt_arbitrary_mod.test.cpp
  requiredBy: []
  timestamp: '2020-11-15 14:30:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: convolution/test/ntt_arbitrary_mod.test.cpp
layout: document
redirect_from:
- /verify/convolution/test/ntt_arbitrary_mod.test.cpp
- /verify/convolution/test/ntt_arbitrary_mod.test.cpp.html
title: convolution/test/ntt_arbitrary_mod.test.cpp
---
