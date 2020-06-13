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


# :heavy_check_mark: linear_algebra_matrix/test/system_of_linear_equations.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#dc91d55fecbe93608b76606ec1490b73">linear_algebra_matrix/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/linear_algebra_matrix/test/system_of_linear_equations.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-06-06 02:17:41+09:00


* see: <a href="https://judge.yosupo.jp/problem/system_of_linear_equations">https://judge.yosupo.jp/problem/system_of_linear_equations</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/linear_algebra_matrix/linalg_modint.hpp.html">linear_algebra_matrix/linalg_modint.hpp</a>
* :heavy_check_mark: <a href="../../../library/linear_algebra_matrix/system_of_linear_equations.hpp.html">linear_algebra_matrix/system_of_linear_equations.hpp</a>
* :question: <a href="../../../library/modulus/modint_fixed.hpp.html">modulus/modint_fixed.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include "modulus/modint_fixed.hpp"
#include "linear_algebra_matrix/system_of_linear_equations.hpp"
#include <iostream>
using mint = ModInt<998244353>;

int main()
{
    int N, M;
    std::cin >> N >> M;
    matrix<mint> A(N, M);
    std::cin >> A;
    std::vector<mint> b(N);
    for (auto &x : b) std::cin >> x;
    auto ret = system_of_linear_equations(A, b);
    if (ret.first.empty()) std::cout << -1 << "\n";
    else
    {
        std::cout << ret.second.size() << "\n";
        for (auto x : ret.first) std::cout << x << " ";
        std::cout << "\n";

        for (auto vec : ret.second) {
            for (auto e : vec) std::cout << e << " ";
            std::cout << "\n";
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "linear_algebra_matrix/test/system_of_linear_equations.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
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
#line 2 "linear_algebra_matrix/linalg_modint.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#line 6 "linear_algebra_matrix/linalg_modint.hpp"

// CUT begin
template <typename T>
struct matrix
{
    int H, W;
    std::vector<T> elem;
    typename std::vector<T>::iterator operator[](int i) { return elem.begin() + i * W; }
    inline T &at(int i, int j) { return elem[i * W + j]; }
    inline T get(int i, int j) const { return elem[i * W + j]; }
    operator std::vector<std::vector<T>>() const {
        std::vector<std::vector<T>> ret(H);
        for (int i = 0; i < H; i++) std::copy(elem.begin() + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));
        return ret;
    }

    matrix(int H = 0, int W = 0) : H(H), W(W), elem(H * W) {}
    matrix(const std::vector<std::vector<T>> &d) : H(d.size()), W(d.size() ? d[0].size() : 0) {
        for (auto &raw : d) std::copy(raw.begin(), raw.end(), std::back_inserter(elem));
    }

    static matrix Identity(int N) {
        matrix ret(N, N);
        for (int i = 0; i < N; i++) ret.at(i, i) = 1;
        return ret;
    }

    matrix operator-() const { matrix ret(H, W); for (int i = 0; i < H * W; i++) ret.elem[i] = -elem[i]; return ret; }
    matrix operator+(const matrix &r) const { matrix ret(H, W); for (int i = 0; i < H * W; i++) ret.elem[i] += r.elem[i]; return ret; }
    matrix operator-(const matrix &r) const { matrix ret(H, W); for (int i = 0; i < H * W; i++) ret.elem[i] -= r.elem[i]; return ret; }
    matrix operator*(const matrix &r) const {
        matrix ret(H, r.W);
        for (int i = 0; i < H; i++) {
            for (int k = 0; k < W; k++) {
                for (int j = 0; j < r.W; j++) {
                    ret.at(i, j) += this->get(i, k) * r.get(k, j);
                }
            }
        }
        return ret;
    }
    matrix &operator+=(const matrix &r) { return *this = *this + r; }
    matrix &operator-=(const matrix &r) { return *this = *this - r; }
    matrix &operator*=(const matrix &r) { return *this = *this * r; }
    bool operator==(const matrix &r) const { return H == r.H and W == r.W and elem == r.elem; }
    bool operator!=(const matrix &r) const { return H != r.H or W != r.W or elem != r.elem; }
    bool operator<(const matrix &r) const { return elem < r.elem; }
    matrix pow(int64_t n) const {
        matrix ret = Identity(H);
        if (n == 0) return ret;
        for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {
            ret *= ret;
            if ((n >> i) & 1) ret *= (*this);
        }
        return ret;
    }
    matrix transpose() const {
        matrix ret(W, H);
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) ret.at(j, i) = this->get(i, j);
        return ret;
    }
    // Gauss-Jordan elimination
    // - Require inverse for every non-zero element
    // - Complexity: O(H^2 W)
    matrix gauss_jordan() const {
        int c = 0;
        matrix mtr(*this);
        for (int h = 0; h < H; h++) {
            if (c == W) break;
            int piv = -1;
            for (int j = h; j < H; j++) if (mtr.get(j, c)) {
                piv = j;
                break;
            }
            if (piv == -1) { c++; h--; continue; }
            if (h != piv) {
                for (int w = 0; w < W; w++) {
                    std::swap(mtr[piv][w], mtr[h][w]);
                    mtr.at(piv, w) *= -1; // To preserve sign of determinant
                }
            }
            for (int hh = 0; hh < H; hh++) if (hh != h) {
                T coeff = mtr.at(hh, c) * mtr.at(h, c).inv();
                for (int w = W - 1; w >= c; w--) {
                    mtr.at(hh, w) -= mtr.at(h, w) * coeff;
                }
            }
            c++;
        }
        return mtr;
    }
    int rank_of_gauss_jordan() const {
        for (int i = H * W - 1; i >= 0; i--) if (elem[i]) return i / W + 1;
        return 0;
    }
    T determinant_of_upper_triangle() const {
        T ret = 1;
        for (int i = 0; i < H; i++) ret *= get(i, i);
        return ret;
    }
    friend std::vector<T> operator*(const matrix &m, const std::vector<T> &v) {
        assert(m.W == int(v.size()));
        std::vector<T> ret(m.H);
        for (int i = 0; i < m.H; i++) {
            for (int j = 0; j < m.W; j++) {
                ret[i] += m.get(i, j) * v[j];
            }
        }
        return ret;
    }
    friend std::vector<T> operator*(const std::vector<T> &v, const matrix &m) {
        assert(int(v.size()) == m.H);
        std::vector<T> ret(m.W);
        for (int i = 0; i < m.H; i++) {
            for (int j = 0; j < m.W; j++) {
                ret[j] += v[i] * m.get(i, j);
            }
        }
        return ret;
    }
    friend std::ostream &operator<<(std::ostream &os, const matrix &x) {
        os << "[(" << x.H << " * " << x.W << " matrix)";
        os << "\n[column sums: ";
        for (int j = 0; j < x.W; j++) {
            T s = 0;
            for (int i = 0; i < x.H; i++) s += x.get(i, j);
            os << s << ",";
        }
        os << "]";
        for (int i = 0; i < x.H; i++) {
            os << "\n[";
            for (int j = 0; j < x.W; j++) os << x.get(i, j) << ",";
            os << "]";
        }
        os << "]\n";
        return os;
    }
    friend std::istream &operator>>(std::istream &is, matrix &x) {
        for (auto &v : x.elem) is >> v;
        return is;
    }
};


// Fibonacci numbers f(n) = af(n - 1) + bf(n - 2)
// Example (a = b = 1): 0=>1, 1=>1, 2=>2, 3=>3, 4=>5, ...
template <typename T>
T Fibonacci(long long int k, int a = 1, int b = 1)
{
    matrix<T> mat(2, 2);
    mat[0][1] = 1;
    mat[1][0] = b;
    mat[1][1] = a;
    return mat.pow(k + 1)[0][1];
}
#line 3 "linear_algebra_matrix/system_of_linear_equations.hpp"
#include <utility>
#line 5 "linear_algebra_matrix/system_of_linear_equations.hpp"

// CUT begin
// Solve Ax = b for T = ModInt<PRIME>
// - retval: {one of the solution, {freedoms}} (if solution exists)
//           {{}, {}} (otherwise)
// Complexity:
// - Yield one of the possible solutions: O(H^2 W) (H: # of eqs., W: # of variables)
// - Enumerate all of the bases: O(HW(H + W))
template <typename T>
std::pair<std::vector<T>, std::vector<std::vector<T>>>
system_of_linear_equations(matrix<T> A, std::vector<T> b)
{
    int H = A.H, W = A.W;
    matrix<T> M(H, W + 1);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) M[i][j] = A[i][j];
        M[i][W] = b[i];
    }
    M = M.gauss_jordan();
    std::vector<int> ss(W, -1);
    for (int i = 0; i < H; i++) {
        int j = 0;
        while (j <= W and M[i][j] == 0) j++;
        if (j == W) { // No solution
            return {{}, {}};
        }
        if (j < W) ss[j] = i;
    }
    std::vector<T> x(W);
    std::vector<std::vector<T>> D;
    for (int j = 0; j < W; j++) {
        if (ss[j] == -1) {
            std::vector<T> d(W);
            d[j] = 1;
            for (int jj = 0; jj < j; jj++) if (ss[jj] != -1) d[jj] = -M[ss[jj]][j] / M[ss[jj]][jj];
            D.emplace_back(d);
        }
        else x[j] = M[ss[j]][W] / M[ss[j]][j];
    }
    return std::make_pair(x, D);
}
#line 5 "linear_algebra_matrix/test/system_of_linear_equations.test.cpp"
using mint = ModInt<998244353>;

int main()
{
    int N, M;
    std::cin >> N >> M;
    matrix<mint> A(N, M);
    std::cin >> A;
    std::vector<mint> b(N);
    for (auto &x : b) std::cin >> x;
    auto ret = system_of_linear_equations(A, b);
    if (ret.first.empty()) std::cout << -1 << "\n";
    else
    {
        std::cout << ret.second.size() << "\n";
        for (auto x : ret.first) std::cout << x << " ";
        std::cout << "\n";

        for (auto vec : ret.second) {
            for (auto e : vec) std::cout << e << " ";
            std::cout << "\n";
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

