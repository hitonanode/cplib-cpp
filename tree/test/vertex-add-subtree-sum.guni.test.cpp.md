---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/binary_indexed_tree.hpp
    title: "Binary indexed tree / Fenwick tree \uFF08BIT\u30FB\u30D5\u30A7\u30CB\u30C3\
      \u30AF\u6728\uFF09"
  - icon: ':heavy_check_mark:'
    path: tree/guni.hpp
    title: "Guni (Sack) / DSU on tree \uFF08\u6839\u4ED8\u304D\u6728\u306E\u5168\u3066\
      \u306E\u90E8\u5206\u6728\u3092\u7D4C\u7531\u3059\u308B\u3088\u3046\u306A\u9802\
      \u70B9\u8FFD\u52A0\u30FB\u524A\u9664\u64CD\u4F5C\u5217\u306E\u751F\u6210\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_subtree_sum
  bundledCode: "#line 2 \"segmenttree/binary_indexed_tree.hpp\"\n#include <algorithm>\n\
    #include <vector>\n\n// CUT begin\n// 0-indexed BIT (binary indexed tree / Fenwick\
    \ tree) (i : [0, len))\ntemplate <class T> struct BIT {\n    int n;\n    std::vector<T>\
    \ data;\n    BIT(int len = 0) : n(len), data(len) {}\n    void reset() { std::fill(data.begin(),\
    \ data.end(), T(0)); }\n    void add(int pos, T v) { // a[pos] += v\n        pos++;\n\
    \        while (pos > 0 and pos <= n) data[pos - 1] += v, pos += pos & -pos;\n\
    \    }\n    T sum(int k) const { // a[0] + ... + a[k - 1]\n        T res = 0;\n\
    \        while (k > 0) res += data[k - 1], k -= k & -k;\n        return res;\n\
    \    }\n\n    T sum(int l, int r) const { return sum(r) - sum(l); } // a[l] +\
    \ ... + a[r - 1]\n\n    template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const BIT &bit) {\n        T prv = 0;\n        os << '[';\n        for\
    \ (int i = 1; i <= bit.n; i++) {\n            T now = bit.sum(i);\n          \
    \  os << now - prv << ',', prv = now;\n        }\n        return os << ']';\n\
    \    }\n};\n#line 3 \"tree/guni.hpp\"\n\n// Guni / Sack / DSU on tree\n// https://codeforces.com/blog/entry/44351\n\
    struct guni {\n    int n;\n    int last_root;\n    std::vector<std::vector<int>>\
    \ to;\n    std::vector<int> sz, ver, st, ft; // subtree size / dfs order / subtree\
    \ start / subtree fin\n\n    guni(int n_ = 0) : n(n_), last_root(-1), to(n_) {}\n\
    \n    void add_bi_edge(int u, int v) { to.at(u).push_back(v), to.at(v).push_back(u);\
    \ }\n\n    void sdfs(int v, int p) { // Build sz / ver / st / ft\n        st.at(v)\
    \ = ver.size(), ver.push_back(v);\n        for (int u : to.at(v)) sz.at(v) +=\
    \ (u != p) ? (sdfs(u, v), sz.at(u)) : 0;\n        ft.at(v) = ver.size();\n   \
    \ }\n\n    template <class F1, class F2, class F3>\n    void dfs(int v, int p,\
    \ bool keep, F1 Add, F2 Remove, F3 Solve) {\n        int mx = -1, big_child =\
    \ -1;\n        for (int u : to.at(v)) {\n            if (u != p and sz.at(u) >\
    \ mx) mx = sz.at(u), big_child = u;\n        }\n        for (int u : to.at(v))\
    \ {\n            if (u != p and u != big_child) dfs(u, v, false, Add, Remove,\
    \ Solve);\n        }\n        if (big_child != -1) dfs(big_child, v, true, Add,\
    \ Remove, Solve);\n\n        for (int u : to.at(v)) {\n            if (u != p\
    \ and u != big_child) {\n                for (int i = st.at(u); i < ft.at(u);\
    \ ++i) Add(ver.at(i));\n            }\n        }\n        Add(v);\n        Solve(v);\n\
    \n        if (!keep) {\n            for (int i = st.at(v); i < ft.at(v); ++i)\
    \ Remove(ver.at(i));\n        }\n    }\n\n    template <class F1, class F2, class\
    \ F3> void run(const int root, F1 Add, F2 Remove, F3 Solve) {\n        if (last_root\
    \ != root) {\n            last_root = root, ver.clear(), st.resize(n), ft.resize(n),\
    \ sz.assign(n, 1);\n            sdfs(root, -1);\n        }\n        dfs(root,\
    \ -1, false, Add, Remove, Solve);\n    }\n};\n#line 3 \"tree/test/vertex-add-subtree-sum.guni.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\n\
    #include <cassert>\n#include <iostream>\n#line 7 \"tree/test/vertex-add-subtree-sum.guni.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    int N, Q;\n    cin >> N >> Q;\n  \
    \  guni g(N);\n    vector<int> A(N);\n    for (auto &a : A) cin >> a;\n    for\
    \ (int i = 1; i < N; i++) {\n        int p;\n        cin >> p;\n        g.add_bi_edge(p,\
    \ i);\n    }\n    BIT<long long> bit(Q);\n    vector<long long> ret(Q, -1);\n\
    \    vector<vector<pair<int, int>>> v2t2add(N), v2t2sol(N);\n\n    for (int i\
    \ = 0; i < N; ++i) v2t2add.at(i).emplace_back(0, A.at(i));\n\n    for (int t =\
    \ 0; t < Q; ++t) {\n        int tp, u;\n        cin >> tp >> u;\n        if (tp\
    \ == 0) {\n            int x;\n            cin >> x;\n            v2t2add.at(u).emplace_back(t,\
    \ x);\n        } else {\n            v2t2sol.at(u).emplace_back(t, -1);\n    \
    \    }\n    }\n\n    auto Add = [&](int v) {\n        for (auto [t, w] : v2t2add.at(v))\
    \ bit.add(t, w);\n    };\n\n    auto Remove = [&](int v) {\n        for (auto\
    \ [t, w] : v2t2add.at(v)) bit.add(t, -w);\n    };\n\n    auto Solve = [&](int\
    \ v) {\n        for (auto [t, _] : v2t2sol.at(v)) ret.at(t) = bit.sum(0, t + 1);\n\
    \    };\n\n    g.run(0, Add, Remove, Solve);\n\n    for (auto x : ret) {\n   \
    \     if (x >= 0) cout << x << '\\n';\n    }\n}\n"
  code: "#include \"../../segmenttree/binary_indexed_tree.hpp\"\n#include \"../guni.hpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\n\
    #include <cassert>\n#include <iostream>\n#include <vector>\nusing namespace std;\n\
    \nint main() {\n    int N, Q;\n    cin >> N >> Q;\n    guni g(N);\n    vector<int>\
    \ A(N);\n    for (auto &a : A) cin >> a;\n    for (int i = 1; i < N; i++) {\n\
    \        int p;\n        cin >> p;\n        g.add_bi_edge(p, i);\n    }\n    BIT<long\
    \ long> bit(Q);\n    vector<long long> ret(Q, -1);\n    vector<vector<pair<int,\
    \ int>>> v2t2add(N), v2t2sol(N);\n\n    for (int i = 0; i < N; ++i) v2t2add.at(i).emplace_back(0,\
    \ A.at(i));\n\n    for (int t = 0; t < Q; ++t) {\n        int tp, u;\n       \
    \ cin >> tp >> u;\n        if (tp == 0) {\n            int x;\n            cin\
    \ >> x;\n            v2t2add.at(u).emplace_back(t, x);\n        } else {\n   \
    \         v2t2sol.at(u).emplace_back(t, -1);\n        }\n    }\n\n    auto Add\
    \ = [&](int v) {\n        for (auto [t, w] : v2t2add.at(v)) bit.add(t, w);\n \
    \   };\n\n    auto Remove = [&](int v) {\n        for (auto [t, w] : v2t2add.at(v))\
    \ bit.add(t, -w);\n    };\n\n    auto Solve = [&](int v) {\n        for (auto\
    \ [t, _] : v2t2sol.at(v)) ret.at(t) = bit.sum(0, t + 1);\n    };\n\n    g.run(0,\
    \ Add, Remove, Solve);\n\n    for (auto x : ret) {\n        if (x >= 0) cout <<\
    \ x << '\\n';\n    }\n}\n"
  dependsOn:
  - segmenttree/binary_indexed_tree.hpp
  - tree/guni.hpp
  isVerificationFile: true
  path: tree/test/vertex-add-subtree-sum.guni.test.cpp
  requiredBy: []
  timestamp: '2023-05-09 07:39:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/vertex-add-subtree-sum.guni.test.cpp
layout: document
redirect_from:
- /verify/tree/test/vertex-add-subtree-sum.guni.test.cpp
- /verify/tree/test/vertex-add-subtree-sum.guni.test.cpp.html
title: tree/test/vertex-add-subtree-sum.guni.test.cpp
---
