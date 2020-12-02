---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: linear_algebra_matrix/det_of_sparse_matrix.hpp
    title: linear_algebra_matrix/det_of_sparse_matrix.hpp
  - icon: ':x:'
    path: linear_algebra_matrix/linear_recurrence.hpp
    title: linear_algebra_matrix/linear_recurrence.hpp
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':question:'
    path: random/rand_nondeterministic.hpp
    title: random/rand_nondeterministic.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sparse_matrix_det
    links:
    - https://judge.yosupo.jp/problem/sparse_matrix_det
  bundledCode: "#line 1 \"linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/sparse_matrix_det\"\n#line\
    \ 2 \"linear_algebra_matrix/det_of_sparse_matrix.hpp\"\n#include <cassert>\n#include\
    \ <numeric>\n#include <utility>\n#include <vector>\n\n#line 2 \"linear_algebra_matrix/linear_recurrence.hpp\"\
    \n#include <algorithm>\n#line 6 \"linear_algebra_matrix/linear_recurrence.hpp\"\
    \n\n// CUT begin\n// Berlekamp\u2013Massey algorithm\n// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>\n\
    // Complexity: O(N^2)\n// input: S = sequence from field K\n// return: L     \
    \     = degree of minimal polynomial,\n//         C_reversed = monic min. polynomial\
    \ (size = L + 1, reversed order, C_reversed[0] = 1))\n// Formula: convolve(S,\
    \ C_reversed)[i] = 0 for i >= L\n// Example:\n// - [1, 2, 4, 8, 16]   -> (1, [1,\
    \ -2])\n// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])\n// - [0, 0, 0, 0, 1]    ->\
    \ (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)\n// - []                 ->\
    \ (0, [1])\n// - [0, 0, 0]          -> (0, [1])\n// - [-2]               -> (1,\
    \ [1, 2])\ntemplate <typename Tfield> std::pair<int, std::vector<Tfield>> linear_recurrence(const\
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
    \ std::make_pair(L, C_reversed);\n}\n#line 2 \"random/rand_nondeterministic.hpp\"\
    \n#include <chrono>\n#include <random>\nusing namespace std;\n\n// CUT begin\n\
    struct rand_int_ {\n    using lint = long long;\n    mt19937 mt;\n    rand_int_()\
    \ : mt(chrono::steady_clock::now().time_since_epoch().count()) {}\n    lint operator()(lint\
    \ x) { return this->operator()(0, x); } // [0, x)\n    lint operator()(lint l,\
    \ lint r) {\n        uniform_int_distribution<lint> d(l, r - 1);\n        return\
    \ d(mt);\n    }\n} rnd;\n#line 9 \"linear_algebra_matrix/det_of_sparse_matrix.hpp\"\
    \n\n// CUT begin\n// Sparse matrix on ModInt/ModIntRuntime\ntemplate <typename\
    \ Tp> struct sparse_matrix {\n    int H, W;\n    std::vector<std::vector<std::pair<int,\
    \ Tp>>> vals;\n    sparse_matrix(int H = 0, int W = 0) : H(H), W(W), vals(H) {}\n\
    \    void add_element(int i, int j, Tp val) {\n        assert(i >= 0 and i < H);\n\
    \        assert(j >= 0 and i < W);\n        vals[i].emplace_back(j, val);\n  \
    \  }\n    Tp eval_bilinear(const std::vector<Tp> &vl, const std::vector<Tp> &vr)\
    \ const {\n        assert(vl.size() == H and vr.size() == W);\n        Tp ret\
    \ = 0;\n        for (int i = 0; i < H; i++) {\n            for (const auto &p\
    \ : vals[i]) { ret += vl[i] * p.second * vr[p.first]; }\n        }\n        return\
    \ ret;\n    }\n    static std::vector<Tp> prod(const sparse_matrix<Tp> &M, const\
    \ std::vector<Tp> &vec) {\n        assert(M.W == int(vec.size()));\n        std::vector<Tp>\
    \ ret(M.H);\n        for (int i = 0; i < M.H; i++) {\n            for (const auto\
    \ &p : M.vals[i]) { ret[i] += p.second * vec[p.first]; }\n        }\n        return\
    \ ret;\n    }\n    // Determinant of sparse matrix\n    // Complexity: O(NK +\
    \ N^2) (K: # of non-zero elements in M)\n    // Reference: <https://yukicoder.me/wiki/black_box_linear_algebra>\n\
    \    Tp Determinant() const {\n        assert(H == W);\n        const int N =\
    \ H, hi = Tp::get_mod();\n        std::vector<Tp> b(N), u(N), D(N);\n        for\
    \ (int i = 0; i < N; i++) { b[i] = rnd(1, hi), u[i] = rnd(1, hi), D[i] = rnd(1,\
    \ hi); }\n        std::vector<Tp> uMDib(2 * N);\n        for (int i = 0; i < 2\
    \ * N; i++) {\n            uMDib[i] = std::inner_product(u.begin(), u.end(), b.begin(),\
    \ Tp(0));\n            for (int j = 0; j < N; j++) { b[j] *= D[j]; }\n       \
    \     b = prod(*this, b);\n        }\n        auto ret = linear_recurrence<Tp>(uMDib);\n\
    \        Tp det = ret.second.back() * (N % 2 ? -1 : 1);\n        Tp ddet = 1;\n\
    \        for (auto d : D) ddet *= d;\n        return det / ddet;\n    }\n};\n\
    #line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#line 5 \"modint.hpp\"\
    \n\n// CUT begin\ntemplate <int mod> struct ModInt {\n#if __cplusplus >= 201402L\n\
    #define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using lint = long\
    \ long;\n    MDCONST static int get_mod() { return mod; }\n    static int get_primitive_root()\
    \ {\n        static int primitive_root = 0;\n        if (!primitive_root) {\n\
    \            primitive_root = [&]() {\n                std::set<int> fac;\n  \
    \              int v = mod - 1;\n                for (lint i = 2; i * i <= v;\
    \ i++)\n                    while (v % i == 0) fac.insert(i), v /= i;\n      \
    \          if (v > 1) fac.insert(v);\n                for (int g = 1; g < mod;\
    \ g++) {\n                    bool ok = true;\n                    for (auto i\
    \ : fac)\n                        if (ModInt(g).pow((mod - 1) / i) == 1) {\n \
    \                           ok = false;\n                            break;\n\
    \                        }\n                    if (ok) return g;\n          \
    \      }\n                return -1;\n            }();\n        }\n        return\
    \ primitive_root;\n    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n   \
    \ MDCONST ModInt &_setval(lint v) { return val = (v >= mod ? v - mod : v), *this;\
    \ }\n    MDCONST ModInt(lint v) { _setval(v % mod + mod); }\n    MDCONST explicit\
    \ operator bool() const { return val != 0; }\n    MDCONST ModInt operator+(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val + x.val); }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + mod); }\n    MDCONST ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % mod); }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % mod); }\n \
    \   MDCONST ModInt operator-() const { return ModInt()._setval(mod - val); }\n\
    \    MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod + x.val); }\n    friend MDCONST ModInt operator-(lint a, const ModInt\
    \ &x) { return ModInt()._setval(a % mod - x.val + mod); }\n    friend MDCONST\
    \ ModInt operator*(lint a, const ModInt &x) { return ModInt()._setval(a % mod\
    \ * x.val % mod); }\n    friend MDCONST ModInt operator/(lint a, const ModInt\
    \ &x) { return ModInt()._setval(a % mod * x.inv() % mod); }\n    MDCONST bool\
    \ operator==(const ModInt &x) const { return val == x.val; }\n    MDCONST bool\
    \ operator!=(const ModInt &x) const { return val != x.val; }\n    MDCONST bool\
    \ operator<(const ModInt &x) const { return val < x.val; } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { return\
    \ os << x.val; }\n    MDCONST ModInt pow(lint n) const {\n        lint ans = 1,\
    \ tmp = this->val;\n        while (n) {\n            if (n & 1) ans = ans * tmp\
    \ % mod;\n            tmp = tmp * tmp % mod, n /= 2;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<long long> facs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ <= l0) return;\n        facs.resize(N), invs.resize(N);\n        for (int i\
    \ = l0; i < N; i++) facs[i] = facs[i - 1] * i % mod;\n        long long facinv\
    \ = ModInt(facs.back()).pow(mod - 2).val;\n        for (int i = N - 1; i >= l0;\
    \ i--) {\n            invs[i] = facinv * facs[i - 1] % mod;\n            facinv\
    \ = facinv * i % mod;\n        }\n    }\n    MDCONST lint inv() const {\n    \
    \    if (this->val < 1 << 20) {\n            while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n            return invs[this->val];\n   \
    \     } else {\n            return this->pow(mod - 2).val;\n        }\n    }\n\
    \    MDCONST ModInt fac() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val];\n    }\n\n\
    \    MDCONST ModInt doublefac() const {\n        lint k = (this->val + 1) / 2;\n\
    \        return (this->val & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\
    \ : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST ModInt nCr(const ModInt\
    \ &r) const { return (this->val < r.val) ? 0 : this->fac() / ((*this - r).fac()\
    \ * r.fac()); }\n\n    ModInt sqrt() const {\n        if (val == 0) return 0;\n\
    \        if (mod == 2) return val;\n        if (pow((mod - 1) / 2) != 1) return\
    \ 0;\n        ModInt b = 1;\n        while (b.pow((mod - 1) / 2) == 1) b += 1;\n\
    \        int e = 0, m = mod - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n \
    \       ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n\
    \        ModInt z = b.pow(m);\n        while (y != 1) {\n            int j = 0;\n\
    \            ModInt t = y;\n            while (t != 1) j++, t *= t;\n        \
    \    z = z.pow(1LL << (e - j - 1));\n            x *= z, z *= z, y *= z;\n   \
    \         e = j;\n        }\n        return ModInt(std::min(x.val, mod - x.val));\n\
    \    }\n};\ntemplate <int mod> std::vector<long long> ModInt<mod>::facs = {1};\n\
    template <int mod> std::vector<long long> ModInt<mod>::invs = {0};\n\n// using\
    \ mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 5 \"linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp\"\
    \n\nint main() {\n    int N, K;\n    std::cin >> N >> K;\n    sparse_matrix<ModInt<998244353>>\
    \ M(N, N);\n    while (K--) {\n        int a, b, c;\n        std::cin >> a >>\
    \ b >> c;\n        M.add_element(a, b, c);\n    }\n    std::cout << M.Determinant()\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sparse_matrix_det\"\n#include\
    \ \"linear_algebra_matrix/det_of_sparse_matrix.hpp\"\n#include \"modint.hpp\"\n\
    #include <iostream>\n\nint main() {\n    int N, K;\n    std::cin >> N >> K;\n\
    \    sparse_matrix<ModInt<998244353>> M(N, N);\n    while (K--) {\n        int\
    \ a, b, c;\n        std::cin >> a >> b >> c;\n        M.add_element(a, b, c);\n\
    \    }\n    std::cout << M.Determinant() << '\\n';\n}\n"
  dependsOn:
  - linear_algebra_matrix/det_of_sparse_matrix.hpp
  - linear_algebra_matrix/linear_recurrence.hpp
  - random/rand_nondeterministic.hpp
  - modint.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
  requiredBy: []
  timestamp: '2020-12-02 23:44:04+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
- /verify/linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp.html
title: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
---
