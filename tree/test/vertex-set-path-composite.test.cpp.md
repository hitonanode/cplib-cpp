---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: segmenttree/point-update-range-get_nonrecursive.hpp
    title: segmenttree/point-update-range-get_nonrecursive.hpp
  - icon: ':heavy_check_mark:'
    path: tree/heavy_light_decomposition.hpp
    title: "Heavy-light decomposition \uFF08HLD, \u6728\u306E\u91CD\u8EFD\u5206\u89E3\
      \uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/vertex_set_path_composite
  bundledCode: "#line 1 \"tree/test/vertex-set-path-composite.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\n#line\
    \ 2 \"modint.hpp\"\n#include <cassert>\n#include <iostream>\n#include <set>\n\
    #include <vector>\n\ntemplate <int md> struct ModInt {\n    static_assert(md >\
    \ 1);\n    using lint = long long;\n    constexpr static int mod() { return md;\
    \ }\n    static int get_primitive_root() {\n        static int primitive_root\
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
    #line 2 \"segmenttree/point-update-range-get_nonrecursive.hpp\"\n#include <algorithm>\n\
    #line 4 \"segmenttree/point-update-range-get_nonrecursive.hpp\"\n#include <functional>\n\
    #line 6 \"segmenttree/point-update-range-get_nonrecursive.hpp\"\n#include <stack>\n\
    #line 8 \"segmenttree/point-update-range-get_nonrecursive.hpp\"\n\n// CUT begin\n\
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
    \ {\n        SegTree::initialize(seq, defaultmin);\n    };\n};\n\ntemplate <typename\
    \ T> struct PointUpdateRangeSum : public NonrecursiveSegmentTree<T, T, bool> {\n\
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
    \ 5 \"tree/heavy_light_decomposition.hpp\"\n#include <queue>\n#line 7 \"tree/heavy_light_decomposition.hpp\"\
    \n#include <utility>\n#line 9 \"tree/heavy_light_decomposition.hpp\"\n\n// Heavy-light\
    \ decomposition of trees (forest)\n// Based on http://beet-aizu.hatenablog.com/entry/2017/12/12/235950\n\
    struct heavy_light_decomposition {\n    int V;\n    int k;\n    std::vector<std::vector<int>>\
    \ e;\n    std::vector<int> par;         // par[i] = parent of vertex i (Default:\
    \ -1)\n    std::vector<int> depth;       // depth[i] = distance between root and\
    \ vertex i\n    std::vector<int> subtree_sz;  // subtree_sz[i] = size of subtree\
    \ whose root is i\n    std::vector<int> heavy_child; // heavy_child[i] = child\
    \ of vertex i on heavy path (Default: -1)\n    std::vector<int> tree_id;     //\
    \ tree_id[i] = id of tree vertex i belongs to\n    // subtree_begin[i] = aligned\
    \ id for vertex i (consecutive on heavy edges)\n    std::vector<int> subtree_begin,\
    \ subtree_end;\n    std::vector<int> vis_order; // vis_order[subtree_begin[i]]\
    \ = i\n    std::vector<int> head; // head[i] = id of vertex on heavy path of vertex\
    \ i, nearest to root\n\n    heavy_light_decomposition(int n, const std::vector<std::pair<int,\
    \ int>> &edges)\n        : V(n), k(0), e(n), par(n), depth(n), subtree_sz(n),\
    \ heavy_child(n), tree_id(n, -1),\n          subtree_begin(n), subtree_end(n),\
    \ vis_order(0), head(n) {\n        for (auto [u, v] : edges) {\n            assert(u\
    \ != v);\n            e.at(u).emplace_back(v);\n            e.at(v).emplace_back(u);\n\
    \        }\n    }\n\n    void _build_dfs_1(int root) {\n        std::vector<std::pair<int,\
    \ int>> st;\n        par[root] = -1;\n        depth[root] = 0;\n        st.emplace_back(root,\
    \ 0);\n        while (!st.empty()) {\n            int now = st.back().first;\n\
    \            int &i = st.back().second;\n            if (i < (int)e[now].size())\
    \ {\n                int nxt = e[now][i++];\n                if (nxt == par[now])\
    \ continue;\n                par[nxt] = now;\n                depth[nxt] = depth[now]\
    \ + 1;\n                st.emplace_back(nxt, 0);\n            } else {\n     \
    \           st.pop_back();\n                int max_sub_sz = 0;\n            \
    \    subtree_sz[now] = 1;\n                heavy_child[now] = -1;\n          \
    \      for (auto nxt : e[now]) {\n                    if (nxt == par[now]) continue;\n\
    \                    subtree_sz[now] += subtree_sz[nxt];\n                   \
    \ if (max_sub_sz < subtree_sz[nxt]) {\n                        max_sub_sz = subtree_sz[nxt],\
    \ heavy_child[now] = nxt;\n                    }\n                }\n        \
    \    }\n        }\n    }\n\n    void _build_dfs_2(int now, int tree_id_now) {\n\
    \        std::vector<std::pair<int, bool>> st;\n        st.emplace_back(now, true);\n\
    \        head[now] = now;\n\n        while (!st.empty()) {\n            auto [now,\
    \ mode] = st.back();\n            st.pop_back();\n\n            if (mode) {\n\
    \                tree_id[now] = tree_id_now;\n                subtree_begin[now]\
    \ = k++;\n                vis_order.push_back(now);\n\n                st.emplace_back(now,\
    \ false);\n\n                for (int nxt : e[now]) {\n                    if\
    \ (nxt == par[now] or nxt == heavy_child[now]) continue;\n                   \
    \ head[nxt] = nxt;\n                    st.emplace_back(nxt, true);\n        \
    \        }\n\n                if (heavy_child[now] != -1) {\n                \
    \    head[heavy_child[now]] = head[now];\n                    st.emplace_back(heavy_child[now],\
    \ true);\n                }\n            } else {\n                subtree_end[now]\
    \ = k;\n            }\n        }\n    }\n\n    void build(std::vector<int> roots\
    \ = {0}) {\n        int tree_id_now = 0;\n        for (int r : roots) {\n    \
    \        _build_dfs_1(r);\n            _build_dfs_2(r, tree_id_now++);\n     \
    \   }\n    }\n\n    template <class T> std::vector<T> segtree_rearrange(const\
    \ std::vector<T> &data) const {\n        assert(int(data.size()) == V);\n    \
    \    std::vector<T> ret;\n        ret.reserve(vis_order.size());\n        for\
    \ (int v : vis_order) ret.emplace_back(data[v]);\n        return ret;\n    }\n\
    \n    void for_vertex(int u, const std::function<void(int)> &f) const { f(subtree_begin[u]);\
    \ }\n\n    // query for vertices on path [u, v] (INCLUSIVE)\n    void\n    for_each_vertex(int\
    \ u, int v, const std::function<void(int ancestor, int descendant)> &f) const\
    \ {\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            f(std::max(subtree_begin[head[v]], subtree_begin[u]),\
    \ subtree_begin[v]);\n            if (head[u] == head[v]) break;\n           \
    \ v = par[head[v]];\n        }\n    }\n\n    void for_each_vertex_noncommutative(\n\
    \        int from, int to, const std::function<void(int ancestor, int descendant)>\
    \ &fup,\n        const std::function<void(int ancestor, int descendant)> &fdown)\
    \ const {\n        int u = from, v = to;\n        const int lca = lowest_common_ancestor(u,\
    \ v), dlca = depth[lca];\n        while (u >= 0 and depth[u] > dlca) {\n     \
    \       const int p = (depth[head[u]] > dlca ? head[u] : lca);\n            fup(subtree_begin[p]\
    \ + (p == lca), subtree_begin[u]), u = par[p];\n        }\n        static std::vector<std::pair<int,\
    \ int>> lrs;\n        int sz = 0;\n        while (v >= 0 and depth[v] >= dlca)\
    \ {\n            const int p = (depth[head[v]] >= dlca ? head[v] : lca);\n   \
    \         if (int(lrs.size()) == sz) lrs.emplace_back(0, 0);\n            lrs.at(sz++)\
    \ = {p, v}, v = par.at(p);\n        }\n        while (sz--) fdown(subtree_begin[lrs.at(sz).first],\
    \ subtree_begin[lrs.at(sz).second]);\n    }\n\n    // query for edges on path\
    \ [u, v]\n    void for_each_edge(int u, int v, const std::function<void(int, int)>\
    \ &f) const {\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            if (head[u] != head[v]) {\n                f(subtree_begin[head[v]],\
    \ subtree_begin[v]);\n                v = par[head[v]];\n            } else {\n\
    \                if (u != v) f(subtree_begin[u] + 1, subtree_begin[v]);\n    \
    \            break;\n            }\n        }\n    }\n\n    // query for vertices\
    \ in subtree rooted at u\n    void for_subtree(int u, const std::function<void(int,\
    \ int)> &f) const {\n        f(subtree_begin[u], subtree_end[u] - 1);\n    }\n\
    \n    // lowest_common_ancestor: O(log V)\n    int lowest_common_ancestor(int\
    \ u, int v) const {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >=\
    \ 0);\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            if (head[u] == head[v]) return u;\n          \
    \  v = par[head[v]];\n        }\n    }\n\n    int distance(int u, int v) const\
    \ {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >= 0);\n        return\
    \ depth[u] + depth[v] - 2 * depth[lowest_common_ancestor(u, v)];\n    }\n\n  \
    \  // Level ancestor, O(log V)\n    // if k-th parent is out of range, return\
    \ -1\n    int kth_parent(int v, int k) const {\n        if (k < 0) return -1;\n\
    \        while (v >= 0) {\n            int h = head.at(v), len = depth.at(v) -\
    \ depth.at(h);\n            if (k <= len) return vis_order.at(subtree_begin.at(v)\
    \ - k);\n            k -= len + 1, v = par.at(h);\n        }\n        return -1;\n\
    \    }\n\n    // Jump on tree, O(log V)\n    int s_to_t_by_k_steps(int s, int\
    \ t, int k) const {\n        if (k < 0) return -1;\n        if (k == 0) return\
    \ s;\n        int lca = lowest_common_ancestor(s, t);\n        if (k <= depth.at(s)\
    \ - depth.at(lca)) return kth_parent(s, k);\n        return kth_parent(t, depth.at(s)\
    \ + depth.at(t) - depth.at(lca) * 2 - k);\n    }\n};\n#line 7 \"tree/test/vertex-set-path-composite.test.cpp\"\
    \nusing namespace std;\nusing mint = ModInt<998244353>;\n\nusing P = pair<mint,\
    \ mint>;\nstruct PointSetRangeComposite : public NonrecursiveSegmentTree<P, P,\
    \ bool> {\n    using SegTree = NonrecursiveSegmentTree<P, P, bool>;\n    P merge_data(const\
    \ P &vl, const P &vr) override {\n        return make_pair(vl.first * vr.first,\
    \ vr.first * vl.second + vr.second);\n    };\n    P data2ret(const P &v, const\
    \ bool &q) override { return v; }\n    P merge_ret(const P &vl, const P &vr) override\
    \ { return merge_data(vl, vr); };\n    PointSetRangeComposite(const std::vector<P>\
    \ &seq, P zero)\n        : SegTree::NonrecursiveSegmentTree() {\n        SegTree::initialize(seq,\
    \ zero);\n    };\n};\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    cin >> N >> Q;\n    vector<P> V(N);\n    for (auto &x : V)\
    \ cin >> x.first >> x.second;\n\n    vector<pair<int, int>> edges(N - 1);\n  \
    \  for (auto &[u, v] : edges) cin >> u >> v;\n\n    heavy_light_decomposition\
    \ hld(N, edges);\n    hld.build();\n    vector<P> stinit = hld.segtree_rearrange(V);\n\
    \n    PointSetRangeComposite segtree(stinit, P{1, 0});\n    reverse(stinit.begin(),\
    \ stinit.end());\n    PointSetRangeComposite segtreeinv(stinit, P{1, 0});\n  \
    \  while (Q--) {\n        int q, u, v, x;\n        cin >> q >> u >> v >> x;\n\
    \        if (q == 0) {\n            segtree.update(hld.subtree_begin[u], P{v,\
    \ x});\n            segtreeinv.update(N - 1 - hld.subtree_begin[u], P{v, x});\n\
    \        } else {\n            mint ret = x;\n            hld.for_each_vertex_noncommutative(\n\
    \                u, v,\n                [&](int l, int r) -> void {\n        \
    \            assert(0 <= l and l <= r and r < N);\n                    P tmp =\
    \ segtreeinv.get(N - 1 - r, N - 1 - l + 1);\n                    ret = tmp.first\
    \ * ret + tmp.second;\n                },\n                [&](int l, int r) ->\
    \ void {\n                    assert(0 <= l and l <= r and r < N);\n         \
    \           P tmp = segtree.get(l, r + 1);\n                    ret = tmp.first\
    \ * ret + tmp.second;\n                });\n            cout << ret << '\\n';\n\
    \        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
    \n#include \"../../modint.hpp\"\n#include \"../../segmenttree/point-update-range-get_nonrecursive.hpp\"\
    \n#include \"../heavy_light_decomposition.hpp\"\n#include <iostream>\n#include\
    \ <vector>\nusing namespace std;\nusing mint = ModInt<998244353>;\n\nusing P =\
    \ pair<mint, mint>;\nstruct PointSetRangeComposite : public NonrecursiveSegmentTree<P,\
    \ P, bool> {\n    using SegTree = NonrecursiveSegmentTree<P, P, bool>;\n    P\
    \ merge_data(const P &vl, const P &vr) override {\n        return make_pair(vl.first\
    \ * vr.first, vr.first * vl.second + vr.second);\n    };\n    P data2ret(const\
    \ P &v, const bool &q) override { return v; }\n    P merge_ret(const P &vl, const\
    \ P &vr) override { return merge_data(vl, vr); };\n    PointSetRangeComposite(const\
    \ std::vector<P> &seq, P zero)\n        : SegTree::NonrecursiveSegmentTree() {\n\
    \        SegTree::initialize(seq, zero);\n    };\n};\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int N, Q;\n    cin >> N >> Q;\n    vector<P>\
    \ V(N);\n    for (auto &x : V) cin >> x.first >> x.second;\n\n    vector<pair<int,\
    \ int>> edges(N - 1);\n    for (auto &[u, v] : edges) cin >> u >> v;\n\n    heavy_light_decomposition\
    \ hld(N, edges);\n    hld.build();\n    vector<P> stinit = hld.segtree_rearrange(V);\n\
    \n    PointSetRangeComposite segtree(stinit, P{1, 0});\n    reverse(stinit.begin(),\
    \ stinit.end());\n    PointSetRangeComposite segtreeinv(stinit, P{1, 0});\n  \
    \  while (Q--) {\n        int q, u, v, x;\n        cin >> q >> u >> v >> x;\n\
    \        if (q == 0) {\n            segtree.update(hld.subtree_begin[u], P{v,\
    \ x});\n            segtreeinv.update(N - 1 - hld.subtree_begin[u], P{v, x});\n\
    \        } else {\n            mint ret = x;\n            hld.for_each_vertex_noncommutative(\n\
    \                u, v,\n                [&](int l, int r) -> void {\n        \
    \            assert(0 <= l and l <= r and r < N);\n                    P tmp =\
    \ segtreeinv.get(N - 1 - r, N - 1 - l + 1);\n                    ret = tmp.first\
    \ * ret + tmp.second;\n                },\n                [&](int l, int r) ->\
    \ void {\n                    assert(0 <= l and l <= r and r < N);\n         \
    \           P tmp = segtree.get(l, r + 1);\n                    ret = tmp.first\
    \ * ret + tmp.second;\n                });\n            cout << ret << '\\n';\n\
    \        }\n    }\n}\n"
  dependsOn:
  - modint.hpp
  - segmenttree/point-update-range-get_nonrecursive.hpp
  - tree/heavy_light_decomposition.hpp
  isVerificationFile: true
  path: tree/test/vertex-set-path-composite.test.cpp
  requiredBy: []
  timestamp: '2025-08-25 00:44:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/vertex-set-path-composite.test.cpp
layout: document
redirect_from:
- /verify/tree/test/vertex-set-path-composite.test.cpp
- /verify/tree/test/vertex-set-path-composite.test.cpp.html
title: tree/test/vertex-set-path-composite.test.cpp
---
