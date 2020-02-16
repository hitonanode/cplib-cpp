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

* <a href="{{ site.github.repository_url }}/blob/master/graph/test/dijkstra.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-08 14:58:12+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/dijkstra.hpp.html">graph/dijkstra.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <vector>
#include "graph/dijkstra.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"

wedges e;

int main()
{
    int V, E, r;
    cin >> V >> E >> r;
    e.resize(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        e[s].emplace_back(t, d);
    }
    auto ret = dijkstra(V, r, e);

    for (int i = 0; i < V; i++) {
        if (ret.first[i] == INF) puts("INF");
        else printf("%lld\n", ret.first[i]);
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/test/dijkstra.test.cpp"
#include <iostream>
#include <vector>
#line 2 "graph/dijkstra.hpp"
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using lint = long long int;
using plint = pair<lint, lint>;

using wedges = vector<vector<plint>>; // (to, weight)

constexpr lint INF = 1e17;
pair<vector<lint>, vector<int>> dijkstra(int N, int s, const wedges &w)
{
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
#line 4 "graph/test/dijkstra.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"

wedges e;

int main()
{
    int V, E, r;
    cin >> V >> E >> r;
    e.resize(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        e[s].emplace_back(t, d);
    }
    auto ret = dijkstra(V, r, e);

    for (int i = 0; i < V; i++) {
        if (ret.first[i] == INF) puts("INF");
        else printf("%lld\n", ret.first[i]);
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

