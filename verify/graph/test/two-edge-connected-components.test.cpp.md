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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: graph/test/two-edge-connected-components.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cb3e5c672d961db00b76e36ddf5c068a">graph/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/test/two-edge-connected-components.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-06 01:35:47+09:00


* see: <a href="https://judge.yosupo.jp/problem/two_edge_connected_components">https://judge.yosupo.jp/problem/two_edge_connected_components</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/lowlink.hpp.html">graph/lowlink.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "graph/lowlink.hpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int V, E;
    std::cin >> V >> E;
    UndirectedGraph graph(V);
    while (E--) {
        int s, t;
        std::cin >> s >> t;
        graph.add_edge(s, t);
    }

    graph.detectBridge();
    graph.two_edge_connected_components();

    std::vector<std::pair<int, int>> bridges;
    for (int i = 0; i < E; i++) {
        if (graph.is_bridge[i]) {
            bridges.emplace_back(graph.edges[i]);
        }
    }
    std::cout << graph.tecc_num << '\n';
    std::vector<std::vector<int>> vids(V);
    for (int i = 0; i < V; i++)
    {
        vids[graph.tecc_id[i]].push_back(i);
    }
    for (const auto &v : vids) if (!v.empty()) {
        std::cout << v.size();
        for (auto x : v) std::cout << ' ' << x;
        std::cout << '\n';
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/test/two-edge-connected-components.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#line 2 "graph/lowlink.hpp"
#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>


// CUT begin
struct UndirectedGraph
{
    using pint = std::pair<int, int>;
    int V; // # of vertices
    int E; // # of edges
    int k;
    std::vector<std::vector<pint>> to;
    std::vector<pint> edges;
    std::vector<int> root_ids; // DFS forestの構築で根になった頂点

    std::vector<int> is_bridge; // Whether edge i is bridge or not, size = E
    std::vector<int> is_articulation; // whether vertex i is articulation point or not, size = V

    // lowlink
    std::vector<int> order;   // visiting order of DFS tree, size = V
    std::vector<int> lowlink; // size = V
    std::vector<int> is_dfstree_edge; // size = E

    int tecc_num; // 分割された二重辺連結成分数
    std::vector<int> tecc_id; // 各頂点が何個目の二重辺連結成分か

    UndirectedGraph(int V) : V(V), E(0), k(0), to(V),  order(V, -1), lowlink(V, -1) {}

    void add_edge(int v1, int v2)
    {
        assert(v1 >= 0 and v1 < V);
        assert(v2 >= 0 and v2 < V);
        to[v1].emplace_back(v2, E);
        to[v2].emplace_back(v1, E);
        edges.emplace_back(v1, v2);
        is_bridge.push_back(0);
        is_dfstree_edge.push_back(0);
        E++;
    }

    // Build DFS tree
    // Complexity: O(V + E)
    void dfs_lowlink(int now, int prv_eid = -1)
    {
        if (prv_eid == -1) root_ids.push_back(now);
        order[now] = lowlink[now] = k++;
        for (const auto &nxt : to[now]) if (nxt.second != prv_eid)
        {
            if (order[nxt.first] >= 0)
            {
                lowlink[now] = std::min(lowlink[now], order[nxt.first]);
            }
            else
            {
                is_dfstree_edge[nxt.second] = 1;
                dfs_lowlink(nxt.first, nxt.second);
                lowlink[now] = std::min(lowlink[now], lowlink[nxt.first]);
            }
        }
    }

    // Find all bridges
    // Complexity: O(V + E)
    void detectBridge()
    {
        for (int i = 0; i < E; i++)
        {
            int v1 = edges[i].first, v2 = edges[i].second;
            if (order[v1] < 0) dfs_lowlink(v1);
            if (order[v1] > order[v2]) std::swap(v1, v2);
            if (order[v1] < lowlink[v2]) is_bridge[i] = 1;
        }
    }

    // Find two-edge-connected components and classify all vertices
    // Complexity:  O(V + E)
    void two_edge_connected_components()
    {
        tecc_num = 0;
        tecc_id.assign(V, -1);

        for (int i = 0; i < V; i++) if (tecc_id[i] == -1)
        {
            tecc_id[i] = tecc_num;
            std::queue<int> que;
            que.push(i);
            while (!que.empty())
            {
                int now = que.front();
                que.pop();
                for (const auto &edge : to[now])
                {
                    int nxt = edge.first;
                    if (tecc_id[nxt] >= 0 or is_bridge[edge.second]) continue;
                    tecc_id[nxt] = tecc_num;
                    que.push(nxt);
                }
            }
            tecc_num++;
        }
    }


    void detectArticulation()
    {
        std::sort(root_ids.begin(), root_ids.end());
        is_articulation.assign(V, 0);
        for (int v = 0; v < V; v++)
        {
            if (std::binary_search(root_ids.begin(), root_ids.end(), v))
            {
                int n = 0;
                for (auto edge : to[v]) n += is_dfstree_edge[edge.second];
                if (n > 1) is_articulation[v] = 1;
            }
            else
            {
                for (auto e : to[v])
                {
                    if (is_dfstree_edge[e.second] and order[v] <= lowlink[e.first]) is_articulation[v] = 1;
                }
            }
        }
    }
};
#line 3 "graph/test/two-edge-connected-components.test.cpp"

#line 5 "graph/test/two-edge-connected-components.test.cpp"
#include <iostream>
#line 8 "graph/test/two-edge-connected-components.test.cpp"

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int V, E;
    std::cin >> V >> E;
    UndirectedGraph graph(V);
    while (E--) {
        int s, t;
        std::cin >> s >> t;
        graph.add_edge(s, t);
    }

    graph.detectBridge();
    graph.two_edge_connected_components();

    std::vector<std::pair<int, int>> bridges;
    for (int i = 0; i < E; i++) {
        if (graph.is_bridge[i]) {
            bridges.emplace_back(graph.edges[i]);
        }
    }
    std::cout << graph.tecc_num << '\n';
    std::vector<std::vector<int>> vids(V);
    for (int i = 0; i < V; i++)
    {
        vids[graph.tecc_id[i]].push_back(i);
    }
    for (const auto &v : vids) if (!v.empty()) {
        std::cout << v.size();
        for (auto x : v) std::cout << ' ' << x;
        std::cout << '\n';
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

