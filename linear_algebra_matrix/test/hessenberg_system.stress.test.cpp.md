---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/hessenberg_system.hpp
    title: Hessenberg linear system
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: number/dual_number.hpp
    title: "Dual number \uFF08\u4E8C\u91CD\u6570\uFF09"
  - icon: ':heavy_check_mark:'
    path: random/xorshift.hpp
    title: random/xorshift.hpp
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
  bundledCode: "#line 1 \"linear_algebra_matrix/test/hessenberg_system.stress.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#line 1 \"number/dual_number.hpp\"\n#include <type_traits>\n\nnamespace\
    \ dual_number_ {\nstruct has_id_method_impl {\n    template <class T_> static\
    \ auto check(T_ *) -> decltype(T_::id(), std::true_type());\n    template <class\
    \ T_> static auto check(...) -> std::false_type;\n};\ntemplate <class T_> struct\
    \ has_id : decltype(has_id_method_impl::check<T_>(nullptr)) {};\n} // namespace\
    \ dual_number_\n\n// Dual number \uFF08\u4E8C\u91CD\u6570\uFF09\n// Verified:\
    \ https://atcoder.jp/contests/abc235/tasks/abc235_f\ntemplate <class T> struct\
    \ DualNumber {\n    T a, b; // a + bx\n\n    template <typename T2, typename std::enable_if<dual_number_::has_id<T2>::value>::type\
    \ * = nullptr>\n    static T2 _T_id() {\n        return T2::id();\n    }\n   \
    \ template <typename T2, typename std::enable_if<!dual_number_::has_id<T2>::value>::type\
    \ * = nullptr>\n    static T2 _T_id() {\n        return T2(1);\n    }\n\n    DualNumber(T\
    \ x = T(), T y = T()) : a(x), b(y) {}\n    static DualNumber id() { return DualNumber(_T_id<T>(),\
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
    \ bx = 0 (b \\neq 0 is assumed)\n};\n#line 3 \"linear_algebra_matrix/hessenberg_system.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n// Solve Ax =\
    \ b, where A is n x n (square), lower Hessenberg, and non-singular.\n// Complexity:\
    \ O(n^2)\n// Verified: https://atcoder.jp/contests/abc249/tasks/abc249_h\ntemplate\
    \ <class T>\nstd::vector<T>\nsolve_lower_hessenberg(const std::vector<std::vector<T>>\
    \ &A, const std::vector<T> &b) {\n    const int N = A.size();\n    if (!N) return\
    \ {};\n    assert(int(A[0].size()) == N and int(b.size()) == N);\n\n    using\
    \ dual = DualNumber<T>;\n    std::vector<dual> sol(N);\n    for (int h = 0; h\
    \ < N;) {\n        sol[h] = dual(0, 1);\n        for (int i = h;; ++i) {\n   \
    \         dual y = b[i];\n            for (int j = 0; j <= i; ++j) y -= sol[j]\
    \ * A[i][j];\n            T a = i + 1 < N ? A[i][i + 1] : T();\n            if\
    \ (a == T()) {\n                T x0 = y.root();\n                while (h <=\
    \ i) sol[h] = sol[h].eval(x0), ++h;\n                break;\n            } else\
    \ {\n                sol[i + 1] = y / a;\n            }\n        }\n    }\n  \
    \  std::vector<T> ret(N);\n    for (int i = 0; i < N; ++i) ret[i] = sol[i].a;\n\
    \    return ret;\n}\n\n// Solve Ax = b, where A is n x n (square), upper Hessenberg,\
    \ and non-singular\n// Complexity: O(n^2)\ntemplate <class T>\nstd::vector<T>\
    \ solve_upper_hessenberg(std::vector<std::vector<T>> A, std::vector<T> b) {\n\
    \    std::reverse(A.begin(), A.end());\n    for (auto &v : A) std::reverse(v.begin(),\
    \ v.end());\n    std::reverse(b.begin(), b.end());\n    auto ret = solve_lower_hessenberg(A,\
    \ b);\n    std::reverse(ret.begin(), ret.end());\n    return ret;\n}\n#line 3\
    \ \"modint.hpp\"\n#include <iostream>\n#include <set>\n#line 6 \"modint.hpp\"\n\
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
    // using mint = ModInt<1000000007>;\n#line 2 \"random/xorshift.hpp\"\n#include\
    \ <cstdint>\n\n// CUT begin\nuint32_t rand_int() // XorShift random integer generator\n\
    {\n    static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;\n\
    \    uint32_t t = x ^ (x << 11);\n    x = y;\n    y = z;\n    z = w;\n    return\
    \ w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n}\ndouble rand_double() { return (double)rand_int()\
    \ / UINT32_MAX; }\n#line 8 \"linear_algebra_matrix/test/hessenberg_system.stress.test.cpp\"\
    \nusing namespace std;\n\nusing mint = ModInt<1000000007>;\n\nvoid test_lower_hessenberg_random()\
    \ {\n    for (int t = 0; t < 10000; ++t) {\n        int N = t / 100;\n       \
    \ vector<vector<mint>> A(N, vector<mint>(N));\n        vector<mint> x(N);\n\n\
    \        const double p = rand_double();\n        for (int i = 0; i < N; ++i)\
    \ {\n            x[i] = rand_int() % mint::mod();\n\n            for (int j =\
    \ 0; j < i; ++j) A[i][j] = rand_int() % mint::mod();\n            A[i][i] = 1\
    \ + rand_int() % (mint::mod() - 1);\n            if (i + 1 < N and rand_double()\
    \ < p) A[i][i + 1] = rand_int() % mint::mod();\n        }\n\n        vector<mint>\
    \ b(N);\n        for (int i = 0; i < N; ++i) {\n            for (int j = 0; j\
    \ < N; ++j) b[i] += A[i][j] * x[j];\n        }\n\n        assert(x == solve_lower_hessenberg<mint>(A,\
    \ b));\n    }\n}\n\nvoid test_upper_hessenberg_random() {\n    for (int t = 0;\
    \ t < 10000; ++t) {\n        int N = t / 100;\n        vector<vector<mint>> A(N,\
    \ vector<mint>(N));\n        vector<mint> x(N);\n\n        const double p = rand_double();\n\
    \        for (int i = 0; i < N; ++i) {\n            x[i] = rand_int() % mint::mod();\n\
    \n            for (int j = i + 1; j < N; ++j) A[i][j] = rand_int() % mint::mod();\n\
    \            A[i][i] = 1 + rand_int() % (mint::mod() - 1);\n            if (i\
    \ and rand_double() < p) A[i][i - 1] = rand_int() % mint::mod();\n        }\n\n\
    \        vector<mint> b(N);\n        for (int i = 0; i < N; ++i) {\n         \
    \   for (int j = 0; j < N; ++j) b[i] += A[i][j] * x[j];\n        }\n\n       \
    \ assert(x == solve_upper_hessenberg<mint>(A, b));\n    }\n}\n\nvoid test_lower_hessenberg_hand()\
    \ {\n    vector<vector<mint>> A{{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};\n    vector<mint>\
    \ b{2, 3, 4}, x{4, 2, 3};\n    assert(solve_lower_hessenberg<mint>(A, b) == x);\n\
    }\n\nint main() {\n    test_lower_hessenberg_random();\n    test_lower_hessenberg_hand();\n\
    \    test_upper_hessenberg_random();\n    cout << \"Hello World\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../hessenberg_system.hpp\"\n#include \"../../modint.hpp\"\
    \n#include \"../../random/xorshift.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <vector>\nusing namespace std;\n\nusing mint = ModInt<1000000007>;\n\n\
    void test_lower_hessenberg_random() {\n    for (int t = 0; t < 10000; ++t) {\n\
    \        int N = t / 100;\n        vector<vector<mint>> A(N, vector<mint>(N));\n\
    \        vector<mint> x(N);\n\n        const double p = rand_double();\n     \
    \   for (int i = 0; i < N; ++i) {\n            x[i] = rand_int() % mint::mod();\n\
    \n            for (int j = 0; j < i; ++j) A[i][j] = rand_int() % mint::mod();\n\
    \            A[i][i] = 1 + rand_int() % (mint::mod() - 1);\n            if (i\
    \ + 1 < N and rand_double() < p) A[i][i + 1] = rand_int() % mint::mod();\n   \
    \     }\n\n        vector<mint> b(N);\n        for (int i = 0; i < N; ++i) {\n\
    \            for (int j = 0; j < N; ++j) b[i] += A[i][j] * x[j];\n        }\n\n\
    \        assert(x == solve_lower_hessenberg<mint>(A, b));\n    }\n}\n\nvoid test_upper_hessenberg_random()\
    \ {\n    for (int t = 0; t < 10000; ++t) {\n        int N = t / 100;\n       \
    \ vector<vector<mint>> A(N, vector<mint>(N));\n        vector<mint> x(N);\n\n\
    \        const double p = rand_double();\n        for (int i = 0; i < N; ++i)\
    \ {\n            x[i] = rand_int() % mint::mod();\n\n            for (int j =\
    \ i + 1; j < N; ++j) A[i][j] = rand_int() % mint::mod();\n            A[i][i]\
    \ = 1 + rand_int() % (mint::mod() - 1);\n            if (i and rand_double() <\
    \ p) A[i][i - 1] = rand_int() % mint::mod();\n        }\n\n        vector<mint>\
    \ b(N);\n        for (int i = 0; i < N; ++i) {\n            for (int j = 0; j\
    \ < N; ++j) b[i] += A[i][j] * x[j];\n        }\n\n        assert(x == solve_upper_hessenberg<mint>(A,\
    \ b));\n    }\n}\n\nvoid test_lower_hessenberg_hand() {\n    vector<vector<mint>>\
    \ A{{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};\n    vector<mint> b{2, 3, 4}, x{4, 2, 3};\n\
    \    assert(solve_lower_hessenberg<mint>(A, b) == x);\n}\n\nint main() {\n   \
    \ test_lower_hessenberg_random();\n    test_lower_hessenberg_hand();\n    test_upper_hessenberg_random();\n\
    \    cout << \"Hello World\\n\";\n}\n"
  dependsOn:
  - linear_algebra_matrix/hessenberg_system.hpp
  - number/dual_number.hpp
  - modint.hpp
  - random/xorshift.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
  requiredBy: []
  timestamp: '2023-08-05 18:05:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
- /verify/linear_algebra_matrix/test/hessenberg_system.stress.test.cpp.html
title: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
---
