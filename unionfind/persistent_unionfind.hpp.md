---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 2 \"unionfind/persistent_unionfind.hpp\"\n#include <map>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\nstruct PersistentUnionFind\n{\n\
    \    std::vector<int> parsz, t_unite;\n    std::vector<std::map<int, int>> size_history;\n\
    \    PersistentUnionFind(int N) : parsz(N, 1), t_unite(N, 2000000000), size_history(N)\
    \ {\n        for (int i = 0; i < N; i++) size_history[i][-1] = 1;\n    }\n   \
    \ int find(int x, int t) { return (t_unite[x] > t) ? x : find(parsz[x], t); }\
    \ // \u6642\u523Bt\u4EE5\u4E0B\u306E\u30DE\u30FC\u30B8\u64CD\u4F5C\u306B\u3088\
    \u3063\u3066\u5B9A\u307E\u308B\u89AA\n    void unite(int x, int y, int t) {\n\
    \        if ((x = find(x, t)) == (y = find(y, t))) return;\n        if (parsz[x]\
    \ < parsz[y]) std::swap(x, y);\n        parsz[x] += parsz[y], parsz[y] = x, t_unite[y]\
    \ = t;\n        size_history[x][t] = parsz[x];\n    }\n    int size(int x, int\
    \ t) { return prev(size_history[find(x, t)].upper_bound(t))->second; }\n    bool\
    \ same(int x, int y, int t) { return find(x, t) == find(y, t); }\n};\n"
  code: "#pragma once\n#include <map>\n#include <utility>\n#include <vector>\n\n//\
    \ CUT begin\nstruct PersistentUnionFind\n{\n    std::vector<int> parsz, t_unite;\n\
    \    std::vector<std::map<int, int>> size_history;\n    PersistentUnionFind(int\
    \ N) : parsz(N, 1), t_unite(N, 2000000000), size_history(N) {\n        for (int\
    \ i = 0; i < N; i++) size_history[i][-1] = 1;\n    }\n    int find(int x, int\
    \ t) { return (t_unite[x] > t) ? x : find(parsz[x], t); } // \u6642\u523Bt\u4EE5\
    \u4E0B\u306E\u30DE\u30FC\u30B8\u64CD\u4F5C\u306B\u3088\u3063\u3066\u5B9A\u307E\
    \u308B\u89AA\n    void unite(int x, int y, int t) {\n        if ((x = find(x,\
    \ t)) == (y = find(y, t))) return;\n        if (parsz[x] < parsz[y]) std::swap(x,\
    \ y);\n        parsz[x] += parsz[y], parsz[y] = x, t_unite[y] = t;\n        size_history[x][t]\
    \ = parsz[x];\n    }\n    int size(int x, int t) { return prev(size_history[find(x,\
    \ t)].upper_bound(t))->second; }\n    bool same(int x, int y, int t) { return\
    \ find(x, t) == find(y, t); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: unionfind/persistent_unionfind.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: unionfind/persistent_unionfind.hpp
layout: document
redirect_from:
- /library/unionfind/persistent_unionfind.hpp
- /library/unionfind/persistent_unionfind.hpp.html
title: unionfind/persistent_unionfind.hpp
---
