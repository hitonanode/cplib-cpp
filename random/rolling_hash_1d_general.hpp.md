---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: random/test/rolling_hash_w_modint.test.cpp
    title: random/test/rolling_hash_w_modint.test.cpp
  - icon: ':heavy_check_mark:'
    path: random/test/rolling_hash.test.cpp
    title: random/test/rolling_hash.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"random/rolling_hash_1d_general.hpp\"\n#include <string>\n\
    #include <vector>\nusing namespace std;\n\n// CUT begin\n// Rolling Hash (Rabin-Karp),\
    \ 1dim\ntemplate<typename V>\nstruct rolling_hash\n{\n    V B;\n    vector<V>\
    \ hash; // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]\n    vector<V> power; //\
    \ power[i] = B^i\n    rolling_hash() {}\n    rolling_hash(const string &s, V b)\
    \ : B(b)\n    {\n        int N = s.length();\n        hash.resize(N + 1), power.resize(N\
    \ + 1, 1);\n        for (int i = 0; i < N; i++)\n        {\n            power[i\
    \ + 1] = power[i] * B;\n            hash[i + 1] = hash[i] * B + s[i];\n      \
    \  }\n    }\n    V get_hash(int l, int r) // s[l] * B^(r - l - 1) + ... + s[r\
    \ - 1]\n    {\n        return hash[r] - hash[l] * power[r - l];\n    }\n};\n\n\
    using lint = long long;\nusing plint = pair<lint, lint>;\nstruct DoubleHash :\
    \ public plint\n{\n    static plint MODs;\n    DoubleHash(plint x) : plint(x)\
    \ {}\n    DoubleHash(lint x, lint y) : plint(x, y) {}\n    DoubleHash(lint x)\
    \ : DoubleHash(x, x) {}\n    DoubleHash() : DoubleHash(0) {}\n    static inline\
    \ DoubleHash mod_subtract(plint x)\n    {\n        if (x.first >= MODs.first)\
    \ x.first -= MODs.first;\n        if (x.second >= MODs.second) x.second -= MODs.second;\n\
    \        return x;\n    }\n    DoubleHash operator+(const DoubleHash &x) const\n\
    \    {\n        return mod_subtract(plint(this->first + x.first, this->second\
    \ + x.second));\n    }\n    DoubleHash operator+(lint x) const\n    {\n      \
    \  return mod_subtract(plint(this->first + x, this->second + x));\n    }\n   \
    \ DoubleHash operator-(const DoubleHash &x) const\n    {\n        return mod_subtract(plint(this->first\
    \ - x.first + MODs.first, this->second - x.second + MODs.second));\n    }\n  \
    \  DoubleHash operator*(const DoubleHash &x) const\n    {\n        return make_pair(this->first\
    \ * x.first % MODs.first, this->second * x.second % MODs.second);\n    }\n   \
    \ DoubleHash operator*(lint x) const\n    {\n        return make_pair(this->first\
    \ * x % MODs.first, this->second * x % MODs.second);\n    }\n};\nplint DoubleHash::MODs\
    \ = plint(1000000007, 998244353);\n"
  code: "#pragma once\n#include <string>\n#include <vector>\nusing namespace std;\n\
    \n// CUT begin\n// Rolling Hash (Rabin-Karp), 1dim\ntemplate<typename V>\nstruct\
    \ rolling_hash\n{\n    V B;\n    vector<V> hash; // hash[i] = s[0] * B^(i - 1)\
    \ + ... + s[i - 1]\n    vector<V> power; // power[i] = B^i\n    rolling_hash()\
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
    \ * x % MODs.second);\n    }\n};\nplint DoubleHash::MODs = plint(1000000007, 998244353);\n"
  dependsOn: []
  isVerificationFile: false
  path: random/rolling_hash_1d_general.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - random/test/rolling_hash_w_modint.test.cpp
  - random/test/rolling_hash.test.cpp
documentation_of: random/rolling_hash_1d_general.hpp
layout: document
redirect_from:
- /library/random/rolling_hash_1d_general.hpp
- /library/random/rolling_hash_1d_general.hpp.html
title: random/rolling_hash_1d_general.hpp
---
