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


# :heavy_check_mark: graph/shortest_path.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/shortest_path.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:40:57+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/graph/test/bellman_ford.test.cpp.html">graph/test/bellman_ford.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/graph/test/dijkstra.test.cpp.html">graph/test/dijkstra.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

// CUT begin
template<typename T>
struct ShortestPath
{
    int V, E;
    int INVALID = -1;
    std::vector<std::vector<std::pair<int, T>>> to;
    ShortestPath() = default;
    ShortestPath(int V) : V(V), E(0), to(V) {}
    void add_edge(int s, int t, T len) {
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        to[s].emplace_back(t, len);
        E++;
    }

    std::vector<T> dist;
    std::vector<int> prev;
    void Dijkstra(int s) {
        assert(0 <= s and s < V);
        dist.assign(V, std::numeric_limits<T>::max());
        dist[s] = 0;
        prev.assign(V, INVALID);
        using P = std::pair<T, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        pq.emplace(0, s);
        while(!pq.empty()) {
            T d;
            int v;
            std::tie(d, v) = pq.top();
            pq.pop();
            if (dist[v] < d) continue;
            for (auto nx : to[v]) {
                T dnx = d + nx.second;
                if (dist[nx.first] > dnx) {
                    dist[nx.first] = dnx, prev[nx.first] = v;
                    pq.emplace(dnx, nx.first);
                }
            }
        }
    }

    bool BellmanFord(int s, int nb_loop) {
        assert(0 <= s and s < V);
        dist.assign(V, std::numeric_limits<T>::max());
        dist[s] = 0;
        prev.assign(V, INVALID);
        for (int l = 0; l < nb_loop; l++) {
            bool upd = false;
            for (int v = 0; v < V; v++) {
                if (dist[v] == std::numeric_limits<T>::max()) continue;
                for (auto nx : to[v]) {
                    T dnx = dist[v] + nx.second;
                    if (dist[nx.first] > dnx) {
                        dist[nx.first] = dnx, prev[nx.first] = v;
                        upd = true;
                    }
                }
            }
            if (!upd) return true;
        }
        return false;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/shortest_path.hpp"
#include <cassert>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

// CUT begin
template<typename T>
struct ShortestPath
{
    int V, E;
    int INVALID = -1;
    std::vector<std::vector<std::pair<int, T>>> to;
    ShortestPath() = default;
    ShortestPath(int V) : V(V), E(0), to(V) {}
    void add_edge(int s, int t, T len) {
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        to[s].emplace_back(t, len);
        E++;
    }

    std::vector<T> dist;
    std::vector<int> prev;
    void Dijkstra(int s) {
        assert(0 <= s and s < V);
        dist.assign(V, std::numeric_limits<T>::max());
        dist[s] = 0;
        prev.assign(V, INVALID);
        using P = std::pair<T, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        pq.emplace(0, s);
        while(!pq.empty()) {
            T d;
            int v;
            std::tie(d, v) = pq.top();
            pq.pop();
            if (dist[v] < d) continue;
            for (auto nx : to[v]) {
                T dnx = d + nx.second;
                if (dist[nx.first] > dnx) {
                    dist[nx.first] = dnx, prev[nx.first] = v;
                    pq.emplace(dnx, nx.first);
                }
            }
        }
    }

    bool BellmanFord(int s, int nb_loop) {
        assert(0 <= s and s < V);
        dist.assign(V, std::numeric_limits<T>::max());
        dist[s] = 0;
        prev.assign(V, INVALID);
        for (int l = 0; l < nb_loop; l++) {
            bool upd = false;
            for (int v = 0; v < V; v++) {
                if (dist[v] == std::numeric_limits<T>::max()) continue;
                for (auto nx : to[v]) {
                    T dnx = dist[v] + nx.second;
                    if (dist[nx.first] > dnx) {
                        dist[nx.first] = dnx, prev[nx.first] = v;
                        upd = true;
                    }
                }
            }
            if (!upd) return true;
        }
        return false;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

