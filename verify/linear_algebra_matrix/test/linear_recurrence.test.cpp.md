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


# :heavy_check_mark: linear_algebra_matrix/test/linear_recurrence.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#dc91d55fecbe93608b76606ec1490b73">linear_algebra_matrix/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/linear_algebra_matrix/test/linear_recurrence.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-19 19:51:42+09:00


* see: <a href="https://judge.yosupo.jp/problem/find_linear_recurrence">https://judge.yosupo.jp/problem/find_linear_recurrence</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/linear_algebra_matrix/linear_recurrence.hpp.html">linear_algebra_matrix/linear_recurrence.hpp</a>
* :heavy_check_mark: <a href="../../../library/modulus/modint_fixed.hpp.html">modulus/modint_fixed.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "linear_algebra_matrix/linear_recurrence.hpp"
#include "modulus/modint_fixed.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"
#include <iostream>

using mint = ModInt<998244353>;
int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int N;
    std::cin >> N;
    std::vector<mint> A(N);
    for (auto &a : A)
    {
        std::cin >> a;
    }
    auto [L, poly] = linear_recurrence(A);
    std::cout << L << '\n';
    for (int i = 1; i <= L; i++) std::cout << -poly[i] << ' ';
    std::cout << '\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "linear_algebra_matrix/linear_recurrence.hpp"
#include <algorithm>
#include <utility>
#include <vector>

// CUT begin
// Berlekamp–Massey algorithm
// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>
// Complexity: O(N^2)
// input: S = sequence from field K
// return: (L=degree of minimal polynomial, C=min. poly.(size = L + 1, C[0] = 1))
// Formula: convolve(S, C)[i] = 0 for i >= L
// Example:
// - [1, 2, 4, 8, 16]   -> (1, [1, -2])
// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])
// - [0, 0, 0, 0, 1]    -> (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)
// - []                 -> (0, [1])
// - [0, 0, 0]          -> (0, [1])
// - [-2]               -> (1, [1, 2])
template <typename K>
std::pair<int, std::vector<K>> linear_recurrence(const std::vector<K> &S)
{
    int N = S.size();
    using poly = std::vector<K>;
    poly C{1}, B{1};
    int L = 0, m = 1;
    K b = 1;

    // adjust: C(x) <- C(x) - (d / b) x^m B(x)
    auto adjust = [](poly C, const poly &B, K d, K b, int m) -> poly {
        C.resize(std::max(C.size(), B.size() + m));
        K a = d / b;
        for (unsigned i = 0; i < B.size(); i++) C[i + m] -= a * B[i];
        return C;
    };

    for (int n = 0; n < N; n++) {
        K d = S[n];
        for (int i = 1; i <= L; i++) d += C[i] * S[n - i];

        if (d == 0) m++;
        else if (2 * L <= n) {
            poly T = C;
            C = adjust(C, B, d, b, m);
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        }
        else C = adjust(C, B, d, b, m++);
    }
    return std::make_pair(L, C);
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
#line 3 "linear_algebra_matrix/test/linear_recurrence.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"
#line 5 "linear_algebra_matrix/test/linear_recurrence.test.cpp"

using mint = ModInt<998244353>;
int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int N;
    std::cin >> N;
    std::vector<mint> A(N);
    for (auto &a : A)
    {
        std::cin >> a;
    }
    auto [L, poly] = linear_recurrence(A);
    std::cout << L << '\n';
    for (int i = 1; i <= L; i++) std::cout << -poly[i] << ' ';
    std::cout << '\n';
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

