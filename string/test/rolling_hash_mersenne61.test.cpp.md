---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/modint_mersenne61.hpp
    title: "$\\mathbb{F}_{2^{61} - 1}$ \uFF08\u30CF\u30C3\u30B7\u30E5\u7528\u30E1\u30EB\
      \u30BB\u30F3\u30CC\u7D20\u6570 modint\uFF09"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
  bundledCode: "#line 2 \"number/modint_mersenne61.hpp\"\n#include <cassert>\n#include\
    \ <chrono>\n#include <random>\n\n// F_p, p = 2^61 - 1\n// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    class ModIntMersenne61 {\n    static const long long md = (1LL << 61) - 1;\n \
    \   long long _v;\n\n    inline unsigned hi() const noexcept { return _v >> 31;\
    \ }\n    inline unsigned lo() const noexcept { return _v & ((1LL << 31) - 1);\
    \ }\n\npublic:\n    static long long mod() { return md; }\n\n    ModIntMersenne61()\
    \ : _v(0) {}\n    // 0 <= x < md * 2\n    explicit ModIntMersenne61(long long\
    \ x) : _v(x >= md ? x - md : x) {}\n\n    long long val() const noexcept { return\
    \ _v; }\n\n    ModIntMersenne61 operator+(const ModIntMersenne61 &x) const {\n\
    \        return ModIntMersenne61(_v + x._v);\n    }\n\n    ModIntMersenne61 operator-(const\
    \ ModIntMersenne61 &x) const {\n        return ModIntMersenne61(_v + md - x._v);\n\
    \    }\n\n    ModIntMersenne61 operator*(const ModIntMersenne61 &x) const {\n\
    \        using ull = unsigned long long;\n\n        ull uu = (ull)hi() * x.hi()\
    \ * 2;\n        ull ll = (ull)lo() * x.lo();\n        ull lu = (ull)hi() * x.lo()\
    \ + (ull)lo() * x.hi();\n\n        ull sum = uu + ll + ((lu & ((1ULL << 30) -\
    \ 1)) << 31) + (lu >> 30);\n        ull reduced = (sum >> 61) + (sum & ull(md));\n\
    \        return ModIntMersenne61(reduced);\n    }\n\n    ModIntMersenne61 pow(long\
    \ long n) const {\n        assert(n >= 0);\n        ModIntMersenne61 ans(1), tmp\
    \ = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n        \
    \    tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n    ModIntMersenne61\
    \ inv() const { return pow(md - 2); }\n\n    ModIntMersenne61 operator/(const\
    \ ModIntMersenne61 &x) const { return *this * x.inv(); }\n\n    ModIntMersenne61\
    \ operator-() const { return ModIntMersenne61(md - _v); }\n    ModIntMersenne61\
    \ &operator+=(const ModIntMersenne61 &x) { return *this = *this + x; }\n    ModIntMersenne61\
    \ &operator-=(const ModIntMersenne61 &x) { return *this = *this - x; }\n    ModIntMersenne61\
    \ &operator*=(const ModIntMersenne61 &x) { return *this = *this * x; }\n    ModIntMersenne61\
    \ &operator/=(const ModIntMersenne61 &x) { return *this = *this / x; }\n\n   \
    \ ModIntMersenne61 operator+(unsigned x) const { return ModIntMersenne61(this->_v\
    \ + x); }\n\n    bool operator==(const ModIntMersenne61 &x) const { return _v\
    \ == x._v; }\n    bool operator!=(const ModIntMersenne61 &x) const { return _v\
    \ != x._v; }\n    bool operator<(const ModIntMersenne61 &x) const { return _v\
    \ < x._v; } // To use std::map\n\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const ModIntMersenne61 &x) {\n        return os <<\
    \ x._v;\n    }\n\n    static ModIntMersenne61 randgen(bool force_update = false)\
    \ {\n        static ModIntMersenne61 b(0);\n        if (b == ModIntMersenne61(0)\
    \ or force_update) {\n            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \            std::uniform_int_distribution<long long> d(1, ModIntMersenne61::mod());\n\
    \            b = ModIntMersenne61(d(mt));\n        }\n        return b;\n    }\n\
    };\n#line 2 \"string/rolling_hash_1d.hpp\"\n#include <algorithm>\n#line 5 \"string/rolling_hash_1d.hpp\"\
    \n#include <string>\n#include <tuple>\n#include <vector>\n\ntemplate <class T1,\
    \ class T2> struct PairHash : public std::pair<T1, T2> {\n    using PH = PairHash<T1,\
    \ T2>;\n    explicit PairHash(T1 x, T2 y) : std::pair<T1, T2>(x, y) {}\n    explicit\
    \ PairHash(int x) : std::pair<T1, T2>(x, x) {}\n    PairHash() : PairHash(0) {}\n\
    \    PH operator+(const PH &x) const { return PH(this->first + x.first, this->second\
    \ + x.second); }\n    PH operator-(const PH &x) const { return PH(this->first\
    \ - x.first, this->second - x.second); }\n    PH operator*(const PH &x) const\
    \ { return PH(this->first * x.first, this->second * x.second); }\n    PH operator+(int\
    \ x) const { return PH(this->first + x, this->second + x); }\n    static PH randgen(bool\
    \ force_update = false) {\n        static PH b(0);\n        if (b == PH(0) or\
    \ force_update) {\n            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
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
    \ == h2 ? lo : hi) = c;\n    }\n    return lo;\n}\n#line 3 \"string/test/rolling_hash_mersenne61.test.cpp\"\
    \n#include <iostream>\n#line 5 \"string/test/rolling_hash_mersenne61.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    string T, P;\n    cin >> T >> P;\n    rolling_hash<ModIntMersenne61> rh_T(T),\
    \ rh_P(P);\n\n    for (int l = 0; l < (int)(T.length() - P.length() + 1); l++)\
    \ {\n        if (rh_T.get(l, l + P.length()) == rh_P.get(0, P.length())) cout\
    \ << l << '\\n';\n    }\n}\n"
  code: "#include \"../../number/modint_mersenne61.hpp\"\n#include \"../rolling_hash_1d.hpp\"\
    \n#include <iostream>\n#include <string>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    string T, P;\n    cin >> T >> P;\n    rolling_hash<ModIntMersenne61> rh_T(T),\
    \ rh_P(P);\n\n    for (int l = 0; l < (int)(T.length() - P.length() + 1); l++)\
    \ {\n        if (rh_T.get(l, l + P.length()) == rh_P.get(0, P.length())) cout\
    \ << l << '\\n';\n    }\n}\n"
  dependsOn:
  - number/modint_mersenne61.hpp
  - string/rolling_hash_1d.hpp
  isVerificationFile: true
  path: string/test/rolling_hash_mersenne61.test.cpp
  requiredBy: []
  timestamp: '2023-03-10 12:42:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: string/test/rolling_hash_mersenne61.test.cpp
layout: document
redirect_from:
- /verify/string/test/rolling_hash_mersenne61.test.cpp
- /verify/string/test/rolling_hash_mersenne61.test.cpp.html
title: string/test/rolling_hash_mersenne61.test.cpp
---
