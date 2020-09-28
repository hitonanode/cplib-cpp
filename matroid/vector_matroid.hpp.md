---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: matroid/matroid.hpp
    title: matroid/matroid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"matroid/matroid.hpp\"\n#include <cassert>\n#include <queue>\n\
    #include <utility>\n#include <vector>\nusing namespace std;\n\n// CUT begin\n\
    using Element = int;\nusing State = vector<bool>;\n\nstruct MatroidExample\n{\n\
    \    int M; // # of elements of set we consider\n\n    // If I is independent\
    \ and I + {e} is not, return elements of the circuit.\n    // If e \\in I, or\
    \ I + {e} is independent, return empty vector.\n    // If I is NOT independent,\
    \ undefined.\n    vector<Element> circuit(State I, Element e);\n};\n\n// Matroid\
    \ intersection solver\n// Algorithm based on <http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/>\n\
    // Complexity: O(CE^2 + E^3) (C : circuit query)\ntemplate <typename T_M1, typename\
    \ T_M2>\nState MatroidIntersection(T_M1 matroid1, T_M2 matroid2)\n{\n    assert(matroid1.M\
    \ == matroid2.M);\n\n    const int M = matroid1.M;\n    const Element S = M, T\
    \ = M + 1;\n    State I(M);\n\n    while (true) {\n        vector<vector<Element>>\
    \ to(M + 2);\n        for (int e = 0; e < M; e++) if (!I[e]) {\n            vector<Element>\
    \ c1 = matroid1.circuit(I, e);\n            if (c1.empty()) to[e].push_back(T);\n\
    \            for (Element f : c1) to[e].push_back(f);\n            vector<Element>\
    \ c2 = matroid2.circuit(I, e);\n            if (c2.empty()) to[S].push_back(e);\n\
    \            for (Element f : c2) to[f].push_back(e);\n        }\n        vector<Element>\
    \ backtrack(M + 2, -1);\n        queue<Element> q;\n        q.push(S);\n     \
    \   while (!q.empty()) {\n            Element now = q.front();\n            q.pop();\n\
    \            if (now == T) break;\n            for (Element nxt : to[now]) {\n\
    \                if (backtrack[nxt] == -1) backtrack[nxt] = now, q.push(nxt);\n\
    \            }\n        }\n        Element e = backtrack[T];\n        if (e ==\
    \ -1) break;\n        while (e != S) I[e] = !I[e], e = backtrack[e];\n    }\n\
    \    return I;\n}\n\n\n// GraphMatroid: subgraph of undirected graphs, without\
    \ loops\nstruct GraphMatroid\n{\n    using Vertex = int;\n    int M;\n    int\
    \ V; // # of vertices of graph\n    vector<vector<pair<Vertex, Element>>> to;\n\
    \    vector<pair<Vertex, Vertex>> edges;\n    GraphMatroid() = default;\n    GraphMatroid(int\
    \ V, vector<pair<Vertex, Vertex>> edges_)\n        : M(edges_.size()), V(V), to(V),\
    \ edges(edges_)\n    {\n        for (size_t e = 0; e < edges_.size(); e++) {\n\
    \            assert(edges_[e].first < V and edges_[e].second < V);\n         \
    \   to[edges_[e].first].emplace_back(edges_[e].second, e);\n            to[edges_[e].second].emplace_back(edges_[e].first,\
    \ e);\n        }\n    }\n    vector<Element> circuit(State I, Element e)\n   \
    \ {\n        if (I[e]) return {};\n        assert(int(I.size()) == M and e < M);\n\
    \        vector<Element> backtrack(V, -1);\n        Vertex S = edges[e].first,\
    \ T = edges[e].second;\n        queue<Vertex> q;\n        q.push(S);\n       \
    \ while (!q.empty()) {\n            Vertex now = q.front();\n            q.pop();\n\
    \            for (auto nxt : to[now]) if (I[nxt.second]) {\n                I[nxt.second]\
    \ = 0;\n                backtrack[nxt.first] = nxt.second;\n                q.push(nxt.first);\n\
    \            }\n        }\n        vector<Element> ret;\n        while (backtrack[T]\
    \ != -1) {\n            ret.push_back(backtrack[T]);\n            T = edges[backtrack[T]].first\
    \ + edges[backtrack[T]].second - T;\n        }\n        return ret;\n    }\n};\n\
    \n\n// Partition matroid (partitional matroid) : direct sum of uniform matroids\n\
    struct PartitionMatroid\n{\n    int M;\n    vector<vector<Element>> parts;\n \
    \   vector<int> belong;\n    vector<int> maxi;\n    PartitionMatroid() = default;\n\
    \    // parts: partition of [0, 1, ..., M - 1]\n    // maxi: only maxi[i] elements\
    \ from parts[i] can be chosen for each i.\n    PartitionMatroid(int M, const vector<vector<int>>\
    \ &parts, const vector<int> &maxi)\n        : M(M), parts(parts), belong(M, -1),\
    \ maxi(maxi)\n    {\n        assert(parts.size() == maxi.size());\n        for\
    \ (size_t i = 0; i < parts.size(); i++)\n        {\n            for (Element x\
    \ : parts[i]) belong[x] = i;\n        }\n        for (Element e = 0; e < M; e++)\
    \ {\n            // assert(belong[e] != -1);\n            if (belong[e] == -1)\
    \ {\n                belong[e] = this->parts.size();\n                this->parts.emplace_back(vector<int>{e});\n\
    \                this->maxi.push_back(1);\n            }\n        }\n    }\n\n\
    \    vector<Element> circuit(const State &I, Element e) {\n        if (I[e]) return\
    \ {};\n        assert(int(I.size()) == M and e < M);\n        vector<Element>\
    \ ret;\n        int p = belong[e];\n        int cnt = 0;\n        for (Element\
    \ x : parts[p]) cnt += I[x];\n        if (cnt == maxi[p]) {\n            for (Element\
    \ x : parts[p]) if (I[x]) ret.push_back(x);\n        }\n        return ret;\n\
    \    }\n};\n#line 3 \"matroid/vector_matroid.hpp\"\n#include <bitset>\n#line 5\
    \ \"matroid/vector_matroid.hpp\"\n#include <unordered_map>\n#line 8 \"matroid/vector_matroid.hpp\"\
    \nusing namespace std;\n\n// CUT begin\n// Vector matroid on F2 : linearly independent\
    \ vectors\n// VDIM: max. dimension of vector space\n// Verified: SRM526.5 1000\
    \ (Used only for linear independence check)\ntemplate <int VDIM>\nstruct F2VectorMatroid\n\
    {\n    int M; // # of vectors\n    vector<bitset<VDIM>> mat;\n    mutable vector<unordered_map<State,\
    \ vector<Element>>> cache;\n    F2VectorMatroid() = default;\n    F2VectorMatroid(const\
    \ vector<bitset<VDIM>> &bitmat) : M(bitmat.size()), mat(bitmat), cache(bitmat.size())\
    \ {}\n\n    // If I is independent and I + {e} is not, return elements of the\
    \ circuit.\n    // If e \\in I, or I + {e} is independent, return empty vector.\n\
    \    // If I is NOT independent, undefined.\n    vector<Element> circuit(const\
    \ State &I, const Element &e) const\n    {\n        assert(int(I.size()) == M\
    \ and e < M);\n        if (I[e]) return {};\n        if (cache[e].count(I)) return\
    \ cache[e][I];\n        vector<bitset<VDIM + 1>> A(VDIM);\n        vector<int>\
    \ eid;\n        for (int i = 0; i < M; i++) {\n            if (!I[i]) continue;\n\
    \            for (int j = 0; j < VDIM; j++) A[j][eid.size()] = mat[i][j];\n  \
    \          eid.push_back(i);\n            if (eid.size() > VDIM) return {};\n\
    \        }\n        int n = eid.size();\n        for (int j = 0; j < VDIM; j++)\
    \ A[j][n] = mat[e][j];\n        for (int c = 0; c < n; c++) {\n            int\
    \ piv = -1;\n            for (int r = c; r < VDIM; r++) {\n                if\
    \ (A[r][c]) {\n                    piv = r;\n                    break;\n    \
    \            }\n            }\n            if (piv == -1) return cache[e][I] =\
    \ {};\n            swap(A[piv], A[c]);\n            for (int r = 0; r < VDIM;\
    \ r++) {\n                if (r != c and A[r][c]) A[r] ^= A[c];\n            }\n\
    \        }\n        for (int r = n; r < VDIM; r++) if (A[r][n]) return cache[e][I]\
    \ = {};\n        vector<Element> ret;\n        for (size_t i = 0; i < eid.size();\
    \ i++) {\n            if (A[i][n]) ret.push_back(eid[i]);\n        }\n       \
    \ return cache[e][I] = ret;\n    }\n};\n"
  code: "#pragma once\n#include \"matroid/matroid.hpp\"\n#include <bitset>\n#include\
    \ <cassert>\n#include <unordered_map>\n#include <utility>\n#include <vector>\n\
    using namespace std;\n\n// CUT begin\n// Vector matroid on F2 : linearly independent\
    \ vectors\n// VDIM: max. dimension of vector space\n// Verified: SRM526.5 1000\
    \ (Used only for linear independence check)\ntemplate <int VDIM>\nstruct F2VectorMatroid\n\
    {\n    int M; // # of vectors\n    vector<bitset<VDIM>> mat;\n    mutable vector<unordered_map<State,\
    \ vector<Element>>> cache;\n    F2VectorMatroid() = default;\n    F2VectorMatroid(const\
    \ vector<bitset<VDIM>> &bitmat) : M(bitmat.size()), mat(bitmat), cache(bitmat.size())\
    \ {}\n\n    // If I is independent and I + {e} is not, return elements of the\
    \ circuit.\n    // If e \\in I, or I + {e} is independent, return empty vector.\n\
    \    // If I is NOT independent, undefined.\n    vector<Element> circuit(const\
    \ State &I, const Element &e) const\n    {\n        assert(int(I.size()) == M\
    \ and e < M);\n        if (I[e]) return {};\n        if (cache[e].count(I)) return\
    \ cache[e][I];\n        vector<bitset<VDIM + 1>> A(VDIM);\n        vector<int>\
    \ eid;\n        for (int i = 0; i < M; i++) {\n            if (!I[i]) continue;\n\
    \            for (int j = 0; j < VDIM; j++) A[j][eid.size()] = mat[i][j];\n  \
    \          eid.push_back(i);\n            if (eid.size() > VDIM) return {};\n\
    \        }\n        int n = eid.size();\n        for (int j = 0; j < VDIM; j++)\
    \ A[j][n] = mat[e][j];\n        for (int c = 0; c < n; c++) {\n            int\
    \ piv = -1;\n            for (int r = c; r < VDIM; r++) {\n                if\
    \ (A[r][c]) {\n                    piv = r;\n                    break;\n    \
    \            }\n            }\n            if (piv == -1) return cache[e][I] =\
    \ {};\n            swap(A[piv], A[c]);\n            for (int r = 0; r < VDIM;\
    \ r++) {\n                if (r != c and A[r][c]) A[r] ^= A[c];\n            }\n\
    \        }\n        for (int r = n; r < VDIM; r++) if (A[r][n]) return cache[e][I]\
    \ = {};\n        vector<Element> ret;\n        for (size_t i = 0; i < eid.size();\
    \ i++) {\n            if (A[i][n]) ret.push_back(eid[i]);\n        }\n       \
    \ return cache[e][I] = ret;\n    }\n};\n"
  dependsOn:
  - matroid/matroid.hpp
  isVerificationFile: false
  path: matroid/vector_matroid.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: matroid/vector_matroid.hpp
layout: document
redirect_from:
- /library/matroid/vector_matroid.hpp
- /library/matroid/vector_matroid.hpp.html
title: matroid/vector_matroid.hpp
---
