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


# :warning: number/enumerate_partitions.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b1bc248a7ff2b2e95569f56de68615df">number</a>
* <a href="{{ site.github.repository_url }}/blob/master/number/enumerate_partitions.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 12:37:26+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <algorithm>
#include <numeric>
#include <vector>

// Enumerate Partitions of number <= N （自然数の分割の列挙）
// - can be used for N less than ~50
// - Example:
//   - 1 => [[1,],]
//   - 2 => [[1,],[1,1,],[2,],]
//   - 3 => [[1,],[1,1,],[1,1,1,],[2,],[2,1,],[3,],]
struct
{
    std::vector<std::vector<int>> ret;
    std::vector<int> now;
    int num;
    void _partition_dfs() {
        int rem = num - std::accumulate(now.begin(), now.end(), 0);
        if (!now.empty()) rem = std::min(rem, now.back());

        now.push_back(0);
        for (int j = 1; j <= rem; j++) {
            now.back() = j;
            ret.push_back(now);
            _partition_dfs();
        }
        now.pop_back();
    }

    std::vector<std::vector<int>> operator()(int N) {
        ret.clear();
        now.clear();
        num = N;
        _partition_dfs();
        return ret;
    }
} EnumeratePartitions;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "number/enumerate_partitions.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

// Enumerate Partitions of number <= N （自然数の分割の列挙）
// - can be used for N less than ~50
// - Example:
//   - 1 => [[1,],]
//   - 2 => [[1,],[1,1,],[2,],]
//   - 3 => [[1,],[1,1,],[1,1,1,],[2,],[2,1,],[3,],]
struct
{
    std::vector<std::vector<int>> ret;
    std::vector<int> now;
    int num;
    void _partition_dfs() {
        int rem = num - std::accumulate(now.begin(), now.end(), 0);
        if (!now.empty()) rem = std::min(rem, now.back());

        now.push_back(0);
        for (int j = 1; j <= rem; j++) {
            now.back() = j;
            ret.push_back(now);
            _partition_dfs();
        }
        now.pop_back();
    }

    std::vector<std::vector<int>> operator()(int N) {
        ret.clear();
        now.clear();
        num = N;
        _partition_dfs();
        return ret;
    }
} EnumeratePartitions;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

