---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
    title: Sum of exponential times polynomial limit ($\sum_{i=0}^\infty r^i i^d)
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: number/sieve.hpp
    title: "Linear sieve \uFF08\u7DDA\u5F62\u7BE9\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit
    links:
    - https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit
  bundledCode: "#line 1 \"formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\"\
    \n#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include <vector>\n\
    \n// CUT begin\ntemplate <int mod> struct ModInt {\n#if __cplusplus >= 201402L\n\
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
    \    if (this->val < std::min(mod >> 1, 1 << 21)) {\n            while (this->val\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val];\n\
    \        } else {\n            return this->pow(mod - 2).val;\n        }\n   \
    \ }\n    MDCONST ModInt fac() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val];\n    }\n\n\
    \    MDCONST ModInt doublefac() const {\n        lint k = (this->val + 1) / 2;\n\
    \        return (this->val & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n\
    \                               : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n\
    \    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val <\
    \ r.val) ? 0 : this->fac() / ((*this - r).fac() * r.fac());\n    }\n\n    ModInt\
    \ sqrt() const {\n        if (val == 0) return 0;\n        if (mod == 2) return\
    \ val;\n        if (pow((mod - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n\
    \        while (b.pow((mod - 1) / 2) == 1) b += 1;\n        int e = 0, m = mod\
    \ - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m -\
    \ 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j\
    \ - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val, mod - x.val));\n    }\n};\ntemplate <int\
    \ mod> std::vector<long long> ModInt<mod>::facs = {1};\ntemplate <int mod> std::vector<long\
    \ long> ModInt<mod>::invs = {0};\n\n// using mint = ModInt<998244353>;\n// using\
    \ mint = ModInt<1000000007>;\n#line 2 \"number/sieve.hpp\"\n#include <cassert>\n\
    #include <map>\n#line 5 \"number/sieve.hpp\"\n\n// CUT begin\n// Linear sieve\
    \ algorithm for fast prime factorization\n// Complexity: O(N) time, O(N) space:\n\
    // - MAXN = 10^7:  ~44 MB,  80~100 ms (Codeforces / AtCoder GCC, C++17)\n// -\
    \ MAXN = 10^8: ~435 MB, 810~980 ms (Codeforces / AtCoder GCC, C++17)\n// Reference:\n\
    // [1] D. Gries, J. Misra, \"A Linear Sieve Algorithm for Finding Prime Numbers,\"\
    \n//     Communications of the ACM, 21(12), 999-1003, 1978.\n// - https://cp-algorithms.com/algebra/prime-sieve-linear.html\n\
    // - https://37zigen.com/linear-sieve/\nstruct Sieve {\n    std::vector<int> min_factor;\n\
    \    std::vector<int> primes;\n    Sieve(int MAXN) : min_factor(MAXN + 1) {\n\
    \        for (int d = 2; d <= MAXN; d++) {\n            if (!min_factor[d]) {\n\
    \                min_factor[d] = d;\n                primes.emplace_back(d);\n\
    \            }\n            for (const auto &p : primes) {\n                if\
    \ (p > min_factor[d] or d * p > MAXN) break;\n                min_factor[d * p]\
    \ = p;\n            }\n        }\n    }\n    // Prime factorization for 1 <= x\
    \ <= MAXN^2\n    // Complexity: O(log x)           (x <= MAXN)\n    //       \
    \      O(MAXN / log MAXN) (MAXN < x <= MAXN^2)\n    template <typename T> std::map<T,\
    \ int> factorize(T x) {\n        std::map<T, int> ret;\n        assert(x > 0 and\
    \ x <= ((long long)min_factor.size() - 1) * ((long long)min_factor.size() - 1));\n\
    \        for (const auto &p : primes) {\n            if (x < T(min_factor.size()))\
    \ break;\n            while (!(x % p)) x /= p, ret[p]++;\n        }\n        if\
    \ (x >= T(min_factor.size())) ret[x]++, x = 1;\n        while (x > 1) ret[min_factor[x]]++,\
    \ x /= min_factor[x];\n        return ret;\n    }\n    // Enumerate divisors of\
    \ 1 <= x <= MAXN^2\n    // Be careful of highly composite numbers https://oeis.org/A002182/list\
    \ https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt\n    //\
    \ (n, (# of div. of n)): 45360->100, 735134400(<1e9)->1344, 963761198400(<1e12)->6720\n\
    \    template <typename T> std::vector<T> divisors(T x) {\n        std::vector<T>\
    \ ret{1};\n        for (const auto p : factorize(x)) {\n            int n = ret.size();\n\
    \            for (int i = 0; i < n; i++) {\n                for (T a = 1, d =\
    \ 1; d <= p.second; d++) {\n                    a *= p.first;\n              \
    \      ret.push_back(ret[i] * a);\n                }\n            }\n        }\n\
    \        return ret; // NOT sorted\n    }\n    // Moebius function Table, (-1)^{#\
    \ of different prime factors} for square-free x\n    // return: [0=>0, 1=>1, 2=>-1,\
    \ 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0, ...] https://oeis.org/A008683\n    std::vector<int>\
    \ GenerateMoebiusFunctionTable() {\n        std::vector<int> ret(min_factor.size());\n\
    \        for (unsigned i = 1; i < min_factor.size(); i++) {\n            if (i\
    \ == 1)\n                ret[i] = 1;\n            else if ((i / min_factor[i])\
    \ % min_factor[i] == 0)\n                ret[i] = 0;\n            else\n     \
    \           ret[i] = -ret[i / min_factor[i]];\n        }\n        return ret;\n\
    \    }\n    // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)\n    template <typename\
    \ MODINT> std::vector<MODINT> enumerate_kth_pows(long long K, int nmax) {\n  \
    \      assert(nmax < int(min_factor.size()));\n        std::vector<MODINT> ret(nmax\
    \ + 1);\n        ret[0] = 0, ret[1] = 1;\n        for (int n = 2; n <= nmax; n++)\
    \ {\n            if (min_factor[n] == n) {\n                ret[n] = MODINT(n).pow(K);\n\
    \            } else {\n                ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];\n\
    \            }\n        }\n        return ret;\n    }\n};\n// Sieve sieve(1 <<\
    \ 15);  // (can factorize n <= 10^9)\n#line 3 \"formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\"\
    \n\n// CUT begin\n// $d$ \u6B21\u4EE5\u4E0B\u306E\u591A\u9805\u5F0F $f(x)$ \u3068\
    \u5B9A\u6570 $r$ \u306B\u3064\u3044\u3066\uFF0C\n// $\\sum_{i=0}^\\infty r^i f(i)$\
    \ \u306E\u5024\u3092 $[f(0), ..., f(d - 1), f(d)]$ \u306E\u5024\u304B\u3089 $O(d)$\
    \ \u3067\u8A08\u7B97\uFF0E\n// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\n\
    template <typename MODINT> MODINT sum_of_exponential_times_polynomial_limit(MODINT\
    \ r, std::vector<MODINT> init) {\n    auto &bs = init;\n    if (bs.empty()) return\
    \ 0;\n    const int d = int(bs.size()) - 1;\n    if (d == 0) { return 1 / (1 -\
    \ r); }\n    MODINT rp = 1;\n    for (int i = 1; i <= d; i++) rp *= r, bs[i] =\
    \ bs[i] * rp + bs[i - 1];\n    MODINT ret = 0;\n    rp = 1;\n    for (int i =\
    \ 0; i <= d; i++) {\n        ret += bs[d - i] * MODINT(d + 1).nCr(i) * rp;\n \
    \       rp *= -r;\n    }\n    return ret / MODINT(1 - r).pow(d + 1);\n};\n#line\
    \ 6 \"formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp\"\
    \nusing namespace std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    int\
    \ r, d;\n    cin >> r >> d;\n    auto initial_terms = Sieve(d).enumerate_kth_pows<mint>(d,\
    \ d);\n    cout << sum_of_exponential_times_polynomial_limit<mint>(r, initial_terms)\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\"\
    \n#include \"../../modint.hpp\"\n#include \"../../number/sieve.hpp\"\n#include\
    \ \"../sum_of_exponential_times_polynomial_limit.hpp\"\n#include <iostream>\n\
    using namespace std;\nusing mint = ModInt<998244353>;\n\nint main() {\n    int\
    \ r, d;\n    cin >> r >> d;\n    auto initial_terms = Sieve(d).enumerate_kth_pows<mint>(d,\
    \ d);\n    cout << sum_of_exponential_times_polynomial_limit<mint>(r, initial_terms)\
    \ << '\\n';\n}\n"
  dependsOn:
  - modint.hpp
  - number/sieve.hpp
  - formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
  isVerificationFile: true
  path: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
  requiredBy: []
  timestamp: '2021-05-03 12:51:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
layout: document
redirect_from:
- /verify/formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
- /verify/formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp.html
title: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
---
