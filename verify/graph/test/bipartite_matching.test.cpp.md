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
    - Last commit date: 2020-04-18 18:32:38+09:00


* see: <a href="https://judge.yosupo.jp/problem/bipartitematching">https://judge.yosupo.jp/problem/bipartitematching</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/bipartite_matching.hpp.html">graph/bipartite_matching.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "graph/bipartite_matching.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int L, R, M;
    std::cin >> L >> R >> M;
    BipartiteMatching bm(L, R);
    while (M--)
    {
        int a, b;
        std::cin >> a >> b;
        bm.add_edge(a, b);
    }
    std::cout << bm.solve() << '\n';
    for (int j = 0; j < R; j++) if (bm.match[j] >= 0) {
        std::cout << bm.match[j] << ' ' << j << '\n';
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
#line 2 "graph/test/bipartite_matching.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int L, R, M;
    std::cin >> L >> R >> M;
    BipartiteMatching bm(L, R);
    while (M--)
    {
        int a, b;
        std::cin >> a >> b;
        bm.add_edge(a, b);
    }
    std::cout << bm.solve() << '\n';
    for (int j = 0; j < R; j++) if (bm.match[j] >= 0) {
        std::cout << bm.match[j] << ' ' << j << '\n';
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

