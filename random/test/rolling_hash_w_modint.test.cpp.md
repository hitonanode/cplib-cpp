---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: random/rolling_hash_1d_general.hpp
    title: random/rolling_hash_1d_general.hpp
  - icon: ':heavy_check_mark:'
    path: random/xorshift.hpp
    title: random/xorshift.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
  bundledCode: "#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\n// CUT begin\ntemplate <int mod> struct ModInt {\n#if __cplusplus\
    \ >= 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using\
    \ lint = long long;\n    MDCONST static int get_mod() { return mod; }\n    static\
    \ int get_primitive_root() {\n        static int primitive_root = 0;\n       \
    \ if (!primitive_root) {\n            primitive_root = [&]() {\n             \
    \   std::set<int> fac;\n                int v = mod - 1;\n                for\
    \ (lint i = 2; i * i <= v; i++)\n                    while (v % i == 0) fac.insert(i),\
    \ v /= i;\n                if (v > 1) fac.insert(v);\n                for (int\
    \ g = 1; g < mod; g++) {\n                    bool ok = true;\n              \
    \      for (auto i : fac)\n                        if (ModInt(g).pow((mod - 1)\
    \ / i) == 1) {\n                            ok = false;\n                    \
    \        break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root;\n    }\n    int val;\n    MDCONST ModInt()\
    \ : val(0) {}\n    MDCONST ModInt &_setval(lint v) { return val = (v >= mod ?\
    \ v - mod : v), *this; }\n    MDCONST ModInt(lint v) { _setval(v % mod + mod);\
    \ }\n    MDCONST explicit operator bool() const { return val != 0; }\n    MDCONST\
    \ ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ + x.val); }\n    MDCONST ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
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
    \ mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"random/rolling_hash_1d_general.hpp\"\
    \n#include <string>\n#line 4 \"random/rolling_hash_1d_general.hpp\"\nusing namespace\
    \ std;\n\n// CUT begin\n// Rolling Hash (Rabin-Karp), 1dim\ntemplate <typename\
    \ V> struct rolling_hash {\n    V B;\n    vector<V> hash;  // hash[i] = s[0] *\
    \ B^(i - 1) + ... + s[i - 1]\n    vector<V> power; // power[i] = B^i\n    rolling_hash()\
    \ {}\n    rolling_hash(const string &s, V b) : B(b) {\n        int N = s.length();\n\
    \        hash.resize(N + 1), power.resize(N + 1, 1);\n        for (int i = 0;\
    \ i < N; i++) {\n            power[i + 1] = power[i] * B;\n            hash[i\
    \ + 1] = hash[i] * B + s[i];\n        }\n    }\n    V get_hash(int l, int r) //\
    \ s[l] * B^(r - l - 1) + ... + s[r - 1]\n    {\n        return hash[r] - hash[l]\
    \ * power[r - l];\n    }\n};\n\nusing lint = long long;\nusing plint = pair<lint,\
    \ lint>;\nstruct DoubleHash : public plint {\n    static plint MODs;\n    DoubleHash(plint\
    \ x) : plint(x) {}\n    DoubleHash(lint x, lint y) : plint(x, y) {}\n    DoubleHash(lint\
    \ x) : DoubleHash(x, x) {}\n    DoubleHash() : DoubleHash(0) {}\n    static inline\
    \ DoubleHash mod_subtract(plint x) {\n        if (x.first >= MODs.first) x.first\
    \ -= MODs.first;\n        if (x.second >= MODs.second) x.second -= MODs.second;\n\
    \        return x;\n    }\n    DoubleHash operator+(const DoubleHash &x) const\
    \ { return mod_subtract(plint(this->first + x.first, this->second + x.second));\
    \ }\n    DoubleHash operator+(lint x) const { return mod_subtract(plint(this->first\
    \ + x, this->second + x)); }\n    DoubleHash operator-(const DoubleHash &x) const\
    \ { return mod_subtract(plint(this->first - x.first + MODs.first, this->second\
    \ - x.second + MODs.second)); }\n    DoubleHash operator*(const DoubleHash &x)\
    \ const { return make_pair(this->first * x.first % MODs.first, this->second *\
    \ x.second % MODs.second); }\n    DoubleHash operator*(lint x) const { return\
    \ make_pair(this->first * x % MODs.first, this->second * x % MODs.second); }\n\
    };\nplint DoubleHash::MODs = plint(1000000007, 998244353);\n#line 2 \"random/xorshift.hpp\"\
    \n#include <cstdint>\n\n// CUT begin\nuint32_t rand_int() // XorShift random integer\
    \ generator\n{\n    static uint32_t x = 123456789, y = 362436069, z = 521288629,\
    \ w = 88675123;\n    uint32_t t = x ^ (x << 11);\n    x = y;\n    y = z;\n   \
    \ z = w;\n    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n}\ndouble rand_double()\
    \ { return (double)rand_int() / UINT32_MAX; }\n#line 6 \"random/test/rolling_hash_w_modint.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nusing mint = ModInt<998244353>;\nint main() {\n    mint\
    \ b1(rand_int() % 1000000 + 1), b2(rand_int() % 1000000 + 1);\n\n    string T,\
    \ P;\n    cin >> T >> P;\n    rolling_hash<mint> rh_T1(T, b1), rh_P1(P, b1);\n\
    \    rolling_hash<mint> rh_T2(T, b2), rh_P2(P, b2);\n\n    for (int l = 0; l <\
    \ (int)(T.length() - P.length() + 1); l++) {\n        if (rh_T1.get_hash(l, l\
    \ + P.length()) == rh_P1.get_hash(0, P.length()) and rh_T2.get_hash(l, l + P.length())\
    \ == rh_P2.get_hash(0, P.length())) { cout << l << endl; }\n    }\n}\n"
  code: "#include \"modint.hpp\"\n#include \"random/rolling_hash_1d_general.hpp\"\n\
    #include \"random/xorshift.hpp\"\n#include <iostream>\n#include <string>\n#define\
    \ PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nusing mint = ModInt<998244353>;\nint main() {\n    mint\
    \ b1(rand_int() % 1000000 + 1), b2(rand_int() % 1000000 + 1);\n\n    string T,\
    \ P;\n    cin >> T >> P;\n    rolling_hash<mint> rh_T1(T, b1), rh_P1(P, b1);\n\
    \    rolling_hash<mint> rh_T2(T, b2), rh_P2(P, b2);\n\n    for (int l = 0; l <\
    \ (int)(T.length() - P.length() + 1); l++) {\n        if (rh_T1.get_hash(l, l\
    \ + P.length()) == rh_P1.get_hash(0, P.length()) and rh_T2.get_hash(l, l + P.length())\
    \ == rh_P2.get_hash(0, P.length())) { cout << l << endl; }\n    }\n}\n"
  dependsOn:
  - modint.hpp
  - random/rolling_hash_1d_general.hpp
  - random/xorshift.hpp
  isVerificationFile: true
  path: random/test/rolling_hash_w_modint.test.cpp
  requiredBy: []
  timestamp: '2020-12-02 23:44:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: random/test/rolling_hash_w_modint.test.cpp
layout: document
redirect_from:
- /verify/random/test/rolling_hash_w_modint.test.cpp
- /verify/random/test/rolling_hash_w_modint.test.cpp.html
title: random/test/rolling_hash_w_modint.test.cpp
---
