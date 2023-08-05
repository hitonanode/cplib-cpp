---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/matrix.hpp
    title: linear_algebra_matrix/matrix.hpp
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: number/dual_number.hpp
    title: "Dual number \uFF08\u4E8C\u91CD\u6570\uFF09"
  - icon: ':heavy_check_mark:'
    path: unionfind/unionfind.hpp
    title: unionfind/unionfind.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1303
    links:
    - https://yukicoder.me/problems/no/1303
  bundledCode: "#line 1 \"linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1303\"\n#line 2 \"modint.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <set>\n#include <vector>\n\
    \ntemplate <int md> struct ModInt {\n    using lint = long long;\n    constexpr\
    \ static int mod() { return md; }\n    static int get_primitive_root() {\n   \
    \     static int primitive_root = 0;\n        if (!primitive_root) {\n       \
    \     primitive_root = [&]() {\n                std::set<int> fac;\n         \
    \       int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n \
    \                   while (v % i == 0) fac.insert(i), v /= i;\n              \
    \  if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((md - 1) / i) == 1) {\n           \
    \                 ok = false;\n                            break;\n          \
    \              }\n                    if (ok) return g;\n                }\n \
    \               return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    constexpr\
    \ ModInt() : val_(0) {}\n    constexpr ModInt &_setval(lint v) { return val_ =\
    \ (v >= md ? v - md : v), *this; }\n    constexpr ModInt(lint v) { _setval(v %\
    \ md + md); }\n    constexpr explicit operator bool() const { return val_ != 0;\
    \ }\n    constexpr ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    constexpr ModInt operator-(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    constexpr\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    constexpr ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    constexpr ModInt operator-() const { return ModInt()._setval(md - val_);\
    \ }\n    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this\
    \ + x; }\n    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this\
    \ - x; }\n    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this\
    \ * x; }\n    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this\
    \ / x; }\n    friend constexpr ModInt operator+(lint a, const ModInt &x) {\n \
    \       return ModInt()._setval(a % md + x.val_);\n    }\n    friend constexpr\
    \ ModInt operator-(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md - x.val_ + md);\n    }\n    friend constexpr ModInt operator*(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.val_ % md);\n    }\n\
    \    friend constexpr ModInt operator/(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md * x.inv().val() % md);\n    }\n    constexpr bool operator==(const\
    \ ModInt &x) const { return val_ == x.val_; }\n    constexpr bool operator!=(const\
    \ ModInt &x) const { return val_ != x.val_; }\n    constexpr bool operator<(const\
    \ ModInt &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    constexpr\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n\n    constexpr ModInt pow(lint n) const {\n\
    \        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n\
    \ & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static constexpr int cache_limit = std::min(md, 1 << 21);\n\
    \    static std::vector<ModInt> facs, facinvs, invs;\n\n    constexpr static void\
    \ _precalculation(int N) {\n        const int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n\n    constexpr\
    \ ModInt inv() const {\n        if (this->val_ < cache_limit) {\n            if\
    \ (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n            while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val_];\n\
    \        } else {\n            return this->pow(md - 2);\n        }\n    }\n \
    \   constexpr ModInt fac() const {\n        while (this->val_ >= int(facs.size()))\
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
    // using mint = ModInt<1000000007>;\n#line 1 \"number/dual_number.hpp\"\n#include\
    \ <type_traits>\n\nnamespace dual_number_ {\nstruct has_id_method_impl {\n   \
    \ template <class T_> static auto check(T_ *) -> decltype(T_::id(), std::true_type());\n\
    \    template <class T_> static auto check(...) -> std::false_type;\n};\ntemplate\
    \ <class T_> struct has_id : decltype(has_id_method_impl::check<T_>(nullptr))\
    \ {};\n} // namespace dual_number_\n\n// Dual number \uFF08\u4E8C\u91CD\u6570\uFF09\
    \n// Verified: https://atcoder.jp/contests/abc235/tasks/abc235_f\ntemplate <class\
    \ T> struct DualNumber {\n    T a, b; // a + bx\n\n    template <typename T2,\
    \ typename std::enable_if<dual_number_::has_id<T2>::value>::type * = nullptr>\n\
    \    static T2 _T_id() {\n        return T2::id();\n    }\n    template <typename\
    \ T2, typename std::enable_if<!dual_number_::has_id<T2>::value>::type * = nullptr>\n\
    \    static T2 _T_id() {\n        return T2(1);\n    }\n\n    DualNumber(T x =\
    \ T(), T y = T()) : a(x), b(y) {}\n    static DualNumber id() { return DualNumber(_T_id<T>(),\
    \ T()); }\n    explicit operator bool() const { return a != T() or b != T(); }\n\
    \    DualNumber operator+(const DualNumber &x) const { return DualNumber(a + x.a,\
    \ b + x.b); }\n    DualNumber operator-(const DualNumber &x) const { return DualNumber(a\
    \ - x.a, b - x.b); }\n    DualNumber operator*(const DualNumber &x) const {\n\
    \        return DualNumber(a * x.a, b * x.a + a * x.b);\n    }\n    DualNumber\
    \ operator/(const DualNumber &x) const {\n        T cinv = _T_id<T>() / x.a;\n\
    \        return DualNumber(a * cinv, (b * x.a - a * x.b) * cinv * cinv);\n   \
    \ }\n    DualNumber operator-() const { return DualNumber(-a, -b); }\n    DualNumber\
    \ &operator+=(const DualNumber &x) { return *this = *this + x; }\n    DualNumber\
    \ &operator-=(const DualNumber &x) { return *this = *this - x; }\n    DualNumber\
    \ &operator*=(const DualNumber &x) { return *this = *this * x; }\n    DualNumber\
    \ &operator/=(const DualNumber &x) { return *this = *this / x; }\n    bool operator==(const\
    \ DualNumber &x) const { return a == x.a and b == x.b; }\n    bool operator!=(const\
    \ DualNumber &x) const { return !(*this == x); }\n    bool operator<(const DualNumber\
    \ &x) const { return (a != x.a ? a < x.a : b < x.b); }\n    template <class OStream>\
    \ friend OStream &operator<<(OStream &os, const DualNumber &x) {\n        return\
    \ os << '{' << x.a << ',' << x.b << '}';\n    }\n\n    T eval(const T &x) const\
    \ { return a + b * x; }\n    T root() const { return (-a) / b; } // Solve a +\
    \ bx = 0 (b \\neq 0 is assumed)\n};\n#line 2 \"unionfind/unionfind.hpp\"\n#include\
    \ <algorithm>\n#include <numeric>\n#include <utility>\n#line 6 \"unionfind/unionfind.hpp\"\
    \n\n// CUT begin\n// UnionFind Tree (0-indexed), based on size of each disjoint\
    \ set\nstruct UnionFind {\n    std::vector<int> par, cou;\n    UnionFind(int N\
    \ = 0) : par(N), cou(N, 1) { iota(par.begin(), par.end(), 0); }\n    int find(int\
    \ x) { return (par[x] == x) ? x : (par[x] = find(par[x])); }\n    bool unite(int\
    \ x, int y) {\n        x = find(x), y = find(y);\n        if (x == y) return false;\n\
    \        if (cou[x] < cou[y]) std::swap(x, y);\n        par[y] = x, cou[x] +=\
    \ cou[y];\n        return true;\n    }\n    int count(int x) { return cou[find(x)];\
    \ }\n    bool same(int x, int y) { return find(x) == find(y); }\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<std::vector<int>> ret(par.size());\n       \
    \ for (int i = 0; i < int(par.size()); ++i) ret[find(i)].push_back(i);\n     \
    \   ret.erase(std::remove_if(ret.begin(), ret.end(),\n                       \
    \          [&](const std::vector<int> &v) { return v.empty(); }),\n          \
    \        ret.end());\n        return ret;\n    }\n};\n#line 4 \"linear_algebra_matrix/matrix.hpp\"\
    \n#include <cmath>\n#include <iterator>\n#line 9 \"linear_algebra_matrix/matrix.hpp\"\
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
    \    }\n};\n#line 6 \"linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp\"\
    \n\n#line 10 \"linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp\"\
    \nusing namespace std;\n\nusing mint = ModInt<998244353>;\nusing dual = DualNumber<mint>;\n\
    \nmint solve1(int N, const vector<pair<int, int>> &edges) {\n    vector<vector<dual>>\
    \ d(N, vector<dual>(N));\n    for (auto p : edges) {\n        int u = p.first,\
    \ v = p.second;\n        d[u][u] += dual::id();\n        d[v][v] += dual::id();\n\
    \        d[u][v] -= dual::id();\n        d[v][u] -= dual::id();\n    }\n    const\
    \ dual x = dual(0, 1);\n    for (int i = 0; i < N; ++i) {\n        for (int j\
    \ = 0; j < i; ++j) {\n            if (d[i][j] == dual()) {\n                d[i][i]\
    \ += x;\n                d[j][j] += x;\n                d[i][j] -= x;\n      \
    \          d[j][i] -= x;\n            }\n        }\n    }\n    d.resize(N - 1);\n\
    \    for (auto &v : d) v.resize(N - 1);\n    auto ret = matrix<dual>(d).gauss_jordan().determinant_of_upper_triangle();\n\
    \    return ret.a + ret.b;\n}\n\nmint solve2(const vector<int> &vs, const vector<pair<int,\
    \ int>> &edges) {\n    int D = vs.size();\n    matrix<mint> mat(D - 1, D - 1);\n\
    \    for (auto p : edges) {\n        int i = lower_bound(vs.begin(), vs.end(),\
    \ p.first) - vs.begin();\n        int j = lower_bound(vs.begin(), vs.end(), p.second)\
    \ - vs.begin();\n        if (i < D - 1) mat[i][i] += 1;\n        if (j < D - 1)\
    \ mat[j][j] += 1;\n        if (i + 1 < D and j + 1 < D) mat[i][j] -= 1, mat[j][i]\
    \ -= 1;\n    }\n    return mat.gauss_jordan().determinant_of_upper_triangle();\n\
    }\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int\
    \ N, M;\n    cin >> N >> M;\n    vector<pair<int, int>> edges;\n    UnionFind\
    \ uf1(N);\n    while (M--) {\n        int u, v;\n        cin >> u >> v;\n    \
    \    --u, --v;\n        edges.emplace_back(u, v);\n        uf1.unite(u, v);\n\
    \    }\n\n    if (uf1.count(0) == N) {\n        cout << \"0\\n\" << solve1(N,\
    \ edges) << '\\n';\n        return 0;\n    }\n\n    int max_red = 0, cntmaxi =\
    \ 0, fuben = 0;\n    for (int i = 0; i < N; ++i) {\n        for (int j = 0; j\
    \ < N; ++j) fuben += !uf1.same(i, j);\n    }\n    for (int i = 0; i < N; ++i)\
    \ {\n        for (int j = 0; j < i; ++j) {\n            if (!uf1.same(i, j)) {\n\
    \                int s = uf1.count(i) * uf1.count(j);\n                if (s >\
    \ max_red) {\n                    max_red = s, cntmaxi = 1;\n                }\
    \ else {\n                    if (max_red == s) cntmaxi++;\n                }\n\
    \            }\n        }\n    }\n    mint ret = cntmaxi;\n    vector<vector<int>>\
    \ r2is(N);\n    vector<vector<pair<int, int>>> r2edges(N);\n    for (int i = 0;\
    \ i < N; ++i) r2is[uf1.find(i)].push_back(i);\n    for (auto p : edges) r2edges[uf1.find(p.first)].push_back(p);\n\
    \n    for (int r = 0; r < N; ++r) {\n        if (r2is[r].size()) ret *= solve2(r2is[r],\
    \ r2edges[r]);\n    }\n    cout << fuben - max_red * 2 << '\\n' << ret << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1303\"\n#include \"../../modint.hpp\"\
    \n#include \"../../number/dual_number.hpp\"\n#include \"../../unionfind/unionfind.hpp\"\
    \n#include \"../matrix.hpp\"\n\n#include <iostream>\n#include <utility>\n#include\
    \ <vector>\nusing namespace std;\n\nusing mint = ModInt<998244353>;\nusing dual\
    \ = DualNumber<mint>;\n\nmint solve1(int N, const vector<pair<int, int>> &edges)\
    \ {\n    vector<vector<dual>> d(N, vector<dual>(N));\n    for (auto p : edges)\
    \ {\n        int u = p.first, v = p.second;\n        d[u][u] += dual::id();\n\
    \        d[v][v] += dual::id();\n        d[u][v] -= dual::id();\n        d[v][u]\
    \ -= dual::id();\n    }\n    const dual x = dual(0, 1);\n    for (int i = 0; i\
    \ < N; ++i) {\n        for (int j = 0; j < i; ++j) {\n            if (d[i][j]\
    \ == dual()) {\n                d[i][i] += x;\n                d[j][j] += x;\n\
    \                d[i][j] -= x;\n                d[j][i] -= x;\n            }\n\
    \        }\n    }\n    d.resize(N - 1);\n    for (auto &v : d) v.resize(N - 1);\n\
    \    auto ret = matrix<dual>(d).gauss_jordan().determinant_of_upper_triangle();\n\
    \    return ret.a + ret.b;\n}\n\nmint solve2(const vector<int> &vs, const vector<pair<int,\
    \ int>> &edges) {\n    int D = vs.size();\n    matrix<mint> mat(D - 1, D - 1);\n\
    \    for (auto p : edges) {\n        int i = lower_bound(vs.begin(), vs.end(),\
    \ p.first) - vs.begin();\n        int j = lower_bound(vs.begin(), vs.end(), p.second)\
    \ - vs.begin();\n        if (i < D - 1) mat[i][i] += 1;\n        if (j < D - 1)\
    \ mat[j][j] += 1;\n        if (i + 1 < D and j + 1 < D) mat[i][j] -= 1, mat[j][i]\
    \ -= 1;\n    }\n    return mat.gauss_jordan().determinant_of_upper_triangle();\n\
    }\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int\
    \ N, M;\n    cin >> N >> M;\n    vector<pair<int, int>> edges;\n    UnionFind\
    \ uf1(N);\n    while (M--) {\n        int u, v;\n        cin >> u >> v;\n    \
    \    --u, --v;\n        edges.emplace_back(u, v);\n        uf1.unite(u, v);\n\
    \    }\n\n    if (uf1.count(0) == N) {\n        cout << \"0\\n\" << solve1(N,\
    \ edges) << '\\n';\n        return 0;\n    }\n\n    int max_red = 0, cntmaxi =\
    \ 0, fuben = 0;\n    for (int i = 0; i < N; ++i) {\n        for (int j = 0; j\
    \ < N; ++j) fuben += !uf1.same(i, j);\n    }\n    for (int i = 0; i < N; ++i)\
    \ {\n        for (int j = 0; j < i; ++j) {\n            if (!uf1.same(i, j)) {\n\
    \                int s = uf1.count(i) * uf1.count(j);\n                if (s >\
    \ max_red) {\n                    max_red = s, cntmaxi = 1;\n                }\
    \ else {\n                    if (max_red == s) cntmaxi++;\n                }\n\
    \            }\n        }\n    }\n    mint ret = cntmaxi;\n    vector<vector<int>>\
    \ r2is(N);\n    vector<vector<pair<int, int>>> r2edges(N);\n    for (int i = 0;\
    \ i < N; ++i) r2is[uf1.find(i)].push_back(i);\n    for (auto p : edges) r2edges[uf1.find(p.first)].push_back(p);\n\
    \n    for (int r = 0; r < N; ++r) {\n        if (r2is[r].size()) ret *= solve2(r2is[r],\
    \ r2edges[r]);\n    }\n    cout << fuben - max_red * 2 << '\\n' << ret << '\\\
    n';\n}\n"
  dependsOn:
  - modint.hpp
  - number/dual_number.hpp
  - unionfind/unionfind.hpp
  - linear_algebra_matrix/matrix.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp
  requiredBy: []
  timestamp: '2023-08-05 18:05:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp
- /verify/linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp.html
title: linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp
---
