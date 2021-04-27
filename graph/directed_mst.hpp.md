---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/directed_mst.aoj.test.cpp
    title: graph/test/directed_mst.aoj.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://joisino.hatenablog.com/entry/2017/01/11/230141
    - https://judge.yosupo.jp/problem/directedmst
  bundledCode: "#line 2 \"graph/directed_mst.hpp\"\n#include <cassert>\n#include <numeric>\n\
    #include <tuple>\n#include <utility>\n#include <vector>\n\n// CUT begin\n// Minimum\
    \ spanning tree for directed graph (spanning arborescence)\n//\n// Complexity:\
    \ O(nm) (Chu-Liu/Edmonds' algorithm)\n// Verify: https://judge.yosupo.jp/problem/directedmst\n\
    // Reference:\n// [1] R. E. Tarjan, \"Finding optimum branchings,\" Networks 7.1\
    \ (1977): 25-35.\n// - https://joisino.hatenablog.com/entry/2017/01/11/230141\n\
    template <typename Weight = long long> struct MinimumSpanningArborescence {\n\
    \    struct noswap_unionfind {\n        std::vector<int> par;\n        void initialize(int\
    \ N) {\n            par.resize(N);\n            std::iota(par.begin(), par.end(),\
    \ 0);\n        }\n        int find(int x) { return (par[x] == x) ? x : par[x]\
    \ = find(par[x]); }\n        bool unite(int child, int parent) {\n           \
    \ child = find(child), parent = find(parent);\n            if (child == parent)\
    \ return false;\n            par[child] = parent;\n            return true;\n\
    \        }\n        bool same(int x, int y) { return find(x) == find(y); }\n \
    \   } uf;\n\n    struct skew_heap {\n        struct node;\n        static std::vector<node>\
    \ data;\n        static unsigned len;\n        using ptr = int;\n        struct\
    \ node {\n        private:\n            Weight add, val;\n            int id;\n\
    \n        public:\n            ptr l, r;\n            node(Weight val, int id_)\
    \ : add(0), val(val), id(id_), l(-1), r(-1) {}\n            node() = default;\n\
    \            Weight weight() const noexcept { return add + val; }\n          \
    \  int getid() const noexcept { return id; }\n            void push() {\n    \
    \            if (l != -1) data[l].add += this->add;\n                if (r !=\
    \ -1) data[r].add += this->add;\n                this->val += this->add;\n   \
    \             this->add = 0;\n            }\n            void apply(Weight w)\
    \ { this->add += w; }\n        };\n\n        ptr _meld(ptr a, ptr b) {\n     \
    \       if (a == -1) return b;\n            if (b == -1) return a;\n         \
    \   if (data[b].weight() < data[a].weight()) std::swap(a, b);\n            data[a].push();\n\
    \            data[a].r = _meld(data[a].r, b);\n            std::swap(data[a].l,\
    \ data[a].r);\n            return a;\n        }\n\n        ptr root;\n       \
    \ int sz;\n\n        ptr _new_node(Weight value, int id_) {\n            if (len\
    \ >= data.size()) data.resize(std::max<int>(1024, data.size() * 2));\n       \
    \     data[len] = node(value, id_);\n            return len++;\n        }\n\n\
    \    public:\n        skew_heap() : root(-1), sz(0) {}\n        void push(Weight\
    \ value, int id_) {\n            root = _meld(_new_node(value, id_), root);\n\
    \            sz++;\n        }\n        void merge(skew_heap &heap) {\n       \
    \     this->root = _meld(this->root, heap.root);\n            if (heap.root !=\
    \ -1) this->sz += heap.sz;\n            heap = skew_heap();\n        }\n     \
    \   std::pair<Weight, int> top() const { return {data[root].weight(), data[root].getid()};\
    \ }\n        void add_all(Weight w) {\n            if (root != -1) data[root].apply(w);\n\
    \        }\n        void pop() {\n            data[root].push();\n           \
    \ root = _meld(data[root].r, data[root].l);\n        }\n        int size() const\
    \ { return sz; }\n        bool empty() const { return sz == 0; }\n    };\n\n \
    \   Weight ret;\n    MinimumSpanningArborescence(const int N, const std::vector<std::tuple<int,\
    \ int, Weight>> &edges, int r) {\n        assert(r >= 0 and r < N);\n        std::vector<short>\
    \ used(N);\n        std::vector<skew_heap> incoming_edges(N);\n\n        ret =\
    \ 0;\n        std::vector<int> from(N, r);\n        std::vector<Weight> from_cost(N,\
    \ 0);\n        std::vector<int> used_eids;\n        uf.initialize(N);\n      \
    \  used[r] = 2;\n\n        // std::vector<int> par(N, -1);\n        int s, t;\n\
    \        Weight w;\n        for (int eid = 0; eid < int(edges.size()); eid++)\
    \ {\n            std::tie(s, t, w) = edges[eid];\n            incoming_edges[t].push(w,\
    \ eid);\n        }\n\n        for (int start = 0; start < N; start++) {\n    \
    \        if (used[start] != 0) continue;\n            int cur = start;\n     \
    \       std::vector<int> processing;\n            while (used[cur] != 2) {\n \
    \               used[cur] = 1;\n                processing.push_back(cur);\n \
    \               if (incoming_edges[cur].empty()) {\n                    // No\
    \ solution\n                    return;\n                }\n\n               \
    \ int eid;\n                Weight w;\n                std::tie(w, eid) = incoming_edges[cur].top();\n\
    \                from[cur] = uf.find(std::get<0>(edges[eid]));\n             \
    \   // par[cur] = std::get<0>(edges[eid]);\n                // par[std::get<1>(edges[eid])]\
    \ = std::get<0>(edges[eid]);\n                from_cost[cur] = w;\n          \
    \      incoming_edges[cur].pop();\n                if (from[cur] == cur) continue;\n\
    \n                ret += from_cost[cur];\n                used_eids.push_back(eid);\n\
    \n                if (used[from[cur]] == 1) {\n                    int p = cur;\n\
    \                    do {\n                        incoming_edges[p].add_all(-from_cost[p]);\n\
    \                        if (p != cur) {\n                            uf.unite(p,\
    \ cur);\n                            incoming_edges[cur].merge(incoming_edges[p]);\n\
    \                        }\n                        p = uf.find(from[p]);\n  \
    \                  } while (p != cur);\n                } else {\n           \
    \         cur = from[cur];\n                }\n            }\n            for\
    \ (int v : processing) used[v] = 2;\n        }\n    }\n};\ntemplate <>\nstd::vector<MinimumSpanningArborescence<long\
    \ long>::skew_heap::node> MinimumSpanningArborescence<long long>::skew_heap::data\
    \ = {};\ntemplate <typename T> unsigned MinimumSpanningArborescence<T>::skew_heap::len\
    \ = 0;\n"
  code: "#pragma once\n#include <cassert>\n#include <numeric>\n#include <tuple>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// Minimum spanning tree\
    \ for directed graph (spanning arborescence)\n//\n// Complexity: O(nm) (Chu-Liu/Edmonds'\
    \ algorithm)\n// Verify: https://judge.yosupo.jp/problem/directedmst\n// Reference:\n\
    // [1] R. E. Tarjan, \"Finding optimum branchings,\" Networks 7.1 (1977): 25-35.\n\
    // - https://joisino.hatenablog.com/entry/2017/01/11/230141\ntemplate <typename\
    \ Weight = long long> struct MinimumSpanningArborescence {\n    struct noswap_unionfind\
    \ {\n        std::vector<int> par;\n        void initialize(int N) {\n       \
    \     par.resize(N);\n            std::iota(par.begin(), par.end(), 0);\n    \
    \    }\n        int find(int x) { return (par[x] == x) ? x : par[x] = find(par[x]);\
    \ }\n        bool unite(int child, int parent) {\n            child = find(child),\
    \ parent = find(parent);\n            if (child == parent) return false;\n   \
    \         par[child] = parent;\n            return true;\n        }\n        bool\
    \ same(int x, int y) { return find(x) == find(y); }\n    } uf;\n\n    struct skew_heap\
    \ {\n        struct node;\n        static std::vector<node> data;\n        static\
    \ unsigned len;\n        using ptr = int;\n        struct node {\n        private:\n\
    \            Weight add, val;\n            int id;\n\n        public:\n      \
    \      ptr l, r;\n            node(Weight val, int id_) : add(0), val(val), id(id_),\
    \ l(-1), r(-1) {}\n            node() = default;\n            Weight weight()\
    \ const noexcept { return add + val; }\n            int getid() const noexcept\
    \ { return id; }\n            void push() {\n                if (l != -1) data[l].add\
    \ += this->add;\n                if (r != -1) data[r].add += this->add;\n    \
    \            this->val += this->add;\n                this->add = 0;\n       \
    \     }\n            void apply(Weight w) { this->add += w; }\n        };\n\n\
    \        ptr _meld(ptr a, ptr b) {\n            if (a == -1) return b;\n     \
    \       if (b == -1) return a;\n            if (data[b].weight() < data[a].weight())\
    \ std::swap(a, b);\n            data[a].push();\n            data[a].r = _meld(data[a].r,\
    \ b);\n            std::swap(data[a].l, data[a].r);\n            return a;\n \
    \       }\n\n        ptr root;\n        int sz;\n\n        ptr _new_node(Weight\
    \ value, int id_) {\n            if (len >= data.size()) data.resize(std::max<int>(1024,\
    \ data.size() * 2));\n            data[len] = node(value, id_);\n            return\
    \ len++;\n        }\n\n    public:\n        skew_heap() : root(-1), sz(0) {}\n\
    \        void push(Weight value, int id_) {\n            root = _meld(_new_node(value,\
    \ id_), root);\n            sz++;\n        }\n        void merge(skew_heap &heap)\
    \ {\n            this->root = _meld(this->root, heap.root);\n            if (heap.root\
    \ != -1) this->sz += heap.sz;\n            heap = skew_heap();\n        }\n  \
    \      std::pair<Weight, int> top() const { return {data[root].weight(), data[root].getid()};\
    \ }\n        void add_all(Weight w) {\n            if (root != -1) data[root].apply(w);\n\
    \        }\n        void pop() {\n            data[root].push();\n           \
    \ root = _meld(data[root].r, data[root].l);\n        }\n        int size() const\
    \ { return sz; }\n        bool empty() const { return sz == 0; }\n    };\n\n \
    \   Weight ret;\n    MinimumSpanningArborescence(const int N, const std::vector<std::tuple<int,\
    \ int, Weight>> &edges, int r) {\n        assert(r >= 0 and r < N);\n        std::vector<short>\
    \ used(N);\n        std::vector<skew_heap> incoming_edges(N);\n\n        ret =\
    \ 0;\n        std::vector<int> from(N, r);\n        std::vector<Weight> from_cost(N,\
    \ 0);\n        std::vector<int> used_eids;\n        uf.initialize(N);\n      \
    \  used[r] = 2;\n\n        // std::vector<int> par(N, -1);\n        int s, t;\n\
    \        Weight w;\n        for (int eid = 0; eid < int(edges.size()); eid++)\
    \ {\n            std::tie(s, t, w) = edges[eid];\n            incoming_edges[t].push(w,\
    \ eid);\n        }\n\n        for (int start = 0; start < N; start++) {\n    \
    \        if (used[start] != 0) continue;\n            int cur = start;\n     \
    \       std::vector<int> processing;\n            while (used[cur] != 2) {\n \
    \               used[cur] = 1;\n                processing.push_back(cur);\n \
    \               if (incoming_edges[cur].empty()) {\n                    // No\
    \ solution\n                    return;\n                }\n\n               \
    \ int eid;\n                Weight w;\n                std::tie(w, eid) = incoming_edges[cur].top();\n\
    \                from[cur] = uf.find(std::get<0>(edges[eid]));\n             \
    \   // par[cur] = std::get<0>(edges[eid]);\n                // par[std::get<1>(edges[eid])]\
    \ = std::get<0>(edges[eid]);\n                from_cost[cur] = w;\n          \
    \      incoming_edges[cur].pop();\n                if (from[cur] == cur) continue;\n\
    \n                ret += from_cost[cur];\n                used_eids.push_back(eid);\n\
    \n                if (used[from[cur]] == 1) {\n                    int p = cur;\n\
    \                    do {\n                        incoming_edges[p].add_all(-from_cost[p]);\n\
    \                        if (p != cur) {\n                            uf.unite(p,\
    \ cur);\n                            incoming_edges[cur].merge(incoming_edges[p]);\n\
    \                        }\n                        p = uf.find(from[p]);\n  \
    \                  } while (p != cur);\n                } else {\n           \
    \         cur = from[cur];\n                }\n            }\n            for\
    \ (int v : processing) used[v] = 2;\n        }\n    }\n};\ntemplate <>\nstd::vector<MinimumSpanningArborescence<long\
    \ long>::skew_heap::node> MinimumSpanningArborescence<long long>::skew_heap::data\
    \ = {};\ntemplate <typename T> unsigned MinimumSpanningArborescence<T>::skew_heap::len\
    \ = 0;\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/directed_mst.hpp
  requiredBy: []
  timestamp: '2021-04-25 18:31:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/directed_mst.aoj.test.cpp
documentation_of: graph/directed_mst.hpp
layout: document
redirect_from:
- /library/graph/directed_mst.hpp
- /library/graph/directed_mst.hpp.html
title: graph/directed_mst.hpp
---
