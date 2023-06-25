---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/characteristic_poly.hpp
    title: "Characteristic polynomial \uFF08\u884C\u5217\u306E\u7279\u6027\u591A\u9805\
      \u5F0F\uFF09"
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/determinant_of_first_degree_poly_mat.hpp
    title: "Determinant of $M_0 + M_1 x$ \uFF08\u5404\u8981\u7D20\u304C\u9AD8\u3005\
      \ $1$ \u6B21\u306E\u884C\u5217\u306E\u884C\u5217\u5F0F\uFF09"
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/hessenberg_reduction.hpp
    title: Hessenberg reduction of matrix
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/matrix.hpp
    title: linear_algebra_matrix/matrix.hpp
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1907
    links:
    - https://yukicoder.me/problems/no/1907
  bundledCode: "#line 1 \"linear_algebra_matrix/test/determinant_of_first_degree_poly_mat.yuki1907.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1907\"\n#line 2 \"linear_algebra_matrix/matrix.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <iterator>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace matrix_\
    \ {\nstruct has_id_method_impl {\n    template <class T_> static auto check(T_\
    \ *) -> decltype(T_::id(), std::true_type());\n    template <class T_> static\
    \ auto check(...) -> std::false_type;\n};\ntemplate <class T_> struct has_id :\
    \ decltype(has_id_method_impl::check<T_>(nullptr)) {};\n} // namespace matrix_\n\
    \ntemplate <typename T> struct matrix {\n    int H, W;\n    std::vector<T> elem;\n\
    \    typename std::vector<T>::iterator operator[](int i) { return elem.begin()\
    \ + i * W; }\n    inline T &at(int i, int j) { return elem[i * W + j]; }\n   \
    \ inline T get(int i, int j) const { return elem[i * W + j]; }\n    int height()\
    \ const { return H; }\n    int width() const { return W; }\n    std::vector<std::vector<T>>\
    \ vecvec() const {\n        std::vector<std::vector<T>> ret(H);\n        for (int\
    \ i = 0; i < H; i++) {\n            std::copy(elem.begin() + i * W, elem.begin()\
    \ + (i + 1) * W, std::back_inserter(ret[i]));\n        }\n        return ret;\n\
    \    }\n    operator std::vector<std::vector<T>>() const { return vecvec(); }\n\
    \    matrix() = default;\n    matrix(int H, int W) : H(H), W(W), elem(H * W) {}\n\
    \    matrix(const std::vector<std::vector<T>> &d) : H(d.size()), W(d.size() ?\
    \ d[0].size() : 0) {\n        for (auto &raw : d) std::copy(raw.begin(), raw.end(),\
    \ std::back_inserter(elem));\n    }\n\n    template <typename T2, typename std::enable_if<matrix_::has_id<T2>::value>::type\
    \ * = nullptr>\n    static T2 _T_id() {\n        return T2::id();\n    }\n   \
    \ template <typename T2, typename std::enable_if<!matrix_::has_id<T2>::value>::type\
    \ * = nullptr>\n    static T2 _T_id() {\n        return T2(1);\n    }\n\n    static\
    \ matrix Identity(int N) {\n        matrix ret(N, N);\n        for (int i = 0;\
    \ i < N; i++) ret.at(i, i) = _T_id<T>();\n        return ret;\n    }\n\n    matrix\
    \ operator-() const {\n        matrix ret(H, W);\n        for (int i = 0; i <\
    \ H * W; i++) ret.elem[i] = -elem[i];\n        return ret;\n    }\n    matrix\
    \ operator*(const T &v) const {\n        matrix ret = *this;\n        for (auto\
    \ &x : ret.elem) x *= v;\n        return ret;\n    }\n    matrix operator/(const\
    \ T &v) const {\n        matrix ret = *this;\n        const T vinv = _T_id<T>()\
    \ / v;\n        for (auto &x : ret.elem) x *= vinv;\n        return ret;\n   \
    \ }\n    matrix operator+(const matrix &r) const {\n        matrix ret = *this;\n\
    \        for (int i = 0; i < H * W; i++) ret.elem[i] += r.elem[i];\n        return\
    \ ret;\n    }\n    matrix operator-(const matrix &r) const {\n        matrix ret\
    \ = *this;\n        for (int i = 0; i < H * W; i++) ret.elem[i] -= r.elem[i];\n\
    \        return ret;\n    }\n    matrix operator*(const matrix &r) const {\n \
    \       matrix ret(H, r.W);\n        for (int i = 0; i < H; i++) {\n         \
    \   for (int k = 0; k < W; k++) {\n                for (int j = 0; j < r.W; j++)\
    \ ret.at(i, j) += this->get(i, k) * r.get(k, j);\n            }\n        }\n \
    \       return ret;\n    }\n    matrix &operator*=(const T &v) { return *this\
    \ = *this * v; }\n    matrix &operator/=(const T &v) { return *this = *this /\
    \ v; }\n    matrix &operator+=(const matrix &r) { return *this = *this + r; }\n\
    \    matrix &operator-=(const matrix &r) { return *this = *this - r; }\n    matrix\
    \ &operator*=(const matrix &r) { return *this = *this * r; }\n    bool operator==(const\
    \ matrix &r) const { return H == r.H and W == r.W and elem == r.elem; }\n    bool\
    \ operator!=(const matrix &r) const { return H != r.H or W != r.W or elem != r.elem;\
    \ }\n    bool operator<(const matrix &r) const { return elem < r.elem; }\n   \
    \ matrix pow(int64_t n) const {\n        matrix ret = Identity(H);\n        bool\
    \ ret_is_id = true;\n        if (n == 0) return ret;\n        for (int i = 63\
    \ - __builtin_clzll(n); i >= 0; i--) {\n            if (!ret_is_id) ret *= ret;\n\
    \            if ((n >> i) & 1) ret *= (*this), ret_is_id = false;\n        }\n\
    \        return ret;\n    }\n    std::vector<T> pow_vec(int64_t n, std::vector<T>\
    \ vec) const {\n        matrix x = *this;\n        while (n) {\n            if\
    \ (n & 1) vec = x * vec;\n            x *= x;\n            n >>= 1;\n        }\n\
    \        return vec;\n    };\n    matrix transpose() const {\n        matrix ret(W,\
    \ H);\n        for (int i = 0; i < H; i++) {\n            for (int j = 0; j <\
    \ W; j++) ret.at(j, i) = this->get(i, j);\n        }\n        return ret;\n  \
    \  }\n    // Gauss-Jordan elimination\n    // - Require inverse for every non-zero\
    \ element\n    // - Complexity: O(H^2 W)\n    template <typename T2, typename\
    \ std::enable_if<std::is_floating_point<T2>::value>::type * = nullptr>\n    static\
    \ int choose_pivot(const matrix<T2> &mtr, int h, int c) noexcept {\n        int\
    \ piv = -1;\n        for (int j = h; j < mtr.H; j++) {\n            if (mtr.get(j,\
    \ c) and (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv, c))))\n \
    \               piv = j;\n        }\n        return piv;\n    }\n    template\
    \ <typename T2, typename std::enable_if<!std::is_floating_point<T2>::value>::type\
    \ * = nullptr>\n    static int choose_pivot(const matrix<T2> &mtr, int h, int\
    \ c) noexcept {\n        for (int j = h; j < mtr.H; j++) {\n            if (mtr.get(j,\
    \ c) != T2()) return j;\n        }\n        return -1;\n    }\n    matrix gauss_jordan()\
    \ const {\n        int c = 0;\n        matrix mtr(*this);\n        std::vector<int>\
    \ ws;\n        ws.reserve(W);\n        for (int h = 0; h < H; h++) {\n       \
    \     if (c == W) break;\n            int piv = choose_pivot(mtr, h, c);\n   \
    \         if (piv == -1) {\n                c++;\n                h--;\n     \
    \           continue;\n            }\n            if (h != piv) {\n          \
    \      for (int w = 0; w < W; w++) {\n                    std::swap(mtr[piv][w],\
    \ mtr[h][w]);\n                    mtr.at(piv, w) *= -_T_id<T>(); // To preserve\
    \ sign of determinant\n                }\n            }\n            ws.clear();\n\
    \            for (int w = c; w < W; w++) {\n                if (mtr.at(h, w) !=\
    \ T()) ws.emplace_back(w);\n            }\n            const T hcinv = _T_id<T>()\
    \ / mtr.at(h, c);\n            for (int hh = 0; hh < H; hh++)\n              \
    \  if (hh != h) {\n                    const T coeff = mtr.at(hh, c) * hcinv;\n\
    \                    for (auto w : ws) mtr.at(hh, w) -= mtr.at(h, w) * coeff;\n\
    \                    mtr.at(hh, c) = T();\n                }\n            c++;\n\
    \        }\n        return mtr;\n    }\n    int rank_of_gauss_jordan() const {\n\
    \        for (int i = H * W - 1; i >= 0; i--) {\n            if (elem[i] != 0)\
    \ return i / W + 1;\n        }\n        return 0;\n    }\n    int rank() const\
    \ { return gauss_jordan().rank_of_gauss_jordan(); }\n\n    T determinant_of_upper_triangle()\
    \ const {\n        T ret = _T_id<T>();\n        for (int i = 0; i < H; i++) ret\
    \ *= get(i, i);\n        return ret;\n    }\n    int inverse() {\n        assert(H\
    \ == W);\n        std::vector<std::vector<T>> ret = Identity(H), tmp = *this;\n\
    \        int rank = 0;\n        for (int i = 0; i < H; i++) {\n            int\
    \ ti = i;\n            while (ti < H and tmp[ti][i] == T()) ti++;\n          \
    \  if (ti == H) {\n                continue;\n            } else {\n         \
    \       rank++;\n            }\n            ret[i].swap(ret[ti]), tmp[i].swap(tmp[ti]);\n\
    \            T inv = _T_id<T>() / tmp[i][i];\n            for (int j = 0; j <\
    \ W; j++) ret[i][j] *= inv;\n            for (int j = i + 1; j < W; j++) tmp[i][j]\
    \ *= inv;\n            for (int h = 0; h < H; h++) {\n                if (i ==\
    \ h) continue;\n                const T c = -tmp[h][i];\n                for (int\
    \ j = 0; j < W; j++) ret[h][j] += ret[i][j] * c;\n                for (int j =\
    \ i + 1; j < W; j++) tmp[h][j] += tmp[i][j] * c;\n            }\n        }\n \
    \       *this = ret;\n        return rank;\n    }\n    friend std::vector<T> operator*(const\
    \ matrix &m, const std::vector<T> &v) {\n        assert(m.W == int(v.size()));\n\
    \        std::vector<T> ret(m.H);\n        for (int i = 0; i < m.H; i++) {\n \
    \           for (int j = 0; j < m.W; j++) ret[i] += m.get(i, j) * v[j];\n    \
    \    }\n        return ret;\n    }\n    friend std::vector<T> operator*(const\
    \ std::vector<T> &v, const matrix &m) {\n        assert(int(v.size()) == m.H);\n\
    \        std::vector<T> ret(m.W);\n        for (int i = 0; i < m.H; i++) {\n \
    \           for (int j = 0; j < m.W; j++) ret[j] += v[i] * m.get(i, j);\n    \
    \    }\n        return ret;\n    }\n    std::vector<T> prod(const std::vector<T>\
    \ &v) const { return (*this) * v; }\n    std::vector<T> prod_left(const std::vector<T>\
    \ &v) const { return v * (*this); }\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const matrix &x) {\n        os << \"[(\" << x.H <<\
    \ \" * \" << x.W << \" matrix)\";\n        os << \"\\n[column sums: \";\n    \
    \    for (int j = 0; j < x.W; j++) {\n            T s = T();\n            for\
    \ (int i = 0; i < x.H; i++) s += x.get(i, j);\n            os << s << \",\";\n\
    \        }\n        os << \"]\";\n        for (int i = 0; i < x.H; i++) {\n  \
    \          os << \"\\n[\";\n            for (int j = 0; j < x.W; j++) os << x.get(i,\
    \ j) << \",\";\n            os << \"]\";\n        }\n        os << \"]\\n\";\n\
    \        return os;\n    }\n    template <class IStream> friend IStream &operator>>(IStream\
    \ &is, matrix &x) {\n        for (auto &v : x.elem) is >> v;\n        return is;\n\
    \    }\n};\n#line 4 \"linear_algebra_matrix/characteristic_poly.hpp\"\n\n// Characteristic\
    \ polynomial of upper Hessenberg matrix M (|xI - M|)\n// Complexity: O(n^3)\n\
    // R. Rehman, I. C. Ipsen, \"La Budde's Method for Computing Characteristic Polynomials,\"\
    \ 2011.\ntemplate <class Tp> std::vector<Tp> characteristic_poly_of_hessenberg(matrix<Tp>\
    \ &M) {\n    const int N = M.height();\n    // p[i + 1] = (Characteristic polynomial\
    \ of i-th leading principal minor)\n    std::vector<std::vector<Tp>> p(N + 1);\n\
    \    p[0] = {1};\n    for (int i = 0; i < N; i++) {\n        p[i + 1].assign(i\
    \ + 2, Tp());\n        for (int j = 0; j < i + 1; j++) p[i + 1][j + 1] += p[i][j];\n\
    \        for (int j = 0; j < i + 1; j++) p[i + 1][j] -= p[i][j] * M[i][i];\n \
    \       Tp betas = 1;\n        for (int j = i - 1; j >= 0; j--) {\n          \
    \  betas *= M[j + 1][j];\n            Tp hb = -M[j][i] * betas;\n            for\
    \ (int k = 0; k < j + 1; k++) p[i + 1][k] += hb * p[j][k];\n        }\n    }\n\
    \    return p[N];\n}\n#line 5 \"linear_algebra_matrix/hessenberg_reduction.hpp\"\
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
    \ j < N; j++) M[j][r + 1] += M[j][i] * n;\n        }\n    }\n}\n\ntemplate <class\
    \ Ring> void ring_hessenberg_reduction(matrix<Ring> &M) {\n    assert(M.height()\
    \ == M.width());\n    const int N = M.height();\n    for (int r = 0; r < N - 2;\
    \ r++) {\n        int piv = matrix<Ring>::choose_pivot(M, r + 1, r);\n       \
    \ if (piv < 0) continue;\n        for (int i = 0; i < N; i++) std::swap(M[r +\
    \ 1][i], M[piv][i]);\n        for (int i = 0; i < N; i++) std::swap(M[i][r + 1],\
    \ M[i][piv]);\n\n        for (int i = r + 2; i < N; i++) {\n            if (M[i][r]\
    \ == Ring()) continue;\n            Ring a = M[r + 1][r], b = M[i][r], m00 = 1,\
    \ m01 = 0, m10 = 0, m11 = 1;\n            while (a != Ring() and b != Ring())\
    \ {\n                if (a.val() > b.val()) {\n                    auto d = a.val()\
    \ / b.val();\n                    a -= b * d, m00 -= m10 * d, m01 -= m11 * d;\n\
    \                } else {\n                    auto d = b.val() / a.val();\n \
    \                   b -= a * d, m10 -= m00 * d, m11 -= m01 * d;\n            \
    \    }\n            }\n            if (a == Ring()) std::swap(a, b), std::swap(m00,\
    \ m10), std::swap(m01, m11);\n\n            for (int j = 0; j < N; j++) {\n  \
    \              Ring anew = M[r + 1][j] * m00 + M[i][j] * m01;\n              \
    \  Ring bnew = M[r + 1][j] * m10 + M[i][j] * m11;\n                M[r + 1][j]\
    \ = anew;\n                M[i][j] = bnew;\n            }\n            assert(M[i][r]\
    \ == 0);\n\n            for (int j = 0; j < N; j++) {\n                Ring anew\
    \ = M[j][r + 1] * m11 - M[j][i] * m10;\n                Ring bnew = -M[j][r +\
    \ 1] * m01 + M[j][i] * m00;\n                M[j][r + 1] = anew;\n           \
    \     M[j][i] = bnew;\n            }\n        }\n    }\n}\n#line 7 \"linear_algebra_matrix/determinant_of_first_degree_poly_mat.hpp\"\
    \n\n// det(M_0 + M_1 x), M0 , M1: n x n matrix of F_p\n// Complexity: O(n^3)\n\
    // Verified: https://yukicoder.me/problems/no/1907\ntemplate <class T>\nstd::vector<T>\
    \ determinant_of_first_degree_poly_mat(std::vector<std::vector<T>> M0,\n     \
    \                                               std::vector<std::vector<T>> M1)\
    \ {\n    const int N = M0.size();\n\n    int multiply_by_x = 0;\n    T detAdetBinv\
    \ = 1;\n\n    for (int p = 0; p < N; ++p) {\n        int pivot = -1;\n       \
    \ for (int row = p; row < N; ++row) {\n            if (M1[row][p] != T()) {\n\
    \                pivot = row;\n                break;\n            }\n       \
    \ }\n\n        if (pivot < 0) {\n            ++multiply_by_x;\n            if\
    \ (multiply_by_x > N) return std::vector<T>(N + 1);\n\n            for (int row\
    \ = 0; row < p; ++row) {\n                T v = M1[row][p];\n                M1[row][p]\
    \ = 0;\n                for (int i = 0; i < N; ++i) M0[i][p] -= v * M0[i][row];\n\
    \            }\n            for (int i = 0; i < N; ++i) std::swap(M0[i][p], M1[i][p]);\n\
    \n            --p;\n            continue;\n        }\n\n        if (pivot != p)\
    \ {\n            M1[pivot].swap(M1[p]);\n            M0[pivot].swap(M0[p]);\n\
    \            detAdetBinv *= -1;\n        }\n\n        T v = M1[p][p], vinv = v.inv();\n\
    \        detAdetBinv *= v;\n        for (int col = 0; col < N; ++col) {\n    \
    \        M0[p][col] *= vinv;\n            M1[p][col] *= vinv;\n        }\n\n \
    \       for (int row = 0; row < N; ++row) {\n            if (row == p) continue;\n\
    \            T v = M1[row][p];\n            for (int col = 0; col < N; ++col)\
    \ {\n                M0[row][col] -= M0[p][col] * v;\n                M1[row][col]\
    \ -= M1[p][col] * v;\n            }\n        }\n    }\n\n    for (auto &vec :\
    \ M0) {\n        for (auto &x : vec) x = -x;\n    }\n    matrix<T> tmp_mat(M0);\n\
    \    hessenberg_reduction(tmp_mat);\n    auto poly = characteristic_poly_of_hessenberg(tmp_mat);\n\
    \    for (auto &x : poly) x *= detAdetBinv;\n\n    poly.erase(poly.begin(), poly.begin()\
    \ + multiply_by_x);\n    poly.resize(N + 1);\n    return poly;\n}\n#line 2 \"\
    modint.hpp\"\n#include <iostream>\n#include <set>\n#line 5 \"modint.hpp\"\n\n\
    template <int md> struct ModInt {\n#if __cplusplus >= 201402L\n#define MDCONST\
    \ constexpr\n#else\n#define MDCONST\n#endif\n    using lint = long long;\n   \
    \ MDCONST static int mod() { return md; }\n    static int get_primitive_root()\
    \ {\n        static int primitive_root = 0;\n        if (!primitive_root) {\n\
    \            primitive_root = [&]() {\n                std::set<int> fac;\n  \
    \              int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n\
    \                    while (v % i == 0) fac.insert(i), v /= i;\n             \
    \   if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((md - 1) / i) == 1) {\n           \
    \                 ok = false;\n                            break;\n          \
    \              }\n                    if (ok) return g;\n                }\n \
    \               return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    MDCONST\
    \ ModInt() : val_(0) {}\n    MDCONST ModInt &_setval(lint v) { return val_ = (v\
    \ >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint v) { _setval(v % md +\
    \ md); }\n    MDCONST explicit operator bool() const { return val_ != 0; }\n \
    \   MDCONST ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    MDCONST ModInt operator-(const ModInt &x) const {\n \
    \       return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    MDCONST\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    MDCONST ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    MDCONST ModInt operator-() const { return ModInt()._setval(md - val_); }\n\
    \    MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md + x.val_);\n    }\n    friend MDCONST ModInt operator-(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md - x.val_ + md);\n\
    \    }\n    friend MDCONST ModInt operator*(lint a, const ModInt &x) {\n     \
    \   return ModInt()._setval(a % md * x.val_ % md);\n    }\n    friend MDCONST\
    \ ModInt operator/(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.inv().val() % md);\n    }\n    MDCONST bool operator==(const ModInt\
    \ &x) const { return val_ == x.val_; }\n    MDCONST bool operator!=(const ModInt\
    \ &x) const { return val_ != x.val_; }\n    MDCONST bool operator<(const ModInt\
    \ &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const {\n    \
    \    ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n & 1)\
    \ ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return ans;\n\
    \    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n    MDCONST\
    \ ModInt inv() const {\n        if (this->val_ < std::min(md >> 1, 1 << 21)) {\n\
    \            if (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n      \
    \      while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \            return invs[this->val_];\n        } else {\n            return this->pow(md\
    \ - 2);\n        }\n    }\n    MDCONST ModInt fac() const {\n        while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n        return facs[this->val_];\n\
    \    }\n    MDCONST ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    MDCONST ModInt doublefac() const {\n        lint k = (this->val_ + 1)\
    \ / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val_\
    \ < r.val_) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n  \
    \  MDCONST ModInt nPr(const ModInt &r) const {\n        return (this->val_ < r.val_)\
    \ ? 0 : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const\
    \ {\n        if (val_ == 0) return 0;\n        if (md == 2) return val_;\n   \
    \     if (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while\
    \ (b.pow((md - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n       \
    \ while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this)\
    \ * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while\
    \ (y != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 6 \"linear_algebra_matrix/test/determinant_of_first_degree_poly_mat.yuki1907.test.cpp\"\
    \nusing namespace std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int n;\n    cin >> n;\n    vector<vector<mint>>\
    \ M0(n, vector<mint>(n));\n    auto M1 = M0;\n\n    for (auto &v : M0) {\n   \
    \     for (auto &x : v) cin >> x;\n    }\n\n    for (auto &v : M1) {\n       \
    \ for (auto &x : v) cin >> x;\n    }\n\n    vector<mint> ret = determinant_of_first_degree_poly_mat(M0,\
    \ M1);\n    for (auto x : ret) cout << x << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1907\"\n#include \"../determinant_of_first_degree_poly_mat.hpp\"\
    \n#include \"../../modint.hpp\"\n#include <iostream>\n#include <vector>\nusing\
    \ namespace std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int n;\n    cin >> n;\n    vector<vector<mint>>\
    \ M0(n, vector<mint>(n));\n    auto M1 = M0;\n\n    for (auto &v : M0) {\n   \
    \     for (auto &x : v) cin >> x;\n    }\n\n    for (auto &v : M1) {\n       \
    \ for (auto &x : v) cin >> x;\n    }\n\n    vector<mint> ret = determinant_of_first_degree_poly_mat(M0,\
    \ M1);\n    for (auto x : ret) cout << x << '\\n';\n}\n"
  dependsOn:
  - linear_algebra_matrix/determinant_of_first_degree_poly_mat.hpp
  - linear_algebra_matrix/characteristic_poly.hpp
  - linear_algebra_matrix/matrix.hpp
  - linear_algebra_matrix/hessenberg_reduction.hpp
  - modint.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/determinant_of_first_degree_poly_mat.yuki1907.test.cpp
  requiredBy: []
  timestamp: '2023-05-21 18:11:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/determinant_of_first_degree_poly_mat.yuki1907.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/determinant_of_first_degree_poly_mat.yuki1907.test.cpp
- /verify/linear_algebra_matrix/test/determinant_of_first_degree_poly_mat.yuki1907.test.cpp.html
title: linear_algebra_matrix/test/determinant_of_first_degree_poly_mat.yuki1907.test.cpp
---
