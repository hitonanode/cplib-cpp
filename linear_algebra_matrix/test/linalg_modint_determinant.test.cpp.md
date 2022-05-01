---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: linear_algebra_matrix/matrix.hpp
    title: linear_algebra_matrix/matrix.hpp
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':question:'
    path: number/modint_runtime.hpp
    title: number/modint_runtime.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/matrix_det
    links:
    - https://judge.yosupo.jp/problem/matrix_det
  bundledCode: "#line 1 \"linear_algebra_matrix/test/linalg_modint_determinant.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_det\"\n#line 2 \"modint.hpp\"\
    \n#include <iostream>\n#include <set>\n#include <vector>\n\ntemplate <int md>\
    \ struct ModInt {\n#if __cplusplus >= 201402L\n#define MDCONST constexpr\n#else\n\
    #define MDCONST\n#endif\n    using lint = long long;\n    MDCONST static int mod()\
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
    \ noexcept { return val_; }\n    MDCONST ModInt() : val_(0) {}\n    MDCONST ModInt\
    \ &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n    MDCONST\
    \ ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit operator bool()\
    \ const { return val_ != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ - x.val_ + md);\n    }\n    MDCONST ModInt operator*(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    MDCONST\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.inv().val() % md);\n    }\n    MDCONST ModInt operator-() const { return\
    \ ModInt()._setval(md - val_); }\n    MDCONST ModInt &operator+=(const ModInt\
    \ &x) { return *this = *this + x; }\n    MDCONST ModInt &operator-=(const ModInt\
    \ &x) { return *this = *this - x; }\n    MDCONST ModInt &operator*=(const ModInt\
    \ &x) { return *this = *this * x; }\n    MDCONST ModInt &operator/=(const ModInt\
    \ &x) { return *this = *this / x; }\n    friend MDCONST ModInt operator+(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md + x.val_);\n \
    \   }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x) {\n      \
    \  return ModInt()._setval(a % md - x.val_ + md);\n    }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) {\n        return ModInt()._setval(a % md\
    \ * x.val_ % md);\n    }\n    friend MDCONST ModInt operator/(lint a, const ModInt\
    \ &x) {\n        return ModInt()._setval(a % md * x.inv().val() % md);\n    }\n\
    \    MDCONST bool operator==(const ModInt &x) const { return val_ == x.val_; }\n\
    \    MDCONST bool operator!=(const ModInt &x) const { return val_ != x.val_; }\n\
    \    MDCONST bool operator<(const ModInt &x) const {\n        return val_ < x.val_;\n\
    \    } // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) {\n        lint t;\n        return is >> t, x = ModInt(t), is;\n\
    \    }\n    MDCONST friend std::ostream &operator<<(std::ostream &os, const ModInt\
    \ &x) {\n        return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const\
    \ {\n        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if\
    \ (n & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST\
    \ static void _precalculation(int N) {\n        int l0 = facs.size();\n      \
    \  if (N > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N),\
    \ facinvs.resize(N), invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n    \
    \    for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n\
    \        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n\
    \    }\n    MDCONST ModInt inv() const {\n        if (this->val_ < std::min(md\
    \ >> 1, 1 << 21)) {\n            while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val_];\n        } else {\n            return\
    \ this->pow(md - 2);\n        }\n    }\n    MDCONST ModInt fac() const {\n   \
    \     while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \        return facs[this->val_];\n    }\n    MDCONST ModInt facinv() const {\n\
    \        while (this->val_ >= int(facs.size())) _precalculation(facs.size() *\
    \ 2);\n        return facinvs[this->val_];\n    }\n    MDCONST ModInt doublefac()\
    \ const {\n        lint k = (this->val_ + 1) / 2;\n        return (this->val_\
    \ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n        \
    \                        : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST\
    \ ModInt nCr(const ModInt &r) const {\n        return (this->val_ < r.val_) ?\
    \ 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST ModInt\
    \ nPr(const ModInt &r) const {\n        return (this->val_ < r.val_) ? 0 : this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val_\
    \ == 0) return 0;\n        if (md == 2) return val_;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 5 \"number/modint_runtime.hpp\"\
    \n\nstruct ModIntRuntime {\nprivate:\n    static int md;\n\npublic:\n    using\
    \ lint = long long;\n    static int mod() { return md; }\n    int val_;\n    static\
    \ std::vector<ModIntRuntime> &facs() {\n        static std::vector<ModIntRuntime>\
    \ facs_;\n        return facs_;\n    }\n    static int &get_primitive_root() {\n\
    \        static int primitive_root_ = 0;\n        if (!primitive_root_) {\n  \
    \          primitive_root_ = [&]() {\n                std::set<int> fac;\n   \
    \             int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n\
    \                    while (v % i == 0) fac.insert(i), v /= i;\n             \
    \   if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModIntRuntime(g).power((md - 1) / i) == 1) {\n  \
    \                          ok = false;\n                            break;\n \
    \                       }\n                    if (ok) return g;\n           \
    \     }\n                return -1;\n            }();\n        }\n        return\
    \ primitive_root_;\n    }\n    static void set_mod(const int &m) {\n        if\
    \ (md != m) facs().clear();\n        md = m;\n        get_primitive_root() = 0;\n\
    \    }\n    ModIntRuntime &_setval(lint v) {\n        val_ = (v >= md ? v - md\
    \ : v);\n        return *this;\n    }\n    int val() const noexcept { return val_;\
    \ }\n    ModIntRuntime() : val_(0) {}\n    ModIntRuntime(lint v) { _setval(v %\
    \ md + md); }\n    explicit operator bool() const { return val_ != 0; }\n    ModIntRuntime\
    \ operator+(const ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val_\
    \ + x.val_);\n    }\n    ModIntRuntime operator-(const ModIntRuntime &x) const\
    \ {\n        return ModIntRuntime()._setval((lint)val_ - x.val_ + md);\n    }\n\
    \    ModIntRuntime operator*(const ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    ModIntRuntime operator/(const ModIntRuntime &x)\
    \ const {\n        return ModIntRuntime()._setval((lint)val_ * x.inv().val() %\
    \ md);\n    }\n    ModIntRuntime operator-() const { return ModIntRuntime()._setval(md\
    \ - val_); }\n    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this\
    \ = *this + x; }\n    ModIntRuntime &operator-=(const ModIntRuntime &x) { return\
    \ *this = *this - x; }\n    ModIntRuntime &operator*=(const ModIntRuntime &x)\
    \ { return *this = *this * x; }\n    ModIntRuntime &operator/=(const ModIntRuntime\
    \ &x) { return *this = *this / x; }\n    friend ModIntRuntime operator+(lint a,\
    \ const ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md + x.val_);\n\
    \    }\n    friend ModIntRuntime operator-(lint a, const ModIntRuntime &x) {\n\
    \        return ModIntRuntime()._setval(a % md - x.val_ + md);\n    }\n    friend\
    \ ModIntRuntime operator*(lint a, const ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a\
    \ % md * x.val_ % md);\n    }\n    friend ModIntRuntime operator/(lint a, const\
    \ ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md * x.inv().val()\
    \ % md);\n    }\n    bool operator==(const ModIntRuntime &x) const { return val_\
    \ == x.val_; }\n    bool operator!=(const ModIntRuntime &x) const { return val_\
    \ != x.val_; }\n    bool operator<(const ModIntRuntime &x) const {\n        return\
    \ val_ < x.val_;\n    } // To use std::map<ModIntRuntime, T>\n    friend std::istream\
    \ &operator>>(std::istream &is, ModIntRuntime &x) {\n        lint t;\n       \
    \ return is >> t, x = ModIntRuntime(t), is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const ModIntRuntime &x) {\n        return os << x.val_;\n    }\n\n    lint\
    \ power(lint n) const {\n        lint ans = 1, tmp = this->val_;\n        while\
    \ (n) {\n            if (n & 1) ans = ans * tmp % md;\n            tmp = tmp *\
    \ tmp % md;\n            n /= 2;\n        }\n        return ans;\n    }\n    ModIntRuntime\
    \ pow(lint n) const { return power(n); }\n    ModIntRuntime inv() const { return\
    \ this->pow(md - 2); }\n\n    ModIntRuntime fac() const {\n        int l0 = facs().size();\n\
    \        if (l0 > this->val_) return facs()[this->val_];\n\n        facs().resize(this->val_\
    \ + 1);\n        for (int i = l0; i <= this->val_; i++)\n            facs()[i]\
    \ = (i == 0 ? ModIntRuntime(1) : facs()[i - 1] * ModIntRuntime(i));\n        return\
    \ facs()[this->val_];\n    }\n\n    ModIntRuntime doublefac() const {\n      \
    \  lint k = (this->val_ + 1) / 2;\n        return (this->val_ & 1)\n         \
    \          ? ModIntRuntime(k * 2).fac() / (ModIntRuntime(2).pow(k) * ModIntRuntime(k).fac())\n\
    \                   : ModIntRuntime(k).fac() * ModIntRuntime(2).pow(k);\n    }\n\
    \n    ModIntRuntime nCr(const ModIntRuntime &r) const {\n        return (this->val_\
    \ < r.val_) ? ModIntRuntime(0)\n                                     : this->fac()\
    \ / ((*this - r).fac() * r.fac());\n    }\n\n    ModIntRuntime sqrt() const {\n\
    \        if (val_ == 0) return 0;\n        if (md == 2) return val_;\n       \
    \ if (power((md - 1) / 2) != 1) return 0;\n        ModIntRuntime b = 1;\n    \
    \    while (b.power((md - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n\
    \        while (m % 2 == 0) m >>= 1, e++;\n        ModIntRuntime x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModIntRuntime\
    \ z = b.power(m);\n        while (y != 1) {\n            int j = 0;\n        \
    \    ModIntRuntime t = y;\n            while (t != 1) j++, t *= t;\n         \
    \   z = z.power(1LL << (e - j - 1));\n            x *= z, z *= z, y *= z;\n  \
    \          e = j;\n        }\n        return ModIntRuntime(std::min(x.val_, md\
    \ - x.val_));\n    }\n};\nint ModIntRuntime::md = 1;\n#line 2 \"linear_algebra_matrix/matrix.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <iterator>\n\
    #include <type_traits>\n#include <utility>\n#line 9 \"linear_algebra_matrix/matrix.hpp\"\
    \n\nnamespace matrix_ {\nstruct has_id_method_impl {\n    template <class T_>\
    \ static auto check(T_ *) -> decltype(T_::id(), std::true_type());\n    template\
    \ <class T_> static auto check(...) -> std::false_type;\n};\ntemplate <class T_>\
    \ struct has_id : decltype(has_id_method_impl::check<T_>(nullptr)) {};\n} // namespace\
    \ matrix_\n\ntemplate <typename T> struct matrix {\n    int H, W;\n    std::vector<T>\
    \ elem;\n    typename std::vector<T>::iterator operator[](int i) { return elem.begin()\
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
    \ ti = i;\n            while (ti < H and tmp[ti][i] == 0) ti++;\n            if\
    \ (ti == H) {\n                continue;\n            } else {\n             \
    \   rank++;\n            }\n            ret[i].swap(ret[ti]), tmp[i].swap(tmp[ti]);\n\
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
    \    for (int j = 0; j < x.W; j++) {\n            T s = 0;\n            for (int\
    \ i = 0; i < x.H; i++) s += x.get(i, j);\n            os << s << \",\";\n    \
    \    }\n        os << \"]\";\n        for (int i = 0; i < x.H; i++) {\n      \
    \      os << \"\\n[\";\n            for (int j = 0; j < x.W; j++) os << x.get(i,\
    \ j) << \",\";\n            os << \"]\";\n        }\n        os << \"]\\n\";\n\
    \        return os;\n    }\n    template <class IStream> friend IStream &operator>>(IStream\
    \ &is, matrix &x) {\n        for (auto &v : x.elem) is >> v;\n        return is;\n\
    \    }\n};\n#line 6 \"linear_algebra_matrix/test/linalg_modint_determinant.test.cpp\"\
    \n\nint main() {\n    constexpr int mod = 998244353;\n    ModIntRuntime::set_mod(mod);\n\
    \n    int N;\n    std::cin >> N;\n\n    matrix<ModInt<mod>> Mfixed(N, N);\n  \
    \  std::cin >> Mfixed;\n\n    matrix<ModIntRuntime> Mruntime(N, N);\n    for (int\
    \ i = 0; i < N; i++) {\n        for (int j = 0; j < N; j++) { Mruntime[i][j] =\
    \ Mfixed[i][j].val(); }\n    }\n    int ret_fixed = Mfixed.gauss_jordan().determinant_of_upper_triangle().val();\n\
    \    int ret_runtime = Mruntime.gauss_jordan().determinant_of_upper_triangle().val();\n\
    \n    assert(ret_fixed == ret_runtime);\n    std::cout << ret_fixed << std::endl;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_det\"\n#include\
    \ \"../../modint.hpp\"\n#include \"../../number/modint_runtime.hpp\"\n#include\
    \ \"../matrix.hpp\"\n#include <iostream>\n\nint main() {\n    constexpr int mod\
    \ = 998244353;\n    ModIntRuntime::set_mod(mod);\n\n    int N;\n    std::cin >>\
    \ N;\n\n    matrix<ModInt<mod>> Mfixed(N, N);\n    std::cin >> Mfixed;\n\n   \
    \ matrix<ModIntRuntime> Mruntime(N, N);\n    for (int i = 0; i < N; i++) {\n \
    \       for (int j = 0; j < N; j++) { Mruntime[i][j] = Mfixed[i][j].val(); }\n\
    \    }\n    int ret_fixed = Mfixed.gauss_jordan().determinant_of_upper_triangle().val();\n\
    \    int ret_runtime = Mruntime.gauss_jordan().determinant_of_upper_triangle().val();\n\
    \n    assert(ret_fixed == ret_runtime);\n    std::cout << ret_fixed << std::endl;\n\
    }\n"
  dependsOn:
  - modint.hpp
  - number/modint_runtime.hpp
  - linear_algebra_matrix/matrix.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/linalg_modint_determinant.test.cpp
  requiredBy: []
  timestamp: '2022-05-01 16:11:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/linalg_modint_determinant.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/linalg_modint_determinant.test.cpp
- /verify/linear_algebra_matrix/test/linalg_modint_determinant.test.cpp.html
title: linear_algebra_matrix/test/linalg_modint_determinant.test.cpp
---
