---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/rolling_hash.test.cpp
    title: string/test/rolling_hash.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/rolling_hash_w_modint.test.cpp
    title: string/test/rolling_hash_w_modint.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"string/rolling_hash_1d.hpp\"\n#include <chrono>\n#include\
    \ <random>\n#include <string>\n#include <vector>\nusing namespace std;\n\n// CUT\
    \ begin\nstruct DoubleHash : public pair<unsigned, unsigned> {\n    using ull\
    \ = unsigned long long;\n    static pair<unsigned, unsigned> MODs;\n    DoubleHash(pair<unsigned,\
    \ unsigned> x) : pair(x) {}\n    DoubleHash(unsigned x, unsigned y) : pair(x,\
    \ y) {}\n    DoubleHash(unsigned x) : DoubleHash(x, x) {}\n    DoubleHash() :\
    \ DoubleHash(0) {}\n    static inline DoubleHash mod_subtract(pair<unsigned, unsigned>\
    \ x) {\n        if (x.first >= MODs.first) x.first -= MODs.first;\n        if\
    \ (x.second >= MODs.second) x.second -= MODs.second;\n        return x;\n    }\n\
    \    DoubleHash operator+(const DoubleHash &x) const { return mod_subtract({this->first\
    \ + x.first, this->second + x.second}); }\n    DoubleHash operator+(unsigned x)\
    \ const { return mod_subtract({this->first + x, this->second + x}); }\n    DoubleHash\
    \ operator-(const DoubleHash &x) const { return mod_subtract({this->first + MODs.first\
    \ - x.first, this->second + MODs.second - x.second}); }\n    DoubleHash operator*(const\
    \ DoubleHash &x) const { return {unsigned(ull(this->first) * x.first % MODs.first),\
    \ unsigned(ull(this->second) * x.second % MODs.second)}; }\n    DoubleHash operator*(unsigned\
    \ x) const { return {unsigned(ull(this->first) * x % MODs.first), unsigned(ull(this->second)\
    \ * x % MODs.second)}; }\n    static DoubleHash gen_b(bool force_update = false)\
    \ {\n        static DoubleHash b{0, 0};\n        if (b == DoubleHash{0, 0} or\
    \ force_update) {\n            mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());\n\
    \            uniform_int_distribution<unsigned> d(1 << 16, 1 << 29);\n       \
    \     b = {d(mt), d(mt)};\n        }\n        return b;\n    }\n};\npair<unsigned,\
    \ unsigned> DoubleHash::MODs{1000000007, 998244353};\n\n// Rolling Hash (Rabin-Karp),\
    \ 1dim\ntemplate <typename V = DoubleHash> struct rolling_hash {\n    int N;\n\
    \    V B;\n    vector<V> hash;  // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]\n\
    \    vector<V> power; // power[i] = B^i\n    rolling_hash(const string &s = \"\
    \", V b = V::gen_b()) : B(b) {\n        N = s.length();\n        hash.resize(N\
    \ + 1), power.resize(N + 1, 1);\n        for (int i = 0; i < N; i++) {\n     \
    \       power[i + 1] = power[i] * B;\n            hash[i + 1] = hash[i] * B +\
    \ s[i];\n        }\n    }\n    void addchar(const char &c) {\n        V hnew =\
    \ hash[N] * B + c, pnew = power[N] * B;\n        N++, hash.emplace_back(hnew),\
    \ power.emplace_back(pnew);\n    }\n    V get(int l, int r) const { // s[l] *\
    \ B^(r - l - 1) + ... + s[r - 1]\n        return hash[r] - hash[l] * power[r -\
    \ l];\n    }\n};\n"
  code: "#pragma once\n#include <chrono>\n#include <random>\n#include <string>\n#include\
    \ <vector>\nusing namespace std;\n\n// CUT begin\nstruct DoubleHash : public pair<unsigned,\
    \ unsigned> {\n    using ull = unsigned long long;\n    static pair<unsigned,\
    \ unsigned> MODs;\n    DoubleHash(pair<unsigned, unsigned> x) : pair(x) {}\n \
    \   DoubleHash(unsigned x, unsigned y) : pair(x, y) {}\n    DoubleHash(unsigned\
    \ x) : DoubleHash(x, x) {}\n    DoubleHash() : DoubleHash(0) {}\n    static inline\
    \ DoubleHash mod_subtract(pair<unsigned, unsigned> x) {\n        if (x.first >=\
    \ MODs.first) x.first -= MODs.first;\n        if (x.second >= MODs.second) x.second\
    \ -= MODs.second;\n        return x;\n    }\n    DoubleHash operator+(const DoubleHash\
    \ &x) const { return mod_subtract({this->first + x.first, this->second + x.second});\
    \ }\n    DoubleHash operator+(unsigned x) const { return mod_subtract({this->first\
    \ + x, this->second + x}); }\n    DoubleHash operator-(const DoubleHash &x) const\
    \ { return mod_subtract({this->first + MODs.first - x.first, this->second + MODs.second\
    \ - x.second}); }\n    DoubleHash operator*(const DoubleHash &x) const { return\
    \ {unsigned(ull(this->first) * x.first % MODs.first), unsigned(ull(this->second)\
    \ * x.second % MODs.second)}; }\n    DoubleHash operator*(unsigned x) const {\
    \ return {unsigned(ull(this->first) * x % MODs.first), unsigned(ull(this->second)\
    \ * x % MODs.second)}; }\n    static DoubleHash gen_b(bool force_update = false)\
    \ {\n        static DoubleHash b{0, 0};\n        if (b == DoubleHash{0, 0} or\
    \ force_update) {\n            mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());\n\
    \            uniform_int_distribution<unsigned> d(1 << 16, 1 << 29);\n       \
    \     b = {d(mt), d(mt)};\n        }\n        return b;\n    }\n};\npair<unsigned,\
    \ unsigned> DoubleHash::MODs{1000000007, 998244353};\n\n// Rolling Hash (Rabin-Karp),\
    \ 1dim\ntemplate <typename V = DoubleHash> struct rolling_hash {\n    int N;\n\
    \    V B;\n    vector<V> hash;  // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]\n\
    \    vector<V> power; // power[i] = B^i\n    rolling_hash(const string &s = \"\
    \", V b = V::gen_b()) : B(b) {\n        N = s.length();\n        hash.resize(N\
    \ + 1), power.resize(N + 1, 1);\n        for (int i = 0; i < N; i++) {\n     \
    \       power[i + 1] = power[i] * B;\n            hash[i + 1] = hash[i] * B +\
    \ s[i];\n        }\n    }\n    void addchar(const char &c) {\n        V hnew =\
    \ hash[N] * B + c, pnew = power[N] * B;\n        N++, hash.emplace_back(hnew),\
    \ power.emplace_back(pnew);\n    }\n    V get(int l, int r) const { // s[l] *\
    \ B^(r - l - 1) + ... + s[r - 1]\n        return hash[r] - hash[l] * power[r -\
    \ l];\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/rolling_hash_1d.hpp
  requiredBy: []
  timestamp: '2020-12-31 05:31:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/rolling_hash_w_modint.test.cpp
  - string/test/rolling_hash.test.cpp
documentation_of: string/rolling_hash_1d.hpp
layout: document
redirect_from:
- /library/string/rolling_hash_1d.hpp
- /library/string/rolling_hash_1d.hpp.html
title: string/rolling_hash_1d.hpp
---
