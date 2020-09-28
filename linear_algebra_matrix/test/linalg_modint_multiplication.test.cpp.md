---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/linalg_modint.hpp
    title: linear_algebra_matrix/linalg_modint.hpp
  - icon: ':question:'
    path: modulus/modint_fixed.hpp
    title: modulus/modint_fixed.hpp
  - icon: ':heavy_check_mark:'
    path: modulus/modint_runtime.hpp
    title: modulus/modint_runtime.hpp
  - icon: ':heavy_check_mark:'
    path: number/bare_mod_algebra.hpp
    title: number/bare_mod_algebra.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D
  bundledCode: "#line 1 \"linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D\"\
    \n#line 2 \"linear_algebra_matrix/linalg_modint.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <iterator>\n#include <vector>\n\
    \n// CUT begin\ntemplate <typename T>\nstruct matrix\n{\n    int H, W;\n    std::vector<T>\
    \ elem;\n    typename std::vector<T>::iterator operator[](int i) { return elem.begin()\
    \ + i * W; }\n    inline T &at(int i, int j) { return elem[i * W + j]; }\n   \
    \ inline T get(int i, int j) const { return elem[i * W + j]; }\n    operator std::vector<std::vector<T>>()\
    \ const {\n        std::vector<std::vector<T>> ret(H);\n        for (int i = 0;\
    \ i < H; i++) std::copy(elem.begin() + i * W, elem.begin() + (i + 1) * W, std::back_inserter(ret[i]));\n\
    \        return ret;\n    }\n\n    matrix() = default;\n    matrix(int H, int\
    \ W) : H(H), W(W), elem(H * W) {}\n    matrix(const std::vector<std::vector<T>>\
    \ &d) : H(d.size()), W(d.size() ? d[0].size() : 0) {\n        for (auto &raw :\
    \ d) std::copy(raw.begin(), raw.end(), std::back_inserter(elem));\n    }\n\n \
    \   static matrix Identity(int N) {\n        matrix ret(N, N);\n        for (int\
    \ i = 0; i < N; i++) ret.at(i, i) = 1;\n        return ret;\n    }\n\n    matrix\
    \ operator-() const { matrix ret(H, W); for (int i = 0; i < H * W; i++) ret.elem[i]\
    \ = -elem[i]; return ret; }\n    matrix operator*(const T &v) const { matrix ret\
    \ = *this; for (auto &x : ret.elem) x *= v; return ret; }\n    matrix operator/(const\
    \ T &v) const { matrix ret = *this; for (auto &x : ret.elem) x /= v; return ret;\
    \ }\n    matrix operator+(const matrix &r) const { matrix ret = *this; for (int\
    \ i = 0; i < H * W; i++) ret.elem[i] += r.elem[i]; return ret; }\n    matrix operator-(const\
    \ matrix &r) const { matrix ret = *this; for (int i = 0; i < H * W; i++) ret.elem[i]\
    \ -= r.elem[i]; return ret; }\n    matrix operator*(const matrix &r) const {\n\
    \        matrix ret(H, r.W);\n        for (int i = 0; i < H; i++) {\n        \
    \    for (int k = 0; k < W; k++) {\n                for (int j = 0; j < r.W; j++)\
    \ {\n                    ret.at(i, j) += this->get(i, k) * r.get(k, j);\n    \
    \            }\n            }\n        }\n        return ret;\n    }\n    matrix\
    \ &operator*=(const T &v) { return *this = *this * v; }\n    matrix &operator/=(const\
    \ T &v) { return *this = *this / v; }\n    matrix &operator+=(const matrix &r)\
    \ { return *this = *this + r; }\n    matrix &operator-=(const matrix &r) { return\
    \ *this = *this - r; }\n    matrix &operator*=(const matrix &r) { return *this\
    \ = *this * r; }\n    bool operator==(const matrix &r) const { return H == r.H\
    \ and W == r.W and elem == r.elem; }\n    bool operator!=(const matrix &r) const\
    \ { return H != r.H or W != r.W or elem != r.elem; }\n    bool operator<(const\
    \ matrix &r) const { return elem < r.elem; }\n    matrix pow(int64_t n) const\
    \ {\n        matrix ret = Identity(H);\n        if (n == 0) return ret;\n    \
    \    for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {\n            ret *=\
    \ ret;\n            if ((n >> i) & 1) ret *= (*this);\n        }\n        return\
    \ ret;\n    }\n    matrix transpose() const {\n        matrix ret(W, H);\n   \
    \     for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) ret.at(j, i) = this->get(i,\
    \ j);\n        return ret;\n    }\n    // Gauss-Jordan elimination\n    // - Require\
    \ inverse for every non-zero element\n    // - Complexity: O(H^2 W)\n    matrix\
    \ gauss_jordan() const {\n        int c = 0;\n        matrix mtr(*this);\n   \
    \     for (int h = 0; h < H; h++) {\n            if (c == W) break;\n        \
    \    int piv = -1;\n            for (int j = h; j < H; j++) if (mtr.get(j, c))\
    \ {\n                piv = j;\n                break;\n            }\n       \
    \     if (piv == -1) { c++; h--; continue; }\n            if (h != piv) {\n  \
    \              for (int w = 0; w < W; w++) {\n                    std::swap(mtr[piv][w],\
    \ mtr[h][w]);\n                    mtr.at(piv, w) *= -1; // To preserve sign of\
    \ determinant\n                }\n            }\n            for (int hh = 0;\
    \ hh < H; hh++) if (hh != h) {\n                T coeff = mtr.at(hh, c) * mtr.at(h,\
    \ c).inv();\n                for (int w = W - 1; w >= c; w--) {\n            \
    \        mtr.at(hh, w) -= mtr.at(h, w) * coeff;\n                }\n         \
    \   }\n            c++;\n        }\n        return mtr;\n    }\n    int rank_of_gauss_jordan()\
    \ const {\n        for (int i = H * W - 1; i >= 0; i--) if (elem[i]) return i\
    \ / W + 1;\n        return 0;\n    }\n    T determinant_of_upper_triangle() const\
    \ {\n        T ret = 1;\n        for (int i = 0; i < H; i++) ret *= get(i, i);\n\
    \        return ret;\n    }\n    friend std::vector<T> operator*(const matrix\
    \ &m, const std::vector<T> &v) {\n        assert(m.W == int(v.size()));\n    \
    \    std::vector<T> ret(m.H);\n        for (int i = 0; i < m.H; i++) {\n     \
    \       for (int j = 0; j < m.W; j++) {\n                ret[i] += m.get(i, j)\
    \ * v[j];\n            }\n        }\n        return ret;\n    }\n    friend std::vector<T>\
    \ operator*(const std::vector<T> &v, const matrix &m) {\n        assert(int(v.size())\
    \ == m.H);\n        std::vector<T> ret(m.W);\n        for (int i = 0; i < m.H;\
    \ i++) {\n            for (int j = 0; j < m.W; j++) {\n                ret[j]\
    \ += v[i] * m.get(i, j);\n            }\n        }\n        return ret;\n    }\n\
    \    friend std::ostream &operator<<(std::ostream &os, const matrix &x) {\n  \
    \      os << \"[(\" << x.H << \" * \" << x.W << \" matrix)\";\n        os << \"\
    \\n[column sums: \";\n        for (int j = 0; j < x.W; j++) {\n            T s\
    \ = 0;\n            for (int i = 0; i < x.H; i++) s += x.get(i, j);\n        \
    \    os << s << \",\";\n        }\n        os << \"]\";\n        for (int i =\
    \ 0; i < x.H; i++) {\n            os << \"\\n[\";\n            for (int j = 0;\
    \ j < x.W; j++) os << x.get(i, j) << \",\";\n            os << \"]\";\n      \
    \  }\n        os << \"]\\n\";\n        return os;\n    }\n    friend std::istream\
    \ &operator>>(std::istream &is, matrix &x) {\n        for (auto &v : x.elem) is\
    \ >> v;\n        return is;\n    }\n};\n\n\n// Fibonacci numbers f(n) = af(n -\
    \ 1) + bf(n - 2)\n// Example (a = b = 1): 0=>1, 1=>1, 2=>2, 3=>3, 4=>5, ...\n\
    template <typename T>\nT Fibonacci(long long int k, int a = 1, int b = 1)\n{\n\
    \    matrix<T> mat(2, 2);\n    mat[0][1] = 1;\n    mat[1][0] = b;\n    mat[1][1]\
    \ = a;\n    return mat.pow(k + 1)[0][1];\n}\n#line 3 \"number/bare_mod_algebra.hpp\"\
    \n#include <utility>\n#line 5 \"number/bare_mod_algebra.hpp\"\n\n// CUT begin\n\
    using lint = long long;\n// Solve ax+by=gcd(a, b)\nlint extgcd(lint a, lint b,\
    \ lint &x, lint &y)\n{\n    lint d = a;\n    if (b != 0) d = extgcd(b, a % b,\
    \ y, x), y -= (a / b) * x;\n    else x = 1, y = 0;\n    return d;\n}\n// Calc\
    \ a^(-1) (MOD m)\nlint mod_inverse(lint a, lint m)\n{\n    lint x, y;\n    extgcd(a,\
    \ m, x, y);\n    return (m + x % m) % m;\n}\n\n// \u87FB\u672C P.262\n// \u4E2D\
    \u56FD\u5270\u4F59\u5B9A\u7406\u3092\u5229\u7528\u3057\u3066\uFF0C\u8272\u3005\
    \u306A\u7D20\u6570\u3067\u5272\u3063\u305F\u4F59\u308A\u304B\u3089\u5143\u306E\
    \u5024\u3092\u5FA9\u5143\n// \u9023\u7ACB\u7DDA\u5F62\u5408\u540C\u5F0F A * x\
    \ = B mod M \u306E\u89E3\n// Output: x = first MOD second\nstd::pair<lint, lint>\
    \ linear_congruence(const std::vector<lint> &A, const std::vector<lint> &B, const\
    \ std::vector<lint> &M)\n{\n    lint x = 0, m = 1;\n    for (int i = 0; i < (int)A.size();\
    \ i++) {\n        lint a = A[i] * m, b = B[i] - A[i] * x, d = std::__gcd(M[i],\
    \ a);\n        if (b % d != 0) {\n            return std::make_pair(0, -1); //\
    \ \u89E3\u306A\u3057\n        }\n        lint t = b / d * mod_inverse(a / d, M[i]\
    \ / d) % (M[i] / d);\n        x += m * t;\n        m *= M[i] / d;\n    }\n   \
    \ return std::make_pair((x < 0 ? x + m : x), m);\n}\n\nlint power(lint x, lint\
    \ n, lint MOD)\n{\n    lint ans = 1;\n    while (n > 0) {\n        if (n & 1)\
    \ (ans *= x) %= MOD;\n        (x *= x) %= MOD;\n       n >>= 1;\n    }\n   return\
    \ ans;\n}\n\n// Find smallest primitive root for given prime P \uFF08\u6700\u5C0F\
    \u306E\u539F\u59CB\u6839\u63A2\u7D22\uFF09\n// Complexity: maybe O(sqrt(p))\n\
    // Algorithm: <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>\n//\
    \ Verified: <https://yukicoder.me/submissions/405938>\n// Sample:\n//  - 998244353\
    \ ( = (119 << 23) + 1 ) -> 3\n//  - 163577857 ( = (39 << 22) + 1 ) -> 23\n// \
    \ - 2 -> 1\n//  - 1 -> -1\n\nlint find_smallest_primitive_root(lint p)\n{\n  \
    \  std::vector<lint> fac;\n    lint v = p - 1;\n    for (lint pp = 2; pp * pp\
    \ <= v; pp++) // prime factorization of (p - 1)\n    {\n        int e = 0;\n \
    \       while (v % pp == 0) e++, v /= pp;\n        if (e) fac.push_back(pp);\n\
    \    }\n    if (v > 1) fac.push_back(v);\n\n    for (lint g = 1; g < p; g++)\n\
    \    {\n        if (power(g, p - 1, p) != 1) return -1;\n        bool ok = true;\n\
    \        for (auto pp : fac)\n        {\n            if (power(g, (p - 1) / pp,\
    \ p) == 1)\n            {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n    return -1;\n\
    }\n#line 4 \"modulus/modint_fixed.hpp\"\n#include <set>\n\n// CUT begin\ntemplate\
    \ <int mod>\nstruct ModInt\n{\n    using lint = long long;\n    static int get_mod()\
    \ { return mod; }\n    static int get_primitive_root() {\n        static int primitive_root\
    \ = 0;\n        if (!primitive_root) {\n            primitive_root = [&](){\n\
    \                std::set<int> fac;\n                int v = mod - 1;\n      \
    \          for (lint i = 2; i * i <= v; i++) while (v % i == 0) fac.insert(i),\
    \ v /= i;\n                if (v > 1) fac.insert(v);\n                for (int\
    \ g = 1; g < mod; g++) {\n                    bool ok = true;\n              \
    \      for (auto i : fac) if (ModInt(g).power((mod - 1) / i) == 1) { ok = false;\
    \ break; }\n                    if (ok) return g;\n                }\n       \
    \         return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val;\n    constexpr ModInt() : val(0) {}\n    constexpr ModInt\
    \ &_setval(lint v) { val = (v >= mod ? v - mod : v); return *this; }\n    constexpr\
    \ ModInt(lint v) { _setval(v % mod + mod); }\n    explicit operator bool() const\
    \ { return val != 0; }\n    constexpr ModInt operator+(const ModInt &x) const\
    \ { return ModInt()._setval((lint)val + x.val); }\n    constexpr ModInt operator-(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val - x.val + mod); }\n   \
    \ constexpr ModInt operator*(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ * x.val % mod); }\n    constexpr ModInt operator/(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.inv() % mod); }\n    constexpr ModInt operator-()\
    \ const { return ModInt()._setval(mod - val); }\n    constexpr ModInt &operator+=(const\
    \ ModInt &x) { return *this = *this + x; }\n    constexpr ModInt &operator-=(const\
    \ ModInt &x) { return *this = *this - x; }\n    constexpr ModInt &operator*=(const\
    \ ModInt &x) { return *this = *this * x; }\n    constexpr ModInt &operator/=(const\
    \ ModInt &x) { return *this = *this / x; }\n    friend constexpr ModInt operator+(lint\
    \ a, const ModInt &x) { return ModInt()._setval(a % mod + x.val); }\n    friend\
    \ constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % mod - x.val + mod); }\n    friend constexpr ModInt operator*(lint a, const\
    \ ModInt &x) { return ModInt()._setval(a % mod * x.val % mod); }\n    friend constexpr\
    \ ModInt operator/(lint a, const ModInt &x) { return ModInt()._setval(a % mod\
    \ * x.inv() % mod); }\n    constexpr bool operator==(const ModInt &x) const {\
    \ return val == x.val; }\n    constexpr bool operator!=(const ModInt &x) const\
    \ { return val != x.val; }\n    bool operator<(const ModInt &x) const { return\
    \ val < x.val; }  // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) { lint t; is >> t; x = ModInt(t); return is; }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const ModInt &x) { os << x.val;  return os; }\n\
    \    constexpr lint power(lint n) const {\n        lint ans = 1, tmp = this->val;\n\
    \        while (n) {\n            if (n & 1) ans = ans * tmp % mod;\n        \
    \    tmp = tmp * tmp % mod;\n            n /= 2;\n        }\n        return ans;\n\
    \    }\n    constexpr lint inv() const { return this->power(mod - 2); }\n    constexpr\
    \ ModInt operator^(lint n) const { return ModInt(this->power(n)); }\n    constexpr\
    \ ModInt &operator^=(lint n) { return *this = *this ^ n; }\n\n    inline ModInt\
    \ fac() const {\n        static std::vector<ModInt> facs;\n        int l0 = facs.size();\n\
    \        if (l0 > this->val) return facs[this->val];\n\n        facs.resize(this->val\
    \ + 1);\n        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1)\
    \ : facs[i - 1] * ModInt(i));\n        return facs[this->val];\n    }\n\n    ModInt\
    \ doublefac() const {\n        lint k = (this->val + 1) / 2;\n        if (this->val\
    \ & 1) return ModInt(k * 2).fac() / ModInt(2).power(k) / ModInt(k).fac();\n  \
    \      else return ModInt(k).fac() * ModInt(2).power(k);\n    }\n\n    ModInt\
    \ nCr(const ModInt &r) const {\n        if (this->val < r.val) return ModInt(0);\n\
    \        return this->fac() / ((*this - r).fac() * r.fac());\n    }\n\n    ModInt\
    \ sqrt() const {\n        if (val == 0) return 0;\n        if (mod == 2) return\
    \ val;\n        if (power((mod - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n\
    \        while (b.power((mod - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod\
    \ - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = power((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.power(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.power(1LL << (e -\
    \ j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val, mod - x.val));\n    }\n};\n\n// constexpr\
    \ lint MOD = 998244353;\n// using mint = ModInt<MOD>;\n#line 5 \"modulus/modint_runtime.hpp\"\
    \n\n// CUT begin\nstruct ModIntRuntime\n{\n    using lint = long long int;\n \
    \   static int get_mod() { return mod; }\n    int val;\n    static int mod;\n\
    \    static std::vector<ModIntRuntime> &facs()\n    {\n        static std::vector<ModIntRuntime>\
    \ facs_;\n        return facs_;\n    }\n    static int &get_primitive_root() {\n\
    \        static int primitive_root_ = 0;\n        if (!primitive_root_) {\n  \
    \          primitive_root_ = [&](){\n                std::set<int> fac;\n    \
    \            int v = mod - 1;\n                for (lint i = 2; i * i <= v; i++)\
    \ while (v % i == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n\
    \                for (int g = 1; g < mod; g++) {\n                    bool ok\
    \ = true;\n                    for (auto i : fac) if (ModIntRuntime(g).power((mod\
    \ - 1) / i) == 1) { ok = false; break; }\n                    if (ok) return g;\n\
    \                }\n                return -1;\n            }();\n        }\n\
    \        return primitive_root_;\n    }\n    static void set_mod(const int &m)\
    \ {\n        if (mod != m) facs().clear();\n        mod = m;\n        get_primitive_root()\
    \ = 0;\n    }\n    ModIntRuntime &_setval(lint v) { val = (v >= mod ? v - mod\
    \ : v); return *this; }\n    ModIntRuntime() : val(0) {}\n    ModIntRuntime(lint\
    \ v) { _setval(v % mod + mod); }\n    explicit operator bool() const { return\
    \ val != 0; }\n    ModIntRuntime operator+(const ModIntRuntime &x) const { return\
    \ ModIntRuntime()._setval((lint)val + x.val); }\n    ModIntRuntime operator-(const\
    \ ModIntRuntime &x) const { return ModIntRuntime()._setval((lint)val - x.val +\
    \ mod); }\n    ModIntRuntime operator*(const ModIntRuntime &x) const { return\
    \ ModIntRuntime()._setval((lint)val * x.val % mod); }\n    ModIntRuntime operator/(const\
    \ ModIntRuntime &x) const { return ModIntRuntime()._setval((lint)val * x.inv()\
    \ % mod); }\n    ModIntRuntime operator-() const { return ModIntRuntime()._setval(mod\
    \ - val); }\n    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this\
    \ = *this + x; }\n    ModIntRuntime &operator-=(const ModIntRuntime &x) { return\
    \ *this = *this - x; }\n    ModIntRuntime &operator*=(const ModIntRuntime &x)\
    \ { return *this = *this * x; }\n    ModIntRuntime &operator/=(const ModIntRuntime\
    \ &x) { return *this = *this / x; }\n    friend ModIntRuntime operator+(lint a,\
    \ const ModIntRuntime &x) { return ModIntRuntime()._setval(a % mod + x.val); }\n\
    \    friend ModIntRuntime operator-(lint a, const ModIntRuntime &x) { return ModIntRuntime()._setval(a\
    \ % mod - x.val + mod); }\n    friend ModIntRuntime operator*(lint a, const ModIntRuntime\
    \ &x) { return ModIntRuntime()._setval(a % mod * x.val % mod); }\n    friend ModIntRuntime\
    \ operator/(lint a, const ModIntRuntime &x) { return ModIntRuntime()._setval(a\
    \ % mod * x.inv() % mod); }\n    bool operator==(const ModIntRuntime &x) const\
    \ { return val == x.val; }\n    bool operator!=(const ModIntRuntime &x) const\
    \ { return val != x.val; }\n    bool operator<(const ModIntRuntime &x) const {\
    \ return val < x.val; }  // To use std::map<ModIntRuntime, T>\n    friend std::istream\
    \ &operator>>(std::istream &is, ModIntRuntime &x) { lint t; is >> t; x = ModIntRuntime(t);\
    \ return is; }\n    friend std::ostream &operator<<(std::ostream &os, const ModIntRuntime\
    \ &x) { os << x.val;  return os; }\n \n    lint power(lint n) const {\n      \
    \  lint ans = 1, tmp = this->val;\n        while (n) {\n            if (n & 1)\
    \ ans = ans * tmp % mod;\n            tmp = tmp * tmp % mod;\n            n /=\
    \ 2;\n        }\n        return ans;\n    }\n    lint inv() const { return this->power(mod\
    \ - 2); }\n    ModIntRuntime operator^(lint n) const { return ModIntRuntime(this->power(n));\
    \ }\n    ModIntRuntime &operator^=(lint n) { return *this = *this ^ n; }\n \n\
    \    ModIntRuntime fac() const {\n        int l0 = facs().size();\n        if\
    \ (l0 > this->val) return facs()[this->val];\n \n        facs().resize(this->val\
    \ + 1);\n        for (int i = l0; i <= this->val; i++) facs()[i] = (i == 0 ? ModIntRuntime(1)\
    \ : facs()[i - 1] * ModIntRuntime(i));\n        return facs()[this->val];\n  \
    \  }\n \n    ModIntRuntime doublefac() const {\n        lint k = (this->val +\
    \ 1) / 2;\n        if (this->val & 1) return ModIntRuntime(k * 2).fac() / ModIntRuntime(2).power(k)\
    \ / ModIntRuntime(k).fac();\n        else return ModIntRuntime(k).fac() * ModIntRuntime(2).power(k);\n\
    \    }\n \n    ModIntRuntime nCr(const ModIntRuntime &r) const {\n        if (this->val\
    \ < r.val) return ModIntRuntime(0);\n        return this->fac() / ((*this - r).fac()\
    \ * r.fac());\n    }\n\n    ModIntRuntime sqrt() const {\n        if (val == 0)\
    \ return 0;\n        if (mod == 2) return val;\n        if (power((mod - 1) /\
    \ 2) != 1) return 0;\n        ModIntRuntime b = 1;\n        while (b.power((mod\
    \ - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod - 1;\n        while (m %\
    \ 2 == 0) m >>= 1, e++;\n        ModIntRuntime x = power((m - 1) / 2), y = (*this)\
    \ * x * x;\n        x *= (*this);\n        ModIntRuntime z = b.power(m);\n   \
    \     while (y != 1) {\n            int j = 0;\n            ModIntRuntime t =\
    \ y;\n            while (t != 1) j++, t *= t;\n            z = z.power(1LL <<\
    \ (e - j - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n   \
    \     }\n        return ModIntRuntime(std::min(x.val, mod - x.val));\n    }\n\
    };\nint ModIntRuntime::mod = 1;\n#line 7 \"linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp\"\
    \n\nconstexpr int MODfixed = 1000003;\nconstexpr int MODruntime = 10007;\n\nint\
    \ main()\n{\n    int N, M, L;\n    std::cin >> N >> M >> L;\n    matrix<ModInt<MODfixed>>\
    \ Afixed(N, M), Bfixed(M, L);\n    ModIntRuntime::set_mod(MODruntime);\n    std::cin\
    \ >> Afixed >> Bfixed;\n    matrix<ModIntRuntime> Aruntime(N, M), Bruntime(M,\
    \ L);\n    for (int i = 0; i < N; i++) {\n        for (int j = 0; j < M; j++)\
    \ {\n            Aruntime[i][j] = Afixed[i][j].val;\n        }\n    }\n\n    for\
    \ (int j = 0; j < M; j++) {\n        for (int k = 0; k < L; k++) {\n         \
    \   Bruntime[j][k] = Bfixed[j][k].val;\n        }\n    }\n\n    auto Cfixed =\
    \ Afixed * Bfixed;\n    auto Cruntime = Aruntime * Bruntime;\n\n    for (int i\
    \ = 0; i < N; i++)\n    {\n        for (int l = 0; l < L; l++) {\n           \
    \ std::cout << linear_congruence({1, 1}, {Cfixed[i][l].val, Cruntime[i][l].val},\
    \ {MODfixed, MODruntime}).first;\n            std::cout << (l == L - 1 ? \"\\\
    n\" : \" \");\n        }\n    }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_7_D\"\
    \n#include \"linear_algebra_matrix/linalg_modint.hpp\"\n#include \"number/bare_mod_algebra.hpp\"\
    \n#include \"modulus/modint_fixed.hpp\"\n#include \"modulus/modint_runtime.hpp\"\
    \n#include <iostream>\n\nconstexpr int MODfixed = 1000003;\nconstexpr int MODruntime\
    \ = 10007;\n\nint main()\n{\n    int N, M, L;\n    std::cin >> N >> M >> L;\n\
    \    matrix<ModInt<MODfixed>> Afixed(N, M), Bfixed(M, L);\n    ModIntRuntime::set_mod(MODruntime);\n\
    \    std::cin >> Afixed >> Bfixed;\n    matrix<ModIntRuntime> Aruntime(N, M),\
    \ Bruntime(M, L);\n    for (int i = 0; i < N; i++) {\n        for (int j = 0;\
    \ j < M; j++) {\n            Aruntime[i][j] = Afixed[i][j].val;\n        }\n \
    \   }\n\n    for (int j = 0; j < M; j++) {\n        for (int k = 0; k < L; k++)\
    \ {\n            Bruntime[j][k] = Bfixed[j][k].val;\n        }\n    }\n\n    auto\
    \ Cfixed = Afixed * Bfixed;\n    auto Cruntime = Aruntime * Bruntime;\n\n    for\
    \ (int i = 0; i < N; i++)\n    {\n        for (int l = 0; l < L; l++) {\n    \
    \        std::cout << linear_congruence({1, 1}, {Cfixed[i][l].val, Cruntime[i][l].val},\
    \ {MODfixed, MODruntime}).first;\n            std::cout << (l == L - 1 ? \"\\\
    n\" : \" \");\n        }\n    }\n}\n"
  dependsOn:
  - linear_algebra_matrix/linalg_modint.hpp
  - number/bare_mod_algebra.hpp
  - modulus/modint_fixed.hpp
  - modulus/modint_runtime.hpp
  isVerificationFile: true
  path: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
  requiredBy: []
  timestamp: '2020-09-29 00:37:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
layout: document
redirect_from:
- /verify/linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
- /verify/linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp.html
title: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
---
