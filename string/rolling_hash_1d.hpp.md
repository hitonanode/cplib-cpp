---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/rolling_hash.test.cpp
    title: string/test/rolling_hash.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/rolling_hash_lcp.test.cpp
    title: string/test/rolling_hash_lcp.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/rolling_hash_mersenne61.test.cpp
    title: string/test/rolling_hash_mersenne61.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/rolling_hash_w_modint.test.cpp
    title: string/test/rolling_hash_w_modint.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/run_enumerate_lyndon_hash.test.cpp
    title: string/test/run_enumerate_lyndon_hash.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/run_enumerate_lyndon_mersenne61.test.cpp
    title: string/test/run_enumerate_lyndon_mersenne61.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/rolling_hash_1d.hpp\"\n#include <algorithm>\n#include\
    \ <chrono>\n#include <random>\n#include <string>\n#include <tuple>\n#include <vector>\n\
    \ntemplate <class T1, class T2> struct PairHash : public std::pair<T1, T2> {\n\
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
    \ T2(d(mt)));\n        }\n        return b;\n    }\n};\n\ntemplate <class T1,\
    \ class T2, class T3> struct TupleHash3 : public std::tuple<T1, T2, T3> {\n  \
    \  using TH = TupleHash3<T1, T2, T3>;\n    explicit TupleHash3(T1 x, T2 y, T3\
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
    \ T2(d(mt)), T3(d(mt)));\n        }\n        return b;\n    }\n};\n\n// Rolling\
    \ Hash (Rabin-Karp), 1dim\ntemplate <typename V> struct rolling_hash {\n    int\
    \ N;\n    const V B;\n    std::vector<V> hash;         // hash[i] = s[0] * B^(i\
    \ - 1) + ... + s[i - 1]\n    static std::vector<V> power; // power[i] = B^i\n\
    \    void _extend_powvec() {\n        if (power.size() > 1 and power.at(1) !=\
    \ B) power = {V(1)};\n        while (static_cast<int>(power.size()) <= N) {\n\
    \            auto tmp = power.back() * B;\n            power.push_back(tmp);\n\
    \        }\n    }\n    template <typename Int>\n    rolling_hash(const std::vector<Int>\
    \ &s, V b = V::randgen()) : N(s.size()), B(b), hash(N + 1) {\n        for (int\
    \ i = 0; i < N; i++) hash[i + 1] = hash[i] * B + s[i];\n        _extend_powvec();\n\
    \    }\n    rolling_hash(const std::string &s = \"\", V b = V::randgen()) : N(s.size()),\
    \ B(b), hash(N + 1) {\n        for (int i = 0; i < N; i++) hash[i + 1] = hash[i]\
    \ * B + s[i];\n        _extend_powvec();\n    }\n    void addchar(const char &c)\
    \ {\n        V hnew = hash[N] * B + c;\n        N++, hash.emplace_back(hnew);\n\
    \        _extend_powvec();\n    }\n    V get(int l, int r) const { // s[l] * B^(r\
    \ - l - 1) + ... + s[r - 1]\n        return hash[r] - hash[l] * power[r - l];\n\
    \    }\n    int lcplen(int l1, int l2) const { return longest_common_prefix(*this,\
    \ l1, *this, l2); }\n};\ntemplate <typename V> std::vector<V> rolling_hash<V>::power{V(1)};\n\
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
    \ == h2 ? lo : hi) = c;\n    }\n    return lo;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <chrono>\n#include <random>\n\
    #include <string>\n#include <tuple>\n#include <vector>\n\ntemplate <class T1,\
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
    \ T2(d(mt)));\n        }\n        return b;\n    }\n};\n\ntemplate <class T1,\
    \ class T2, class T3> struct TupleHash3 : public std::tuple<T1, T2, T3> {\n  \
    \  using TH = TupleHash3<T1, T2, T3>;\n    explicit TupleHash3(T1 x, T2 y, T3\
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
    \ T2(d(mt)), T3(d(mt)));\n        }\n        return b;\n    }\n};\n\n// Rolling\
    \ Hash (Rabin-Karp), 1dim\ntemplate <typename V> struct rolling_hash {\n    int\
    \ N;\n    const V B;\n    std::vector<V> hash;         // hash[i] = s[0] * B^(i\
    \ - 1) + ... + s[i - 1]\n    static std::vector<V> power; // power[i] = B^i\n\
    \    void _extend_powvec() {\n        if (power.size() > 1 and power.at(1) !=\
    \ B) power = {V(1)};\n        while (static_cast<int>(power.size()) <= N) {\n\
    \            auto tmp = power.back() * B;\n            power.push_back(tmp);\n\
    \        }\n    }\n    template <typename Int>\n    rolling_hash(const std::vector<Int>\
    \ &s, V b = V::randgen()) : N(s.size()), B(b), hash(N + 1) {\n        for (int\
    \ i = 0; i < N; i++) hash[i + 1] = hash[i] * B + s[i];\n        _extend_powvec();\n\
    \    }\n    rolling_hash(const std::string &s = \"\", V b = V::randgen()) : N(s.size()),\
    \ B(b), hash(N + 1) {\n        for (int i = 0; i < N; i++) hash[i + 1] = hash[i]\
    \ * B + s[i];\n        _extend_powvec();\n    }\n    void addchar(const char &c)\
    \ {\n        V hnew = hash[N] * B + c;\n        N++, hash.emplace_back(hnew);\n\
    \        _extend_powvec();\n    }\n    V get(int l, int r) const { // s[l] * B^(r\
    \ - l - 1) + ... + s[r - 1]\n        return hash[r] - hash[l] * power[r - l];\n\
    \    }\n    int lcplen(int l1, int l2) const { return longest_common_prefix(*this,\
    \ l1, *this, l2); }\n};\ntemplate <typename V> std::vector<V> rolling_hash<V>::power{V(1)};\n\
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
    \ == h2 ? lo : hi) = c;\n    }\n    return lo;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/rolling_hash_1d.hpp
  requiredBy: []
  timestamp: '2022-10-09 12:55:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/rolling_hash_lcp.test.cpp
  - string/test/rolling_hash_mersenne61.test.cpp
  - string/test/rolling_hash_w_modint.test.cpp
  - string/test/run_enumerate_lyndon_hash.test.cpp
  - string/test/rolling_hash.test.cpp
  - string/test/run_enumerate_lyndon_mersenne61.test.cpp
documentation_of: string/rolling_hash_1d.hpp
layout: document
title: "Rolling hash (one dimensional) \uFF08\u4E00\u6B21\u5143\u30ED\u30FC\u30EA\u30F3\
  \u30B0\u30CF\u30C3\u30B7\u30E5\uFF09"
---

文字列・数列に対する典型的なローリングハッシュ．長さ $N$ の入力に対して時間計算量 $O(N)$ で構築，区間ハッシュ値を $O(1)$ で取得．

算出されるハッシュ値は，コンストラクタでランダムにとった `Hash b` とクエリ $(l, r)$ に対して

$\displaystyle
\mathrm{hash}(l, r) = \sum\_{i=l}^{r - 1} b^{r - 1 - i} s[i]
$

と表される．

## 使用方法

```cpp
using Hash = ModIntMersenne61;

string S = "sakanakanandaka";
rolling_hash<Hash> rh(S)

int l, r;
Hash h = rh.get(l, r);  // S[l:r], 半開区間
```

ハッシュの型 `PairHash` や `TupleHash3` は任意に入れ子にすることも可能で，例えば

```cpp
using Hash = ModIntMersenne61;
using Hash = TupleHash3<ModInt998244353, ModInt998244353, ModInt998244353>;
using PH = PairHash<ModInt998244353, ModInt998244353>;
using Hash = TupleHash3<PH, ModInt998244353, PH>;
using Hash = PairHash<PH, PairHash<ModInt998244353, ModInt998244353>>;
```

は全て動作する．
