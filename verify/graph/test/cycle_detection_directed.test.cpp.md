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


# :x: graph/test/cycle_detection_directed.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cb3e5c672d961db00b76e36ddf5c068a">graph/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/test/cycle_detection_directed.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-05 20:52:47+09:00


* see: <a href="https://judge.yosupo.jp/problem/cycle_detection">https://judge.yosupo.jp/problem/cycle_detection</a>


## Depends on

* :question: <a href="../../../library/graph/strongly_connected_components.hpp.html">graph/strongly_connected_components.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"
#include "graph/strongly_connected_components.hpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    DirectedGraphSCC graph(V);
    vector<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < E; i++)
    {
        int s, t;
        cin >> s >> t;
        graph.add_edge(s, t);
        edges.emplace_back(make_pair(make_pair(s, t), i));
    }
    sort(edges.begin(), edges.end());

    auto cycle = graph.DetectCycle();
    if (cycle.empty())
    {
        cout << "-1\n";
    }
    else
    {
        cout << cycle.size() << '\n';
        for (int i = 0; i < int(cycle.size()); i++)
        {
            pair<int, int> p{cycle[i], cycle[(i + 1) % cycle.size()]};
            int eid = lower_bound(edges.begin(), edges.end(), make_pair(p, 0))->second;
            cout << eid << '\n';
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/test/cycle_detection_directed.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"
#line 2 "graph/strongly_connected_components.hpp"
#include <cassert>
#include <algorithm>
#include <vector>

// CUT begin
// Directed graph library to find strongly connected components （強連結成分分解）
// 0-indexed directed graph
// Complexity: O(V + E)
struct DirectedGraphSCC {
    int V; // # of Vertices
    std::vector<std::vector<int>> to, from;
    std::vector<int> used;  // Only true/false
    std::vector<int> vs;
    std::vector<int> cmp;
    int scc_num = -1;

    DirectedGraphSCC(int V = 0) : V(V), to(V), from(V), cmp(V) {}

    void _dfs(int v) {
        used[v] = true;
        for (auto t : to[v]) if (!used[t]) _dfs(t);
        vs.push_back(v);
    }
    void _rdfs(int v, int k) {
        used[v] = true;
        cmp[v] = k;
        for (auto t : from[v]) if (!used[t]) _rdfs(t, k);
    }

    void add_edge(int from_, int to_) {
        assert(from_ >= 0 and from_ < V and to_ >= 0 and to_ < V);
        to[from_].push_back(to_);
        from[to_].push_back(from_);
    }

    // Detect strongly connected components and return # of them.
    // Also, assign each vertex `v` the scc id `cmp[v]` (0-indexed)
    int FindStronglyConnectedComponents() {
        used.assign(V, false);
        vs.clear();
        for (int v = 0; v < V; v++) if (!used[v]) _dfs(v);
        used.assign(V, false);
        scc_num = 0;
        for (int i = (int)vs.size() - 1; i >= 0; i--) if (!used[vs[i]]) _rdfs(vs[i], scc_num++);
        return scc_num;
    }

    // Find and output the vertices that form a closed cycle.
    // output: {v_1, ..., v_C}, where C is the length of cycle,
    //         {} if there's NO cycle (graph is DAG)
    std::vector<int> DetectCycle()
    {
        int ns = FindStronglyConnectedComponents();
        if (ns == V) return {};
        std::vector<int> cnt(ns);
        for (auto x : cmp) cnt[x]++;
        const int c = std::find_if(cnt.begin(), cnt.end(), [](int x) { return x > 1; }) - cnt.begin();
        const int init = std::find(cmp.begin(), cmp.end(), c) - cmp.begin();
        used.assign(V, false);
        std::vector<int> ret;
        auto dfs = [&](auto &&dfs, int now, bool b0) -> bool {
            if (now == init and b0) return true;
            for (auto nxt : to[now]) if (cmp[nxt] == c and !used[nxt])
            {
                ret.emplace_back(nxt), used[nxt] = 1;
                if (dfs(dfs, nxt, true)) return true;
                ret.pop_back();
            }
            return false;
        };
        dfs(dfs, init, false);
        return ret;
    }

    // After calling `FindStronglyConnectedComponents()`, generate a new graph by uniting all vertices
    // belonging to the same component(The resultant graph is DAG).
    DirectedGraphSCC GenerateTopologicalGraph() {
        DirectedGraphSCC newgraph(scc_num);
        for (int s = 0; s < V; s++) for (auto t : to[s]) {
            if (cmp[s] != cmp[t]) newgraph.add_edge(cmp[s], cmp[t]);
        }
        return newgraph;
    }
};

// 2-SAT solver: Find a solution for  `(Ai v Aj) ^ (Ak v Al) ^ ... = true`
// - `nb_sat_vars`: Number of variables
// - Considering a graph with `2 * nb_sat_vars` vertices
// - Vertices [0, nb_sat_vars) means `Ai`
// - vertices [nb_sat_vars, 2 * nb_sat_vars) means `not Ai`
struct SATSolver : DirectedGraphSCC {
    int nb_sat_vars;
    std::vector<int> solution;
    SATSolver(int nb_variables = 0) : DirectedGraphSCC(nb_variables * 2), nb_sat_vars(nb_variables), solution(nb_sat_vars) {}
    void add_x_or_y_constraint(bool is_x_true, int x, bool is_y_true, int y) {
        assert(x >= 0 and x < nb_sat_vars);
        assert(y >= 0 and y < nb_sat_vars);
        if (!is_x_true) x += nb_sat_vars;
        if (!is_y_true) y += nb_sat_vars;
        add_edge((x + nb_sat_vars) % (nb_sat_vars * 2), y);
        add_edge((y + nb_sat_vars) % (nb_sat_vars * 2), x);
    }
    // Solve the 2-SAT problem. If no solution exists, return `false`.
    // Otherwise, dump one solution to `solution` and return `true`.
    bool run() {
        FindStronglyConnectedComponents();
        for (int i = 0; i < nb_sat_vars; i++) {
            if (cmp[i] == cmp[i + nb_sat_vars]) return false;
            solution[i] = cmp[i] > cmp[i + nb_sat_vars];
        }
        return true;
    }
};
#line 3 "graph/test/cycle_detection_directed.test.cpp"

#line 5 "graph/test/cycle_detection_directed.test.cpp"
#include <iostream>
#include <utility>
#line 8 "graph/test/cycle_detection_directed.test.cpp"
using namespace std;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    DirectedGraphSCC graph(V);
    vector<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < E; i++)
    {
        int s, t;
        cin >> s >> t;
        graph.add_edge(s, t);
        edges.emplace_back(make_pair(make_pair(s, t), i));
    }
    sort(edges.begin(), edges.end());

    auto cycle = graph.DetectCycle();
    if (cycle.empty())
    {
        cout << "-1\n";
    }
    else
    {
        cout << cycle.size() << '\n';
        for (int i = 0; i < int(cycle.size()); i++)
        {
            pair<int, int> p{cycle[i], cycle[(i + 1) % cycle.size()]};
            int eid = lower_bound(edges.begin(), edges.end(), make_pair(p, 0))->second;
            cout << eid << '\n';
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

