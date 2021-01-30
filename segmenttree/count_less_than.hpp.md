---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/contest/1288/submission/68865506
  bundledCode: "#line 2 \"segmenttree/count_less_than.hpp\"\n#include <algorithm>\n\
    #include <iostream>\n#include <vector>\nusing namespace std;\n\n// CUT begin\n\
    // Count elements in [A_begin, ..., A_{end-1}] which satisfy A_i < query\n// Complexity:\
    \ O(N log N) for initialization, O(log^2 N) for each query\n// Verified: cntLess\
    \ https://codeforces.com/contest/1288/submission/68865506\ntemplate <typename\
    \ T> struct CountLessThan {\n    int N;\n    vector<vector<T>> x;\n    CountLessThan()\
    \ = default;\n    CountLessThan(const vector<T> &vec) : N(vec.size()) {\n    \
    \    x.resize(N * 2);\n        for (int i = 0; i < N; i++) x[N + i] = {vec[i]};\n\
    \        for (int i = N - 1; i; i--) {\n            std::merge(x[i * 2].begin(),\
    \ x[i * 2].end(), x[i * 2 + 1].begin(), x[i * 2 + 1].end(), std::back_inserter(x[i]));\n\
    \        }\n    }\n    int cntLess(int l, int r, T query) const {\n        l +=\
    \ N, r += N;\n        int ret = 0;\n        while (l < r) {\n            if (l\
    \ & 1) ret += std::lower_bound(x[l].begin(), x[l].end(), query) - x[l].begin(),\
    \ l++;\n            if (r & 1) r--, ret += std::lower_bound(x[r].begin(), x[r].end(),\
    \ query) - x[r].begin();\n            l >>= 1, r >>= 1;\n        }\n        return\
    \ ret;\n    }\n    int cntLesseq(int l, int r, T query) const {\n        l +=\
    \ N, r += N;\n        int ret = 0;\n        while (l < r) {\n            if (l\
    \ & 1) ret += std::upper_bound(x[l].begin(), x[l].end(), query) - x[l].begin(),\
    \ l++;\n            if (r & 1) r--, ret += std::upper_bound(x[r].begin(), x[r].end(),\
    \ query) - x[r].begin();\n            l >>= 1, r >>= 1;\n        }\n        return\
    \ ret;\n    }\n    int cntMore(int begin, int end, T query) const {\n        int\
    \ tot = max(0, min(end, N) - max(begin, 0));\n        return tot - cntLesseq(begin,\
    \ end, query);\n    }\n    int cntMoreeq(int begin, int end, T query) const {\n\
    \        int tot = max(0, min(end, N) - max(begin, 0));\n        return tot -\
    \ cntLess(begin, end, query);\n    }\n\n    friend ostream &operator<<(ostream\
    \ &os, const CountLessThan &clt) {\n        os << '[';\n        for (int i = 0;\
    \ i < clt.N; i++) os << clt.x[clt.N + i][0] << ',';\n        return os << ']';\n\
    \    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <iostream>\n#include <vector>\n\
    using namespace std;\n\n// CUT begin\n// Count elements in [A_begin, ..., A_{end-1}]\
    \ which satisfy A_i < query\n// Complexity: O(N log N) for initialization, O(log^2\
    \ N) for each query\n// Verified: cntLess https://codeforces.com/contest/1288/submission/68865506\n\
    template <typename T> struct CountLessThan {\n    int N;\n    vector<vector<T>>\
    \ x;\n    CountLessThan() = default;\n    CountLessThan(const vector<T> &vec)\
    \ : N(vec.size()) {\n        x.resize(N * 2);\n        for (int i = 0; i < N;\
    \ i++) x[N + i] = {vec[i]};\n        for (int i = N - 1; i; i--) {\n         \
    \   std::merge(x[i * 2].begin(), x[i * 2].end(), x[i * 2 + 1].begin(), x[i * 2\
    \ + 1].end(), std::back_inserter(x[i]));\n        }\n    }\n    int cntLess(int\
    \ l, int r, T query) const {\n        l += N, r += N;\n        int ret = 0;\n\
    \        while (l < r) {\n            if (l & 1) ret += std::lower_bound(x[l].begin(),\
    \ x[l].end(), query) - x[l].begin(), l++;\n            if (r & 1) r--, ret +=\
    \ std::lower_bound(x[r].begin(), x[r].end(), query) - x[r].begin();\n        \
    \    l >>= 1, r >>= 1;\n        }\n        return ret;\n    }\n    int cntLesseq(int\
    \ l, int r, T query) const {\n        l += N, r += N;\n        int ret = 0;\n\
    \        while (l < r) {\n            if (l & 1) ret += std::upper_bound(x[l].begin(),\
    \ x[l].end(), query) - x[l].begin(), l++;\n            if (r & 1) r--, ret +=\
    \ std::upper_bound(x[r].begin(), x[r].end(), query) - x[r].begin();\n        \
    \    l >>= 1, r >>= 1;\n        }\n        return ret;\n    }\n    int cntMore(int\
    \ begin, int end, T query) const {\n        int tot = max(0, min(end, N) - max(begin,\
    \ 0));\n        return tot - cntLesseq(begin, end, query);\n    }\n    int cntMoreeq(int\
    \ begin, int end, T query) const {\n        int tot = max(0, min(end, N) - max(begin,\
    \ 0));\n        return tot - cntLess(begin, end, query);\n    }\n\n    friend\
    \ ostream &operator<<(ostream &os, const CountLessThan &clt) {\n        os <<\
    \ '[';\n        for (int i = 0; i < clt.N; i++) os << clt.x[clt.N + i][0] << ',';\n\
    \        return os << ']';\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/count_less_than.hpp
  requiredBy: []
  timestamp: '2021-01-31 00:11:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: segmenttree/count_less_than.hpp
layout: document
redirect_from:
- /library/segmenttree/count_less_than.hpp
- /library/segmenttree/count_less_than.hpp.html
title: segmenttree/count_less_than.hpp
---
