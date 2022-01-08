---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://ei1333.github.io/library/graph/others/eulerian-trail.cpp
  bundledCode: "#line 2 \"graph/eulerian_trail.hpp\"\n#include <algorithm>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// This implementation is based\
    \ on https://ei1333.github.io/library/graph/others/eulerian-trail.cpp\ntemplate\
    \ <bool directed> struct EulerianTrail {\n    using Vertex = int;\n    using Edge\
    \ = int;\n    int M;\n    std::vector<int> deg;\n    std::vector<std::pair<Vertex,\
    \ Vertex>> edges;\n    std::vector<std::vector<std::pair<Vertex, Edge>>> to;\n\
    \    std::vector<int> used_vertex, used_edge;\n    EulerianTrail(int V = 0) :\
    \ M(0), deg(V, 0), to(V), used_vertex(V) {}\n    void add_edge(Vertex a, Vertex\
    \ b) {\n        to[a].emplace_back(b, M);\n        if (directed) {\n         \
    \   deg[a]++;\n            deg[b]--;\n        } else {\n            to[b].emplace_back(a,\
    \ M);\n            deg[a]++;\n            deg[b]++;\n        }\n        edges.emplace_back(a,\
    \ b);\n        M++;\n        used_edge.push_back(0);\n    }\n\n    std::vector<std::vector<Edge>>\
    \ solve() {\n        if (directed) {\n            if (std::count_if(deg.begin(),\
    \ deg.end(), [](int x) { return x != 0; })) return {};\n        } else {\n   \
    \         if (std::count_if(deg.begin(), deg.end(), [](int x) { return (x & 1)\
    \ != 0; }))\n                return {};\n        }\n        std::vector<std::vector<Edge>>\
    \ ret;\n        for (int i = 0; i < int(to.size()); i++) {\n            if (to[i].empty()\
    \ or used_vertex[i]) continue;\n            ret.emplace_back(go(i));\n       \
    \ }\n        return ret;\n    }\n\n    std::vector<Edge> go(Vertex s) {\n    \
    \    std::vector<std::pair<Vertex, Edge>> st;\n        std::vector<Edge> ord;\n\
    \        st.emplace_back(s, -1);\n        while (!st.empty()) {\n            Vertex\
    \ now = st.back().first;\n            used_vertex[now] = true;\n            if\
    \ (to[now].empty()) {\n                ord.emplace_back(st.back().second);\n \
    \               st.pop_back();\n            } else {\n                auto e =\
    \ to[now].back();\n                to[now].pop_back();\n                if (used_edge[e.second])\
    \ continue;\n                used_edge[e.second] = true;\n                st.emplace_back(e);\n\
    \            }\n        }\n        ord.pop_back();\n        std::reverse(ord.begin(),\
    \ ord.end());\n        return ord;\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\n// This implementation is based on https://ei1333.github.io/library/graph/others/eulerian-trail.cpp\n\
    template <bool directed> struct EulerianTrail {\n    using Vertex = int;\n   \
    \ using Edge = int;\n    int M;\n    std::vector<int> deg;\n    std::vector<std::pair<Vertex,\
    \ Vertex>> edges;\n    std::vector<std::vector<std::pair<Vertex, Edge>>> to;\n\
    \    std::vector<int> used_vertex, used_edge;\n    EulerianTrail(int V = 0) :\
    \ M(0), deg(V, 0), to(V), used_vertex(V) {}\n    void add_edge(Vertex a, Vertex\
    \ b) {\n        to[a].emplace_back(b, M);\n        if (directed) {\n         \
    \   deg[a]++;\n            deg[b]--;\n        } else {\n            to[b].emplace_back(a,\
    \ M);\n            deg[a]++;\n            deg[b]++;\n        }\n        edges.emplace_back(a,\
    \ b);\n        M++;\n        used_edge.push_back(0);\n    }\n\n    std::vector<std::vector<Edge>>\
    \ solve() {\n        if (directed) {\n            if (std::count_if(deg.begin(),\
    \ deg.end(), [](int x) { return x != 0; })) return {};\n        } else {\n   \
    \         if (std::count_if(deg.begin(), deg.end(), [](int x) { return (x & 1)\
    \ != 0; }))\n                return {};\n        }\n        std::vector<std::vector<Edge>>\
    \ ret;\n        for (int i = 0; i < int(to.size()); i++) {\n            if (to[i].empty()\
    \ or used_vertex[i]) continue;\n            ret.emplace_back(go(i));\n       \
    \ }\n        return ret;\n    }\n\n    std::vector<Edge> go(Vertex s) {\n    \
    \    std::vector<std::pair<Vertex, Edge>> st;\n        std::vector<Edge> ord;\n\
    \        st.emplace_back(s, -1);\n        while (!st.empty()) {\n            Vertex\
    \ now = st.back().first;\n            used_vertex[now] = true;\n            if\
    \ (to[now].empty()) {\n                ord.emplace_back(st.back().second);\n \
    \               st.pop_back();\n            } else {\n                auto e =\
    \ to[now].back();\n                to[now].pop_back();\n                if (used_edge[e.second])\
    \ continue;\n                used_edge[e.second] = true;\n                st.emplace_back(e);\n\
    \            }\n        }\n        ord.pop_back();\n        std::reverse(ord.begin(),\
    \ ord.end());\n        return ord;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: graph/eulerian_trail.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/eulerian_trail.hpp
layout: document
redirect_from:
- /library/graph/eulerian_trail.hpp
- /library/graph/eulerian_trail.hpp.html
title: graph/eulerian_trail.hpp
---
