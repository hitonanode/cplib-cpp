---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/rerooting.hpp
    title: "Rerooting \uFF08\u5168\u65B9\u4F4D\u6728 DP\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1718
    links:
    - https://yukicoder.me/problems/no/1718
  bundledCode: "#line 1 \"tree/test/rerooting.yuki1718.test.cpp\"\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/no/1718\"\n#line 2 \"tree/rerooting.hpp\"\n\
    #include <cassert>\n#include <cstdlib>\n#include <utility>\n#include <vector>\n\
    \n// Rerooting\n// Reference:\n// - https://atcoder.jp/contests/abc222/editorial/2749\n\
    // - https://null-mn.hatenablog.com/entry/2020/04/14/124151\ntemplate <class Edge,\
    \ class Subtree, class Children, Children (*rake)(Children, Children),\n     \
    \     Children (*add_edge)(Subtree, int, Edge), Subtree (*add_vertex)(Children,\
    \ int),\n          Children (*e)()>\nstruct rerooting {\n    int n_;\n    std::vector<int>\
    \ par, visited;\n    std::vector<std::vector<std::pair<int, Edge>>> to;\n\n  \
    \  // dp_subtree[i] = DP(root=i, edge (i, par[i]) is removed).\n    std::vector<Subtree>\
    \ dp_subtree;\n\n    // dp_par[i] = DP(root=par[i], edge (i, par[i]) is removed).\
    \ dp_par[root] is meaningless.\n    std::vector<Subtree> dp_par;\n\n    // dpall[i]\
    \ = DP(root=i, all edges exist).\n    std::vector<Subtree> dpall;\n\n    rerooting(const\
    \ std::vector<std::vector<std::pair<int, Edge>>> &to_)\n        : n_(to_.size()),\
    \ par(n_, -1), visited(n_, 0), to(to_) {\n        for (int i = 0; i < n_; ++i)\
    \ dp_subtree.push_back(add_vertex(e(), i));\n        dp_par = dpall = dp_subtree;\n\
    \    }\n\n    void run_connected(int root) {\n        if (visited.at(root)) return;\n\
    \        visited.at(root) = 1;\n        std::vector<int> visorder{root};\n\n \
    \       for (int t = 0; t < int(visorder.size()); ++t) {\n            int now\
    \ = visorder.at(t);\n            for (const auto &[nxt, _] : to[now]) {\n    \
    \            if (visited.at(nxt)) continue;\n                visorder.push_back(nxt);\n\
    \                visited.at(nxt) = 1;\n                par.at(nxt) = now;\n  \
    \          }\n        }\n\n        for (int t = int(visorder.size()) - 1; t >=\
    \ 0; --t) {\n            const int now = visorder.at(t);\n            Children\
    \ ch = e();\n            for (const auto &[nxt, edge] : to.at(now)) {\n      \
    \          if (nxt != par.at(now)) ch = rake(ch, add_edge(dp_subtree.at(nxt),\
    \ nxt, edge));\n            }\n            dp_subtree.at(now) = add_vertex(ch,\
    \ now);\n        }\n\n        std::vector<Children> left;\n        for (int now\
    \ : visorder) {\n            const int m = to.at(now).size();\n            left.assign(m\
    \ + 1, e());\n            for (int j = 0; j < m; j++) {\n                const\
    \ auto &[nxt, edge] = to.at(now).at(j);\n                const Subtree &st = (nxt\
    \ == par.at(now) ? dp_par.at(now) : dp_subtree.at(nxt));\n                left.at(j\
    \ + 1) = rake(left.at(j), add_edge(st, nxt, edge));\n            }\n         \
    \   dpall.at(now) = add_vertex(left.back(), now);\n\n            Children rprod\
    \ = e();\n            for (int j = m - 1; j >= 0; --j) {\n                const\
    \ auto &[nxt, edge] = to.at(now).at(j);\n\n                if (nxt != par.at(now))\
    \ dp_par.at(nxt) = add_vertex(rake(left.at(j), rprod), now);\n\n             \
    \   const Subtree &st = (nxt == par.at(now) ? dp_par.at(now) : dp_subtree.at(nxt));\n\
    \                rprod = rake(add_edge(st, nxt, edge), rprod);\n            }\n\
    \        }\n    }\n\n    void run() {\n        for (int i = 0; i < n_; ++i) {\n\
    \            if (!visited.at(i)) run_connected(i);\n        }\n    }\n\n    const\
    \ Subtree &get_subtree(int root_, int par_) const {\n        if (par_ < 0) return\
    \ dpall.at(root_);\n        if (par.at(root_) == par_) return dp_subtree.at(root_);\n\
    \        if (par.at(par_) == root_) return dp_par.at(par_);\n        std::exit(1);\n\
    \    }\n};\n/* Template:\nstruct Subtree {};\nstruct Children {};\nstruct Edge\
    \ {};\nChildren e() { return Children(); }\nChildren rake(Children x, Children\
    \ y) { return Children(); }\nChildren add_edge(Subtree x, int ch_id, Edge edge)\
    \ { return Children(); }\nSubtree add_vertex(Children x, int v_id) { return Subtree();\
    \ }\n\nvector<vector<pair<int, Edge>>> to;\nrerooting<Edge, Subtree, Children,\
    \ rake, add_edge, add_vertex, e> tree(to);\n*/\n#line 3 \"tree/test/rerooting.yuki1718.test.cpp\"\
    \n#include <iostream>\n#include <tuple>\n#line 6 \"tree/test/rerooting.yuki1718.test.cpp\"\
    \nusing namespace std;\n\nvector<int> inD;\n\nstruct Subtree {\n    bool exist;\n\
    \    int oneway, round;\n};\nstruct Children {\n    bool exist;\n    int oneway,\
    \ round;\n};\nChildren e() { return {false, 0, 0}; }\n\nChildren merge(Children\
    \ x, Children y) {\n    if (!x.exist) return y;\n    if (!y.exist) return x;\n\
    \    return Children{true, min(x.oneway + y.round, y.oneway + x.round), x.round\
    \ + y.round};\n}\n\nChildren add_edge(Subtree x, int, tuple<>) {\n    if (!x.exist)\
    \ return e();\n    return {true, x.oneway + 1, x.round + 2};\n}\n\nSubtree add_vertex(Children\
    \ x, int v) {\n    if (x.exist or inD[v]) return {true, x.oneway, x.round};\n\
    \    return {false, 0, 0};\n}\n\nint main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\
    \    int N, K;\n    cin >> N >> K;\n    vector<vector<pair<int, tuple<>>>> to(N);\n\
    \    for (int e = 0; e < N - 1; e++) {\n        int u, v;\n        cin >> u >>\
    \ v;\n        u--, v--;\n        to[u].emplace_back(v, make_tuple());\n      \
    \  to[v].emplace_back(u, make_tuple());\n    }\n    inD.assign(N, 0);\n    while\
    \ (K--) {\n        int d;\n        cin >> d;\n        inD[d - 1] = 1;\n    }\n\
    \    rerooting<tuple<>, Subtree, Children, merge, add_edge, add_vertex, e> tree(to);\n\
    \    tree.run();\n    for (auto x : tree.dpall) cout << x.oneway << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1718\"\n#include \"../rerooting.hpp\"\
    \n#include <iostream>\n#include <tuple>\n#include <vector>\nusing namespace std;\n\
    \nvector<int> inD;\n\nstruct Subtree {\n    bool exist;\n    int oneway, round;\n\
    };\nstruct Children {\n    bool exist;\n    int oneway, round;\n};\nChildren e()\
    \ { return {false, 0, 0}; }\n\nChildren merge(Children x, Children y) {\n    if\
    \ (!x.exist) return y;\n    if (!y.exist) return x;\n    return Children{true,\
    \ min(x.oneway + y.round, y.oneway + x.round), x.round + y.round};\n}\n\nChildren\
    \ add_edge(Subtree x, int, tuple<>) {\n    if (!x.exist) return e();\n    return\
    \ {true, x.oneway + 1, x.round + 2};\n}\n\nSubtree add_vertex(Children x, int\
    \ v) {\n    if (x.exist or inD[v]) return {true, x.oneway, x.round};\n    return\
    \ {false, 0, 0};\n}\n\nint main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\
    \    int N, K;\n    cin >> N >> K;\n    vector<vector<pair<int, tuple<>>>> to(N);\n\
    \    for (int e = 0; e < N - 1; e++) {\n        int u, v;\n        cin >> u >>\
    \ v;\n        u--, v--;\n        to[u].emplace_back(v, make_tuple());\n      \
    \  to[v].emplace_back(u, make_tuple());\n    }\n    inD.assign(N, 0);\n    while\
    \ (K--) {\n        int d;\n        cin >> d;\n        inD[d - 1] = 1;\n    }\n\
    \    rerooting<tuple<>, Subtree, Children, merge, add_edge, add_vertex, e> tree(to);\n\
    \    tree.run();\n    for (auto x : tree.dpall) cout << x.oneway << '\\n';\n}\n"
  dependsOn:
  - tree/rerooting.hpp
  isVerificationFile: true
  path: tree/test/rerooting.yuki1718.test.cpp
  requiredBy: []
  timestamp: '2024-05-05 15:10:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/rerooting.yuki1718.test.cpp
layout: document
redirect_from:
- /verify/tree/test/rerooting.yuki1718.test.cpp
- /verify/tree/test/rerooting.yuki1718.test.cpp.html
title: tree/test/rerooting.yuki1718.test.cpp
---
