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


# :heavy_check_mark: other_data_structures/persistent_queue.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#d8e67fcaf05802735e10c02b3e2db75e">other_data_structures</a>
* <a href="{{ site.github.repository_url }}/blob/master/other_data_structures/persistent_queue.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 22:56:40+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/other_data_structures/test/persistent_queue.test.cpp.html">other_data_structures/test/persistent_queue.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// Fully persistent queue
template<typename T, int D>
struct pqueue
{
    int now;

    std::vector<T> data;               // Elements on each node of tree
    std::vector<std::vector<int>> par; // binary-lifted parents

    std::vector<int> back_id; // back_id[t] = leaf id of the tree at time t
    std::vector<int> size;    // size[t] = size of the queue at time t

    pqueue() : now(0), data(1), par(1, std::vector<int>(D)), back_id(1, 0), size(1, 0) {}

    // Complexity: O(lgD)
    // return: (curret_time, popped element)
    std::pair<int, T> pop(int t)
    {
        now++;
        assert(now < 1 << (D + 1));
        int r = back_id[t], len = size[t] - 1;
        back_id.emplace_back(r), size.emplace_back(len);
        for (int d = 0; d < D; d++) if ((len >> d) & 1) r = par[r][d];
        return std::make_pair(now, data[r]);
    }

    // Complexity: O(lgD)
    // return: curret_time
    int push(int t, const T &dat)
    {
        now++;
        assert(now < 1 << (D + 1));
        int newid = data.size();
        data.emplace_back(dat);
        par.emplace_back(std::vector<int>(D, back_id[t]));
        back_id.emplace_back(newid), size.emplace_back(size[t] + 1);
        for (int d = 1; d < D; d++) par[newid][d] = par[par[newid][d - 1]][d - 1];
        return now;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other_data_structures/persistent_queue.hpp"
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// Fully persistent queue
template<typename T, int D>
struct pqueue
{
    int now;

    std::vector<T> data;               // Elements on each node of tree
    std::vector<std::vector<int>> par; // binary-lifted parents

    std::vector<int> back_id; // back_id[t] = leaf id of the tree at time t
    std::vector<int> size;    // size[t] = size of the queue at time t

    pqueue() : now(0), data(1), par(1, std::vector<int>(D)), back_id(1, 0), size(1, 0) {}

    // Complexity: O(lgD)
    // return: (curret_time, popped element)
    std::pair<int, T> pop(int t)
    {
        now++;
        assert(now < 1 << (D + 1));
        int r = back_id[t], len = size[t] - 1;
        back_id.emplace_back(r), size.emplace_back(len);
        for (int d = 0; d < D; d++) if ((len >> d) & 1) r = par[r][d];
        return std::make_pair(now, data[r]);
    }

    // Complexity: O(lgD)
    // return: curret_time
    int push(int t, const T &dat)
    {
        now++;
        assert(now < 1 << (D + 1));
        int newid = data.size();
        data.emplace_back(dat);
        par.emplace_back(std::vector<int>(D, back_id[t]));
        back_id.emplace_back(newid), size.emplace_back(size[t] + 1);
        for (int d = 1; d < D; d++) par[newid][d] = par[par[newid][d - 1]][d - 1];
        return now;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

