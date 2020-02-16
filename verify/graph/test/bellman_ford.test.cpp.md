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


# :heavy_check_mark: graph/test/bellman_ford.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/graph/test/bellman_ford.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-08 14:58:12+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/bellman_ford.hpp.html">graph/bellman_ford.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <vector>
#include "graph/bellman_ford.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B"

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
    vector<lint> ret = bellman_ford(r, e, V);
    vector<lint> ret2 = bellman_ford(r, e, V + 1);

    for (int i = 0; i < V; i++) {
        if (ret[i] != ret2[i]) {
            puts("NEGATIVE CYCLE");
            return 0;
        }
    }

    for (int i = 0; i < V; i++) {
        if (ret[i] == INF) puts("INF");
        else printf("%lld\n", ret[i]);
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/test/bellman_ford.test.cpp"
#include <iostream>
#include <vector>
#line 2 "graph/bellman_ford.hpp"
#include <utility>
#include <vector>
using namespace std;
using lint = long long;

using wedges = vector<vector<pair<lint, lint>>>; // (to, weight)
constexpr lint INF = 1e17;
vector<lint> bellman_ford(int s, const wedges &w, int T)
{
    int N = w.size();
    vector<lint> d(N, INF);
    d[s] = 0;
    for(int l = 0; l < T; l++) {
        bool upd = false;
        for (int i = 0; i < N; i++)
        {
            if (d[i] >= INF) continue;
            for (auto pa : w[i]) {
                if (d[pa.first] > d[i] + pa.second) {
                    d[pa.first] = d[i] + pa.second;
                    upd = true;
                }
            }
        }
        if (!upd) break;
    }
    return d;
}
#line 4 "graph/test/bellman_ford.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B"

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
    vector<lint> ret = bellman_ford(r, e, V);
    vector<lint> ret2 = bellman_ford(r, e, V + 1);

    for (int i = 0; i < V; i++) {
        if (ret[i] != ret2[i]) {
            puts("NEGATIVE CYCLE");
            return 0;
        }
    }

    for (int i = 0; i < V; i++) {
        if (ret[i] == INF) puts("INF");
        else printf("%lld\n", ret[i]);
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

