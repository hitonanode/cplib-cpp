---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: data_structure/rectangle_add_rectangle_sum.hpp
    title: "Static rectangle add rectangle sum \uFF08\u77E9\u5F62\u4E00\u69D8\u52A0\
      \u7B97\u30FB\u77E9\u5F62\u7DCF\u548C\u53D6\u5F97\uFF09"
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':question:'
    path: segmenttree/binary_indexed_tree.hpp
    title: "Binary indexed tree / Fenwick tree \uFF08BIT\u30FB\u30D5\u30A7\u30CB\u30C3\
      \u30AF\u6728\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
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
    \n#include <iostream>\n#include <set>\n#line 5 \"modint.hpp\"\n\ntemplate <int\
    \ md> struct ModInt {\n#if __cplusplus >= 201402L\n#define MDCONST constexpr\n\
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
    \  }\n        return primitive_root;\n    }\n    int val_;\n    int val() const\
    \ noexcept { return val_; }\n    MDCONST ModInt() : val_(0) {}\n    MDCONST ModInt\
    \ &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n    MDCONST\
    \ ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit operator bool()\
    \ const { return val_ != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ - x.val_ + md);\n    }\n    MDCONST ModInt operator*(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    MDCONST\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.inv().val() % md);\n    }\n    MDCONST ModInt operator-() const { return\
    \ ModInt()._setval(md - val_); }\n    MDCONST ModInt &operator+=(const ModInt\
    \ &x) { return *this = *this + x; }\n    MDCONST ModInt &operator-=(const ModInt\
    \ &x) { return *this = *this - x; }\n    MDCONST ModInt &operator*=(const ModInt\
    \ &x) { return *this = *this * x; }\n    MDCONST ModInt &operator/=(const ModInt\
    \ &x) { return *this = *this / x; }\n    friend MDCONST ModInt operator+(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md + x.val_);\n \
    \   }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x) {\n      \
    \  return ModInt()._setval(a % md - x.val_ + md);\n    }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) {\n        return ModInt()._setval(a % md\
    \ * x.val_ % md);\n    }\n    friend MDCONST ModInt operator/(lint a, const ModInt\
    \ &x) {\n        return ModInt()._setval(a % md * x.inv().val() % md);\n    }\n\
    \    MDCONST bool operator==(const ModInt &x) const { return val_ == x.val_; }\n\
    \    MDCONST bool operator!=(const ModInt &x) const { return val_ != x.val_; }\n\
    \    MDCONST bool operator<(const ModInt &x) const {\n        return val_ < x.val_;\n\
    \    } // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) {\n        lint t;\n        return is >> t, x = ModInt(t), is;\n\
    \    }\n    MDCONST friend std::ostream &operator<<(std::ostream &os, const ModInt\
    \ &x) {\n        return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const\
    \ {\n        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if\
    \ (n & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST\
    \ static void _precalculation(int N) {\n        int l0 = facs.size();\n      \
    \  if (N > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N),\
    \ facinvs.resize(N), invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n    \
    \    for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n\
    \        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n\
    \    }\n    MDCONST ModInt inv() const {\n        if (this->val_ < std::min(md\
    \ >> 1, 1 << 21)) {\n            if (facs.empty()) facs = {1}, facinvs = {1},\
    \ invs = {0};\n            while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val_];\n        } else {\n            return\
    \ this->pow(md - 2);\n        }\n    }\n    MDCONST ModInt fac() const {\n   \
    \     while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \        return facs[this->val_];\n    }\n    MDCONST ModInt facinv() const {\n\
    \        while (this->val_ >= int(facs.size())) _precalculation(facs.size() *\
    \ 2);\n        return facinvs[this->val_];\n    }\n    MDCONST ModInt doublefac()\
    \ const {\n        lint k = (this->val_ + 1) / 2;\n        return (this->val_\
    \ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n        \
    \                        : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST\
    \ ModInt nCr(const ModInt &r) const {\n        return (this->val_ < r.val_) ?\
    \ 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST ModInt\
    \ nPr(const ModInt &r) const {\n        return (this->val_ < r.val_) ? 0 : this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val_\
    \ == 0) return 0;\n        if (md == 2) return val_;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 5 \"data_structure/test/rectangle_add_rectangle_sum.test.cpp\"\nusing namespace\
    \ std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr),\
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
  timestamp: '2022-07-12 00:34:46+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: data_structure/test/rectangle_add_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/rectangle_add_rectangle_sum.test.cpp
- /verify/data_structure/test/rectangle_add_rectangle_sum.test.cpp.html
title: data_structure/test/rectangle_add_rectangle_sum.test.cpp
---
