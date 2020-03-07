---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: matroid/vector_matroid.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#2a6c9c56c5dd30cd2db2c415985dabce">matroid</a>
* <a href="{{ site.github.repository_url }}/blob/master/matroid/vector_matroid.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Depends on

* :warning: <a href="matroid.hpp.html">matroid/matroid.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include "matroid/matroid.hpp"
#include <bitset>
#include <cassert>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

// CUT begin
// Vector matroid on F2 : linearly independent vectors
// VDIM: max. dimension of vector space
// Verified: SRM526.5 1000 (Used only for linear independence check)
template <int VDIM>
struct F2VectorMatroid
{
    int M; // # of vectors
    vector<bitset<VDIM>> mat;
    mutable vector<unordered_map<State, vector<Element>>> cache;
    F2VectorMatroid() = default;
    F2VectorMatroid(const vector<bitset<VDIM>> &bitmat) : M(bitmat.size()), mat(bitmat), cache(bitmat.size()) {}

    // If I is independent and I + {e} is not, return elements of the circuit.
    // If e \in I, or I + {e} is independent, return empty vector.
    // If I is NOT independent, undefined.
    vector<Element> circuit(const State &I, const Element &e) const
    {
        assert(int(I.size()) == M and e < M);
        if (I[e]) return {};
        if (cache[e].count(I)) return cache[e][I];
        vector<bitset<VDIM + 1>> A(VDIM);
        vector<int> eid;
        for (int i = 0; i < M; i++) {
            if (!I[i]) continue;
            for (int j = 0; j < VDIM; j++) A[j][eid.size()] = mat[i][j];
            eid.push_back(i);
            if (eid.size() > VDIM) return {};
        }
        int n = eid.size();
        for (int j = 0; j < VDIM; j++) A[j][n] = mat[e][j];
        for (int c = 0; c < n; c++) {
            int piv = -1;
            for (int r = c; r < VDIM; r++) {
                if (A[r][c]) {
                    piv = r;
                    break;
                }
            }
            if (piv == -1) return cache[e][I] = {};
            swap(A[piv], A[c]);
            for (int r = 0; r < VDIM; r++) {
                if (r != c and A[r][c]) A[r] ^= A[c];
            }
        }
        for (int r = n; r < VDIM; r++) if (A[r][n]) return cache[e][I] = {};
        vector<Element> ret;
        for (size_t i = 0; i < eid.size(); i++) {
            if (A[i][n]) ret.push_back(eid[i]);
        }
        return cache[e][I] = ret;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "matroid/matroid.hpp"
#include <cassert>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

// CUT begin
using Element = int;
using State = vector<bool>;

struct MatroidExample
{
    int M; // # of elements of set we consider

    // If I is independent and I + {e} is not, return elements of the circuit.
    // If e \in I, or I + {e} is independent, return empty vector.
    // If I is NOT independent, undefined.
    vector<Element> circuit(State I, Element e);
};

// Matroid intersection solver
// Algorithm based on <http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/>
// Complexity: O(CE^2 + E^3) (C : circuit query)
template <typename T_M1, typename T_M2>
State MatroidIntersection(T_M1 matroid1, T_M2 matroid2)
{
    assert(matroid1.M == matroid2.M);

    const int M = matroid1.M;
    const Element S = M, T = M + 1;
    State I(M);

    while (true) {
        vector<vector<Element>> to(M + 2);
        for (int e = 0; e < M; e++) if (!I[e]) {
            vector<Element> c1 = matroid1.circuit(I, e);
            if (c1.empty()) to[e].push_back(T);
            for (Element f : c1) to[e].push_back(f);
            vector<Element> c2 = matroid2.circuit(I, e);
            if (c2.empty()) to[S].push_back(e);
            for (Element f : c2) to[f].push_back(e);
        }
        vector<Element> backtrack(M + 2, -1);
        queue<Element> q;
        q.push(S);
        while (!q.empty()) {
            Element now = q.front();
            q.pop();
            if (now == T) break;
            for (Element nxt : to[now]) {
                if (backtrack[nxt] == -1) backtrack[nxt] = now, q.push(nxt);
            }
        }
        Element e = backtrack[T];
        if (e == -1) break;
        while (e != S) I[e] = !I[e], e = backtrack[e];
    }
    return I;
}


// GraphMatroid: subgraph of undirected graphs, without loops
struct GraphMatroid
{
    using Vertex = int;
    int M;
    int V; // # of vertices of graph
    vector<vector<pair<Vertex, Element>>> to;
    vector<pair<Vertex, Vertex>> edges;
    GraphMatroid() = default;
    GraphMatroid(int V, vector<pair<Vertex, Vertex>> edges_)
        : M(edges_.size()), V(V), to(V), edges(edges_)
    {
        for (size_t e = 0; e < edges_.size(); e++) {
            assert(edges_[e].first < V and edges_[e].second < V);
            to[edges_[e].first].emplace_back(edges_[e].second, e);
            to[edges_[e].second].emplace_back(edges_[e].first, e);
        }
    }
    vector<Element> circuit(State I, Element e)
    {
        if (I[e]) return {};
        assert(int(I.size()) == M and e < M);
        vector<Element> backtrack(V, -1);
        Vertex S = edges[e].first, T = edges[e].second;
        queue<Vertex> q;
        q.push(S);
        while (!q.empty()) {
            Vertex now = q.front();
            q.pop();
            for (auto nxt : to[now]) if (I[nxt.second]) {
                I[nxt.second] = 0;
                backtrack[nxt.first] = nxt.second;
                q.push(nxt.first);
            }
        }
        vector<Element> ret;
        while (backtrack[T] != -1) {
            ret.push_back(backtrack[T]);
            T = edges[backtrack[T]].first + edges[backtrack[T]].second - T;
        }
        return ret;
    }
};


// Partition matroid (partitional matroid) : direct sum of uniform matroids
struct PartitionMatroid
{
    int M;
    vector<vector<Element>> parts;
    vector<int> belong;
    vector<int> maxi;
    PartitionMatroid() = default;
    // parts: partition of [0, 1, ..., M - 1]
    // maxi: only maxi[i] elements from parts[i] can be chosen for each i.
    PartitionMatroid(int M, const vector<vector<int>> &parts, const vector<int> &maxi)
        : M(M), parts(parts), belong(M, -1), maxi(maxi)
    {
        assert(parts.size() == maxi.size());
        for (size_t i = 0; i < parts.size(); i++)
        {
            for (Element x : parts[i]) belong[x] = i;
        }
        for (Element e = 0; e < M; e++) {
            // assert(belong[e] != -1);
            if (belong[e] == -1) {
                belong[e] = this->parts.size();
                this->parts.emplace_back(vector<int>{e});
                this->maxi.push_back(1);
            }
        }
    }

    vector<Element> circuit(const State &I, Element e) {
        if (I[e]) return {};
        assert(int(I.size()) == M and e < M);
        vector<Element> ret;
        int p = belong[e];
        int cnt = 0;
        for (Element x : parts[p]) cnt += I[x];
        if (cnt == maxi[p]) {
            for (Element x : parts[p]) if (I[x]) ret.push_back(x);
        }
        return ret;
    }
};
#line 3 "matroid/vector_matroid.hpp"
#include <bitset>
#include <cassert>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

// CUT begin
// Vector matroid on F2 : linearly independent vectors
// VDIM: max. dimension of vector space
// Verified: SRM526.5 1000 (Used only for linear independence check)
template <int VDIM>
struct F2VectorMatroid
{
    int M; // # of vectors
    vector<bitset<VDIM>> mat;
    mutable vector<unordered_map<State, vector<Element>>> cache;
    F2VectorMatroid() = default;
    F2VectorMatroid(const vector<bitset<VDIM>> &bitmat) : M(bitmat.size()), mat(bitmat), cache(bitmat.size()) {}

    // If I is independent and I + {e} is not, return elements of the circuit.
    // If e \in I, or I + {e} is independent, return empty vector.
    // If I is NOT independent, undefined.
    vector<Element> circuit(const State &I, const Element &e) const
    {
        assert(int(I.size()) == M and e < M);
        if (I[e]) return {};
        if (cache[e].count(I)) return cache[e][I];
        vector<bitset<VDIM + 1>> A(VDIM);
        vector<int> eid;
        for (int i = 0; i < M; i++) {
            if (!I[i]) continue;
            for (int j = 0; j < VDIM; j++) A[j][eid.size()] = mat[i][j];
            eid.push_back(i);
            if (eid.size() > VDIM) return {};
        }
        int n = eid.size();
        for (int j = 0; j < VDIM; j++) A[j][n] = mat[e][j];
        for (int c = 0; c < n; c++) {
            int piv = -1;
            for (int r = c; r < VDIM; r++) {
                if (A[r][c]) {
                    piv = r;
                    break;
                }
            }
            if (piv == -1) return cache[e][I] = {};
            swap(A[piv], A[c]);
            for (int r = 0; r < VDIM; r++) {
                if (r != c and A[r][c]) A[r] ^= A[c];
            }
        }
        for (int r = n; r < VDIM; r++) if (A[r][n]) return cache[e][I] = {};
        vector<Element> ret;
        for (size_t i = 0; i < eid.size(); i++) {
            if (A[i][n]) ret.push_back(eid[i]);
        }
        return cache[e][I] = ret;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

