---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/offline_dynamic_connectivity.hpp
    title: Offline dynamic connectivity
  - icon: ':heavy_check_mark:'
    path: unionfind/undo_monoid_unionfind.hpp
    title: "UnionFind with Undo operation, monoid weights \uFF08Undo \u53EF\u80FD\u30FB\
      \u91CD\u307F\u548C\u53D6\u5F97\u53EF\u80FD UnionFind\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
  bundledCode: "#line 1 \"data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n#line 2 \"unionfind/undo_monoid_unionfind.hpp\"\n#include <numeric>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\n// UnionFind, able to rewind\
    \ to the previous state by undo()\ntemplate <class S> struct undo_dsu {\n    std::vector<int>\
    \ par, cou;\n    std::vector<S> weights;\n    std::vector<std::tuple<int, int,\
    \ S>> history;\n\n    explicit undo_dsu(const std::vector<S> &init)\n        :\
    \ par(init.size()), cou(init.size(), 1), weights(init) {\n        std::iota(par.begin(),\
    \ par.end(), 0);\n    }\n    explicit undo_dsu(int N) : undo_dsu(std::vector<S>(N,\
    \ S())) {}\n    undo_dsu() : undo_dsu(0) {}\n\n    int find(int x) const { return\
    \ (par[x] == x) ? x : find(par[x]); }\n    bool unite(int x, int y) {\n      \
    \  x = find(x), y = find(y);\n        if (cou[x] < cou[y]) std::swap(x, y);\n\
    \        history.emplace_back(y, cou[x], weights[x]);\n        return x != y ?\
    \ par[y] = x, cou[x] += cou[y], weights[x] += weights[y], true : false;\n    }\n\
    \n    void set_weight(int x, S w) {\n        x = find(x);\n        history.emplace_back(x,\
    \ cou[x], weights[x]);\n        weights[x] = w;\n    }\n\n    void undo() {\n\
    \        weights[par[std::get<0>(history.back())]] = std::get<2>(history.back());\n\
    \        cou[par[std::get<0>(history.back())]] = std::get<1>(history.back());\n\
    \        par[std::get<0>(history.back())] = std::get<0>(history.back());\n   \
    \     history.pop_back();\n    }\n\n    void reset() {\n        while (!history.empty())\
    \ undo();\n    }\n\n    int count(int x) const { return cou[find(x)]; }\n\n  \
    \  const S &sum(int x) const { return weights[find(x)]; }\n\n    bool same(int\
    \ x, int y) const { return find(x) == find(y); }\n};\n#line 2 \"data_structure/offline_dynamic_connectivity.hpp\"\
    \n#include <algorithm>\n#include <limits>\n#include <set>\n#line 7 \"data_structure/offline_dynamic_connectivity.hpp\"\
    \n\nenum class DyConOperation {\n    Begins = 1,\n    Ends = 2,\n    Event = 3,\n\
    };\n\ntemplate <class Tick = int> struct offline_dynamic_connectivity {\n\n  \
    \  std::vector<std::pair<Tick, int>> ops;\n\n    struct Edge {\n        Tick since;\n\
    \        Tick until;\n        int edge_id;\n    };\n    std::vector<Edge> edges;\n\
    \n    offline_dynamic_connectivity() = default;\n\n    void add_observation(Tick\
    \ clk, int event_id) { ops.emplace_back(clk, event_id); }\n\n    void apply_time_range(Tick\
    \ since, Tick until, int edge_id) {\n        edges.push_back(Edge{since, until,\
    \ edge_id});\n    }\n\n    struct Procedure {\n        DyConOperation op;\n  \
    \      int id_;\n    };\n\n    std::vector<std::vector<Procedure>> nodes;\n  \
    \  std::vector<Procedure> ret_;\n\n    void rec(int now) {\n        ret_.insert(ret_.end(),\
    \ nodes[now].cbegin(), nodes[now].cend());\n        if (now * 2 < int(nodes.size()))\
    \ rec(now * 2);\n        if (now * 2 + 1 < int(nodes.size())) rec(now * 2 + 1);\n\
    \n        for (auto itr = nodes[now].rbegin(); itr != nodes[now].rend(); ++itr)\
    \ {\n            if (itr->op == DyConOperation::Begins) {\n                ret_.push_back(Procedure{DyConOperation::Ends,\
    \ itr->id_});\n            }\n        }\n    }\n\n    std::vector<Procedure> generate()\
    \ {\n        if (ops.empty()) return {};\n\n        std::vector<Tick> query_ts;\n\
    \        {\n            query_ts.reserve(ops.size());\n            for (const\
    \ auto &p : ops) query_ts.push_back(p.first);\n            std::sort(query_ts.begin(),\
    \ query_ts.end());\n            query_ts.erase(std::unique(query_ts.begin(), query_ts.end()),\
    \ query_ts.end());\n\n            std::vector<int> t_use(query_ts.size() + 1);\n\
    \            t_use.at(0) = 1;\n\n            for (const Edge &e : edges) {\n \
    \               t_use[std::lower_bound(query_ts.begin(), query_ts.end(), e.since)\
    \ - query_ts.begin()] =\n                    1;\n                t_use[std::lower_bound(query_ts.begin(),\
    \ query_ts.end(), e.until) - query_ts.begin()] =\n                    1;\n   \
    \         }\n            for (int i = 1; i < int(query_ts.size()); ++i) {\n  \
    \              if (!t_use[i]) query_ts[i] = query_ts[i - 1];\n            }\n\n\
    \            query_ts.erase(std::unique(query_ts.begin(), query_ts.end()), query_ts.end());\n\
    \        }\n\n        const int N = query_ts.size();\n        int D = 1;\n   \
    \     while (D < int(query_ts.size())) D *= 2;\n\n        nodes.assign(D + N,\
    \ {});\n\n        for (const Edge &e : edges) {\n            int l =\n       \
    \         D + (std::lower_bound(query_ts.begin(), query_ts.end(), e.since) - query_ts.begin());\n\
    \            int r =\n                D + (std::lower_bound(query_ts.begin(),\
    \ query_ts.end(), e.until) - query_ts.begin());\n\n            while (l < r) {\n\
    \                if (l & 1) nodes[l++].push_back(Procedure{DyConOperation::Begins,\
    \ e.edge_id});\n                if (r & 1) nodes[--r].push_back(Procedure{DyConOperation::Begins,\
    \ e.edge_id});\n                l >>= 1, r >>= 1;\n            }\n        }\n\n\
    \        for (const auto &op : ops) {\n            int clk = op.first, qid = op.second;\n\
    \            int t =\n                D + (std::upper_bound(query_ts.begin(),\
    \ query_ts.end(), clk) - query_ts.begin()) - 1;\n            nodes[t].push_back(Procedure{DyConOperation::Event,\
    \ qid});\n        }\n        ret_.clear();\n        rec(1);\n        return ret_;\n\
    \    }\n};\n#line 4 \"data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp\"\
    \n\n#include <iostream>\n#include <map>\nusing namespace std;\n\nint main() {\n\
    \    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, Q;\n    cin >>\
    \ N >> Q;\n\n    using lint = long long;\n    vector<lint> a(N);\n    for (auto\
    \ &x : a) cin >> x;\n\n    vector<pair<int, int>> edges;\n    map<pair<int, int>,\
    \ pair<int, int>> edge_to_id_since;\n\n    offline_dynamic_connectivity<int> dc;\n\
    \n    vector<pair<int, lint>> qs;\n\n    vector<int> get_query;\n    vector<lint>\
    \ ret;\n    for (int q = 0; q < Q; ++q) {\n        int tp;\n        cin >> tp;\n\
    \        if (tp <= 1) {\n            int u, v;\n            cin >> u >> v;\n \
    \           if (u > v) swap(u, v);\n\n            if (tp == 0) {\n           \
    \     edge_to_id_since[make_pair(u, v)] = make_pair(edges.size(), q);\n      \
    \          edges.emplace_back(u, v);\n            } else {\n                int\
    \ id_, since;\n                tie(id_, since) = edge_to_id_since[make_pair(u,\
    \ v)];\n                dc.apply_time_range(since, q, id_);\n                edge_to_id_since.erase(make_pair(u,\
    \ v));\n            }\n        } else if (tp == 2) {\n            int v;\n   \
    \         lint x;\n            cin >> v >> x;\n\n            dc.apply_time_range(q,\
    \ 1 << 30, -1 - int(qs.size()));\n            qs.emplace_back(v, x);\n       \
    \ } else if (tp == 3) {\n            int v;\n            cin >> v;\n\n       \
    \     dc.add_observation(q, ret.size());\n            get_query.push_back(v);\n\
    \            ret.push_back(0);\n        }\n    }\n\n    for (auto p : edge_to_id_since)\
    \ {\n        dc.apply_time_range(p.second.second, 1 << 30, p.second.first);\n\
    \    }\n\n    undo_dsu<lint> dsu(a);\n\n    for (auto p : dc.generate()) {\n \
    \       if (p.op == DyConOperation::Begins) {\n            if (p.id_ >= 0) {\n\
    \                auto edge = edges.at(p.id_);\n                dsu.unite(edge.first,\
    \ edge.second);\n            } else {\n                auto q = qs.at(-p.id_ -\
    \ 1);\n                int v = q.first, x = q.second;\n                dsu.set_weight(v,\
    \ dsu.sum(v) + x);\n            }\n        } else if (p.op == DyConOperation::Ends)\
    \ {\n            dsu.undo();\n        } else if (p.op == DyConOperation::Event)\
    \ {\n            int v = get_query.at(p.id_);\n            ret.at(p.id_) = dsu.sum(v);\n\
    \        }\n    }\n\n    for (auto x : ret) cout << x << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n#include \"../../unionfind/undo_monoid_unionfind.hpp\"\n#include \"../offline_dynamic_connectivity.hpp\"\
    \n\n#include <iostream>\n#include <map>\nusing namespace std;\n\nint main() {\n\
    \    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N, Q;\n    cin >>\
    \ N >> Q;\n\n    using lint = long long;\n    vector<lint> a(N);\n    for (auto\
    \ &x : a) cin >> x;\n\n    vector<pair<int, int>> edges;\n    map<pair<int, int>,\
    \ pair<int, int>> edge_to_id_since;\n\n    offline_dynamic_connectivity<int> dc;\n\
    \n    vector<pair<int, lint>> qs;\n\n    vector<int> get_query;\n    vector<lint>\
    \ ret;\n    for (int q = 0; q < Q; ++q) {\n        int tp;\n        cin >> tp;\n\
    \        if (tp <= 1) {\n            int u, v;\n            cin >> u >> v;\n \
    \           if (u > v) swap(u, v);\n\n            if (tp == 0) {\n           \
    \     edge_to_id_since[make_pair(u, v)] = make_pair(edges.size(), q);\n      \
    \          edges.emplace_back(u, v);\n            } else {\n                int\
    \ id_, since;\n                tie(id_, since) = edge_to_id_since[make_pair(u,\
    \ v)];\n                dc.apply_time_range(since, q, id_);\n                edge_to_id_since.erase(make_pair(u,\
    \ v));\n            }\n        } else if (tp == 2) {\n            int v;\n   \
    \         lint x;\n            cin >> v >> x;\n\n            dc.apply_time_range(q,\
    \ 1 << 30, -1 - int(qs.size()));\n            qs.emplace_back(v, x);\n       \
    \ } else if (tp == 3) {\n            int v;\n            cin >> v;\n\n       \
    \     dc.add_observation(q, ret.size());\n            get_query.push_back(v);\n\
    \            ret.push_back(0);\n        }\n    }\n\n    for (auto p : edge_to_id_since)\
    \ {\n        dc.apply_time_range(p.second.second, 1 << 30, p.second.first);\n\
    \    }\n\n    undo_dsu<lint> dsu(a);\n\n    for (auto p : dc.generate()) {\n \
    \       if (p.op == DyConOperation::Begins) {\n            if (p.id_ >= 0) {\n\
    \                auto edge = edges.at(p.id_);\n                dsu.unite(edge.first,\
    \ edge.second);\n            } else {\n                auto q = qs.at(-p.id_ -\
    \ 1);\n                int v = q.first, x = q.second;\n                dsu.set_weight(v,\
    \ dsu.sum(v) + x);\n            }\n        } else if (p.op == DyConOperation::Ends)\
    \ {\n            dsu.undo();\n        } else if (p.op == DyConOperation::Event)\
    \ {\n            int v = get_query.at(p.id_);\n            ret.at(p.id_) = dsu.sum(v);\n\
    \        }\n    }\n\n    for (auto x : ret) cout << x << '\\n';\n}\n"
  dependsOn:
  - unionfind/undo_monoid_unionfind.hpp
  - data_structure/offline_dynamic_connectivity.hpp
  isVerificationFile: true
  path: data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp
  requiredBy: []
  timestamp: '2022-10-11 22:40:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp
- /verify/data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp.html
title: data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp
---
