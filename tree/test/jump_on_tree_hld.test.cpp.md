---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/heavy_light_decomposition.hpp
    title: "Heavy-light decomposition \uFF08HLD, \u6728\u306E\u91CD\u8EFD\u5206\u89E3\
      \uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/jump_on_tree
    links:
    - https://judge.yosupo.jp/problem/jump_on_tree
  bundledCode: "#line 1 \"tree/test/jump_on_tree_hld.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/jump_on_tree\"\n#line 2 \"tree/heavy_light_decomposition.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include <queue>\n\
    #include <stack>\n#include <utility>\n#include <vector>\n\n// Heavy-Light Decomposition\
    \ of trees\n// Based on http://beet-aizu.hatenablog.com/entry/2017/12/12/235950\n\
    struct HeavyLightDecomposition {\n    int V;\n    int k;\n    int nb_heavy_path;\n\
    \    std::vector<std::vector<int>> e;\n    std::vector<int> par;         // par[i]\
    \ = parent of vertex i (Default: -1)\n    std::vector<int> depth;       // depth[i]\
    \ = distance between root and vertex i\n    std::vector<int> subtree_sz;  // subtree_sz[i]\
    \ = size of subtree whose root is i\n    std::vector<int> heavy_child; // heavy_child[i]\
    \ = child of vertex i on heavy path (Default: -1)\n    std::vector<int> tree_id;\
    \     // tree_id[i] = id of tree vertex i belongs to\n    std::vector<int> aligned_id,\n\
    \        aligned_id_inv;    // aligned_id[i] =  aligned id for vertex i (consecutive\
    \ on heavy edges)\n    std::vector<int> head; // head[i] = id of vertex on heavy\
    \ path of vertex i, nearest to root\n    std::vector<int> head_ids;      // consist\
    \ of head vertex id's\n    std::vector<int> heavy_path_id; // heavy_path_id[i]\
    \ = heavy_path_id for vertex [i]\n\n    HeavyLightDecomposition(int sz = 0)\n\
    \        : V(sz), k(0), nb_heavy_path(0), e(sz), par(sz), depth(sz), subtree_sz(sz),\
    \ heavy_child(sz),\n          tree_id(sz, -1), aligned_id(sz), aligned_id_inv(sz),\
    \ head(sz), heavy_path_id(sz, -1) {}\n    void add_edge(int u, int v) {\n    \
    \    e[u].emplace_back(v);\n        e[v].emplace_back(u);\n    }\n\n    void _build_dfs(int\
    \ root) {\n        std::stack<std::pair<int, int>> st;\n        par[root] = -1;\n\
    \        depth[root] = 0;\n        st.emplace(root, 0);\n        while (!st.empty())\
    \ {\n            int now = st.top().first;\n            int &i = st.top().second;\n\
    \            if (i < (int)e[now].size()) {\n                int nxt = e[now][i++];\n\
    \                if (nxt == par[now]) continue;\n                par[nxt] = now;\n\
    \                depth[nxt] = depth[now] + 1;\n                st.emplace(nxt,\
    \ 0);\n            } else {\n                st.pop();\n                int max_sub_sz\
    \ = 0;\n                subtree_sz[now] = 1;\n                heavy_child[now]\
    \ = -1;\n                for (auto nxt : e[now]) {\n                    if (nxt\
    \ == par[now]) continue;\n                    subtree_sz[now] += subtree_sz[nxt];\n\
    \                    if (max_sub_sz < subtree_sz[nxt])\n                     \
    \   max_sub_sz = subtree_sz[nxt], heavy_child[now] = nxt;\n                }\n\
    \            }\n        }\n    }\n\n    void _build_bfs(int root, int tree_id_now)\
    \ {\n        std::queue<int> q({root});\n        while (!q.empty()) {\n      \
    \      int h = q.front();\n            q.pop();\n            head_ids.emplace_back(h);\n\
    \            for (int now = h; now != -1; now = heavy_child[now]) {\n        \
    \        tree_id[now] = tree_id_now;\n                aligned_id[now] = k++;\n\
    \                aligned_id_inv[aligned_id[now]] = now;\n                heavy_path_id[now]\
    \ = nb_heavy_path;\n                head[now] = h;\n                for (int nxt\
    \ : e[now])\n                    if (nxt != par[now] and nxt != heavy_child[now])\
    \ q.push(nxt);\n            }\n            nb_heavy_path++;\n        }\n    }\n\
    \n    void build(std::vector<int> roots = {0}) {\n        int tree_id_now = 0;\n\
    \        for (auto r : roots) _build_dfs(r), _build_bfs(r, tree_id_now++);\n \
    \   }\n\n    template <class T> std::vector<T> segtree_rearrange(const std::vector<T>\
    \ &data) const {\n        assert(int(data.size()) == V);\n        std::vector<T>\
    \ ret;\n        ret.reserve(V);\n        for (int i = 0; i < V; i++) ret.emplace_back(data[aligned_id_inv[i]]);\n\
    \        return ret;\n    }\n\n    // query for vertices on path [u, v] (INCLUSIVE)\n\
    \    void\n    for_each_vertex(int u, int v, const std::function<void(int ancestor,\
    \ int descendant)> &f) const {\n        while (true) {\n            if (aligned_id[u]\
    \ > aligned_id[v]) std::swap(u, v);\n            f(std::max(aligned_id[head[v]],\
    \ aligned_id[u]), aligned_id[v]);\n            if (head[u] == head[v]) break;\n\
    \            v = par[head[v]];\n        }\n    }\n\n    void for_each_vertex_noncommutative(\n\
    \        int from, int to, const std::function<void(int ancestor, int descendant)>\
    \ &fup,\n        const std::function<void(int ancestor, int descendant)> &fdown)\
    \ const {\n        int u = from, v = to;\n        const int lca = lowest_common_ancestor(u,\
    \ v), dlca = depth[lca];\n        while (u >= 0 and depth[u] > dlca) {\n     \
    \       const int p = (depth[head[u]] > dlca ? head[u] : lca);\n            fup(aligned_id[p]\
    \ + (p == lca), aligned_id[u]), u = par[p];\n        }\n        static std::vector<std::pair<int,\
    \ int>> lrs;\n        int sz = 0;\n        while (v >= 0 and depth[v] >= dlca)\
    \ {\n            const int p = (depth[head[v]] >= dlca ? head[v] : lca);\n   \
    \         if (int(lrs.size()) == sz) lrs.emplace_back(0, 0);\n            lrs.at(sz++)\
    \ = {p, v}, v = par.at(p);\n        }\n        while (sz--) fdown(aligned_id[lrs.at(sz).first],\
    \ aligned_id[lrs.at(sz).second]);\n    }\n\n    // query for edges on path [u,\
    \ v]\n    void for_each_edge(int u, int v, const std::function<void(int, int)>\
    \ &f) const {\n        while (true) {\n            if (aligned_id[u] > aligned_id[v])\
    \ std::swap(u, v);\n            if (head[u] != head[v]) {\n                f(aligned_id[head[v]],\
    \ aligned_id[v]);\n                v = par[head[v]];\n            } else {\n \
    \               if (u != v) f(aligned_id[u] + 1, aligned_id[v]);\n           \
    \     break;\n            }\n        }\n    }\n\n    // lowest_common_ancestor:\
    \ O(log V)\n    int lowest_common_ancestor(int u, int v) const {\n        assert(tree_id[u]\
    \ == tree_id[v] and tree_id[u] >= 0);\n        while (true) {\n            if\
    \ (aligned_id[u] > aligned_id[v]) std::swap(u, v);\n            if (head[u] ==\
    \ head[v]) return u;\n            v = par[head[v]];\n        }\n    }\n\n    int\
    \ distance(int u, int v) const {\n        assert(tree_id[u] == tree_id[v] and\
    \ tree_id[u] >= 0);\n        return depth[u] + depth[v] - 2 * depth[lowest_common_ancestor(u,\
    \ v)];\n    }\n\n    // Level ancestor, O(log V)\n    // if k-th parent is out\
    \ of range, return -1\n    int kth_parent(int v, int k) const {\n        if (k\
    \ < 0) return -1;\n        while (v >= 0) {\n            int h = head.at(v), len\
    \ = depth.at(v) - depth.at(h);\n            if (k <= len) return aligned_id_inv.at(aligned_id.at(v)\
    \ - k);\n            k -= len + 1, v = par.at(h);\n        }\n        return -1;\n\
    \    }\n\n    // Jump on tree, O(log V)\n    int s_to_t_by_k_steps(int s, int\
    \ t, int k) const {\n        if (k < 0) return -1;\n        if (k == 0) return\
    \ s;\n        int lca = lowest_common_ancestor(s, t);\n        if (k <= depth.at(s)\
    \ - depth.at(lca)) return kth_parent(s, k);\n        return kth_parent(t, depth.at(s)\
    \ + depth.at(t) - depth.at(lca) * 2 - k);\n    }\n};\n#line 3 \"tree/test/jump_on_tree_hld.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, Q;\n    cin >> N >> Q;\n    HeavyLightDecomposition\
    \ tree(N);\n    for (int e = 0; e < N - 1; ++e) {\n        int a, b;\n       \
    \ cin >> a >> b;\n        tree.add_edge(a, b);\n    }\n\n    tree.build({0});\n\
    \n    while (Q--) {\n        int s, t, i;\n        cin >> s >> t >> i;\n     \
    \   cout << tree.s_to_t_by_k_steps(s, t, i) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/jump_on_tree\"\n#include\
    \ \"../heavy_light_decomposition.hpp\"\n#include <iostream>\nusing namespace std;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N,\
    \ Q;\n    cin >> N >> Q;\n    HeavyLightDecomposition tree(N);\n    for (int e\
    \ = 0; e < N - 1; ++e) {\n        int a, b;\n        cin >> a >> b;\n        tree.add_edge(a,\
    \ b);\n    }\n\n    tree.build({0});\n\n    while (Q--) {\n        int s, t, i;\n\
    \        cin >> s >> t >> i;\n        cout << tree.s_to_t_by_k_steps(s, t, i)\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - tree/heavy_light_decomposition.hpp
  isVerificationFile: true
  path: tree/test/jump_on_tree_hld.test.cpp
  requiredBy: []
  timestamp: '2023-03-12 17:40:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/jump_on_tree_hld.test.cpp
layout: document
redirect_from:
- /verify/tree/test/jump_on_tree_hld.test.cpp
- /verify/tree/test/jump_on_tree_hld.test.cpp.html
title: tree/test/jump_on_tree_hld.test.cpp
---
