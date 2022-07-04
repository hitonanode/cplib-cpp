---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/linear_recurrence.hpp
    title: "\u7DDA\u5F62\u6F38\u5316\u5F0F\u306E\u767A\u898B\u30FB\u7B2C $N$ \u9805\
      \u63A8\u5B9A"
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/blackbox_algorithm.hpp
    title: "Black box linear algebra \u3092\u5229\u7528\u3057\u305F\u5404\u7A2E\u9AD8\
      \u901F\u8A08\u7B97"
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/blackbox_matrices.hpp
    title: "Black box linear algebra \u306E\u305F\u3081\u306E\u884C\u5217"
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\ntemplate <int md> struct ModInt {\n#if __cplusplus >= 201402L\n\
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
    \            while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
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
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"formal_power_series/linear_recurrence.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <utility>\n#line 6 \"formal_power_series/linear_recurrence.hpp\"\
    \n\n// CUT begin\n// Berlekamp\u2013Massey algorithm\n// https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm\n\
    // Complexity: O(N^2)\n// input: S = sequence from field K\n// return: L     \
    \     = degree of minimal polynomial,\n//         C_reversed = monic min. polynomial\
    \ (size = L + 1, reversed order, C_reversed[0] = 1))\n// Formula: convolve(S,\
    \ C_reversed)[i] = 0 for i >= L\n// Example:\n// - [1, 2, 4, 8, 16]   -> (1, [1,\
    \ -2])\n// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])\n// - [0, 0, 0, 0, 1]    ->\
    \ (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)\n// - []                 ->\
    \ (0, [1])\n// - [0, 0, 0]          -> (0, [1])\n// - [-2]               -> (1,\
    \ [1, 2])\ntemplate <typename Tfield>\nstd::pair<int, std::vector<Tfield>> find_linear_recurrence(const\
    \ std::vector<Tfield> &S) {\n    int N = S.size();\n    using poly = std::vector<Tfield>;\n\
    \    poly C_reversed{1}, B{1};\n    int L = 0, m = 1;\n    Tfield b = 1;\n\n \
    \   // adjust: C(x) <- C(x) - (d / b) x^m B(x)\n    auto adjust = [](poly C, const\
    \ poly &B, Tfield d, Tfield b, int m) -> poly {\n        C.resize(std::max(C.size(),\
    \ B.size() + m));\n        Tfield a = d / b;\n        for (unsigned i = 0; i <\
    \ B.size(); i++) C[i + m] -= a * B[i];\n        return C;\n    };\n\n    for (int\
    \ n = 0; n < N; n++) {\n        Tfield d = S[n];\n        for (int i = 1; i <=\
    \ L; i++) d += C_reversed[i] * S[n - i];\n\n        if (d == 0)\n            m++;\n\
    \        else if (2 * L <= n) {\n            poly T = C_reversed;\n          \
    \  C_reversed = adjust(C_reversed, B, d, b, m);\n            L = n + 1 - L;\n\
    \            B = T;\n            b = d;\n            m = 1;\n        } else\n\
    \            C_reversed = adjust(C_reversed, B, d, b, m++);\n    }\n    return\
    \ std::make_pair(L, C_reversed);\n}\n\n// Calculate $x^N \\bmod f(x)$\n// Known\
    \ as `Kitamasa method`\n// Input: f_reversed: monic, reversed (f_reversed[0] =\
    \ 1)\n// Complexity: $O(K^2 \\log N)$ ($K$: deg. of $f$)\n// Example: (4, [1,\
    \ -1, -1]) -> [2, 3]\n//          ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2\
    \ )\n// Reference: http://misawa.github.io/others/fast_kitamasa_method.html\n\
    //            http://sugarknri.hatenablog.com/entry/2017/11/18/233936\ntemplate\
    \ <typename Tfield>\nstd::vector<Tfield> monomial_mod_polynomial(long long N,\
    \ const std::vector<Tfield> &f_reversed) {\n    assert(!f_reversed.empty() and\
    \ f_reversed[0] == 1);\n    int K = f_reversed.size() - 1;\n    if (!K) return\
    \ {};\n    int D = 64 - __builtin_clzll(N);\n    std::vector<Tfield> ret(K, 0);\n\
    \    ret[0] = 1;\n    auto self_conv = [](std::vector<Tfield> x) -> std::vector<Tfield>\
    \ {\n        int d = x.size();\n        std::vector<Tfield> ret(d * 2 - 1);\n\
    \        for (int i = 0; i < d; i++) {\n            ret[i * 2] += x[i] * x[i];\n\
    \            for (int j = 0; j < i; j++) ret[i + j] += x[i] * x[j] * 2;\n    \
    \    }\n        return ret;\n    };\n    for (int d = D; d--;) {\n        ret\
    \ = self_conv(ret);\n        for (int i = 2 * K - 2; i >= K; i--) {\n        \
    \    for (int j = 1; j <= K; j++) ret[i - j] -= ret[i] * f_reversed[j];\n    \
    \    }\n        ret.resize(K);\n        if ((N >> d) & 1) {\n            std::vector<Tfield>\
    \ c(K);\n            c[0] = -ret[K - 1] * f_reversed[K];\n            for (int\
    \ i = 1; i < K; i++) { c[i] = ret[i - 1] - ret[K - 1] * f_reversed[K - i]; }\n\
    \            ret = c;\n        }\n    }\n    return ret;\n}\n\n// Guess k-th element\
    \ of the sequence, assuming linear recurrence\n// initial_elements: 0-ORIGIN\n\
    // Verify: abc198f https://atcoder.jp/contests/abc198/submissions/21837815\ntemplate\
    \ <typename Tfield>\nTfield guess_kth_term(const std::vector<Tfield> &initial_elements,\
    \ long long k) {\n    assert(k >= 0);\n    if (k < static_cast<long long>(initial_elements.size()))\
    \ return initial_elements[k];\n    const auto f = find_linear_recurrence<Tfield>(initial_elements).second;\n\
    \    const auto g = monomial_mod_polynomial<Tfield>(k, f);\n    Tfield ret = 0;\n\
    \    for (unsigned i = 0; i < g.size(); i++) ret += g[i] * initial_elements[i];\n\
    \    return ret;\n}\n#line 3 \"linear_algebra_matrix/blackbox_algorithm.hpp\"\n\
    #include <chrono>\n#include <random>\n#line 6 \"linear_algebra_matrix/blackbox_algorithm.hpp\"\
    \n\ntemplate <typename ModInt> std::vector<ModInt> gen_random_vector(int len)\
    \ {\n    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    static std::uniform_int_distribution<int> rnd(1, ModInt::mod() - 1);\n  \
    \  std::vector<ModInt> ret(len);\n    for (auto &x : ret) x = rnd(mt);\n    return\
    \ ret;\n};\n\n// Probabilistic algorithm to find a solution of linear equation\
    \ Ax = b if exists.\n// Complexity: O(n T(n) + n^2)\n// Reference:\n// [1] W.\
    \ Eberly, E. Kaltofen, \"On randomized Lanczos algorithms,\" Proc. of international\
    \ symposium on\n//     Symbolic and algebraic computation, 176-183, 1997.\ntemplate\
    \ <typename Matrix, typename T>\nstd::vector<T> linear_system_solver_lanczos(const\
    \ Matrix &A, const std::vector<T> &b) {\n    assert(A.height() == int(b.size()));\n\
    \    const int M = A.height(), N = A.width();\n\n    const std::vector<T> D1 =\
    \ gen_random_vector<T>(N), D2 = gen_random_vector<T>(M),\n                   \
    \      v = gen_random_vector<T>(N);\n    auto applyD1 = [&D1](std::vector<T> v)\
    \ {\n        for (int i = 0; i < int(v.size()); i++) v[i] *= D1[i];\n        return\
    \ v;\n    };\n    auto applyD2 = [&D2](std::vector<T> v) {\n        for (int i\
    \ = 0; i < int(v.size()); i++) v[i] *= D2[i];\n        return v;\n    };\n   \
    \ auto applyAtilde = [&](std::vector<T> v) -> std::vector<T> {\n        v = applyD1(v);\n\
    \        v = A.prod(v);\n        v = applyD2(v);\n        v = A.prod_left(v);\n\
    \        v = applyD1(v);\n        return v;\n    };\n    auto dot = [&](const\
    \ std::vector<T> &vl, const std::vector<T> &vr) -> T {\n        return std::inner_product(vl.begin(),\
    \ vl.end(), vr.begin(), T(0));\n    };\n    auto scalar_vec = [&](const T &x,\
    \ std::vector<T> vec) -> std::vector<T> {\n        for (auto &v : vec) v *= x;\n\
    \        return vec;\n    };\n\n    auto btilde1 = applyD1(A.prod_left(applyD2(b))),\
    \ btilde2 = applyAtilde(v);\n    std::vector<T> btilde(N);\n    for (int i = 0;\
    \ i < N; i++) btilde[i] = btilde1[i] + btilde2[i];\n\n    std::vector<T> w0 =\
    \ btilde, v1 = applyAtilde(w0);\n    std::vector<T> wm1(w0.size()), v0(v1.size());\n\
    \    T t0 = dot(v1, w0), gamma = dot(btilde, w0) / t0, tm1 = 1;\n    std::vector<T>\
    \ x = scalar_vec(gamma, w0);\n    while (true) {\n        if (!t0 or !std::count_if(w0.begin(),\
    \ w0.end(), [](T x) { return x != T(0); })) break;\n        T alpha = dot(v1,\
    \ v1) / t0, beta = dot(v1, v0) / tm1;\n        std::vector<T> w1(N);\n       \
    \ for (int i = 0; i < N; i++) w1[i] = v1[i] - alpha * w0[i] - beta * wm1[i];\n\
    \        std::vector<T> v2 = applyAtilde(w1);\n        T t1 = dot(w1, v2);\n \
    \       gamma = dot(btilde, w1) / t1;\n        for (int i = 0; i < N; i++) x[i]\
    \ += gamma * w1[i];\n\n        wm1 = w0, w0 = w1;\n        v0 = v1, v1 = v2;\n\
    \        tm1 = t0, t0 = t1;\n    }\n    for (int i = 0; i < N; i++) x[i] -= v[i];\n\
    \    return applyD1(x);\n}\n\n// Probabilistic algorithm to calculate determinant\
    \ of matrices\n// Complexity: O(n T(n) + n^2)\n// Reference:\n// [1] D. H. Wiedmann,\
    \ \"Solving sparse linear equations over finite fields,\"\n//     IEEE Trans.\
    \ on Information Theory, 32(1), 54-62, 1986.\ntemplate <class Matrix, class Tp>\
    \ Tp blackbox_determinant(const Matrix &M) {\n    assert(M.height() == M.width());\n\
    \    const int N = M.height();\n    std::vector<Tp> b = gen_random_vector<Tp>(N),\
    \ u = gen_random_vector<Tp>(N),\n                    D = gen_random_vector<Tp>(N);\n\
    \    std::vector<Tp> uMDib(2 * N);\n    for (int i = 0; i < 2 * N; i++) {\n  \
    \      uMDib[i] = std::inner_product(u.begin(), u.end(), b.begin(), Tp(0));\n\
    \        for (int j = 0; j < N; j++) b[j] *= D[j];\n        b = M.prod(b);\n \
    \   }\n    auto ret = find_linear_recurrence<Tp>(uMDib);\n    Tp det = ret.second.back()\
    \ * (N % 2 ? -1 : 1);\n    Tp ddet = 1;\n    for (auto d : D) ddet *= d;\n   \
    \ return det / ddet;\n}\n\n// Complexity: O(n T(n) + n^2)\ntemplate <class Matrix,\
    \ class Tp>\nstd::vector<Tp> reversed_minimal_polynomial_of_matrix(const Matrix\
    \ &M) {\n    assert(M.height() == M.width());\n    const int N = M.height();\n\
    \    std::vector<Tp> b = gen_random_vector<Tp>(N), u = gen_random_vector<Tp>(N);\n\
    \    std::vector<Tp> uMb(2 * N);\n    for (int i = 0; i < 2 * N; i++) {\n    \
    \    uMb[i] = std::inner_product(u.begin(), u.end(), b.begin(), Tp());\n     \
    \   b = M.prod(b);\n    }\n    auto ret = find_linear_recurrence<Tp>(uMb);\n \
    \   return ret.second;\n}\n\n// Calculate A^k b\n// Complexity: O(n^2 log k +\
    \ n T(n))\n// Verified: https://www.codechef.com/submit/COUNTSEQ2\ntemplate <class\
    \ Matrix, class Tp>\nstd::vector<Tp> blackbox_matrix_pow_vec(const Matrix &A,\
    \ long long k, std::vector<Tp> b) {\n    assert(A.width() == int(b.size()));\n\
    \    assert(k >= 0);\n\n    std::vector<Tp> rev_min_poly = reversed_minimal_polynomial_of_matrix<Matrix,\
    \ Tp>(A);\n    std::vector<Tp> remainder = monomial_mod_polynomial<Tp>(k, rev_min_poly);\n\
    \n    std::vector<Tp> ret(b.size());\n    for (Tp c : remainder) {\n        for\
    \ (int d = 0; d < int(b.size()); ++d) ret[d] += b[d] * c;\n        b = A.prod(b);\n\
    \    }\n    return ret;\n}\n#line 3 \"convolution/ntt.hpp\"\n\n#line 5 \"convolution/ntt.hpp\"\
    \n#include <array>\n#line 7 \"convolution/ntt.hpp\"\n#include <tuple>\n#line 9\
    \ \"convolution/ntt.hpp\"\n\n// CUT begin\n// Integer convolution for arbitrary\
    \ mod\n// with NTT (and Garner's algorithm) for ModInt / ModIntRuntime class.\n\
    // We skip Garner's algorithm if `skip_garner` is true or mod is in `nttprimes`.\n\
    // input: a (size: n), b (size: m)\n// return: vector (size: n + m - 1)\ntemplate\
    \ <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT>\
    \ b, bool skip_garner);\n\nconstexpr int nttprimes[3] = {998244353, 167772161,\
    \ 469762049};\n\n// Integer FFT (Fast Fourier Transform) for ModInt class\n//\
    \ (Also known as Number Theoretic Transform, NTT)\n// is_inverse: inverse transform\n\
    // ** Input size must be 2^n **\ntemplate <typename MODINT> void ntt(std::vector<MODINT>\
    \ &a, bool is_inverse = false) {\n    int n = a.size();\n    if (n == 1) return;\n\
    \    static const int mod = MODINT::mod();\n    static const MODINT root = MODINT::get_primitive_root();\n\
    \    assert(__builtin_popcount(n) == 1 and (mod - 1) % n == 0);\n\n    static\
    \ std::vector<MODINT> w{1}, iw{1};\n    for (int m = w.size(); m < n / 2; m *=\
    \ 2) {\n        MODINT dw = root.pow((mod - 1) / (4 * m)), dwinv = 1 / dw;\n \
    \       w.resize(m * 2), iw.resize(m * 2);\n        for (int i = 0; i < m; i++)\
    \ w[m + i] = w[i] * dw, iw[m + i] = iw[i] * dwinv;\n    }\n\n    if (!is_inverse)\
    \ {\n        for (int m = n; m >>= 1;) {\n            for (int s = 0, k = 0; s\
    \ < n; s += 2 * m, k++) {\n                for (int i = s; i < s + m; i++) {\n\
    \                    MODINT x = a[i], y = a[i + m] * w[k];\n                 \
    \   a[i] = x + y, a[i + m] = x - y;\n                }\n            }\n      \
    \  }\n    } else {\n        for (int m = 1; m < n; m *= 2) {\n            for\
    \ (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n                for (int i = s;\
    \ i < s + m; i++) {\n                    MODINT x = a[i], y = a[i + m];\n    \
    \                a[i] = x + y, a[i + m] = (x - y) * iw[k];\n                }\n\
    \            }\n        }\n        int n_inv = MODINT(n).inv().val();\n      \
    \  for (auto &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
    \ nttconv_(const std::vector<int> &a, const std::vector<int> &b) {\n    int sz\
    \ = a.size();\n    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n\
    \    std::vector<ModInt<MOD>> ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++)\
    \ ap[i] = a[i], bp[i] = b[i];\n    ntt(ap, false);\n    if (a == b)\n        bp\
    \ = ap;\n    else\n        ntt(bp, false);\n    for (int i = 0; i < sz; i++) ap[i]\
    \ *= bp[i];\n    ntt(ap, true);\n    return ap;\n}\nlong long garner_ntt_(int\
    \ r0, int r1, int r2, int mod) {\n    using mint2 = ModInt<nttprimes[2]>;\n  \
    \  static const long long m01 = 1LL * nttprimes[0] * nttprimes[1];\n    static\
    \ const long long m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv().val();\n\
    \    static const long long m01_inv_m2 = mint2(m01).inv().val();\n\n    int v1\
    \ = (m0_inv_m1 * (r1 + nttprimes[1] - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2)\
    \ - r0 - mint2(nttprimes[0]) * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0]\
    \ * v1 + m01 % mod * v2.val()) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT>\
    \ nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool skip_garner) {\n\
    \    if (a.empty() or b.empty()) return {};\n    int sz = 1, n = a.size(), m =\
    \ b.size();\n    while (sz < n + m) sz <<= 1;\n    if (sz <= 16) {\n        std::vector<MODINT>\
    \ ret(n + m - 1);\n        for (int i = 0; i < n; i++) {\n            for (int\
    \ j = 0; j < m; j++) ret[i + j] += a[i] * b[j];\n        }\n        return ret;\n\
    \    }\n    int mod = MODINT::mod();\n    if (skip_garner or\n        std::find(std::begin(nttprimes),\
    \ std::end(nttprimes), mod) != std::end(nttprimes)) {\n        a.resize(sz), b.resize(sz);\n\
    \        if (a == b) {\n            ntt(a, false);\n            b = a;\n     \
    \   } else {\n            ntt(a, false), ntt(b, false);\n        }\n        for\
    \ (int i = 0; i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n\
    \ + m - 1);\n    } else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val();\n        for (int i = 0; i < m;\
    \ i++) bi[i] = b[i].val();\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n\
    \        auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\n\
    \            a[i] = garner_ntt_(ntt0[i].val(), ntt1[i].val(), ntt2[i].val(), mod);\n\
    \    }\n    return a;\n}\n\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(const\
    \ std::vector<MODINT> &a, const std::vector<MODINT> &b) {\n    return nttconv<MODINT>(a,\
    \ b, false);\n}\n#line 5 \"linear_algebra_matrix/blackbox_matrices.hpp\"\n#include\
    \ <numeric>\n#line 8 \"linear_algebra_matrix/blackbox_matrices.hpp\"\n\n// Sparse\
    \ matrix\ntemplate <typename Tp> struct sparse_matrix {\n    int H, W;\n    std::vector<std::vector<std::pair<int,\
    \ Tp>>> vals;\n    sparse_matrix(int H = 0, int W = 0) : H(H), W(W), vals(H) {}\n\
    \    int height() const { return H; }\n    int width() const { return W; }\n \
    \   void add_element(int i, int j, Tp val) {\n        assert(i >= 0 and i < H);\n\
    \        assert(j >= 0 and i < W);\n        vals[i].emplace_back(j, val);\n  \
    \  }\n    std::vector<Tp> prod(const std::vector<Tp> &vec) const {\n        assert(W\
    \ == int(vec.size()));\n        std::vector<Tp> ret(H);\n        for (int i =\
    \ 0; i < H; i++) {\n            for (const auto &p : vals[i]) ret[i] += p.second\
    \ * vec[p.first];\n        }\n        return ret;\n    }\n    std::vector<Tp>\
    \ prod_left(const std::vector<Tp> &vec) const {\n        assert(H == int(vec.size()));\n\
    \        std::vector<Tp> ret(W);\n        for (int i = 0; i < H; i++) {\n    \
    \        for (const auto &p : vals[i]) ret[p.first] += p.second * vec[i];\n  \
    \      }\n        return ret;\n    }\n    std::vector<std::vector<Tp>> vecvec()\
    \ const {\n        std::vector<std::vector<Tp>> ret(H, std::vector<Tp>(W));\n\
    \        for (int i = 0; i < H; i++) {\n            for (auto p : vals[i]) ret[i][p.first]\
    \ += p.second;\n        }\n        return ret;\n    }\n};\n\n// Toeplitz matrix\n\
    // M = [\n// [ vw_0 vw_1 vw_2 ... ]\n// [ vh_1 ...           ]\n// [ vh_2 ...\
    \           ]\n// [ ...                ] (vw_0 == vh_0)\n// prod() / prod_left()\
    \ : O((H + W) log (H + W))\ntemplate <typename NTTModInt> struct toeplitz_ntt\
    \ {\n    int _h, _w;\n    int _len_pow2;\n    std::vector<NTTModInt> ts, ntt_ts;\n\
    \    toeplitz_ntt(const std::vector<NTTModInt> &vh, const std::vector<NTTModInt>\
    \ &vw)\n        : _h(vh.size()), _w(vw.size()) {\n        assert(vh.size() and\
    \ vw.size() and vh[0] == vw[0]);\n        ts.resize(_h + _w - 1);\n        for\
    \ (int i = 0; i < _w; i++) ts[i] = vw[_w - 1 - i];\n        for (int j = 0; j\
    \ < _h; j++) ts[_w - 1 + j] = vh[j];\n        _len_pow2 = 1;\n        while (_len_pow2\
    \ < int(ts.size()) + std::max(_h, _w) - 1) _len_pow2 *= 2;\n        ntt_ts = ts;\n\
    \        ntt_ts.resize(_len_pow2);\n        ntt(ntt_ts, false);\n    }\n    int\
    \ height() const { return _h; }\n    int width() const { return _w; }\n    std::vector<NTTModInt>\
    \ prod(std::vector<NTTModInt> b) const {\n        assert(int(b.size()) == _w);\n\
    \        b.resize(_len_pow2);\n        ntt(b, false);\n        for (int i = 0;\
    \ i < _len_pow2; i++) b[i] *= ntt_ts[i];\n        ntt(b, true);\n        b.erase(b.begin(),\
    \ b.begin() + _w - 1);\n        b.resize(_h);\n        return b;\n    }\n    std::vector<NTTModInt>\
    \ prod_left(std::vector<NTTModInt> b) const {\n        assert(int(b.size()) ==\
    \ _h);\n        std::reverse(b.begin(), b.end());\n        b.resize(_len_pow2);\n\
    \        ntt(b, false);\n        for (int i = 0; i < _len_pow2; i++) b[i] *= ntt_ts[i];\n\
    \        ntt(b, true);\n        b.erase(b.begin(), b.begin() + _h - 1);\n    \
    \    b.resize(_w);\n        std::reverse(b.begin(), b.end());\n        return\
    \ b;\n    }\n    std::vector<std::vector<NTTModInt>> vecvec() const {\n      \
    \  std::vector<std::vector<NTTModInt>> ret(_h, std::vector<NTTModInt>(_w));\n\
    \        for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ ret[i][j] = ts[i - j + _w - 1];\n        }\n        return ret;\n    }\n};\n\
    \n// Square Toeplitz matrix\n// M = [\n// [ t_(N-1) t_(N-2) ... t_1 t_0     ]\n\
    // [ t_N     t_(N-1) ... t_2 t_1     ]\n// [ ...                             ]\n\
    // [ t_(N*2-2)       ...     t_(N-1) ]]\n// prod() / prod_left() : O(N log N)\n\
    template <typename NTTModInt> struct square_toeplitz_ntt {\n    int _dim;\n  \
    \  int _len_pow2;\n    std::vector<NTTModInt> ts;\n    std::vector<NTTModInt>\
    \ ntt_ts;\n    square_toeplitz_ntt(const std::vector<NTTModInt> &t) : _dim(t.size()\
    \ / 2 + 1), ts(t) {\n        assert(t.size() % 2);\n        _len_pow2 = 1;\n \
    \       while (_len_pow2 < int(ts.size()) + _dim - 1) _len_pow2 *= 2;\n      \
    \  ntt_ts = ts;\n        ntt_ts.resize(_len_pow2);\n        ntt(ntt_ts, false);\n\
    \    }\n    int height() const { return _dim; }\n    int width() const { return\
    \ _dim; }\n\n    // Calculate A * b\n    std::vector<NTTModInt> prod(std::vector<NTTModInt>\
    \ b) const {\n        assert(int(b.size()) == _dim);\n        b.resize(_len_pow2);\n\
    \        ntt(b, false);\n        for (int i = 0; i < _len_pow2; i++) b[i] *= ntt_ts[i];\n\
    \        ntt(b, true);\n        b.erase(b.begin(), b.begin() + _dim - 1);\n  \
    \      b.resize(_dim);\n        return b;\n    }\n    // Calculate bT * A\n  \
    \  std::vector<NTTModInt> prod_left(std::vector<NTTModInt> b) const {\n      \
    \  std::reverse(b.begin(), b.end());\n        b = prod(b);\n        std::reverse(b.begin(),\
    \ b.end());\n        return b;\n    }\n    std::vector<std::vector<NTTModInt>>\
    \ vecvec() const {\n        std::vector<std::vector<NTTModInt>> ret(_dim, std::vector<NTTModInt>(_dim));\n\
    \        for (int i = 0; i < _dim; i++) {\n            for (int j = 0; j < _dim;\
    \ j++) ret[i][j] = ts[i - j + _dim - 1];\n        }\n        return ret;\n   \
    \ }\n};\n#line 4 \"linear_algebra_matrix/matrix.hpp\"\n#include <cmath>\n#include\
    \ <iterator>\n#include <type_traits>\n#line 9 \"linear_algebra_matrix/matrix.hpp\"\
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
    \    }\n};\n#line 7 \"linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp\"\
    \n#include <cstdio>\n#line 11 \"linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp\"\
    \nusing namespace std;\n\nmt19937 mt(1010101);\n\ntemplate <class MODINT, class\
    \ MATRIX,\n          typename std::enable_if<std::is_same<MATRIX, toeplitz_ntt<MODINT>>::value>::type\
    \ * = nullptr>\ntoeplitz_ntt<MODINT> gen_random_matrix() {\n    auto rnd = uniform_int_distribution<int>(1,\
    \ 100);\n    int h = rnd(mt), w = max(h, rnd(mt));\n    auto vh = gen_random_vector<MODINT>(h),\
    \ vw = gen_random_vector<MODINT>(w);\n    vw[0] = vh[0];\n    return toeplitz_ntt<MODINT>(vh,\
    \ vw);\n}\n\ntemplate <class MODINT, class MATRIX,\n          typename std::enable_if<std::is_same<MATRIX,\
    \ square_toeplitz_ntt<MODINT>>::value>::type * = nullptr>\nsquare_toeplitz_ntt<MODINT>\
    \ gen_random_matrix() {\n    int N = uniform_int_distribution<int>(1, 100)(mt);\n\
    \    auto v = gen_random_vector<MODINT>(N * 2 - 1);\n    return square_toeplitz_ntt<MODINT>(v);\n\
    }\n\ntemplate <class MODINT, class MATRIX,\n          typename std::enable_if<std::is_same<MATRIX,\
    \ sparse_matrix<MODINT>>::value>::type * = nullptr>\nsparse_matrix<MODINT> gen_random_matrix()\
    \ {\n    int H = uniform_int_distribution<int>(1, 20)(mt),\n        W = max(H,\
    \ uniform_int_distribution<int>(1, 20)(mt));\n    sparse_matrix<MODINT> M(H, W);\n\
    \    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) {\n  \
    \          MODINT v = uniform_int_distribution<int>(0, MODINT::mod() - 1)(mt);\n\
    \            M.add_element(i, j, v);\n        }\n    }\n    return M;\n}\n\ntemplate\
    \ <class MODINT, class MATRIX,\n          typename std::enable_if<std::is_same<MATRIX,\
    \ matrix<MODINT>>::value>::type * = nullptr>\nmatrix<MODINT> gen_random_matrix()\
    \ {\n    int H = uniform_int_distribution<int>(1, 20)(mt),\n        W = max(H,\
    \ uniform_int_distribution<int>(1, 20)(mt));\n    matrix<MODINT> M(H, W);\n  \
    \  for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) {\n    \
    \        MODINT v = uniform_int_distribution<int>(0, MODINT::mod() - 1)(mt);\n\
    \            M[i][j] = v;\n        }\n    }\n    return M;\n}\n\ntemplate <typename\
    \ MATRIX, typename mint> void blackbox_mat_checker(int n_try) {\n    for (int\
    \ i = 0; i < n_try; i++) {\n        const MATRIX M = gen_random_matrix<mint, MATRIX>();\n\
    \        vector<vector<mint>> Mvv = M.vecvec();\n        const int H = M.height(),\
    \ W = M.width();\n        const auto b = gen_random_vector<mint>(H);\n       \
    \ // Check linear eq. solver\n        const auto x = linear_system_solver_lanczos(M,\
    \ b);\n        assert(M.prod(x) == b);\n\n        // Check prod()\n        const\
    \ auto c = gen_random_vector<mint>(W);\n        const auto Mc = M.prod(c);\n \
    \       vector<mint> Mc2(H);\n        for (int i = 0; i < H; i++) {\n        \
    \    for (int j = 0; j < W; j++) Mc2[i] += Mvv[i][j] * c[j];\n        }\n    \
    \    assert(Mc == Mc2);\n\n        // Check prod_left()\n        const auto a\
    \ = gen_random_vector<mint>(H);\n        const auto aM = M.prod_left(a);\n   \
    \     vector<mint> aM2(W);\n        for (int i = 0; i < H; i++) {\n          \
    \  for (int j = 0; j < W; j++) aM2[j] += Mvv[i][j] * a[i];\n        }\n      \
    \  assert(aM == aM2);\n\n        // Check black_box_determinant()\n        if\
    \ (H == W) {\n            mint det = blackbox_determinant<MATRIX, mint>(M);\n\
    \            mint det2 = matrix<mint>(Mvv).gauss_jordan().determinant_of_upper_triangle();\n\
    \            assert(det == det2);\n        }\n    }\n}\n\nint main() {\n    using\
    \ mint = ModInt<998244353>;\n    blackbox_mat_checker<toeplitz_ntt<mint>, mint>(1000);\n\
    \    blackbox_mat_checker<square_toeplitz_ntt<mint>, mint>(1000);\n    blackbox_mat_checker<sparse_matrix<mint>,\
    \ mint>(1000);\n    blackbox_mat_checker<matrix<mint>, mint>(1000);\n    puts(\"\
    Hello World\");\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../../modint.hpp\"\n#include \"../blackbox_algorithm.hpp\"\
    \n#include \"../blackbox_matrices.hpp\"\n#include \"../matrix.hpp\"\n#include\
    \ <chrono>\n#include <cstdio>\n#include <random>\n#include <type_traits>\n#include\
    \ <vector>\nusing namespace std;\n\nmt19937 mt(1010101);\n\ntemplate <class MODINT,\
    \ class MATRIX,\n          typename std::enable_if<std::is_same<MATRIX, toeplitz_ntt<MODINT>>::value>::type\
    \ * = nullptr>\ntoeplitz_ntt<MODINT> gen_random_matrix() {\n    auto rnd = uniform_int_distribution<int>(1,\
    \ 100);\n    int h = rnd(mt), w = max(h, rnd(mt));\n    auto vh = gen_random_vector<MODINT>(h),\
    \ vw = gen_random_vector<MODINT>(w);\n    vw[0] = vh[0];\n    return toeplitz_ntt<MODINT>(vh,\
    \ vw);\n}\n\ntemplate <class MODINT, class MATRIX,\n          typename std::enable_if<std::is_same<MATRIX,\
    \ square_toeplitz_ntt<MODINT>>::value>::type * = nullptr>\nsquare_toeplitz_ntt<MODINT>\
    \ gen_random_matrix() {\n    int N = uniform_int_distribution<int>(1, 100)(mt);\n\
    \    auto v = gen_random_vector<MODINT>(N * 2 - 1);\n    return square_toeplitz_ntt<MODINT>(v);\n\
    }\n\ntemplate <class MODINT, class MATRIX,\n          typename std::enable_if<std::is_same<MATRIX,\
    \ sparse_matrix<MODINT>>::value>::type * = nullptr>\nsparse_matrix<MODINT> gen_random_matrix()\
    \ {\n    int H = uniform_int_distribution<int>(1, 20)(mt),\n        W = max(H,\
    \ uniform_int_distribution<int>(1, 20)(mt));\n    sparse_matrix<MODINT> M(H, W);\n\
    \    for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) {\n  \
    \          MODINT v = uniform_int_distribution<int>(0, MODINT::mod() - 1)(mt);\n\
    \            M.add_element(i, j, v);\n        }\n    }\n    return M;\n}\n\ntemplate\
    \ <class MODINT, class MATRIX,\n          typename std::enable_if<std::is_same<MATRIX,\
    \ matrix<MODINT>>::value>::type * = nullptr>\nmatrix<MODINT> gen_random_matrix()\
    \ {\n    int H = uniform_int_distribution<int>(1, 20)(mt),\n        W = max(H,\
    \ uniform_int_distribution<int>(1, 20)(mt));\n    matrix<MODINT> M(H, W);\n  \
    \  for (int i = 0; i < H; i++) {\n        for (int j = 0; j < W; j++) {\n    \
    \        MODINT v = uniform_int_distribution<int>(0, MODINT::mod() - 1)(mt);\n\
    \            M[i][j] = v;\n        }\n    }\n    return M;\n}\n\ntemplate <typename\
    \ MATRIX, typename mint> void blackbox_mat_checker(int n_try) {\n    for (int\
    \ i = 0; i < n_try; i++) {\n        const MATRIX M = gen_random_matrix<mint, MATRIX>();\n\
    \        vector<vector<mint>> Mvv = M.vecvec();\n        const int H = M.height(),\
    \ W = M.width();\n        const auto b = gen_random_vector<mint>(H);\n       \
    \ // Check linear eq. solver\n        const auto x = linear_system_solver_lanczos(M,\
    \ b);\n        assert(M.prod(x) == b);\n\n        // Check prod()\n        const\
    \ auto c = gen_random_vector<mint>(W);\n        const auto Mc = M.prod(c);\n \
    \       vector<mint> Mc2(H);\n        for (int i = 0; i < H; i++) {\n        \
    \    for (int j = 0; j < W; j++) Mc2[i] += Mvv[i][j] * c[j];\n        }\n    \
    \    assert(Mc == Mc2);\n\n        // Check prod_left()\n        const auto a\
    \ = gen_random_vector<mint>(H);\n        const auto aM = M.prod_left(a);\n   \
    \     vector<mint> aM2(W);\n        for (int i = 0; i < H; i++) {\n          \
    \  for (int j = 0; j < W; j++) aM2[j] += Mvv[i][j] * a[i];\n        }\n      \
    \  assert(aM == aM2);\n\n        // Check black_box_determinant()\n        if\
    \ (H == W) {\n            mint det = blackbox_determinant<MATRIX, mint>(M);\n\
    \            mint det2 = matrix<mint>(Mvv).gauss_jordan().determinant_of_upper_triangle();\n\
    \            assert(det == det2);\n        }\n    }\n}\n\nint main() {\n    using\
    \ mint = ModInt<998244353>;\n    blackbox_mat_checker<toeplitz_ntt<mint>, mint>(1000);\n\
    \    blackbox_mat_checker<square_toeplitz_ntt<mint>, mint>(1000);\n    blackbox_mat_checker<sparse_matrix<mint>,\
    \ mint>(1000);\n    blackbox_mat_checker<matrix<mint>, mint>(1000);\n    puts(\"\
    Hello World\");\n}\n"
  dependsOn:
  - modint.hpp
  - linear_algebra_matrix/blackbox_algorithm.hpp
  - formal_power_series/linear_recurrence.hpp
  - linear_algebra_matrix/blackbox_matrices.hpp
  - convolution/ntt.hpp
  - linear_algebra_matrix/matrix.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp
  requiredBy: []
  timestamp: '2022-07-05 01:52:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp
- /verify/linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp.html
title: linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp
---
