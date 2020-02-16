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


# :heavy_check_mark: graph/bellman_ford.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/bellman_ford.hpp">View this file on GitHub</a>
    - Last commit date: 2019-08-12 12:36:28+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/graph/test/bellman_ford.test.cpp.html">graph/test/bellman_ford.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

