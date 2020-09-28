---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/contest/1288/submission/68865506>
  bundledCode: "#line 2 \"segmenttree/count_less_than.hpp\"\n#include <algorithm>\n\
    #include <iostream>\n#include <vector>\nusing namespace std;\n\n// CUT begin\n\
    // Count elements in [A_begin, ..., A_{end-1}] which satisfy A_i < query\n// Complexity:\
    \ O(N log^2 N) for initialization, O(log^2 N) for each query\n// Verified: cntLess\
    \ <https://codeforces.com/contest/1288/submission/68865506>\nstruct CountLessThan\n\
    {\n    using T = int;\n    int N;\n    int head;\n    vector<vector<T>> x;\n \
    \   inline void merge(int pos) {\n        x[pos] = x[pos * 2 + 1];\n        x[pos].insert(x[pos].end(),\
    \ x[pos * 2 + 2].begin(), x[pos * 2 + 2].end());\n        sort(x[pos].begin(),\
    \ x[pos].end());\n    }\n    int _getless(int begin, int end, int pos, int l,\
    \ int r, T query) const {\n        if (r <= begin or l >= end) return 0;\n   \
    \     if (l >= begin and r <= end) return lower_bound(x[pos].begin(), x[pos].end(),\
    \ query) - x[pos].begin();\n        return _getless(begin, end, 2 * pos + 1, l,\
    \ (l + r) / 2, query) + _getless(begin, end, 2 * pos + 2, (l + r) / 2, r, query);\n\
    \    }\n    int _getlesseq(int begin, int end, int pos, int l, int r, T query)\
    \ const {\n        if (r <= begin or l >= end) return 0;\n        if (l >= begin\
    \ and r <= end) return upper_bound(x[pos].begin(), x[pos].end(), query) - x[pos].begin();\n\
    \        return _getlesseq(begin, end, 2 * pos + 1, l, (l + r) / 2, query) + _getlesseq(begin,\
    \ end, 2 * pos + 2, (l + r) / 2, r, query);\n    }\n    CountLessThan() = default;\n\
    \    CountLessThan(const vector<T> &vec) : N(vec.size()) {\n        int N_tmp\
    \ = 1; while (N_tmp < N) N_tmp <<= 1;\n        x.resize(N_tmp*2), head = N_tmp\
    \ - 1;\n        for (int i = 0; i < N; i++) x[head + i] = {vec[i]};\n        for\
    \ (int i = head - 1; i >= 0; i--) merge(i);\n    }\n    int cntLess(int begin,\
    \ int end, T query) const { return _getless(begin, end, 0, 0, (int)x.size() /\
    \ 2, query); }\n    int cntLesseq(int begin, int end, T query) const { return\
    \ _getlesseq(begin, end, 0, 0, (int)x.size() / 2, query); }\n    int cntMore(int\
    \ begin, int end, T query) const {\n        int tot = max(0, min(end, N) - max(begin,\
    \ 0));\n        return tot - cntLesseq(begin, end, query);\n    }\n    int cntMoreeq(int\
    \ begin, int end, T query) const {\n        int tot = max(0, min(end, N) - max(begin,\
    \ 0));\n        return tot - cntLess(begin, end, query);\n    }\n\n    friend\
    \ ostream &operator<<(ostream &os, const CountLessThan &clt) {\n        os <<\
    \ '[';\n        for (int i = 0; i < clt.N; i++) os << clt.x[clt.head + i][0] <<\
    \ ',';\n        os << ']';\n        return os;\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <iostream>\n#include <vector>\n\
    using namespace std;\n\n// CUT begin\n// Count elements in [A_begin, ..., A_{end-1}]\
    \ which satisfy A_i < query\n// Complexity: O(N log^2 N) for initialization, O(log^2\
    \ N) for each query\n// Verified: cntLess <https://codeforces.com/contest/1288/submission/68865506>\n\
    struct CountLessThan\n{\n    using T = int;\n    int N;\n    int head;\n    vector<vector<T>>\
    \ x;\n    inline void merge(int pos) {\n        x[pos] = x[pos * 2 + 1];\n   \
    \     x[pos].insert(x[pos].end(), x[pos * 2 + 2].begin(), x[pos * 2 + 2].end());\n\
    \        sort(x[pos].begin(), x[pos].end());\n    }\n    int _getless(int begin,\
    \ int end, int pos, int l, int r, T query) const {\n        if (r <= begin or\
    \ l >= end) return 0;\n        if (l >= begin and r <= end) return lower_bound(x[pos].begin(),\
    \ x[pos].end(), query) - x[pos].begin();\n        return _getless(begin, end,\
    \ 2 * pos + 1, l, (l + r) / 2, query) + _getless(begin, end, 2 * pos + 2, (l +\
    \ r) / 2, r, query);\n    }\n    int _getlesseq(int begin, int end, int pos, int\
    \ l, int r, T query) const {\n        if (r <= begin or l >= end) return 0;\n\
    \        if (l >= begin and r <= end) return upper_bound(x[pos].begin(), x[pos].end(),\
    \ query) - x[pos].begin();\n        return _getlesseq(begin, end, 2 * pos + 1,\
    \ l, (l + r) / 2, query) + _getlesseq(begin, end, 2 * pos + 2, (l + r) / 2, r,\
    \ query);\n    }\n    CountLessThan() = default;\n    CountLessThan(const vector<T>\
    \ &vec) : N(vec.size()) {\n        int N_tmp = 1; while (N_tmp < N) N_tmp <<=\
    \ 1;\n        x.resize(N_tmp*2), head = N_tmp - 1;\n        for (int i = 0; i\
    \ < N; i++) x[head + i] = {vec[i]};\n        for (int i = head - 1; i >= 0; i--)\
    \ merge(i);\n    }\n    int cntLess(int begin, int end, T query) const { return\
    \ _getless(begin, end, 0, 0, (int)x.size() / 2, query); }\n    int cntLesseq(int\
    \ begin, int end, T query) const { return _getlesseq(begin, end, 0, 0, (int)x.size()\
    \ / 2, query); }\n    int cntMore(int begin, int end, T query) const {\n     \
    \   int tot = max(0, min(end, N) - max(begin, 0));\n        return tot - cntLesseq(begin,\
    \ end, query);\n    }\n    int cntMoreeq(int begin, int end, T query) const {\n\
    \        int tot = max(0, min(end, N) - max(begin, 0));\n        return tot -\
    \ cntLess(begin, end, query);\n    }\n\n    friend ostream &operator<<(ostream\
    \ &os, const CountLessThan &clt) {\n        os << '[';\n        for (int i = 0;\
    \ i < clt.N; i++) os << clt.x[clt.head + i][0] << ',';\n        os << ']';\n \
    \       return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/count_less_than.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: segmenttree/count_less_than.hpp
layout: document
redirect_from:
- /library/segmenttree/count_less_than.hpp
- /library/segmenttree/count_less_than.hpp.html
title: segmenttree/count_less_than.hpp
---
