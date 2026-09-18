---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/sparse_fps.hpp
    title: "Sparse formal power series \uFF08\u758E\u306A\u5F62\u5F0F\u7684\u51AA\u7D1A\
      \u6570\u306E\u6F14\u7B97\uFF09"
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
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_of_formal_power_series_sparse
    links:
    - https://judge.yosupo.jp/problem/sqrt_of_formal_power_series_sparse
  bundledCode: "#line 1 \"formal_power_series/test/sparse_fps_sqrt.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/sqrt_of_formal_power_series_sparse\"\
    \n#line 2 \"formal_power_series/sparse_fps.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <concepts>\n#include <optional>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace sparse_fps {\n// https://github.com/yosupo06/library-checker-problems/issues/767#issuecomment-1166414020\n\
    \n// Calculate f(x)^k up to x^max_deg\ntemplate <typename Vec>\n    requires std::derived_from<Vec,\
    \ std::vector<typename Vec::value_type>>\nVec pow(const Vec &f, int max_deg, long\
    \ long k) {\n    using T = typename Vec::value_type;\n    assert(k >= 0);\n\n\
    \    Vec ret(max_deg + 1);\n\n    if (k == 0) {\n        ret[0] = T{1};\n    \
    \    return ret;\n    }\n\n    std::vector<std::pair<int, T>> terms;\n    int\
    \ d0 = 0;\n    while (d0 < int(f.size()) and d0 <= max_deg and f[d0] == T()) ++d0;\n\
    \    if (d0 == int(f.size()) or d0 > max_deg) return ret;\n\n    if (d0 and max_deg\
    \ / d0 < k) return ret;\n\n    for (int d = d0 + 1; d < std::min<int>(max_deg\
    \ + 1, f.size()); ++d) {\n        if (f[d] != T{}) terms.emplace_back(d - d0,\
    \ f[d]);\n    }\n\n    const int bias = d0 * k;\n    ret[bias] = f[d0].pow(k);\n\
    \    const T fd0inv = 1 / f[d0];\n    for (int d = 0; bias + d + 1 < int(ret.size());\
    \ ++d) {\n        // Compare [x^d](k f'g - fg')\n        T tmp{0};\n        for\
    \ (auto [i, fi] : terms) {\n            int j = d - i;\n            if (0 <= j)\
    \ tmp -= fi * ret[bias + j + 1] * (j + 1);\n            j = d - (i - 1);\n   \
    \         if (0 <= j) tmp += fi * i * ret[bias + j] * T(k);\n        }\n     \
    \   ret[bias + d + 1] = tmp * fd0inv / (d + 1);\n    }\n\n    return ret;\n}\n\
    \ntemplate <typename Vec>\n    requires std::derived_from<Vec, std::vector<typename\
    \ Vec::value_type>>\nVec inv(const Vec &f, int max_deg) {\n    using T = typename\
    \ Vec::value_type;\n    assert(!f.empty() and f[0] != T{0});\n\n    Vec ret(max_deg\
    \ + 1);\n\n    std::vector<std::pair<int, T>> terms;\n    for (int d = 1; d <\
    \ (int)f.size() and d <= max_deg; ++d) {\n        if (f[d] != T{}) terms.emplace_back(d,\
    \ f[d]);\n    }\n\n    const T f0inv = f[0].inv();\n    ret[0] = f0inv;\n\n  \
    \  for (int d = 1; d <= max_deg; ++d) {\n        T tmp{0};\n        for (auto\
    \ [i, fi] : terms) {\n            if (i > d) break;\n            tmp -= fi * ret[d\
    \ - i];\n        }\n        ret[d] = tmp * f0inv;\n    }\n\n    return ret;\n\
    }\n\ntemplate <typename Vec>\n    requires std::derived_from<Vec, std::vector<typename\
    \ Vec::value_type>>\nVec log(const Vec &f, int max_deg) {\n    using T = typename\
    \ Vec::value_type;\n    assert(!f.empty() and f[0] != T{0});\n\n    const auto\
    \ inv = sparse_fps::inv(f, max_deg);\n\n    std::vector<std::pair<int, T>> df_terms;\n\
    \    for (int d = 1; d < (int)f.size() and d <= max_deg; ++d) {\n        if (f[d]\
    \ != T{}) df_terms.emplace_back(d - 1, f[d] * T{d});\n    }\n\n    Vec ret(max_deg\
    \ + 1);\n\n    for (int d = 0; d < max_deg; ++d) {\n        for (auto [i, fi]\
    \ : df_terms) {\n            const int j = d + i + 1;\n            if (j > max_deg)\
    \ break;\n            ret[j] += inv[d] * fi * T{j}.inv();\n        }\n    }\n\n\
    \    return ret;\n}\n\ntemplate <typename Vec>\n    requires std::derived_from<Vec,\
    \ std::vector<typename Vec::value_type>>\nVec exp(const Vec &f, int max_deg) {\n\
    \    using T = typename Vec::value_type;\n    assert(f.empty() or f[0] == T{0});\n\
    \n    std::vector<std::pair<int, T>> df_terms;\n    for (int d = 1; d < (int)f.size()\
    \ and d <= max_deg; ++d) {\n        if (f[d] != T{}) df_terms.emplace_back(d -\
    \ 1, f[d] * T{d});\n    }\n\n    Vec ret(max_deg + 1);\n    ret[0] = T{1};\n \
    \   // F' = F * f'\n    for (int d = 1; d <= max_deg; ++d) {\n        T tmp{0};\n\
    \        for (auto [i, dfi] : df_terms) {\n            if (i > d - 1) break;\n\
    \            tmp += dfi * ret[d - 1 - i];\n        }\n        ret[d] = tmp * T{d}.inv();\n\
    \    }\n\n    return ret;\n}\n\ntemplate <typename Vec>\n    requires std::derived_from<Vec,\
    \ std::vector<typename Vec::value_type>>\nstd::optional<Vec> sqrt(const Vec &f,\
    \ int max_deg) {\n    using T = typename Vec::value_type;\n\n    Vec ret(max_deg\
    \ + 1);\n\n    int d0 = 0;\n    while (d0 < int(f.size()) and d0 <= max_deg and\
    \ f[d0] == T{}) ++d0;\n    if (d0 == int(f.size()) or d0 > max_deg) return ret;\n\
    \    if (d0 & 1) return std::nullopt;\n\n    const T sqrtf0 = f[d0].sqrt();\n\
    \    if (sqrtf0 == T{}) return std::nullopt;\n\n    std::vector<std::pair<int,\
    \ T>> terms;\n    const T fd0inv = 1 / f[d0];\n    for (int d = d0 + 1; d < std::min<int>(max_deg\
    \ + 1, f.size()); ++d) {\n        if (f[d] != T{}) terms.emplace_back(d - d0,\
    \ f[d] * fd0inv);\n    }\n\n    const int bias = d0 / 2;\n    const T inv2 = T{2}.inv();\n\
    \    ret[bias] = sqrtf0;\n    for (int d = 0; bias + d + 1 < int(ret.size());\
    \ ++d) {\n        T tmp{0};\n        for (auto [i, fi] : terms) {\n          \
    \  if (i > d + 1) break;\n            int j = d - i;\n            if (0 <= j)\
    \ tmp -= fi * ret[bias + j + 1] * (j + 1);\n            j = d - (i - 1);\n   \
    \         if (0 <= j) tmp += fi * i * ret[bias + j] * inv2;\n        }\n     \
    \   ret[bias + d + 1] = tmp / (d + 1);\n    }\n\n    return ret;\n}\n\n} // namespace\
    \ sparse_fps\n#line 3 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#line\
    \ 6 \"modint.hpp\"\n\ntemplate <int md> struct ModInt {\n    static_assert(md\
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
    // using mint = ModInt<1000000007>;\n#line 6 \"formal_power_series/test/sparse_fps_sqrt.test.cpp\"\
    \nusing namespace std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, K;\n    cin >> N >> K;\n    vector<mint>\
    \ f(N);\n    while (K--) {\n        int i, a;\n        cin >> i >> a;\n      \
    \  f.at(i) = a;\n    }\n\n    const auto ret = sparse_fps::sqrt(f, N - 1);\n \
    \   if (!ret) {\n        cout << -1 << '\\n';\n    } else {\n        for (auto\
    \ e : *ret) cout << e << ' ';\n        cout << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_of_formal_power_series_sparse\"\
    \n#include \"../sparse_fps.hpp\"\n#include \"../../modint.hpp\"\n#include <iostream>\n\
    #include <vector>\nusing namespace std;\nusing mint = ModInt<998244353>;\n\nint\
    \ main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, K;\n\
    \    cin >> N >> K;\n    vector<mint> f(N);\n    while (K--) {\n        int i,\
    \ a;\n        cin >> i >> a;\n        f.at(i) = a;\n    }\n\n    const auto ret\
    \ = sparse_fps::sqrt(f, N - 1);\n    if (!ret) {\n        cout << -1 << '\\n';\n\
    \    } else {\n        for (auto e : *ret) cout << e << ' ';\n        cout <<\
    \ '\\n';\n    }\n}\n"
  dependsOn:
  - formal_power_series/sparse_fps.hpp
  - modint.hpp
  isVerificationFile: true
  path: formal_power_series/test/sparse_fps_sqrt.test.cpp
  requiredBy: []
  timestamp: '2026-03-01 22:00:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: formal_power_series/test/sparse_fps_sqrt.test.cpp
layout: document
redirect_from:
- /verify/formal_power_series/test/sparse_fps_sqrt.test.cpp
- /verify/formal_power_series/test/sparse_fps_sqrt.test.cpp.html
title: formal_power_series/test/sparse_fps_sqrt.test.cpp
---
