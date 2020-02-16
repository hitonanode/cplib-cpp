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


# :heavy_check_mark: graph/maximum_independent_set.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/maximum_independent_set.hpp">View this file on GitHub</a>
    - Last commit date: 2019-12-14 11:23:41+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/graph/test/maximum_independent_set.test.cpp.html">graph/test/maximum_independent_set.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <numeric>
#include <stack>
#include <vector>

// Maximum Independent Set for general graph （最大独立集合）
// Works with reasonable time complexity when N~40
// Given graph must not have self-edges
// Verified: <https://judge.yosupo.jp/submission/1864>
// Reference: <https://www.slideshare.net/wata_orz/ss-12131479>

struct MaximumIndependentSet
{
    using E = std::vector<std::vector<int>>;
    // using E = std::vector<std::set<int>>;  // #include <set> needed
    // using E = std::vector<std::unordered_set<int>>;  // #include <unordered_set> needed
    int V;  // # of vertices
    int independence_number;  // Largest possible size of independent set
    std::vector<int> ret;  // Result is saved here: use (1), don't use (0)
    std::vector<int> deg;  // Degree of each vertex
    std::vector<int> tmp_state;
    E edges;
    void mis_dfs() {
        int t = std::accumulate(tmp_state.begin(), tmp_state.end(), 0);
        if (t > independence_number) independence_number = t, ret = tmp_state;

        int n = std::max_element(deg.begin(), deg.end()) - deg.begin();
        if (deg[n] == 0) return;

        int deg_tmp = deg[n];
        deg[n] = 0;

        std::stack<std::pair<int, int>> newly_occupied;
        for (auto x : edges[n]) if (deg[x]) {
            newly_occupied.emplace(x, deg[x]);
            deg[x] = 0;
        }
        tmp_state[n] = 1;
        mis_dfs();

        tmp_state[n] = 0;
        while (!newly_occupied.empty()) {
            deg[newly_occupied.top().first] = newly_occupied.top().second;
            newly_occupied.pop();
        }
        mis_dfs();

        deg[n] = deg_tmp;
    }
    MaximumIndependentSet(const E &e) : V(e.size()), independence_number(-1), deg(V), tmp_state(V), edges(e) {
        for (int i = 0; i < V; i++) deg[i] = edges[i].size();
        for (int i = 0; i < V; i++) {
            if (edges[i].size() == 0 or (edges[i].size() == 1 and deg[i])) {
                deg[i] = 0, tmp_state[i] = 1;
                for (auto x : edges[i]) deg[x] = 0;
            }
        }
        mis_dfs();
    }
};


// A little fast implementation of MaximumIndependentSet 
// by substituting long long int's bit for `ret` & `tmp_state`
// Requirement: V <= 64
struct MaximumIndependentSetFast
{
    using E = std::vector<std::vector<int>>;
    using ull = unsigned long long int;
    // using E = std::vector<std::set<int>>;  // #include <set> needed
    // using E = std::vector<std::unordered_set<int>>;  // #include <unordered_set> needed
    int V;  // # of vertices
    int independence_number;  // Largest possible size of independent set
    ull ret;  // Result is saved here: use (1), don't use (0)
    std::vector<int> deg;  // Degree of each vertex
    ull tmp_state;
    E edges;
    void mis_dfs() {
        int t = __builtin_popcountll(tmp_state);
        if (t > independence_number) independence_number = t, ret = tmp_state;

        int n = std::max_element(deg.begin(), deg.end()) - deg.begin();
        if (deg[n] == 0) return;

        int deg_tmp = deg[n];
        deg[n] = 0;

        std::stack<std::pair<int, int>> newly_occupied;
        for (auto x : edges[n]) if (deg[x]) {
            newly_occupied.emplace(x, deg[x]);
            deg[x] = 0;
        }
        tmp_state += 1LL << n;
        mis_dfs();

        tmp_state -= 1LL << n;
        while (!newly_occupied.empty()) {
            deg[newly_occupied.top().first] = newly_occupied.top().second;
            newly_occupied.pop();
        }
        mis_dfs();

        deg[n] = deg_tmp;
    }
    MaximumIndependentSetFast(const E &e) : V(e.size()), independence_number(-1), ret(0), deg(V), tmp_state(0), edges(e) {
        for (int i = 0; i < V; i++) deg[i] = edges[i].size();
        for (int i = 0; i < V; i++) {
            if (edges[i].size() == 0 or (edges[i].size() == 1 and deg[i])) {
                deg[i] = 0, tmp_state += 1LL << i;
                for (auto x : edges[i]) deg[x] = 0;
            }
        }
        mis_dfs();
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/maximum_independent_set.hpp"
#include <algorithm>
#include <numeric>
#include <stack>
#include <vector>

// Maximum Independent Set for general graph （最大独立集合）
// Works with reasonable time complexity when N~40
// Given graph must not have self-edges
// Verified: <https://judge.yosupo.jp/submission/1864>
// Reference: <https://www.slideshare.net/wata_orz/ss-12131479>

struct MaximumIndependentSet
{
    using E = std::vector<std::vector<int>>;
    // using E = std::vector<std::set<int>>;  // #include <set> needed
    // using E = std::vector<std::unordered_set<int>>;  // #include <unordered_set> needed
    int V;  // # of vertices
    int independence_number;  // Largest possible size of independent set
    std::vector<int> ret;  // Result is saved here: use (1), don't use (0)
    std::vector<int> deg;  // Degree of each vertex
    std::vector<int> tmp_state;
    E edges;
    void mis_dfs() {
        int t = std::accumulate(tmp_state.begin(), tmp_state.end(), 0);
        if (t > independence_number) independence_number = t, ret = tmp_state;

        int n = std::max_element(deg.begin(), deg.end()) - deg.begin();
        if (deg[n] == 0) return;

        int deg_tmp = deg[n];
        deg[n] = 0;

        std::stack<std::pair<int, int>> newly_occupied;
        for (auto x : edges[n]) if (deg[x]) {
            newly_occupied.emplace(x, deg[x]);
            deg[x] = 0;
        }
        tmp_state[n] = 1;
        mis_dfs();

        tmp_state[n] = 0;
        while (!newly_occupied.empty()) {
            deg[newly_occupied.top().first] = newly_occupied.top().second;
            newly_occupied.pop();
        }
        mis_dfs();

        deg[n] = deg_tmp;
    }
    MaximumIndependentSet(const E &e) : V(e.size()), independence_number(-1), deg(V), tmp_state(V), edges(e) {
        for (int i = 0; i < V; i++) deg[i] = edges[i].size();
        for (int i = 0; i < V; i++) {
            if (edges[i].size() == 0 or (edges[i].size() == 1 and deg[i])) {
                deg[i] = 0, tmp_state[i] = 1;
                for (auto x : edges[i]) deg[x] = 0;
            }
        }
        mis_dfs();
    }
};


// A little fast implementation of MaximumIndependentSet 
// by substituting long long int's bit for `ret` & `tmp_state`
// Requirement: V <= 64
struct MaximumIndependentSetFast
{
    using E = std::vector<std::vector<int>>;
    using ull = unsigned long long int;
    // using E = std::vector<std::set<int>>;  // #include <set> needed
    // using E = std::vector<std::unordered_set<int>>;  // #include <unordered_set> needed
    int V;  // # of vertices
    int independence_number;  // Largest possible size of independent set
    ull ret;  // Result is saved here: use (1), don't use (0)
    std::vector<int> deg;  // Degree of each vertex
    ull tmp_state;
    E edges;
    void mis_dfs() {
        int t = __builtin_popcountll(tmp_state);
        if (t > independence_number) independence_number = t, ret = tmp_state;

        int n = std::max_element(deg.begin(), deg.end()) - deg.begin();
        if (deg[n] == 0) return;

        int deg_tmp = deg[n];
        deg[n] = 0;

        std::stack<std::pair<int, int>> newly_occupied;
        for (auto x : edges[n]) if (deg[x]) {
            newly_occupied.emplace(x, deg[x]);
            deg[x] = 0;
        }
        tmp_state += 1LL << n;
        mis_dfs();

        tmp_state -= 1LL << n;
        while (!newly_occupied.empty()) {
            deg[newly_occupied.top().first] = newly_occupied.top().second;
            newly_occupied.pop();
        }
        mis_dfs();

        deg[n] = deg_tmp;
    }
    MaximumIndependentSetFast(const E &e) : V(e.size()), independence_number(-1), ret(0), deg(V), tmp_state(0), edges(e) {
        for (int i = 0; i < V; i++) deg[i] = edges[i].size();
        for (int i = 0; i < V; i++) {
            if (edges[i].size() == 0 or (edges[i].size() == 1 and deg[i])) {
                deg[i] = 0, tmp_state += 1LL << i;
                for (auto x : edges[i]) deg[x] = 0;
            }
        }
        mis_dfs();
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

