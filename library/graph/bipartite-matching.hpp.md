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


# :heavy_check_mark: graph/bipartite-matching.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/bipartite-matching.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:40:57+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/graph/test/bipartite-matching.test.cpp.html">graph/test/bipartite-matching.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <iostream>
#include <vector>
using namespace std;

// CUT begin
// 二部グラフの最大マッチング bipartite-matching of undirected bipartite graph
// <https://ei1333.github.io/luzhiled/snippets/graph/bipartite-matching.html>
// Comprexity: O(VE)
struct BipartiteMatching
{
    int V;  // # of vertices
    vector<vector<int>> edges;  // Adjacency list
    vector<int> match;  // match[i] = (Partner of i'th node) or -1 (No parter)
    vector<int> used;
    int timestamp;
    BipartiteMatching(int V = 0) : V(V), edges(V), match(V, -1), used(V, 0), timestamp(0) {}

    void add_edge(int u, int v)
    {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    bool dfs(int v)
    {
        used[v] = timestamp;
        for (auto to : edges[v])
        {
            if (match[to] < 0 or (used[match[to]] != timestamp and dfs(match[to])))
            {
                match[v] = to;
                match[to] = v;
                return true;
            }
        }
        return false;
    }

    int solve() // Count up newly formed pairs
    {
        int ret = 0;
        for (int v = 0; v < V; v++) if (match[v] < 0)
        {
            ++timestamp;
            ret += dfs(v);
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const BipartiteMatching &bm)
    {
        os << "{V=" << bm.V << ":";
        for (int i = 0; i < bm.V; i++) if (i < bm.match[i])
        {
            os << "(" << i << "-" << bm.match[i] << "),";
        }
        os << "}";
        return os;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/bipartite-matching.hpp"
#include <iostream>
#include <vector>
using namespace std;

// CUT begin
// 二部グラフの最大マッチング bipartite-matching of undirected bipartite graph
// <https://ei1333.github.io/luzhiled/snippets/graph/bipartite-matching.html>
// Comprexity: O(VE)
struct BipartiteMatching
{
    int V;  // # of vertices
    vector<vector<int>> edges;  // Adjacency list
    vector<int> match;  // match[i] = (Partner of i'th node) or -1 (No parter)
    vector<int> used;
    int timestamp;
    BipartiteMatching(int V = 0) : V(V), edges(V), match(V, -1), used(V, 0), timestamp(0) {}

    void add_edge(int u, int v)
    {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    bool dfs(int v)
    {
        used[v] = timestamp;
        for (auto to : edges[v])
        {
            if (match[to] < 0 or (used[match[to]] != timestamp and dfs(match[to])))
            {
                match[v] = to;
                match[to] = v;
                return true;
            }
        }
        return false;
    }

    int solve() // Count up newly formed pairs
    {
        int ret = 0;
        for (int v = 0; v < V; v++) if (match[v] < 0)
        {
            ++timestamp;
            ret += dfs(v);
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const BipartiteMatching &bm)
    {
        os << "{V=" << bm.V << ":";
        for (int i = 0; i < bm.V; i++) if (i < bm.match[i])
        {
            os << "(" << i << "-" << bm.match[i] << "),";
        }
        os << "}";
        return os;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

