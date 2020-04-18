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


# :heavy_check_mark: graph/test/bipartite_matching.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cb3e5c672d961db00b76e36ddf5c068a">graph/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/test/bipartite_matching.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 19:20:50+09:00


* see: <a href="https://judge.yosupo.jp/problem/bipartitematching">https://judge.yosupo.jp/problem/bipartitematching</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/bipartite_matching.hpp.html">graph/bipartite_matching.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "graph/bipartite_matching.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <algorithm>
#include <numeric>
#include <random>

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int L, R, M;
    std::cin >> L >> R >> M;

    std::vector<int> perm(L + R), perm_inv(L + R);
    std::iota(perm.begin(), perm.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(perm.begin(), perm.end(), g);
    for (int i = 0; i < L + R; i++)
    {
        perm_inv[perm[i]] = i;
    }

    BipartiteMatching bm(L + R);
    while (M--)
    {
        int a, b;
        std::cin >> a >> b;
        bm.add_edge(perm[a], perm[L + b]);
    }

    std::cout << bm.solve() << '\n';
    for (int j = 0; j < L + R; j++) if (bm.match[j] > j) {
        int a = perm_inv[j], b = perm_inv[bm.match[j]];
        if (a > b) std::cout << b << ' ' << a - L << '\n';
        else std::cout << a << ' ' << b - L << '\n';
    }
}

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
// int solve(): enumerate maximum number of matching / return -1 (if graph is not bipartite)
struct BipartiteMatching
{
    int V;
    std::vector<std::vector<int>> to; // Adjacency list
    std::vector<int> dist;            // dist[i] = (Distance from i'th node)
    std::vector<int> match;           // match[i] = (Partner of i'th node) or -1 (No parter)
    std::vector<int> used, vv;        //
    std::vector<int> color;           // color of each node(checking bipartition): 0/1/-1(not determined)

    BipartiteMatching() = default;
    BipartiteMatching(int V_) : V(V_), to(V_), match(V_, -1), used(V_), color(V_, -1) {}

    void add_edge(int u, int v)
    {
        assert(u >= 0 and u < V and v >= 0 and v < V and u != v);
        to[u].push_back(v);
        to[v].push_back(u);
    }

    void bfs()
    {
        dist.assign(V, -1);
        std::queue<int> q;
        for (int i = 0; i < V; i++) {
            if (!color[i] and !used[i]) {
                q.emplace(i), dist[i] = 0;
            }
        }

        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (auto nxt : to[now]) {
                int c = match[nxt];
                if (c >= 0 and dist[c] == -1) {
                    q.emplace(c), dist[c] = dist[now] + 1;
                }
            }
        }
    }

    bool dfs(int now)
    {
        vv[now] = true;
        for (auto nxt : to[now]) {
            int c = match[nxt];
            if (c < 0 or (!vv[c] and dist[c] == dist[now] + 1 and dfs(c))) {
                match[nxt] = now, match[now] = nxt;
                used[now] = true;
                return true;
            }
        }
        return false;
    }

    bool _color_bfs(int root)
    {
        color[root] = 0;
        std::queue<int> q;
        q.emplace(root);
        while (!q.empty()) {
            int now = q.front(), c = color[now];
            q.pop();
            for (auto nxt : to[now])
            if (color[nxt] == -1) color[nxt] = !c, q.emplace(nxt);
            else if (color[nxt] == c) return false;
        }
        return true;
    }

    int solve()
    {
        for (int i = 0; i < V; i++) if (color[i] == -1) {
            if (!_color_bfs(i)) return -1;
        }
        int ret = 0;
        while (true) {
            bfs();
            vv.assign(V, false);
            int flow = 0;
            for (int i = 0; i < V; i++) if (!color[i] and !used[i] and dfs(i)) flow++;
            if (!flow) break;
            ret += flow;
        }
        return ret;
    }

    friend std::ostream &operator<<(std::ostream &os, const BipartiteMatching &bm)
    {
        os << "{N=" << bm.V  << ':';
        for (int i = 0; i < bm.V; i++) if (bm.match[i] > i)
        {
            os << '(' << i << '-' << bm.match[i] << "),";
        }
        os << '}';
        return os;
    }
};
#line 2 "graph/test/bipartite_matching.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <algorithm>
#include <numeric>
#include <random>

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int L, R, M;
    std::cin >> L >> R >> M;

    std::vector<int> perm(L + R), perm_inv(L + R);
    std::iota(perm.begin(), perm.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(perm.begin(), perm.end(), g);
    for (int i = 0; i < L + R; i++)
    {
        perm_inv[perm[i]] = i;
    }

    BipartiteMatching bm(L + R);
    while (M--)
    {
        int a, b;
        std::cin >> a >> b;
        bm.add_edge(perm[a], perm[L + b]);
    }

    std::cout << bm.solve() << '\n';
    for (int j = 0; j < L + R; j++) if (bm.match[j] > j) {
        int a = perm_inv[j], b = perm_inv[bm.match[j]];
        if (a > b) std::cout << b << ' ' << a - L << '\n';
        else std::cout << a << ' ' << b - L << '\n';
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

