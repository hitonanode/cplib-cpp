---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: number/modint_runtime.hpp
    title: number/modint_runtime.hpp
  - icon: ':question:'
    path: number/sieve.hpp
    title: "Linear sieve \uFF08\u7DDA\u5F62\u7BE9\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"number/test/sieve.stress.test.cpp\"\n#define PROBLEM \"\
    https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\" // DUMMY\n\
    #line 2 \"number/sieve.hpp\"\n#include <cassert>\n#include <map>\n#include <vector>\n\
    \n// CUT begin\n// Linear sieve algorithm for fast prime factorization\n// Complexity:\
    \ O(N) time, O(N) space:\n// - MAXN = 10^7:  ~44 MB,  80~100 ms (Codeforces /\
    \ AtCoder GCC, C++17)\n// - MAXN = 10^8: ~435 MB, 810~980 ms (Codeforces / AtCoder\
    \ GCC, C++17)\n// Reference:\n// [1] D. Gries, J. Misra, \"A Linear Sieve Algorithm\
    \ for Finding Prime Numbers,\"\n//     Communications of the ACM, 21(12), 999-1003,\
    \ 1978.\n// - https://cp-algorithms.com/algebra/prime-sieve-linear.html\n// -\
    \ https://37zigen.com/linear-sieve/\nstruct Sieve {\n    std::vector<int> min_factor;\n\
    \    std::vector<int> primes;\n    Sieve(int MAXN) : min_factor(MAXN + 1) {\n\
    \        for (int d = 2; d <= MAXN; d++) {\n            if (!min_factor[d]) {\n\
    \                min_factor[d] = d;\n                primes.emplace_back(d);\n\
    \            }\n            for (const auto &p : primes) {\n                if\
    \ (p > min_factor[d] or d * p > MAXN) break;\n                min_factor[d * p]\
    \ = p;\n            }\n        }\n    }\n    // Prime factorization for 1 <= x\
    \ <= MAXN^2\n    // Complexity: O(log x)           (x <= MAXN)\n    //       \
    \      O(MAXN / log MAXN) (MAXN < x <= MAXN^2)\n    template <class T> std::map<T,\
    \ int> factorize(T x) const {\n        std::map<T, int> ret;\n        assert(x\
    \ > 0 and\n               x <= ((long long)min_factor.size() - 1) * ((long long)min_factor.size()\
    \ - 1));\n        for (const auto &p : primes) {\n            if (x < T(min_factor.size()))\
    \ break;\n            while (!(x % p)) x /= p, ret[p]++;\n        }\n        if\
    \ (x >= T(min_factor.size())) ret[x]++, x = 1;\n        while (x > 1) ret[min_factor[x]]++,\
    \ x /= min_factor[x];\n        return ret;\n    }\n    // Enumerate divisors of\
    \ 1 <= x <= MAXN^2\n    // Be careful of highly composite numbers https://oeis.org/A002182/list\n\
    \    // https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt (n,\
    \ (# of div. of n)):\n    // 45360->100, 735134400(<1e9)->1344, 963761198400(<1e12)->6720\n\
    \    template <class T> std::vector<T> divisors(T x) const {\n        std::vector<T>\
    \ ret{1};\n        for (const auto p : factorize(x)) {\n            int n = ret.size();\n\
    \            for (int i = 0; i < n; i++) {\n                for (T a = 1, d =\
    \ 1; d <= p.second; d++) {\n                    a *= p.first;\n              \
    \      ret.push_back(ret[i] * a);\n                }\n            }\n        }\n\
    \        return ret; // NOT sorted\n    }\n    // Euler phi functions of divisors\
    \ of given x\n    // Verified: ABC212 G https://atcoder.jp/contests/abc212/tasks/abc212_g\n\
    \    // Complexity: O(sqrt(x) + d(x))\n    template <class T> std::map<T, T> euler_of_divisors(T\
    \ x) const {\n        assert(x >= 1);\n        std::map<T, T> ret;\n        ret[1]\
    \ = 1;\n        std::vector<T> divs{1};\n        for (auto p : factorize(x)) {\n\
    \            int n = ret.size();\n            for (int i = 0; i < n; i++) {\n\
    \                ret[divs[i] * p.first] = ret[divs[i]] * (p.first - 1);\n    \
    \            divs.push_back(divs[i] * p.first);\n                for (T a = divs[i]\
    \ * p.first, d = 1; d < p.second; a *= p.first, d++) {\n                    ret[a\
    \ * p.first] = ret[a] * p.first;\n                    divs.push_back(a * p.first);\n\
    \                }\n            }\n        }\n        return ret;\n    }\n   \
    \ // Moebius function Table, (-1)^{# of different prime factors} for square-free\
    \ x\n    // return: [0=>0, 1=>1, 2=>-1, 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0,\
    \ ...] https://oeis.org/A008683\n    std::vector<int> GenerateMoebiusFunctionTable()\
    \ const {\n        std::vector<int> ret(min_factor.size());\n        for (unsigned\
    \ i = 1; i < min_factor.size(); i++) {\n            if (i == 1) {\n          \
    \      ret[i] = 1;\n            } else if ((i / min_factor[i]) % min_factor[i]\
    \ == 0) {\n                ret[i] = 0;\n            } else {\n               \
    \ ret[i] = -ret[i / min_factor[i]];\n            }\n        }\n        return\
    \ ret;\n    }\n    // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)\n    // Note:\
    \ **0^0 == 1**\n    template <class MODINT> std::vector<MODINT> enumerate_kth_pows(long\
    \ long K, int nmax) const {\n        assert(nmax < int(min_factor.size()));\n\
    \        assert(K >= 0);\n        if (K == 0) return std::vector<MODINT>(nmax\
    \ + 1, 1);\n        std::vector<MODINT> ret(nmax + 1);\n        ret[0] = 0, ret[1]\
    \ = 1;\n        for (int n = 2; n <= nmax; n++) {\n            if (min_factor[n]\
    \ == n) {\n                ret[n] = MODINT(n).pow(K);\n            } else {\n\
    \                ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];\n     \
    \       }\n        }\n        return ret;\n    }\n};\n// Sieve sieve((1 << 20));\n\
    #line 2 \"number/modint_runtime.hpp\"\n#include <iostream>\n#include <set>\n#line\
    \ 5 \"number/modint_runtime.hpp\"\n\n// CUT begin\nstruct ModIntRuntime {\nprivate:\n\
    \    static int md;\n\npublic:\n    using lint = long long;\n    static int mod()\
    \ { return md; }\n    int val;\n    static std::vector<ModIntRuntime> &facs()\
    \ {\n        static std::vector<ModIntRuntime> facs_;\n        return facs_;\n\
    \    }\n    static int &get_primitive_root() {\n        static int primitive_root_\
    \ = 0;\n        if (!primitive_root_) {\n            primitive_root_ = [&]() {\n\
    \                std::set<int> fac;\n                int v = md - 1;\n       \
    \         for (lint i = 2; i * i <= v; i++)\n                    while (v % i\
    \ == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n  \
    \              for (int g = 1; g < md; g++) {\n                    bool ok = true;\n\
    \                    for (auto i : fac)\n                        if (ModIntRuntime(g).power((md\
    \ - 1) / i) == 1) {\n                            ok = false;\n               \
    \             break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root_;\n    }\n    static void set_mod(const int\
    \ &m) {\n        if (md != m) facs().clear();\n        md = m;\n        get_primitive_root()\
    \ = 0;\n    }\n    ModIntRuntime &_setval(lint v) {\n        val = (v >= md ?\
    \ v - md : v);\n        return *this;\n    }\n    ModIntRuntime() : val(0) {}\n\
    \    ModIntRuntime(lint v) { _setval(v % md + md); }\n    explicit operator bool()\
    \ const { return val != 0; }\n    ModIntRuntime operator+(const ModIntRuntime\
    \ &x) const {\n        return ModIntRuntime()._setval((lint)val + x.val);\n  \
    \  }\n    ModIntRuntime operator-(const ModIntRuntime &x) const {\n        return\
    \ ModIntRuntime()._setval((lint)val - x.val + md);\n    }\n    ModIntRuntime operator*(const\
    \ ModIntRuntime &x) const {\n        return ModIntRuntime()._setval((lint)val\
    \ * x.val % md);\n    }\n    ModIntRuntime operator/(const ModIntRuntime &x) const\
    \ {\n        return ModIntRuntime()._setval((lint)val * x.inv() % md);\n    }\n\
    \    ModIntRuntime operator-() const { return ModIntRuntime()._setval(md - val);\
    \ }\n    ModIntRuntime &operator+=(const ModIntRuntime &x) { return *this = *this\
    \ + x; }\n    ModIntRuntime &operator-=(const ModIntRuntime &x) { return *this\
    \ = *this - x; }\n    ModIntRuntime &operator*=(const ModIntRuntime &x) { return\
    \ *this = *this * x; }\n    ModIntRuntime &operator/=(const ModIntRuntime &x)\
    \ { return *this = *this / x; }\n    friend ModIntRuntime operator+(lint a, const\
    \ ModIntRuntime &x) {\n        return ModIntRuntime()._setval(a % md + x.val);\n\
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
    \ = 1;\n#line 4 \"number/test/sieve.stress.test.cpp\"\n#include <algorithm>\n\
    #line 6 \"number/test/sieve.stress.test.cpp\"\n#include <cstdio>\n#line 9 \"number/test/sieve.stress.test.cpp\"\
    \nusing namespace std;\n\nstruct Case {\n    int SIEVE_SIZE;\n    int MAX;\n};\n\
    \nint euler_phi(int x) {\n    int ret = 0;\n    for (int d = 1; d <= x; d++) ret\
    \ += (std::__gcd(d, x) == 1);\n    return ret;\n}\n\nvoid test_divisors(Case testcase)\
    \ {\n    const Sieve sieve(testcase.SIEVE_SIZE);\n    for (int x = 1; x <= testcase.MAX;\
    \ x++) {\n        auto divs = sieve.divisors(x);\n        std::vector<int> is_div(x\
    \ + 1);\n        for (auto d : divs) is_div.at(d) = 1;\n        for (int y = 1;\
    \ y <= x; y++) assert(is_div.at(y) == (x % y == 0));\n    }\n\n    cerr << \"\
    divisors(): passed\" << endl;\n}\n\nvoid test_euler_of_divisors(Case testcase)\
    \ {\n    const Sieve sieve(testcase.SIEVE_SIZE);\n    for (int x = 1; x <= testcase.MAX;\
    \ x++) {\n        auto div2euler = sieve.euler_of_divisors(x);\n        for (auto\
    \ de : div2euler) {\n            assert(euler_phi(de.first) == de.second);\n \
    \           assert(x % de.first == 0);\n        }\n        assert(div2euler.size()\
    \ == sieve.divisors(x).size());\n    }\n\n    cerr << \"euler_of_divisors(): passed\"\
    \ << endl;\n}\n\nvoid test_moebius_table(int HI) {\n    const Sieve sieve_hi(HI);\n\
    \    const auto answer = sieve_hi.GenerateMoebiusFunctionTable();\n    assert(int(answer.size())\
    \ == HI + 1);\n\n    for (int x = 1; x <= HI; x++) {\n        int ret = 1;\n \
    \       for (auto p : sieve_hi.primes) {\n            if (x % (p * p) == 0) ret\
    \ = 0;\n            if (x % p == 0) ret *= -1;\n        }\n        assert(answer[x]\
    \ == ret);\n    }\n\n    for (int x = 1; x <= HI - 1; x++) {\n        auto mu\
    \ = Sieve(x).GenerateMoebiusFunctionTable();\n        assert(int(mu.size()) ==\
    \ x + 1);\n        for (int i = 0; i < x + 1; i++) assert(mu[i] == answer[i]);\n\
    \    }\n\n    cerr << \"GenerateMoebiusFunctionTable(): passed\" << endl;\n}\n\
    \nvoid test_enumerate_kth_pows(int hi_sieve_size) {\n    for (int sieve_size =\
    \ 1; sieve_size <= hi_sieve_size; sieve_size++) {\n        const Sieve sieve(sieve_size);\n\
    \        for (int nmax = 1; nmax <= sieve_size; nmax++) {\n            for (int\
    \ p = 1; p <= 20; p++) {\n                using mint = ModIntRuntime;\n      \
    \          mint::set_mod(p);\n                for (int k = 0; k < 10; k++) {\n\
    \                    auto ret = sieve.enumerate_kth_pows<mint>(k, nmax);\n   \
    \                 assert(int(ret.size()) == nmax + 1);\n                    for\
    \ (int i = 0; i <= nmax; i++) assert(ret[i] == mint(i).pow(k));\n            \
    \    }\n            }\n        }\n    }\n    cerr << \"enumerate_kth_pows(): passed\"\
    \ << endl;\n}\n\nint main() {\n    std::vector<Case> cases{{31, 31 * 31}, {100,\
    \ 1000}, {2, 4}};\n    for (auto testcase : cases) {\n        test_divisors(testcase);\n\
    \        test_euler_of_divisors(testcase);\n    }\n\n    test_moebius_table(1000);\n\
    \    test_enumerate_kth_pows(100);\n\n    puts(\"Hello World\");\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../sieve.hpp\"\n#include \"../modint_runtime.hpp\"\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cstdio>\n#include <iostream>\n#include\
    \ <vector>\nusing namespace std;\n\nstruct Case {\n    int SIEVE_SIZE;\n    int\
    \ MAX;\n};\n\nint euler_phi(int x) {\n    int ret = 0;\n    for (int d = 1; d\
    \ <= x; d++) ret += (std::__gcd(d, x) == 1);\n    return ret;\n}\n\nvoid test_divisors(Case\
    \ testcase) {\n    const Sieve sieve(testcase.SIEVE_SIZE);\n    for (int x = 1;\
    \ x <= testcase.MAX; x++) {\n        auto divs = sieve.divisors(x);\n        std::vector<int>\
    \ is_div(x + 1);\n        for (auto d : divs) is_div.at(d) = 1;\n        for (int\
    \ y = 1; y <= x; y++) assert(is_div.at(y) == (x % y == 0));\n    }\n\n    cerr\
    \ << \"divisors(): passed\" << endl;\n}\n\nvoid test_euler_of_divisors(Case testcase)\
    \ {\n    const Sieve sieve(testcase.SIEVE_SIZE);\n    for (int x = 1; x <= testcase.MAX;\
    \ x++) {\n        auto div2euler = sieve.euler_of_divisors(x);\n        for (auto\
    \ de : div2euler) {\n            assert(euler_phi(de.first) == de.second);\n \
    \           assert(x % de.first == 0);\n        }\n        assert(div2euler.size()\
    \ == sieve.divisors(x).size());\n    }\n\n    cerr << \"euler_of_divisors(): passed\"\
    \ << endl;\n}\n\nvoid test_moebius_table(int HI) {\n    const Sieve sieve_hi(HI);\n\
    \    const auto answer = sieve_hi.GenerateMoebiusFunctionTable();\n    assert(int(answer.size())\
    \ == HI + 1);\n\n    for (int x = 1; x <= HI; x++) {\n        int ret = 1;\n \
    \       for (auto p : sieve_hi.primes) {\n            if (x % (p * p) == 0) ret\
    \ = 0;\n            if (x % p == 0) ret *= -1;\n        }\n        assert(answer[x]\
    \ == ret);\n    }\n\n    for (int x = 1; x <= HI - 1; x++) {\n        auto mu\
    \ = Sieve(x).GenerateMoebiusFunctionTable();\n        assert(int(mu.size()) ==\
    \ x + 1);\n        for (int i = 0; i < x + 1; i++) assert(mu[i] == answer[i]);\n\
    \    }\n\n    cerr << \"GenerateMoebiusFunctionTable(): passed\" << endl;\n}\n\
    \nvoid test_enumerate_kth_pows(int hi_sieve_size) {\n    for (int sieve_size =\
    \ 1; sieve_size <= hi_sieve_size; sieve_size++) {\n        const Sieve sieve(sieve_size);\n\
    \        for (int nmax = 1; nmax <= sieve_size; nmax++) {\n            for (int\
    \ p = 1; p <= 20; p++) {\n                using mint = ModIntRuntime;\n      \
    \          mint::set_mod(p);\n                for (int k = 0; k < 10; k++) {\n\
    \                    auto ret = sieve.enumerate_kth_pows<mint>(k, nmax);\n   \
    \                 assert(int(ret.size()) == nmax + 1);\n                    for\
    \ (int i = 0; i <= nmax; i++) assert(ret[i] == mint(i).pow(k));\n            \
    \    }\n            }\n        }\n    }\n    cerr << \"enumerate_kth_pows(): passed\"\
    \ << endl;\n}\n\nint main() {\n    std::vector<Case> cases{{31, 31 * 31}, {100,\
    \ 1000}, {2, 4}};\n    for (auto testcase : cases) {\n        test_divisors(testcase);\n\
    \        test_euler_of_divisors(testcase);\n    }\n\n    test_moebius_table(1000);\n\
    \    test_enumerate_kth_pows(100);\n\n    puts(\"Hello World\");\n}\n"
  dependsOn:
  - number/sieve.hpp
  - number/modint_runtime.hpp
  isVerificationFile: true
  path: number/test/sieve.stress.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: number/test/sieve.stress.test.cpp
layout: document
redirect_from:
- /verify/number/test/sieve.stress.test.cpp
- /verify/number/test/sieve.stress.test.cpp.html
title: number/test/sieve.stress.test.cpp
---
