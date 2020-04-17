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


# :warning: graph/grid_graph_template.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/grid_graph_template.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 04:11:17+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <array>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
struct GridGraph
{

    int H, W;
    const std::vector<int> dx{1, -1, 0, 0};
    const std::vector<int> dy{0, 0, 1, -1};

    GridGraph() = default;
    GridGraph(int h, int w) : H(h), W(w) {}

    /* Implement here. */
    using T_E = long long int;
    const T_E INF = 1e18;
    inline T_E edge_cost(int x_s, int y_s, int x_t, int y_t)
    {
        return 0;
    }

    // Dijkstra's algorithm
    // Complexity: O(HWlog(HW))
    std::vector<std::vector<T_E>> dij; // Distance from (x_s, y_s)
    std::vector<std::vector<std::pair<int, int>>> dij_prv; // Previous node for Dijkstra optimal path
    void dijkstra(int x_s, int y_s) {
        dij.assign(H, std::vector<T_E>(W, INF));
        dij_prv.assign(H, std::vector<std::pair<int, int>>(W, std::make_pair(-1, -1)));

        using P = std::tuple<T_E, int, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        dij[x_s][y_s] = 0;
        pq.emplace(0, x_s, y_s);
        while (!pq.empty()) {
            T_E dnow;
            int x, y;
            std::tie(dnow, x, y) = pq.top();
            pq.pop();
            if (dij[x][y] < dnow) continue;
            for (size_t d = 0; d < dx.size(); d++) {
                int xn = x + dx[d], yn = y + dy[d];
                if (xn < 0 or yn < 0 or xn >= H or yn >= W) continue;
                T_E dnxt = dnow + edge_cost(x, y, xn, yn);
                if (dnxt < dij[xn][yn]) {
                    dij[xn][yn] = dnxt;
                    dij_prv[xn][yn] = std::make_pair(x, y);
                    pq.emplace(dnxt, xn, yn);
                }
            }
        }
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/grid_graph_template.hpp"
#include <array>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
struct GridGraph
{

    int H, W;
    const std::vector<int> dx{1, -1, 0, 0};
    const std::vector<int> dy{0, 0, 1, -1};

    GridGraph() = default;
    GridGraph(int h, int w) : H(h), W(w) {}

    /* Implement here. */
    using T_E = long long int;
    const T_E INF = 1e18;
    inline T_E edge_cost(int x_s, int y_s, int x_t, int y_t)
    {
        return 0;
    }

    // Dijkstra's algorithm
    // Complexity: O(HWlog(HW))
    std::vector<std::vector<T_E>> dij; // Distance from (x_s, y_s)
    std::vector<std::vector<std::pair<int, int>>> dij_prv; // Previous node for Dijkstra optimal path
    void dijkstra(int x_s, int y_s) {
        dij.assign(H, std::vector<T_E>(W, INF));
        dij_prv.assign(H, std::vector<std::pair<int, int>>(W, std::make_pair(-1, -1)));

        using P = std::tuple<T_E, int, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        dij[x_s][y_s] = 0;
        pq.emplace(0, x_s, y_s);
        while (!pq.empty()) {
            T_E dnow;
            int x, y;
            std::tie(dnow, x, y) = pq.top();
            pq.pop();
            if (dij[x][y] < dnow) continue;
            for (size_t d = 0; d < dx.size(); d++) {
                int xn = x + dx[d], yn = y + dy[d];
                if (xn < 0 or yn < 0 or xn >= H or yn >= W) continue;
                T_E dnxt = dnow + edge_cost(x, y, xn, yn);
                if (dnxt < dij[xn][yn]) {
                    dij[xn][yn] = dnxt;
                    dij_prv[xn][yn] = std::make_pair(x, y);
                    pq.emplace(dnxt, xn, yn);
                }
            }
        }
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

