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
    #include <cassert>\n#include <utility>\n#include <vector>\n\n// Rerooting\n//\
    \ Reference:\n// - https://atcoder.jp/contests/abc222/editorial/2749\n// - https://null-mn.hatenablog.com/entry/2020/04/14/124151\n\
    template <class Edge, class St, class Ch, Ch (*merge)(Ch, Ch), Ch (*f)(St, int,\
    \ Edge),\n          St (*g)(Ch, int), Ch (*e)()>\nstruct rerooting {\n    int\
    \ n_;\n    std::vector<int> par, visited;\n    std::vector<std::vector<std::pair<int,\
    \ Edge>>> to;\n    std::vector<St> dp_subtree;\n    std::vector<St> dp_par;\n\
    \    std::vector<St> dpall;\n    rerooting(const std::vector<std::vector<std::pair<int,\
    \ Edge>>> &to_)\n        : n_(to_.size()), par(n_, -1), visited(n_, 0), to(to_)\
    \ {\n        for (int i = 0; i < n_; ++i) dp_subtree.push_back(g(e(), i));\n \
    \       dp_par = dpall = dp_subtree;\n    }\n\n    void run_connected(int root)\
    \ {\n        if (visited[root]) return;\n        visited[root] = 1;\n        std::vector<int>\
    \ visorder{root};\n\n        for (int t = 0; t < int(visorder.size()); ++t) {\n\
    \            int now = visorder[t];\n            for (const auto &edge : to[now])\
    \ {\n                int nxt = edge.first;\n                if (visited[nxt])\
    \ continue;\n                visorder.push_back(nxt);\n                visited[nxt]\
    \ = 1;\n                par[nxt] = now;\n            }\n        }\n\n        for\
    \ (int t = int(visorder.size()) - 1; t >= 0; --t) {\n            int now = visorder[t];\n\
    \            Ch ch = e();\n            for (const auto &edge : to[now]) {\n  \
    \              int nxt = edge.first;\n                if (nxt == par[now]) continue;\n\
    \                ch = merge(ch, f(dp_subtree[nxt], nxt, edge.second));\n     \
    \       }\n            dp_subtree[now] = g(ch, now);\n        }\n\n        std::vector<Ch>\
    \ left;\n        for (int now : visorder) {\n            int m = int(to[now].size());\n\
    \            left.assign(m + 1, e());\n            for (int j = 0; j < m; j++)\
    \ {\n                int nxt = to[now][j].first;\n                const St &st\
    \ = (nxt == par[now] ? dp_par[now] : dp_subtree[nxt]);\n                left[j\
    \ + 1] = merge(left[j], f(st, nxt, to[now][j].second));\n            }\n     \
    \       dpall[now] = g(left.back(), now);\n\n            Ch rprod = e();\n   \
    \         for (int j = m - 1; j >= 0; --j) {\n                int nxt = to[now][j].first;\n\
    \                if (nxt != par[now]) dp_par[nxt] = g(merge(left[j], rprod), now);\n\
    \n                const St &st = (nxt == par[now] ? dp_par[now] : dp_subtree[nxt]);\n\
    \                rprod = merge(f(st, nxt, to[now][j].second), rprod);\n      \
    \      }\n        }\n    }\n\n    void run() {\n        for (int i = 0; i < n_;\
    \ ++i) {\n            if (!visited[i]) run_connected(i);\n        }\n    }\n};\n\
    /* Template:\nstruct Subtree {};\nstruct Child {};\nstruct Edge {};\nChild e()\
    \ { return Child(); }\nChild merge(Child x, Child y) { return Child(); }\nChild\
    \ f(Subtree x, int ch_id, Edge edge) { return Child(); }\nSubtree g(Child x, int\
    \ v_id) { return Subtree(); }\n\nvector<vector<pair<int, Edge>>> to;\nrerooting<Edge,\
    \ Subtree, Child, merge, f, g, e> tree(to);\n*/\n#line 3 \"tree/test/rerooting.yuki1718.test.cpp\"\
    \n#include <iostream>\n#include <tuple>\n#line 6 \"tree/test/rerooting.yuki1718.test.cpp\"\
    \nusing namespace std;\n\nvector<int> inD;\n\nstruct Subtree {\n    bool exist;\n\
    \    int oneway, round;\n};\nstruct Child {\n    bool exist;\n    int oneway,\
    \ round;\n};\nChild e() { return {false, 0, 0}; }\n\nChild merge(Child x, Child\
    \ y) {\n    if (!x.exist) return y;\n    if (!y.exist) return x;\n    return Child{true,\
    \ min(x.oneway + y.round, y.oneway + x.round), x.round + y.round};\n}\n\nChild\
    \ f(Subtree x, int, tuple<>) {\n    if (!x.exist) return e();\n    return {true,\
    \ x.oneway + 1, x.round + 2};\n}\n\nSubtree g(Child x, int v) {\n    if (x.exist\
    \ or inD[v]) return {true, x.oneway, x.round};\n    return {false, 0, 0};\n}\n\
    \nint main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    int\
    \ N, K;\n    cin >> N >> K;\n    vector<vector<pair<int, tuple<>>>> to(N);\n \
    \   for (int e = 0; e < N - 1; e++) {\n        int u, v;\n        cin >> u >>\
    \ v;\n        u--, v--;\n        to[u].emplace_back(v, make_tuple());\n      \
    \  to[v].emplace_back(u, make_tuple());\n    }\n    inD.assign(N, 0);\n    while\
    \ (K--) {\n        int d;\n        cin >> d;\n        inD[d - 1] = 1;\n    }\n\
    \    rerooting<tuple<>, Subtree, Child, merge, f, g, e> tree(to);\n    tree.run();\n\
    \    for (auto x : tree.dpall) cout << x.oneway << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1718\"\n#include \"../rerooting.hpp\"\
    \n#include <iostream>\n#include <tuple>\n#include <vector>\nusing namespace std;\n\
    \nvector<int> inD;\n\nstruct Subtree {\n    bool exist;\n    int oneway, round;\n\
    };\nstruct Child {\n    bool exist;\n    int oneway, round;\n};\nChild e() { return\
    \ {false, 0, 0}; }\n\nChild merge(Child x, Child y) {\n    if (!x.exist) return\
    \ y;\n    if (!y.exist) return x;\n    return Child{true, min(x.oneway + y.round,\
    \ y.oneway + x.round), x.round + y.round};\n}\n\nChild f(Subtree x, int, tuple<>)\
    \ {\n    if (!x.exist) return e();\n    return {true, x.oneway + 1, x.round +\
    \ 2};\n}\n\nSubtree g(Child x, int v) {\n    if (x.exist or inD[v]) return {true,\
    \ x.oneway, x.round};\n    return {false, 0, 0};\n}\n\nint main() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n    int N, K;\n    cin >> N >> K;\n    vector<vector<pair<int,\
    \ tuple<>>>> to(N);\n    for (int e = 0; e < N - 1; e++) {\n        int u, v;\n\
    \        cin >> u >> v;\n        u--, v--;\n        to[u].emplace_back(v, make_tuple());\n\
    \        to[v].emplace_back(u, make_tuple());\n    }\n    inD.assign(N, 0);\n\
    \    while (K--) {\n        int d;\n        cin >> d;\n        inD[d - 1] = 1;\n\
    \    }\n    rerooting<tuple<>, Subtree, Child, merge, f, g, e> tree(to);\n   \
    \ tree.run();\n    for (auto x : tree.dpall) cout << x.oneway << '\\n';\n}\n"
  dependsOn:
  - tree/rerooting.hpp
  isVerificationFile: true
  path: tree/test/rerooting.yuki1718.test.cpp
  requiredBy: []
  timestamp: '2021-10-23 00:38:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/rerooting.yuki1718.test.cpp
layout: document
redirect_from:
- /verify/tree/test/rerooting.yuki1718.test.cpp
- /verify/tree/test/rerooting.yuki1718.test.cpp.html
title: tree/test/rerooting.yuki1718.test.cpp
---