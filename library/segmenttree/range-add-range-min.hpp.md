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


# :warning: segmenttree/range-add-range-min.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4d78bd1b354012e24586b247dc164462">segmenttree</a>
* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/range-add-range-min.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-06 02:17:41+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <vector>

// CUT begin
// StarrySkyTree: segment tree for Range Minimum Query & Range Add Query
// Complexity: O(N) (construction), O(lg N) (add / get)
template <typename Tp>
struct RangeAddRangeMin
{
    int N, head;
    Tp defaultMin;
    std::vector<Tp> range_min, range_add;
    static inline Tp f(Tp x, Tp y) noexcept
    {
        return std::min(x, y);
    }

    inline void _merge(int pos)
    {
        range_min[pos] = f(range_min[pos * 2] + range_add[pos * 2], range_min[pos * 2 + 1] + range_add[pos * 2 + 1]);
    }
    void initialize(const std::vector<Tp> &data_init, Tp default_min)
    {
        N = data_init.size(), head = 1;
        while (head < N) head <<= 1;
        defaultMin = default_min;
        range_min.assign(head * 2, defaultMin);
        range_add.assign(head * 2, 0);
        std::copy(data_init.begin(), data_init.end(), range_min.begin() + head);
        for (int pos = head; --pos;) _merge(pos);
    }
    RangeAddRangeMin() = default;
    RangeAddRangeMin(const std::vector<Tp> &data_init, Tp default_min)
    {
        initialize(data_init, default_min);
    }
    void _add(int begin, int end, int pos, int l, int r, Tp vadd) noexcept
    {
        if (r <= begin or end <= l) return;
        if (begin <= l and r <= end)
        {
            range_add[pos] += vadd;
            return;
        }
        _add(begin, end, pos * 2, l, (l + r) / 2, vadd);
        _add(begin, end, pos * 2 + 1, (l + r) / 2, r, vadd);
        _merge(pos);
    }
    // Add `vadd` to (x_begin, ..., x_{end - 1})
    void add(int begin, int end, Tp vadd) noexcept
    {
        return _add(begin, end, 1, 0, head, vadd);
    }
    Tp _get(int begin, int end, int pos, int l, int r) const noexcept
    {
        if (r <= begin or end <= l) return defaultMin;
        if (begin <= l and r <= end) return range_min[pos] + range_add[pos];
        return f(_get(begin, end, pos * 2, l, (l + r) / 2), _get(begin, end, pos * 2 + 1, (l + r) / 2, r)) + range_add[pos];
    }
    // Return f(x_begin, ..., x_{end - 1})
    Tp get(int begin, int end) const noexcept
    {
        return _get(begin, end, 1, 0, head);
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "segmenttree/range-add-range-min.hpp"
#include <algorithm>
#include <vector>

// CUT begin
// StarrySkyTree: segment tree for Range Minimum Query & Range Add Query
// Complexity: O(N) (construction), O(lg N) (add / get)
template <typename Tp>
struct RangeAddRangeMin
{
    int N, head;
    Tp defaultMin;
    std::vector<Tp> range_min, range_add;
    static inline Tp f(Tp x, Tp y) noexcept
    {
        return std::min(x, y);
    }

    inline void _merge(int pos)
    {
        range_min[pos] = f(range_min[pos * 2] + range_add[pos * 2], range_min[pos * 2 + 1] + range_add[pos * 2 + 1]);
    }
    void initialize(const std::vector<Tp> &data_init, Tp default_min)
    {
        N = data_init.size(), head = 1;
        while (head < N) head <<= 1;
        defaultMin = default_min;
        range_min.assign(head * 2, defaultMin);
        range_add.assign(head * 2, 0);
        std::copy(data_init.begin(), data_init.end(), range_min.begin() + head);
        for (int pos = head; --pos;) _merge(pos);
    }
    RangeAddRangeMin() = default;
    RangeAddRangeMin(const std::vector<Tp> &data_init, Tp default_min)
    {
        initialize(data_init, default_min);
    }
    void _add(int begin, int end, int pos, int l, int r, Tp vadd) noexcept
    {
        if (r <= begin or end <= l) return;
        if (begin <= l and r <= end)
        {
            range_add[pos] += vadd;
            return;
        }
        _add(begin, end, pos * 2, l, (l + r) / 2, vadd);
        _add(begin, end, pos * 2 + 1, (l + r) / 2, r, vadd);
        _merge(pos);
    }
    // Add `vadd` to (x_begin, ..., x_{end - 1})
    void add(int begin, int end, Tp vadd) noexcept
    {
        return _add(begin, end, 1, 0, head, vadd);
    }
    Tp _get(int begin, int end, int pos, int l, int r) const noexcept
    {
        if (r <= begin or end <= l) return defaultMin;
        if (begin <= l and r <= end) return range_min[pos] + range_add[pos];
        return f(_get(begin, end, pos * 2, l, (l + r) / 2), _get(begin, end, pos * 2 + 1, (l + r) / 2, r)) + range_add[pos];
    }
    // Return f(x_begin, ..., x_{end - 1})
    Tp get(int begin, int end) const noexcept
    {
        return _get(begin, end, 1, 0, head);
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

