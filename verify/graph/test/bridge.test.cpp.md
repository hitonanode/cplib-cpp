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


# :heavy_check_mark: graph/test/bridge.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/graph/test/bridge.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-08 14:58:12+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/lowlink.hpp.html">graph/lowlink.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <utility>
#include "graph/lowlink.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"

int main()
{
    int V, E;
    cin >> V >> E;
    UndirectedGraph graph(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        if (s > t) swap(s, t);
        graph.add_edge(s, t);
    }
    graph.dfs_lowlink(0);
    graph.detectBridge();

    vector<pair<int, int>> bridges;
    for (int i = 0; i < E; i++) {
        if (graph.isBridge[i]) {
            bridges.emplace_back(graph.edges[i]);
        }
    }
    sort(bridges.begin(), bridges.end());
    for (auto pa : bridges) {
        printf("%d %d\n", pa.first, pa.second);
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/test/bridge.test.cpp"
#include <iostream>
#include <utility>
#line 2 "graph/lowlink.hpp"
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

struct UndirectedGraph
{
    using pint = pair<int, int>;

    int V; // 頂点数
    int E; // 辺の数
    int k;
    vector<vector<pint>> to;
    vector<pint> edges;
    vector<int> root_id; // DFSで根になった頂点

    vector<int> isBridge; // edgesの各要素が橋かどうか
    vector<int> isArticulation; // 各頂点が間接点かどうか

    vector<int> order, lowlink, isusedforDFS; // lowlink

    int bec_num; // 分割された二重辺連結成分数
    vector<int> bec_id; // 各頂点が何個目の二重辺連結成分か

    UndirectedGraph(int V) : V(V), E(0), k(0),
                           to(vector<vector<pint> >(V)), 
                           order(vector<int>(V, -1)),
                           lowlink(vector<int>(V, -1)) {}

    void add_edge(int v1, int v2)
    {
        to[v1].push_back(pint(v2, E));
        to[v2].push_back(pint(v1, E));
        edges.push_back(pint(v1, v2));
        isBridge.push_back(0);
        isusedforDFS.push_back(0);
        E++;
    }

    void dfs_lowlink(int now, int prev = -1)
    {
        if (prev < 0 || prev >= V) root_id.push_back(now);
        order[now] = lowlink[now] = k;
        k++;
        for (auto nxt : to[now])
        {
            if (nxt.first == prev) continue;
            if (order[nxt.first] >= 0)
            {
                lowlink[now] = min(lowlink[now], order[nxt.first]);
            }
            else
            {
                isusedforDFS[nxt.second] = 1;
                dfs_lowlink(nxt.first, now);
                lowlink[now] = min(lowlink[now], lowlink[nxt.first]);
            }
        }
    }

    void detectBridge()
    {
        for (int i = 0; i < E; i++)
        {
            int v1 = edges[i].first, v2 = edges[i].second;
            if (order[v1] < 0) dfs_lowlink(v1);
            if (order[v1] > order[v2]) swap(v1, v2);
            if (order[v1] < lowlink[v2]) isBridge[i] = 1;
        }
    }

    void biconnected_edge_decompose()
    {
        bec_num = 0;
        bec_id = vector<int>(V, -1);

        for (int i = 0; i < V; i++)
        {
            if (bec_id[i] >= 0) continue;
            bec_id[i] = bec_num;
            queue<int> que;
            que.push(i);
            while (!que.empty())
            {
                int now = que.front();
                que.pop();
                for (auto edge : to[now])
                {
                    int nxt = edge.first;
                    if (bec_id[nxt] >= 0 || isBridge[edge.second]) continue;
                    bec_id[nxt] = bec_num;
                    que.push(nxt);
                }
            }
            bec_num++;
        }
    }

    void detectArticulation()
    {
        // sort(root_id.begin(), root_id.end());
        isArticulation = vector<int>(V);
        for (int v = 0; v < V; v++)
        {
            if (binary_search(root_id.begin(), root_id.end(), v))
            {
                int n = 0;
                for (auto edge : to[v]) n += isusedforDFS[edge.second];
                if (n > 1) isArticulation[v] = 1;
            }
            else
            {
                for (auto e : to[v])
                {
                    if (isusedforDFS[e.second] && order[v] <= lowlink[e.first]) isArticulation[v] = 1;
                }
            }
        }
    }
};
#line 4 "graph/test/bridge.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"

int main()
{
    int V, E;
    cin >> V >> E;
    UndirectedGraph graph(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        if (s > t) swap(s, t);
        graph.add_edge(s, t);
    }
    graph.dfs_lowlink(0);
    graph.detectBridge();

    vector<pair<int, int>> bridges;
    for (int i = 0; i < E; i++) {
        if (graph.isBridge[i]) {
            bridges.emplace_back(graph.edges[i]);
        }
    }
    sort(bridges.begin(), bridges.end());
    for (auto pa : bridges) {
        printf("%d %d\n", pa.first, pa.second);
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

