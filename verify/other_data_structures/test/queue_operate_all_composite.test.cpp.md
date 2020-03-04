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


# :heavy_check_mark: other_data_structures/test/queue_operate_all_composite.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/other_data_structures/test/queue_operate_all_composite.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-24 18:37:52+09:00


* see: <a href="https://judge.yosupo.jp/problem/queue_operate_all_composite">https://judge.yosupo.jp/problem/queue_operate_all_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/modulus/modint_fixed.hpp.html">modulus/modint_fixed.hpp</a>
* :heavy_check_mark: <a href="../../../library/other_data_structures/sliding_window_aggregation.hpp.html">other_data_structures/sliding_window_aggregation.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other_data_structures/sliding_window_aggregation.hpp"
#include "modulus/modint_fixed.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include <iostream>

using mint = ModInt<998244353>;
int main()
{
    LinearFunctionQueue<mint> swag;
    int Q;
    cin >> Q;
    while (Q--) {
        int q;
        cin >> q;
        if (q == 0) {
            mint a, b;
            cin >> a >> b;
            swag.push({a, b});
        }
        if (q == 1) swag.pop();
        if (q == 2) {
            mint x;
            cin >> x;
            pair<mint, mint> f = swag.fold_all();
            printf("%d\n", (f.first * x + f.second).val);
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other_data_structures/sliding_window_aggregation.hpp"
#include <stack>
#include <utility>
using namespace std;


// Sliding-Window Aggregation based queue
// - `std::queue`-like data structure with monoid operation
// - Each operation is amortized O(1)
// - Verification: <https://www.hackerrank.com/contests/tsg-live-4-programming-contest/challenges/tsg-live-4-procon-lcm-interval/submissions/code/1317888077>
// - Reference: <https://github.com/NiMiLib/NoshiMochiLibrary/blob/queue_aggregation/lib/data_structure/sequence/queue_aggregation.hpp>
template<typename T_VAL, typename T_PROD, typename VAL2PROD, typename MERGE>
struct SlidingWindowAggregation
{
    stack<pair<T_VAL, T_PROD>> front_stack, back_stack;
    VAL2PROD val2prod;
    MERGE merge;
    T_PROD ID_;

    SlidingWindowAggregation(VAL2PROD v2p, MERGE pp2p, T_PROD id_prod)
        : val2prod(v2p), merge(pp2p), ID_(id_prod) {}
    bool empty() const { return front_stack.empty() and back_stack.empty(); }
    int size() const { return front_stack.size() + back_stack.size(); }
    T_PROD fold_all() const {
        if (empty()) return ID_;
        else if (front_stack.empty()) return back_stack.top().second;
        else if (back_stack.empty()) return front_stack.top().second;
        else return merge(front_stack.top().second, back_stack.top().second);
    }
    void push(const T_VAL &x) {
        if (back_stack.empty()) back_stack.emplace(x, val2prod(x));
        else back_stack.emplace(x, merge(back_stack.top().second, val2prod(x)));
    }
    T_VAL pop() {
        if (front_stack.empty()) {
            front_stack.emplace(back_stack.top().first, val2prod(back_stack.top().first));
            back_stack.pop();
            while (!back_stack.empty()) {
                T_VAL t = back_stack.top().first;
                front_stack.emplace(t, merge(val2prod(t), front_stack.top().second));
                back_stack.pop();
            }
        }
        T_VAL t = front_stack.top().first;
        front_stack.pop();
        return t;
    }
};

auto swag_op_id = [](auto x) { return x; };
auto swag_op_linear_merge = [](auto l, auto r) { return make_pair(l.first * r.first, l.second * r.first + r.second); };

// Linear function composition
// `f(x) = first * x + second`, operate most recently added function first
template <typename T>
struct LinearFunctionQueue : public SlidingWindowAggregation<pair<T, T>, pair<T, T>, decltype(swag_op_id), decltype(swag_op_linear_merge)>
{
    LinearFunctionQueue() : SlidingWindowAggregation<pair<T, T>, pair<T, T>, decltype(swag_op_id), decltype(swag_op_linear_merge)>::SlidingWindowAggregation(swag_op_id, swag_op_linear_merge, pair<T, T>(1, 0)) {}
};
#line 2 "modulus/modint_fixed.hpp"
#include <iostream>
#include <vector>
#include <set>

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
#line 3 "other_data_structures/test/queue_operate_all_composite.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include <iostream>

using mint = ModInt<998244353>;
int main()
{
    LinearFunctionQueue<mint> swag;
    int Q;
    cin >> Q;
    while (Q--) {
        int q;
        cin >> q;
        if (q == 0) {
            mint a, b;
            cin >> a >> b;
            swag.push({a, b});
        }
        if (q == 1) swag.pop();
        if (q == 2) {
            mint x;
            cin >> x;
            pair<mint, mint> f = swag.fold_all();
            printf("%d\n", (f.first * x + f.second).val);
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

