---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: segmenttree/test/point-update-range-min.test.cpp
    title: segmenttree/test/point-update-range-min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"segmenttree/range_minimum_query.hpp\"\n#include <iostream>\n\
    #include <vector>\nusing namespace std;\n\n// CUT begin\nusing T = int;\nstruct\
    \ RangeMinimumQuery {\n    int N;\n    T defaultT = 1e9;\n    int head;\n    vector<T>\
    \ x;\n    T _get(int begin, int end, int pos, int l, int r) const {\n        if\
    \ (r <= begin or l >= end) return defaultT;\n        if (l >= begin and r <= end)\
    \ return x[pos];\n        return min(_get(begin, end, 2 * pos + 1, l, (l + r)\
    \ / 2), _get(begin, end, 2 * pos + 2, (l + r) / 2, r));\n    }\n    RangeMinimumQuery(int\
    \ N, T defaultT) : N(N), defaultT(defaultT) {\n        int N_tmp = 1;\n      \
    \  while (N_tmp < N) N_tmp <<= 1;\n        x.assign(N_tmp * 2, defaultT), head\
    \ = N_tmp - 1;\n    }\n    void build(const vector<T> &vals) {\n        copy(vals.begin(),\
    \ vals.end(), x.begin() + head);\n        for (int i = head - 1; i >= 0; i--)\
    \ { x[i] = min(x[i * 2 + 1], x[i * 2 + 2]); }\n    }\n    RangeMinimumQuery(const\
    \ vector<T> &vals, T defaultT) : N(vals.size()), defaultT(defaultT) {\n      \
    \  int N_tmp = 1;\n        while (N_tmp < N) N_tmp <<= 1;\n        x.assign(N_tmp\
    \ * 2, defaultT), head = N_tmp - 1;\n        build(vals);\n    }\n    RangeMinimumQuery()\
    \ : RangeMinimumQuery(0, T()) {}\n    void update(int pos, T val) {\n        pos\
    \ += head, x[pos] = val;\n        while (pos) pos = (pos - 1) / 2, x[pos] = min(x[pos\
    \ * 2 + 1], x[pos * 2 + 2]);\n    }\n    T get(int begin, int end) const { return\
    \ _get(begin, end, 0, 0, (int)x.size() / 2); }\n    friend ostream &operator<<(ostream\
    \ &os, const RangeMinimumQuery &s) {\n        os << \"[\";\n        for (int i\
    \ = 0; i < s.N; i++) os << s.get(i, i + 1) << \",\";\n        return os << \"\
    ]\";\n    }\n};\n"
  code: "#pragma once\n#include <iostream>\n#include <vector>\nusing namespace std;\n\
    \n// CUT begin\nusing T = int;\nstruct RangeMinimumQuery {\n    int N;\n    T\
    \ defaultT = 1e9;\n    int head;\n    vector<T> x;\n    T _get(int begin, int\
    \ end, int pos, int l, int r) const {\n        if (r <= begin or l >= end) return\
    \ defaultT;\n        if (l >= begin and r <= end) return x[pos];\n        return\
    \ min(_get(begin, end, 2 * pos + 1, l, (l + r) / 2), _get(begin, end, 2 * pos\
    \ + 2, (l + r) / 2, r));\n    }\n    RangeMinimumQuery(int N, T defaultT) : N(N),\
    \ defaultT(defaultT) {\n        int N_tmp = 1;\n        while (N_tmp < N) N_tmp\
    \ <<= 1;\n        x.assign(N_tmp * 2, defaultT), head = N_tmp - 1;\n    }\n  \
    \  void build(const vector<T> &vals) {\n        copy(vals.begin(), vals.end(),\
    \ x.begin() + head);\n        for (int i = head - 1; i >= 0; i--) { x[i] = min(x[i\
    \ * 2 + 1], x[i * 2 + 2]); }\n    }\n    RangeMinimumQuery(const vector<T> &vals,\
    \ T defaultT) : N(vals.size()), defaultT(defaultT) {\n        int N_tmp = 1;\n\
    \        while (N_tmp < N) N_tmp <<= 1;\n        x.assign(N_tmp * 2, defaultT),\
    \ head = N_tmp - 1;\n        build(vals);\n    }\n    RangeMinimumQuery() : RangeMinimumQuery(0,\
    \ T()) {}\n    void update(int pos, T val) {\n        pos += head, x[pos] = val;\n\
    \        while (pos) pos = (pos - 1) / 2, x[pos] = min(x[pos * 2 + 1], x[pos *\
    \ 2 + 2]);\n    }\n    T get(int begin, int end) const { return _get(begin, end,\
    \ 0, 0, (int)x.size() / 2); }\n    friend ostream &operator<<(ostream &os, const\
    \ RangeMinimumQuery &s) {\n        os << \"[\";\n        for (int i = 0; i < s.N;\
    \ i++) os << s.get(i, i + 1) << \",\";\n        return os << \"]\";\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/range_minimum_query.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - segmenttree/test/point-update-range-min.test.cpp
documentation_of: segmenttree/range_minimum_query.hpp
layout: document
redirect_from:
- /library/segmenttree/range_minimum_query.hpp
- /library/segmenttree/range_minimum_query.hpp.html
title: segmenttree/range_minimum_query.hpp
---
