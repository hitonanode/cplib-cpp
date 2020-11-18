---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: graph/strongly_connected_components_bitset.hpp
    title: graph/strongly_connected_components_bitset.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C
  bundledCode: "#line 1 \"graph/test/strongly_connected_components_bitset.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C\"\
    \n#line 2 \"graph/strongly_connected_components_bitset.hpp\"\n#include <bitset>\n\
    #include <vector>\n\n// CUT begin\n// Directed graph library to find strongly\
    \ connected components \uFF08\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3\uFF09\n\
    // 0-indexed directed graph\n// - using std::bitset\n// - Fast for dense graphs\n\
    // Complexity: O(V^2/64)\n// Verified: CF1268D <https://codeforces.com/contest/1268/submission/68125495>\n\
    template<int VMAX>\nstruct DirectedGraphSCC64 {\n    int V;\n    const std::vector<std::bitset<VMAX>>\
    \ &e, &einv;\n    std::vector<int> vs, cmp;\n    std::bitset<VMAX> unvisited;\n\
    \    int scc_num;\n    void _dfs(int now) {\n        unvisited.reset(now);\n \
    \       while (true) {\n            int nxt = (unvisited & e[now])._Find_first();\n\
    \            if (nxt >= V) break;\n            _dfs(nxt);\n        }\n       \
    \ vs.push_back(now);\n    }\n    void _rdfs(int now, int k) {\n        unvisited.reset(now);\n\
    \        cmp[now] = k;\n        while (true) {\n            int nxt = (unvisited\
    \ & einv[now])._Find_first();\n            if (nxt >= V) break;\n            _rdfs(nxt,\
    \ k);\n        }\n    }\n    // Detect strongly connected components and return\
    \ # of them.\n    // Also, assign each vertex `v` the scc id `cmp[v]` (0-indexed)\n\
    \    DirectedGraphSCC64(const std::vector<std::bitset<VMAX>> &edge, const std::vector<std::bitset<VMAX>>\
    \ &edge_inv)\n        : V(edge.size()), e(edge), einv(edge_inv), cmp(edge.size()),\
    \ scc_num(0)\n    {\n        unvisited.set();\n        for (int i = 0; i < V;\
    \ i++) if (unvisited[i]) _dfs(i);\n        unvisited.set();\n        for (int\
    \ i = (int)vs.size() - 1; i >= 0; i--) if (unvisited[vs[i]]) {\n            _rdfs(vs[i],\
    \ scc_num++);\n        }\n    }\n};\n#line 3 \"graph/test/strongly_connected_components_bitset.test.cpp\"\
    \n\n#include <cassert>\n#include <stdio.h>\nconstexpr int VMAX = 10000;\nint main()\
    \ {\n    int V, E;\n    scanf(\"%d %d\", &V, &E);\n    assert(V <= VMAX);\n  \
    \  std::vector<std::bitset<VMAX>> e(V), einv(V);\n    while (E--) {\n        int\
    \ s, t;\n        scanf(\"%d %d\", &s, &t);\n        e[s][t] = einv[t][s] = 1;\n\
    \    }\n    DirectedGraphSCC64<VMAX> graph(e, einv);\n\n    int Q;\n    scanf(\"\
    %d\", &Q);\n    while (Q--) {\n        int u, v;\n        scanf(\"%d %d\", &u,\
    \ &v);\n        printf(\"%d\\n\", graph.cmp[u] == graph.cmp[v]);\n    }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C\"\
    \n#include \"graph/strongly_connected_components_bitset.hpp\"\n\n#include <cassert>\n\
    #include <stdio.h>\nconstexpr int VMAX = 10000;\nint main() {\n    int V, E;\n\
    \    scanf(\"%d %d\", &V, &E);\n    assert(V <= VMAX);\n    std::vector<std::bitset<VMAX>>\
    \ e(V), einv(V);\n    while (E--) {\n        int s, t;\n        scanf(\"%d %d\"\
    , &s, &t);\n        e[s][t] = einv[t][s] = 1;\n    }\n    DirectedGraphSCC64<VMAX>\
    \ graph(e, einv);\n\n    int Q;\n    scanf(\"%d\", &Q);\n    while (Q--) {\n \
    \       int u, v;\n        scanf(\"%d %d\", &u, &v);\n        printf(\"%d\\n\"\
    , graph.cmp[u] == graph.cmp[v]);\n    }\n}\n"
  dependsOn:
  - graph/strongly_connected_components_bitset.hpp
  isVerificationFile: true
  path: graph/test/strongly_connected_components_bitset.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: graph/test/strongly_connected_components_bitset.test.cpp
layout: document
redirect_from:
- /verify/graph/test/strongly_connected_components_bitset.test.cpp
- /verify/graph/test/strongly_connected_components_bitset.test.cpp.html
title: graph/test/strongly_connected_components_bitset.test.cpp
---
