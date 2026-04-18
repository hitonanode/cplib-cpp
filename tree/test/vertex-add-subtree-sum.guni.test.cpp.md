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
    \    }\n};\n#line 2 \"tree/guni.hpp\"\n#include <span>\n#include <type_traits>\n\
    #line 5 \"tree/guni.hpp\"\n\n// Guni / Sack / DSU on tree\n// https://codeforces.com/blog/entry/44351\n\
    // https://atcoder.jp/contests/abc454/editorial/19112\nstruct guni {\n    int\
    \ n;\n    int last_root;\n    std::vector<std::vector<int>> to;\n    std::vector<int>\
    \ sz, ver, st, ft; // subtree size / dfs order / subtree start / subtree fin\n\
    \n    guni(int n_ = 0) : n(n_), last_root(-1), to(n_) {}\n\n    void add_bi_edge(int\
    \ u, int v) { to.at(u).push_back(v), to.at(v).push_back(u); }\n\n    void sdfs(int\
    \ v, int p) { // Build sz / ver / st / ft, and move heavy child to the back\n\
    \        st.at(v) = ver.size(), ver.push_back(v);\n        int heavy_idx = -1;\n\
    \        for (int i = 0; i < int(to.at(v).size()); ++i) {\n            int u =\
    \ to.at(v).at(i);\n            if (u == p) continue;\n            sdfs(u, v);\n\
    \            sz.at(v) += sz.at(u);\n            if (heavy_idx == -1 or sz.at(u)\
    \ > sz.at(to.at(v).at(heavy_idx))) heavy_idx = i;\n        }\n        if (heavy_idx\
    \ != -1) std::swap(to.at(v).at(heavy_idx), to.at(v).back());\n        ft.at(v)\
    \ = ver.size();\n    }\n\n    std::span<const int> subtree(int v) const {\n  \
    \      return std::span<const int>(ver).subspan(st.at(v), ft.at(v) - st.at(v));\n\
    \    }\n\n    template <class F> void call_reset(F &ResetAll, int v) const {\n\
    \        if constexpr (std::is_invocable_v<F &, std::span<const int>>) {\n   \
    \         ResetAll(subtree(v));\n        } else {\n            static_assert(\n\
    \                std::is_invocable_v<F &>,\n                \"ResetAll must be\
    \ callable with std::span<const int> or with no argument\");\n            ResetAll();\n\
    \        }\n    }\n\n    template <class F1, class F2, class F3>\n    void dfs(int\
    \ v, int p, F1 &Add, F2 &ResetAll, F3 &Solve) {\n        const int big_child =\
    \ (!to.at(v).empty() and to.at(v).back() != p) ? to.at(v).back() : -1;\n     \
    \   for (int u : to.at(v)) {\n            if (u != p and u != big_child) {\n \
    \               dfs(u, v, Add, ResetAll, Solve);\n                call_reset(ResetAll,\
    \ u);\n            }\n        }\n        if (big_child != -1) dfs(big_child, v,\
    \ Add, ResetAll, Solve);\n\n        for (int u : to.at(v)) {\n            if (u\
    \ != p and u != big_child) {\n                for (int i = st.at(u); i < ft.at(u);\
    \ ++i) Add(ver.at(i));\n            }\n        }\n        Add(v);\n        Solve(v);\n\
    \    }\n\n    template <class F1, class F2, class F3>\n    void run(const int\
    \ root, F1 Add, F2 ResetAll, F3 Solve) {\n        if (last_root != root) {\n \
    \           last_root = root, ver.clear(), st.resize(n), ft.resize(n), sz.assign(n,\
    \ 1);\n            sdfs(root, -1);\n        }\n        dfs(root, -1, Add, ResetAll,\
    \ Solve);\n        call_reset(ResetAll, root);\n    }\n};\n#line 3 \"tree/test/vertex-add-subtree-sum.guni.test.cpp\"\
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
    \ bit.add(t, w);\n    };\n\n    auto ResetSubtree = [&](std::span<const int> view)\
    \ {\n        for (int v : view) {\n            for (auto [t, w] : v2t2add.at(v))\
    \ bit.add(t, -w);\n        }\n    };\n\n    auto Solve = [&](int v) {\n      \
    \  for (auto [t, _] : v2t2sol.at(v)) ret.at(t) = bit.sum(0, t + 1);\n    };\n\n\
    \    g.run(0, Add, ResetSubtree, Solve);\n\n    for (auto x : ret) {\n       \
    \ if (x >= 0) cout << x << '\\n';\n    }\n}\n"
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
    \   };\n\n    auto ResetSubtree = [&](std::span<const int> view) {\n        for\
    \ (int v : view) {\n            for (auto [t, w] : v2t2add.at(v)) bit.add(t, -w);\n\
    \        }\n    };\n\n    auto Solve = [&](int v) {\n        for (auto [t, _]\
    \ : v2t2sol.at(v)) ret.at(t) = bit.sum(0, t + 1);\n    };\n\n    g.run(0, Add,\
    \ ResetSubtree, Solve);\n\n    for (auto x : ret) {\n        if (x >= 0) cout\
    \ << x << '\\n';\n    }\n}\n"
  dependsOn:
  - segmenttree/binary_indexed_tree.hpp
  - tree/guni.hpp
  isVerificationFile: true
  path: tree/test/vertex-add-subtree-sum.guni.test.cpp
  requiredBy: []
  timestamp: '2026-04-19 01:24:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/vertex-add-subtree-sum.guni.test.cpp
layout: document
redirect_from:
- /verify/tree/test/vertex-add-subtree-sum.guni.test.cpp
- /verify/tree/test/vertex-add-subtree-sum.guni.test.cpp.html
title: tree/test/vertex-add-subtree-sum.guni.test.cpp
---
