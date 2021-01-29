---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/bellman_ford.test.cpp
    title: graph/test/bellman_ford.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"graph/bellman_ford.hpp\"\n#include <utility>\n#include <vector>\n\
    using namespace std;\n\n// CUT begin\nusing wedges = vector<vector<pair<long long,\
    \ long long>>>; // (to, weight)\nconstexpr long long INF = 1e17;\nvector<long\
    \ long> bellman_ford(int s, const wedges &w, int T) {\n    int N = w.size();\n\
    \    vector<long long> d(N, INF);\n    d[s] = 0;\n    for (int l = 0; l < T; l++)\
    \ {\n        bool upd = false;\n        for (int i = 0; i < N; i++) {\n      \
    \      if (d[i] >= INF) continue;\n            for (auto pa : w[i]) {\n      \
    \          if (d[pa.first] > d[i] + pa.second) {\n                    d[pa.first]\
    \ = d[i] + pa.second;\n                    upd = true;\n                }\n  \
    \          }\n        }\n        if (!upd) break;\n    }\n    return d;\n}\n"
  code: "#pragma once\n#include <utility>\n#include <vector>\nusing namespace std;\n\
    \n// CUT begin\nusing wedges = vector<vector<pair<long long, long long>>>; //\
    \ (to, weight)\nconstexpr long long INF = 1e17;\nvector<long long> bellman_ford(int\
    \ s, const wedges &w, int T) {\n    int N = w.size();\n    vector<long long> d(N,\
    \ INF);\n    d[s] = 0;\n    for (int l = 0; l < T; l++) {\n        bool upd =\
    \ false;\n        for (int i = 0; i < N; i++) {\n            if (d[i] >= INF)\
    \ continue;\n            for (auto pa : w[i]) {\n                if (d[pa.first]\
    \ > d[i] + pa.second) {\n                    d[pa.first] = d[i] + pa.second;\n\
    \                    upd = true;\n                }\n            }\n        }\n\
    \        if (!upd) break;\n    }\n    return d;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/bellman_ford.hpp
  requiredBy: []
  timestamp: '2020-11-21 18:08:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/bellman_ford.test.cpp
documentation_of: graph/bellman_ford.hpp
layout: document
redirect_from:
- /library/graph/bellman_ford.hpp
- /library/graph/bellman_ford.hpp.html
title: graph/bellman_ford.hpp
---
