---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/static_toptree.hpp
    title: Static top tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root
    links:
    - https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root
  bundledCode: "#line 1 \"data_structure/test/static_toptree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root\"\
    \n\n#line 2 \"data_structure/static_toptree.hpp\"\n#include <cassert>\n#include\
    \ <utility>\n#include <vector>\n\n// Structure of static top tree\n// https://atcoder.jp/contests/abc351/submissions/52777033\n\
    struct static_toptree_structure {\n    enum NodeType {\n        Vertex,\n    \
    \    Compress,\n        Rake,\n        AddEdge,\n        AddVertex,\n    };\n\n\
    \    const std::vector<std::vector<int>> &to;\n    std::vector<int> par;\n   \
    \ std::vector<int> heavy_child; // heavy_child[i] = child of i on heavy path\n\
    \n    // toptree data\n    int stt_root = -1;\n    std::vector<int> P, L, R;\n\
    \    std::vector<NodeType> T;\n\nprivate:\n    int hld_dfs(int now, int prv) {\n\
    \        int sz = 1, max_sz = 0;\n        for (int nxt : to.at(now)) {\n     \
    \       if (nxt == prv) continue;\n            par.at(nxt) = now;\n          \
    \  int sub_sz = hld_dfs(nxt, now);\n            sz += sub_sz;\n            if\
    \ (max_sz < sub_sz) max_sz = sub_sz, heavy_child.at(now) = nxt;\n        }\n \
    \       return sz;\n    }\n\n    int create(int k, int l, int r, NodeType t) {\n\
    \        if (k == -1) {\n            k = P.size();\n            P.push_back(-1),\
    \ L.push_back(l), R.push_back(r), T.push_back(t);\n        } else {\n        \
    \    P.at(k) = -1, L.at(k) = l, R.at(k) = r, T.at(k) = t;\n        }\n\n     \
    \   if (l != -1) P.at(l) = k;\n        if (r != -1) P.at(r) = k;\n\n        return\
    \ k;\n    }\n\n    std::pair<int, int> merge(const std::vector<std::pair<int,\
    \ int>> &a, NodeType t) {\n        if (a.size() == 1) return a.front();\n\n  \
    \      int u = 0;\n        for (auto &[idx, sz] : a) u += sz;\n\n        std::vector<std::pair<int,\
    \ int>> left, right;\n        for (const auto &[idx, sz] : a) {\n            (u\
    \ > sz ? left : right).emplace_back(idx, sz), u -= sz * 2;\n        }\n\n    \
    \    auto [left_idx, left_sz] = merge(left, t);\n        auto [right_idx, right_sz]\
    \ = merge(right, t);\n\n        return {create(-1, left_idx, right_idx, t), left_sz\
    \ + right_sz};\n    }\n\n    std::pair<int, int> compress(int i) {\n        std::vector<std::pair<int,\
    \ int>> chs{add_vertex(i)};\n        while (heavy_child.at(i) != -1) {\n     \
    \       i = heavy_child.at(i);\n            chs.push_back(add_vertex(i));\n  \
    \      }\n\n        return merge(chs, Compress);\n    }\n\n    std::pair<int,\
    \ int> rake(int i) {\n        std::vector<std::pair<int, int>> chs;\n        for\
    \ (int j : to.at(i)) {\n            if (j == par.at(i) or j == heavy_child.at(i))\
    \ continue;\n            chs.push_back(add_edge(j));\n        }\n\n        return\
    \ chs.empty() ? std::make_pair(-1, 0) : merge(chs, Rake);\n    }\n\n    std::pair<int,\
    \ int> add_edge(int i) {\n        auto [c, sz] = compress(i);\n        return\
    \ {create(-1, c, -1, AddEdge), sz};\n    }\n\n    std::pair<int, int> add_vertex(int\
    \ i) {\n        auto [c, sz] = rake(i);\n        return {create(i, c, -1, c ==\
    \ -1 ? Vertex : AddVertex), sz + 1};\n    }\n\npublic:\n    static_toptree_structure(const\
    \ std::vector<std::vector<int>> &to, int root) : to(to) {\n\n        const int\
    \ n = to.size();\n\n        par.assign(n, -1), heavy_child.assign(n, -1);\n\n\
    \        hld_dfs(root, -1);\n\n        P.assign(n, -1), L.assign(n, -1), R.assign(n,\
    \ -1), T.assign(n, Vertex);\n\n        stt_root = compress(root).first;\n    }\n\
    \n    int size() const { return P.size(); }\n\n    // Top tree \u306E\u5E30\u308A\
    \u304C\u3051\u9806\u306B f() \u3092\u547C\u3076\n    // \u30C7\u30FC\u30BF\u306E\
    \u521D\u671F\u5316\u306A\u3069\u306B\u5229\u7528\u53EF\u80FD\n    template <class\
    \ Callback> void dfs_postorder(Callback f) const {\n        auto rec = [&](auto\
    \ &&self, int now) -> void {\n            if (L.at(now) != -1) self(self, L.at(now));\n\
    \            if (R.at(now) != -1) self(self, R.at(now));\n            f(now);\n\
    \        };\n        rec(rec, stt_root);\n    }\n\n    // Top tree \u306E v \u304B\
    \u3089\u6839\uFF08!= \u3082\u3068\u306E\u6728\u306E\u6839\uFF09\u307E\u3067\u306E\
    \u30D1\u30B9\u4E0A\u3067 f() \u3092\u547C\u3076\n    // \u4E00\u70B9\u66F4\u65B0\
    \u306A\u3069\u306B\u5229\u7528\u53EF\u80FD\n    template <class Callback> void\
    \ path_to_root(int v, Callback f) const {\n        while (v != -1) f(v), v = P.at(v);\n\
    \    }\n};\n\n// Static top tree\ntemplate <class TreeDP> struct static_toptree\
    \ {\n\n    using Point = typename TreeDP::Point;\n    using Path = typename TreeDP::Path;\n\
    \n    const static_toptree_structure &stts;\n    TreeDP &tree_dp;\n\n    std::vector<Point>\
    \ point;\n    std::vector<Path> path;\n\nprivate:\n    void _update(int i) {\n\
    \        if (stts.T.at(i) == static_toptree_structure::Vertex) {\n           \
    \ path.at(i) = tree_dp.vertex(i);\n        } else if (stts.T.at(i) == static_toptree_structure::Compress)\
    \ {\n            path.at(i) = tree_dp.compress(path.at(stts.L.at(i)), path.at(stts.R.at(i)));\n\
    \        } else if (stts.T.at(i) == static_toptree_structure::Rake) {\n      \
    \      point.at(i) = tree_dp.rake(point.at(stts.L.at(i)), point.at(stts.R.at(i)));\n\
    \        } else if (stts.T.at(i) == static_toptree_structure::AddEdge) {\n   \
    \         point.at(i) = tree_dp.add_edge(path.at(stts.L.at(i)));\n        } else\
    \ if (stts.T.at(i) == static_toptree_structure::AddVertex) {\n            path.at(i)\
    \ = tree_dp.add_vertex(point.at(stts.L.at(i)), i);\n        } else {\n       \
    \     assert(false);\n        }\n    }\n\npublic:\n    static_toptree(const static_toptree_structure\
    \ &stts, TreeDP &tree_dp)\n        : stts(stts), tree_dp(tree_dp), point(stts.size()),\
    \ path(stts.size()) {\n        stts.dfs_postorder([&](int k) { _update(k); });\n\
    \    }\n\n    void set(int i) {\n        stts.path_to_root(i, [&](int k) { _update(k);\
    \ });\n    }\n\n    Path all_prod() const { return path.at(stts.stt_root); }\n\
    \n    // Not verified yet\n    Path get_subtree(int i) const {\n        Path res\
    \ = path.at(i);\n        while (true) {\n            const int p = stts.P.at(i);\n\
    \            if (p == -1 or stts.T.at(p) != static_toptree_structure::Compress)\
    \ break;\n\n            if (stts.L.at(p) == i) res = tree_dp.compress(res, path.at(stts.R.at(p)));\n\
    \            i = p;\n        }\n\n        return res;\n    }\n};\n\n/*\nstruct\
    \ tree_dp {\n    struct Point;  // Point Cluster\n    struct Path;  // Path Cluster\n\
    \n    Path vertex(int i);\n\n    Path compress(const Path &p, const Path &c);\n\
    \n    Point rake(const Point &l, const Point &r);\n\n    Point add_edge(const\
    \ Path &d);\n\n    Path add_vertex(const Point &d, int i);\n};\n\nvector<vector<int>>\
    \ to(n);\nint root;\n\nconst static_toptree_structure stts(to, root);\n\ntree_dp\
    \ dp;\nstatic_toptree tree(stts, dp);\n*/\n#line 4 \"data_structure/test/static_toptree.test.cpp\"\
    \n\n#include <iostream>\n#line 7 \"data_structure/test/static_toptree.test.cpp\"\
    \nusing namespace std;\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \nstruct tree_dp {\n    vector<int> A;\n    vector<mint> parB;\n    vector<mint>\
    \ parC;\n\n    // Point Cluster\n    struct Point {\n        mint n;\n       \
    \ mint sum;\n    };\n\n    // Path Cluster\n    struct Path {\n        mint n;\n\
    \        mint sum;\n\n        mint b;\n        mint c;\n    };\n\n    Path vertex(int\
    \ i) { return {1, A.at(i) * parB.at(i) + parC.at(i), parB.at(i), parC.at(i)};\
    \ }\n\n    static Path compress(const Path &p, const Path &c) {\n        return\
    \ {p.n + c.n, p.sum + c.sum * p.b + c.n * p.c, c.b * p.b, p.c + c.c * p.b};\n\
    \    }\n\n    static Point rake(const Point &l, const Point &r) { return {l.n\
    \ + r.n, l.sum + r.sum}; }\n\n    static Point add_edge(const Path &d) { return\
    \ {d.n, d.sum}; }\n\n    Path add_vertex(const Point &d, int i) {\n        return\
    \ {d.n + 1, (d.sum + A.at(i)) * parB.at(i) + (d.n + 1) * parC.at(i), parB.at(i),\n\
    \                parC.at(i)};\n    }\n};\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int N, Q;\n    cin >> N >> Q;\n\n    vector<int>\
    \ A(N);\n    for (auto &a : A) cin >> a;\n\n    vector<int> U(N - 1), V(N - 1),\
    \ B(N - 1), C(N - 1);\n    vector<vector<int>> to(N);\n\n    for (int e = 0; e\
    \ < N - 1; ++e) {\n        cin >> U.at(e) >> V.at(e) >> B.at(e) >> C.at(e);\n\
    \        to.at(U.at(e)).push_back(V.at(e));\n        to.at(V.at(e)).push_back(U.at(e));\n\
    \    }\n\n    const static_toptree_structure stts(to, 0);\n\n    vector<mint>\
    \ parB(N, 1);\n    vector<mint> parC(N, 0);\n\n    for (int e = 0; e < N - 1;\
    \ ++e) {\n        int u = U.at(e), v = V.at(e);\n        if (stts.par.at(u) !=\
    \ v) swap(u, v);\n\n        assert(stts.par.at(u) == v);\n\n        parB.at(u)\
    \ = B.at(e);\n        parC.at(u) = C.at(e);\n    }\n\n    tree_dp dp{A, parB,\
    \ parC};\n\n    static_toptree tree(stts, dp);\n\n    while (Q--) {\n        int\
    \ tp;\n        cin >> tp;\n        if (tp == 0) {\n            int w, x;\n   \
    \         cin >> w >> x;\n            dp.A.at(w) = x;\n            tree.set(w);\n\
    \        } else {\n            int e, y, z;\n            cin >> e >> y >> z;\n\
    \n            int u = U.at(e), v = V.at(e);\n            if (stts.par.at(u) !=\
    \ v) swap(u, v);\n            assert(stts.par.at(u) == v);\n\n            dp.parB.at(u)\
    \ = y;\n            dp.parC.at(u) = z;\n            tree.set(u);\n        }\n\n\
    \        cout << tree.all_prod().sum.val() << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root\"\
    \n\n#include \"../static_toptree.hpp\"\n\n#include <iostream>\n#include <vector>\n\
    using namespace std;\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \nstruct tree_dp {\n    vector<int> A;\n    vector<mint> parB;\n    vector<mint>\
    \ parC;\n\n    // Point Cluster\n    struct Point {\n        mint n;\n       \
    \ mint sum;\n    };\n\n    // Path Cluster\n    struct Path {\n        mint n;\n\
    \        mint sum;\n\n        mint b;\n        mint c;\n    };\n\n    Path vertex(int\
    \ i) { return {1, A.at(i) * parB.at(i) + parC.at(i), parB.at(i), parC.at(i)};\
    \ }\n\n    static Path compress(const Path &p, const Path &c) {\n        return\
    \ {p.n + c.n, p.sum + c.sum * p.b + c.n * p.c, c.b * p.b, p.c + c.c * p.b};\n\
    \    }\n\n    static Point rake(const Point &l, const Point &r) { return {l.n\
    \ + r.n, l.sum + r.sum}; }\n\n    static Point add_edge(const Path &d) { return\
    \ {d.n, d.sum}; }\n\n    Path add_vertex(const Point &d, int i) {\n        return\
    \ {d.n + 1, (d.sum + A.at(i)) * parB.at(i) + (d.n + 1) * parC.at(i), parB.at(i),\n\
    \                parC.at(i)};\n    }\n};\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int N, Q;\n    cin >> N >> Q;\n\n    vector<int>\
    \ A(N);\n    for (auto &a : A) cin >> a;\n\n    vector<int> U(N - 1), V(N - 1),\
    \ B(N - 1), C(N - 1);\n    vector<vector<int>> to(N);\n\n    for (int e = 0; e\
    \ < N - 1; ++e) {\n        cin >> U.at(e) >> V.at(e) >> B.at(e) >> C.at(e);\n\
    \        to.at(U.at(e)).push_back(V.at(e));\n        to.at(V.at(e)).push_back(U.at(e));\n\
    \    }\n\n    const static_toptree_structure stts(to, 0);\n\n    vector<mint>\
    \ parB(N, 1);\n    vector<mint> parC(N, 0);\n\n    for (int e = 0; e < N - 1;\
    \ ++e) {\n        int u = U.at(e), v = V.at(e);\n        if (stts.par.at(u) !=\
    \ v) swap(u, v);\n\n        assert(stts.par.at(u) == v);\n\n        parB.at(u)\
    \ = B.at(e);\n        parC.at(u) = C.at(e);\n    }\n\n    tree_dp dp{A, parB,\
    \ parC};\n\n    static_toptree tree(stts, dp);\n\n    while (Q--) {\n        int\
    \ tp;\n        cin >> tp;\n        if (tp == 0) {\n            int w, x;\n   \
    \         cin >> w >> x;\n            dp.A.at(w) = x;\n            tree.set(w);\n\
    \        } else {\n            int e, y, z;\n            cin >> e >> y >> z;\n\
    \n            int u = U.at(e), v = V.at(e);\n            if (stts.par.at(u) !=\
    \ v) swap(u, v);\n            assert(stts.par.at(u) == v);\n\n            dp.parB.at(u)\
    \ = y;\n            dp.parC.at(u) = z;\n            tree.set(u);\n        }\n\n\
    \        cout << tree.all_prod().sum.val() << '\\n';\n    }\n}\n"
  dependsOn:
  - data_structure/static_toptree.hpp
  isVerificationFile: true
  path: data_structure/test/static_toptree.test.cpp
  requiredBy: []
  timestamp: '2024-05-05 13:48:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/static_toptree.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/static_toptree.test.cpp
- /verify/data_structure/test/static_toptree.test.cpp.html
title: data_structure/test/static_toptree.test.cpp
---
