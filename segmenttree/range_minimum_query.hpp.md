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
    #include <limits>\n#include <vector>\n\n// CUT begin\n// Range Minimum Query\n\
    // - RangeMinimumQuery<T, defaultT>(int N = 0) : Initialize array x = [defaultT,\
    \ ..., defaultT] of length N, O(N)\n// - RangeMinimumQuery<T, defaultT>(const\
    \ std::vector<T> &vals) : Initialize array x by [vals[0], ..., vals[-1]], O(N)\n\
    // - update(int pos, T val) : x[pos] <- val, O(log N)\n// - get(int begin, int\
    \ end) : Get min(x_begin, ..., x_(end - 1)), O(log N)\ntemplate <typename T, T\
    \ defaultT = std::numeric_limits<T>::max() / 2> struct RangeMinimumQuery {\n \
    \   int N;\n    int head;\n    std::vector<T> x;\n    T _get(int begin, int end,\
    \ int pos, int l, int r) const {\n        if (r <= begin or l >= end) return defaultT;\n\
    \        if (l >= begin and r <= end) return x[pos];\n        return std::min(_get(begin,\
    \ end, 2 * pos + 1, l, (l + r) / 2), _get(begin, end, 2 * pos + 2, (l + r) / 2,\
    \ r));\n    }\n    RangeMinimumQuery(int N = 0) : N(N) {\n        int N_tmp =\
    \ 1;\n        while (N_tmp < N) N_tmp <<= 1;\n        x.assign(N_tmp * 2, defaultT),\
    \ head = N_tmp - 1;\n    }\n    void _build(const std::vector<T> &vals) {\n  \
    \      std::copy(vals.begin(), vals.end(), x.begin() + head);\n        for (int\
    \ i = head - 1; i >= 0; i--) x[i] = std::min(x[i * 2 + 1], x[i * 2 + 2]);\n  \
    \  }\n    RangeMinimumQuery(const std::vector<T> &vals) : N(vals.size()) {\n \
    \       int N_tmp = 1;\n        while (N_tmp < N) N_tmp <<= 1;\n        x.assign(N_tmp\
    \ * 2, defaultT), head = N_tmp - 1;\n        _build(vals);\n    }\n    void update(int\
    \ pos, T val) {\n        pos += head, x[pos] = val;\n        while (pos) pos =\
    \ (pos - 1) / 2, x[pos] = std::min(x[pos * 2 + 1], x[pos * 2 + 2]);\n    }\n \
    \   T get(int begin, int end) const { return _get(begin, end, 0, 0, (int)x.size()\
    \ / 2); }\n    friend std::ostream &operator<<(std::ostream &os, const RangeMinimumQuery\
    \ &s) {\n        os << '[';\n        for (int i = 0; i < s.N; i++) os << s.get(i,\
    \ i + 1) << ',';\n        return os << ']';\n    }\n};\n"
  code: "#pragma once\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \n// CUT begin\n// Range Minimum Query\n// - RangeMinimumQuery<T, defaultT>(int\
    \ N = 0) : Initialize array x = [defaultT, ..., defaultT] of length N, O(N)\n\
    // - RangeMinimumQuery<T, defaultT>(const std::vector<T> &vals) : Initialize array\
    \ x by [vals[0], ..., vals[-1]], O(N)\n// - update(int pos, T val) : x[pos] <-\
    \ val, O(log N)\n// - get(int begin, int end) : Get min(x_begin, ..., x_(end -\
    \ 1)), O(log N)\ntemplate <typename T, T defaultT = std::numeric_limits<T>::max()\
    \ / 2> struct RangeMinimumQuery {\n    int N;\n    int head;\n    std::vector<T>\
    \ x;\n    T _get(int begin, int end, int pos, int l, int r) const {\n        if\
    \ (r <= begin or l >= end) return defaultT;\n        if (l >= begin and r <= end)\
    \ return x[pos];\n        return std::min(_get(begin, end, 2 * pos + 1, l, (l\
    \ + r) / 2), _get(begin, end, 2 * pos + 2, (l + r) / 2, r));\n    }\n    RangeMinimumQuery(int\
    \ N = 0) : N(N) {\n        int N_tmp = 1;\n        while (N_tmp < N) N_tmp <<=\
    \ 1;\n        x.assign(N_tmp * 2, defaultT), head = N_tmp - 1;\n    }\n    void\
    \ _build(const std::vector<T> &vals) {\n        std::copy(vals.begin(), vals.end(),\
    \ x.begin() + head);\n        for (int i = head - 1; i >= 0; i--) x[i] = std::min(x[i\
    \ * 2 + 1], x[i * 2 + 2]);\n    }\n    RangeMinimumQuery(const std::vector<T>\
    \ &vals) : N(vals.size()) {\n        int N_tmp = 1;\n        while (N_tmp < N)\
    \ N_tmp <<= 1;\n        x.assign(N_tmp * 2, defaultT), head = N_tmp - 1;\n   \
    \     _build(vals);\n    }\n    void update(int pos, T val) {\n        pos +=\
    \ head, x[pos] = val;\n        while (pos) pos = (pos - 1) / 2, x[pos] = std::min(x[pos\
    \ * 2 + 1], x[pos * 2 + 2]);\n    }\n    T get(int begin, int end) const { return\
    \ _get(begin, end, 0, 0, (int)x.size() / 2); }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const RangeMinimumQuery &s) {\n        os << '[';\n        for (int i =\
    \ 0; i < s.N; i++) os << s.get(i, i + 1) << ',';\n        return os << ']';\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/range_minimum_query.hpp
  requiredBy: []
  timestamp: '2021-04-18 20:20:24+09:00'
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
