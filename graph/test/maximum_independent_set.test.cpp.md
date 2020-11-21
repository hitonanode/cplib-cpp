---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/maximum_independent_set.hpp
    title: graph/maximum_independent_set.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/maximum_independent_set
    links:
    - https://judge.yosupo.jp/problem/maximum_independent_set
  bundledCode: "#line 1 \"graph/test/maximum_independent_set.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/maximum_independent_set\"\n#line 2 \"graph/maximum_independent_set.hpp\"\
    \n#include <bitset>\n#include <cassert>\n#include <stack>\n#include <vector>\n\
    \n// CUT begin\n// Maximum Independent Set for general graph \uFF08\u6700\u5927\
    \u72EC\u7ACB\u96C6\u5408\uFF09\n// Works with reasonable time complexity when\
    \ N~40\n// Given graph must not have self-edges\n// Verified: <https://judge.yosupo.jp/submission/1864>\n\
    // Reference: <https://www.slideshare.net/wata_orz/ss-12131479>\ntemplate <typename\
    \ E, int BS = 64> struct MaximumIndependentSet {\n    std::vector<std::bitset<BS>>\
    \ conn;\n    int V;               // # of vertices\n    int nret;            //\
    \ Largest possible size of independent set\n    std::bitset<BS> ret; // Result\
    \ is saved here: use (1), don't use (0)\n    std::bitset<BS> _avail;\n    std::bitset<BS>\
    \ _tmp_state;\n\n    void mis_dfs() {\n        bool retry = true;\n        std::stack<int>\
    \ st;\n        while (retry) {\n            retry = false;\n            for (int\
    \ i = _avail._Find_first(); i < V; i = _avail._Find_next(i)) {\n             \
    \   int nb = (_avail & conn[i]).count();\n                if (nb <= 1) {\n   \
    \                 st.emplace(i), _avail.reset(i), _tmp_state.set(i);\n       \
    \             retry = true;\n                    if (nb == 1) {\n            \
    \            int j = (_avail & conn[i])._Find_first();\n                     \
    \   st.emplace(j), _avail.reset(j);\n                    }\n                }\n\
    \            }\n        }\n\n        int t = _tmp_state.count();\n        if (t\
    \ > nret) nret = t, ret = _tmp_state;\n\n        int d = -1, n = -1;\n       \
    \ for (int i = _avail._Find_first(); i < V; i = _avail._Find_next(i)) {\n    \
    \        int c = (_avail & conn[i]).count();\n            if (c > d) d = c, n\
    \ = i;\n        }\n\n        if (d > 0) {\n            std::bitset<BS> nxt = _avail\
    \ & conn[n];\n            _avail.reset(n);\n            mis_dfs();\n         \
    \   _tmp_state.set(n);\n            _avail &= ~nxt;\n            mis_dfs();\n\
    \            _avail |= nxt;\n            _avail.set(n);\n            _tmp_state.reset(n);\n\
    \        }\n\n        while (st.size()) {\n            int i = st.top();\n   \
    \         _avail.set(i);\n            _tmp_state.reset(i);\n            st.pop();\n\
    \        }\n    }\n    MaximumIndependentSet(const E &e) : conn(e.size()), V(e.size()),\
    \ nret(-1) {\n        assert(V <= BS);\n        for (int i = 0; i < V; i++)\n\
    \            for (auto &j : e[i])\n                if (i != j) conn[i].set(j),\
    \ conn[j].set(i);\n        for (int i = 0; i < V; i++) _avail.set(i);\n      \
    \  _tmp_state.reset();\n        mis_dfs();\n    }\n};\n\n// A little fast implementation\
    \ of MaximumIndependentSet\n// by substituting long long int's bit for `ret` &\
    \ `_tmp_state`\n// Requirement: V <= 64\ntemplate <typename E> struct MaximumIndependentSet_Intbased\
    \ {\n    std::vector<long long> conn;\n    int V;         // # of vertices\n \
    \   int nret;      // Largest possible size of independent set\n    long long\
    \ ret; // Result is saved here: use (1), don't use (0)\n    long long _avail;\n\
    \    long long _tmp_state;\n\n    void mis_dfs() {\n        bool retry = true;\n\
    \        std::stack<int> st;\n        while (retry) {\n            retry = false;\n\
    \            for (int i = 0; i < V; i++)\n                if (_avail & (1LL <<\
    \ i)) {\n                    int nb = __builtin_popcountll(_avail & conn[i]);\n\
    \                    if (nb <= 1) {\n                        st.emplace(i), _avail\
    \ -= 1LL << i, _tmp_state |= 1LL << i;\n                        retry = true;\n\
    \                        if (nb == 1) {\n                            int j = __builtin_ctzll(_avail\
    \ & conn[i]);\n                            st.emplace(j), _avail &= ~(1LL << j);\n\
    \                        }\n                    }\n                }\n       \
    \ }\n\n        int t = __builtin_popcountll(_tmp_state);\n        if (t > nret)\
    \ nret = t, ret = _tmp_state;\n\n        int d = -1, n = -1;\n        for (int\
    \ i = 0; i < V; i++)\n            if (_avail & (1LL << i)) {\n               \
    \ int c = __builtin_popcountll(_avail & conn[i]);\n                if (c > d)\
    \ d = c, n = i;\n            }\n\n        if (d > 0) {\n            long long\
    \ nxt = _avail & conn[n];\n            _avail -= 1LL << n;\n            mis_dfs();\n\
    \            _tmp_state |= 1LL << n;\n            _avail &= ~nxt;\n          \
    \  mis_dfs();\n            _avail |= nxt;\n            _avail |= 1LL << n;\n \
    \           _tmp_state &= ~(1LL << n);\n        }\n\n        while (st.size())\
    \ {\n            int i = st.top();\n            _avail |= 1LL << i;\n        \
    \    _tmp_state &= ~(1LL << i);\n            st.pop();\n        }\n    }\n   \
    \ MaximumIndependentSet_Intbased(const E &e) : conn(e.size()), V(e.size()), nret(-1),\
    \ _avail((1LL << V) - 1), _tmp_state(0) {\n        assert(V <= 63);\n        for\
    \ (int i = 0; i < V; i++)\n            for (auto &j : e[i])\n                if\
    \ (i != j) conn[i] |= 1LL << j, conn[j] |= 1LL << i;\n        mis_dfs();\n   \
    \ }\n};\n#line 3 \"graph/test/maximum_independent_set.test.cpp\"\n\n#line 5 \"\
    graph/test/maximum_independent_set.test.cpp\"\n#include <iostream>\n#line 7 \"\
    graph/test/maximum_independent_set.test.cpp\"\n\nint main() {\n    int N, M;\n\
    \    std::cin >> N >> M;\n    std::vector<std::vector<int>> edges(N);\n    while\
    \ (M--) {\n        int u, v;\n        std::cin >> u >> v;\n        edges[u].emplace_back(v);\n\
    \        edges[v].emplace_back(u);\n    }\n    MaximumIndependentSet<decltype(edges),\
    \ 40> mis(edges);\n    MaximumIndependentSet_Intbased<decltype(edges)> misfast(edges);\n\
    \    std::cout << mis.ret.count() << \"\\n\";\n    for (int i = 0; i < N; i++)\
    \ {\n        // Check whether two implementation gives same results\n        assert(mis.ret[i]\
    \ == ((misfast.ret >> i) & 1));\n\n        if (mis.ret[i]) std::cout << i << \"\
    \ \";\n    }\n    std::cout << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\
    \n#include \"../maximum_independent_set.hpp\"\n\n#include <cassert>\n#include\
    \ <iostream>\n#include <vector>\n\nint main() {\n    int N, M;\n    std::cin >>\
    \ N >> M;\n    std::vector<std::vector<int>> edges(N);\n    while (M--) {\n  \
    \      int u, v;\n        std::cin >> u >> v;\n        edges[u].emplace_back(v);\n\
    \        edges[v].emplace_back(u);\n    }\n    MaximumIndependentSet<decltype(edges),\
    \ 40> mis(edges);\n    MaximumIndependentSet_Intbased<decltype(edges)> misfast(edges);\n\
    \    std::cout << mis.ret.count() << \"\\n\";\n    for (int i = 0; i < N; i++)\
    \ {\n        // Check whether two implementation gives same results\n        assert(mis.ret[i]\
    \ == ((misfast.ret >> i) & 1));\n\n        if (mis.ret[i]) std::cout << i << \"\
    \ \";\n    }\n    std::cout << \"\\n\";\n}\n"
  dependsOn:
  - graph/maximum_independent_set.hpp
  isVerificationFile: true
  path: graph/test/maximum_independent_set.test.cpp
  requiredBy: []
  timestamp: '2020-11-21 18:08:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/maximum_independent_set.test.cpp
layout: document
redirect_from:
- /verify/graph/test/maximum_independent_set.test.cpp
- /verify/graph/test/maximum_independent_set.test.cpp.html
title: graph/test/maximum_independent_set.test.cpp
---
