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


# :heavy_check_mark: segmenttree/test/range-affine-range-sum.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5fd93d3fa59267c091e036914d93749e">segmenttree/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/test/range-affine-range-sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-19 16:04:51+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_affine_range_sum">https://judge.yosupo.jp/problem/range_affine_range_sum</a>


## Depends on

* :question: <a href="../../../library/modulus/modint_fixed.hpp.html">modulus/modint_fixed.hpp</a>
* :heavy_check_mark: <a href="../../../library/segmenttree/range-update-range-get.hpp.html">segmenttree/range-update-range-get.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "segmenttree/range-update-range-get.hpp"
#include "modulus/modint_fixed.hpp"
#include <utility>
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

// RangeAffineRangeSum
// - update: x_i -> a * x_i + b for i in [l, r)
// - get: return x_l + ... + x_{r - 1}
template <typename T>
struct RangeAffineRangeSum : public LazySegmentTree<std::pair<T, int>, std::pair<T, T>, T, bool>
{
    using TDATA = std::pair<T, int>;
    using TLAZY = std::pair<T, T>;
    using SegTree = LazySegmentTree<TDATA, TLAZY, T, bool>;
    void merge_data(int pos)
    {
        this->data[pos].first = this->data[pos * 2].first + this->data[pos * 2 + 1].first;
        this->data[pos].second = this->data[pos * 2].second + this->data[pos * 2 + 1].second;
    }
    void reflect_lazy(int pos)
    {
        if (pos < this->head)
        {
            overlap_lazy(pos * 2, this->lazy[pos]);
            overlap_lazy(pos * 2 + 1, this->lazy[pos]);
        }
        this->data[pos].first = this->lazy[pos].first * this->data[pos].first + this->lazy[pos].second * this->data[pos].second;
        this->lazy[pos] = this->zero_lazy;
    }
    void overlap_lazy(int pos, const TLAZY &d)
    {
        this->lazy[pos] = std::make_pair(this->lazy[pos].first * d.first, this->lazy[pos].second * d.first + d.second);
    }
    T data2ret(int pos, const bool &)
    {
        return this->data[pos].first;
    }
    T merge_ret(const T &l, const T &r, const bool &)
    {
        return l + r;
    }
    RangeAffineRangeSum(const std::vector<T> &seq) : SegTree::LazySegmentTree()
    {
        std::vector<std::pair<T, int>> vinit;
        for (auto x : seq) vinit.emplace_back(x, 1);
        SegTree::initialize(vinit, std::make_pair(0, 0), std::make_pair(1, 0), T(0));
    };
};

using mint = ModInt<998244353>;

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<mint> A(N);
    for (auto &a : A) std::cin >> a;
    RangeAffineRangeSum<mint> segtree(A);
    while (Q--)
    {
        int q, l, r;
        std::cin >> q >> l >> r;
        if (q)
        {
            std::cout << segtree.get(l, r) << '\n';
        }
        else
        {
            mint b, c;
            std::cin >> b >> c;
            segtree.update(l, r, std::make_pair(b, c));
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "segmenttree/range-update-range-get.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

// CUT begin
template<typename TDATA, typename TLAZY, typename TRET, typename TQUERY>
struct LazySegmentTree
{
    TLAZY zero_lazy;
    TRET zero_ret;
    int N;
    int head;
    std::vector<TDATA> data;
    std::vector<TLAZY> lazy;

    // Here, you have to calculate data[pos] from children (data[l], data[r]),
    // Assumptions: `lazy[pos] = lazy[l] = lazy[r] = zero_lazy`
    virtual void merge_data(int pos) = 0;

    // Here, you must propagate lazy[pos] and update data[pos] by reflecting lazy[pos], without inconsistency
    // After this, lazy[pos] must be zero_lazy.
    virtual void reflect_lazy(int pos) = 0;

    // operate d to lazy[pos] (merge two TLAZY's)
    virtual void overlap_lazy(int pos, const TLAZY &d) = 0;

    // Assumption: `lazy[pos] = zero_lazy`
    virtual TRET data2ret(int pos, const TQUERY &query) = 0;

    virtual TRET merge_ret(const TRET &l, const TRET &r, const TQUERY &query) = 0;

    ////// general description //////
    LazySegmentTree() = default;
    void initialize(const std::vector<TDATA> &data_init, const TDATA &zero_data, const TLAZY &zero_lazy_, const TRET &zero_ret_)
    {
        N = data_init.size();
        head = 1;
        while (head < N) head <<= 1;
        zero_lazy = zero_lazy_;
        zero_ret = zero_ret_;
        data.assign(head * 2, zero_data);
        lazy.assign(head * 2, zero_lazy);
        std::copy(data_init.begin(), data_init.end(), data.begin() + head);
        for (int pos = head; --pos;) merge_data(pos);
    }

    void _update(int begin, int end, const TLAZY &delay, int pos, int l, int r)
    {
        // Operate `delay` to the node pos
        // After this, lazy[pos] MUST be zero so that merge_data() works correctly
        if (begin <= l and r <= end) { // Update whole [l, r) by delay
            overlap_lazy(pos, delay);
            reflect_lazy(pos);
        }
        else if (begin < r and l < end) { // Update somewhere in [l, r)
            reflect_lazy(pos);
            _update(begin, end, delay, pos * 2, l, (l + r) / 2);
            _update(begin, end, delay, pos * 2 + 1, (l + r) / 2, r);
            merge_data(pos);
        }
        else reflect_lazy(pos);
    }

    void update(int begin, int end, const TLAZY &delay) {
        _update(begin, end, delay, 1, 0, head);
    }

    TRET _get(int begin, int end, int pos, int l, int r, const TQUERY &query) // Get value in [begin, end)
    {
        reflect_lazy(pos);
        if (begin <= l and r <= end) return data2ret(pos, query);
        else if (begin < r and l < end) {
            TRET vl = _get(begin, end, pos * 2, l, (l + r) / 2, query);
            TRET vr = _get(begin, end, pos * 2 + 1, (l + r) / 2, r, query);
            return merge_ret(vl, vr, query);
        }
        else return zero_ret;
    }
    TRET get(int begin, int end, const TQUERY &query = NULL)
    {
        return _get(begin, end, 1, 0, head, query);
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
#line 3 "segmenttree/test/range-affine-range-sum.test.cpp"
#include <utility>
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

// RangeAffineRangeSum
// - update: x_i -> a * x_i + b for i in [l, r)
// - get: return x_l + ... + x_{r - 1}
template <typename T>
struct RangeAffineRangeSum : public LazySegmentTree<std::pair<T, int>, std::pair<T, T>, T, bool>
{
    using TDATA = std::pair<T, int>;
    using TLAZY = std::pair<T, T>;
    using SegTree = LazySegmentTree<TDATA, TLAZY, T, bool>;
    void merge_data(int pos)
    {
        this->data[pos].first = this->data[pos * 2].first + this->data[pos * 2 + 1].first;
        this->data[pos].second = this->data[pos * 2].second + this->data[pos * 2 + 1].second;
    }
    void reflect_lazy(int pos)
    {
        if (pos < this->head)
        {
            overlap_lazy(pos * 2, this->lazy[pos]);
            overlap_lazy(pos * 2 + 1, this->lazy[pos]);
        }
        this->data[pos].first = this->lazy[pos].first * this->data[pos].first + this->lazy[pos].second * this->data[pos].second;
        this->lazy[pos] = this->zero_lazy;
    }
    void overlap_lazy(int pos, const TLAZY &d)
    {
        this->lazy[pos] = std::make_pair(this->lazy[pos].first * d.first, this->lazy[pos].second * d.first + d.second);
    }
    T data2ret(int pos, const bool &)
    {
        return this->data[pos].first;
    }
    T merge_ret(const T &l, const T &r, const bool &)
    {
        return l + r;
    }
    RangeAffineRangeSum(const std::vector<T> &seq) : SegTree::LazySegmentTree()
    {
        std::vector<std::pair<T, int>> vinit;
        for (auto x : seq) vinit.emplace_back(x, 1);
        SegTree::initialize(vinit, std::make_pair(0, 0), std::make_pair(1, 0), T(0));
    };
};

using mint = ModInt<998244353>;

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<mint> A(N);
    for (auto &a : A) std::cin >> a;
    RangeAffineRangeSum<mint> segtree(A);
    while (Q--)
    {
        int q, l, r;
        std::cin >> q >> l >> r;
        if (q)
        {
            std::cout << segtree.get(l, r) << '\n';
        }
        else
        {
            mint b, c;
            std::cin >> b >> c;
            segtree.update(l, r, std::make_pair(b, c));
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

