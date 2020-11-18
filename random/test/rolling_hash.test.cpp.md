---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: random/rand_nondeterministic.hpp
    title: random/rand_nondeterministic.hpp
  - icon: ':x:'
    path: random/rolling_hash_1d_general.hpp
    title: random/rolling_hash_1d_general.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
  bundledCode: "#line 2 \"random/rand_nondeterministic.hpp\"\n#include <chrono>\n\
    #include <random>\nusing namespace std;\n\n// CUT begin\nstruct rand_int_ {\n\
    \    using lint = long long;\n    mt19937 mt;\n    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count())\
    \ {}\n    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)\n\
    \    lint operator()(lint l, lint r) {\n        uniform_int_distribution<lint>\
    \ d(l, r - 1);\n        return d(mt);\n    }\n} rnd;\n#line 2 \"random/rolling_hash_1d_general.hpp\"\
    \n#include <string>\n#include <vector>\nusing namespace std;\n\n// CUT begin\n\
    // Rolling Hash (Rabin-Karp), 1dim\ntemplate <typename V> struct rolling_hash\
    \ {\n    V B;\n    vector<V> hash;  // hash[i] = s[0] * B^(i - 1) + ... + s[i\
    \ - 1]\n    vector<V> power; // power[i] = B^i\n    rolling_hash() {}\n    rolling_hash(const\
    \ string &s, V b) : B(b) {\n        int N = s.length();\n        hash.resize(N\
    \ + 1), power.resize(N + 1, 1);\n        for (int i = 0; i < N; i++) {\n     \
    \       power[i + 1] = power[i] * B;\n            hash[i + 1] = hash[i] * B +\
    \ s[i];\n        }\n    }\n    V get_hash(int l, int r) // s[l] * B^(r - l - 1)\
    \ + ... + s[r - 1]\n    {\n        return hash[r] - hash[l] * power[r - l];\n\
    \    }\n};\n\nusing lint = long long;\nusing plint = pair<lint, lint>;\nstruct\
    \ DoubleHash : public plint {\n    static plint MODs;\n    DoubleHash(plint x)\
    \ : plint(x) {}\n    DoubleHash(lint x, lint y) : plint(x, y) {}\n    DoubleHash(lint\
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
    };\nplint DoubleHash::MODs = plint(1000000007, 998244353);\n#line 3 \"random/test/rolling_hash.test.cpp\"\
    \n#include <iostream>\n#line 5 \"random/test/rolling_hash.test.cpp\"\n#define\
    \ PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nint main() {\n    DoubleHash b(rnd(1, 1000000), rnd(1,\
    \ 1000000));\n\n    string T, P;\n    cin >> T >> P;\n    rolling_hash<DoubleHash>\
    \ rh_T(T, b), rh_P(P, b);\n\n    for (int l = 0; l < (int)(T.length() - P.length()\
    \ + 1); l++) {\n        if (rh_T.get_hash(l, l + P.length()) == rh_P.get_hash(0,\
    \ P.length())) { cout << l << endl; }\n    }\n}\n"
  code: "#include \"random/rand_nondeterministic.hpp\"\n#include \"random/rolling_hash_1d_general.hpp\"\
    \n#include <iostream>\n#include <string>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \nusing namespace std;\n\nint main() {\n    DoubleHash b(rnd(1, 1000000), rnd(1,\
    \ 1000000));\n\n    string T, P;\n    cin >> T >> P;\n    rolling_hash<DoubleHash>\
    \ rh_T(T, b), rh_P(P, b);\n\n    for (int l = 0; l < (int)(T.length() - P.length()\
    \ + 1); l++) {\n        if (rh_T.get_hash(l, l + P.length()) == rh_P.get_hash(0,\
    \ P.length())) { cout << l << endl; }\n    }\n}\n"
  dependsOn:
  - random/rand_nondeterministic.hpp
  - random/rolling_hash_1d_general.hpp
  isVerificationFile: true
  path: random/test/rolling_hash.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: random/test/rolling_hash.test.cpp
layout: document
redirect_from:
- /verify/random/test/rolling_hash.test.cpp
- /verify/random/test/rolling_hash.test.cpp.html
title: random/test/rolling_hash.test.cpp
---
