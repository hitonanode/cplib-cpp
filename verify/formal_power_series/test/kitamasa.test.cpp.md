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


# :x: formal_power_series/test/kitamasa.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#a20fdd22d4cc62ca1cf4e679d77fd3d2">formal_power_series/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/formal_power_series/test/kitamasa.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-13 13:03:10+09:00


* see: <a href="https://yukicoder.me/problems/no/214">https://yukicoder.me/problems/no/214</a>


## Depends on

* :question: <a href="../../../library/convolution/ntt.hpp.html">convolution/ntt.hpp</a>
* :x: <a href="../../../library/formal_power_series/monomial_mod_polynomial.hpp.html">formal_power_series/monomial_mod_polynomial.hpp</a>
* :question: <a href="../../../library/modulus/modint_fixed.hpp.html">modulus/modint_fixed.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://yukicoder.me/problems/no/214"
#include "modulus/modint_fixed.hpp"
#include "convolution/ntt.hpp"
#include "formal_power_series/monomial_mod_polynomial.hpp"
using mint = ModInt<1000000007>;

#include <iostream>
#include <numeric>
template<typename T> istream &operator>>(istream &is, vector<T> &vec){ for (auto &v : vec) is >> v; return is; }
#define dbg(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ") " << __FILE__ << endl;


std::vector<mint> gen_dp(std::vector<int> v, int n)
{
    vector<vector<mint>> dp(n + 1, vector<mint>(v.back() * n + 1));
    dp[0][0] = 1;
    for (auto x : v)
    {
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j < dp[i].size(); j++) if (dp[i][j])
            {
                for (int k = 1; i + k <= n; k++) dp[i + k][j + x * k] += dp[i][j];
            }
        }
    }
    return dp.back();
}

int main()
{
    long long N;
    int P, C;
    std::cin >> N >> P >> C;
    std::vector<mint> primes = gen_dp({2, 3, 5, 7, 11, 13}, P), composites = gen_dp({4, 6, 8, 9, 10, 12}, C);
    std::vector<mint> f_reversed = nttconv(primes, composites);
    std::vector<mint> dp(f_reversed.size());
    dp[0] = 1;
    for (int i = 0; i < dp.size(); i++)
    {
        for (int j = 1; i + j < dp.size(); j++) dp[i + j] += dp[i] * f_reversed[j];
    }

    for (auto &x : f_reversed) x = -x;
    f_reversed[0] = 1;

    std::vector<mint> g(f_reversed.size() - 1);
    g[0] = 1;
    if (N > f_reversed.size())
    {
        long long d = N - f_reversed.size();
        N -= d;
        g = monomial_mod_polynomial<mint>(d, f_reversed);
    }

    auto prod_x = [&](std::vector<mint> v) -> std::vector<mint> {
        int K = v.size();
        std::vector<mint> c(K);
        c[0] = -v[K - 1] * f_reversed[K];
        for (int i = 1; i < K; i++)
        {
            c[i] = v[i - 1] - v[K - 1] * f_reversed[K - i];
        }
        return c;
    };
    mint acc = 0;
    for (int i = N; i < f_reversed.size(); i++) acc += f_reversed[i];
    mint ret = 0;
    while (N)
    {
        mint p = std::inner_product(g.begin(), g.end(), dp.begin(), mint(0));
        ret -= acc * p;
        g = prod_x(g);
        N--;
        acc += f_reversed[N];
    }
    cout << ret << '\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "formal_power_series/test/kitamasa.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/214"
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
#line 3 "convolution/ntt.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <tuple>
#line 9 "convolution/ntt.hpp"

// CUT begin
// Integer convolution for arbitrary mod
// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime class.
// We skip Garner's algorithm if `skip_garner` is true or mod is in `nttprimes`.
// input: a (size: n), b (size: m)
// return: vector (size: n + m - 1)
template <typename MODINT>
std::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool skip_garner = false);

constexpr int nttprimes[3] = {998244353, 167772161, 469762049};

// Integer FFT (Fast Fourier Transform) for ModInt class
// (Also known as Number Theoretic Transform, NTT)
// is_inverse: inverse transform
// ** Input size must be 2^n **
template <typename MODINT>
void ntt(std::vector<MODINT> &a, bool is_inverse = false)
{
    int n = a.size();
    if (n == 1) return;
    static const int mod = MODINT::get_mod();
    static const MODINT root = MODINT::get_primitive_root();
    assert(__builtin_popcount(n) == 1 and (mod - 1) % n == 0);

    static std::vector<MODINT> w{1}, iw{1};
    for (int m = w.size(); m < n / 2; m *= 2)
    {
        MODINT dw = root.power((mod - 1) / (4 * m)), dwinv = 1 / dw;
        w.resize(m * 2), iw.resize(m * 2);
        for (int i = 0; i < m; i++) w[m + i] = w[i] * dw, iw[m + i] = iw[i] * dwinv;
    }

    if (!is_inverse) {
        for (int m = n; m >>= 1;) {
            for (int s = 0, k = 0; s < n; s += 2 * m, k++) {
                for (int i = s; i < s + m; i++) {
#ifdef __clang__
                    a[i + m] *= w[k];
                    std::tie(a[i], a[i + m]) = std::make_pair(a[i] + a[i + m], a[i] - a[i + m]);
#else
                    MODINT x = a[i], y = a[i + m] * w[k];
                    a[i] = x + y, a[i + m] = x - y;
#endif
                }
            }
        }
    }
    else {
        for (int m = 1; m < n; m *= 2) {
            for (int s = 0, k = 0; s < n; s += 2 * m, k++) {
                for (int i = s; i < s + m; i++) {
#ifdef __clang__
                    std::tie(a[i], a[i + m]) = std::make_pair(a[i] + a[i + m], a[i] - a[i + m]);
                    a[i + m] *= iw[k];
#else
                    MODINT x = a[i], y = a[i + m];
                    a[i] = x + y, a[i + m] = (x - y) * iw[k];
#endif
                }
            }
        }
        int n_inv = MODINT(n).inv();
        for (auto &v : a) v *= n_inv;
    }
}
template <int MOD>
std::vector<ModInt<MOD>> nttconv_(const std::vector<int> &a, const std::vector<int> &b) {
    int sz = a.size();
    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);
    std::vector<ModInt<MOD>> ap(sz), bp(sz);
    for (int i = 0; i < sz; i++) ap[i] = a[i], bp[i] = b[i];
    if (a == b) {
        ntt(ap, false);
        bp = ap;
    }
    else {
        ntt(ap, false);
        ntt(bp, false);
    }
    for (int i = 0; i < sz; i++) ap[i] *= bp[i];
    ntt(ap, true);
    return ap;
}
long long extgcd_ntt_(long long a, long long b, long long &x, long long &y)
{
    long long d = a;
    if (b != 0) d = extgcd_ntt_(b, a % b, y, x), y -= (a / b) * x;
    else x = 1, y = 0;
    return d;
}
long long modinv_ntt_(long long a, long long m)
{
    long long x, y;
    extgcd_ntt_(a, m, x, y);
    return (m + x % m) % m;
}
long long garner_ntt_(int r0, int r1, int r2, int mod)
{
    std::array<long long, 4> rs = {r0, r1, r2, 0};
    std::vector<long long> coffs(4, 1), constants(4, 0);
    for (int i = 0; i < 3; i++) {
        long long v = (rs[i] - constants[i]) * modinv_ntt_(coffs[i], nttprimes[i]) % nttprimes[i];
        if (v < 0) v += nttprimes[i];
        for (int j = i + 1; j < 4; j++) {
            (constants[j] += coffs[j] * v) %= (j < 3 ? nttprimes[j] : mod);
            (coffs[j] *= nttprimes[i]) %= (j < 3 ? nttprimes[j] : mod);
        }
    }
    return constants.back();
}
template <typename MODINT>
std::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool skip_garner)
{
    int sz = 1, n = a.size(), m = b.size();
    while (sz < n + m) sz <<= 1;
    if (sz <= 16) {
        std::vector<MODINT> ret(n + m - 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ret[i + j] += a[i] * b[j];
        }
        return ret;
    }
    int mod = MODINT::get_mod();
    if (skip_garner or std::find(std::begin(nttprimes), std::end(nttprimes), mod) != std::end(nttprimes))
    {
        a.resize(sz), b.resize(sz);
        if (a == b) { ntt(a, false); b = a; }
        else ntt(a, false), ntt(b, false);
        for (int i = 0; i < sz; i++) a[i] *= b[i];
        ntt(a, true);
        a.resize(n + m - 1);
    }
    else {
        std::vector<int> ai(sz), bi(sz);
        for (int i = 0; i < n; i++) ai[i] = a[i].val;
        for (int i = 0; i < m; i++) bi[i] = b[i].val;
        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);
        auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);
        auto ntt2 = nttconv_<nttprimes[2]>(ai, bi);
        a.resize(n + m - 1);
        for (int i = 0; i < n + m - 1; i++) {
            a[i] = garner_ntt_(ntt0[i].val, ntt1[i].val, ntt2[i].val, mod);
        }
    }
    return a;
}
#line 4 "formal_power_series/monomial_mod_polynomial.hpp"

// Calculate x^N mod f(x)
// Known as `Kitamasa method`
// Input: f_reversed: monic, reversed (f_reversed[0] = 1)
// Complexity: O(K^2 lgN) (K: deg. of f)
// Example: (4, [1, -1, -1]) -> [2, 3]
//          ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2 )
// Reference: <http://misawa.github.io/others/fast_kitamasa_method.html>
//            <http://sugarknri.hatenablog.com/entry/2017/11/18/233936>
template <typename Tfield>
std::vector<Tfield> monomial_mod_polynomial(long long N, const std::vector<Tfield> &f_reversed)
{
    assert(!f_reversed.empty() and f_reversed[0] == 1);
    int K = f_reversed.size() - 1;
    if (!K) return {};
    int D = 64 - __builtin_clzll(N);
    std::vector<Tfield> ret(K, 0);
    ret[0] = 1;
    auto self_conv = [](std::vector<Tfield> x) -> std::vector<Tfield> {
        int d = x.size();
        std::vector<Tfield> ret(d * 2 - 1);
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
            std::vector<Tfield> c(K);
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
#line 5 "formal_power_series/test/kitamasa.test.cpp"
using mint = ModInt<1000000007>;

#line 8 "formal_power_series/test/kitamasa.test.cpp"
#include <numeric>
template<typename T> istream &operator>>(istream &is, vector<T> &vec){ for (auto &v : vec) is >> v; return is; }
#define dbg(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ") " << __FILE__ << endl;


std::vector<mint> gen_dp(std::vector<int> v, int n)
{
    vector<vector<mint>> dp(n + 1, vector<mint>(v.back() * n + 1));
    dp[0][0] = 1;
    for (auto x : v)
    {
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j < dp[i].size(); j++) if (dp[i][j])
            {
                for (int k = 1; i + k <= n; k++) dp[i + k][j + x * k] += dp[i][j];
            }
        }
    }
    return dp.back();
}

int main()
{
    long long N;
    int P, C;
    std::cin >> N >> P >> C;
    std::vector<mint> primes = gen_dp({2, 3, 5, 7, 11, 13}, P), composites = gen_dp({4, 6, 8, 9, 10, 12}, C);
    std::vector<mint> f_reversed = nttconv(primes, composites);
    std::vector<mint> dp(f_reversed.size());
    dp[0] = 1;
    for (int i = 0; i < dp.size(); i++)
    {
        for (int j = 1; i + j < dp.size(); j++) dp[i + j] += dp[i] * f_reversed[j];
    }

    for (auto &x : f_reversed) x = -x;
    f_reversed[0] = 1;

    std::vector<mint> g(f_reversed.size() - 1);
    g[0] = 1;
    if (N > f_reversed.size())
    {
        long long d = N - f_reversed.size();
        N -= d;
        g = monomial_mod_polynomial<mint>(d, f_reversed);
    }

    auto prod_x = [&](std::vector<mint> v) -> std::vector<mint> {
        int K = v.size();
        std::vector<mint> c(K);
        c[0] = -v[K - 1] * f_reversed[K];
        for (int i = 1; i < K; i++)
        {
            c[i] = v[i - 1] - v[K - 1] * f_reversed[K - i];
        }
        return c;
    };
    mint acc = 0;
    for (int i = N; i < f_reversed.size(); i++) acc += f_reversed[i];
    mint ret = 0;
    while (N)
    {
        mint p = std::inner_product(g.begin(), g.end(), dp.begin(), mint(0));
        ret -= acc * p;
        g = prod_x(g);
        N--;
        acc += f_reversed[N];
    }
    cout << ret << '\n';
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

