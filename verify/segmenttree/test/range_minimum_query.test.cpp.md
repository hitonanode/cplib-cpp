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


# :heavy_check_mark: segmenttree/test/range_minimum_query.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/test/range_minimum_query.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-08 15:25:44+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/segmenttree/range_minimum_query.hpp.html">segmenttree/range_minimum_query.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include "segmenttree/range_minimum_query.hpp"
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"


int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N, (1LL << 31) - 1);
    RangeMinimumQuery rmq(A, A[0]);
    for (int q = 0; q < Q; q++)
    {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0)
        {
            rmq.update(x, y);
        }
        else
        {
            cout << rmq.get(x, y + 1) << endl;
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "segmenttree/test/range_minimum_query.test.cpp"
#include <iostream>
#line 2 "segmenttree/range_minimum_query.hpp"
#include <iostream>
#include <vector>
using namespace std;

using T = int;
struct RangeMinimumQuery
{
    int N;
    T defaultT = 1e9;
    int head;
    vector<T> x;
    T _get(int begin, int end, int pos, int l, int r) const
    {
        if (r <= begin or l >= end) return defaultT;
        if (l >= begin and r <= end) return x[pos];
        return min(_get(begin, end, 2 * pos + 1, l, (l + r) / 2), _get(begin, end, 2 * pos + 2, (l + r) / 2, r));
    }
    RangeMinimumQuery(int N, T defaultT) : N(N), defaultT(defaultT)
    {
        int N_tmp = 1; while (N_tmp < N) N_tmp <<= 1;
        x.assign(N_tmp*2, defaultT), head = N_tmp - 1;
    }
    void build(const vector<T> &vals)
    {
        copy(vals.begin(), vals.end(), x.begin() + head);
        for (int i = head - 1; i >= 0; i--)
        {
            x[i] = min(x[i * 2 + 1], x[i * 2 + 2]);
        }
    }
    RangeMinimumQuery(const vector<T> &vals, T defaultT) : N(vals.size()), defaultT(defaultT)
    {
        int N_tmp = 1; while (N_tmp < N) N_tmp <<= 1;
        x.assign(N_tmp*2, defaultT), head = N_tmp - 1;
        build(vals);
    }
    RangeMinimumQuery() : RangeMinimumQuery(0, T()) {}
    void update(int pos, T val)
    {
        pos += head, x[pos] = val;
        while (pos) pos = (pos - 1) / 2, x[pos] = min(x[pos * 2 + 1], x[pos * 2 + 2]);
    }
    T get(int begin, int end) const { return _get(begin, end, 0, 0, (int)x.size() / 2); }
    friend ostream &operator<<(ostream &os, const RangeMinimumQuery &s)
    {
        os << "[";
        for (int i = 0; i < s.N; i++) os << s.get(i, i + 1) << ",";
        os << "]";
        return os;
    }
};
#line 3 "segmenttree/test/range_minimum_query.test.cpp"
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"


int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N, (1LL << 31) - 1);
    RangeMinimumQuery rmq(A, A[0]);
    for (int q = 0; q < Q; q++)
    {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0)
        {
            rmq.update(x, y);
        }
        else
        {
            cout << rmq.get(x, y + 1) << endl;
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

