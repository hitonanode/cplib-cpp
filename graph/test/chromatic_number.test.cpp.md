---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/chromatic_number.hpp
    title: "Chromatic number of undirected graph \uFF08\u7121\u5411\u30B0\u30E9\u30D5\
      \u306E\u5F69\u8272\u6570\uFF09"
  - icon: ':question:'
    path: number/factorize.hpp
    title: number/factorize.hpp
  - icon: ':question:'
    path: number/modint_runtime.hpp
    title: number/modint_runtime.hpp
  - icon: ':heavy_check_mark:'
    path: random/rand_nondeterministic.hpp
    title: random/rand_nondeterministic.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/chromatic_number
    links:
    - https://judge.yosupo.jp/problem/chromatic_number
  bundledCode: "#line 1 \"graph/test/chromatic_number.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/chromatic_number\"\n#line 2 \"graph/chromatic_number.hpp\"\
    \n#include <numeric>\n#include <vector>\n\n// CUT begin\n// (vertex) chromatic\
    \ number: \uFF08\u9802\u70B9\uFF09\u5F69\u8272\u6570\n// Verified: https://judge.yosupo.jp/problem/chromatic_number,\
    \ https://atcoder.jp/contests/abc187/tasks/abc187_f\n// Reference:\n// [1] A.\
    \ Bjorklund and T. Husfeldt, \"Inclusion--Exclusion Algorithms for Counting Set\
    \ Partitions,\"\n//     2006 47th Annual IEEE Symposium on Foundations of Computer\
    \ Science (FOCS'06).\n// - https://www.slideshare.net/wata_orz/ss-12131479\ntemplate\
    \ <typename MODINT, typename Int> int ChromaticNumber(const std::vector<Int> &edge)\
    \ {\n    const int V = edge.size(), S = 1 << V;\n    if (V == 0) return 0;\n \
    \   std::vector<MODINT> f(S), g(S);\n    for (int s = 0; s < S; s++) g[s] = (__builtin_popcount(s)\
    \ & 1) ? 1 : -1;\n    f[0] = 1;\n    for (int s = 1; s < S; s++) {\n        int\
    \ i = __builtin_ctz(s);\n        f[s] = f[s - (1 << i)] + f[(s - (1 << i)) & ~edge[i]];\n\
    \    }\n    for (int k = 1; k < V; k++) {\n        for (int s = 0; s < S; s++)\
    \ g[s] *= f[s];\n        if (std::accumulate(g.begin(), g.end(), MODINT(0)).val)\
    \ return k;\n    }\n    return V;\n};\n#line 2 \"number/factorize.hpp\"\n#include\
    \ <algorithm>\n#include <array>\n#include <cassert>\n#line 6 \"number/factorize.hpp\"\
    \n\n// CUT begin\nnamespace SPRP {\n// http://miller-rabin.appspot.com/\nconst\
    \ std::vector<std::vector<__int128>> bases{\n    {126401071349994536},       \
    \                       // < 291831\n    {336781006125, 9639812373923155},   \
    \               // < 1050535501 (1e9)\n    {2, 2570940, 211991001, 3749873356},\
    \               // < 47636622961201 (4e13)\n    {2, 325, 9375, 28178, 450775,\
    \ 9780504, 1795265022} // <= 2^64\n};\ninline int get_id(long long n) {\n    if\
    \ (n < 291831) {\n        return 0;\n    } else if (n < 1050535501) {\n      \
    \  return 1;\n    } else if (n < 47636622961201)\n        return 2;\n    else\
    \ {\n        return 3;\n    }\n}\n} // namespace SPRP\n\n// Miller-Rabin primality\
    \ test\n// https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%A9%E3%83%BC%E2%80%93%E3%83%A9%E3%83%93%E3%83%B3%E7%B4%A0%E6%95%B0%E5%88%A4%E5%AE%9A%E6%B3%95\n\
    // Complexity: O(lg n) per query\nstruct {\n    long long modpow(__int128 x, __int128\
    \ n, long long mod) noexcept {\n        __int128 ret = 1;\n        for (x %= mod;\
    \ n; x = x * x % mod, n >>= 1) ret = (n & 1) ? ret * x % mod : ret;\n        return\
    \ ret;\n    }\n    bool operator()(long long n) noexcept {\n        if (n < 2)\
    \ return false;\n        if (n % 2 == 0) return n == 2;\n        int s = __builtin_ctzll(n\
    \ - 1);\n\n        for (__int128 a : SPRP::bases[SPRP::get_id(n)]) {\n       \
    \     if (a % n == 0) continue;\n            a = modpow(a, (n - 1) >> s, n);\n\
    \            bool may_composite = true;\n            if (a == 1) continue;\n \
    \           for (int r = s; r--; a = a * a % n) {\n                if (a == n\
    \ - 1) may_composite = false;\n            }\n            if (may_composite) return\
    \ false;\n        }\n        return true;\n    }\n} is_prime;\n\nstruct {\n  \
    \  // Pollard's rho algorithm: find factor greater than 1\n    long long find_factor(long\
    \ long n) {\n        assert(n > 1);\n        if (n % 2 == 0) return 2;\n     \
    \   if (is_prime(n)) return n;\n        long long c = 1;\n        auto f = [&](__int128\
    \ x) -> long long { return (x * x + c) % n; };\n\n        for (int t = 1;; t++)\
    \ {\n            long long x0 = t, m = std::max(n >> 3, 1LL), x, ys, y = x0, r\
    \ = 1, g, q = 1;\n            do {\n                x = y;\n                for\
    \ (int i = r; i--;) y = f(y);\n                long long k = 0;\n            \
    \    do {\n                    ys = y;\n                    for (int i = std::min(m,\
    \ r - k); i--;)\n                        y = f(y), q = __int128(q) * std::abs(x\
    \ - y) % n;\n                    g = std::__gcd<long long>(q, n);\n          \
    \          k += m;\n                } while (k < r and g <= 1);\n            \
    \    r <<= 1;\n            } while (g <= 1);\n            if (g == n) {\n    \
    \            do {\n                    ys = f(ys);\n                    g = std::__gcd(std::abs(x\
    \ - ys), n);\n                } while (g <= 1);\n            }\n            if\
    \ (g != n) return g;\n        }\n    }\n\n    std::vector<long long> operator()(long\
    \ long n) {\n        std::vector<long long> ret;\n        while (n > 1) {\n  \
    \          long long f = find_factor(n);\n            if (f < n) {\n         \
    \       auto tmp = operator()(f);\n                ret.insert(ret.end(), tmp.begin(),\
    \ tmp.end());\n            } else\n                ret.push_back(n);\n       \
    \     n /= f;\n        }\n        std::sort(ret.begin(), ret.end());\n       \
    \ return ret;\n    }\n} FactorizeLonglong;\n#line 2 \"number/modint_runtime.hpp\"\
    \n#include <iostream>\n#include <set>\n#line 5 \"number/modint_runtime.hpp\"\n\
    \n// CUT begin\nstruct ModIntRuntime {\nprivate:\n    static int md;\n\npublic:\n\
    \    using lint = long long;\n    static int mod() { return md; }\n    int val;\n\
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
    \ = 1;\n#line 2 \"random/rand_nondeterministic.hpp\"\n#include <chrono>\n#include\
    \ <random>\nusing namespace std;\n\n// CUT begin\nstruct rand_int_ {\n    using\
    \ lint = long long;\n    mt19937 mt;\n    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)\n\
    \    lint operator()(lint l, lint r) {\n        uniform_int_distribution<lint>\
    \ d(l, r - 1);\n        return d(mt);\n    }\n} rnd;\n#line 6 \"graph/test/chromatic_number.test.cpp\"\
    \n\n#line 9 \"graph/test/chromatic_number.test.cpp\"\nusing namespace std;\n\n\
    int main() {\n    int N, M;\n    cin >> N >> M;\n    vector<int> to(N);\n\n  \
    \  long long md = 4;\n    do { md = rnd(1LL << 29, 1LL << 30); } while (!is_prime(md));\n\
    \    cerr << md << '\\n';\n    ModIntRuntime::set_mod(md);\n\n    while (M--)\
    \ {\n        int u, v;\n        cin >> u >> v;\n        to[u] |= 1 << v;\n   \
    \     to[v] |= 1 << u;\n    }\n    cout << ChromaticNumber<ModIntRuntime>(to)\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/chromatic_number\"\n#include\
    \ \"../chromatic_number.hpp\"\n#include \"../../number/factorize.hpp\"\n#include\
    \ \"../../number/modint_runtime.hpp\"\n#include \"../../random/rand_nondeterministic.hpp\"\
    \n\n#include <iostream>\n#include <vector>\nusing namespace std;\n\nint main()\
    \ {\n    int N, M;\n    cin >> N >> M;\n    vector<int> to(N);\n\n    long long\
    \ md = 4;\n    do { md = rnd(1LL << 29, 1LL << 30); } while (!is_prime(md));\n\
    \    cerr << md << '\\n';\n    ModIntRuntime::set_mod(md);\n\n    while (M--)\
    \ {\n        int u, v;\n        cin >> u >> v;\n        to[u] |= 1 << v;\n   \
    \     to[v] |= 1 << u;\n    }\n    cout << ChromaticNumber<ModIntRuntime>(to)\
    \ << '\\n';\n}\n"
  dependsOn:
  - graph/chromatic_number.hpp
  - number/factorize.hpp
  - number/modint_runtime.hpp
  - random/rand_nondeterministic.hpp
  isVerificationFile: true
  path: graph/test/chromatic_number.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/chromatic_number.test.cpp
layout: document
redirect_from:
- /verify/graph/test/chromatic_number.test.cpp
- /verify/graph/test/chromatic_number.test.cpp.html
title: graph/test/chromatic_number.test.cpp
---
