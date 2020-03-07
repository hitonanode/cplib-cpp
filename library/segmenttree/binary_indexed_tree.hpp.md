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


# :x: segmenttree/binary_indexed_tree.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4d78bd1b354012e24586b247dc164462">segmenttree</a>
* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/binary_indexed_tree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Verified with

* :x: <a href="../../verify/segmenttree/test/binary_indexed_tree.test.cpp.html">segmenttree/test/binary_indexed_tree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

