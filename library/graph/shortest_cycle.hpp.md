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


# :warning: graph/shortest_cycle.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/shortest_cycle.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-15 20:16:09+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <limits>
#include <deque>
#include <utility>
#include <vector>

// CUT begin
// Shortest cycle detection of UNDIRECTED SIMPLE graphs based on 01-BFS
// Assumption: only two types of edges are permitted: weight = 0 or W ( > 0)
// Complexity: O(E)
// Verified: <https://codeforces.com/contest/1325/problem/E>
struct ShortestCycle01
{
    int V, E;
    int INVALID = -1;
    std::vector<std::vector<std::pair<int, int>>> to;  // (nxt, weight)
    ShortestCycle01() = default;
    ShortestCycle01(int V) : V(V), E(0), to(V) {}
    void add_edge(int s, int t, int len) {
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        assert(len >= 0);
        to[s].emplace_back(t, len);
        to[t].emplace_back(s, len);
        E++;
    }

    std::vector<int> dist;
    std::vector<int> prev;
    // Find minimum length simple cycle which passes vertex `v`
    // - return: (LEN, (a, b))
    //   - LEN: length of the shortest cycles if exists, numeric_limits<int>::max() otherwise.
    //   - the cycle consists of vertices [v, ..., prev[prev[a]], prev[a], a, b, prev[b], prev[prev[b]], ..., v]
    std::pair<int, std::pair<int, int>> Solve(int v) {
        assert(0 <= v and v < V);
        dist.assign(V, std::numeric_limits<int>::max());
        dist[v] = 0;
        prev.assign(V, -1);
        std::deque<std::pair<int, int>> bfsq;
        std::vector<std::pair<std::pair<int, int>, int>> add_edge;
        bfsq.emplace_back(v, -1);
        while (!bfsq.empty()) {
            int now = bfsq.front().first, prv = bfsq.front().second;
            bfsq.pop_front();
            for (auto nxt : to[now]) if (nxt.first != prv) {
                if (dist[nxt.first] == std::numeric_limits<int>::max()) {
                    dist[nxt.first] = dist[now] + nxt.second;
                    prev[nxt.first] = now;
                    if (nxt.second) bfsq.emplace_back(nxt.first, now);
                    else bfsq.emplace_front(nxt.first, now);
                }
                else add_edge.emplace_back(std::make_pair(now, nxt.first), nxt.second);
            }
        }
        int minimum_cycle = std::numeric_limits<int>::max();
        int s = -1, t = -1;
        for (auto edge : add_edge) {
            int a = edge.first.first, b = edge.first.second;
            int L = dist[a] + dist[b] + edge.second;
            if (L < minimum_cycle) minimum_cycle = L, s = a, t = b;
        }
        return std::make_pair(minimum_cycle, std::make_pair(s, t));
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/shortest_cycle.hpp"
#include <cassert>
#include <limits>
#include <deque>
#include <utility>
#include <vector>

// CUT begin
// Shortest cycle detection of UNDIRECTED SIMPLE graphs based on 01-BFS
// Assumption: only two types of edges are permitted: weight = 0 or W ( > 0)
// Complexity: O(E)
// Verified: <https://codeforces.com/contest/1325/problem/E>
struct ShortestCycle01
{
    int V, E;
    int INVALID = -1;
    std::vector<std::vector<std::pair<int, int>>> to;  // (nxt, weight)
    ShortestCycle01() = default;
    ShortestCycle01(int V) : V(V), E(0), to(V) {}
    void add_edge(int s, int t, int len) {
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        assert(len >= 0);
        to[s].emplace_back(t, len);
        to[t].emplace_back(s, len);
        E++;
    }

    std::vector<int> dist;
    std::vector<int> prev;
    // Find minimum length simple cycle which passes vertex `v`
    // - return: (LEN, (a, b))
    //   - LEN: length of the shortest cycles if exists, numeric_limits<int>::max() otherwise.
    //   - the cycle consists of vertices [v, ..., prev[prev[a]], prev[a], a, b, prev[b], prev[prev[b]], ..., v]
    std::pair<int, std::pair<int, int>> Solve(int v) {
        assert(0 <= v and v < V);
        dist.assign(V, std::numeric_limits<int>::max());
        dist[v] = 0;
        prev.assign(V, -1);
        std::deque<std::pair<int, int>> bfsq;
        std::vector<std::pair<std::pair<int, int>, int>> add_edge;
        bfsq.emplace_back(v, -1);
        while (!bfsq.empty()) {
            int now = bfsq.front().first, prv = bfsq.front().second;
            bfsq.pop_front();
            for (auto nxt : to[now]) if (nxt.first != prv) {
                if (dist[nxt.first] == std::numeric_limits<int>::max()) {
                    dist[nxt.first] = dist[now] + nxt.second;
                    prev[nxt.first] = now;
                    if (nxt.second) bfsq.emplace_back(nxt.first, now);
                    else bfsq.emplace_front(nxt.first, now);
                }
                else add_edge.emplace_back(std::make_pair(now, nxt.first), nxt.second);
            }
        }
        int minimum_cycle = std::numeric_limits<int>::max();
        int s = -1, t = -1;
        for (auto edge : add_edge) {
            int a = edge.first.first, b = edge.first.second;
            int L = dist[a] + dist[b] + edge.second;
            if (L < minimum_cycle) minimum_cycle = L, s = a, t = b;
        }
        return std::make_pair(minimum_cycle, std::make_pair(s, t));
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

