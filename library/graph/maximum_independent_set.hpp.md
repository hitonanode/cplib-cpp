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
    - Last commit date: 2020-06-06 14:20:46+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/graph/test/maximum_independent_set.test.cpp.html">graph/test/maximum_independent_set.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <bitset>
#include <cassert>
#include <stack>
#include <vector>

// CUT begin
// Maximum Independent Set for general graph （最大独立集合）
// Works with reasonable time complexity when N~40
// Given graph must not have self-edges
// Verified: <https://judge.yosupo.jp/submission/1864>
// Reference: <https://www.slideshare.net/wata_orz/ss-12131479>
template <typename E, int BS = 64>
struct MaximumIndependentSet
{
    std::vector<std::bitset<BS>> conn;
    int V;                    // # of vertices
    int nret;  // Largest possible size of independent set
    std::bitset<BS> ret;  // Result is saved here: use (1), don't use (0)
    std::bitset<BS> _avail;
    std::bitset<BS> _tmp_state;

    void mis_dfs() {
        bool retry = true;
        std::stack<int> st;
        while (retry)
        {
            retry = false;
            for (int i = _avail._Find_first(); i < V; i = _avail._Find_next(i))
            {
                int nb = (_avail & conn[i]).count();
                if (nb <= 1)
                {
                    st.emplace(i), _avail.reset(i), _tmp_state.set(i);
                    retry = true;
                    if (nb == 1)
                    {
                        int j = (_avail & conn[i])._Find_first();
                        st.emplace(j), _avail.reset(j);
                    }
                }
            }
        }

        int t = _tmp_state.count();
        if (t > nret) nret = t, ret = _tmp_state;

        int d = -1, n = -1;
        for (int i = _avail._Find_first(); i < V; i = _avail._Find_next(i))
        {
            int c = (_avail & conn[i]).count();
            if (c > d) d = c, n = i;
        }

        if (d > 0)
        {
            std::bitset<BS> nxt = _avail & conn[n];
            _avail.reset(n);
            mis_dfs();
            _tmp_state.set(n);
            _avail &= ~nxt;
            mis_dfs();
            _avail |= nxt;
            _avail.set(n);
            _tmp_state.reset(n);
        }

        while (st.size())
        {
            int i = st.top();
            _avail.set(i);
            _tmp_state.reset(i);
            st.pop();
        }
    }
    MaximumIndependentSet(const E &e) : conn(e.size()), V(e.size()), nret(-1) {
        assert(V <= BS);
        for (int i = 0; i < V; i++) for (auto &j : e[i]) if (i != j) conn[i].set(j), conn[j].set(i);
        for (int i = 0; i < V; i++) _avail.set(i);
        _tmp_state.reset();
        mis_dfs();
    }
};


// A little fast implementation of MaximumIndependentSet 
// by substituting long long int's bit for `ret` & `_tmp_state`
// Requirement: V <= 64
template <typename E>
struct MaximumIndependentSet_Intbased
{
    std::vector<long long> conn;
    int V;                    // # of vertices
    int nret;  // Largest possible size of independent set
    long long ret;  // Result is saved here: use (1), don't use (0)
    long long _avail;
    long long _tmp_state;

    void mis_dfs() {
        bool retry = true;
        std::stack<int> st;
        while (retry)
        {
            retry = false;
            for (int i = 0; i < V; i++) if (_avail & (1LL << i))
            {
                int nb = __builtin_popcountll(_avail & conn[i]);
                if (nb <= 1)
                {
                    st.emplace(i), _avail -= 1LL << i, _tmp_state |= 1LL << i;
                    retry = true;
                    if (nb == 1)
                    {
                        int j = __builtin_ctzll(_avail & conn[i]);
                        st.emplace(j), _avail &= ~(1LL << j);
                    }
                }
            }
        }

        int t = __builtin_popcountll(_tmp_state);
        if (t > nret) nret = t, ret = _tmp_state;

        int d = -1, n = -1;
        for (int i = 0; i < V; i++) if (_avail & (1LL << i))
        {
            int c = __builtin_popcountll(_avail & conn[i]);
            if (c > d) d = c, n = i;
        }

        if (d > 0)
        {
            long long nxt = _avail & conn[n];
            _avail -= 1LL << n;
            mis_dfs();
            _tmp_state |= 1LL << n;
            _avail &= ~nxt;
            mis_dfs();
            _avail |= nxt;
            _avail |= 1LL << n;
            _tmp_state &= ~(1LL << n);
        }

        while (st.size())
        {
            int i = st.top();
            _avail |= 1LL << i;
            _tmp_state &= ~(1LL << i);
            st.pop();
        }
    }
    MaximumIndependentSet_Intbased(const E &e) : conn(e.size()), V(e.size()), nret(-1), _avail((1LL << V) - 1), _tmp_state(0) {
        assert(V <= 63);
        for (int i = 0; i < V; i++) for (auto &j : e[i]) if (i != j) conn[i] |= 1LL << j, conn[j] |= 1LL << i;
        mis_dfs();
    }
};
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/maximum_independent_set.hpp"
#include <bitset>
#include <cassert>
#include <stack>
#include <vector>

// CUT begin
// Maximum Independent Set for general graph （最大独立集合）
// Works with reasonable time complexity when N~40
// Given graph must not have self-edges
// Verified: <https://judge.yosupo.jp/submission/1864>
// Reference: <https://www.slideshare.net/wata_orz/ss-12131479>
template <typename E, int BS = 64>
struct MaximumIndependentSet
{
    std::vector<std::bitset<BS>> conn;
    int V;                    // # of vertices
    int nret;  // Largest possible size of independent set
    std::bitset<BS> ret;  // Result is saved here: use (1), don't use (0)
    std::bitset<BS> _avail;
    std::bitset<BS> _tmp_state;

    void mis_dfs() {
        bool retry = true;
        std::stack<int> st;
        while (retry)
        {
            retry = false;
            for (int i = _avail._Find_first(); i < V; i = _avail._Find_next(i))
            {
                int nb = (_avail & conn[i]).count();
                if (nb <= 1)
                {
                    st.emplace(i), _avail.reset(i), _tmp_state.set(i);
                    retry = true;
                    if (nb == 1)
                    {
                        int j = (_avail & conn[i])._Find_first();
                        st.emplace(j), _avail.reset(j);
                    }
                }
            }
        }

        int t = _tmp_state.count();
        if (t > nret) nret = t, ret = _tmp_state;

        int d = -1, n = -1;
        for (int i = _avail._Find_first(); i < V; i = _avail._Find_next(i))
        {
            int c = (_avail & conn[i]).count();
            if (c > d) d = c, n = i;
        }

        if (d > 0)
        {
            std::bitset<BS> nxt = _avail & conn[n];
            _avail.reset(n);
            mis_dfs();
            _tmp_state.set(n);
            _avail &= ~nxt;
            mis_dfs();
            _avail |= nxt;
            _avail.set(n);
            _tmp_state.reset(n);
        }

        while (st.size())
        {
            int i = st.top();
            _avail.set(i);
            _tmp_state.reset(i);
            st.pop();
        }
    }
    MaximumIndependentSet(const E &e) : conn(e.size()), V(e.size()), nret(-1) {
        assert(V <= BS);
        for (int i = 0; i < V; i++) for (auto &j : e[i]) if (i != j) conn[i].set(j), conn[j].set(i);
        for (int i = 0; i < V; i++) _avail.set(i);
        _tmp_state.reset();
        mis_dfs();
    }
};


// A little fast implementation of MaximumIndependentSet 
// by substituting long long int's bit for `ret` & `_tmp_state`
// Requirement: V <= 64
template <typename E>
struct MaximumIndependentSet_Intbased
{
    std::vector<long long> conn;
    int V;                    // # of vertices
    int nret;  // Largest possible size of independent set
    long long ret;  // Result is saved here: use (1), don't use (0)
    long long _avail;
    long long _tmp_state;

    void mis_dfs() {
        bool retry = true;
        std::stack<int> st;
        while (retry)
        {
            retry = false;
            for (int i = 0; i < V; i++) if (_avail & (1LL << i))
            {
                int nb = __builtin_popcountll(_avail & conn[i]);
                if (nb <= 1)
                {
                    st.emplace(i), _avail -= 1LL << i, _tmp_state |= 1LL << i;
                    retry = true;
                    if (nb == 1)
                    {
                        int j = __builtin_ctzll(_avail & conn[i]);
                        st.emplace(j), _avail &= ~(1LL << j);
                    }
                }
            }
        }

        int t = __builtin_popcountll(_tmp_state);
        if (t > nret) nret = t, ret = _tmp_state;

        int d = -1, n = -1;
        for (int i = 0; i < V; i++) if (_avail & (1LL << i))
        {
            int c = __builtin_popcountll(_avail & conn[i]);
            if (c > d) d = c, n = i;
        }

        if (d > 0)
        {
            long long nxt = _avail & conn[n];
            _avail -= 1LL << n;
            mis_dfs();
            _tmp_state |= 1LL << n;
            _avail &= ~nxt;
            mis_dfs();
            _avail |= nxt;
            _avail |= 1LL << n;
            _tmp_state &= ~(1LL << n);
        }

        while (st.size())
        {
            int i = st.top();
            _avail |= 1LL << i;
            _tmp_state &= ~(1LL << i);
            st.pop();
        }
    }
    MaximumIndependentSet_Intbased(const E &e) : conn(e.size()), V(e.size()), nret(-1), _avail((1LL << V) - 1), _tmp_state(0) {
        assert(V <= 63);
        for (int i = 0; i < V; i++) for (auto &j : e[i]) if (i != j) conn[i] |= 1LL << j, conn[j] |= 1LL << i;
        mis_dfs();
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

