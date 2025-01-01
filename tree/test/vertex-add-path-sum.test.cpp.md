---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/point-update-range-get_nonrecursive.hpp
    title: segmenttree/point-update-range-get_nonrecursive.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_path_sum
  bundledCode: "#line 1 \"tree/test/vertex-add-path-sum.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n#line 2 \"segmenttree/point-update-range-get_nonrecursive.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include <iostream>\n\
    #include <stack>\n#include <vector>\n\n// CUT begin\n// Nonrecursive Segment Tree\
    \ (point-update, range-get)\n// - Conditions for operations:\n//   - merge_data:\
    \ [TDATA, TDATA] -> TDATA, e(x, y) == e(y, x)\n//   - data2ret: [TDATA, TQUERY]\
    \ -> TRET\n//   - merge_ret: [TRET, TRET] -> TRET, g(defaultRET, x) == x, g(x,\
    \ y) = g(y, x)\n//   - commutability f(e(x, y), q) == g(f(x, q), f(y, q))\ntemplate\
    \ <typename TDATA, typename TRET, typename TQUERY> struct NonrecursiveSegmentTree\
    \ {\n    int N;\n    TRET defaultRET;\n    virtual TDATA merge_data(const TDATA\
    \ &, const TDATA &) = 0;\n    virtual TRET data2ret(const TDATA &, const TQUERY\
    \ &) = 0;\n    virtual TRET merge_ret(const TRET &, const TRET &) = 0;\n    std::vector<TDATA>\
    \ data;\n    inline TDATA &at(int i) { return data[i]; }\n\n    inline void _merge(int\
    \ i) { at(i) = merge_data(at(i << 1), at((i << 1) + 1)); }\n    void initialize(const\
    \ std::vector<TDATA> &seq, TRET RET_ZERO) {\n        N = seq.size();\n       \
    \ defaultRET = RET_ZERO;\n        data = seq;\n        data.insert(data.end(),\
    \ seq.begin(), seq.end());\n        for (int i = N - 1; i; i--) _merge(i);\n \
    \   }\n    NonrecursiveSegmentTree() = default;\n    void update(int pos, const\
    \ TDATA &x) {\n        assert(pos >= 0 and pos < N);\n        at(pos + N) = x;\n\
    \        for (int i = pos + N; i > 1;) i >>= 1, _merge(i);\n    }\n\n    // [l,\
    \ r), 0-indexed\n    TRET get(int l, int r, TQUERY query = NULL) {\n        assert(l\
    \ >= 0 and r <= N);\n        TRET retl = defaultRET, retr = defaultRET;\n    \
    \    l += N, r += N;\n        while (l < r) {\n            if (l & 1) retl = merge_ret(retl,\
    \ data2ret(data[l++], query));\n            if (r & 1) retr = merge_ret(data2ret(data[--r],\
    \ query), retr);\n            l >>= 1, r >>= 1;\n        }\n        return merge_ret(retl,\
    \ retr);\n    }\n\n    // Calculate smallest r that satisfies condition(g(f(x_l,\
    \ q), ..., f(x_{r - 1}, q)) == true\n    // Assumption: Monotonicity of g(x_l,\
    \ ..., x_r) about r (l: fixed)\n    // Complexity: O(log N)\n    int binary_search(int\
    \ l, std::function<bool(TRET)> condition, TQUERY query = NULL) {\n        std::stack<int>\
    \ rs;\n        l += N;\n        int r = N * 2;\n        TRET retl = defaultRET;\n\
    \        if (condition(retl)) return l - N;\n        while (l < r) {\n       \
    \     if (l & 1) {\n                TRET ret_tmp = merge_ret(retl, data2ret(data[l],\
    \ query));\n                if (condition(ret_tmp)) {\n                    while\
    \ (l * 2 < N * 2) {\n                        ret_tmp = merge_ret(retl, data2ret(data[l\
    \ * 2], query));\n                        if (condition(ret_tmp))\n          \
    \                  l *= 2;\n                        else\n                   \
    \         retl = ret_tmp, l = l * 2 + 1;\n                    }\n            \
    \        return l - N;\n                }\n                l++;\n            \
    \    retl = ret_tmp;\n            }\n            if (r & 1) rs.push(--r);\n  \
    \          l >>= 1, r >>= 1;\n        }\n        while (!rs.empty()) {\n     \
    \       l = rs.top();\n            rs.pop();\n            TRET ret_tmp = merge_ret(retl,\
    \ data2ret(data[l], query));\n            if (condition(ret_tmp)) {\n        \
    \        while (l * 2 < N * 2) {\n                    ret_tmp = merge_ret(retl,\
    \ data2ret(data[l * 2], query));\n                    if (condition(ret_tmp))\n\
    \                        l *= 2;\n                    else\n                 \
    \       retl = ret_tmp, l = l * 2 + 1;\n                }\n                return\
    \ l - N;\n            }\n            retl = ret_tmp;\n        }\n        return\
    \ N;\n    }\n\n    template <typename T1, typename T2, typename T3>\n    friend\
    \ std::ostream &operator<<(std::ostream &os, NonrecursiveSegmentTree<T1, T2, T3>\
    \ s) {\n        os << \"[SegmentTree (len: \" << s.N << ')';\n        for (int\
    \ i = 0; i < s.N; i++) os << s.at(i + s.N) << ',';\n        os << \"]\";\n   \
    \     return os;\n    }\n};\n\n// Range Minimum Query\n// - get: return min(x_l,\
    \ ..., x_{r - 1})\ntemplate <typename T> struct RangeMinimumQuery : public NonrecursiveSegmentTree<T,\
    \ T, bool> {\n    using SegTree = NonrecursiveSegmentTree<T, T, bool>;\n    T\
    \ merge_data(const T &vl, const T &vr) override { return std::min(vl, vr); };\n\
    \    T data2ret(const T &v, const bool &q) override { return v; }\n    T merge_ret(const\
    \ T &vl, const T &vr) override { return std::min(vl, vr); };\n    RangeMinimumQuery(const\
    \ std::vector<T> &seq, T defaultmin)\n        : SegTree::NonrecursiveSegmentTree()\
    \ {\n        SegTree::initialize(seq, defaultmin);\n    };\n};\n\ntemplate <typename\
    \ T> struct PointUpdateRangeSum : public NonrecursiveSegmentTree<T, T, bool> {\n\
    \    using SegTree = NonrecursiveSegmentTree<T, T, bool>;\n    T merge_data(const\
    \ T &vl, const T &vr) override { return vl + vr; };\n    T data2ret(const T &v,\
    \ const bool &q) override { return v; }\n    T merge_ret(const T &vl, const T\
    \ &vr) override { return vl + vr; };\n    PointUpdateRangeSum(const std::vector<T>\
    \ &seq, T zero) : SegTree::NonrecursiveSegmentTree() {\n        SegTree::initialize(seq,\
    \ zero);\n    };\n};\n\n// Range Counting less than q Query\n// - get: return\
    \ (#{i | l <= i < r, x_i < q}, total sum of them).\ntemplate <typename T>\nstruct\
    \ CountAndSumLessThan\n    : public NonrecursiveSegmentTree<std::vector<std::pair<T,\
    \ T>>, std::pair<int, T>, T> {\n    using TDATA = std::vector<std::pair<T, T>>;\n\
    \    using TRET = std::pair<int, T>;\n    using TQUERY = T;\n    TDATA merge_data(const\
    \ TDATA &vl, const TDATA &vr) override {\n        TDATA ret = vl;\n        ret.insert(ret.end(),\
    \ vr.begin(), vr.end());\n        std::sort(ret.begin(), ret.end());\n       \
    \ if (ret.size()) {\n            ret[0].second = ret[0].first;\n            for\
    \ (size_t i = 1; i < ret.size(); i++)\n                ret[i].second = ret[i -\
    \ 1].second + ret[i].first;\n        }\n        return ret;\n    }\n    TRET data2ret(const\
    \ TDATA &vec, const TQUERY &q) override {\n        int i = std::lower_bound(vec.begin(),\
    \ vec.end(), std::make_pair(q, q)) - vec.begin();\n        if (!i)\n         \
    \   return std::make_pair(0, 0);\n        else\n            return std::make_pair(i,\
    \ vec[i - 1].second);\n    }\n    TRET merge_ret(const TRET &l, const TRET &r)\
    \ override {\n        return std::make_pair(l.first + r.first, l.second + r.second);\n\
    \    }\n    using SegTree = NonrecursiveSegmentTree<TDATA, TRET, TQUERY>;\n  \
    \  CountAndSumLessThan(const std::vector<T> &seq) : SegTree::NonrecursiveSegmentTree()\
    \ {\n        std::vector<TDATA> init;\n        for (auto x : seq) init.emplace_back(TDATA{std::pair<T,\
    \ T>(x, x)});\n        SegTree::initialize(init, TRET(0, 0));\n    }\n};\n#line\
    \ 5 \"tree/heavy_light_decomposition.hpp\"\n#include <queue>\n#line 7 \"tree/heavy_light_decomposition.hpp\"\
    \n#include <utility>\n#line 9 \"tree/heavy_light_decomposition.hpp\"\n\n// Heavy-light\
    \ decomposition of trees (forest)\n// Based on http://beet-aizu.hatenablog.com/entry/2017/12/12/235950\n\
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
    \ + depth.at(t) - depth.at(lca) * 2 - k);\n    }\n};\n#line 6 \"tree/test/vertex-add-path-sum.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, Q, q, u, v;\n    cin >> N >> Q;\n\n    vector<long long> A(N);\n\
    \    for (auto &x : A) cin >> x;\n    vector<pair<int, int>> edges(N - 1);\n \
    \   for (auto &[u, v] : edges) cin >> u >> v;\n    heavy_light_decomposition hld(N,\
    \ edges);\n\n    hld.build();\n    PointUpdateRangeSum<long long> segtree(hld.segtree_rearrange(A),\
    \ 0LL);\n\n    while (Q--) {\n        cin >> q >> u >> v;\n        if (q) {\n\
    \            long long ret = 0;\n            hld.for_each_vertex(u, v, [&](int\
    \ l, int r) -> void { ret += segtree.get(l, r + 1); });\n            cout << ret\
    \ << '\\n';\n        } else {\n            A[u] += v;\n            segtree.update(hld.subtree_begin[u],\
    \ A[u]);\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\
    #include \"../../segmenttree/point-update-range-get_nonrecursive.hpp\"\n#include\
    \ \"../heavy_light_decomposition.hpp\"\n#include <iostream>\n#include <vector>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, Q, q, u, v;\n    cin >> N >> Q;\n\n    vector<long long> A(N);\n\
    \    for (auto &x : A) cin >> x;\n    vector<pair<int, int>> edges(N - 1);\n \
    \   for (auto &[u, v] : edges) cin >> u >> v;\n    heavy_light_decomposition hld(N,\
    \ edges);\n\n    hld.build();\n    PointUpdateRangeSum<long long> segtree(hld.segtree_rearrange(A),\
    \ 0LL);\n\n    while (Q--) {\n        cin >> q >> u >> v;\n        if (q) {\n\
    \            long long ret = 0;\n            hld.for_each_vertex(u, v, [&](int\
    \ l, int r) -> void { ret += segtree.get(l, r + 1); });\n            cout << ret\
    \ << '\\n';\n        } else {\n            A[u] += v;\n            segtree.update(hld.subtree_begin[u],\
    \ A[u]);\n        }\n    }\n}\n"
  dependsOn:
  - segmenttree/point-update-range-get_nonrecursive.hpp
  - tree/heavy_light_decomposition.hpp
  isVerificationFile: true
  path: tree/test/vertex-add-path-sum.test.cpp
  requiredBy: []
  timestamp: '2025-01-01 21:39:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/vertex-add-path-sum.test.cpp
layout: document
redirect_from:
- /verify/tree/test/vertex-add-path-sum.test.cpp
- /verify/tree/test/vertex-add-path-sum.test.cpp.html
title: tree/test/vertex-add-path-sum.test.cpp
---
