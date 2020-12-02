---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: random/test/rolling_hash.test.cpp
    title: random/test/rolling_hash.test.cpp
  - icon: ':x:'
    path: random/test/rolling_hash_w_modint.test.cpp
    title: random/test/rolling_hash_w_modint.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"random/rolling_hash_1d_general.hpp\"\n#include <string>\n\
    #include <vector>\nusing namespace std;\n\n// CUT begin\n// Rolling Hash (Rabin-Karp),\
    \ 1dim\ntemplate <typename V> struct rolling_hash {\n    V B;\n    vector<V> hash;\
    \  // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]\n    vector<V> power; // power[i]\
    \ = B^i\n    rolling_hash() {}\n    rolling_hash(const string &s, V b) : B(b)\
    \ {\n        int N = s.length();\n        hash.resize(N + 1), power.resize(N +\
    \ 1, 1);\n        for (int i = 0; i < N; i++) {\n            power[i + 1] = power[i]\
    \ * B;\n            hash[i + 1] = hash[i] * B + s[i];\n        }\n    }\n    V\
    \ get_hash(int l, int r) // s[l] * B^(r - l - 1) + ... + s[r - 1]\n    {\n   \
    \     return hash[r] - hash[l] * power[r - l];\n    }\n};\n\nusing lint = long\
    \ long;\nusing plint = pair<lint, lint>;\nstruct DoubleHash : public plint {\n\
    \    static plint MODs;\n    DoubleHash(plint x) : plint(x) {}\n    DoubleHash(lint\
    \ x, lint y) : plint(x, y) {}\n    DoubleHash(lint x) : DoubleHash(x, x) {}\n\
    \    DoubleHash() : DoubleHash(0) {}\n    static inline DoubleHash mod_subtract(plint\
    \ x) {\n        if (x.first >= MODs.first) x.first -= MODs.first;\n        if\
    \ (x.second >= MODs.second) x.second -= MODs.second;\n        return x;\n    }\n\
    \    DoubleHash operator+(const DoubleHash &x) const { return mod_subtract(plint(this->first\
    \ + x.first, this->second + x.second)); }\n    DoubleHash operator+(lint x) const\
    \ { return mod_subtract(plint(this->first + x, this->second + x)); }\n    DoubleHash\
    \ operator-(const DoubleHash &x) const { return mod_subtract(plint(this->first\
    \ - x.first + MODs.first, this->second - x.second + MODs.second)); }\n    DoubleHash\
    \ operator*(const DoubleHash &x) const { return make_pair(this->first * x.first\
    \ % MODs.first, this->second * x.second % MODs.second); }\n    DoubleHash operator*(lint\
    \ x) const { return make_pair(this->first * x % MODs.first, this->second * x %\
    \ MODs.second); }\n};\nplint DoubleHash::MODs = plint(1000000007, 998244353);\n"
  code: "#pragma once\n#include <string>\n#include <vector>\nusing namespace std;\n\
    \n// CUT begin\n// Rolling Hash (Rabin-Karp), 1dim\ntemplate <typename V> struct\
    \ rolling_hash {\n    V B;\n    vector<V> hash;  // hash[i] = s[0] * B^(i - 1)\
    \ + ... + s[i - 1]\n    vector<V> power; // power[i] = B^i\n    rolling_hash()\
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
    };\nplint DoubleHash::MODs = plint(1000000007, 998244353);\n"
  dependsOn: []
  isVerificationFile: false
  path: random/rolling_hash_1d_general.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - random/test/rolling_hash.test.cpp
  - random/test/rolling_hash_w_modint.test.cpp
documentation_of: random/rolling_hash_1d_general.hpp
layout: document
redirect_from:
- /library/random/rolling_hash_1d_general.hpp
- /library/random/rolling_hash_1d_general.hpp.html
title: random/rolling_hash_1d_general.hpp
---
