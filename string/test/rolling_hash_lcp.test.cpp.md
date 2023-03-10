---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash_1d.hpp
    title: "Rolling hash (one dimensional) \uFF08\u4E00\u6B21\u5143\u30ED\u30FC\u30EA\
      \u30F3\u30B0\u30CF\u30C3\u30B7\u30E5\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/1408
    links:
    - https://yukicoder.me/problems/1408
  bundledCode: "#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\ntemplate <int md> struct ModInt {\n#if __cplusplus >= 201402L\n\
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
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    MDCONST\
    \ ModInt() : val_(0) {}\n    MDCONST ModInt &_setval(lint v) { return val_ = (v\
    \ >= md ? v - md : v), *this; }\n    MDCONST ModInt(lint v) { _setval(v % md +\
    \ md); }\n    MDCONST explicit operator bool() const { return val_ != 0; }\n \
    \   MDCONST ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    MDCONST ModInt operator-(const ModInt &x) const {\n \
    \       return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    MDCONST\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    MDCONST ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    MDCONST ModInt operator-() const { return ModInt()._setval(md - val_); }\n\
    \    MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) {\n        return\
    \ ModInt()._setval(a % md + x.val_);\n    }\n    friend MDCONST ModInt operator-(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md - x.val_ + md);\n\
    \    }\n    friend MDCONST ModInt operator*(lint a, const ModInt &x) {\n     \
    \   return ModInt()._setval(a % md * x.val_ % md);\n    }\n    friend MDCONST\
    \ ModInt operator/(lint a, const ModInt &x) {\n        return ModInt()._setval(a\
    \ % md * x.inv().val() % md);\n    }\n    MDCONST bool operator==(const ModInt\
    \ &x) const { return val_ == x.val_; }\n    MDCONST bool operator!=(const ModInt\
    \ &x) const { return val_ != x.val_; }\n    MDCONST bool operator<(const ModInt\
    \ &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const {\n    \
    \    ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n & 1)\
    \ ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return ans;\n\
    \    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static\
    \ void _precalculation(int N) {\n        int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n    MDCONST\
    \ ModInt inv() const {\n        if (this->val_ < std::min(md >> 1, 1 << 21)) {\n\
    \            if (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n      \
    \      while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \            return invs[this->val_];\n        } else {\n            return this->pow(md\
    \ - 2);\n        }\n    }\n    MDCONST ModInt fac() const {\n        while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n        return facs[this->val_];\n\
    \    }\n    MDCONST ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    MDCONST ModInt doublefac() const {\n        lint k = (this->val_ + 1)\
    \ / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val_\
    \ < r.val_) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n  \
    \  MDCONST ModInt nPr(const ModInt &r) const {\n        return (this->val_ < r.val_)\
    \ ? 0 : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const\
    \ {\n        if (val_ == 0) return 0;\n        if (md == 2) return val_;\n   \
    \     if (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while\
    \ (b.pow((md - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n       \
    \ while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this)\
    \ * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while\
    \ (y != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 2 \"string/rolling_hash_1d.hpp\"\n#include <algorithm>\n#include <chrono>\n\
    #include <random>\n#include <string>\n#include <tuple>\n#line 8 \"string/rolling_hash_1d.hpp\"\
    \n\ntemplate <class T1, class T2> struct PairHash : public std::pair<T1, T2> {\n\
    \    using PH = PairHash<T1, T2>;\n    explicit PairHash(T1 x, T2 y) : std::pair<T1,\
    \ T2>(x, y) {}\n    explicit PairHash(int x) : std::pair<T1, T2>(x, x) {}\n  \
    \  PairHash() : PairHash(0) {}\n    PH operator+(const PH &x) const { return PH(this->first\
    \ + x.first, this->second + x.second); }\n    PH operator-(const PH &x) const\
    \ { return PH(this->first - x.first, this->second - x.second); }\n    PH operator*(const\
    \ PH &x) const { return PH(this->first * x.first, this->second * x.second); }\n\
    \    PH operator+(int x) const { return PH(this->first + x, this->second + x);\
    \ }\n    static PH randgen(bool force_update = false) {\n        static PH b(0);\n\
    \        if (b == PH(0) or force_update) {\n            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \            std::uniform_int_distribution<int> d(1 << 30);\n            b = PH(T1(d(mt)),\
    \ T2(d(mt)));\n        }\n        return b;\n    }\n\n    template <class OStream>\
    \ friend OStream &operator<<(OStream &os, const PH &x) {\n        return os <<\
    \ \"(\" << x.first << \", \" << x.second << \")\";\n    }\n};\n\ntemplate <class\
    \ T1, class T2, class T3> struct TupleHash3 : public std::tuple<T1, T2, T3> {\n\
    \    using TH = TupleHash3<T1, T2, T3>;\n    explicit TupleHash3(T1 x, T2 y, T3\
    \ z) : std::tuple<T1, T2, T3>(x, y, z) {}\n    explicit TupleHash3(int x) : std::tuple<T1,\
    \ T2, T3>(x, x, x) {}\n    TupleHash3() : TupleHash3(0) {}\n\n    inline const\
    \ T1 &v1() const noexcept { return std::get<0>(*this); }\n    inline const T2\
    \ &v2() const noexcept { return std::get<1>(*this); }\n    inline const T3 &v3()\
    \ const noexcept { return std::get<2>(*this); }\n\n    TH operator+(const TH &x)\
    \ const { return TH(v1() + x.v1(), v2() + x.v2(), v3() + x.v3()); }\n    TH operator-(const\
    \ TH &x) const { return TH(v1() - x.v1(), v2() - x.v2(), v3() - x.v3()); }\n \
    \   TH operator*(const TH &x) const { return TH(v1() * x.v1(), v2() * x.v2(),\
    \ v3() * x.v3()); }\n    TH operator+(int x) const { return TH(v1() + x, v2()\
    \ + x, v3() + x); }\n    static TH randgen(bool force_update = false) {\n    \
    \    static TH b(0);\n        if (b == TH(0) or force_update) {\n            std::mt19937\
    \ mt(std::chrono::steady_clock::now().time_since_epoch().count());\n         \
    \   std::uniform_int_distribution<int> d(1 << 30);\n            b = TH(T1(d(mt)),\
    \ T2(d(mt)), T3(d(mt)));\n        }\n        return b;\n    }\n\n    template\
    \ <class OStream> friend OStream &operator<<(OStream &os, const TH &x) {\n   \
    \     return os << \"(\" << x.v1() << \", \" << x.v2() << \", \" << x.v3() <<\
    \ \")\";\n    }\n};\n\n// Rolling Hash (Rabin-Karp), 1dim\ntemplate <typename\
    \ V> struct rolling_hash {\n    int N;\n    const V B;\n    std::vector<V> hash;\
    \         // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]\n    static std::vector<V>\
    \ power; // power[i] = B^i\n    void _extend_powvec() {\n        if (power.size()\
    \ > 1 and power.at(1) != B) power = {V(1)};\n        while (static_cast<int>(power.size())\
    \ <= N) {\n            auto tmp = power.back() * B;\n            power.push_back(tmp);\n\
    \        }\n    }\n    template <typename Int>\n    rolling_hash(const std::vector<Int>\
    \ &s, V b = V::randgen()) : N(s.size()), B(b), hash(N + 1) {\n        for (int\
    \ i = 0; i < N; i++) hash[i + 1] = hash[i] * B + s[i];\n        _extend_powvec();\n\
    \    }\n    rolling_hash(const std::string &s = \"\", V b = V::randgen()) : N(s.size()),\
    \ B(b), hash(N + 1) {\n        for (int i = 0; i < N; i++) hash[i + 1] = hash[i]\
    \ * B + s[i];\n        _extend_powvec();\n    }\n    void addchar(const char &c)\
    \ {\n        V hnew = hash[N] * B + c;\n        N++, hash.emplace_back(hnew);\n\
    \        _extend_powvec();\n    }\n\n    struct Hash {\n        int length;\n\
    \        V val;\n        Hash() : length(0), val(V()) {}\n        Hash(int len,\
    \ const V &v) : length(len), val(v) {}\n\n        bool operator==(const Hash &r)\
    \ const noexcept {\n            return length == r.length and val == r.val;\n\
    \        }\n\n        Hash operator*(const Hash &r) const {\n            return\
    \ Hash(length + r.length, val * power.at(r.length) + r.val);\n        }\n\n  \
    \      template <class OStream> friend OStream &operator<<(OStream &os, const\
    \ Hash &x) {\n            return os << \"(length=\" << x.length << \", val=\"\
    \ << x.val << \")\";\n        }\n    };\n\n    Hash get(int l, int r) const {\
    \ // s[l] * B^(r - l - 1) + ... + s[r - 1]\n        if (l >= r) return Hash();\n\
    \        return Hash(r - l, hash[r] - hash[l] * power[r - l]);\n    }\n\n    int\
    \ lcplen(int l1, int l2) const { return longest_common_prefix(*this, l1, *this,\
    \ l2); }\n};\ntemplate <typename V> std::vector<V> rolling_hash<V>::power{V(1)};\n\
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
    \ == h2 ? lo : hi) = c;\n    }\n    return lo;\n}\n#line 3 \"string/test/rolling_hash_lcp.test.cpp\"\
    \n#include <cassert>\n#line 6 \"string/test/rolling_hash_lcp.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/1408\"\nusing namespace std;\n\nint\
    \ main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N;\n \
    \   cin >> N;\n    using Hash = PairHash<ModInt998244353, ModInt998244353>;\n\
    \    vector<rolling_hash<Hash>> rhs, rhs_rev;\n    for (int i = 0; i < N; i++)\
    \ {\n        string s;\n        cin >> s;\n        rhs.emplace_back(s);\n    \
    \    reverse(s.begin(), s.end());\n        rhs_rev.emplace_back(s);\n    }\n\n\
    \    int M;\n    long long x, d, ret = 0;\n    cin >> M >> x >> d;\n\n    while\
    \ (M--) {\n        int i = x / (N - 1);\n        int j = x % (N - 1);\n      \
    \  if (i <= j) j++;\n        x = (x + d) % (static_cast<long long>(N) * (N - 1));\n\
    \        auto tmp = longest_common_prefix(rhs[i], 0, rhs[j], 0);\n        assert(tmp\
    \ == longest_common_suffix(rhs_rev[i], rhs_rev[i].N, rhs_rev[j], rhs_rev[j].N));\n\
    \        ret += tmp;\n    }\n    cout << ret << '\\n';\n}\n"
  code: "#include \"../../modint.hpp\"\n#include \"../rolling_hash_1d.hpp\"\n#include\
    \ <cassert>\n#include <iostream>\n#include <string>\n#define PROBLEM \"https://yukicoder.me/problems/1408\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N;\n    cin >> N;\n    using Hash = PairHash<ModInt998244353, ModInt998244353>;\n\
    \    vector<rolling_hash<Hash>> rhs, rhs_rev;\n    for (int i = 0; i < N; i++)\
    \ {\n        string s;\n        cin >> s;\n        rhs.emplace_back(s);\n    \
    \    reverse(s.begin(), s.end());\n        rhs_rev.emplace_back(s);\n    }\n\n\
    \    int M;\n    long long x, d, ret = 0;\n    cin >> M >> x >> d;\n\n    while\
    \ (M--) {\n        int i = x / (N - 1);\n        int j = x % (N - 1);\n      \
    \  if (i <= j) j++;\n        x = (x + d) % (static_cast<long long>(N) * (N - 1));\n\
    \        auto tmp = longest_common_prefix(rhs[i], 0, rhs[j], 0);\n        assert(tmp\
    \ == longest_common_suffix(rhs_rev[i], rhs_rev[i].N, rhs_rev[j], rhs_rev[j].N));\n\
    \        ret += tmp;\n    }\n    cout << ret << '\\n';\n}\n"
  dependsOn:
  - modint.hpp
  - string/rolling_hash_1d.hpp
  isVerificationFile: true
  path: string/test/rolling_hash_lcp.test.cpp
  requiredBy: []
  timestamp: '2023-03-10 12:42:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/rolling_hash_lcp.test.cpp
layout: document
redirect_from:
- /verify/string/test/rolling_hash_lcp.test.cpp
- /verify/string/test/rolling_hash_lcp.test.cpp.html
title: string/test/rolling_hash_lcp.test.cpp
---
