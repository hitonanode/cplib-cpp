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


# :heavy_check_mark: graph/bipartite_matching.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/bipartite_matching.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 18:32:38+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/graph/test/bipartite_matching.test.cpp.html">graph/test/bipartite_matching.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <iostream>
#include <vector>
#include <queue>

// CUT begin
// Bipartite matching of undirected bipartite graph (Hopcroft-Karp)
// <https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html>
// Comprexity: O(EsqrtV)
struct BipartiteMatching
{
    int N, M;
    std::vector<std::vector<int>> to; // Adjacency list
    std::vector<int> dist;            // dist[i] = (Distance from i'th node)
    std::vector<int> match;           // match[j] = (Partner of j'th node) or -1 (No parter)
    std::vector<int> used, vv;

    BipartiteMatching() = default;
    BipartiteMatching(int N_, int M_) : N(N_), M(M_), to(N_), match(M_, -1), used(N_) {}

    void add_edge(int u, int v)
    {
        assert(u >= 0 and u < N and v >= 0 and v < M);
        to[u].push_back(v);
    }

    void bfs()
    {
        dist.assign(N, -1);
        std::queue<int> q;
        for (int i = 0; i < N; i++) {
            if (!used[i]) {
                q.emplace(i), dist[i] = 0;
            }
        }

        while (!q.empty()) {
            int a = q.front();
            q.pop();
            for (auto b : to[a]) {
                int c = match[b];
                if (c >= 0 and dist[c] == -1) {
                    q.emplace(c), dist[c] = dist[a] + 1;
                }
            }
        }
    }

    bool dfs(int a)
    {
        vv[a] = true;
        for (auto b : to[a]) {
            int c = match[b];
            if (c < 0 or (!vv[c] and dist[c] == dist[a] + 1 and dfs(c))) {
                match[b] = a;
                used[a] = true;
                return true;
            }
        }
        return false;
    }

    int solve()
    {
        int ret = 0;
        while (true) {
            bfs();
            vv.assign(N, false);
            int flow = 0;
            for (int i = 0; i < N; i++) if (!used[i] and dfs(i)) flow++;
            if (!flow) break;
            ret += flow;
        }
        return ret;
    }

    friend std::ostream &operator<<(std::ostream &os, const BipartiteMatching &bm)
    {
        os << "{(N,M)=" << bm.N << ',' << bm.M << ':';
        for (int j = 0; j < bm.M; j++) if (bm.match[j] >= 0)
        {
            os << '(' << bm.match[j] << '-' << j << "),";
        }
        os << '}';
        return os;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/bipartite_matching.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <queue>

// CUT begin
// Bipartite matching of undirected bipartite graph (Hopcroft-Karp)
// <https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html>
// Comprexity: O(EsqrtV)
struct BipartiteMatching
{
    int N, M;
    std::vector<std::vector<int>> to; // Adjacency list
    std::vector<int> dist;            // dist[i] = (Distance from i'th node)
    std::vector<int> match;           // match[j] = (Partner of j'th node) or -1 (No parter)
    std::vector<int> used, vv;

    BipartiteMatching() = default;
    BipartiteMatching(int N_, int M_) : N(N_), M(M_), to(N_), match(M_, -1), used(N_) {}

    void add_edge(int u, int v)
    {
        assert(u >= 0 and u < N and v >= 0 and v < M);
        to[u].push_back(v);
    }

    void bfs()
    {
        dist.assign(N, -1);
        std::queue<int> q;
        for (int i = 0; i < N; i++) {
            if (!used[i]) {
                q.emplace(i), dist[i] = 0;
            }
        }

        while (!q.empty()) {
            int a = q.front();
            q.pop();
            for (auto b : to[a]) {
                int c = match[b];
                if (c >= 0 and dist[c] == -1) {
                    q.emplace(c), dist[c] = dist[a] + 1;
                }
            }
        }
    }

    bool dfs(int a)
    {
        vv[a] = true;
        for (auto b : to[a]) {
            int c = match[b];
            if (c < 0 or (!vv[c] and dist[c] == dist[a] + 1 and dfs(c))) {
                match[b] = a;
                used[a] = true;
                return true;
            }
        }
        return false;
    }

    int solve()
    {
        int ret = 0;
        while (true) {
            bfs();
            vv.assign(N, false);
            int flow = 0;
            for (int i = 0; i < N; i++) if (!used[i] and dfs(i)) flow++;
            if (!flow) break;
            ret += flow;
        }
        return ret;
    }

    friend std::ostream &operator<<(std::ostream &os, const BipartiteMatching &bm)
    {
        os << "{(N,M)=" << bm.N << ',' << bm.M << ':';
        for (int j = 0; j < bm.M; j++) if (bm.match[j] >= 0)
        {
            os << '(' << bm.match[j] << '-' << j << "),";
        }
        os << '}';
        return os;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

