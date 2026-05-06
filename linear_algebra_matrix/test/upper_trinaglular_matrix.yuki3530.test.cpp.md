---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/upper_triangular_matrix.hpp
    title: "Upper triangular matrix \uFF08\u5B9A\u6570\u6B21\u5143\u4E0A\u4E09\u89D2\
      \u884C\u5217\uFF09"
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
    PROBLEM: https://yukicoder.me/problems/no/3530
    links:
    - https://yukicoder.me/problems/no/3530
  bundledCode: "#line 1 \"linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/3530\"\n#line 2 \"linear_algebra_matrix/upper_triangular_matrix.hpp\"\
    \n\ntemplate <class T> struct UpperTriangular3d {\n    static T explicit_init_required()\
    \ = delete;\n    T a00 = this->explicit_init_required(), a01 = this->explicit_init_required(),\n\
    \      a02 = this->explicit_init_required();\n    T a11 = this->explicit_init_required(),\
    \ a12 = this->explicit_init_required();\n    T a22 = this->explicit_init_required();\n\
    \n    UpperTriangular3d operator*(const UpperTriangular3d &r) const {\n      \
    \  return UpperTriangular3d{\n            .a00 = this->a00 * r.a00,\n        \
    \    .a01 = this->a00 * r.a01 + this->a01 * r.a11,\n            .a02 = this->a00\
    \ * r.a02 + this->a01 * r.a12 + this->a02 * r.a22,\n            .a11 = this->a11\
    \ * r.a11,\n            .a12 = this->a11 * r.a12 + this->a12 * r.a22,\n      \
    \      .a22 = this->a22 * r.a22,\n        };\n    }\n\n    UpperTriangular3d operator-()\
    \ const {\n        return UpperTriangular3d{\n            .a00 = -this->a00,\n\
    \            .a01 = -this->a01,\n            .a02 = -this->a02,\n            .a11\
    \ = -this->a11,\n            .a12 = -this->a12,\n            .a22 = -this->a22,\n\
    \        };\n    }\n\n    UpperTriangular3d operator+(const UpperTriangular3d\
    \ &r) const {\n        return UpperTriangular3d{\n            .a00 = this->a00\
    \ + r.a00,\n            .a01 = this->a01 + r.a01,\n            .a02 = this->a02\
    \ + r.a02,\n            .a11 = this->a11 + r.a11,\n            .a12 = this->a12\
    \ + r.a12,\n            .a22 = this->a22 + r.a22,\n        };\n    }\n\n    auto\
    \ operator<=>(const UpperTriangular3d &) const = default;\n};\n#line 2 \"modint.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <set>\n#include <vector>\n\
    \ntemplate <int md> struct ModInt {\n    static_assert(md > 1);\n    using lint\
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
    // using mint = ModInt<1000000007>;\n#line 4 \"linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp\"\
    \n\n#include <algorithm>\n#line 7 \"linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp\"\
    \n#include <map>\n#include <utility>\n#line 10 \"linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp\"\
    \n#include <atcoder/segtree>\n\nusing namespace std;\nusing S = UpperTriangular3d<ModInt998244353>;\n\
    \nS op(const S &l, const S &r) { return l * r; }\nS e() { return S{1, 0, 0, 1,\
    \ 0, 1}; }\n\nS GenR() { return S{ModInt998244353(3) / 4, ModInt998244353(1) /\
    \ 4, 0, 1, 0, 1}; }\nS GenL() { return S{1, 0, 0, ModInt998244353(3) / 4, ModInt998244353(1)\
    \ / 4, 1}; }\n\nModInt998244353 Solve(vector<pair<int, int>> ps) {\n    vector<tuple<int,\
    \ int, int>> yxis;\n    for (int i = 0; i < (int)ps.size(); ++i) {\n        auto\
    \ [x, y] = ps.at(i);\n        yxis.emplace_back(y, x, i);\n    }\n    sort(yxis.begin(),\
    \ yxis.end());\n\n    const auto L = GenL(), R = GenR();\n    const vector<S>\
    \ init(ps.size(), R);\n    atcoder::segtree<S, op, e> seg(init);\n\n    int last_x\
    \ = -1e9;\n\n    ModInt998244353 ret = 0;\n\n    map<int, vector<pair<int, int>>>\
    \ x2yis;\n    for (int i = 0; i < (int)ps.size(); ++i) {\n        auto [x, y]\
    \ = ps.at(i);\n        x2yis[x].emplace_back(y, i);\n    }\n    for (auto [x,\
    \ yis] : x2yis) {\n\n        const ModInt998244353 dx = x - last_x;\n        ret\
    \ += dx * seg.all_prod().a02;\n\n        for (auto [y, i] : yis) {\n         \
    \   const int idx =\n                lower_bound(yxis.begin(), yxis.end(), make_tuple(y,\
    \ x, i)) - yxis.begin();\n            seg.set(idx, L);\n        }\n\n        last_x\
    \ = x;\n    }\n\n    return ret;\n}\n\nint main() {\n    int N;\n    cin >> N;\n\
    \    vector<pair<int, int>> xy(N);\n\n    for (auto &[x, y] : xy) cin >> x >>\
    \ y;\n\n    const ModInt998244353 coeff = ModInt998244353(4).pow(N);\n    ModInt998244353\
    \ ret1 = Solve(xy) * coeff;\n    for (auto &[x, y] : xy) swap(x, y);\n    ModInt998244353\
    \ ret2 = Solve(xy) * coeff;\n    cout << (ret1 + ret2) * 2 << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/3530\"\n#include \"../upper_triangular_matrix.hpp\"\
    \n#include \"../../modint.hpp\"\n\n#include <algorithm>\n#include <iostream>\n\
    #include <map>\n#include <utility>\n#include <vector>\n#include <atcoder/segtree>\n\
    \nusing namespace std;\nusing S = UpperTriangular3d<ModInt998244353>;\n\nS op(const\
    \ S &l, const S &r) { return l * r; }\nS e() { return S{1, 0, 0, 1, 0, 1}; }\n\
    \nS GenR() { return S{ModInt998244353(3) / 4, ModInt998244353(1) / 4, 0, 1, 0,\
    \ 1}; }\nS GenL() { return S{1, 0, 0, ModInt998244353(3) / 4, ModInt998244353(1)\
    \ / 4, 1}; }\n\nModInt998244353 Solve(vector<pair<int, int>> ps) {\n    vector<tuple<int,\
    \ int, int>> yxis;\n    for (int i = 0; i < (int)ps.size(); ++i) {\n        auto\
    \ [x, y] = ps.at(i);\n        yxis.emplace_back(y, x, i);\n    }\n    sort(yxis.begin(),\
    \ yxis.end());\n\n    const auto L = GenL(), R = GenR();\n    const vector<S>\
    \ init(ps.size(), R);\n    atcoder::segtree<S, op, e> seg(init);\n\n    int last_x\
    \ = -1e9;\n\n    ModInt998244353 ret = 0;\n\n    map<int, vector<pair<int, int>>>\
    \ x2yis;\n    for (int i = 0; i < (int)ps.size(); ++i) {\n        auto [x, y]\
    \ = ps.at(i);\n        x2yis[x].emplace_back(y, i);\n    }\n    for (auto [x,\
    \ yis] : x2yis) {\n\n        const ModInt998244353 dx = x - last_x;\n        ret\
    \ += dx * seg.all_prod().a02;\n\n        for (auto [y, i] : yis) {\n         \
    \   const int idx =\n                lower_bound(yxis.begin(), yxis.end(), make_tuple(y,\
    \ x, i)) - yxis.begin();\n            seg.set(idx, L);\n        }\n\n        last_x\
    \ = x;\n    }\n\n    return ret;\n}\n\nint main() {\n    int N;\n    cin >> N;\n\
    \    vector<pair<int, int>> xy(N);\n\n    for (auto &[x, y] : xy) cin >> x >>\
    \ y;\n\n    const ModInt998244353 coeff = ModInt998244353(4).pow(N);\n    ModInt998244353\
    \ ret1 = Solve(xy) * coeff;\n    for (auto &[x, y] : xy) swap(x, y);\n    ModInt998244353\
    \ ret2 = Solve(xy) * coeff;\n    cout << (ret1 + ret2) * 2 << '\\n';\n}\n"
  dependsOn:
  - linear_algebra_matrix/upper_triangular_matrix.hpp
  - modint.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp
  requiredBy: []
  timestamp: '2026-05-06 21:05:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp
- /verify/linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp.html
title: linear_algebra_matrix/test/upper_trinaglular_matrix.yuki3530.test.cpp
---
