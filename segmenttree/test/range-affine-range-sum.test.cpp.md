---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/range-update-range-get.hpp
    title: segmenttree/range-update-range-get.hpp
  - icon: ':question:'
    path: modulus/modint_fixed.hpp
    title: modulus/modint_fixed.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 2 \"segmenttree/range-update-range-get.hpp\"\n#include <algorithm>\n\
    #include <iostream>\n#include <tuple>\n#include <vector>\n\n// CUT begin\ntemplate\
    \ <typename TDATA, typename TLAZY, typename TRET, typename TQUERY>\nstruct LazySegmentTree\n\
    {\n    TLAZY zero_lazy;\n    TRET zero_ret;\n    int N;\n    int head;\n    std::vector<TDATA>\
    \ data;\n    std::vector<TLAZY> lazy;\n\n    // Here, you have to calculate data[pos]\
    \ from children (data[l], data[r]),\n    // Assumptions: `lazy[pos] = lazy[l]\
    \ = lazy[r] = zero_lazy`\n    virtual void merge_data(int pos) = 0;\n\n    //\
    \ Here, you must propagate lazy[pos] and update data[pos] by reflecting lazy[pos],\
    \ without inconsistency\n    // After this, lazy[pos] must be zero_lazy.\n   \
    \ virtual void reflect_lazy(int pos) = 0;\n\n    // operate d to lazy[pos] (merge\
    \ two TLAZY's)\n    virtual void overlap_lazy(int pos, const TLAZY &d) = 0;\n\n\
    \    // Assumption: `lazy[pos] = zero_lazy`\n    virtual TRET data2ret(int pos,\
    \ const TQUERY &query) = 0;\n\n    virtual TRET merge_ret(const TRET &l, const\
    \ TRET &r, const TQUERY &query) = 0;\n\n    ////// general description //////\n\
    \    LazySegmentTree() = default;\n    void initialize(const std::vector<TDATA>\
    \ &data_init, const TDATA &zero_data, const TLAZY &zero_lazy_, const TRET &zero_ret_)\n\
    \    {\n        N = data_init.size();\n        head = 1;\n        while (head\
    \ < N) head <<= 1;\n        zero_lazy = zero_lazy_;\n        zero_ret = zero_ret_;\n\
    \        data.assign(head * 2, zero_data);\n        lazy.assign(head * 2, zero_lazy);\n\
    \        std::copy(data_init.begin(), data_init.end(), data.begin() + head);\n\
    \        for (int pos = head; --pos;) merge_data(pos);\n    }\n\n    void _update(int\
    \ begin, int end, const TLAZY &delay, int pos, int l, int r)\n    {\n        //\
    \ Operate `delay` to the node pos\n        // After this, lazy[pos] MUST be zero\
    \ so that merge_data() works correctly\n        if (begin <= l and r <= end) {\
    \ // Update whole [l, r) by delay\n            overlap_lazy(pos, delay);\n   \
    \         reflect_lazy(pos);\n        }\n        else if (begin < r and l < end)\
    \ { // Update somewhere in [l, r)\n            reflect_lazy(pos);\n          \
    \  _update(begin, end, delay, pos * 2, l, (l + r) / 2);\n            _update(begin,\
    \ end, delay, pos * 2 + 1, (l + r) / 2, r);\n            merge_data(pos);\n  \
    \      }\n        else reflect_lazy(pos);\n    }\n\n    void update(int begin,\
    \ int end, const TLAZY &delay) {\n        _update(begin, end, delay, 1, 0, head);\n\
    \    }\n\n    TRET _get(int begin, int end, int pos, int l, int r, const TQUERY\
    \ &query) // Get value in [begin, end)\n    {\n        reflect_lazy(pos);\n  \
    \      if (begin <= l and r <= end) return data2ret(pos, query);\n        else\
    \ if (begin < r and l < end) {\n            TRET vl = _get(begin, end, pos * 2,\
    \ l, (l + r) / 2, query);\n            TRET vr = _get(begin, end, pos * 2 + 1,\
    \ (l + r) / 2, r, query);\n            return merge_ret(vl, vr, query);\n    \
    \    }\n        else return zero_ret;\n    }\n    TRET get(int begin, int end,\
    \ const TQUERY &query = NULL)\n    {\n        return _get(begin, end, 1, 0, head,\
    \ query);\n    }\n};\n\n\n// Range Update & Range Sum\n// - get(l, r): return\
    \ x_l + ... + x_{r - 1}\n// - update(l, r, val): x_l, ..., x_{r - 1} <- val\n\
    template <typename T>\nstruct RangeUpdateRangeSum : public LazySegmentTree<std::pair<T,\
    \ size_t>, std::pair<T, bool>, T, std::tuple<>>\n{\n    using TDATA = std::pair<T,\
    \ size_t>;\n    using TLAZY = std::pair<T, bool>;\n    using SegTree = LazySegmentTree<TDATA,\
    \ TLAZY, T, std::tuple<>>;\n    using SegTree::data;\n    using SegTree::lazy;\n\
    \    void merge_data(int i) override\n    {\n        data[i] = std::make_pair(data[i\
    \ * 2].first + data[i * 2 + 1].first, data[i * 2].second + data[i * 2 + 1].second);\n\
    \    };\n    void reflect_lazy(int i) override\n    {\n        if (lazy[i].second)\n\
    \        {\n            if (i < SegTree::head) overlap_lazy(i * 2, lazy[i]), overlap_lazy(i\
    \ * 2 + 1, lazy[i]);\n            data[i].first = lazy[i].first * data[i].second;\n\
    \        }\n        lazy[i].second = false;\n    }\n    void overlap_lazy(int\
    \ i, const TLAZY &p) override { if (p.second) lazy[i] = p; }\n    T data2ret(int\
    \ i, const std::tuple<> &) override { return data[i].first; }\n    T merge_ret(const\
    \ T &l, const T &r, const std::tuple<> &) override { return l + r; }\n    void\
    \ update(int l, int r, T val) { SegTree::update(l, r, TLAZY(val, true)); }\n \
    \   T get(int l, int r) { return SegTree::get(l, r, {}); }\n    RangeUpdateRangeSum(const\
    \ std::vector<T> &seq) : SegTree::LazySegmentTree()\n    {\n        std::vector<TDATA>\
    \ vec;\n        for (const auto &x : seq) vec.emplace_back(x, 1);\n        SegTree::initialize(vec,\
    \ TDATA(0, 0), TLAZY(0, false), 0);\n    }\n};\n#line 4 \"modulus/modint_fixed.hpp\"\
    \n#include <set>\n\n// CUT begin\ntemplate <int mod>\nstruct ModInt\n{\n    using\
    \ lint = long long;\n    static int get_mod() { return mod; }\n    static int\
    \ get_primitive_root() {\n        static int primitive_root = 0;\n        if (!primitive_root)\
    \ {\n            primitive_root = [&](){\n                std::set<int> fac;\n\
    \                int v = mod - 1;\n                for (lint i = 2; i * i <= v;\
    \ i++) while (v % i == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n\
    \                for (int g = 1; g < mod; g++) {\n                    bool ok\
    \ = true;\n                    for (auto i : fac) if (ModInt(g).power((mod - 1)\
    \ / i) == 1) { ok = false; break; }\n                    if (ok) return g;\n \
    \               }\n                return -1;\n            }();\n        }\n \
    \       return primitive_root;\n    }\n    int val;\n    constexpr ModInt() :\
    \ val(0) {}\n    constexpr ModInt &_setval(lint v) { val = (v >= mod ? v - mod\
    \ : v); return *this; }\n    constexpr ModInt(lint v) { _setval(v % mod + mod);\
    \ }\n    explicit operator bool() const { return val != 0; }\n    constexpr ModInt\
    \ operator+(const ModInt &x) const { return ModInt()._setval((lint)val + x.val);\
    \ }\n    constexpr ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + mod); }\n    constexpr ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % mod); }\n    constexpr ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % mod); }\n \
    \   constexpr ModInt operator-() const { return ModInt()._setval(mod - val); }\n\
    \    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this + x;\
    \ }\n    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this\
    \ - x; }\n    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this\
    \ * x; }\n    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this\
    \ / x; }\n    friend constexpr ModInt operator+(lint a, const ModInt &x) { return\
    \ ModInt()._setval(a % mod + x.val); }\n    friend constexpr ModInt operator-(lint\
    \ a, const ModInt &x) { return ModInt()._setval(a % mod - x.val + mod); }\n  \
    \  friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod * x.val % mod); }\n    friend constexpr ModInt operator/(lint a, const\
    \ ModInt &x) { return ModInt()._setval(a % mod * x.inv() % mod); }\n    constexpr\
    \ bool operator==(const ModInt &x) const { return val == x.val; }\n    constexpr\
    \ bool operator!=(const ModInt &x) const { return val != x.val; }\n    bool operator<(const\
    \ ModInt &x) const { return val < x.val; }  // To use std::map<ModInt, T>\n  \
    \  friend std::istream &operator>>(std::istream &is, ModInt &x) { lint t; is >>\
    \ t; x = ModInt(t); return is; }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const ModInt &x) { os << x.val;  return os; }\n    constexpr lint power(lint\
    \ n) const {\n        lint ans = 1, tmp = this->val;\n        while (n) {\n  \
    \          if (n & 1) ans = ans * tmp % mod;\n            tmp = tmp * tmp % mod;\n\
    \            n /= 2;\n        }\n        return ans;\n    }\n    constexpr lint\
    \ inv() const { return this->power(mod - 2); }\n    constexpr ModInt operator^(lint\
    \ n) const { return ModInt(this->power(n)); }\n    constexpr ModInt &operator^=(lint\
    \ n) { return *this = *this ^ n; }\n\n    inline ModInt fac() const {\n      \
    \  static std::vector<ModInt> facs;\n        int l0 = facs.size();\n        if\
    \ (l0 > this->val) return facs[this->val];\n\n        facs.resize(this->val +\
    \ 1);\n        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1)\
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
    \        return ModInt(std::min(x.val, mod - x.val));\n    }\n};\n\n// constexpr\
    \ lint MOD = 998244353;\n// using mint = ModInt<MOD>;\n#line 3 \"segmenttree/test/range-affine-range-sum.test.cpp\"\
    \n#include <utility>\n#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n// RangeAffineRangeSum\n// - update: x_i -> a * x_i + b for i in [l, r)\n\
    // - get: return x_l + ... + x_{r - 1}\ntemplate <typename T>\nstruct RangeAffineRangeSum\
    \ : public LazySegmentTree<std::pair<T, int>, std::pair<T, T>, T, bool>\n{\n \
    \   using TDATA = std::pair<T, int>;\n    using TLAZY = std::pair<T, T>;\n   \
    \ using SegTree = LazySegmentTree<TDATA, TLAZY, T, bool>;\n    void merge_data(int\
    \ pos)\n    {\n        this->data[pos].first = this->data[pos * 2].first + this->data[pos\
    \ * 2 + 1].first;\n        this->data[pos].second = this->data[pos * 2].second\
    \ + this->data[pos * 2 + 1].second;\n    }\n    void reflect_lazy(int pos)\n \
    \   {\n        if (pos < this->head)\n        {\n            overlap_lazy(pos\
    \ * 2, this->lazy[pos]);\n            overlap_lazy(pos * 2 + 1, this->lazy[pos]);\n\
    \        }\n        this->data[pos].first = this->lazy[pos].first * this->data[pos].first\
    \ + this->lazy[pos].second * this->data[pos].second;\n        this->lazy[pos]\
    \ = this->zero_lazy;\n    }\n    void overlap_lazy(int pos, const TLAZY &d)\n\
    \    {\n        this->lazy[pos] = std::make_pair(this->lazy[pos].first * d.first,\
    \ this->lazy[pos].second * d.first + d.second);\n    }\n    T data2ret(int pos,\
    \ const bool &)\n    {\n        return this->data[pos].first;\n    }\n    T merge_ret(const\
    \ T &l, const T &r, const bool &)\n    {\n        return l + r;\n    }\n    RangeAffineRangeSum(const\
    \ std::vector<T> &seq) : SegTree::LazySegmentTree()\n    {\n        std::vector<std::pair<T,\
    \ int>> vinit;\n        for (auto x : seq) vinit.emplace_back(x, 1);\n       \
    \ SegTree::initialize(vinit, std::make_pair(0, 0), std::make_pair(1, 0), T(0));\n\
    \    };\n};\n\nusing mint = ModInt<998244353>;\n\nint main()\n{\n    std::cin.tie(NULL);\n\
    \    std::ios::sync_with_stdio(false);\n\n    int N, Q;\n    std::cin >> N >>\
    \ Q;\n\n    std::vector<mint> A(N);\n    for (auto &a : A) std::cin >> a;\n  \
    \  RangeAffineRangeSum<mint> segtree(A);\n    while (Q--)\n    {\n        int\
    \ q, l, r;\n        std::cin >> q >> l >> r;\n        if (q)\n        {\n    \
    \        std::cout << segtree.get(l, r) << '\\n';\n        }\n        else\n \
    \       {\n            mint b, c;\n            std::cin >> b >> c;\n         \
    \   segtree.update(l, r, std::make_pair(b, c));\n        }\n    }\n}\n"
  code: "#include \"segmenttree/range-update-range-get.hpp\"\n#include \"modulus/modint_fixed.hpp\"\
    \n#include <utility>\n#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n// RangeAffineRangeSum\n// - update: x_i -> a * x_i + b for i in [l, r)\n\
    // - get: return x_l + ... + x_{r - 1}\ntemplate <typename T>\nstruct RangeAffineRangeSum\
    \ : public LazySegmentTree<std::pair<T, int>, std::pair<T, T>, T, bool>\n{\n \
    \   using TDATA = std::pair<T, int>;\n    using TLAZY = std::pair<T, T>;\n   \
    \ using SegTree = LazySegmentTree<TDATA, TLAZY, T, bool>;\n    void merge_data(int\
    \ pos)\n    {\n        this->data[pos].first = this->data[pos * 2].first + this->data[pos\
    \ * 2 + 1].first;\n        this->data[pos].second = this->data[pos * 2].second\
    \ + this->data[pos * 2 + 1].second;\n    }\n    void reflect_lazy(int pos)\n \
    \   {\n        if (pos < this->head)\n        {\n            overlap_lazy(pos\
    \ * 2, this->lazy[pos]);\n            overlap_lazy(pos * 2 + 1, this->lazy[pos]);\n\
    \        }\n        this->data[pos].first = this->lazy[pos].first * this->data[pos].first\
    \ + this->lazy[pos].second * this->data[pos].second;\n        this->lazy[pos]\
    \ = this->zero_lazy;\n    }\n    void overlap_lazy(int pos, const TLAZY &d)\n\
    \    {\n        this->lazy[pos] = std::make_pair(this->lazy[pos].first * d.first,\
    \ this->lazy[pos].second * d.first + d.second);\n    }\n    T data2ret(int pos,\
    \ const bool &)\n    {\n        return this->data[pos].first;\n    }\n    T merge_ret(const\
    \ T &l, const T &r, const bool &)\n    {\n        return l + r;\n    }\n    RangeAffineRangeSum(const\
    \ std::vector<T> &seq) : SegTree::LazySegmentTree()\n    {\n        std::vector<std::pair<T,\
    \ int>> vinit;\n        for (auto x : seq) vinit.emplace_back(x, 1);\n       \
    \ SegTree::initialize(vinit, std::make_pair(0, 0), std::make_pair(1, 0), T(0));\n\
    \    };\n};\n\nusing mint = ModInt<998244353>;\n\nint main()\n{\n    std::cin.tie(NULL);\n\
    \    std::ios::sync_with_stdio(false);\n\n    int N, Q;\n    std::cin >> N >>\
    \ Q;\n\n    std::vector<mint> A(N);\n    for (auto &a : A) std::cin >> a;\n  \
    \  RangeAffineRangeSum<mint> segtree(A);\n    while (Q--)\n    {\n        int\
    \ q, l, r;\n        std::cin >> q >> l >> r;\n        if (q)\n        {\n    \
    \        std::cout << segtree.get(l, r) << '\\n';\n        }\n        else\n \
    \       {\n            mint b, c;\n            std::cin >> b >> c;\n         \
    \   segtree.update(l, r, std::make_pair(b, c));\n        }\n    }\n}\n"
  dependsOn:
  - segmenttree/range-update-range-get.hpp
  - modulus/modint_fixed.hpp
  isVerificationFile: true
  path: segmenttree/test/range-affine-range-sum.test.cpp
  requiredBy: []
  timestamp: '2020-09-04 23:33:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/range-affine-range-sum.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/range-affine-range-sum.test.cpp
- /verify/segmenttree/test/range-affine-range-sum.test.cpp.html
title: segmenttree/test/range-affine-range-sum.test.cpp
---
