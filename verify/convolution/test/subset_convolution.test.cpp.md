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


# :heavy_check_mark: convolution/test/subset_convolution.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#138f586853b56e3cad59aa29ba977214">convolution/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/convolution/test/subset_convolution.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 21:06:32+09:00


* see: <a href="https://judge.yosupo.jp/problem/subset_convolution">https://judge.yosupo.jp/problem/subset_convolution</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/convolution/subset_convolution.hpp.html">convolution/subset_convolution.hpp</a>
* :question: <a href="../../../library/modulus/modint_fixed.hpp.html">modulus/modint_fixed.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#include "convolution/subset_convolution.hpp"
#include "modulus/modint_fixed.hpp"
#include <iostream>

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N;
    std::cin >> N;
    std::vector<ModInt<998244353>> A(1 << N), B(1 << N);
    for (auto &x : A) std::cin >> x;
    for (auto &x : B) std::cin >> x;

    for (auto x : subset_convolution(A, B)) std::cout << x << ' ';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "convolution/test/subset_convolution.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"
#line 2 "convolution/subset_convolution.hpp"
#include <cassert>
#include <vector>

// CUT begin
// Subset sum (fast zeta transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T>
void subset_sum(std::vector<T> &f)
{
    const int sz = f.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (S & (1 << d)) f[S] += f[S ^ (1 << d)];
    }
}
// Inverse of subset sum (fast moebius transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T>
void subset_sum_inv(std::vector<T> &g)
{
    const int sz = g.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (S & (1 << d)) g[S] -= g[S ^ (1 << d)];
    }
}

// Superset sum / its inverse (fast zeta/moebius transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T>
void superset_sum(std::vector<T> &f)
{
    const int sz = f.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (!(S & (1 << d))) f[S] += f[S | (1 << d)];
    }
}
template <typename T>
void superset_sum_inv(std::vector<T> &g)
{
    const int sz = g.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (!(S & (1 << d))) g[S] -= g[S | (1 << d)];
    }
}


// Subset convolution
// h[S] = \sum_T f[T] * g[S - T]
// Complexity: O(N^2 2^N) for arrays of size 2^N
template <typename T>
std::vector<T> subset_convolution(std::vector<T> f, std::vector<T> g)
{
    const int sz = f.size(), m = __builtin_ctz(sz) + 1;
    assert(__builtin_popcount(sz) == 1 and f.size() == g.size());

    std::vector<std::vector<T>> ff(m, std::vector<T>(sz)), fg(m, std::vector<T>(sz));
    for (int i = 0; i < sz; i++) {
        int pc = __builtin_popcount(i);
        ff[pc][i] += f[i], fg[pc][i] += g[i];
    }
    for (auto &vec : ff) subset_sum(vec);
    for (auto &vec : fg) subset_sum(vec);

    std::vector<std::vector<T>> fh(m, std::vector<T>(sz));
    for (int d = 0; d < m; d++) {
        for (int e = 0; d + e < m; e++) {
            for (int i = 0; i < sz; i++) fh[d + e][i] += ff[d][i] * fg[e][i];
        }
    }
    for (auto &vec : fh) subset_sum_inv(vec);
    std::vector<T> ret(sz);
    for (int i = 0; i < sz; i++) ret[i] = fh[__builtin_popcount(i)][i];
    return ret;
}
#line 2 "modulus/modint_fixed.hpp"
#include <iostream>
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
#line 5 "convolution/test/subset_convolution.test.cpp"

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N;
    std::cin >> N;
    std::vector<ModInt<998244353>> A(1 << N), B(1 << N);
    for (auto &x : A) std::cin >> x;
    for (auto &x : B) std::cin >> x;

    for (auto x : subset_convolution(A, B)) std::cout << x << ' ';
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

