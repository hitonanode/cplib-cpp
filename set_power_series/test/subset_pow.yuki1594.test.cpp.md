---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: set_power_series/subset_convolution.hpp
    title: "Subset convolution \uFF08\u96C6\u5408\u95A2\u6570\u306E\u5404\u7A2E\u6F14\
      \u7B97\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1594
    links:
    - https://yukicoder.me/problems/no/1594
  bundledCode: "#line 1 \"set_power_series/test/subset_pow.yuki1594.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/1594\"\n#line 2 \"modint.hpp\"\n\
    #include <cassert>\n#include <iostream>\n#include <set>\n#include <vector>\n\n\
    template <int md> struct ModInt {\n    static_assert(md > 1);\n    using lint\
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
    \    }\n\n    static ModInt binom(long long n, long long r) {\n        static\
    \ long long bruteforce_times = 0;\n\n        if (r < 0 or n < r) return ModInt(0);\n\
    \        if (n <= bruteforce_times or n < (int)facs.size()) return ModInt::nCr(n,\
    \ r);\n\n        r = std::min(r, n - r);\n        assert((int)r == r);\n\n   \
    \     ModInt ret = ModInt::facinv(r);\n        for (int i = 0; i < r; ++i) ret\
    \ *= n - i;\n        bruteforce_times += r;\n\n        return ret;\n    }\n\n\
    \    // Multinomial coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)\n\
    \    // Complexity: O(sum(ks))\n    // Verify: https://yukicoder.me/problems/no/3178\n\
    \    template <class Vec> static ModInt multinomial(const Vec &ks) {\n       \
    \ ModInt ret{1};\n        int sum = 0;\n        for (int k : ks) {\n         \
    \   assert(k >= 0);\n            ret *= ModInt::facinv(k), sum += k;\n       \
    \ }\n        return ret * ModInt::fac(sum);\n    }\n    template <class... Args>\
    \ static ModInt multinomial(Args... args) {\n        int sum = (0 + ... + args);\n\
    \        ModInt result = (1 * ... * ModInt::facinv(args));\n        return ModInt::fac(sum)\
    \ * result;\n    }\n\n    // Catalan number, C_n = binom(2n, n) / (n + 1) = #\
    \ of Dyck words of length 2n\n    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4 =\
    \ 14, ...\n    // https://oeis.org/A000108\n    // Complexity: O(n)\n    static\
    \ ModInt catalan(int n) {\n        if (n < 0) return ModInt(0);\n        return\
    \ ModInt::fac(n * 2) * ModInt::facinv(n + 1) * ModInt::facinv(n);\n    }\n\n \
    \   ModInt sqrt() const {\n        if (val_ == 0) return 0;\n        if (md ==\
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
    // using mint = ModInt<1000000007>;\n#line 2 \"set_power_series/subset_convolution.hpp\"\
    \n#include <algorithm>\n#line 5 \"set_power_series/subset_convolution.hpp\"\n\n\
    // CUT begin\n// Subset sum (fast zeta transform)\n// Complexity: O(N 2^N) for\
    \ array of size 2^N\ntemplate <typename T> void subset_sum(std::vector<T> &f)\
    \ {\n    const int sz = f.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    for (int d = 0; d < n; d++) {\n        for (int S = 0; S < 1 <<\
    \ n; S++)\n            if (S & (1 << d)) f[S] += f[S ^ (1 << d)];\n    }\n}\n\
    // Inverse of subset sum (fast moebius transform)\n// Complexity: O(N 2^N) for\
    \ array of size 2^N\ntemplate <typename T> void subset_sum_inv(std::vector<T>\
    \ &g) {\n    const int sz = g.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    for (int d = 0; d < n; d++) {\n        for (int S = 0; S < 1 <<\
    \ n; S++)\n            if (S & (1 << d)) g[S] -= g[S ^ (1 << d)];\n    }\n}\n\n\
    // Superset sum / its inverse (fast zeta/moebius transform)\n// Complexity: O(N\
    \ 2^N) for array of size 2^N\ntemplate <typename T> void superset_sum(std::vector<T>\
    \ &f) {\n    const int sz = f.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    for (int d = 0; d < n; d++) {\n        for (int S = 0; S < 1 <<\
    \ n; S++)\n            if (!(S & (1 << d))) f[S] += f[S | (1 << d)];\n    }\n\
    }\ntemplate <typename T> void superset_sum_inv(std::vector<T> &g) {\n    const\
    \ int sz = g.size(), n = __builtin_ctz(sz);\n    assert(__builtin_popcount(sz)\
    \ == 1);\n    for (int d = 0; d < n; d++) {\n        for (int S = 0; S < 1 <<\
    \ n; S++)\n            if (!(S & (1 << d))) g[S] -= g[S | (1 << d)];\n    }\n\
    }\n\ntemplate <typename T> std::vector<std::vector<T>> build_zeta_(int D, const\
    \ std::vector<T> &f) {\n    int n = f.size();\n    std::vector<std::vector<T>>\
    \ ret(D, std::vector<T>(n));\n    for (int i = 0; i < n; i++) ret[__builtin_popcount(i)][i]\
    \ += f[i];\n    for (auto &vec : ret) subset_sum(vec);\n    return ret;\n}\n\n\
    template <typename T>\nstd::vector<T> get_moebius_of_prod_(const std::vector<std::vector<T>>\
    \ &mat1,\n                                    const std::vector<std::vector<T>>\
    \ &mat2) {\n    int D = mat1.size(), n = mat1[0].size();\n    std::vector<std::vector<int>>\
    \ pc2i(D);\n    for (int i = 0; i < n; i++) pc2i[__builtin_popcount(i)].push_back(i);\n\
    \    std::vector<T> tmp, ret(mat1[0].size());\n    for (int d = 0; d < D; d++)\
    \ {\n        tmp.assign(mat1[d].size(), 0);\n        for (int e = 0; e <= d; e++)\
    \ {\n            for (int i = 0; i < int(tmp.size()); i++) tmp[i] += mat1[e][i]\
    \ * mat2[d - e][i];\n        }\n        subset_sum_inv(tmp);\n        for (auto\
    \ i : pc2i[d]) ret[i] = tmp[i];\n    }\n    return ret;\n};\n\n// Subset convolution\n\
    // h[S] = \\sum_T f[T] * g[S - T]\n// Complexity: O(N^2 2^N) for arrays of size\
    \ 2^N\ntemplate <typename T> std::vector<T> subset_convolution(std::vector<T>\
    \ f, std::vector<T> g) {\n    const int sz = f.size(), m = __builtin_ctz(sz) +\
    \ 1;\n    assert(__builtin_popcount(sz) == 1 and f.size() == g.size());\n    auto\
    \ ff = build_zeta_(m, f), fg = build_zeta_(m, g);\n    return get_moebius_of_prod_(ff,\
    \ fg);\n}\n\n// https://hos-lyric.hatenablog.com/entry/2021/01/14/201231\ntemplate\
    \ <class T, class Function> void subset_func(std::vector<T> &f, const Function\
    \ &func) {\n    const int sz = f.size(), m = __builtin_ctz(sz) + 1;\n    assert(__builtin_popcount(sz)\
    \ == 1);\n\n    auto ff = build_zeta_(m, f);\n\n    std::vector<T> p(m);\n   \
    \ for (int i = 0; i < sz; i++) {\n        for (int d = 0; d < m; d++) p[d] = ff[d][i];\n\
    \        func(p);\n        for (int d = 0; d < m; d++) ff[d][i] = p[d];\n    }\n\
    \n    for (auto &vec : ff) subset_sum_inv(vec);\n    for (int i = 0; i < sz; i++)\
    \ f[i] = ff[__builtin_popcount(i)][i];\n}\n\n// log(f(x)) for f(x), f(0) == 1\n\
    // Requires inv()\ntemplate <class T> void poly_log(std::vector<T> &f) {\n   \
    \ assert(f.at(0) == T(1));\n    static std::vector<T> invs{0};\n    const int\
    \ m = f.size();\n    std::vector<T> finv(m);\n    for (int d = 0; d < m; d++)\
    \ {\n        finv[d] = (d == 0);\n        if (int(invs.size()) <= d) invs.push_back(T(d).inv());\n\
    \        for (int e = 0; e < d; e++) finv[d] -= finv[e] * f[d - e];\n    }\n \
    \   std::vector<T> ret(m);\n    for (int d = 1; d < m; d++) {\n        for (int\
    \ e = 0; d + e < m; e++) ret[d + e] += f[d] * d * finv[e] * invs[d + e];\n   \
    \ }\n    f = ret;\n}\n\n// log(f(S)) for set function f(S), f(0) == 1\n// Requires\
    \ inv()\n// Complexity: O(n^2 2^n)\n// https://atcoder.jp/contests/abc213/tasks/abc213_g\n\
    template <class T> void subset_log(std::vector<T> &f) { subset_func(f, poly_log<T>);\
    \ }\n\n// exp(f(S)) for set function f(S), f(0) == 0\n// Complexity: O(n^2 2^n)\n\
    // https://codeforces.com/blog/entry/92183\ntemplate <class T> void subset_exp(std::vector<T>\
    \ &f) {\n    const int sz = f.size(), m = __builtin_ctz(sz);\n    assert(sz ==\
    \ 1 << m);\n    assert(f.at(0) == 0);\n    std::vector<T> ret{T(1)};\n    ret.reserve(sz);\n\
    \    for (int d = 0; d < m; d++) {\n        auto c = subset_convolution({f.begin()\
    \ + (1 << d), f.begin() + (1 << (d + 1))}, ret);\n        ret.insert(ret.end(),\
    \ c.begin(), c.end());\n    }\n    f = ret;\n}\n\n// sqrt(f(x)), f(x) == 1\n//\
    \ Requires inv of 2\n// Compelxity: O(n^2)\ntemplate <class T> void poly_sqrt(std::vector<T>\
    \ &f) {\n    assert(f.at(0) == T(1));\n    const int m = f.size();\n    static\
    \ const auto inv2 = T(2).inv();\n    for (int d = 1; d < m; d++) {\n        if\
    \ (~(d & 1)) f[d] -= f[d / 2] * f[d / 2];\n        f[d] *= inv2;\n        for\
    \ (int e = 1; e < d - e; e++) f[d] -= f[e] * f[d - e];\n    }\n}\n\n// sqrt(f(S))\
    \ for set function f(S), f(0) == 1\n// Requires inv()\n// https://atcoder.jp/contests/xmascon20/tasks/xmascon20_h\n\
    template <class T> void subset_sqrt(std::vector<T> &f) { subset_func(f, poly_sqrt<T>);\
    \ }\n\n// exp(f(S)) for set function f(S), f(0) == 0\ntemplate <class T> void\
    \ poly_exp(std::vector<T> &P) {\n    const int m = P.size();\n    assert(m and\
    \ P[0] == 0);\n    std::vector<T> Q(m), logQ(m), Qinv(m);\n    Q[0] = Qinv[0]\
    \ = T(1);\n    static std::vector<T> invs{0};\n\n    auto set_invlog = [&](int\
    \ d) {\n        Qinv[d] = 0;\n        for (int e = 0; e < d; e++) Qinv[d] -= Qinv[e]\
    \ * Q[d - e];\n        while (d >= int(invs.size())) {\n            int sz = invs.size();\n\
    \            invs.push_back(T(sz).inv());\n        }\n        logQ[d] = 0;\n \
    \       for (int e = 1; e <= d; e++) logQ[d] += Q[e] * e * Qinv[d - e];\n    \
    \    logQ[d] *= invs[d];\n    };\n    for (int d = 1; d < m; d++) {\n        Q[d]\
    \ += P[d] - logQ[d];\n        set_invlog(d);\n        assert(logQ[d] == P[d]);\n\
    \        if (d + 1 < m) set_invlog(d + 1);\n    }\n    P = Q;\n}\n\n// f(S)^k\
    \ for set function f(S)\n// Requires inv()\ntemplate <class T> void subset_pow(std::vector<T>\
    \ &f, long long k) {\n    auto poly_pow = [&](std::vector<T> &f) {\n        const\
    \ int m = f.size();\n        if (k == 0) f[0] = 1, std::fill(f.begin() + 1, f.end(),\
    \ T(0));\n        if (k <= 1) return;\n        int nzero = 0;\n        while (nzero\
    \ < int(f.size()) and f[nzero] == T(0)) nzero++;\n        int rem = std::max<long\
    \ long>((long long)f.size() - nzero * k, 0LL);\n        if (rem == 0) {\n    \
    \        std::fill(f.begin(), f.end(), 0);\n            return;\n        }\n \
    \       f.erase(f.begin(), f.begin() + nzero);\n        f.resize(rem);\n     \
    \   const T f0 = f.at(0), f0inv = f0.inv(), f0pow = f0.pow(k);\n        for (auto\
    \ &x : f) x *= f0inv;\n        poly_log(f);\n        for (auto &x : f) x *= k;\n\
    \        poly_exp(f);\n        for (auto &x : f) x *= f0pow;\n        f.resize(rem,\
    \ 0);\n        f.insert(f.begin(), m - int(f.size()), T(0));\n    };\n    subset_func(f,\
    \ poly_pow);\n}\n#line 5 \"set_power_series/test/subset_pow.yuki1594.test.cpp\"\
    \n#include <numeric>\n#line 7 \"set_power_series/test/subset_pow.yuki1594.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    int N;\n    cin >> N;\n    vector<int>\
    \ A(N);\n    for (auto &x : A) cin >> x;\n    int sum = accumulate(A.begin(),\
    \ A.end(), 0);\n    vector<ModInt<1000000007>> f(1 << N);\n    for (int S = 0;\
    \ S < 1 << N; S++) {\n        int tot = 0;\n        for (int d = 0; d < N; d++)\
    \ tot += A[d] * ((S >> d) & 1);\n        if (tot * 3 == sum) f[S] = 1;\n    }\n\
    \    subset_pow(f, 3);\n    cout << (f.back() ? \"Yes\" : \"No\") << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1594\"\n#include \"../../modint.hpp\"\
    \n#include \"../subset_convolution.hpp\"\n#include <iostream>\n#include <numeric>\n\
    #include <vector>\nusing namespace std;\n\nint main() {\n    int N;\n    cin >>\
    \ N;\n    vector<int> A(N);\n    for (auto &x : A) cin >> x;\n    int sum = accumulate(A.begin(),\
    \ A.end(), 0);\n    vector<ModInt<1000000007>> f(1 << N);\n    for (int S = 0;\
    \ S < 1 << N; S++) {\n        int tot = 0;\n        for (int d = 0; d < N; d++)\
    \ tot += A[d] * ((S >> d) & 1);\n        if (tot * 3 == sum) f[S] = 1;\n    }\n\
    \    subset_pow(f, 3);\n    cout << (f.back() ? \"Yes\" : \"No\") << '\\n';\n\
    }\n"
  dependsOn:
  - modint.hpp
  - set_power_series/subset_convolution.hpp
  isVerificationFile: true
  path: set_power_series/test/subset_pow.yuki1594.test.cpp
  requiredBy: []
  timestamp: '2025-09-11 21:33:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: set_power_series/test/subset_pow.yuki1594.test.cpp
layout: document
redirect_from:
- /verify/set_power_series/test/subset_pow.yuki1594.test.cpp
- /verify/set_power_series/test/subset_pow.yuki1594.test.cpp.html
title: set_power_series/test/subset_pow.yuki1594.test.cpp
---
