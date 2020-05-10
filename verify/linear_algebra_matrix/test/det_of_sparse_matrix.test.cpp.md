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


# :heavy_check_mark: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#dc91d55fecbe93608b76606ec1490b73">linear_algebra_matrix/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-05 22:31:32+09:00


* see: <a href="https://judge.yosupo.jp/problem/sparse_matrix_det">https://judge.yosupo.jp/problem/sparse_matrix_det</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/linear_algebra_matrix/det_of_sparse_matrix.hpp.html">linear_algebra_matrix/det_of_sparse_matrix.hpp</a>
* :question: <a href="../../../library/linear_algebra_matrix/linear_recurrence.hpp.html">linear_algebra_matrix/linear_recurrence.hpp</a>
* :question: <a href="../../../library/modulus/modint_fixed.hpp.html">modulus/modint_fixed.hpp</a>
* :heavy_check_mark: <a href="../../../library/random/rand_nondeterministic.hpp.html">random/rand_nondeterministic.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"
#include "modulus/modint_fixed.hpp"
#include "linear_algebra_matrix/det_of_sparse_matrix.hpp"
#include <iostream>

int main()
{
    int N, K;
    std::cin >> N >> K;
    sparse_matrix<ModInt<998244353>> M(N, N);
    while (K--)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        M.add_element(a, b, c);
    }
    std::cout << M.Determinant() << '\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"
#line 2 "modulus/modint_fixed.hpp"
#include <iostream>
#include <vector>
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
#line 2 "linear_algebra_matrix/det_of_sparse_matrix.hpp"
#include <cassert>
#include <numeric>
#include <utility>
#line 6 "linear_algebra_matrix/det_of_sparse_matrix.hpp"

#line 2 "random/rand_nondeterministic.hpp"
#include <chrono>
#include <random>
using namespace std;

// CUT begin
struct rand_int_
{
    using lint = long long;
    mt19937 mt;
    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)
    lint operator()(lint l, lint r) {
        uniform_int_distribution<lint> d(l, r - 1);
        return d(mt);
    }
} rnd;
#line 2 "linear_algebra_matrix/linear_recurrence.hpp"
#include <algorithm>
#line 6 "linear_algebra_matrix/linear_recurrence.hpp"

// CUT begin
// Berlekamp–Massey algorithm
// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>
// Complexity: O(N^2)
// input: S = sequence from field K
// return: L          = degree of minimal polynomial,
//         C_reversed = monic min. polynomial (size = L + 1, reversed order, C_reversed[0] = 1))
// Formula: convolve(S, C_reversed)[i] = 0 for i >= L
// Example:
// - [1, 2, 4, 8, 16]   -> (1, [1, -2])
// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])
// - [0, 0, 0, 0, 1]    -> (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)
// - []                 -> (0, [1])
// - [0, 0, 0]          -> (0, [1])
// - [-2]               -> (1, [1, 2])
template <typename _Tfield>
std::pair<int, std::vector<_Tfield>> linear_recurrence(const std::vector<_Tfield> &S)
{
    int N = S.size();
    using poly = std::vector<_Tfield>;
    poly C_reversed{1}, B{1};
    int L = 0, m = 1;
    _Tfield b = 1;

    // adjust: C(x) <- C(x) - (d / b) x^m B(x)
    auto adjust = [](poly C, const poly &B, _Tfield d, _Tfield b, int m) -> poly {
        C.resize(std::max(C.size(), B.size() + m));
        _Tfield a = d / b;
        for (unsigned i = 0; i < B.size(); i++) C[i + m] -= a * B[i];
        return C;
    };

    for (int n = 0; n < N; n++) {
        _Tfield d = S[n];
        for (int i = 1; i <= L; i++) d += C_reversed[i] * S[n - i];

        if (d == 0) m++;
        else if (2 * L <= n) {
            poly T = C_reversed;
            C_reversed = adjust(C_reversed, B, d, b, m);
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        }
        else C_reversed = adjust(C_reversed, B, d, b, m++);
    }
    return std::make_pair(L, C_reversed);
}


// Calculate x^N mod f(x)
// Known as `Kitamasa method`
// Input: f_reversed: monic, reversed (f_reversed[0] = 1)
// Complexity: O(K^2 lgN) (K: deg. of f)
// Example: (4, [1, -1, -1]) -> [2, 3]
//          ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2 )
// Reference: <http://misawa.github.io/others/fast_kitamasa_method.html>
//            <http://sugarknri.hatenablog.com/entry/2017/11/18/233936>
template <typename _Tfield>
std::vector<_Tfield> monomial_mod_polynomial(long long N, const std::vector<_Tfield> &f_reversed)
{
    assert(!f_reversed.empty() and f_reversed[0] == 1);
    int K = f_reversed.size() - 1;
    if (!K) return {};
    int D = 64 - __builtin_clzll(N);
    std::vector<_Tfield> ret(K, 0);
    ret[0] = 1;
    auto self_conv = [](std::vector<_Tfield> x) -> std::vector<_Tfield> {
        int d = x.size();
        std::vector<_Tfield> ret(d * 2 - 1);
        for (int i = 0; i < d; i++)
        {
            ret[i * 2] += x[i] * x[i];
            for (int j = 0; j < i; j++) ret[i + j] += x[i] * x[j] * 2;
        }
        return ret;
    };
    for (int d = D; d--;)
    {
        ret = self_conv(ret);
        for (int i = 2 * K - 2; i >= K; i--)
        {
            for (int j = 1; j <= K; j++) ret[i - j] -= ret[i] * f_reversed[j];
        }
        ret.resize(K);
        if ((N >> d) & 1)
        {
            std::vector<_Tfield> c(K);
            c[0] = -ret[K - 1] * f_reversed[K];
            for (int i = 1; i < K; i++)
            {
                c[i] = ret[i - 1] - ret[K - 1] * f_reversed[K - i];
            }
            ret = c;
        }
    }
    return ret;
}
#line 9 "linear_algebra_matrix/det_of_sparse_matrix.hpp"

// CUT begin
// Sparse matrix on ModInt/ModIntRuntime
template <typename _Tp>
struct sparse_matrix
{
    int H, W;
    std::vector<std::vector<std::pair<int, _Tp>>> vals;
    sparse_matrix(int H = 0, int W = 0) : H(H), W(W), vals(H) {}
    void add_element(int i, int j, _Tp val)
    {
        assert(i >= 0 and i < H);
        assert(j >= 0 and i < W);
        vals[i].emplace_back(j, val);
    }
    _Tp eval_bilinear(const std::vector<_Tp> &vl, const std::vector<_Tp> &vr) const
    {
        assert(vl.size() == H and vr.size() == W);
        _Tp ret = 0;
        for (int i = 0; i < H; i++)
        {
            for (const auto &p : vals[i])
            {
                ret += vl[i] * p.second * vr[p.first];
            }
        }
        return ret;
    }
    static std::vector<_Tp> prod(const sparse_matrix<_Tp> &M, const std::vector<_Tp> &vec)
    {
        assert(M.W == int(vec.size()));
        std::vector<_Tp> ret(M.H);
        for (int i = 0; i < M.H; i++)
        {
            for (const auto &p : M.vals[i])
            {
                ret[i] += p.second * vec[p.first];
            }
        }
        return ret;
    }
    // Determinant of sparse matrix
    // Complexity: O(NK + N^2) (K: # of non-zero elements in M)
    // Reference: <https://yukicoder.me/wiki/black_box_linear_algebra>
    _Tp Determinant() const
    {
        assert(H == W);
        const int N = H, hi = _Tp::get_mod();
        std::vector<_Tp> b(N), u(N), D(N);
        for (int i = 0; i < N; i++)
        {
            b[i] = rnd(1, hi), u[i] = rnd(1, hi), D[i] = rnd(1, hi);
        }
        std::vector<_Tp> uMDib(2 * N);
        for (int i = 0; i < 2 * N; i++)
        {
            uMDib[i] = std::inner_product(u.begin(), u.end(), b.begin(), _Tp(0));
            for (int j = 0; j < N; j++)
            {
                b[j] *= D[j];
            }
            b = prod(*this, b);
        }
        auto ret = linear_recurrence<_Tp>(uMDib);
        _Tp det = ret.second.back() * (N % 2 ? -1 : 1);
        _Tp ddet = 1;
        for (auto d : D) ddet *= d;
        return det / ddet;
    }
};
#line 5 "linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp"

int main()
{
    int N, K;
    std::cin >> N >> K;
    sparse_matrix<ModInt<998244353>> M(N, N);
    while (K--)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        M.add_element(a, b, c);
    }
    std::cout << M.Determinant() << '\n';
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

