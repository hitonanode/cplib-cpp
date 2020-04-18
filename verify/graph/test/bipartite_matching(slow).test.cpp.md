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


# :heavy_check_mark: graph/test/bipartite_matching(slow).test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cb3e5c672d961db00b76e36ddf5c068a">graph/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/test/bipartite_matching(slow).test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 18:32:38+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/bipartite_matching(slow).hpp.html">graph/bipartite_matching(slow).hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include "graph/bipartite_matching(slow).hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A"

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int X, Y, E;
    std::cin >> X >> Y >> E;
    BipartiteMatching graph(X + Y);
    while (E--)
    {
        int s, t;
        std::cin >> s >> t;
        graph.add_edge(s, X + t);
    }
    std::cout << graph.solve() << '\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/test/bipartite_matching(slow).test.cpp"
#include <iostream>
#line 3 "graph/bipartite_matching(slow).hpp"
#include <vector>

// CUT begin
// Bipartite matching of undirected bipartite graph
// <https://ei1333.github.io/luzhiled/snippets/graph/bipartite-matching.html>
// Comprexity: O(VE)
struct BipartiteMatching
{
    int V;                               // # of vertices
    std::vector<std::vector<int>> edges; // Adjacency list
    std::vector<int> match;              // match[i] = (Partner of i'th node) or -1 (No parter)
    std::vector<int> used;
    int timestamp;
    BipartiteMatching(int V = 0) : V(V), edges(V), match(V, -1), used(V, 0), timestamp(0) {}

    void add_edge(int u, int v)
    {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    bool dfs(int v)
    {
        used[v] = timestamp;
        for (auto to : edges[v])
        {
            if (match[to] < 0 or (used[match[to]] != timestamp and dfs(match[to])))
            {
                match[v] = to;
                match[to] = v;
                return true;
            }
        }
        return false;
    }

    int solve() // Count up newly formed pairs
    {
        int ret = 0;
        for (int v = 0; v < V; v++) if (match[v] < 0)
        {
            ++timestamp;
            ret += dfs(v);
        }
        return ret;
    }

    friend std::ostream &operator<<(std::ostream &os, const BipartiteMatching &bm)
    {
        os << "{V=" << bm.V << ":";
        for (int i = 0; i < bm.V; i++) if (i < bm.match[i])
        {
            os << "(" << i << "-" << bm.match[i] << "),";
        }
        os << "}";
        return os;
    }
};
#line 3 "graph/test/bipartite_matching(slow).test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A"

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int X, Y, E;
    std::cin >> X >> Y >> E;
    BipartiteMatching graph(X + Y);
    while (E--)
    {
        int s, t;
        std::cin >> s >> t;
        graph.add_edge(s, X + t);
    }
    std::cout << graph.solve() << '\n';
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

