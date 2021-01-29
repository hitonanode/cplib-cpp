---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/segtree_relevant_points.hpp\"\n#include <algorithm>\n\
    #include <vector>\n\n// CUT begin\n// Enumerate nodes of nonrecursive segtree\
    \ which cover [l, r)\nstd::vector<int> segtree_relevant_points(int N, int l, int\
    \ r) {\n    std::vector<int> ret;\n    l += N, r += N;\n    while (l < r) {\n\
    \        if (l & 1) ret.push_back(l++);\n        if (r & 1) ret.push_back(--r);\n\
    \        l >>= 1, r >>= 1;\n    }\n    std::sort(ret.begin(), ret.end());\n  \
    \  return ret;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <vector>\n\n// CUT begin\n//\
    \ Enumerate nodes of nonrecursive segtree which cover [l, r)\nstd::vector<int>\
    \ segtree_relevant_points(int N, int l, int r) {\n    std::vector<int> ret;\n\
    \    l += N, r += N;\n    while (l < r) {\n        if (l & 1) ret.push_back(l++);\n\
    \        if (r & 1) ret.push_back(--r);\n        l >>= 1, r >>= 1;\n    }\n  \
    \  std::sort(ret.begin(), ret.end());\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/segtree_relevant_points.hpp
  requiredBy: []
  timestamp: '2021-01-12 01:46:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/segtree_relevant_points.hpp
layout: document
redirect_from:
- /library/utilities/segtree_relevant_points.hpp
- /library/utilities/segtree_relevant_points.hpp.html
title: utilities/segtree_relevant_points.hpp
---
