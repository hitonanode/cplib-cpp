---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':question:'
    path: random/rolling_hash_1d_general.hpp
    title: random/rolling_hash_1d_general.hpp
  - icon: ':x:'
    path: random/xorshift.hpp
    title: random/xorshift.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
  bundledCode: "#line 1 \"random/test/rolling_hash_w_modint.test.cpp\"\n#include <iostream>\n\
    #include <string>\n#line 3 \"random/rolling_hash_1d_general.hpp\"\n#include <vector>\n\
    using namespace std;\n\n// CUT begin\n// Rolling Hash (Rabin-Karp), 1dim\ntemplate<typename\
    \ V>\nstruct rolling_hash\n{\n    V B;\n    vector<V> hash; // hash[i] = s[0]\
    \ * B^(i - 1) + ... + s[i - 1]\n    vector<V> power; // power[i] = B^i\n    rolling_hash()\
    \ {}\n    rolling_hash(const string &s, V b) : B(b)\n    {\n        int N = s.length();\n\
    \        hash.resize(N + 1), power.resize(N + 1, 1);\n        for (int i = 0;\
    \ i < N; i++)\n        {\n            power[i + 1] = power[i] * B;\n         \
    \   hash[i + 1] = hash[i] * B + s[i];\n        }\n    }\n    V get_hash(int l,\
    \ int r) // s[l] * B^(r - l - 1) + ... + s[r - 1]\n    {\n        return hash[r]\
    \ - hash[l] * power[r - l];\n    }\n};\n\nusing lint = long long;\nusing plint\
    \ = pair<lint, lint>;\nstruct DoubleHash : public plint\n{\n    static plint MODs;\n\
    \    DoubleHash(plint x) : plint(x) {}\n    DoubleHash(lint x, lint y) : plint(x,\
    \ y) {}\n    DoubleHash(lint x) : DoubleHash(x, x) {}\n    DoubleHash() : DoubleHash(0)\
    \ {}\n    static inline DoubleHash mod_subtract(plint x)\n    {\n        if (x.first\
    \ >= MODs.first) x.first -= MODs.first;\n        if (x.second >= MODs.second)\
    \ x.second -= MODs.second;\n        return x;\n    }\n    DoubleHash operator+(const\
    \ DoubleHash &x) const\n    {\n        return mod_subtract(plint(this->first +\
    \ x.first, this->second + x.second));\n    }\n    DoubleHash operator+(lint x)\
    \ const\n    {\n        return mod_subtract(plint(this->first + x, this->second\
    \ + x));\n    }\n    DoubleHash operator-(const DoubleHash &x) const\n    {\n\
    \        return mod_subtract(plint(this->first - x.first + MODs.first, this->second\
    \ - x.second + MODs.second));\n    }\n    DoubleHash operator*(const DoubleHash\
    \ &x) const\n    {\n        return make_pair(this->first * x.first % MODs.first,\
    \ this->second * x.second % MODs.second);\n    }\n    DoubleHash operator*(lint\
    \ x) const\n    {\n        return make_pair(this->first * x % MODs.first, this->second\
    \ * x % MODs.second);\n    }\n};\nplint DoubleHash::MODs = plint(1000000007, 998244353);\n\
    #line 4 \"modint.hpp\"\n#include <set>\n\n// CUT begin\ntemplate <int mod>\nstruct\
    \ ModInt\n{\n    using lint = long long;\n    static int get_mod() { return mod;\
    \ }\n    static int get_primitive_root() {\n        static int primitive_root\
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
    \    }\n    constexpr ModInt pow(lint n) const {\n        return power(n);\n \
    \   }\n    constexpr lint inv() const { return this->power(mod - 2); }\n    constexpr\
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
    \ lint MOD = 998244353;\n// using mint = ModInt<MOD>;\n#line 2 \"random/xorshift.hpp\"\
    \n#include <cstdint>\n\n// CUT begin\nuint32_t rand_int() // XorShift random integer\
    \ generator\n{\n    static uint32_t x = 123456789, y = 362436069, z = 521288629,\
    \ w = 88675123;\n    uint32_t t = x ^ (x << 11);\n    x = y;\n    y = z;\n   \
    \ z = w;\n    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n}\ndouble rand_double()\
    \ { return (double)rand_int() / UINT32_MAX; }\n#line 6 \"random/test/rolling_hash_w_modint.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nusing mint = ModInt<998244353>;\nint main()\n{\n   \
    \ mint b1(rand_int() % 1000000 + 1), b2(rand_int() % 1000000 + 1);\n\n    string\
    \ T, P;\n    cin >> T >> P;\n    rolling_hash<mint> rh_T1(T, b1),rh_P1(P, b1);\n\
    \    rolling_hash<mint> rh_T2(T, b2),rh_P2(P, b2);\n\n    for (int l = 0; l <\
    \ (int)(T.length() - P.length() + 1); l++)\n    {\n        if (rh_T1.get_hash(l,\
    \ l + P.length()) == rh_P1.get_hash(0, P.length())\n            and rh_T2.get_hash(l,\
    \ l + P.length()) == rh_P2.get_hash(0, P.length()))\n        {\n            cout\
    \ << l << endl;\n        }\n    }\n}\n"
  code: "#include <iostream>\n#include <string>\n#include \"random/rolling_hash_1d_general.hpp\"\
    \n#include \"modint.hpp\"\n#include \"random/xorshift.hpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\nusing namespace\
    \ std;\n\nusing mint = ModInt<998244353>;\nint main()\n{\n    mint b1(rand_int()\
    \ % 1000000 + 1), b2(rand_int() % 1000000 + 1);\n\n    string T, P;\n    cin >>\
    \ T >> P;\n    rolling_hash<mint> rh_T1(T, b1),rh_P1(P, b1);\n    rolling_hash<mint>\
    \ rh_T2(T, b2),rh_P2(P, b2);\n\n    for (int l = 0; l < (int)(T.length() - P.length()\
    \ + 1); l++)\n    {\n        if (rh_T1.get_hash(l, l + P.length()) == rh_P1.get_hash(0,\
    \ P.length())\n            and rh_T2.get_hash(l, l + P.length()) == rh_P2.get_hash(0,\
    \ P.length()))\n        {\n            cout << l << endl;\n        }\n    }\n\
    }\n"
  dependsOn:
  - random/rolling_hash_1d_general.hpp
  - modint.hpp
  - random/xorshift.hpp
  isVerificationFile: true
  path: random/test/rolling_hash_w_modint.test.cpp
  requiredBy: []
  timestamp: '2020-11-15 01:21:08+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: random/test/rolling_hash_w_modint.test.cpp
layout: document
redirect_from:
- /verify/random/test/rolling_hash_w_modint.test.cpp
- /verify/random/test/rolling_hash_w_modint.test.cpp.html
title: random/test/rolling_hash_w_modint.test.cpp
---
