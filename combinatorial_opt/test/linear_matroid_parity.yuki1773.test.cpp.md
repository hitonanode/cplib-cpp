---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/linear_matroid_parity.hpp
    title: "Linear matroid parity (unweighted) \uFF08\u7DDA\u5F62\u30DE\u30C8\u30ED\
      \u30A4\u30C9\u30D1\u30EA\u30C6\u30A3\uFF09"
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
    PROBLEM: https://yukicoder.me/problems/no/1773
    links:
    - https://yukicoder.me/problems/no/1773
  bundledCode: "#line 1 \"combinatorial_opt/test/linear_matroid_parity.yuki1773.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1773\"\n#line 2 \"linear_algebra_matrix/matrix.hpp\"\
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
    \    }\n};\n#line 4 \"combinatorial_opt/linear_matroid_parity.hpp\"\n#include\
    \ <chrono>\n#include <numeric>\n#include <random>\n#line 9 \"combinatorial_opt/linear_matroid_parity.hpp\"\
    \n\n// Solve linear matroid parity problem and return (especially lexicographically\
    \ smallest) binary\n// vector\n// Complexity: O(d^2 (d + m)), d: dimension, m:\
    \ number of input vector pairs\n// Reference:\n// [1] H. Y. Cheung, L. C. Lau,\
    \ K. M. Leung,\n//     \"Algebraic Algorithms for Linear Matroid Parity Problems,\"\
    \n//     ACM Transactions on Algorithms, 10(3), 1-26, 2014.\ntemplate <class ModInt>\n\
    std::vector<bool>\nlinear_matroid_parity(std::vector<std::pair<std::vector<ModInt>,\
    \ std::vector<ModInt>>> bcs,\n                      long long seed = std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {\n    if (bcs.empty()) return {};\n    const int r = bcs[0].first.size(), r2\
    \ = (r + 1) / 2;\n    int m = bcs.size();\n    for (auto &v : bcs) v.first.resize(r2\
    \ * 2), v.second.resize(r2 * 2);\n\n    std::mt19937 mt(seed);\n    std::uniform_int_distribution<int>\
    \ d(0, ModInt::mod() - 1);\n\n    std::vector<ModInt> x(m), xadd(r2);\n\n    matrix<ModInt>\
    \ Yinv; // (r2 * 2) * (r2 * 2) matrix\n    int rankY = -1;\n    while (rankY <\
    \ r2 * 2) {\n        Yinv = matrix<ModInt>(r2 * 2, r2 * 2);\n\n        auto add_i\
    \ = [&](int i) {\n            x[i] = d(mt);\n            const auto &b = bcs[i].first,\
    \ &c = bcs[i].second;\n            for (int j = 0; j < r2 * 2; j++) {\n      \
    \          for (int k = 0; k < r2 * 2; k++) Yinv[j][k] += x[i] * (b[j] * c[k]\
    \ - c[j] * b[k]);\n            }\n        };\n        for (int i = 0; i < m; ++i)\
    \ add_i(i);\n\n        int num_add_vec = (r2 * 2 - Yinv.rank()) / 2;\n\n     \
    \   bcs.resize(m + num_add_vec,\n                   std::make_pair(std::vector<ModInt>(r2\
    \ * 2), std::vector<ModInt>(r2 * 2)));\n        x.resize(bcs.size());\n      \
    \  for (int i = m; i < int(bcs.size()); ++i) {\n            for (auto &x : bcs[i].first)\
    \ x = d(mt);\n            for (auto &x : bcs[i].second) x = d(mt);\n        }\n\
    \n        for (int i = m; i < int(bcs.size()); i++) add_i(i);\n        rankY =\
    \ Yinv.inverse();\n    }\n\n    std::vector<bool> ret(bcs.size(), 1);\n\n    auto\
    \ try_erase_i = [&](int i) {\n        auto b = bcs[i].first, c = bcs[i].second;\n\
    \        b.resize(r2 * 2, 0), c.resize(r2 * 2, 0);\n        std::vector<ModInt>\
    \ Yib = Yinv * b, Yic = Yinv * c;\n        ModInt bYic = std::inner_product(b.begin(),\
    \ b.end(), Yic.begin(), ModInt());\n        ModInt a00 = bYic * x[i] + 1;\n  \
    \      if (a00 == ModInt()) return;\n        ret[i] = 0;\n        const ModInt\
    \ f = x[i] / a00;\n        for (int j = 0; j < r2 * 2; ++j) {\n            for\
    \ (int k = 0; k < r2 * 2; ++k) {\n                Yinv[j][k] -= f * (Yib[j] *\
    \ Yic[k] - Yic[j] * Yib[k]);\n            }\n        }\n    };\n\n    for (int\
    \ i = m; i < int(bcs.size()); ++i) try_erase_i(i);\n    for (int i = 0; i < m;\
    \ i++) try_erase_i(i);\n    ret.resize(m);\n    return ret;\n}\n\n// Solve linear\
    \ matroid parity problem, size-only (no construction)\ntemplate <class ModInt>\n\
    int linear_matroid_parity_size(\n    const std::vector<std::pair<std::vector<ModInt>,\
    \ std::vector<ModInt>>> &bcs,\n    long long seed = std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {\n\n    if (bcs.empty()) return 0;\n\n    std::mt19937 mt(seed);\n    std::uniform_int_distribution<int>\
    \ d(0, ModInt::mod() - 1);\n\n    const int r = bcs[0].first.size();\n    matrix<ModInt>\
    \ mat(r, r);\n    for (const auto &bc : bcs) {\n        const auto &b = bc.first,\
    \ &c = bc.second;\n        ModInt x = d(mt);\n        for (int i = 0; i < r; ++i)\
    \ {\n            for (int j = 0; j < r; ++j) mat[i][j] += x * (b[i] * c[j] - b[j]\
    \ * c[i]);\n        }\n    }\n    return mat.rank() / 2;\n}\n#line 3 \"modint.hpp\"\
    \n#include <iostream>\n#include <set>\n#line 6 \"modint.hpp\"\n\ntemplate <int\
    \ md> struct ModInt {\n    using lint = long long;\n    constexpr static int mod()\
    \ { return md; }\n    static int get_primitive_root() {\n        static int primitive_root\
    \ = 0;\n        if (!primitive_root) {\n            primitive_root = [&]() {\n\
    \                std::set<int> fac;\n                int v = md - 1;\n       \
    \         for (lint i = 2; i * i <= v; i++)\n                    while (v % i\
    \ == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n  \
    \              for (int g = 1; g < md; g++) {\n                    bool ok = true;\n\
    \                    for (auto i : fac)\n                        if (ModInt(g).pow((md\
    \ - 1) / i) == 1) {\n                            ok = false;\n               \
    \             break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root;\n    }\n    int val_;\n    int val() const\
    \ noexcept { return val_; }\n    constexpr ModInt() : val_(0) {}\n    constexpr\
    \ ModInt &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n \
    \   constexpr ModInt(lint v) { _setval(v % md + md); }\n    constexpr explicit\
    \ operator bool() const { return val_ != 0; }\n    constexpr ModInt operator+(const\
    \ ModInt &x) const {\n        return ModInt()._setval((lint)val_ + x.val_);\n\
    \    }\n    constexpr ModInt operator-(const ModInt &x) const {\n        return\
    \ ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    constexpr ModInt operator*(const\
    \ ModInt &x) const {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n\
    \    }\n    constexpr ModInt operator/(const ModInt &x) const {\n        return\
    \ ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n    constexpr ModInt\
    \ operator-() const { return ModInt()._setval(md - val_); }\n    constexpr ModInt\
    \ &operator+=(const ModInt &x) { return *this = *this + x; }\n    constexpr ModInt\
    \ &operator-=(const ModInt &x) { return *this = *this - x; }\n    constexpr ModInt\
    \ &operator*=(const ModInt &x) { return *this = *this * x; }\n    constexpr ModInt\
    \ &operator/=(const ModInt &x) { return *this = *this / x; }\n    friend constexpr\
    \ ModInt operator+(lint a, const ModInt &x) { return ModInt(a) + x; }\n    friend\
    \ constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt(a) - x;\
    \ }\n    friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt(a)\
    \ * x; }\n    friend constexpr ModInt operator/(lint a, const ModInt &x) { return\
    \ ModInt(a) / x; }\n    constexpr bool operator==(const ModInt &x) const { return\
    \ val_ == x.val_; }\n    constexpr bool operator!=(const ModInt &x) const { return\
    \ val_ != x.val_; }\n    constexpr bool operator<(const ModInt &x) const {\n \
    \       return val_ < x.val_;\n    } // To use std::map<ModInt, T>\n    friend\
    \ std::istream &operator>>(std::istream &is, ModInt &x) {\n        lint t;\n \
    \       return is >> t, x = ModInt(t), is;\n    }\n    constexpr friend std::ostream\
    \ &operator<<(std::ostream &os, const ModInt &x) {\n        return os << x.val_;\n\
    \    }\n\n    constexpr ModInt pow(lint n) const {\n        ModInt ans = 1, tmp\
    \ = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n        \
    \    tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n    static\
    \ constexpr int cache_limit = std::min(md, 1 << 21);\n    static std::vector<ModInt>\
    \ facs, facinvs, invs;\n\n    constexpr static void _precalculation(int N) {\n\
    \        const int l0 = facs.size();\n        if (N > md) N = md;\n        if\
    \ (N <= l0) return;\n        facs.resize(N), facinvs.resize(N), invs.resize(N);\n\
    \        for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i;\n        facinvs[N\
    \ - 1] = facs.back().pow(md - 2);\n        for (int i = N - 2; i >= l0; i--) facinvs[i]\
    \ = facinvs[i + 1] * (i + 1);\n        for (int i = N - 1; i >= l0; i--) invs[i]\
    \ = facinvs[i] * facs[i - 1];\n    }\n\n    constexpr ModInt inv() const {\n \
    \       if (this->val_ < cache_limit) {\n            if (facs.empty()) facs =\
    \ {1}, facinvs = {1}, invs = {0};\n            while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n            return invs[this->val_];\n  \
    \      } else {\n            return this->pow(md - 2);\n        }\n    }\n   \
    \ constexpr ModInt fac() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val_];\n    }\n\
    \    constexpr ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    constexpr ModInt doublefac() const {\n        lint k = (this->val_ +\
    \ 1) / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n\n    constexpr ModInt nCr(int r) const {\n        if (r < 0 or this->val_\
    \ < r) return ModInt(0);\n        return this->fac() * (*this - r).facinv() *\
    \ ModInt(r).facinv();\n    }\n\n    constexpr ModInt nPr(int r) const {\n    \
    \    if (r < 0 or this->val_ < r) return ModInt(0);\n        return this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    static ModInt binom(int n, int r) {\n\
    \        static long long bruteforce_times = 0;\n\n        if (r < 0 or n < r)\
    \ return ModInt(0);\n        if (n <= bruteforce_times or n < (int)facs.size())\
    \ return ModInt(n).nCr(r);\n\n        r = std::min(r, n - r);\n\n        ModInt\
    \ ret = ModInt(r).facinv();\n        for (int i = 0; i < r; ++i) ret *= n - i;\n\
    \        bruteforce_times += r;\n\n        return ret;\n    }\n\n    // Multinomial\
    \ coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)\n    // Complexity:\
    \ O(sum(ks))\n    template <class Vec> static ModInt multinomial(const Vec &ks)\
    \ {\n        ModInt ret{1};\n        int sum = 0;\n        for (int k : ks) {\n\
    \            assert(k >= 0);\n            ret *= ModInt(k).facinv(), sum += k;\n\
    \        }\n        return ret * ModInt(sum).fac();\n    }\n\n    // Catalan number,\
    \ C_n = binom(2n, n) / (n + 1)\n    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4\
    \ = 14, ...\n    // https://oeis.org/A000108\n    // Complexity: O(n)\n    static\
    \ ModInt catalan(int n) {\n        if (n < 0) return ModInt(0);\n        return\
    \ ModInt(n * 2).fac() * ModInt(n + 1).facinv() * ModInt(n).facinv();\n    }\n\n\
    \    ModInt sqrt() const {\n        if (val_ == 0) return 0;\n        if (md ==\
    \ 2) return val_;\n        if (pow((md - 1) / 2) != 1) return 0;\n        ModInt\
    \ b = 1;\n        while (b.pow((md - 1) / 2) == 1) b += 1;\n        int e = 0,\
    \ m = md - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j\
    \ - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val_, md - x.val_));\n    }\n};\ntemplate <int\
    \ md> std::vector<ModInt<md>> ModInt<md>::facs = {1};\ntemplate <int md> std::vector<ModInt<md>>\
    \ ModInt<md>::facinvs = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::invs\
    \ = {0};\n\nusing ModInt998244353 = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n\
    // using mint = ModInt<1000000007>;\n#line 8 \"combinatorial_opt/test/linear_matroid_parity.yuki1773.test.cpp\"\
    \nusing mint = ModInt<1000000007>;\nusing namespace std;\n\nint main() {\n   \
    \ cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, M;\n    cin >> N\
    \ >> M;\n    vector<pair<vector<mint>, vector<mint>>> uvs;\n\n    while (M--)\
    \ {\n        int u, v, w;\n        cin >> u >> v >> w;\n        --u, --v, --w;\n\
    \        vector<mint> a(N), b(N);\n        a[u] = b[v] = 1, a[w] = b[w] = -1;\n\
    \        uvs.emplace_back(a, b);\n    }\n\n    auto sol = linear_matroid_parity(uvs,\
    \ 14786);\n    cout << accumulate(sol.begin(), sol.end(), 0) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1773\"\n#include \"../linear_matroid_parity.hpp\"\
    \n#include \"../../modint.hpp\"\n#include <iostream>\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\nusing mint = ModInt<1000000007>;\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n \
    \   int N, M;\n    cin >> N >> M;\n    vector<pair<vector<mint>, vector<mint>>>\
    \ uvs;\n\n    while (M--) {\n        int u, v, w;\n        cin >> u >> v >> w;\n\
    \        --u, --v, --w;\n        vector<mint> a(N), b(N);\n        a[u] = b[v]\
    \ = 1, a[w] = b[w] = -1;\n        uvs.emplace_back(a, b);\n    }\n\n    auto sol\
    \ = linear_matroid_parity(uvs, 14786);\n    cout << accumulate(sol.begin(), sol.end(),\
    \ 0) << '\\n';\n}\n"
  dependsOn:
  - combinatorial_opt/linear_matroid_parity.hpp
  - linear_algebra_matrix/matrix.hpp
  - modint.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/linear_matroid_parity.yuki1773.test.cpp
  requiredBy: []
  timestamp: '2023-12-26 21:26:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/linear_matroid_parity.yuki1773.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/linear_matroid_parity.yuki1773.test.cpp
- /verify/combinatorial_opt/test/linear_matroid_parity.yuki1773.test.cpp.html
title: combinatorial_opt/test/linear_matroid_parity.yuki1773.test.cpp
---