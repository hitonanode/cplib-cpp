---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash_1d.hpp
    title: string/rolling_hash_1d.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
  bundledCode: "#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus\
    \ >= 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using\
    \ lint = long long;\n    MDCONST static int mod() { return md; }\n    static int\
    \ get_primitive_root() {\n        static int primitive_root = 0;\n        if (!primitive_root)\
    \ {\n            primitive_root = [&]() {\n                std::set<int> fac;\n\
    \                int v = md - 1;\n                for (lint i = 2; i * i <= v;\
    \ i++)\n                    while (v % i == 0) fac.insert(i), v /= i;\n      \
    \          if (v > 1) fac.insert(v);\n                for (int g = 1; g < md;\
    \ g++) {\n                    bool ok = true;\n                    for (auto i\
    \ : fac)\n                        if (ModInt(g).pow((md - 1) / i) == 1) {\n  \
    \                          ok = false;\n                            break;\n \
    \                       }\n                    if (ok) return g;\n           \
    \     }\n                return -1;\n            }();\n        }\n        return\
    \ primitive_root;\n    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n   \
    \ MDCONST ModInt &_setval(lint v) { return val = (v >= md ? v - md : v), *this;\
    \ }\n    MDCONST ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit\
    \ operator bool() const { return val != 0; }\n    MDCONST ModInt operator+(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val + x.val); }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val\
    \ - x.val + md);\n    }\n    MDCONST ModInt operator*(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val * x.val % md);\n    }\n    MDCONST\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val\
    \ * x.inv() % md);\n    }\n    MDCONST ModInt operator-() const { return ModInt()._setval(md\
    \ - val); }\n    MDCONST ModInt &operator+=(const ModInt &x) { return *this =\
    \ *this + x; }\n    MDCONST ModInt &operator-=(const ModInt &x) { return *this\
    \ = *this - x; }\n    MDCONST ModInt &operator*=(const ModInt &x) { return *this\
    \ = *this * x; }\n    MDCONST ModInt &operator/=(const ModInt &x) { return *this\
    \ = *this / x; }\n    friend MDCONST ModInt operator+(lint a, const ModInt &x)\
    \ {\n        return ModInt()._setval(a % md + x.val);\n    }\n    friend MDCONST\
    \ ModInt operator-(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md - x.val + md);\n    }\n    friend MDCONST ModInt operator*(lint a, const\
    \ ModInt &x) {\n        return ModInt()._setval(a % md * x.val % md);\n    }\n\
    \    friend MDCONST ModInt operator/(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md * x.inv() % md);\n    }\n    MDCONST bool operator==(const\
    \ ModInt &x) const { return val == x.val; }\n    MDCONST bool operator!=(const\
    \ ModInt &x) const { return val != x.val; }\n    MDCONST bool operator<(const\
    \ ModInt &x) const {\n        return val < x.val;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val;\n    }\n    MDCONST ModInt pow(lint n) const {\n     \
    \   ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n & 1)\
    \ ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return ans;\n\
    \    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n    MDCONST\
    \ lint inv() const {\n        if (this->val < std::min(md >> 1, 1 << 21)) {\n\
    \            while (this->val >= int(facs.size())) _precalculation(facs.size()\
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
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 2 \"string/rolling_hash_1d.hpp\"\
    \n#include <algorithm>\n#include <chrono>\n#include <random>\n#include <string>\n\
    #line 7 \"string/rolling_hash_1d.hpp\"\n\n// CUT begin\nstruct DoubleHash : public\
    \ std::pair<unsigned, unsigned> {\n    using ull = unsigned long long;\n    using\
    \ pair = std::pair<unsigned, unsigned>;\n    static std::pair<unsigned, unsigned>\
    \ MODs;\n    DoubleHash(std::pair<unsigned, unsigned> x) : pair(x) {}\n    DoubleHash(unsigned\
    \ x, unsigned y) : pair(x, y) {}\n    DoubleHash(unsigned x) : DoubleHash(x, x)\
    \ {}\n    DoubleHash() : DoubleHash(0) {}\n    static inline DoubleHash mod_subtract(pair\
    \ x) {\n        if (x.first >= MODs.first) x.first -= MODs.first;\n        if\
    \ (x.second >= MODs.second) x.second -= MODs.second;\n        return x;\n    }\n\
    \    DoubleHash operator+(const DoubleHash &x) const {\n        return mod_subtract({this->first\
    \ + x.first, this->second + x.second});\n    }\n    DoubleHash operator+(unsigned\
    \ x) const {\n        return mod_subtract({this->first + x, this->second + x});\n\
    \    }\n    DoubleHash operator-(const DoubleHash &x) const {\n        return\
    \ mod_subtract(\n            {this->first + MODs.first - x.first, this->second\
    \ + MODs.second - x.second});\n    }\n    DoubleHash operator*(const DoubleHash\
    \ &x) const {\n        return {unsigned(ull(this->first) * x.first % MODs.first),\n\
    \                unsigned(ull(this->second) * x.second % MODs.second)};\n    }\n\
    \    DoubleHash operator*(unsigned x) const {\n        return {unsigned(ull(this->first)\
    \ * x % MODs.first),\n                unsigned(ull(this->second) * x % MODs.second)};\n\
    \    }\n    static DoubleHash gen_b(bool force_update = false) {\n        static\
    \ DoubleHash b{0, 0};\n        if (b == DoubleHash{0, 0} or force_update) {\n\
    \            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \            std::uniform_int_distribution<unsigned> d(1 << 16, 1 << 29);\n  \
    \          b = {d(mt), d(mt)};\n        }\n        return b;\n    }\n};\nstd::pair<unsigned,\
    \ unsigned> DoubleHash::MODs{1000000007, 998244353};\n\n// Rolling Hash (Rabin-Karp),\
    \ 1dim\ntemplate <typename V = DoubleHash> struct rolling_hash {\n    int N;\n\
    \    const V B;\n    std::vector<V> hash;         // hash[i] = s[0] * B^(i - 1)\
    \ + ... + s[i - 1]\n    static std::vector<V> power; // power[i] = B^i\n    void\
    \ _extend_powvec() {\n        while (static_cast<int>(power.size()) <= N) {\n\
    \            auto tmp = power.back() * B;\n            power.push_back(tmp);\n\
    \        }\n    }\n    template <typename Int>\n    rolling_hash(const std::vector<Int>\
    \ &s, V b = V::gen_b()) : N(s.size()), B(b), hash(N + 1) {\n        for (int i\
    \ = 0; i < N; i++) hash[i + 1] = hash[i] * B + s[i];\n        _extend_powvec();\n\
    \    }\n    rolling_hash(const std::string &s = \"\", V b = V::gen_b()) : N(s.size()),\
    \ B(b), hash(N + 1) {\n        for (int i = 0; i < N; i++) hash[i + 1] = hash[i]\
    \ * B + s[i];\n        _extend_powvec();\n    }\n    void addchar(const char &c)\
    \ {\n        V hnew = hash[N] * B + c;\n        N++, hash.emplace_back(hnew);\n\
    \        _extend_powvec();\n    }\n    V get(int l, int r) const { // s[l] * B^(r\
    \ - l - 1) + ... + s[r - 1]\n        return hash[r] - hash[l] * power[r - l];\n\
    \    }\n    int lcplen(int l1, int l2) const { return longest_common_prefix(*this,\
    \ l1, *this, l2); }\n};\ntemplate <typename V> std::vector<V> rolling_hash<V>::power{1};\n\
    \n// Longest common prerfix between s1[l1, N1) and s2[l2, N2)\ntemplate <typename\
    \ T>\nint longest_common_prefix(const rolling_hash<T> &rh1, int l1, const rolling_hash<T>\
    \ &rh2, int l2) {\n    int lo = 0, hi = std::min(rh1.N + 1 - l1, rh2.N + 1 - l2);\n\
    \    while (hi - lo > 1) {\n        const int c = (lo + hi) / 2;\n        auto\
    \ h1 = rh1.get(l1, l1 + c), h2 = rh2.get(l2, l2 + c);\n        (h1 == h2 ? lo\
    \ : hi) = c;\n    }\n    return lo;\n}\n// Longest common suffix between s1[0,\
    \ r1) and s2[0, r2)\ntemplate <typename T>\nint longest_common_suffix(const rolling_hash<T>\
    \ &rh1, int r1, const rolling_hash<T> &rh2, int r2) {\n    int lo = 0, hi = std::min(r1,\
    \ r2) + 1;\n    while (hi - lo > 1) {\n        const int c = (lo + hi) / 2;\n\
    \        auto h1 = rh1.get(r1 - c, r1), h2 = rh2.get(r2 - c, r2);\n        (h1\
    \ == h2 ? lo : hi) = c;\n    }\n    return lo;\n}\n#line 5 \"string/test/rolling_hash_w_modint.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nusing mint1 = ModInt<998244353>;\nusing mint2 = ModInt<1000000007>;\n\
    int main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    mint1\
    \ b1 = 51152368;\n    mint2 b2 = 1537689;\n\n    string T, P;\n    cin >> T >>\
    \ P;\n    rolling_hash<mint1> rh_T1(T, b1), rh_P1(P, b1);\n    rolling_hash<mint2>\
    \ rh_T2(T, b2), rh_P2(P, b2);\n\n    for (int l = 0; l < (int)(T.length() - P.length()\
    \ + 1); l++) {\n        if (rh_T1.get(l, l + P.length()) == rh_P1.get(0, P.length())\
    \ and\n            rh_T2.get(l, l + P.length()) == rh_P2.get(0, P.length())) {\n\
    \            cout << l << '\\n';\n        }\n    }\n}\n"
  code: "#include \"../../modint.hpp\"\n#include \"../rolling_hash_1d.hpp\"\n#include\
    \ <iostream>\n#include <string>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nusing mint1 = ModInt<998244353>;\nusing mint2 = ModInt<1000000007>;\n\
    int main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    mint1\
    \ b1 = 51152368;\n    mint2 b2 = 1537689;\n\n    string T, P;\n    cin >> T >>\
    \ P;\n    rolling_hash<mint1> rh_T1(T, b1), rh_P1(P, b1);\n    rolling_hash<mint2>\
    \ rh_T2(T, b2), rh_P2(P, b2);\n\n    for (int l = 0; l < (int)(T.length() - P.length()\
    \ + 1); l++) {\n        if (rh_T1.get(l, l + P.length()) == rh_P1.get(0, P.length())\
    \ and\n            rh_T2.get(l, l + P.length()) == rh_P2.get(0, P.length())) {\n\
    \            cout << l << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - modint.hpp
  - string/rolling_hash_1d.hpp
  isVerificationFile: true
  path: string/test/rolling_hash_w_modint.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/rolling_hash_w_modint.test.cpp
layout: document
redirect_from:
- /verify/string/test/rolling_hash_w_modint.test.cpp
- /verify/string/test/rolling_hash_w_modint.test.cpp.html
title: string/test/rolling_hash_w_modint.test.cpp
---
