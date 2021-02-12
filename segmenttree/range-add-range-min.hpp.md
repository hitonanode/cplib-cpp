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
  bundledCode: "#line 2 \"segmenttree/range-add-range-min.hpp\"\n#include <algorithm>\n\
    #include <vector>\n\n// CUT begin\n// StarrySkyTree: segment tree for Range Minimum\
    \ Query & Range Add Query\n// Complexity: $O(N)$ (construction), $O(\\log N)$\
    \ (add / get)\ntemplate <typename Tp> struct RangeAddRangeMin {\n    int N, head;\n\
    \    Tp defaultMin;\n    std::vector<Tp> range_min, range_add;\n    static inline\
    \ Tp f(Tp x, Tp y) noexcept { return std::min(x, y); }\n\n    inline void _merge(int\
    \ pos) {\n        range_min[pos] = f(range_min[pos * 2] + range_add[pos * 2],\
    \ range_min[pos * 2 + 1] + range_add[pos * 2 + 1]);\n    }\n    void initialize(const\
    \ std::vector<Tp> &data_init, Tp default_min) {\n        N = data_init.size(),\
    \ head = 1;\n        while (head < N) head <<= 1;\n        defaultMin = default_min;\n\
    \        range_min.assign(head * 2, defaultMin);\n        range_add.assign(head\
    \ * 2, 0);\n        std::copy(data_init.begin(), data_init.end(), range_min.begin()\
    \ + head);\n        for (int pos = head; --pos;) _merge(pos);\n    }\n    RangeAddRangeMin()\
    \ = default;\n    RangeAddRangeMin(const std::vector<Tp> &data_init, Tp default_min)\
    \ { initialize(data_init, default_min); }\n    void _add(int begin, int end, int\
    \ pos, int l, int r, Tp vadd) noexcept {\n        if (r <= begin or end <= l)\
    \ return;\n        if (begin <= l and r <= end) {\n            range_add[pos]\
    \ += vadd;\n            return;\n        }\n        _add(begin, end, pos * 2,\
    \ l, (l + r) / 2, vadd);\n        _add(begin, end, pos * 2 + 1, (l + r) / 2, r,\
    \ vadd);\n        _merge(pos);\n    }\n    // Add `vadd` to (x_begin, ..., x_{end\
    \ - 1})\n    void add(int begin, int end, Tp vadd) noexcept { return _add(begin,\
    \ end, 1, 0, head, vadd); }\n    Tp _get(int begin, int end, int pos, int l, int\
    \ r) const noexcept {\n        if (r <= begin or end <= l) return defaultMin;\n\
    \        if (begin <= l and r <= end) return range_min[pos] + range_add[pos];\n\
    \        return f(_get(begin, end, pos * 2, l, (l + r) / 2), _get(begin, end,\
    \ pos * 2 + 1, (l + r) / 2, r)) + range_add[pos];\n    }\n    // Return f(x_begin,\
    \ ..., x_{end - 1})\n    Tp get(int begin, int end) const noexcept { return _get(begin,\
    \ end, 1, 0, head); }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <vector>\n\n// CUT begin\n//\
    \ StarrySkyTree: segment tree for Range Minimum Query & Range Add Query\n// Complexity:\
    \ $O(N)$ (construction), $O(\\log N)$ (add / get)\ntemplate <typename Tp> struct\
    \ RangeAddRangeMin {\n    int N, head;\n    Tp defaultMin;\n    std::vector<Tp>\
    \ range_min, range_add;\n    static inline Tp f(Tp x, Tp y) noexcept { return\
    \ std::min(x, y); }\n\n    inline void _merge(int pos) {\n        range_min[pos]\
    \ = f(range_min[pos * 2] + range_add[pos * 2], range_min[pos * 2 + 1] + range_add[pos\
    \ * 2 + 1]);\n    }\n    void initialize(const std::vector<Tp> &data_init, Tp\
    \ default_min) {\n        N = data_init.size(), head = 1;\n        while (head\
    \ < N) head <<= 1;\n        defaultMin = default_min;\n        range_min.assign(head\
    \ * 2, defaultMin);\n        range_add.assign(head * 2, 0);\n        std::copy(data_init.begin(),\
    \ data_init.end(), range_min.begin() + head);\n        for (int pos = head; --pos;)\
    \ _merge(pos);\n    }\n    RangeAddRangeMin() = default;\n    RangeAddRangeMin(const\
    \ std::vector<Tp> &data_init, Tp default_min) { initialize(data_init, default_min);\
    \ }\n    void _add(int begin, int end, int pos, int l, int r, Tp vadd) noexcept\
    \ {\n        if (r <= begin or end <= l) return;\n        if (begin <= l and r\
    \ <= end) {\n            range_add[pos] += vadd;\n            return;\n      \
    \  }\n        _add(begin, end, pos * 2, l, (l + r) / 2, vadd);\n        _add(begin,\
    \ end, pos * 2 + 1, (l + r) / 2, r, vadd);\n        _merge(pos);\n    }\n    //\
    \ Add `vadd` to (x_begin, ..., x_{end - 1})\n    void add(int begin, int end,\
    \ Tp vadd) noexcept { return _add(begin, end, 1, 0, head, vadd); }\n    Tp _get(int\
    \ begin, int end, int pos, int l, int r) const noexcept {\n        if (r <= begin\
    \ or end <= l) return defaultMin;\n        if (begin <= l and r <= end) return\
    \ range_min[pos] + range_add[pos];\n        return f(_get(begin, end, pos * 2,\
    \ l, (l + r) / 2), _get(begin, end, pos * 2 + 1, (l + r) / 2, r)) + range_add[pos];\n\
    \    }\n    // Return f(x_begin, ..., x_{end - 1})\n    Tp get(int begin, int\
    \ end) const noexcept { return _get(begin, end, 1, 0, head); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/range-add-range-min.hpp
  requiredBy: []
  timestamp: '2021-02-13 02:26:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: segmenttree/range-add-range-min.hpp
layout: document
title: Range Add Range Min (known as the Starry sky tree)
---

## Link
