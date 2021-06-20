---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/characteristic_poly.hpp
    title: "Characteristic polynomial \uFF08\u884C\u5217\u306E\u7279\u6027\u591A\u9805\
      \u5F0F\uFF09"
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
    PROBLEM: https://judge.yosupo.jp/problem/characteristic_polynomial
    links:
    - https://judge.yosupo.jp/problem/characteristic_polynomial
  bundledCode: "#line 1 \"linear_algebra_matrix/test/characteristic_poly.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/characteristic_polynomial\"\
    \n#line 2 \"linear_algebra_matrix/matrix.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <iostream>\n#include <iterator>\n#include\
    \ <type_traits>\n#include <vector>\n\n// CUT begin\ntemplate <typename T> struct\
    \ matrix {\n    int H, W;\n    std::vector<T> elem;\n    typename std::vector<T>::iterator\
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
    \    return p[N];\n}\n#line 3 \"modint.hpp\"\n#include <set>\n#line 5 \"modint.hpp\"\
    \n\n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus >= 201402L\n\
    #define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using lint = long\
    \ long;\n    MDCONST static int mod() { return md; }\n    static int get_primitive_root()\
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
    \    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n    MDCONST ModInt &_setval(lint\
    \ v) { return val = (v >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint\
    \ v) { _setval(v % md + md); }\n    MDCONST explicit operator bool() const { return\
    \ val != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ + x.val); }\n    MDCONST ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + md); }\n    MDCONST ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % md); }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % md); }\n  \
    \  MDCONST ModInt operator-() const { return ModInt()._setval(md - val); }\n \
    \   MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % md + x.val); }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x)\
    \ { return ModInt()._setval(a % md - x.val + md); }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) { return ModInt()._setval(a % md * x.val\
    \ % md); }\n    friend MDCONST ModInt operator/(lint a, const ModInt &x) {\n \
    \       return ModInt()._setval(a % md * x.inv() % md);\n    }\n    MDCONST bool\
    \ operator==(const ModInt &x) const { return val == x.val; }\n    MDCONST bool\
    \ operator!=(const ModInt &x) const { return val != x.val; }\n    MDCONST bool\
    \ operator<(const ModInt &x) const { return val < x.val; } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { return\
    \ os << x.val; }\n    MDCONST ModInt pow(lint n) const {\n        ModInt ans =\
    \ 1, tmp = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n \
    \           tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n  \
    \  static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static void _precalculation(int\
    \ N) {\n        int l0 = facs.size();\n        if (N > md) N = md;\n        if\
    \ (N <= l0) return;\n        facs.resize(N), facinvs.resize(N), invs.resize(N);\n\
    \        for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i;\n        facinvs[N\
    \ - 1] = facs.back().pow(md - 2);\n        for (int i = N - 2; i >= l0; i--) facinvs[i]\
    \ = facinvs[i + 1] * (i + 1);\n        for (int i = N - 1; i >= l0; i--) invs[i]\
    \ = facinvs[i] * facs[i - 1];\n    }\n    MDCONST lint inv() const {\n       \
    \ if (this->val < std::min(md >> 1, 1 << 21)) {\n            while (this->val\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val].val;\n\
    \        } else {\n            return this->pow(md - 2).val;\n        }\n    }\n\
    \    MDCONST ModInt fac() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val];\n    }\n\
    \    MDCONST ModInt facinv() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val];\n    }\n\
    \    MDCONST ModInt doublefac() const {\n        lint k = (this->val + 1) / 2;\n\
    \        return (this->val & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n\
    \                               : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n\
    \    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val <\
    \ r.val) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST\
    \ ModInt nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n\
    \        if (val == 0) return 0;\n        if (md == 2) return val;\n        if\
    \ (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md\
    \ - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m %\
    \ 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x\
    \ * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while (y\
    \ != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
    \ md - x.val));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 7 \"linear_algebra_matrix/test/characteristic_poly.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N;\n    cin >> N;\n    using mint = ModInt<998244353>;\n    matrix<mint>\
    \ M(N, N);\n    cin >> M;\n    auto poly = characteristic_poly<mint>(M);\n   \
    \ for (auto x : poly) cout << x << ' ';\n    cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/characteristic_polynomial\"\
    \n#include \"../characteristic_poly.hpp\"\n#include \"../../modint.hpp\"\n#include\
    \ \"../matrix.hpp\"\n#include <algorithm>\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int N;\n    cin >> N;\n    using mint = ModInt<998244353>;\n    matrix<mint>\
    \ M(N, N);\n    cin >> M;\n    auto poly = characteristic_poly<mint>(M);\n   \
    \ for (auto x : poly) cout << x << ' ';\n    cout << '\\n';\n}\n"
  dependsOn:
  - linear_algebra_matrix/characteristic_poly.hpp
  - linear_algebra_matrix/matrix.hpp
  - modint.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/characteristic_poly.test.cpp
  requiredBy: []
  timestamp: '2021-06-20 13:43:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/characteristic_poly.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/characteristic_poly.test.cpp
- /verify/linear_algebra_matrix/test/characteristic_poly.test.cpp.html
title: linear_algebra_matrix/test/characteristic_poly.test.cpp
---
