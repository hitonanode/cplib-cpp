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
    path: number/bare_mod_algebra.hpp
    title: number/bare_mod_algebra.hpp
  - icon: ':heavy_check_mark:'
    path: number/modint_runtime.hpp
    title: number/modint_runtime.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D
  bundledCode: "#line 1 \"linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D\"\
    \n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include <vector>\n\
    \n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus >= 201402L\n\
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
    \ + x.val); }\n    MDCONST ModInt operator-(const ModInt &x) const {\n       \
    \ return ModInt()._setval((lint)val - x.val + md);\n    }\n    MDCONST ModInt\
    \ operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val\
    \ * x.val % md);\n    }\n    MDCONST ModInt operator/(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val * x.inv() % md);\n    }\n    MDCONST\
    \ ModInt operator-() const { return ModInt()._setval(md - val); }\n    MDCONST\
    \ ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n    MDCONST\
    \ ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n    MDCONST\
    \ ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n    MDCONST\
    \ ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n    friend\
    \ MDCONST ModInt operator+(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md + x.val);\n    }\n    friend MDCONST ModInt operator-(lint a, const ModInt\
    \ &x) {\n        return ModInt()._setval(a % md - x.val + md);\n    }\n    friend\
    \ MDCONST ModInt operator*(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.val % md);\n    }\n    friend MDCONST ModInt operator/(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.inv() % md);\n    }\n\
    \    MDCONST bool operator==(const ModInt &x) const { return val == x.val; }\n\
    \    MDCONST bool operator!=(const ModInt &x) const { return val != x.val; }\n\
    \    MDCONST bool operator<(const ModInt &x) const {\n        return val < x.val;\n\
    \    } // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) {\n        lint t;\n        return is >> t, x = ModInt(t), is;\n\
    \    }\n    MDCONST friend std::ostream &operator<<(std::ostream &os, const ModInt\
    \ &x) {\n        return os << x.val;\n    }\n    MDCONST ModInt pow(lint n) const\
    \ {\n        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if\
    \ (n & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST\
    \ static void _precalculation(int N) {\n        int l0 = facs.size();\n      \
    \  if (N > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N),\
    \ facinvs.resize(N), invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n    \
    \    for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n\
    \        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n\
    \    }\n    MDCONST lint inv() const {\n        if (this->val < std::min(md >>\
    \ 1, 1 << 21)) {\n            while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val].val;\n        } else {\n         \
    \   return this->pow(md - 2).val;\n        }\n    }\n    MDCONST ModInt fac()\
    \ const {\n        while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facs[this->val];\n    }\n    MDCONST ModInt facinv() const\
    \ {\n        while (this->val >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facinvs[this->val];\n    }\n    MDCONST ModInt doublefac()\
    \ const {\n        lint k = (this->val + 1) / 2;\n        return (this->val &\
    \ 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n          \
    \                     : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST\
    \ ModInt nCr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST ModInt\
    \ nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0 : this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val\
    \ == 0) return 0;\n        if (md == 2) return val;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
    \ md - x.val));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"number/bare_mod_algebra.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <tuple>\n#include <utility>\n\
    #line 7 \"number/bare_mod_algebra.hpp\"\n\n// CUT begin\n// Solve ax+by=gcd(a,\
    \ b)\ntemplate <class Int> Int extgcd(Int a, Int b, Int &x, Int &y) {\n    Int\
    \ d = a;\n    if (b != 0) {\n        d = extgcd(b, a % b, y, x), y -= (a / b)\
    \ * x;\n    } else {\n        x = 1, y = 0;\n    }\n    return d;\n}\n// Calculate\
    \ a^(-1) (MOD m) s if gcd(a, m) == 1\n// Calculate x s.t. ax == gcd(a, m) MOD\
    \ m\ntemplate <class Int> Int mod_inverse(Int a, Int m) {\n    Int x, y;\n   \
    \ extgcd<Int>(a, m, x, y);\n    x %= m;\n    return x + (x < 0) * m;\n}\n\n//\
    \ Require: 1 <= b\n// return: (g, x) s.t. g = gcd(a, b), xa = g MOD b, 0 <= x\
    \ < b/g\ntemplate <class Int> /* constexpr */ std::pair<Int, Int> inv_gcd(Int\
    \ a, Int b) {\n    a %= b;\n    if (a < 0) a += b;\n    if (a == 0) return {b,\
    \ 0};\n    Int s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n        Int u =\
    \ s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp = s;\n        s\
    \ = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0 < 0) m0 += b /\
    \ s;\n    return {s, m0};\n}\n\ntemplate <class Int>\n/* constexpr */ std::pair<Int,\
    \ Int> crt(const std::vector<Int> &r, const std::vector<Int> &m) {\n    assert(r.size()\
    \ == m.size());\n    int n = int(r.size());\n    // Contracts: 0 <= r0 < m0\n\
    \    Int r0 = 0, m0 = 1;\n    for (int i = 0; i < n; i++) {\n        assert(1\
    \ <= m[i]);\n        Int r1 = r[i] % m[i], m1 = m[i];\n        if (r1 < 0) r1\
    \ += m1;\n        if (m0 < m1) {\n            std::swap(r0, r1);\n           \
    \ std::swap(m0, m1);\n        }\n        if (m0 % m1 == 0) {\n            if (r0\
    \ % m1 != r1) return {0, 0};\n            continue;\n        }\n        Int g,\
    \ im;\n        std::tie(g, im) = inv_gcd<Int>(m0, m1);\n\n        Int u1 = m1\
    \ / g;\n        if ((r1 - r0) % g) return {0, 0};\n\n        Int x = (r1 - r0)\
    \ / g % u1 * im % u1;\n        r0 += x * m0;\n        m0 *= u1;\n        if (r0\
    \ < 0) r0 += m0;\n    }\n    return {r0, m0};\n}\n\n// \u87FB\u672C P.262\n//\
    \ \u4E2D\u56FD\u5270\u4F59\u5B9A\u7406\u3092\u5229\u7528\u3057\u3066\uFF0C\u8272\
    \u3005\u306A\u7D20\u6570\u3067\u5272\u3063\u305F\u4F59\u308A\u304B\u3089\u5143\
    \u306E\u5024\u3092\u5FA9\u5143\n// \u9023\u7ACB\u7DDA\u5F62\u5408\u540C\u5F0F\
    \ A * x = B mod M \u306E\u89E3\n// Requirement: M[i] > 0\n// Output: x = first\
    \ MOD second (if solution exists), (0, 0) (otherwise)\ntemplate <class Int>\n\
    std::pair<Int, Int>\nlinear_congruence(const std::vector<Int> &A, const std::vector<Int>\
    \ &B, const std::vector<Int> &M) {\n    Int r = 0, m = 1;\n    assert(A.size()\
    \ == M.size());\n    assert(B.size() == M.size());\n    for (int i = 0; i < (int)A.size();\
    \ i++) {\n        assert(M[i] > 0);\n        const Int ai = A[i] % M[i];\n   \
    \     Int a = ai * m, b = B[i] - ai * r, d = std::__gcd(M[i], a);\n        if\
    \ (b % d != 0) {\n            return std::make_pair(0, 0); // \u89E3\u306A\u3057\
    \n        }\n        Int t = b / d * mod_inverse<Int>(a / d, M[i] / d) % (M[i]\
    \ / d);\n        r += m * t;\n        m *= M[i] / d;\n    }\n    return std::make_pair((r\
    \ < 0 ? r + m : r), m);\n}\n\nint pow_mod(int x, long long n, int md) {\n    if\
    \ (md == 1) return 0;\n    long long ans = 1;\n    while (n > 0) {\n        if\
    \ (n & 1) ans = ans * x % md;\n        x = (long long)x * x % md;\n        n >>=\
    \ 1;\n    }\n    return ans;\n}\n#line 5 \"number/modint_runtime.hpp\"\n\n// CUT\
    \ begin\nstruct ModIntRuntime {\nprivate:\n    static int md;\n\npublic:\n   \
    \ using lint = long long;\n    static int mod() { return md; }\n    int val;\n\
    \    static std::vector<ModIntRuntime> &facs() {\n        static std::vector<ModIntRuntime>\
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
    \    }\n    ModIntRuntime &_setval(lint v) {\n        val = (v >= md ? v - md\
    \ : v);\n        return *this;\n    }\n    ModIntRuntime() : val(0) {}\n    ModIntRuntime(lint\
    \ v) { _setval(v % md + md); }\n    explicit operator bool() const { return val\
    \ != 0; }\n    ModIntRuntime operator+(const ModIntRuntime &x) const {\n     \
    \   return ModIntRuntime()._setval((lint)val + x.val);\n    }\n    ModIntRuntime\
    \ operator-(const ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val\
    \ - x.val + md);\n    }\n    ModIntRuntime operator*(const ModIntRuntime &x) const\
    \ {\n        return ModIntRuntime()._setval((lint)val * x.val % md);\n    }\n\
    \    ModIntRuntime operator/(const ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val\
    \ * x.inv() % md);\n    }\n    ModIntRuntime operator-() const { return ModIntRuntime()._setval(md\
    \ - val); }\n    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this\
    \ = *this + x; }\n    ModIntRuntime &operator-=(const ModIntRuntime &x) { return\
    \ *this = *this - x; }\n    ModIntRuntime &operator*=(const ModIntRuntime &x)\
    \ { return *this = *this * x; }\n    ModIntRuntime &operator/=(const ModIntRuntime\
    \ &x) { return *this = *this / x; }\n    friend ModIntRuntime operator+(lint a,\
    \ const ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md + x.val);\n\
    \    }\n    friend ModIntRuntime operator-(lint a, const ModIntRuntime &x) {\n\
    \        return ModIntRuntime()._setval(a % md - x.val + md);\n    }\n    friend\
    \ ModIntRuntime operator*(lint a, const ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a\
    \ % md * x.val % md);\n    }\n    friend ModIntRuntime operator/(lint a, const\
    \ ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md * x.inv()\
    \ % md);\n    }\n    bool operator==(const ModIntRuntime &x) const { return val\
    \ == x.val; }\n    bool operator!=(const ModIntRuntime &x) const { return val\
    \ != x.val; }\n    bool operator<(const ModIntRuntime &x) const {\n        return\
    \ val < x.val;\n    } // To use std::map<ModIntRuntime, T>\n    friend std::istream\
    \ &operator>>(std::istream &is, ModIntRuntime &x) {\n        lint t;\n       \
    \ return is >> t, x = ModIntRuntime(t), is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const ModIntRuntime &x) {\n        return os << x.val;\n    }\n\n    lint\
    \ power(lint n) const {\n        lint ans = 1, tmp = this->val;\n        while\
    \ (n) {\n            if (n & 1) ans = ans * tmp % md;\n            tmp = tmp *\
    \ tmp % md;\n            n /= 2;\n        }\n        return ans;\n    }\n    ModIntRuntime\
    \ pow(lint n) const { return power(n); }\n    lint inv() const { return this->power(md\
    \ - 2); }\n\n    ModIntRuntime fac() const {\n        int l0 = facs().size();\n\
    \        if (l0 > this->val) return facs()[this->val];\n\n        facs().resize(this->val\
    \ + 1);\n        for (int i = l0; i <= this->val; i++)\n            facs()[i]\
    \ = (i == 0 ? ModIntRuntime(1) : facs()[i - 1] * ModIntRuntime(i));\n        return\
    \ facs()[this->val];\n    }\n\n    ModIntRuntime doublefac() const {\n       \
    \ lint k = (this->val + 1) / 2;\n        return (this->val & 1)\n            \
    \       ? ModIntRuntime(k * 2).fac() / (ModIntRuntime(2).pow(k) * ModIntRuntime(k).fac())\n\
    \                   : ModIntRuntime(k).fac() * ModIntRuntime(2).pow(k);\n    }\n\
    \n    ModIntRuntime nCr(const ModIntRuntime &r) const {\n        return (this->val\
    \ < r.val) ? ModIntRuntime(0) : this->fac() / ((*this - r).fac() * r.fac());\n\
    \    }\n\n    ModIntRuntime sqrt() const {\n        if (val == 0) return 0;\n\
    \        if (md == 2) return val;\n        if (power((md - 1) / 2) != 1) return\
    \ 0;\n        ModIntRuntime b = 1;\n        while (b.power((md - 1) / 2) == 1)\
    \ b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0) m >>= 1,\
    \ e++;\n        ModIntRuntime x = power((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModIntRuntime z = b.power(m);\n        while (y\
    \ != 1) {\n            int j = 0;\n            ModIntRuntime t = y;\n        \
    \    while (t != 1) j++, t *= t;\n            z = z.power(1LL << (e - j - 1));\n\
    \            x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return\
    \ ModIntRuntime(std::min(x.val, md - x.val));\n    }\n};\nint ModIntRuntime::md\
    \ = 1;\n#line 4 \"linear_algebra_matrix/matrix.hpp\"\n#include <cmath>\n#include\
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
    \ return i / W + 1;\n        }\n        return 0;\n    }\n    T determinant_of_upper_triangle()\
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
    \    }\n};\n#line 7 \"linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp\"\
    \nusing namespace std;\n\nconstexpr int MODfixed = 1000003;\nconstexpr int MODruntime\
    \ = 10007;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, M, L;\n    cin >> N >> M >> L;\n    matrix<ModInt<MODfixed>> Afixed(N,\
    \ M), Bfixed(M, L);\n    ModIntRuntime::set_mod(MODruntime);\n    cin >> Afixed\
    \ >> Bfixed;\n    matrix<ModIntRuntime> Aruntime(N, M), Bruntime(M, L);\n    for\
    \ (int i = 0; i < N; i++) {\n        for (int j = 0; j < M; j++) Aruntime[i][j]\
    \ = Afixed[i][j].val;\n    }\n\n    for (int j = 0; j < M; j++) {\n        for\
    \ (int k = 0; k < L; k++) Bruntime[j][k] = Bfixed[j][k].val;\n    }\n\n    auto\
    \ Cfixed = Afixed * Bfixed;\n    auto Cruntime = Aruntime * Bruntime;\n\n    for\
    \ (int i = 0; i < N; i++) {\n        for (int l = 0; l < L; l++) {\n         \
    \   cout << linear_congruence<long long>(\n                        {1, 1}, {Cfixed[i][l].val,\
    \ Cruntime[i][l].val}, {MODfixed, MODruntime})\n                        .first;\n\
    \            cout << (l == L - 1 ? \"\\n\" : \" \");\n        }\n    }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D\"\
    \n#include \"../../modint.hpp\"\n#include \"../../number/bare_mod_algebra.hpp\"\
    \n#include \"../../number/modint_runtime.hpp\"\n#include \"../matrix.hpp\"\n#include\
    \ <iostream>\nusing namespace std;\n\nconstexpr int MODfixed = 1000003;\nconstexpr\
    \ int MODruntime = 10007;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, M, L;\n    cin >> N >> M >> L;\n    matrix<ModInt<MODfixed>> Afixed(N,\
    \ M), Bfixed(M, L);\n    ModIntRuntime::set_mod(MODruntime);\n    cin >> Afixed\
    \ >> Bfixed;\n    matrix<ModIntRuntime> Aruntime(N, M), Bruntime(M, L);\n    for\
    \ (int i = 0; i < N; i++) {\n        for (int j = 0; j < M; j++) Aruntime[i][j]\
    \ = Afixed[i][j].val;\n    }\n\n    for (int j = 0; j < M; j++) {\n        for\
    \ (int k = 0; k < L; k++) Bruntime[j][k] = Bfixed[j][k].val;\n    }\n\n    auto\
    \ Cfixed = Afixed * Bfixed;\n    auto Cruntime = Aruntime * Bruntime;\n\n    for\
    \ (int i = 0; i < N; i++) {\n        for (int l = 0; l < L; l++) {\n         \
    \   cout << linear_congruence<long long>(\n                        {1, 1}, {Cfixed[i][l].val,\
    \ Cruntime[i][l].val}, {MODfixed, MODruntime})\n                        .first;\n\
    \            cout << (l == L - 1 ? \"\\n\" : \" \");\n        }\n    }\n}\n"
  dependsOn:
  - modint.hpp
  - number/bare_mod_algebra.hpp
  - number/modint_runtime.hpp
  - linear_algebra_matrix/matrix.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
  requiredBy: []
  timestamp: '2022-01-27 23:13:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
- /verify/linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp.html
title: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
---
