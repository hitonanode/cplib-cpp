---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: random/rand_nondeterministic.hpp
    title: random/rand_nondeterministic.hpp
  - icon: ':question:'
    path: random/rolling_hash_1d_general.hpp
    title: random/rolling_hash_1d_general.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
  bundledCode: "#line 1 \"random/test/rolling_hash.test.cpp\"\n#include <iostream>\n\
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
    #line 2 \"random/rand_nondeterministic.hpp\"\n#include <chrono>\n#include <random>\n\
    using namespace std;\n\n// CUT begin\nstruct rand_int_\n{\n    using lint = long\
    \ long;\n    mt19937 mt;\n    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)\n\
    \    lint operator()(lint l, lint r) {\n        uniform_int_distribution<lint>\
    \ d(l, r - 1);\n        return d(mt);\n    }\n} rnd;\n#line 5 \"random/test/rolling_hash.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nint main()\n{\n    DoubleHash b(rnd(1, 1000000), rnd(1,\
    \ 1000000));\n\n    string T, P;\n    cin >> T >> P;\n    rolling_hash<DoubleHash>\
    \ rh_T(T, b),rh_P(P, b);\n\n    for (int l = 0; l < (int)(T.length() - P.length()\
    \ + 1); l++)\n    {\n        if (rh_T.get_hash(l, l + P.length()) == rh_P.get_hash(0,\
    \ P.length()))\n        {\n            cout << l << endl;\n        }\n    }\n\
    }\n"
  code: "#include <iostream>\n#include <string>\n#include \"random/rolling_hash_1d_general.hpp\"\
    \n#include \"random/rand_nondeterministic.hpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nint main()\n{\n    DoubleHash b(rnd(1, 1000000), rnd(1,\
    \ 1000000));\n\n    string T, P;\n    cin >> T >> P;\n    rolling_hash<DoubleHash>\
    \ rh_T(T, b),rh_P(P, b);\n\n    for (int l = 0; l < (int)(T.length() - P.length()\
    \ + 1); l++)\n    {\n        if (rh_T.get_hash(l, l + P.length()) == rh_P.get_hash(0,\
    \ P.length()))\n        {\n            cout << l << endl;\n        }\n    }\n\
    }\n"
  dependsOn:
  - random/rolling_hash_1d_general.hpp
  - random/rand_nondeterministic.hpp
  isVerificationFile: true
  path: random/test/rolling_hash.test.cpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: random/test/rolling_hash.test.cpp
layout: document
redirect_from:
- /verify/random/test/rolling_hash.test.cpp
- /verify/random/test/rolling_hash.test.cpp.html
title: random/test/rolling_hash.test.cpp
---
