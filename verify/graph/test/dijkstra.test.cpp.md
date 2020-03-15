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


# :heavy_check_mark: graph/test/dijkstra.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cb3e5c672d961db00b76e36ddf5c068a">graph/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/test/dijkstra.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-15 20:16:09+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/dijkstra.hpp.html">graph/dijkstra.hpp</a>
* :heavy_check_mark: <a href="../../../library/graph/shortest_path.hpp.html">graph/shortest_path.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cassert>
#include <iostream>
#include <vector>
#include "graph/dijkstra.hpp"
#include "graph/shortest_path.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"

wedges e;

int main()
{
    int V, E, r;
    cin >> V >> E >> r;
    e.resize(V);
    ShortestPath<int> graph(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        e[s].emplace_back(t, d);
        graph.add_edge(s, t, d);
    }
    auto ret = dijkstra(V, r, e);
    graph.Dijkstra(r);

    for (int i = 0; i < V; i++) {
        if (ret.first[i] == INF) puts("INF");
        else {
            assert(ret.first[i] == graph.dist[i]);
            printf("%lld\n", ret.first[i]);
        }
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/test/dijkstra.test.cpp"
#include <cassert>
#include <iostream>
#include <vector>
#line 2 "graph/dijkstra.hpp"
#include <queue>
#include <utility>
#line 5 "graph/dijkstra.hpp"
using namespace std;

using wedges = vector<vector<pair<long long int, long long int>>>; // (to, weight)

constexpr long long int INF = 1e17;
pair<vector<long long int>, vector<int>> dijkstra(int N, int s, const wedges &w)
{
    using lint = long long int;
    using plint = pair<long long int, long long int>;
    vector<lint> dist(N, INF);
    dist[s] = 0;
    vector<int> prev(N, -1);
    priority_queue<plint, vector<plint>, greater<plint>> pq;
    pq.emplace(0, s);
    while (!pq.empty())
    {
        plint p = pq.top();
        pq.pop();
        int v = p.second;
        if (dist[v] < p.first) continue;
        for (auto nx : w[v])
        {
            lint dnx = p.first + nx.second;
            if (dist[nx.first] > dnx)
            {
                dist[nx.first] = dnx, prev[nx.first] = v;
                pq.emplace(dnx, nx.first);
            }
        }
    }
    return make_pair(dist, prev); // (distance, previous_node)
}
#line 3 "graph/shortest_path.hpp"
#include <functional>
#include <limits>
#line 8 "graph/shortest_path.hpp"

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
    // Dijkstra algorithm
    // Complexity: O(E log E)
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

    // Bellman-Ford algorithm
    // Complexity: O(VE)
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
    // Warshall-Floyd algorithm
    // Complexity: O(E + V^3)
    std::vector<std::vector<T>> dist2d;
    void WarshallFloyd() {
        dist2d.assign(V, std::vector<T>(V, std::numeric_limits<T>::max()));
        for (int i = 0; i < V; i++) {
            dist2d[i][i] = 0;
            for (auto p : to[i]) dist2d[i][p.first] = min(dist2d[i][p.first], p.second);
        }
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                if (dist2d[i][k] = std::numeric_limits<T>::max()) continue;
                for (int j = 0; j < V; j++) {
                    if (dist2d[k][j] = std::numeric_limits<T>::max()) continue;
                    dist2d[i][j] = min(dist2d[i][j], dist2d[i][k] + dist2d[k][j]);
                }
            }
        }
    }
};
#line 6 "graph/test/dijkstra.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"

wedges e;

int main()
{
    int V, E, r;
    cin >> V >> E >> r;
    e.resize(V);
    ShortestPath<int> graph(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        e[s].emplace_back(t, d);
        graph.add_edge(s, t, d);
    }
    auto ret = dijkstra(V, r, e);
    graph.Dijkstra(r);

    for (int i = 0; i < V; i++) {
        if (ret.first[i] == INF) puts("INF");
        else {
            assert(ret.first[i] == graph.dist[i]);
            printf("%lld\n", ret.first[i]);
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

