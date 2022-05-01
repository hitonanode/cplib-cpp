---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/point-update-range-get_nonrecursive.hpp
    title: segmenttree/point-update-range-get_nonrecursive.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\ntemplate <int md> struct ModInt {\n#if __cplusplus >= 201402L\n\
    #define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using lint = long\
    \ long;\n    MDCONST static int mod() { return md; }\n    static int get_primitive_root()\
    \ {\n        static int primitive_root = 0;\n        if (!primitive_root) {\n\
    \            primitive_root = [&]() {\n                std::set<int> fac;\n  \
    \              int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n\
    \                    while (v % i == 0) fac.insert(i), v /= i;\n             \
    \   if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((md - 1) / i) == 1) {\n           \
    \                 ok = false;\n                            break;\n          \
    \              }\n                    if (ok) return g;\n                }\n \
    \               return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    MDCONST\
    \ ModInt() : val_(0) {}\n    MDCONST ModInt &_setval(lint v) { return val_ = (v\
    \ >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint v) { _setval(v % md +\
    \ md); }\n    MDCONST explicit operator bool() const { return val_ != 0; }\n \
    \   MDCONST ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    MDCONST ModInt operator-(const ModInt &x) const {\n \
    \       return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    MDCONST\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    MDCONST ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    MDCONST ModInt operator-() const { return ModInt()._setval(md - val_); }\n\
    \    MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md + x.val_);\n    }\n    friend MDCONST ModInt operator-(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md - x.val_ + md);\n\
    \    }\n    friend MDCONST ModInt operator*(lint a, const ModInt &x) {\n     \
    \   return ModInt()._setval(a % md * x.val_ % md);\n    }\n    friend MDCONST\
    \ ModInt operator/(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.inv().val() % md);\n    }\n    MDCONST bool operator==(const ModInt\
    \ &x) const { return val_ == x.val_; }\n    MDCONST bool operator!=(const ModInt\
    \ &x) const { return val_ != x.val_; }\n    MDCONST bool operator<(const ModInt\
    \ &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const {\n    \
    \    ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n & 1)\
    \ ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return ans;\n\
    \    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n    MDCONST\
    \ ModInt inv() const {\n        if (this->val_ < std::min(md >> 1, 1 << 21)) {\n\
    \            while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
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
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"segmenttree/point-update-range-get_nonrecursive.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <functional>\n#line 6 \"\
    segmenttree/point-update-range-get_nonrecursive.hpp\"\n#include <stack>\n#line\
    \ 8 \"segmenttree/point-update-range-get_nonrecursive.hpp\"\n\n// CUT begin\n\
    // Nonrecursive Segment Tree (point-update, range-get)\n// - Conditions for operations:\n\
    //   - merge_data: [TDATA, TDATA] -> TDATA, e(x, y) == e(y, x)\n//   - data2ret:\
    \ [TDATA, TQUERY] -> TRET\n//   - merge_ret: [TRET, TRET] -> TRET, g(defaultRET,\
    \ x) == x, g(x, y) = g(y, x)\n//   - commutability f(e(x, y), q) == g(f(x, q),\
    \ f(y, q))\ntemplate <typename TDATA, typename TRET, typename TQUERY> struct NonrecursiveSegmentTree\
    \ {\n    int N;\n    TRET defaultRET;\n    virtual TDATA merge_data(const TDATA\
    \ &, const TDATA &) = 0;\n    virtual TRET data2ret(const TDATA &, const TQUERY\
    \ &) = 0;\n    virtual TRET merge_ret(const TRET &, const TRET &) = 0;\n    std::vector<TDATA>\
    \ data;\n    inline TDATA &at(int i) { return data[i]; }\n\n    inline void _merge(int\
    \ i) { at(i) = merge_data(at(i << 1), at((i << 1) + 1)); }\n    void initialize(const\
    \ std::vector<TDATA> &seq, TRET RET_ZERO) {\n        N = seq.size();\n       \
    \ defaultRET = RET_ZERO;\n        data = seq;\n        data.insert(data.end(),\
    \ seq.begin(), seq.end());\n        for (int i = N - 1; i; i--) _merge(i);\n \
    \   }\n    NonrecursiveSegmentTree() = default;\n    void update(int pos, const\
    \ TDATA &x) {\n        assert(pos >= 0 and pos < N);\n        at(pos + N) = x;\n\
    \        for (int i = pos + N; i > 1;) i >>= 1, _merge(i);\n    }\n\n    // [l,\
    \ r), 0-indexed\n    TRET get(int l, int r, TQUERY query = NULL) {\n        assert(l\
    \ >= 0 and r <= N);\n        TRET retl = defaultRET, retr = defaultRET;\n    \
    \    l += N, r += N;\n        while (l < r) {\n            if (l & 1) retl = merge_ret(retl,\
    \ data2ret(data[l++], query));\n            if (r & 1) retr = merge_ret(data2ret(data[--r],\
    \ query), retr);\n            l >>= 1, r >>= 1;\n        }\n        return merge_ret(retl,\
    \ retr);\n    }\n\n    // Calculate smallest r that satisfies condition(g(f(x_l,\
    \ q), ..., f(x_{r - 1}, q)) == true\n    // Assumption: Monotonicity of g(x_l,\
    \ ..., x_r) about r (l: fixed)\n    // Complexity: O(log N)\n    int binary_search(int\
    \ l, std::function<bool(TRET)> condition, TQUERY query = NULL) {\n        std::stack<int>\
    \ rs;\n        l += N;\n        int r = N * 2;\n        TRET retl = defaultRET;\n\
    \        if (condition(retl)) return l - N;\n        while (l < r) {\n       \
    \     if (l & 1) {\n                TRET ret_tmp = merge_ret(retl, data2ret(data[l],\
    \ query));\n                if (condition(ret_tmp)) {\n                    while\
    \ (l * 2 < N * 2) {\n                        ret_tmp = merge_ret(retl, data2ret(data[l\
    \ * 2], query));\n                        if (condition(ret_tmp))\n          \
    \                  l *= 2;\n                        else\n                   \
    \         retl = ret_tmp, l = l * 2 + 1;\n                    }\n            \
    \        return l - N;\n                }\n                l++;\n            \
    \    retl = ret_tmp;\n            }\n            if (r & 1) rs.push(--r);\n  \
    \          l >>= 1, r >>= 1;\n        }\n        while (!rs.empty()) {\n     \
    \       l = rs.top();\n            rs.pop();\n            TRET ret_tmp = merge_ret(retl,\
    \ data2ret(data[l], query));\n            if (condition(ret_tmp)) {\n        \
    \        while (l * 2 < N * 2) {\n                    ret_tmp = merge_ret(retl,\
    \ data2ret(data[l * 2], query));\n                    if (condition(ret_tmp))\n\
    \                        l *= 2;\n                    else\n                 \
    \       retl = ret_tmp, l = l * 2 + 1;\n                }\n                return\
    \ l - N;\n            }\n            retl = ret_tmp;\n        }\n        return\
    \ N;\n    }\n\n    template <typename T1, typename T2, typename T3>\n    friend\
    \ std::ostream &operator<<(std::ostream &os, NonrecursiveSegmentTree<T1, T2, T3>\
    \ s) {\n        os << \"[SegmentTree (len: \" << s.N << ')';\n        for (int\
    \ i = 0; i < s.N; i++) os << s.at(i + s.N) << ',';\n        os << \"]\";\n   \
    \     return os;\n    }\n};\n\n// Range Minimum Query\n// - get: return min(x_l,\
    \ ..., x_{r - 1})\ntemplate <typename T> struct RangeMinimumQuery : public NonrecursiveSegmentTree<T,\
    \ T, bool> {\n    using SegTree = NonrecursiveSegmentTree<T, T, bool>;\n    T\
    \ merge_data(const T &vl, const T &vr) override { return std::min(vl, vr); };\n\
    \    T data2ret(const T &v, const bool &q) override { return v; }\n    T merge_ret(const\
    \ T &vl, const T &vr) override { return std::min(vl, vr); };\n    RangeMinimumQuery(const\
    \ std::vector<T> &seq, T defaultmin)\n        : SegTree::NonrecursiveSegmentTree()\
    \ {\n        SegTree::initialize(seq, defaultmin);\n    };\n};\n\n// Range Maximum\
    \ Query\n// - get: return max(x_l, ..., x_{r - 1})\ntemplate <typename T> struct\
    \ RangeMaximumQuery : public NonrecursiveSegmentTree<T, T, bool> {\n    using\
    \ SegTree = NonrecursiveSegmentTree<T, T, bool>;\n    T merge_data(const T &vl,\
    \ const T &vr) override { return std::max(vl, vr); };\n    T data2ret(const T\
    \ &v, const bool &q) override { return v; }\n    T merge_ret(const T &vl, const\
    \ T &vr) override { return std::max(vl, vr); };\n    RangeMaximumQuery(const std::vector<T>\
    \ &seq, T defaultmax)\n        : SegTree::NonrecursiveSegmentTree() {\n      \
    \  SegTree::initialize(seq, defaultmax);\n    };\n};\n\ntemplate <typename T>\
    \ struct PointUpdateRangeSum : public NonrecursiveSegmentTree<T, T, bool> {\n\
    \    using SegTree = NonrecursiveSegmentTree<T, T, bool>;\n    T merge_data(const\
    \ T &vl, const T &vr) override { return vl + vr; };\n    T data2ret(const T &v,\
    \ const bool &q) override { return v; }\n    T merge_ret(const T &vl, const T\
    \ &vr) override { return vl + vr; };\n    PointUpdateRangeSum(const std::vector<T>\
    \ &seq, T zero) : SegTree::NonrecursiveSegmentTree() {\n        SegTree::initialize(seq,\
    \ zero);\n    };\n};\n\n// Range Counting less than q Query\n// - get: return\
    \ (#{i | l <= i < r, x_i < q}, total sum of them).\ntemplate <typename T>\nstruct\
    \ CountAndSumLessThan\n    : public NonrecursiveSegmentTree<std::vector<std::pair<T,\
    \ T>>, std::pair<int, T>, T> {\n    using TDATA = std::vector<std::pair<T, T>>;\n\
    \    using TRET = std::pair<int, T>;\n    using TQUERY = T;\n    TDATA merge_data(const\
    \ TDATA &vl, const TDATA &vr) override {\n        TDATA ret = vl;\n        ret.insert(ret.end(),\
    \ vr.begin(), vr.end());\n        std::sort(ret.begin(), ret.end());\n       \
    \ if (ret.size()) {\n            ret[0].second = ret[0].first;\n            for\
    \ (size_t i = 1; i < ret.size(); i++)\n                ret[i].second = ret[i -\
    \ 1].second + ret[i].first;\n        }\n        return ret;\n    }\n    TRET data2ret(const\
    \ TDATA &vec, const TQUERY &q) override {\n        int i = std::lower_bound(vec.begin(),\
    \ vec.end(), std::make_pair(q, q)) - vec.begin();\n        if (!i)\n         \
    \   return std::make_pair(0, 0);\n        else\n            return std::make_pair(i,\
    \ vec[i - 1].second);\n    }\n    TRET merge_ret(const TRET &l, const TRET &r)\
    \ override {\n        return std::make_pair(l.first + r.first, l.second + r.second);\n\
    \    }\n    using SegTree = NonrecursiveSegmentTree<TDATA, TRET, TQUERY>;\n  \
    \  CountAndSumLessThan(const std::vector<T> &seq) : SegTree::NonrecursiveSegmentTree()\
    \ {\n        std::vector<TDATA> init;\n        for (auto x : seq) init.emplace_back(TDATA{std::pair<T,\
    \ T>(x, x)});\n        SegTree::initialize(init, TRET(0, 0));\n    }\n};\n#line\
    \ 4 \"segmenttree/test/point-set-range-composite.test.cpp\"\n#include <utility>\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\n\
    using mint = ModInt<998244353>;\n\ntemplate <typename T>\nstruct PointSetRangeComposite\n\
    \    : public NonrecursiveSegmentTree<std::pair<T, T>, std::pair<T, T>, bool>\
    \ {\n    using T_NODE = std::pair<T, T>;\n    using SegTree = NonrecursiveSegmentTree<T_NODE,\
    \ T_NODE, bool>;\n    T_NODE merge_data(const T_NODE &vl, const T_NODE &vr) override\
    \ {\n        return std::make_pair(vl.first * vr.first, vr.first * vl.second +\
    \ vr.second);\n    };\n    T_NODE data2ret(const T_NODE &v, const bool &q) override\
    \ { return v; }\n    T_NODE merge_ret(const T_NODE &vl, const T_NODE &vr) override\
    \ { return merge_data(vl, vr); };\n    PointSetRangeComposite(const std::vector<T_NODE>\
    \ &seq) : SegTree::NonrecursiveSegmentTree() {\n        SegTree::initialize(seq,\
    \ T_NODE(1, 0));\n    };\n};\n\nint main() {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<std::pair<mint, mint>>\
    \ A(N);\n    for (auto &p : A) { std::cin >> p.first >> p.second; }\n    PointSetRangeComposite<mint>\
    \ s(A);\n    while (Q--) {\n        int q, l, r, x;\n        std::cin >> q >>\
    \ l >> r >> x;\n        if (q) {\n            auto ret = s.get(l, r);\n      \
    \      std::cout << ret.first * x + ret.second << '\\n';\n        } else {\n \
    \           s.update(l, std::make_pair(r, x));\n        }\n    }\n}\n"
  code: "#include \"../../modint.hpp\"\n#include \"../point-update-range-get_nonrecursive.hpp\"\
    \n#include <iostream>\n#include <utility>\n#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \nusing mint = ModInt<998244353>;\n\ntemplate <typename T>\nstruct PointSetRangeComposite\n\
    \    : public NonrecursiveSegmentTree<std::pair<T, T>, std::pair<T, T>, bool>\
    \ {\n    using T_NODE = std::pair<T, T>;\n    using SegTree = NonrecursiveSegmentTree<T_NODE,\
    \ T_NODE, bool>;\n    T_NODE merge_data(const T_NODE &vl, const T_NODE &vr) override\
    \ {\n        return std::make_pair(vl.first * vr.first, vr.first * vl.second +\
    \ vr.second);\n    };\n    T_NODE data2ret(const T_NODE &v, const bool &q) override\
    \ { return v; }\n    T_NODE merge_ret(const T_NODE &vl, const T_NODE &vr) override\
    \ { return merge_data(vl, vr); };\n    PointSetRangeComposite(const std::vector<T_NODE>\
    \ &seq) : SegTree::NonrecursiveSegmentTree() {\n        SegTree::initialize(seq,\
    \ T_NODE(1, 0));\n    };\n};\n\nint main() {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<std::pair<mint, mint>>\
    \ A(N);\n    for (auto &p : A) { std::cin >> p.first >> p.second; }\n    PointSetRangeComposite<mint>\
    \ s(A);\n    while (Q--) {\n        int q, l, r, x;\n        std::cin >> q >>\
    \ l >> r >> x;\n        if (q) {\n            auto ret = s.get(l, r);\n      \
    \      std::cout << ret.first * x + ret.second << '\\n';\n        } else {\n \
    \           s.update(l, std::make_pair(r, x));\n        }\n    }\n}\n"
  dependsOn:
  - modint.hpp
  - segmenttree/point-update-range-get_nonrecursive.hpp
  isVerificationFile: true
  path: segmenttree/test/point-set-range-composite.test.cpp
  requiredBy: []
  timestamp: '2022-05-01 16:11:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/point-set-range-composite.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/point-set-range-composite.test.cpp
- /verify/segmenttree/test/point-set-range-composite.test.cpp.html
title: segmenttree/test/point-set-range-composite.test.cpp
---
