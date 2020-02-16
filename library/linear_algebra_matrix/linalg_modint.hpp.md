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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: linear_algebra_matrix/linalg_modint.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#20f2c5d841ec31673050aaedd8b17f50">linear_algebra_matrix</a>
* <a href="{{ site.github.repository_url }}/blob/master/linear_algebra_matrix/linalg_modint.hpp">View this file on GitHub</a>
    - Last commit date: 2020-02-02 01:11:21+09:00




## Required by

* :heavy_check_mark: <a href="system_of_linear_equations.hpp.html">linear_algebra_matrix/system_of_linear_equations.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/linear_algebra_matrix/test/linalg_modint_determinant.test.cpp.html">linear_algebra_matrix/test/linalg_modint_determinant.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp.html">linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/linear_algebra_matrix/test/system_of_linear_equations.test.cpp.html">linear_algebra_matrix/test/system_of_linear_equations.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

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
    friend std::ostream &operator<<(std::ostream &os, const matrix &x) {
        os << "[(" << x.H << " * " << x.W << " matrix)";
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "linear_algebra_matrix/linalg_modint.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

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
    friend std::ostream &operator<<(std::ostream &os, const matrix &x) {
        os << "[(" << x.H << " * " << x.W << " matrix)";
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

