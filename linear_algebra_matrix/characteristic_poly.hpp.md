---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/matrix.hpp
    title: linear_algebra_matrix/matrix.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/characteristic_poly.test.cpp
    title: linear_algebra_matrix/test/characteristic_poly.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf
  bundledCode: "#line 2 \"linear_algebra_matrix/matrix.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <iostream>\n#include <iterator>\n\
    #include <type_traits>\n#include <vector>\n\n// CUT begin\ntemplate <typename\
    \ T> struct matrix {\n    int H, W;\n    std::vector<T> elem;\n    typename std::vector<T>::iterator\
    \ operator[](int i) { return elem.begin() + i * W; }\n    inline T &at(int i,\
    \ int j) { return elem[i * W + j]; }\n    inline T get(int i, int j) const { return\
    \ elem[i * W + j]; }\n    int height() const { return H; }\n    int width() const\
    \ { return W; }\n    std::vector<std::vector<T>> vecvec() const {\n        std::vector<std::vector<T>>\
    \ ret(H);\n        for (int i = 0; i < H; i++) {\n            std::copy(elem.begin()\
    \ + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));\n        }\n\
    \        return ret;\n    }\n    operator std::vector<std::vector<T>>() const\
    \ { return vecvec(); }\n    matrix() = default;\n    matrix(int H, int W) : H(H),\
    \ W(W), elem(H * W) {}\n    matrix(const std::vector<std::vector<T>> &d) : H(d.size()),\
    \ W(d.size() ? d[0].size() : 0) {\n        for (auto &raw : d) std::copy(raw.begin(),\
    \ raw.end(), std::back_inserter(elem));\n    }\n\n    static matrix Identity(int\
    \ N) {\n        matrix ret(N, N);\n        for (int i = 0; i < N; i++) ret.at(i,\
    \ i) = 1;\n        return ret;\n    }\n\n    matrix operator-() const {\n    \
    \    matrix ret(H, W);\n        for (int i = 0; i < H * W; i++) ret.elem[i] =\
    \ -elem[i];\n        return ret;\n    }\n    matrix operator*(const T &v) const\
    \ {\n        matrix ret = *this;\n        for (auto &x : ret.elem) x *= v;\n \
    \       return ret;\n    }\n    matrix operator/(const T &v) const {\n       \
    \ matrix ret = *this;\n        const T vinv = T(1) / v;\n        for (auto &x\
    \ : ret.elem) x *= vinv;\n        return ret;\n    }\n    matrix operator+(const\
    \ matrix &r) const {\n        matrix ret = *this;\n        for (int i = 0; i <\
    \ H * W; i++) ret.elem[i] += r.elem[i];\n        return ret;\n    }\n    matrix\
    \ operator-(const matrix &r) const {\n        matrix ret = *this;\n        for\
    \ (int i = 0; i < H * W; i++) ret.elem[i] -= r.elem[i];\n        return ret;\n\
    \    }\n    matrix operator*(const matrix &r) const {\n        matrix ret(H, r.W);\n\
    \        for (int i = 0; i < H; i++) {\n            for (int k = 0; k < W; k++)\
    \ {\n                for (int j = 0; j < r.W; j++) ret.at(i, j) += this->get(i,\
    \ k) * r.get(k, j);\n            }\n        }\n        return ret;\n    }\n  \
    \  matrix &operator*=(const T &v) { return *this = *this * v; }\n    matrix &operator/=(const\
    \ T &v) { return *this = *this / v; }\n    matrix &operator+=(const matrix &r)\
    \ { return *this = *this + r; }\n    matrix &operator-=(const matrix &r) { return\
    \ *this = *this - r; }\n    matrix &operator*=(const matrix &r) { return *this\
    \ = *this * r; }\n    bool operator==(const matrix &r) const { return H == r.H\
    \ and W == r.W and elem == r.elem; }\n    bool operator!=(const matrix &r) const\
    \ { return H != r.H or W != r.W or elem != r.elem; }\n    bool operator<(const\
    \ matrix &r) const { return elem < r.elem; }\n    matrix pow(int64_t n) const\
    \ {\n        matrix ret = Identity(H);\n        bool ret_is_id = true;\n     \
    \   if (n == 0) return ret;\n        for (int i = 63 - __builtin_clzll(n); i >=\
    \ 0; i--) {\n            if (!ret_is_id) ret *= ret;\n            if ((n >> i)\
    \ & 1) ret *= (*this), ret_is_id = false;\n        }\n        return ret;\n  \
    \  }\n    std::vector<T> pow_vec(int64_t n, std::vector<T> vec) const {\n    \
    \    matrix x = *this;\n        while (n) {\n            if (n & 1) vec = x *\
    \ vec;\n            x *= x;\n            n >>= 1;\n        }\n        return vec;\n\
    \    };\n    matrix transpose() const {\n        matrix ret(W, H);\n        for\
    \ (int i = 0; i < H; i++) {\n            for (int j = 0; j < W; j++) ret.at(j,\
    \ i) = this->get(i, j);\n        }\n        return ret;\n    }\n    // Gauss-Jordan\
    \ elimination\n    // - Require inverse for every non-zero element\n    // - Complexity:\
    \ O(H^2 W)\n    template <typename T2, typename std::enable_if<std::is_floating_point<T2>::value>::type\
    \ * = nullptr>\n    static int choose_pivot(const matrix<T2> &mtr, int h, int\
    \ c) noexcept {\n        int piv = -1;\n        for (int j = h; j < mtr.H; j++)\
    \ {\n            if (mtr.get(j, c) and (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv,\
    \ c)))) piv = j;\n        }\n        return piv;\n    }\n    template <typename\
    \ T2, typename std::enable_if<!std::is_floating_point<T2>::value>::type * = nullptr>\n\
    \    static int choose_pivot(const matrix<T2> &mtr, int h, int c) noexcept {\n\
    \        for (int j = h; j < mtr.H; j++) {\n            if (mtr.get(j, c)) return\
    \ j;\n        }\n        return -1;\n    }\n    matrix gauss_jordan() const {\n\
    \        int c = 0;\n        matrix mtr(*this);\n        std::vector<int> ws;\n\
    \        ws.reserve(W);\n        for (int h = 0; h < H; h++) {\n            if\
    \ (c == W) break;\n            int piv = choose_pivot(mtr, h, c);\n          \
    \  if (piv == -1) {\n                c++;\n                h--;\n            \
    \    continue;\n            }\n            if (h != piv) {\n                for\
    \ (int w = 0; w < W; w++) {\n                    std::swap(mtr[piv][w], mtr[h][w]);\n\
    \                    mtr.at(piv, w) *= -1; // To preserve sign of determinant\n\
    \                }\n            }\n            ws.clear();\n            for (int\
    \ w = c; w < W; w++) {\n                if (mtr.at(h, w) != 0) ws.emplace_back(w);\n\
    \            }\n            const T hcinv = T(1) / mtr.at(h, c);\n           \
    \ for (int hh = 0; hh < H; hh++)\n                if (hh != h) {\n           \
    \         const T coeff = mtr.at(hh, c) * hcinv;\n                    for (auto\
    \ w : ws) mtr.at(hh, w) -= mtr.at(h, w) * coeff;\n                    mtr.at(hh,\
    \ c) = 0;\n                }\n            c++;\n        }\n        return mtr;\n\
    \    }\n    int rank_of_gauss_jordan() const {\n        for (int i = H * W - 1;\
    \ i >= 0; i--) {\n            if (elem[i]) return i / W + 1;\n        }\n    \
    \    return 0;\n    }\n    T determinant_of_upper_triangle() const {\n       \
    \ T ret = 1;\n        for (int i = 0; i < H; i++) ret *= get(i, i);\n        return\
    \ ret;\n    }\n    int inverse() {\n        assert(H == W);\n        std::vector<std::vector<T>>\
    \ ret = Identity(H), tmp = *this;\n        int rank = 0;\n        for (int i =\
    \ 0; i < H; i++) {\n            int ti = i;\n            while (ti < H and tmp[ti][i]\
    \ == 0) ti++;\n            if (ti == H) {\n                continue;\n       \
    \     } else {\n                rank++;\n            }\n            ret[i].swap(ret[ti]),\
    \ tmp[i].swap(tmp[ti]);\n            T inv = T(1) / tmp[i][i];\n            for\
    \ (int j = 0; j < W; j++) ret[i][j] *= inv;\n            for (int j = i + 1; j\
    \ < W; j++) tmp[i][j] *= inv;\n            for (int h = 0; h < H; h++) {\n   \
    \             if (i == h) continue;\n                const T c = -tmp[h][i];\n\
    \                for (int j = 0; j < W; j++) ret[h][j] += ret[i][j] * c;\n   \
    \             for (int j = i + 1; j < W; j++) tmp[h][j] += tmp[i][j] * c;\n  \
    \          }\n        }\n        *this = ret;\n        return rank;\n    }\n \
    \   friend std::vector<T> operator*(const matrix &m, const std::vector<T> &v)\
    \ {\n        assert(m.W == int(v.size()));\n        std::vector<T> ret(m.H);\n\
    \        for (int i = 0; i < m.H; i++) {\n            for (int j = 0; j < m.W;\
    \ j++) ret[i] += m.get(i, j) * v[j];\n        }\n        return ret;\n    }\n\
    \    friend std::vector<T> operator*(const std::vector<T> &v, const matrix &m)\
    \ {\n        assert(int(v.size()) == m.H);\n        std::vector<T> ret(m.W);\n\
    \        for (int i = 0; i < m.H; i++) {\n            for (int j = 0; j < m.W;\
    \ j++) ret[j] += v[i] * m.get(i, j);\n        }\n        return ret;\n    }\n\
    \    std::vector<T> prod(const std::vector<T> &v) const { return (*this) * v;\
    \ }\n    std::vector<T> prod_left(const std::vector<T> &v) const { return v *\
    \ (*this); }\n    friend std::ostream &operator<<(std::ostream &os, const matrix\
    \ &x) {\n        os << \"[(\" << x.H << \" * \" << x.W << \" matrix)\";\n    \
    \    os << \"\\n[column sums: \";\n        for (int j = 0; j < x.W; j++) {\n \
    \           T s = 0;\n            for (int i = 0; i < x.H; i++) s += x.get(i,\
    \ j);\n            os << s << \",\";\n        }\n        os << \"]\";\n      \
    \  for (int i = 0; i < x.H; i++) {\n            os << \"\\n[\";\n            for\
    \ (int j = 0; j < x.W; j++) os << x.get(i, j) << \",\";\n            os << \"\
    ]\";\n        }\n        os << \"]\\n\";\n        return os;\n    }\n    friend\
    \ std::istream &operator>>(std::istream &is, matrix &x) {\n        for (auto &v\
    \ : x.elem) is >> v;\n        return is;\n    }\n};\n\n// Example: Fibonacci numbers\
    \ f(n) = af(n - 1) + bf(n - 2)\n// (a = b = 1): 0=>1, 1=>1, 2=>2, 3=>3, 4=>5,\
    \ ...\ntemplate <typename T> T Fibonacci(long long int k, int a = 1, int b = 1)\
    \ {\n    matrix<T> mat(2, 2);\n    mat[0][1] = 1;\n    mat[1][0] = b;\n    mat[1][1]\
    \ = a;\n    return mat.pow(k + 1)[0][1];\n}\n#line 4 \"linear_algebra_matrix/characteristic_poly.hpp\"\
    \n#include <utility>\n#line 6 \"linear_algebra_matrix/characteristic_poly.hpp\"\
    \n\n// Upper Hessenberg reduction of square matrices\n// Complexity: O(n^3)\n\
    // Reference:\n// http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf\ntemplate\
    \ <class Tp> void hessenberg_reduction(matrix<Tp> &M) {\n    assert(M.height()\
    \ == M.width());\n    const int N = M.height();\n    for (int r = 0; r < N - 2;\
    \ r++) {\n        int piv = matrix<Tp>::choose_pivot(M, r + 1, r);\n        if\
    \ (piv < 0) continue;\n        for (int i = 0; i < N; i++) std::swap(M[r + 1][i],\
    \ M[piv][i]);\n        for (int i = 0; i < N; i++) std::swap(M[i][r + 1], M[i][piv]);\n\
    \n        const auto rinv = Tp(1) / M[r + 1][r];\n        for (int i = r + 2;\
    \ i < N; i++) {\n            const auto n = M[i][r] * rinv;\n            for (int\
    \ j = 0; j < N; j++) M[i][j] -= M[r + 1][j] * n;\n            for (int j = 0;\
    \ j < N; j++) M[j][r + 1] += M[j][i] * n;\n        }\n    }\n}\n\n// Characteristic\
    \ polynomial of matrix M (|xI - M|)\n// Complexity: O(n^3)\n// R. Rehman, I. C.\
    \ Ipsen, \"La Budde's Method for Computing Characteristic Polynomials,\" 2011.\n\
    template <class Tp> std::vector<Tp> characteristic_poly(matrix<Tp> M) {\n    hessenberg_reduction(M);\n\
    \    const int N = M.height();\n    std::vector<std::vector<Tp>> p(N + 1); //\
    \ p[i + 1] = (Characteristic polynomial of i-th leading principal minor)\n   \
    \ p[0] = {1};\n    for (int i = 0; i < N; i++) {\n        p[i + 1].assign(i +\
    \ 2, 0);\n        for (int j = 0; j < i + 1; j++) p[i + 1][j + 1] += p[i][j];\n\
    \        for (int j = 0; j < i + 1; j++) p[i + 1][j] -= p[i][j] * M[i][i];\n \
    \       Tp betas = 1;\n        for (int j = i - 1; j >= 0; j--) {\n          \
    \  betas *= M[j + 1][j];\n            Tp hb = -M[j][i] * betas;\n            for\
    \ (int k = 0; k < j + 1; k++) p[i + 1][k] += hb * p[j][k];\n        }\n    }\n\
    \    return p[N];\n}\n"
  code: "#pragma once\n#include \"matrix.hpp\"\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n// Upper Hessenberg reduction of square matrices\n// Complexity:\
    \ O(n^3)\n// Reference:\n// http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf\n\
    template <class Tp> void hessenberg_reduction(matrix<Tp> &M) {\n    assert(M.height()\
    \ == M.width());\n    const int N = M.height();\n    for (int r = 0; r < N - 2;\
    \ r++) {\n        int piv = matrix<Tp>::choose_pivot(M, r + 1, r);\n        if\
    \ (piv < 0) continue;\n        for (int i = 0; i < N; i++) std::swap(M[r + 1][i],\
    \ M[piv][i]);\n        for (int i = 0; i < N; i++) std::swap(M[i][r + 1], M[i][piv]);\n\
    \n        const auto rinv = Tp(1) / M[r + 1][r];\n        for (int i = r + 2;\
    \ i < N; i++) {\n            const auto n = M[i][r] * rinv;\n            for (int\
    \ j = 0; j < N; j++) M[i][j] -= M[r + 1][j] * n;\n            for (int j = 0;\
    \ j < N; j++) M[j][r + 1] += M[j][i] * n;\n        }\n    }\n}\n\n// Characteristic\
    \ polynomial of matrix M (|xI - M|)\n// Complexity: O(n^3)\n// R. Rehman, I. C.\
    \ Ipsen, \"La Budde's Method for Computing Characteristic Polynomials,\" 2011.\n\
    template <class Tp> std::vector<Tp> characteristic_poly(matrix<Tp> M) {\n    hessenberg_reduction(M);\n\
    \    const int N = M.height();\n    std::vector<std::vector<Tp>> p(N + 1); //\
    \ p[i + 1] = (Characteristic polynomial of i-th leading principal minor)\n   \
    \ p[0] = {1};\n    for (int i = 0; i < N; i++) {\n        p[i + 1].assign(i +\
    \ 2, 0);\n        for (int j = 0; j < i + 1; j++) p[i + 1][j + 1] += p[i][j];\n\
    \        for (int j = 0; j < i + 1; j++) p[i + 1][j] -= p[i][j] * M[i][i];\n \
    \       Tp betas = 1;\n        for (int j = i - 1; j >= 0; j--) {\n          \
    \  betas *= M[j + 1][j];\n            Tp hb = -M[j][i] * betas;\n            for\
    \ (int k = 0; k < j + 1; k++) p[i + 1][k] += hb * p[j][k];\n        }\n    }\n\
    \    return p[N];\n}\n"
  dependsOn:
  - linear_algebra_matrix/matrix.hpp
  isVerificationFile: false
  path: linear_algebra_matrix/characteristic_poly.hpp
  requiredBy: []
  timestamp: '2021-06-20 13:43:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/characteristic_poly.test.cpp
documentation_of: linear_algebra_matrix/characteristic_poly.hpp
layout: document
title: "Characteristic polynomial \uFF08\u884C\u5217\u306E\u7279\u6027\u591A\u9805\
  \u5F0F\uFF09"
---

体上の $n$ 次正方行列 $M$ の特性多項式 $p_M(x) = \det (xI - M)$ を $O(n^3)$ で求める決定的アルゴリズム．

## やっていること

入力として与えられた正方行列 $M$ に (upper) Hessenberg reduction を施した後，これに対して $M$ の首座小行列の特性多項式を再帰的に求めていく（La Budde's method, [1]）．(Upper) Hessenberg reduction とは，行列に相似変換を施すことでその対角成分より2つ以上左下側の成分を全てゼロにするというもので，このような変換は特に Householder 変換の組合せによって可能である（もちろん相似変換で特性多項式は不変）．

## References

- [1] R. Rehman, I. C. Ipsen, "La Budde's Method for Computing Characteristic Polynomials," 2011.
