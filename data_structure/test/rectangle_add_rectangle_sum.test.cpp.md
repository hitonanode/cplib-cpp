---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/rectangle_add_rectangle_sum.hpp
    title: "Static rectangle add rectangle sum \uFF08\u77E9\u5F62\u4E00\u69D8\u52A0\
      \u7B97\u30FB\u77E9\u5F62\u7DCF\u548C\u53D6\u5F97\uFF09"
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/binary_indexed_tree.hpp
    title: "Binary indexed tree / Fenwick tree \uFF08BIT\u30FB\u30D5\u30A7\u30CB\u30C3\
      \u30AF\u6728\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum
  bundledCode: "#line 1 \"data_structure/test/rectangle_add_rectangle_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum\"\
    \n#line 2 \"segmenttree/binary_indexed_tree.hpp\"\n#include <algorithm>\n#include\
    \ <vector>\n\n// CUT begin\n// 0-indexed BIT (binary indexed tree / Fenwick tree)\
    \ (i : [0, len))\ntemplate <class T> struct BIT {\n    int n;\n    std::vector<T>\
    \ data;\n    BIT(int len = 0) : n(len), data(len) {}\n    void reset() { std::fill(data.begin(),\
    \ data.end(), T(0)); }\n    void add(int pos, T v) { // a[pos] += v\n        pos++;\n\
    \        while (pos > 0 and pos <= n) data[pos - 1] += v, pos += pos & -pos;\n\
    \    }\n    T sum(int k) const { // a[0] + ... + a[k - 1]\n        T res = 0;\n\
    \        while (k > 0) res += data[k - 1], k -= k & -k;\n        return res;\n\
    \    }\n\n    T sum(int l, int r) const { return sum(r) - sum(l); } // a[l] +\
    \ ... + a[r - 1]\n\n    template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const BIT &bit) {\n        T prv = 0;\n        os << '[';\n        for\
    \ (int i = 1; i <= bit.n; i++) {\n            T now = bit.sum(i);\n          \
    \  os << now - prv << ',', prv = now;\n        }\n        return os << ']';\n\
    \    }\n};\n#line 4 \"data_structure/rectangle_add_rectangle_sum.hpp\"\n#include\
    \ <tuple>\n#line 6 \"data_structure/rectangle_add_rectangle_sum.hpp\"\n\n// Static\
    \ rectangle add rectangle sum\n// Calculate sums of rectangular weights inside\
    \ the given rectangles\n// Complexity: O(q log q), q = # of rectangles / queries\n\
    template <class Int, class T> class RectangleAddRectangleSum {\n    struct AddQuery\
    \ {\n        Int xl, xr, yl, yr;\n        T val;\n    };\n    struct SumQuery\
    \ {\n        Int xl, xr, yl, yr;\n    };\n    std::vector<AddQuery> add_queries;\n\
    \    std::vector<SumQuery> sum_queries;\n\npublic:\n    RectangleAddRectangleSum()\
    \ = default;\n\n    // A[x][y] += val for (x, y) in [xl, xr) * [yl, yr)\n    void\
    \ add_rectangle(Int xl, Int xr, Int yl, Int yr, T val) {\n        add_queries.push_back(AddQuery{xl,\
    \ xr, yl, yr, val});\n    }\n\n    // Get sum of A[x][y] for (x, y) in [xl, xr)\
    \ * [yl, yr)\n    void add_query(Int xl, Int xr, Int yl, Int yr) {\n        sum_queries.push_back(SumQuery{xl,\
    \ xr, yl, yr});\n    }\n\n    std::vector<T> solve() const {\n        std::vector<Int>\
    \ ys;\n        for (const auto &a : add_queries) {\n            ys.push_back(a.yl);\n\
    \            ys.push_back(a.yr);\n        }\n        std::sort(ys.begin(), ys.end());\n\
    \        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n\n        const\
    \ int Y = ys.size();\n\n        std::vector<std::tuple<Int, int, int>> ops;\n\
    \        for (int q = 0; q < int(sum_queries.size()); ++q) {\n            ops.emplace_back(sum_queries[q].xl,\
    \ 0, q);\n            ops.emplace_back(sum_queries[q].xr, 1, q);\n        }\n\
    \        for (int q = 0; q < int(add_queries.size()); ++q) {\n            ops.emplace_back(add_queries[q].xl,\
    \ 2, q);\n            ops.emplace_back(add_queries[q].xr, 3, q);\n        }\n\
    \        std::sort(ops.begin(), ops.end());\n\n        BIT<T> b00(Y), b01(Y),\
    \ b10(Y), b11(Y);\n        std::vector<T> ret(sum_queries.size());\n        for\
    \ (auto o : ops) {\n            int qtype = std::get<1>(o), q = std::get<2>(o);\n\
    \            if (qtype >= 2) {\n                const AddQuery &query = add_queries.at(q);\n\
    \                int i = std::lower_bound(ys.begin(), ys.end(), query.yl) - ys.begin();\n\
    \                int j = std::lower_bound(ys.begin(), ys.end(), query.yr) - ys.begin();\n\
    \                T x = std::get<0>(o);\n                T yi = query.yl, yj =\
    \ query.yr;\n                if (qtype & 1) std::swap(i, j), std::swap(yi, yj);\n\
    \n                b00.add(i, x * yi * query.val);\n                b01.add(i,\
    \ -x * query.val);\n                b10.add(i, -yi * query.val);\n           \
    \     b11.add(i, query.val);\n                b00.add(j, -x * yj * query.val);\n\
    \                b01.add(j, x * query.val);\n                b10.add(j, yj * query.val);\n\
    \                b11.add(j, -query.val);\n            } else {\n             \
    \   const SumQuery &query = sum_queries.at(q);\n                int i = std::lower_bound(ys.begin(),\
    \ ys.end(), query.yl) - ys.begin();\n                int j = std::lower_bound(ys.begin(),\
    \ ys.end(), query.yr) - ys.begin();\n                T x = std::get<0>(o);\n \
    \               T yi = query.yl, yj = query.yr;\n                if (qtype & 1)\
    \ std::swap(i, j), std::swap(yi, yj);\n\n                ret[q] += b00.sum(i)\
    \ + b01.sum(i) * yi + b10.sum(i) * x + b11.sum(i) * x * yi;\n                ret[q]\
    \ -= b00.sum(j) + b01.sum(j) * yj + b10.sum(j) * x + b11.sum(j) * x * yj;\n  \
    \          }\n        }\n        return ret;\n    }\n};\n#line 2 \"modint.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <set>\n#line 6 \"modint.hpp\"\
    \n\ntemplate <int md> struct ModInt {\n    static_assert(md > 1);\n    using lint\
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
    // using mint = ModInt<1000000007>;\n#line 5 \"data_structure/test/rectangle_add_rectangle_sum.test.cpp\"\
    \nusing namespace std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    RectangleAddRectangleSum<int, mint> rect_sum;\n\
    \n    const int bias = 500000000;\n\n    int N, Q;\n    cin >> N >> Q;\n\n   \
    \ while (N--) {\n        int l, r, d, u;\n        mint w;\n        cin >> l >>\
    \ d >> r >> u >> w;\n        l -= bias;\n        d -= bias;\n        r -= bias;\n\
    \        u -= bias;\n        rect_sum.add_rectangle(l, r, d, u, w);\n    }\n\n\
    \    while (Q--) {\n        int l, r, d, u;\n        cin >> l >> d >> r >> u;\n\
    \        l -= bias;\n        d -= bias;\n        r -= bias;\n        u -= bias;\n\
    \        rect_sum.add_query(l, r, d, u);\n    }\n\n    auto ret = rect_sum.solve();\n\
    \    for (auto x : ret) cout << x << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum\"\
    \n#include \"../rectangle_add_rectangle_sum.hpp\"\n#include \"../../modint.hpp\"\
    \n#include <iostream>\nusing namespace std;\nusing mint = ModInt<998244353>;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    RectangleAddRectangleSum<int,\
    \ mint> rect_sum;\n\n    const int bias = 500000000;\n\n    int N, Q;\n    cin\
    \ >> N >> Q;\n\n    while (N--) {\n        int l, r, d, u;\n        mint w;\n\
    \        cin >> l >> d >> r >> u >> w;\n        l -= bias;\n        d -= bias;\n\
    \        r -= bias;\n        u -= bias;\n        rect_sum.add_rectangle(l, r,\
    \ d, u, w);\n    }\n\n    while (Q--) {\n        int l, r, d, u;\n        cin\
    \ >> l >> d >> r >> u;\n        l -= bias;\n        d -= bias;\n        r -= bias;\n\
    \        u -= bias;\n        rect_sum.add_query(l, r, d, u);\n    }\n\n    auto\
    \ ret = rect_sum.solve();\n    for (auto x : ret) cout << x << '\\n';\n}\n"
  dependsOn:
  - data_structure/rectangle_add_rectangle_sum.hpp
  - segmenttree/binary_indexed_tree.hpp
  - modint.hpp
  isVerificationFile: true
  path: data_structure/test/rectangle_add_rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2025-09-11 21:33:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/rectangle_add_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/rectangle_add_rectangle_sum.test.cpp
- /verify/data_structure/test/rectangle_add_rectangle_sum.test.cpp.html
title: data_structure/test/rectangle_add_rectangle_sum.test.cpp
---
