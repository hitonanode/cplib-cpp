---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/merge_sort_tree.hpp
    title: "Merge sort tree \uFF08\u9759\u7684\u306A\u5217\u306E\u90E8\u5206\u5217\
      \u306B\u542B\u307E\u308C\u308B\u95BE\u5024\u4EE5\u4E0B\u306E\u8981\u7D20\u6570\
      \u30AF\u30A8\u30EA\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426
  bundledCode: "#line 1 \"segmenttree/test/merge_sort_tree.aoj2426.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426\"\n\
    #line 2 \"segmenttree/merge_sort_tree.hpp\"\n#include <algorithm>\n#include <vector>\n\
    \n// CUT begin\n// Count elements in $[A_\\mathrm{begin}, ..., A_{\\mathrm{end}-1}]$\
    \ which satisfy $A_i < \\mathrm{query}$\n// Complexity: $O(N \\log N)$ for initialization,\
    \ $O(\\log^2 N)$ for each query\n// Verified: https://codeforces.com/contest/1288/submission/68865506\n\
    template <typename T> struct merge_sort_tree {\n    int N;\n    std::vector<std::vector<T>>\
    \ x;\n    merge_sort_tree() = default;\n    merge_sort_tree(const std::vector<T>\
    \ &vec) : N(vec.size()) {\n        x.resize(N * 2);\n        for (int i = 0; i\
    \ < N; i++) x[N + i] = {vec[i]};\n        for (int i = N - 1; i; i--) {\n    \
    \        std::merge(x[i * 2].begin(), x[i * 2].end(), x[i * 2 + 1].begin(), x[i\
    \ * 2 + 1].end(), std::back_inserter(x[i]));\n        }\n    }\n    int cntLess(int\
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
    \ begin, int end, T query) const {\n        int tot = std::max(0, std::min(end,\
    \ N) - std::max(begin, 0));\n        return tot - cntLesseq(begin, end, query);\n\
    \    }\n    int cntMoreeq(int begin, int end, T query) const {\n        int tot\
    \ = std::max(0, std::min(end, N) - std::max(begin, 0));\n        return tot -\
    \ cntLess(begin, end, query);\n    }\n\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const merge_sort_tree &clt) {\n        os << '[';\n\
    \        for (int i = 0; i < clt.N; i++) os << clt.x[clt.N + i][0] << ',';\n \
    \       return os << ']';\n    }\n};\n#line 4 \"segmenttree/test/merge_sort_tree.aoj2426.test.cpp\"\
    \n#include <iostream>\n#include <utility>\n#line 7 \"segmenttree/test/merge_sort_tree.aoj2426.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, M;\n    cin >> N >> M;\n    vector<pair<int, int>> P(N);\n    for\
    \ (auto &p : P) cin >> p.first >> p.second;\n    sort(P.begin(), P.end());\n \
    \   vector<int> xs, ys;\n    for (auto p : P) xs.push_back(p.first), ys.push_back(p.second);\n\
    \    merge_sort_tree<int> tree(ys);\n    while (M--) {\n        int x1, y1, x2,\
    \ y2;\n        cin >> x1 >> y1 >> x2 >> y2;\n        int l = lower_bound(xs.begin(),\
    \ xs.end(), x1) - xs.begin();\n        int r = upper_bound(xs.begin(), xs.end(),\
    \ x2) - xs.begin();\n        cout << tree.cntLesseq(l, r, y2) - tree.cntLess(l,\
    \ r, y1) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426\"\
    \n#include \"../merge_sort_tree.hpp\"\n#include <algorithm>\n#include <iostream>\n\
    #include <utility>\n#include <vector>\nusing namespace std;\n\nint main() {\n\
    \    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, M;\n    cin >>\
    \ N >> M;\n    vector<pair<int, int>> P(N);\n    for (auto &p : P) cin >> p.first\
    \ >> p.second;\n    sort(P.begin(), P.end());\n    vector<int> xs, ys;\n    for\
    \ (auto p : P) xs.push_back(p.first), ys.push_back(p.second);\n    merge_sort_tree<int>\
    \ tree(ys);\n    while (M--) {\n        int x1, y1, x2, y2;\n        cin >> x1\
    \ >> y1 >> x2 >> y2;\n        int l = lower_bound(xs.begin(), xs.end(), x1) -\
    \ xs.begin();\n        int r = upper_bound(xs.begin(), xs.end(), x2) - xs.begin();\n\
    \        cout << tree.cntLesseq(l, r, y2) - tree.cntLess(l, r, y1) << '\\n';\n\
    \    }\n}\n"
  dependsOn:
  - segmenttree/merge_sort_tree.hpp
  isVerificationFile: true
  path: segmenttree/test/merge_sort_tree.aoj2426.test.cpp
  requiredBy: []
  timestamp: '2021-08-28 13:42:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/merge_sort_tree.aoj2426.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/merge_sort_tree.aoj2426.test.cpp
- /verify/segmenttree/test/merge_sort_tree.aoj2426.test.cpp.html
title: segmenttree/test/merge_sort_tree.aoj2426.test.cpp
---
