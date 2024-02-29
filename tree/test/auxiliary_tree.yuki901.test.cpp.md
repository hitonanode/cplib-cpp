---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/fast_set.hpp
    title: "Fast set of integers \uFF0864\u5206\u6728\u3067\u6574\u6570\u96C6\u5408\
      \u3092\u9AD8\u901F\u306B\u51E6\u7406\u3059\u308B\u30C7\u30FC\u30BF\u69CB\u9020\
      \uFF09"
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: "Shortest Path \uFF08\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF\uFF09"
  - icon: ':heavy_check_mark:'
    path: sparse_table/rmq_sparse_table.hpp
    title: sparse_table/rmq_sparse_table.hpp
  - icon: ':heavy_check_mark:'
    path: tree/auxiliary_tree.hpp
    title: "LCA-based auxiliary tree / virtual tree, online \uFF08\"\u865A\u6811\"\
      \uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/901
    links:
    - https://yukicoder.me/problems/no/901
  bundledCode: "#line 1 \"tree/test/auxiliary_tree.yuki901.test.cpp\"\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/no/901\"\n#line 2 \"tree/auxiliary_tree.hpp\"\
    \n#include <unordered_set>\n#include <vector>\n\n#line 2 \"data_structure/fast_set.hpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#line 6 \"data_structure/fast_set.hpp\"\
    \n\n// Sorted set of integers [0, n)\n// Space complexity: (64 / 63) n + O(log\
    \ n) bit\nclass fast_set {\n    static constexpr int B = 64;\n\n    int n;\n \
    \   int cnt;\n    std::vector<std::vector<uint64_t>> _d;\n\n    static int bsf(uint64_t\
    \ x) { return __builtin_ctzll(x); }\n    static int bsr(uint64_t x) { return 63\
    \ - __builtin_clzll(x); }\n\npublic:\n    // 0 \u4EE5\u4E0A n_ \u672A\u6E80\u306E\
    \u6574\u6570\u304C\u5165\u308C\u3089\u308C\u308B sorted set \u3092\u4F5C\u6210\
    \n    fast_set(int n_) : n(n_), cnt(0) {\n        do { n_ = (n_ + B - 1) / B,\
    \ _d.push_back(std::vector<uint64_t>(n_)); } while (n_ > 1);\n    }\n\n    bool\
    \ contains(int i) const {\n        assert(0 <= i and i < n);\n        return (_d.front().at(i\
    \ / B) >> (i % B)) & 1;\n    }\n\n    void insert(int i) {\n        assert(0 <=\
    \ i and i < n);\n        if (contains(i)) return;\n        ++cnt;\n        for\
    \ (auto &vec : _d) {\n            bool f = vec.at(i / B);\n            vec.at(i\
    \ / B) |= 1ULL << (i % B), i /= B;\n            if (f) break;\n        }\n   \
    \ }\n\n    void erase(int i) {\n        assert(0 <= i and i < n);\n        if\
    \ (!contains(i)) return;\n        --cnt;\n        for (auto &vec : _d) {\n   \
    \         vec.at(i / B) &= ~(1ULL << (i % B)), i /= B;\n            if (vec.at(i))\
    \ break;\n        }\n    }\n\n    // i \u4EE5\u4E0A\u306E\u6700\u5C0F\u8981\u7D20\
    \ \u306A\u3051\u308C\u3070 default_val\n    int next(int i, const int default_val)\
    \ const {\n        assert(0 <= i and i <= n);\n\n        for (auto itr = _d.cbegin();\
    \ itr != _d.cend(); ++itr, i = i / B + 1) {\n            if (i / B >= int(itr->size()))\
    \ break;\n\n            if (auto d = itr->at(i / B) >> (i % B); d) {\n       \
    \         i += bsf(d);\n                while (itr != _d.cbegin()) i = i * B +\
    \ bsf((--itr)->at(i));\n                return i;\n            }\n        }\n\n\
    \        return default_val;\n    }\n    int next(const int i) const { return\
    \ next(i, n); }\n\n    // i \u4EE5\u4E0B\u306E\u6700\u5C0F\u8981\u7D20 \u306A\u3051\
    \u308C\u3070 default_val\n    int prev(int i, int default_val = -1) const {\n\
    \        assert(-1 <= i and i < n);\n\n        for (auto itr = _d.cbegin(); itr\
    \ != _d.cend() and i >= 0; ++itr, i = i / B - 1) {\n            if (auto d = itr->at(i\
    \ / B) << (B - 1 - i % B); d) {\n                i += bsr(d) - (B - 1);\n    \
    \            while (itr != _d.cbegin()) i = i * B + bsr((--itr)->at(i));\n   \
    \             return i;\n            }\n        }\n\n        return default_val;\n\
    \    }\n\n    // return minimum element (if exists) or `n` (empty)\n    int min()\
    \ const { return next(0); }\n    // return maximum element (if exists) or `-1`\
    \ (empty)\n    int max() const { return prev(n - 1); }\n    int size() const {\
    \ return cnt; }\n    bool empty() const { return cnt == 0; }\n\n    void clear()\
    \ {\n        if (!cnt) return;\n        cnt = 0;\n        auto rec = [&](auto\
    \ &&self, int d, int x) -> void {\n            if (d) {\n                for (auto\
    \ m = _d.at(d).at(x); m;) {\n                    int i = bsf(m);\n           \
    \         m -= 1ULL << i, self(self, d - 1, x * B + i);\n                }\n \
    \           }\n            _d.at(d).at(x) = 0;\n        };\n        rec(rec, _d.size()\
    \ - 1, 0);\n    }\n};\n#line 2 \"sparse_table/rmq_sparse_table.hpp\"\n#include\
    \ <algorithm>\n#line 5 \"sparse_table/rmq_sparse_table.hpp\"\n\n// CUT begin\n\
    // Range Minimum Query for static sequence by sparse table\n// Complexity: $O(N\
    \ \\log N)$ for precalculation, $O(1)$ per query\ntemplate <typename T> struct\
    \ StaticRMQ {\n    inline T func(const T &l, const T &r) const noexcept { return\
    \ std::min<T>(l, r); }\n    int N, lgN;\n    T defaultT;\n    std::vector<std::vector<T>>\
    \ data;\n    std::vector<int> lgx_table;\n    StaticRMQ() = default;\n    StaticRMQ(const\
    \ std::vector<T> &sequence, T defaultT)\n        : N(sequence.size()), defaultT(defaultT)\
    \ {\n        lgx_table.resize(N + 1);\n        for (int i = 2; i < N + 1; i++)\
    \ lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgN = lgx_table[N] + 1;\n   \
    \     data.assign(lgN, std::vector<T>(N, defaultT));\n        data[0] = sequence;\n\
    \        for (int d = 1; d < lgN; d++) {\n            for (int i = 0; i + (1 <<\
    \ d) <= N; i++) {\n                data[d][i] = func(data[d - 1][i], data[d -\
    \ 1][i + (1 << (d - 1))]);\n            }\n        }\n    }\n    T get(int l,\
    \ int r) const { // [l, r), 0-indexed\n        assert(l >= 0 and r <= N);\n  \
    \      if (l >= r) return defaultT;\n        int d = lgx_table[r - l];\n     \
    \   return func(data[d][l], data[d][r - (1 << d)]);\n    }\n};\n#line 7 \"tree/auxiliary_tree.hpp\"\
    \n\n// Data structure maintaining \"compressed graph\" of subsets of the vertices\
    \ of a tree\n// Known as \"auxiliary tree\" and \"virtual tree\"\n// https://noshi91.github.io/algorithm-encyclopedia/auxiliary-tree\n\
    class auxiliary_tree {\n\n    int n_ = 0;\n    int root_ = -1;\n\n    // Each\
    \ node is labeled by both v (given as input) and t (DFS preorder)\n    std::vector<int>\
    \ v2t; // v2t[v] = t\n    std::vector<int> t2v; // t2v[t] = v\n\n    // To get\
    \ LCA of two vertices in O(1) per query\n    std::vector<int> _rmq_pos;\n    StaticRMQ<std::pair<int,\
    \ int>> _rmq;\n\n    // Auxiliary tree info\n    // Variables starting with '_'\
    \ are labeled by t, not v\n    int _auxiliary_root = -1; // LCA of all currently\
    \ activated vertices\n    fast_set _is_active;      // \"t in _is_active\" iff\
    \ t is activated\n    fast_set _is_semiactive;  // \"t in _is_semiactive\" iff\
    \ t is used in the current tree\n    std::vector<int> _parent; // _parent[t] =\
    \ parent of t in the current tree\n    std::vector<std::unordered_set<int>> _child;\
    \ // _child[t] = children of t in the current tree\n\n    int _get_lca(int t1,\
    \ int t2) const {\n        if (t1 > t2) std::swap(t1, t2);\n        return _rmq.get(_rmq_pos.at(t1),\
    \ _rmq_pos.at(t2) + 1).second;\n    }\n\n    void _add_edge(int tpar, int tchild)\
    \ {\n        assert(tpar != tchild);\n        assert(_parent.at(tchild) == -1);\n\
    \n        _parent.at(tchild) = tpar;\n        _child.at(tpar).insert(tchild);\n\
    \    }\n\n    void _erase_edge(int tpar, int tchild) {\n        assert(tpar !=\
    \ tchild);\n        assert(_parent.at(tchild) == tpar);\n\n        _parent.at(tchild)\
    \ = -1;\n        _child.at(tpar).erase(tchild);\n    }\n\npublic:\n    int n()\
    \ const { return n_; }\n\n    int original_root() const { return root_; }\n\n\
    \    int auxiliary_root() const { return _auxiliary_root == -1 ? -1 : t2v.at(_auxiliary_root);\
    \ }\n\n    bool is_active(int v) const { return _is_active.contains(v2t.at(v));\
    \ }\n\n    bool is_semiactive(int v) const { return _is_semiactive.contains(v2t.at(v));\
    \ }\n\n    int get_parent(int v) const {\n        const int t = v2t.at(v);\n \
    \       return _parent.at(t) == -1 ? -1 : t2v.at(_parent.at(t));\n    }\n\n  \
    \  std::vector<int> get_children(int v) const {\n        const int t = v2t.at(v);\n\
    \        std::vector<int> ret;\n        ret.reserve(_child.at(t).size());\n  \
    \      for (int c : _child.at(t)) ret.push_back(t2v.at(c));\n        return ret;\n\
    \    }\n\n    auxiliary_tree() = default;\n\n    auxiliary_tree(const std::vector<std::vector<int>>\
    \ &to, int root)\n        : n_(to.size()), root_(root), v2t(n_, -1), _rmq_pos(n_,\
    \ -1), _is_active(n_),\n          _is_semiactive(n_), _parent(n_, -1), _child(n_)\
    \ {\n        std::vector<std::pair<int, int>> dfspath; // (depth, t[v])\n    \
    \    t2v.reserve(n_);\n\n        auto rec = [&](auto &&self, int now, int prv,\
    \ int depth) -> void {\n            const int t = t2v.size();\n            v2t.at(now)\
    \ = t;\n            t2v.push_back(now);\n\n            _rmq_pos.at(t) = dfspath.size();\n\
    \            dfspath.emplace_back(depth, t);\n\n            for (int nxt : to.at(now))\
    \ {\n                if (nxt == prv) continue;\n                self(self, nxt,\
    \ now, depth + 1);\n                dfspath.emplace_back(depth, t);\n        \
    \    }\n        };\n        rec(rec, root, -1, 0);\n\n        _rmq = {dfspath,\
    \ std::make_pair(n_, -1)};\n    }\n\n    void activate(int v_) {\n        const\
    \ int t = v2t.at(v_);\n\n        if (_is_semiactive.contains(t)) {\n\n       \
    \     // Already semiactive. Nothing to do.\n\n        } else if (_auxiliary_root\
    \ == -1) {\n\n            // Add one vertex to empty set.\n            _auxiliary_root\
    \ = t;\n\n        } else if (const int next_root = _get_lca(_auxiliary_root, t);\
    \ next_root != _auxiliary_root) {\n\n            // New node is outside the current\
    \ tree. Update root.\n            if (next_root != t) {\n                _is_semiactive.insert(next_root);\n\
    \                _add_edge(next_root, t);\n            }\n            _add_edge(next_root,\
    \ _auxiliary_root);\n            _auxiliary_root = next_root;\n\n        } else\
    \ if (const int tnxt = _is_semiactive.next(t, n_);\n                   tnxt <\
    \ n_ and _get_lca(t, tnxt) == t) {\n\n            // New node lies on the path\
    \ of the current tree. Insert new node.\n            const int tpar = _parent.at(tnxt);\n\
    \            assert(tpar >= 0);\n\n            // tpar->tnxt => tpar->t->tnxt\n\
    \            _erase_edge(tpar, tnxt);\n            _add_edge(tpar, t);\n     \
    \       _add_edge(t, tnxt);\n\n        } else {\n\n            // New node is\
    \ \"under\" the current tree.\n            const int tprv = _is_semiactive.prev(t,\
    \ -1);\n            assert(tprv >= 0);\n            const int tprvlca = _get_lca(t,\
    \ tprv), tnxtlca = tnxt < n_ ? _get_lca(t, tnxt) : n_;\n\n            const int\
    \ t2 = (tnxt == n_ or _get_lca(tprvlca, tnxtlca) == tnxtlca) ? tprv : tnxt;\n\
    \            const int tlca = _get_lca(t, t2);\n\n            if (!_is_semiactive.contains(tlca))\
    \ {\n                const int tc = _is_semiactive.next(tlca, n_);\n         \
    \       const int tpar = _parent.at(tc);\n                assert(tpar >= 0);\n\
    \                // tpar->tc => tpar->tlca->tc\n                _is_semiactive.insert(tlca);\n\
    \                _erase_edge(tpar, tc);\n                _add_edge(tpar, tlca);\n\
    \                _add_edge(tlca, tc);\n            }\n\n            _add_edge(tlca,\
    \ t);\n        }\n\n        _is_semiactive.insert(t);\n        _is_active.insert(t);\n\
    \    }\n\n    void deactivate(int v_) {\n        const int t = v2t.at(v_);\n\n\
    \        if (!_is_active.contains(t)) return;\n\n        const int num_children\
    \ = _child.at(t).size();\n\n        if (num_children > 1) { // (1)\n\n       \
    \     // Nothing to do (just deactivate it). Still semiactivated.\n\n        }\
    \ else if (num_children == 1) {\n\n            // Delete this vertex from the\
    \ current tree.\n            const int tchild = *_child.at(t).begin();\n\n   \
    \         if (_parent.at(t) == -1) {\n\n                // Root changes.\n   \
    \             // t->tchild => tchild\n                _auxiliary_root = tchild;\n\
    \                _erase_edge(t, tchild);\n\n            } else {\n\n         \
    \       // tpar->t->tchild => tpar->tchild\n                const int tpar = _parent.at(t);\n\
    \                _erase_edge(tpar, t);\n                _erase_edge(t, tchild);\n\
    \                _add_edge(tpar, tchild);\n            }\n\n            _is_semiactive.erase(t);\n\
    \n        } else if (num_children == 0 and _parent.at(t) == -1) {\n\n        \
    \    // Erase the only vertex in the current tree.\n            _auxiliary_root\
    \ = -1;\n            _is_semiactive.erase(t);\n\n        } else {\n\n        \
    \    assert(num_children == 0 and _parent.at(t) != -1);\n\n            const int\
    \ tpar = _parent.at(t);\n            const int tparpar = _parent.at(tpar);\n\n\
    \            if (!_is_active.contains(tpar) and _child.at(tpar).size() == 2) {\n\
    \n                // In only this case, parent of t is also erased.\n        \
    \        const int t2 =\n                    t ^ (*_child.at(tpar).begin()) ^\
    \ (*std::next(_child.at(tpar).begin()));\n                if (tparpar == -1) {\n\
    \                    // t<-tpar->t2 => t2\n                    _auxiliary_root\
    \ = t2;\n                    _is_semiactive.erase(tpar);\n                   \
    \ _erase_edge(tpar, t2);\n                } else {\n                    // tparpar->tpar->t2\
    \ => tparpar->t2\n                    _is_semiactive.erase(tpar);\n          \
    \          _erase_edge(tparpar, tpar);\n                    _erase_edge(tpar,\
    \ t2);\n                    _add_edge(tparpar, t2);\n                }\n     \
    \       }\n            _erase_edge(tpar, t);\n            _is_semiactive.erase(t);\n\
    \        }\n\n        _is_active.erase(t);\n    }\n};\n#line 4 \"graph/shortest_path.hpp\"\
    \n#include <deque>\n#include <fstream>\n#include <functional>\n#include <limits>\n\
    #include <queue>\n#include <string>\n#include <tuple>\n#include <utility>\n#line\
    \ 13 \"graph/shortest_path.hpp\"\n\ntemplate <typename T, T INF = std::numeric_limits<T>::max()\
    \ / 2, int INVALID = -1>\nstruct shortest_path {\n    int V, E;\n    bool single_positive_weight;\n\
    \    T wmin, wmax;\n\n    std::vector<std::pair<int, T>> tos;\n    std::vector<int>\
    \ head;\n    std::vector<std::tuple<int, int, T>> edges;\n\n    void build_()\
    \ {\n        if (int(tos.size()) == E and int(head.size()) == V + 1) return;\n\
    \        tos.resize(E);\n        head.assign(V + 1, 0);\n        for (const auto\
    \ &e : edges) ++head[std::get<0>(e) + 1];\n        for (int i = 0; i < V; ++i)\
    \ head[i + 1] += head[i];\n        auto cur = head;\n        for (const auto &e\
    \ : edges) {\n            tos[cur[std::get<0>(e)]++] = std::make_pair(std::get<1>(e),\
    \ std::get<2>(e));\n        }\n    }\n\n    shortest_path(int V = 0) : V(V), E(0),\
    \ single_positive_weight(true), wmin(0), wmax(0) {}\n    void add_edge(int s,\
    \ int t, T w) {\n        assert(0 <= s and s < V);\n        assert(0 <= t and\
    \ t < V);\n        edges.emplace_back(s, t, w);\n        ++E;\n        if (w >\
    \ 0 and wmax > 0 and wmax != w) single_positive_weight = false;\n        wmin\
    \ = std::min(wmin, w);\n        wmax = std::max(wmax, w);\n    }\n\n    void add_bi_edge(int\
    \ u, int v, T w) {\n        add_edge(u, v, w);\n        add_edge(v, u, w);\n \
    \   }\n\n    std::vector<T> dist;\n    std::vector<int> prev;\n\n    // Dijkstra\
    \ algorithm\n    // - Requirement: wmin >= 0\n    // - Complexity: O(E log E)\n\
    \    using Pque = std::priority_queue<std::pair<T, int>, std::vector<std::pair<T,\
    \ int>>,\n                                     std::greater<std::pair<T, int>>>;\n\
    \    template <class Heap = Pque> void dijkstra(int s, int t = INVALID) {\n  \
    \      assert(0 <= s and s < V);\n        build_();\n        dist.assign(V, INF);\n\
    \        prev.assign(V, INVALID);\n        dist[s] = 0;\n        Heap pq;\n  \
    \      pq.emplace(0, s);\n        while (!pq.empty()) {\n            T d;\n  \
    \          int v;\n            std::tie(d, v) = pq.top();\n            pq.pop();\n\
    \            if (t == v) return;\n            if (dist[v] < d) continue;\n   \
    \         for (int e = head[v]; e < head[v + 1]; ++e) {\n                const\
    \ auto &nx = tos[e];\n                T dnx = d + nx.second;\n               \
    \ if (dist[nx.first] > dnx) {\n                    dist[nx.first] = dnx, prev[nx.first]\
    \ = v;\n                    pq.emplace(dnx, nx.first);\n                }\n  \
    \          }\n        }\n    }\n\n    // Dijkstra algorithm\n    // - Requirement:\
    \ wmin >= 0\n    // - Complexity: O(V^2 + E)\n    void dijkstra_vquad(int s, int\
    \ t = INVALID) {\n        assert(0 <= s and s < V);\n        build_();\n     \
    \   dist.assign(V, INF);\n        prev.assign(V, INVALID);\n        dist[s] =\
    \ 0;\n        std::vector<char> fixed(V, false);\n        while (true) {\n   \
    \         int r = INVALID;\n            T dr = INF;\n            for (int i =\
    \ 0; i < V; i++) {\n                if (!fixed[i] and dist[i] < dr) r = i, dr\
    \ = dist[i];\n            }\n            if (r == INVALID or r == t) break;\n\
    \            fixed[r] = true;\n            int nxt;\n            T dx;\n     \
    \       for (int e = head[r]; e < head[r + 1]; ++e) {\n                std::tie(nxt,\
    \ dx) = tos[e];\n                if (dist[nxt] > dist[r] + dx) dist[nxt] = dist[r]\
    \ + dx, prev[nxt] = r;\n            }\n        }\n    }\n\n    // Bellman-Ford\
    \ algorithm\n    // - Requirement: no negative loop\n    // - Complexity: O(VE)\n\
    \    bool bellman_ford(int s, int nb_loop) {\n        assert(0 <= s and s < V);\n\
    \        build_();\n        dist.assign(V, INF), prev.assign(V, INVALID);\n  \
    \      dist[s] = 0;\n        for (int l = 0; l < nb_loop; l++) {\n           \
    \ bool upd = false;\n            for (int v = 0; v < V; v++) {\n             \
    \   if (dist[v] == INF) continue;\n                for (int e = head[v]; e < head[v\
    \ + 1]; ++e) {\n                    const auto &nx = tos[e];\n               \
    \     T dnx = dist[v] + nx.second;\n                    if (dist[nx.first] > dnx)\
    \ dist[nx.first] = dnx, prev[nx.first] = v, upd = true;\n                }\n \
    \           }\n            if (!upd) return true;\n        }\n        return false;\n\
    \    }\n\n    // Bellman-ford algorithm using deque\n    // - Requirement: no\
    \ negative loop\n    // - Complexity: O(VE)\n    void spfa(int s) {\n        assert(0\
    \ <= s and s < V);\n        build_();\n        dist.assign(V, INF);\n        prev.assign(V,\
    \ INVALID);\n        dist[s] = 0;\n        std::deque<int> q;\n        std::vector<char>\
    \ in_queue(V);\n        q.push_back(s), in_queue[s] = 1;\n        while (!q.empty())\
    \ {\n            int now = q.front();\n            q.pop_front(), in_queue[now]\
    \ = 0;\n            for (int e = head[now]; e < head[now + 1]; ++e) {\n      \
    \          const auto &nx = tos[e];\n                T dnx = dist[now] + nx.second;\n\
    \                int nxt = nx.first;\n                if (dist[nxt] > dnx) {\n\
    \                    dist[nxt] = dnx;\n                    if (!in_queue[nxt])\
    \ {\n                        if (q.size() and dnx < dist[q.front()]) { // Small\
    \ label first optimization\n                            q.push_front(nxt);\n \
    \                       } else {\n                            q.push_back(nxt);\n\
    \                        }\n                        prev[nxt] = now, in_queue[nxt]\
    \ = 1;\n                    }\n                }\n            }\n        }\n \
    \   }\n\n    // 01-BFS\n    // - Requirement: all weights must be 0 or w (positive\
    \ constant).\n    // - Complexity: O(V + E)\n    void zero_one_bfs(int s, int\
    \ t = INVALID) {\n        assert(0 <= s and s < V);\n        build_();\n     \
    \   dist.assign(V, INF), prev.assign(V, INVALID);\n        dist[s] = 0;\n    \
    \    std::vector<int> q(V * 4);\n        int ql = V * 2, qr = V * 2;\n       \
    \ q[qr++] = s;\n        while (ql < qr) {\n            int v = q[ql++];\n    \
    \        if (v == t) return;\n            for (int e = head[v]; e < head[v + 1];\
    \ ++e) {\n                const auto &nx = tos[e];\n                T dnx = dist[v]\
    \ + nx.second;\n                if (dist[nx.first] > dnx) {\n                \
    \    dist[nx.first] = dnx, prev[nx.first] = v;\n                    if (nx.second)\
    \ {\n                        q[qr++] = nx.first;\n                    } else {\n\
    \                        q[--ql] = nx.first;\n                    }\n        \
    \        }\n            }\n        }\n    }\n\n    // Dial's algorithm\n    //\
    \ - Requirement: wmin >= 0\n    // - Complexity: O(wmax * V + E)\n    void dial(int\
    \ s, int t = INVALID) {\n        assert(0 <= s and s < V);\n        build_();\n\
    \        dist.assign(V, INF), prev.assign(V, INVALID);\n        dist[s] = 0;\n\
    \        std::vector<std::vector<std::pair<int, T>>> q(wmax + 1);\n        q[0].emplace_back(s,\
    \ dist[s]);\n        int ninq = 1;\n\n        int cur = 0;\n        T dcur = 0;\n\
    \        for (; ninq; ++cur, ++dcur) {\n            if (cur == wmax + 1) cur =\
    \ 0;\n            while (!q[cur].empty()) {\n                int v = q[cur].back().first;\n\
    \                T dnow = q[cur].back().second;\n                q[cur].pop_back(),\
    \ --ninq;\n                if (v == t) return;\n                if (dist[v] <\
    \ dnow) continue;\n\n                for (int e = head[v]; e < head[v + 1]; ++e)\
    \ {\n                    const auto &nx = tos[e];\n                    T dnx =\
    \ dist[v] + nx.second;\n                    if (dist[nx.first] > dnx) {\n    \
    \                    dist[nx.first] = dnx, prev[nx.first] = v;\n             \
    \           int nxtcur = cur + int(nx.second);\n                        if (nxtcur\
    \ >= int(q.size())) nxtcur -= q.size();\n                        q[nxtcur].emplace_back(nx.first,\
    \ dnx), ++ninq;\n                    }\n                }\n            }\n   \
    \     }\n    }\n\n    // Solver for DAG\n    // - Requirement: graph is DAG\n\
    \    // - Complexity: O(V + E)\n    bool dag_solver(int s) {\n        assert(0\
    \ <= s and s < V);\n        build_();\n        dist.assign(V, INF), prev.assign(V,\
    \ INVALID);\n        dist[s] = 0;\n        std::vector<int> indeg(V, 0);\n   \
    \     std::vector<int> q(V * 2);\n        int ql = 0, qr = 0;\n        q[qr++]\
    \ = s;\n        while (ql < qr) {\n            int now = q[ql++];\n          \
    \  for (int e = head[now]; e < head[now + 1]; ++e) {\n                const auto\
    \ &nx = tos[e];\n                ++indeg[nx.first];\n                if (indeg[nx.first]\
    \ == 1) q[qr++] = nx.first;\n            }\n        }\n        ql = qr = 0;\n\
    \        q[qr++] = s;\n        while (ql < qr) {\n            int now = q[ql++];\n\
    \            for (int e = head[now]; e < head[now + 1]; ++e) {\n             \
    \   const auto &nx = tos[e];\n                --indeg[nx.first];\n           \
    \     if (dist[nx.first] > dist[now] + nx.second)\n                    dist[nx.first]\
    \ = dist[now] + nx.second, prev[nx.first] = now;\n                if (indeg[nx.first]\
    \ == 0) q[qr++] = nx.first;\n            }\n        }\n        return *max_element(indeg.begin(),\
    \ indeg.end()) == 0;\n    }\n\n    // Retrieve a sequence of vertex ids that represents\
    \ shortest path [s, ..., goal]\n    // If not reachable to goal, return {}\n \
    \   std::vector<int> retrieve_path(int goal) const {\n        assert(int(prev.size())\
    \ == V);\n        assert(0 <= goal and goal < V);\n        if (dist[goal] == INF)\
    \ return {};\n        std::vector<int> ret{goal};\n        while (prev[goal] !=\
    \ INVALID) {\n            goal = prev[goal];\n            ret.push_back(goal);\n\
    \        }\n        std::reverse(ret.begin(), ret.end());\n        return ret;\n\
    \    }\n\n    void solve(int s, int t = INVALID) {\n        if (wmin >= 0) {\n\
    \            if (single_positive_weight) {\n                zero_one_bfs(s, t);\n\
    \            } else if (wmax <= 10) {\n                dial(s, t);\n         \
    \   } else {\n                if ((long long)V * V < (E << 4)) {\n           \
    \         dijkstra_vquad(s, t);\n                } else {\n                  \
    \  dijkstra(s, t);\n                }\n            }\n        } else {\n     \
    \       bellman_ford(s, V);\n        }\n    }\n\n    // Warshall-Floyd algorithm\n\
    \    // - Requirement: no negative loop\n    // - Complexity: O(E + V^3)\n   \
    \ std::vector<std::vector<T>> floyd_warshall() {\n        build_();\n        std::vector<std::vector<T>>\
    \ dist2d(V, std::vector<T>(V, INF));\n        for (int i = 0; i < V; i++) {\n\
    \            dist2d[i][i] = 0;\n            for (const auto &e : edges) {\n  \
    \              int s = std::get<0>(e), t = std::get<1>(e);\n                dist2d[s][t]\
    \ = std::min(dist2d[s][t], std::get<2>(e));\n            }\n        }\n      \
    \  for (int k = 0; k < V; k++) {\n            for (int i = 0; i < V; i++) {\n\
    \                if (dist2d[i][k] == INF) continue;\n                for (int\
    \ j = 0; j < V; j++) {\n                    if (dist2d[k][j] == INF) continue;\n\
    \                    dist2d[i][j] = std::min(dist2d[i][j], dist2d[i][k] + dist2d[k][j]);\n\
    \                }\n            }\n        }\n        return dist2d;\n    }\n\n\
    \    void to_dot(std::string filename = \"shortest_path\") const {\n        std::ofstream\
    \ ss(filename + \".DOT\");\n        ss << \"digraph{\\n\";\n        build_();\n\
    \        for (int i = 0; i < V; i++) {\n            for (int e = head[i]; e <\
    \ head[i + 1]; ++e) {\n                ss << i << \"->\" << tos[e].first << \"\
    [label=\" << tos[e].second << \"];\\n\";\n            }\n        }\n        ss\
    \ << \"}\\n\";\n        ss.close();\n        return;\n    }\n};\n#line 5 \"tree/test/auxiliary_tree.yuki901.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N;\n    cin >> N;\n    vector<vector<int>>\
    \ to(N);\n\n    shortest_path<long long> sp(N);\n\n    for (int e = 0; e < N -\
    \ 1; ++e) {\n        int u, v, w;\n        cin >> u >> v >> w;\n        to.at(u).push_back(v);\n\
    \        to.at(v).push_back(u);\n        sp.add_bi_edge(u, v, w);\n    }\n\n \
    \   const int root = 0;\n\n    auxiliary_tree at(to, root);\n\n    sp.solve(root);\n\
    \n    int Q;\n    cin >> Q;\n    while (Q--) {\n        int k;\n        cin >>\
    \ k;\n        vector<int> xs(k);\n        for (auto &x : xs) cin >> x;\n\n   \
    \     for (int x : xs) at.activate(x);\n\n        long long ret = 0;\n\n     \
    \   auto rec = [&](auto &&self, int now) -> void {\n            for (int nxt :\
    \ at.get_children(now)) {\n                self(self, nxt);\n                ret\
    \ += sp.dist.at(nxt) - sp.dist.at(now);\n            }\n        };\n\n       \
    \ rec(rec, at.auxiliary_root());\n\n        for (int x : xs) at.deactivate(x);\n\
    \n        cout << ret << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/901\"\n#include \"../auxiliary_tree.hpp\"\
    \n#include \"../../graph/shortest_path.hpp\"\n#include <cassert>\n#include <iostream>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N;\n    cin >> N;\n    vector<vector<int>> to(N);\n\n    shortest_path<long\
    \ long> sp(N);\n\n    for (int e = 0; e < N - 1; ++e) {\n        int u, v, w;\n\
    \        cin >> u >> v >> w;\n        to.at(u).push_back(v);\n        to.at(v).push_back(u);\n\
    \        sp.add_bi_edge(u, v, w);\n    }\n\n    const int root = 0;\n\n    auxiliary_tree\
    \ at(to, root);\n\n    sp.solve(root);\n\n    int Q;\n    cin >> Q;\n    while\
    \ (Q--) {\n        int k;\n        cin >> k;\n        vector<int> xs(k);\n   \
    \     for (auto &x : xs) cin >> x;\n\n        for (int x : xs) at.activate(x);\n\
    \n        long long ret = 0;\n\n        auto rec = [&](auto &&self, int now) ->\
    \ void {\n            for (int nxt : at.get_children(now)) {\n               \
    \ self(self, nxt);\n                ret += sp.dist.at(nxt) - sp.dist.at(now);\n\
    \            }\n        };\n\n        rec(rec, at.auxiliary_root());\n\n     \
    \   for (int x : xs) at.deactivate(x);\n\n        cout << ret << '\\n';\n    }\n\
    }\n"
  dependsOn:
  - tree/auxiliary_tree.hpp
  - data_structure/fast_set.hpp
  - sparse_table/rmq_sparse_table.hpp
  - graph/shortest_path.hpp
  isVerificationFile: true
  path: tree/test/auxiliary_tree.yuki901.test.cpp
  requiredBy: []
  timestamp: '2024-02-29 17:58:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/auxiliary_tree.yuki901.test.cpp
layout: document
redirect_from:
- /verify/tree/test/auxiliary_tree.yuki901.test.cpp
- /verify/tree/test/auxiliary_tree.yuki901.test.cpp.html
title: tree/test/auxiliary_tree.yuki901.test.cpp
---
