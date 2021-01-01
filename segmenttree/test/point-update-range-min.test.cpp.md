---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/range_minimum_query.hpp
    title: segmenttree/range_minimum_query.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
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
    ]\";\n    }\n};\n#line 3 \"segmenttree/test/point-update-range-min.test.cpp\"\n\
    using namespace std;\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A\"\
    \n\nint main() {\n    int N, Q;\n    cin >> N >> Q;\n    vector<int> A(N, (1LL\
    \ << 31) - 1);\n    RangeMinimumQuery rmq(A, A[0]);\n    for (int q = 0; q < Q;\
    \ q++) {\n        int c, x, y;\n        cin >> c >> x >> y;\n        if (c ==\
    \ 0) {\n            rmq.update(x, y);\n        } else {\n            cout << rmq.get(x,\
    \ y + 1) << endl;\n        }\n    }\n}\n"
  code: "#include \"../range_minimum_query.hpp\"\n#include <iostream>\nusing namespace\
    \ std;\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A\"\
    \n\nint main() {\n    int N, Q;\n    cin >> N >> Q;\n    vector<int> A(N, (1LL\
    \ << 31) - 1);\n    RangeMinimumQuery rmq(A, A[0]);\n    for (int q = 0; q < Q;\
    \ q++) {\n        int c, x, y;\n        cin >> c >> x >> y;\n        if (c ==\
    \ 0) {\n            rmq.update(x, y);\n        } else {\n            cout << rmq.get(x,\
    \ y + 1) << endl;\n        }\n    }\n}\n"
  dependsOn:
  - segmenttree/range_minimum_query.hpp
  isVerificationFile: true
  path: segmenttree/test/point-update-range-min.test.cpp
  requiredBy: []
  timestamp: '2021-01-01 16:52:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/point-update-range-min.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/point-update-range-min.test.cpp
- /verify/segmenttree/test/point-update-range-min.test.cpp.html
title: segmenttree/test/point-update-range-min.test.cpp
---
