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


# :heavy_check_mark: other_data_structures/binary_trie.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d8e67fcaf05802735e10c02b3e2db75e">other_data_structures</a>
* <a href="{{ site.github.repository_url }}/blob/master/other_data_structures/binary_trie.hpp">View this file on GitHub</a>
    - Last commit date: 2020-09-05 13:06:28+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/other_data_structures/test/binary_trie.test.cpp.html">other_data_structures/test/binary_trie.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <vector>

struct BinaryTrie
{
    using Int = int;
    int maxD;
    std::vector<int> deg, sz;
    std::vector<int> ch0, ch1, par;

    int _new_node(int id_par)
    {
        deg.emplace_back(0);
        sz.emplace_back(0);
        ch0.emplace_back(-1);
        ch1.emplace_back(-1);
        par.emplace_back(id_par);
        return ch0.size() - 1;
    }

    BinaryTrie(int maxD = 0) : maxD(maxD)
    {
        _new_node(-1);
    }
    int _goto(Int x)
    {
        int now = 0;
        for (int d = maxD - 1; d >= 0; d--)
        {
            int nxt = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (nxt == -1)
            {
                nxt = _new_node(now);
                (((x >> d) & 1) ? ch1[now] : ch0[now]) = nxt;
            }
            now = nxt;
        }
        return now;
    }

    void insert(Int x)
    {
        int now = _goto(x);
        if (deg[now] == 0)
        {
            deg[now] = 1;
            while (now >= 0)
            {
                sz[now]++, now = par[now];
            }
        }
    }

    void erase(Int x)
    {
        int now = _goto(x);
        if (deg[now] > 0)
        {
            deg[now] = 0;
            while (now >= 0)
            {
                sz[now]--, now = par[now];
            }
        }
    }

    Int xor_min(Int x)
    {
        Int ret = 0;
        int now = 0;
        if (!sz[now]) return -1;
        for (int d = maxD - 1; d >= 0; d--)
        {
            int y = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (y != -1 and sz[y])
            {
                now = y;
            }
            else
            {
                ret += Int(1) << d, now = ch0[now] ^ ch1[now] ^ y;
            }
        }
        return ret;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other_data_structures/binary_trie.hpp"
#include <vector>

struct BinaryTrie
{
    using Int = int;
    int maxD;
    std::vector<int> deg, sz;
    std::vector<int> ch0, ch1, par;

    int _new_node(int id_par)
    {
        deg.emplace_back(0);
        sz.emplace_back(0);
        ch0.emplace_back(-1);
        ch1.emplace_back(-1);
        par.emplace_back(id_par);
        return ch0.size() - 1;
    }

    BinaryTrie(int maxD = 0) : maxD(maxD)
    {
        _new_node(-1);
    }
    int _goto(Int x)
    {
        int now = 0;
        for (int d = maxD - 1; d >= 0; d--)
        {
            int nxt = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (nxt == -1)
            {
                nxt = _new_node(now);
                (((x >> d) & 1) ? ch1[now] : ch0[now]) = nxt;
            }
            now = nxt;
        }
        return now;
    }

    void insert(Int x)
    {
        int now = _goto(x);
        if (deg[now] == 0)
        {
            deg[now] = 1;
            while (now >= 0)
            {
                sz[now]++, now = par[now];
            }
        }
    }

    void erase(Int x)
    {
        int now = _goto(x);
        if (deg[now] > 0)
        {
            deg[now] = 0;
            while (now >= 0)
            {
                sz[now]--, now = par[now];
            }
        }
    }

    Int xor_min(Int x)
    {
        Int ret = 0;
        int now = 0;
        if (!sz[now]) return -1;
        for (int d = maxD - 1; d >= 0; d--)
        {
            int y = ((x >> d) & 1) ? ch1[now] : ch0[now];
            if (y != -1 and sz[y])
            {
                now = y;
            }
            else
            {
                ret += Int(1) << d, now = ch0[now] ^ ch1[now] ^ y;
            }
        }
        return ret;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

