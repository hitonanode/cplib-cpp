---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/extended_block_cut_trees.hpp
    title: "Extended block cut tree \uFF08Block cut tree \u306E\u4E9C\u7A2E\uFF09"
  - icon: ':question:'
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
    PROBLEM: https://yukicoder.me/problems/no/1326
    links:
    - https://yukicoder.me/problems/no/1326
  bundledCode: "#line 1 \"graph/test/extended_block_cut_trees.yuki1326.test.cpp\"\n\
    #define PROBLEM \"https://yukicoder.me/problems/no/1326\"\n#line 2 \"graph/extended_block_cut_trees.hpp\"\
    \n\n#include <cassert>\n#include <utility>\n#include <vector>\n\n// Construct\
    \ block cut tree (or forest) from a given graph\n// Complexity: O(N + M), N =\
    \ |vertices|, M = |edges|\n// based on this idea: https://x.com/noshi91/status/1529858538650374144\n\
    // based on this implementation: https://ssrs-cp.github.io/cp_library/graph/extended_block_cut_tree.hpp.html\n\
    struct extended_block_cut_trees {\n    int N;                            // number\
    \ of vertices\n    int B;                            // number of blocks\n   \
    \ std::vector<std::vector<int>> to; // (0, ..., N - 1): vertices, (N, ..., N +\
    \ B - 1): blocks\n\n    extended_block_cut_trees(int N, const std::vector<std::pair<int,\
    \ int>> &edges)\n        : N(N), B(0), to(N) {\n        std::vector<std::vector<int>>\
    \ adj(N);\n        for (auto [u, v] : edges) {\n            if (u != v) adj.at(u).push_back(v),\
    \ adj.at(v).push_back(u);\n        }\n\n        std::vector<int> dfs_next(N, -1),\
    \ dist(N, -1), back_cnt(N);\n\n        auto rec1 = [&](auto &&self, int now) ->\
    \ void {\n            for (int nxt : adj[now]) {\n                if (dist[nxt]\
    \ == -1) {\n                    dist[nxt] = dist[now] + 1;\n                 \
    \   dfs_next[now] = nxt;\n                    self(self, nxt);\n             \
    \       back_cnt[now] += back_cnt[nxt];\n                } else if (dist[nxt]\
    \ < dist[now] - 1) {\n                    ++back_cnt[now];\n                 \
    \   --back_cnt[dfs_next[nxt]];\n                }\n            }\n        };\n\
    \n        for (int i = 0; i < N; ++i) {\n            if (dist[i] == -1) dist[i]\
    \ = 0, rec1(rec1, i);\n        }\n\n        std::vector<bool> used(N);\n\n   \
    \     auto rec2 = [&](auto &&self, int now, int current_b) -> void {\n       \
    \     used[now] = true;\n            bool ok = false;\n\n            for (int\
    \ nxt : adj[now]) {\n                if (dist[nxt] == dist[now] + 1 and !used[nxt])\
    \ {\n                    if (back_cnt[nxt] > 0) {\n                        if\
    \ (!ok) {\n                            ok = true;\n                          \
    \  add_edge(now, current_b);\n                        }\n                    \
    \    self(self, nxt, current_b);\n                    } else {\n             \
    \           to.push_back({});\n                        ++B;\n                \
    \        add_edge(now, B - 1);\n                        self(self, nxt, B - 1);\n\
    \                    }\n                }\n            }\n\n            if (!ok\
    \ and dist[now] > 0) { add_edge(now, current_b); }\n        };\n\n        for\
    \ (int i = 0; i < N; ++i) {\n            if (dist[i] == 0) { rec2(rec2, i, B -\
    \ 1); }\n            if (adj[i].empty()) {\n                to.push_back({});\n\
    \                ++B;\n                add_edge(i, B - 1);\n            }\n  \
    \      }\n    }\n\n    int size() const { return N + B; }\n\n    bool is_articulation_point(int\
    \ vertex) const {\n        assert(0 <= vertex and vertex < N);\n        return\
    \ to[vertex].size() > 1;\n    }\n\n    int block_size(int block) const {\n   \
    \     assert(0 <= block and block < B);\n        return to[N + block].size();\n\
    \    }\n\n    const std::vector<int> &block_vertices(int block) const {\n    \
    \    assert(0 <= block and block < B);\n        return to[N + block];\n    }\n\
    \n    std::vector<std::vector<int>> biconnected_components() const {\n       \
    \ return std::vector<std::vector<int>>(to.begin() + N, to.end());\n    }\n\n \
    \   // first < N (vertices), second >= N (blocks)\n    std::vector<std::pair<int,\
    \ int>> get_edges() const {\n        std::vector<std::pair<int, int>> edges;\n\
    \        for (int i = 0; i < N; ++i) {\n            for (int j : to[i]) edges.emplace_back(i,\
    \ j);\n        }\n        return edges;\n    }\n\nprivate:\n    void add_edge(int\
    \ vertex, int block) {\n        assert(0 <= vertex and vertex < N);\n        assert(0\
    \ <= block and block < B);\n        to[vertex].push_back(N + block);\n       \
    \ to[N + block].push_back(vertex);\n    }\n};\n#line 2 \"tree/heavy_light_decomposition.hpp\"\
    \n#include <algorithm>\n#line 4 \"tree/heavy_light_decomposition.hpp\"\n#include\
    \ <functional>\n#include <queue>\n#include <stack>\n#line 9 \"tree/heavy_light_decomposition.hpp\"\
    \n\n// Heavy-light decomposition of trees (forest)\n// Based on http://beet-aizu.hatenablog.com/entry/2017/12/12/235950\n\
    struct heavy_light_decomposition {\n    int V;\n    int k;\n    std::vector<std::vector<int>>\
    \ e;\n    std::vector<int> par;         // par[i] = parent of vertex i (Default:\
    \ -1)\n    std::vector<int> depth;       // depth[i] = distance between root and\
    \ vertex i\n    std::vector<int> subtree_sz;  // subtree_sz[i] = size of subtree\
    \ whose root is i\n    std::vector<int> heavy_child; // heavy_child[i] = child\
    \ of vertex i on heavy path (Default: -1)\n    std::vector<int> tree_id;     //\
    \ tree_id[i] = id of tree vertex i belongs to\n    // subtree_begin[i] = aligned\
    \ id for vertex i (consecutive on heavy edges)\n    std::vector<int> subtree_begin,\
    \ subtree_end;\n    std::vector<int> vis_order; // vis_order[subtree_begin[i]]\
    \ = i\n    std::vector<int> head; // head[i] = id of vertex on heavy path of vertex\
    \ i, nearest to root\n\n    heavy_light_decomposition(int n, const std::vector<std::pair<int,\
    \ int>> &edges)\n        : V(n), k(0), e(n), par(n), depth(n), subtree_sz(n),\
    \ heavy_child(n), tree_id(n, -1),\n          subtree_begin(n), subtree_end(n),\
    \ vis_order(0), head(n) {\n        for (auto [u, v] : edges) {\n            assert(u\
    \ != v);\n            e.at(u).emplace_back(v);\n            e.at(v).emplace_back(u);\n\
    \        }\n    }\n\n    void _build_dfs_1(int root) {\n        std::vector<std::pair<int,\
    \ int>> st;\n        par[root] = -1;\n        depth[root] = 0;\n        st.emplace_back(root,\
    \ 0);\n        while (!st.empty()) {\n            int now = st.back().first;\n\
    \            int &i = st.back().second;\n            if (i < (int)e[now].size())\
    \ {\n                int nxt = e[now][i++];\n                if (nxt == par[now])\
    \ continue;\n                par[nxt] = now;\n                depth[nxt] = depth[now]\
    \ + 1;\n                st.emplace_back(nxt, 0);\n            } else {\n     \
    \           st.pop_back();\n                int max_sub_sz = 0;\n            \
    \    subtree_sz[now] = 1;\n                heavy_child[now] = -1;\n          \
    \      for (auto nxt : e[now]) {\n                    if (nxt == par[now]) continue;\n\
    \                    subtree_sz[now] += subtree_sz[nxt];\n                   \
    \ if (max_sub_sz < subtree_sz[nxt]) {\n                        max_sub_sz = subtree_sz[nxt],\
    \ heavy_child[now] = nxt;\n                    }\n                }\n        \
    \    }\n        }\n    }\n\n    void _build_dfs_2(int now, int tree_id_now) {\n\
    \        std::vector<std::pair<int, bool>> st;\n        st.emplace_back(now, true);\n\
    \        head[now] = now;\n\n        while (!st.empty()) {\n            auto [now,\
    \ mode] = st.back();\n            st.pop_back();\n\n            if (mode) {\n\
    \                tree_id[now] = tree_id_now;\n                subtree_begin[now]\
    \ = k++;\n                vis_order.push_back(now);\n\n                st.emplace_back(now,\
    \ false);\n\n                for (int nxt : e[now]) {\n                    if\
    \ (nxt == par[now] or nxt == heavy_child[now]) continue;\n                   \
    \ head[nxt] = nxt;\n                    st.emplace_back(nxt, true);\n        \
    \        }\n\n                if (heavy_child[now] != -1) {\n                \
    \    head[heavy_child[now]] = head[now];\n                    st.emplace_back(heavy_child[now],\
    \ true);\n                }\n            } else {\n                subtree_end[now]\
    \ = k;\n            }\n        }\n    }\n\n    void build(std::vector<int> roots\
    \ = {0}) {\n        int tree_id_now = 0;\n        for (int r : roots) {\n    \
    \        _build_dfs_1(r);\n            _build_dfs_2(r, tree_id_now++);\n     \
    \   }\n    }\n\n    template <class T> std::vector<T> segtree_rearrange(const\
    \ std::vector<T> &data) const {\n        assert(int(data.size()) == V);\n    \
    \    std::vector<T> ret;\n        ret.reserve(vis_order.size());\n        for\
    \ (int v : vis_order) ret.emplace_back(data[v]);\n        return ret;\n    }\n\
    \n    void for_vertex(int u, const std::function<void(int)> &f) const { f(subtree_begin[u]);\
    \ }\n\n    // query for vertices on path [u, v] (INCLUSIVE)\n    void\n    for_each_vertex(int\
    \ u, int v, const std::function<void(int ancestor, int descendant)> &f) const\
    \ {\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            f(std::max(subtree_begin[head[v]], subtree_begin[u]),\
    \ subtree_begin[v]);\n            if (head[u] == head[v]) break;\n           \
    \ v = par[head[v]];\n        }\n    }\n\n    void for_each_vertex_noncommutative(\n\
    \        int from, int to, const std::function<void(int ancestor, int descendant)>\
    \ &fup,\n        const std::function<void(int ancestor, int descendant)> &fdown)\
    \ const {\n        int u = from, v = to;\n        const int lca = lowest_common_ancestor(u,\
    \ v), dlca = depth[lca];\n        while (u >= 0 and depth[u] > dlca) {\n     \
    \       const int p = (depth[head[u]] > dlca ? head[u] : lca);\n            fup(subtree_begin[p]\
    \ + (p == lca), subtree_begin[u]), u = par[p];\n        }\n        static std::vector<std::pair<int,\
    \ int>> lrs;\n        int sz = 0;\n        while (v >= 0 and depth[v] >= dlca)\
    \ {\n            const int p = (depth[head[v]] >= dlca ? head[v] : lca);\n   \
    \         if (int(lrs.size()) == sz) lrs.emplace_back(0, 0);\n            lrs.at(sz++)\
    \ = {p, v}, v = par.at(p);\n        }\n        while (sz--) fdown(subtree_begin[lrs.at(sz).first],\
    \ subtree_begin[lrs.at(sz).second]);\n    }\n\n    // query for edges on path\
    \ [u, v]\n    void for_each_edge(int u, int v, const std::function<void(int, int)>\
    \ &f) const {\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            if (head[u] != head[v]) {\n                f(subtree_begin[head[v]],\
    \ subtree_begin[v]);\n                v = par[head[v]];\n            } else {\n\
    \                if (u != v) f(subtree_begin[u] + 1, subtree_begin[v]);\n    \
    \            break;\n            }\n        }\n    }\n\n    // query for vertices\
    \ in subtree rooted at u\n    void for_subtree(int u, const std::function<void(int,\
    \ int)> &f) const {\n        f(subtree_begin[u], subtree_end[u] - 1);\n    }\n\
    \n    // lowest_common_ancestor: O(log V)\n    int lowest_common_ancestor(int\
    \ u, int v) const {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >=\
    \ 0);\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            if (head[u] == head[v]) return u;\n          \
    \  v = par[head[v]];\n        }\n    }\n\n    int distance(int u, int v) const\
    \ {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >= 0);\n        return\
    \ depth[u] + depth[v] - 2 * depth[lowest_common_ancestor(u, v)];\n    }\n\n  \
    \  // Level ancestor, O(log V)\n    // if k-th parent is out of range, return\
    \ -1\n    int kth_parent(int v, int k) const {\n        if (k < 0) return -1;\n\
    \        while (v >= 0) {\n            int h = head.at(v), len = depth.at(v) -\
    \ depth.at(h);\n            if (k <= len) return vis_order.at(subtree_begin.at(v)\
    \ - k);\n            k -= len + 1, v = par.at(h);\n        }\n        return -1;\n\
    \    }\n\n    // Jump on tree, O(log V)\n    int s_to_t_by_k_steps(int s, int\
    \ t, int k) const {\n        if (k < 0) return -1;\n        if (k == 0) return\
    \ s;\n        int lca = lowest_common_ancestor(s, t);\n        if (k <= depth.at(s)\
    \ - depth.at(lca)) return kth_parent(s, k);\n        return kth_parent(t, depth.at(s)\
    \ + depth.at(t) - depth.at(lca) * 2 - k);\n    }\n};\n#line 4 \"graph/test/extended_block_cut_trees.yuki1326.test.cpp\"\
    \n\n#include <atcoder/fenwicktree>\n\n#include <iostream>\n\nusing namespace std;\n\
    \nint main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\n  \
    \  int N, M;\n    cin >> N >> M;\n    vector<pair<int, int>> edges(M);\n    for\
    \ (auto &[u, v] : edges) cin >> u >> v, --u, --v;\n\n    const extended_block_cut_trees\
    \ bct(N, edges);\n\n    heavy_light_decomposition hld(bct.size(), bct.get_edges());\n\
    \    hld.build();\n\n    atcoder::fenwick_tree<int> fw(hld.V);\n    for (int i\
    \ = 0; i < N; ++i) fw.add(hld.subtree_begin[i], 1);\n\n    int Q;\n    cin >>\
    \ Q;\n    while (Q--) {\n        int u, v;\n        cin >> u >> v;\n        --u,\
    \ --v;\n        int ret = 0;\n        if (u != v) {\n            ret = -2;\n \
    \           hld.for_each_vertex(u, v, [&](int a, int b) { ret += fw.sum(a, b +\
    \ 1); });\n        }\n        cout << ret << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1326\"\n#include \"../extended_block_cut_trees.hpp\"\
    \n#include \"../../tree/heavy_light_decomposition.hpp\"\n\n#include <atcoder/fenwicktree>\n\
    \n#include <iostream>\n\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n\n    int N, M;\n    cin >> N >> M;\n    vector<pair<int,\
    \ int>> edges(M);\n    for (auto &[u, v] : edges) cin >> u >> v, --u, --v;\n\n\
    \    const extended_block_cut_trees bct(N, edges);\n\n    heavy_light_decomposition\
    \ hld(bct.size(), bct.get_edges());\n    hld.build();\n\n    atcoder::fenwick_tree<int>\
    \ fw(hld.V);\n    for (int i = 0; i < N; ++i) fw.add(hld.subtree_begin[i], 1);\n\
    \n    int Q;\n    cin >> Q;\n    while (Q--) {\n        int u, v;\n        cin\
    \ >> u >> v;\n        --u, --v;\n        int ret = 0;\n        if (u != v) {\n\
    \            ret = -2;\n            hld.for_each_vertex(u, v, [&](int a, int b)\
    \ { ret += fw.sum(a, b + 1); });\n        }\n        cout << ret << '\\n';\n \
    \   }\n}\n"
  dependsOn:
  - graph/extended_block_cut_trees.hpp
  - tree/heavy_light_decomposition.hpp
  isVerificationFile: true
  path: graph/test/extended_block_cut_trees.yuki1326.test.cpp
  requiredBy: []
  timestamp: '2025-01-01 21:10:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/extended_block_cut_trees.yuki1326.test.cpp
layout: document
redirect_from:
- /verify/graph/test/extended_block_cut_trees.yuki1326.test.cpp
- /verify/graph/test/extended_block_cut_trees.yuki1326.test.cpp.html
title: graph/test/extended_block_cut_trees.yuki1326.test.cpp
---
