---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: segmenttree/test/point-set-range-composite.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5fd93d3fa59267c091e036914d93749e">segmenttree/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/test/point-set-range-composite.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-19 16:04:51+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_set_range_composite">https://judge.yosupo.jp/problem/point_set_range_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/modulus/modint_fixed.hpp.html">modulus/modint_fixed.hpp</a>
* :heavy_check_mark: <a href="../../../library/segmenttree/point-update-range-get_nonrecursive.hpp.html">segmenttree/point-update-range-get_nonrecursive.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "segmenttree/point-update-range-get_nonrecursive.hpp"
#include "modulus/modint_fixed.hpp"
#include <iostream>
#include <utility>
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
using mint = ModInt<998244353>;

template <typename T>
struct PointSetRangeComposite : public NonrecursiveSegmentTree<std::pair<T, T>, std::pair<T, T>, bool>
{
    using T_NODE = std::pair<T, T>;
    using SegTree = NonrecursiveSegmentTree<T_NODE, T_NODE, bool>;
    T_NODE merge_data(const T_NODE &vl, const T_NODE &vr) override { return std::make_pair(vl.first * vr.first, vr.first * vl.second + vr.second); };
    T_NODE data2ret(const T_NODE &v, const bool &q) override { return v; }
    T_NODE merge_ret(const T_NODE &vl, const T_NODE &vr) override { return merge_data(vl, vr); };
    PointSetRangeComposite(const std::vector<T_NODE> &seq) : SegTree::NonrecursiveSegmentTree()
    {
        SegTree::initialize(seq, T_NODE(1, 0));
    };
};

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<std::pair<mint, mint>> A(N);
    for (auto &p : A)
    {
        std::cin >> p.first >> p.second;
    }
    PointSetRangeComposite<mint> s(A);
    while (Q--)
    {
        int q, l, r, x;
        std::cin >> q >> l >> r >> x;
        if (q)
        {
            auto ret = s.get(l, r);
            std::cout << ret.first * x + ret.second << '\n';
        }
        else
        {
            s.update(l, std::make_pair(r, x));
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "segmenttree/point-update-range-get_nonrecursive.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

// CUT begin
// Nonrecursive Segment Tree (point-update, range-get)
// - Conditions for operations:
//   - merge_data: [TDATA, TDATA] -> TDATA, e(x, y) == e(y, x)
//   - data2ret: [TDATA, TQUERY] -> TRET
//   - merge_ret: [TRET, TRET] -> TRET, g(defaultRET, x) == x, g(x, y) = g(y, x)
//   - commutability f(e(x, y), q) == g(f(x, q), f(y, q))
template <typename TDATA, typename TRET, typename TQUERY>
struct NonrecursiveSegmentTree
{
    int N;
    TRET defaultRET;
    virtual TDATA merge_data(const TDATA &, const TDATA &) = 0;
    virtual TRET data2ret(const TDATA &, const TQUERY &) = 0;
    virtual TRET merge_ret(const TRET &, const TRET &) = 0;
    std::vector<TDATA> data;
    inline TDATA& at(int i) { return data[i]; }

    inline void _merge(int i) { at(i) = merge_data(at(i << 1), at((i << 1) + 1)); }
    void initialize(const std::vector<TDATA> &seq, TRET RET_ZERO) {
        N = seq.size();
        defaultRET = RET_ZERO;
        data = seq;
        data.insert(data.end(), seq.begin(), seq.end());
        for (int i = N - 1; i; i--) _merge(i);
    }
    NonrecursiveSegmentTree() = default;
    void update(int pos, const TDATA &x) {
        assert(pos >= 0 and pos < N);
        at(pos + N) = x;
        for (int i = pos + N; i > 1;) i >>= 1, _merge(i);
    }

    // [l, r), 0-indexed
    TRET get(int l, int r, TQUERY query = NULL) {
        assert(l >= 0 and r <= N);
        TRET retl = defaultRET, retr = defaultRET;
        l += N, r += N;
        while (l < r) {
            if (l & 1) retl = merge_ret(retl, data2ret(data[l++], query));
            if (r & 1) retr = merge_ret(data2ret(data[--r], query), retr);
            l >>= 1, r >>= 1;
        }
        return merge_ret(retl, retr);
    }

    // Calculate smallest r that satisfies g(f(x_l, q), ..., f(x_{r - 1}, q)) >= threshold
    // Assumption: Monotonicity of g(x_l, ..., x_r) about r (l: fixed)
    // Complexity: O(log N)
    int binary_search(int l, const TRET &threshold, TQUERY query = NULL) {
        std::stack<int> rs;
        l += N;
        int r = N * 2;
        TRET retl = defaultRET;
        if (threshold <= retl) return l - N;
        while (l < r) {
            if (l & 1) {
                TRET ret_tmp = merge_ret(retl, data2ret(data[l], query));
                if (threshold <= ret_tmp) {
                    while (l * 2 < N * 2) {
                        ret_tmp = merge_ret(retl, data2ret(data[l * 2], query));
                        if (threshold <= ret_tmp) l *= 2;
                        else retl = ret_tmp, l = l * 2 + 1;
                    }
                    return l - N;
                }
                l++;
                retl = ret_tmp;
            }
            if (r & 1) rs.push(--r);
            l >>= 1, r >>= 1;
        }
        while (!rs.empty()) {
            l = rs.top();
            rs.pop();
            TRET ret_tmp = merge_ret(retl, data2ret(data[l], query));
            if (threshold <= ret_tmp) {
                while (l * 2 < N * 2) {
                    ret_tmp = merge_ret(retl, data2ret(data[l * 2], query));
                    if (threshold <= ret_tmp) l *= 2;
                    else retl = ret_tmp, l = l * 2 + 1;
                }
                return l - N;
            }
            retl = ret_tmp;
        }
        return N;
    }

    template<typename T1, typename T2, typename T3>
    friend std::ostream &operator<<(std::ostream &os, NonrecursiveSegmentTree<T1, T2, T3> s) {
        os << "[SegmentTree (len: " << s.N << ')';
        for (int i = 0; i < s.N; i++) os << s.at(i + s.N) << ',';
        os << "]";
        return os;
    }
};


// Range Minimum Query
// - get: return min(x_l, ..., x_{r - 1})
template <typename T>
struct RangeMinimumQuery : public NonrecursiveSegmentTree<T, T, bool>
{
    using SegTree = NonrecursiveSegmentTree<T, T, bool>;
    T merge_data(const T &vl, const T &vr) override { return std::min(vl, vr); };
    T data2ret(const T &v, const bool &q) override { return v; }
    T merge_ret(const T &vl, const T &vr) override { return std::min(vl, vr); };
    RangeMinimumQuery(const std::vector<T> &seq, T defaultmin) : SegTree::NonrecursiveSegmentTree() {
        SegTree::initialize(seq, defaultmin);
    };
};

// Range Maximum Query
// - get: return max(x_l, ..., x_{r - 1})
template <typename T>
struct RangeMaximumQuery : public NonrecursiveSegmentTree<T, T, bool>
{
    using SegTree = NonrecursiveSegmentTree<T, T, bool>;
    T merge_data(const T &vl, const T &vr) override { return std::max(vl, vr); };
    T data2ret(const T &v, const bool &q) override { return v; }
    T merge_ret(const T &vl, const T &vr) override { return std::max(vl, vr); };
    RangeMaximumQuery(const std::vector<T> &seq, T defaultmax) : SegTree::NonrecursiveSegmentTree() {
        SegTree::initialize(seq, defaultmax);
    };
};

template <typename T>
struct PointUpdateRangeSum : public NonrecursiveSegmentTree<T, T, bool>
{
    using SegTree = NonrecursiveSegmentTree<T, T, bool>;
    T merge_data(const T &vl, const T &vr) override { return vl + vr; };
    T data2ret(const T &v, const bool &q) override { return v; }
    T merge_ret(const T &vl, const T &vr) override { return vl + vr; };
    PointUpdateRangeSum(const std::vector<T> &seq, T zero) : SegTree::NonrecursiveSegmentTree() {
        SegTree::initialize(seq, zero);
    };
};

// Range Counting less than q Query
// - get: return (#{i | l <= i < r, x_i < q}, total sum of them).
template <typename T>
struct CountAndSumLessThan : public NonrecursiveSegmentTree<std::vector<std::pair<T, T>>, std::pair<int, T>, T>
{
    using TDATA = std::vector<std::pair<T, T>>;
    using TRET = std::pair<int, T>;
    using TQUERY = T;
    TDATA merge_data(const TDATA &vl, const TDATA &vr) override {
        TDATA ret = vl;
        ret.insert(ret.end(), vr.begin(), vr.end());
        std::sort(ret.begin(), ret.end());
        if (ret.size()) {
            ret[0].second = ret[0].first;
            for (size_t i = 1; i < ret.size(); i++) ret[i].second = ret[i - 1].second + ret[i].first;
        }
        return ret;
    }
    TRET data2ret(const TDATA &vec, const TQUERY &q) override {
        int i = std::lower_bound(vec.begin(), vec.end(), std::make_pair(q, q)) - vec.begin();
        if (!i) return std::make_pair(0, 0);
        else return std::make_pair(i, vec[i - 1].second);
    }
    TRET merge_ret(const TRET &l, const TRET &r) override {
        return std::make_pair(l.first + r.first, l.second + r.second);
    }
    using SegTree = NonrecursiveSegmentTree<TDATA, TRET, TQUERY>;
    CountAndSumLessThan(const std::vector<T> &seq) : SegTree::NonrecursiveSegmentTree(){
        std::vector<TDATA> init;
        for (auto x : seq) init.emplace_back(TDATA{std::pair<T, T>(x, x)});
        SegTree::initialize(init, TRET(0, 0));
    }
};
#line 4 "modulus/modint_fixed.hpp"
#include <set>

// CUT begin
template <int mod>
struct ModInt
{
    using lint = long long;
    static int get_mod() { return mod; }
    static int get_primitive_root() {
        static int primitive_root = 0;
        if (!primitive_root) {
            primitive_root = [&](){
                std::set<int> fac;
                int v = mod - 1;
                for (lint i = 2; i * i <= v; i++) while (v % i == 0) fac.insert(i), v /= i;
                if (v > 1) fac.insert(v);
                for (int g = 1; g < mod; g++) {
                    bool ok = true;
                    for (auto i : fac) if (ModInt(g).power((mod - 1) / i) == 1) { ok = false; break; }
                    if (ok) return g;
                }
                return -1;
            }();
        }
        return primitive_root;
    }
    int val;
    constexpr ModInt() : val(0) {}
    constexpr ModInt &_setval(lint v) { val = (v >= mod ? v - mod : v); return *this; }
    constexpr ModInt(lint v) { _setval(v % mod + mod); }
    explicit operator bool() const { return val != 0; }
    constexpr ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val + x.val); }
    constexpr ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val - x.val + mod); }
    constexpr ModInt operator*(const ModInt &x) const { return ModInt()._setval((lint)val * x.val % mod); }
    constexpr ModInt operator/(const ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % mod); }
    constexpr ModInt operator-() const { return ModInt()._setval(mod - val); }
    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this + x; }
    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this - x; }
    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this * x; }
    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this / x; }
    friend constexpr ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a % mod + x.val); }
    friend constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt()._setval(a % mod - x.val + mod); }
    friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt()._setval(a % mod * x.val % mod); }
    friend constexpr ModInt operator/(lint a, const ModInt &x) { return ModInt()._setval(a % mod * x.inv() % mod); }
    constexpr bool operator==(const ModInt &x) const { return val == x.val; }
    constexpr bool operator!=(const ModInt &x) const { return val != x.val; }
    bool operator<(const ModInt &x) const { return val < x.val; }  // To use std::map<ModInt, T>
    friend std::istream &operator>>(std::istream &is, ModInt &x) { lint t; is >> t; x = ModInt(t); return is; }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { os << x.val;  return os; }
    constexpr lint power(lint n) const {
        lint ans = 1, tmp = this->val;
        while (n) {
            if (n & 1) ans = ans * tmp % mod;
            tmp = tmp * tmp % mod;
            n /= 2;
        }
        return ans;
    }
    constexpr lint inv() const { return this->power(mod - 2); }
    constexpr ModInt operator^(lint n) const { return ModInt(this->power(n)); }
    constexpr ModInt &operator^=(lint n) { return *this = *this ^ n; }

    inline ModInt fac() const {
        static std::vector<ModInt> facs;
        int l0 = facs.size();
        if (l0 > this->val) return facs[this->val];

        facs.resize(this->val + 1);
        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1) : facs[i - 1] * ModInt(i));
        return facs[this->val];
    }

    ModInt doublefac() const {
        lint k = (this->val + 1) / 2;
        if (this->val & 1) return ModInt(k * 2).fac() / ModInt(2).power(k) / ModInt(k).fac();
        else return ModInt(k).fac() * ModInt(2).power(k);
    }

    ModInt nCr(const ModInt &r) const {
        if (this->val < r.val) return ModInt(0);
        return this->fac() / ((*this - r).fac() * r.fac());
    }

    ModInt sqrt() const {
        if (val == 0) return 0;
        if (mod == 2) return val;
        if (power((mod - 1) / 2) != 1) return 0;
        ModInt b = 1;
        while (b.power((mod - 1) / 2) == 1) b += 1;
        int e = 0, m = mod - 1;
        while (m % 2 == 0) m >>= 1, e++;
        ModInt x = power((m - 1) / 2), y = (*this) * x * x;
        x *= (*this);
        ModInt z = b.power(m);
        while (y != 1) {
            int j = 0;
            ModInt t = y;
            while (t != 1) j++, t *= t;
            z = z.power(1LL << (e - j - 1));
            x *= z, z *= z, y *= z;
            e = j;
        }
        return ModInt(std::min(x.val, mod - x.val));
    }
};

// constexpr lint MOD = 998244353;
// using mint = ModInt<MOD>;
#line 4 "segmenttree/test/point-set-range-composite.test.cpp"
#include <utility>
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
using mint = ModInt<998244353>;

template <typename T>
struct PointSetRangeComposite : public NonrecursiveSegmentTree<std::pair<T, T>, std::pair<T, T>, bool>
{
    using T_NODE = std::pair<T, T>;
    using SegTree = NonrecursiveSegmentTree<T_NODE, T_NODE, bool>;
    T_NODE merge_data(const T_NODE &vl, const T_NODE &vr) override { return std::make_pair(vl.first * vr.first, vr.first * vl.second + vr.second); };
    T_NODE data2ret(const T_NODE &v, const bool &q) override { return v; }
    T_NODE merge_ret(const T_NODE &vl, const T_NODE &vr) override { return merge_data(vl, vr); };
    PointSetRangeComposite(const std::vector<T_NODE> &seq) : SegTree::NonrecursiveSegmentTree()
    {
        SegTree::initialize(seq, T_NODE(1, 0));
    };
};

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<std::pair<mint, mint>> A(N);
    for (auto &p : A)
    {
        std::cin >> p.first >> p.second;
    }
    PointSetRangeComposite<mint> s(A);
    while (Q--)
    {
        int q, l, r, x;
        std::cin >> q >> l >> r >> x;
        if (q)
        {
            auto ret = s.get(l, r);
            std::cout << ret.first * x + ret.second << '\n';
        }
        else
        {
            s.update(l, std::make_pair(r, x));
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

