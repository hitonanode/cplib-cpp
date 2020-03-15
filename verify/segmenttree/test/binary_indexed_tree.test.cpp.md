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


# :heavy_check_mark: segmenttree/test/binary_indexed_tree.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5fd93d3fa59267c091e036914d93749e">segmenttree/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/test/binary_indexed_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/segmenttree/binary_indexed_tree.hpp.html">segmenttree/binary_indexed_tree.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "segmenttree/binary_indexed_tree.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
#include <cstdio>

int main()
{
    int N, Q;
    scanf("%d %d", &N, &Q);
    BIT<int> bit(N);
    while (Q--)
    {
        int c, x, y;
        scanf("%d %d %d", &c, &x, &y);
        if (c) printf("%d\n", bit.sum(y) - bit.sum(x - 1));
        else bit.add(x, y);
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "segmenttree/binary_indexed_tree.hpp"
#include <iostream>
#include <vector>

// CUT begin
// 1-indexed BIT (i : [1, len])
template<typename T>
struct BIT : std::vector<T>
{
    BIT(int len = 0) : std::vector<T>(len + 1) {}
    void reset() { fill(this->begin(), this->end(), 0); }
    void add(int pos, T v) {
        while (pos > 0 and pos < (int)this->size()) (*this)[pos] += v, pos += pos & -pos;
    }
    T sum(int pos) const { // (0, pos]
        T res = 0;
        while (pos > 0) res += (*this)[pos], pos -= pos & -pos;
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const BIT &bit) {
        T prv = 0;
        os << '[';
        for (int i = 1; i < (int)bit.size(); i++) {
            T now = bit.sum(i);
            os << now - prv << ",";
            prv = now;
        }
        os << ']';
        return os;
    }
};
#line 2 "segmenttree/test/binary_indexed_tree.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
#include <cstdio>

int main()
{
    int N, Q;
    scanf("%d %d", &N, &Q);
    BIT<int> bit(N);
    while (Q--)
    {
        int c, x, y;
        scanf("%d %d %d", &c, &x, &y);
        if (c) printf("%d\n", bit.sum(y) - bit.sum(x - 1));
        else bit.add(x, y);
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

