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


# :warning: convolution/set_convolution/zeta_moebius.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#fdfbcfdf78ce9afce8338cf04c6824f1">convolution/set_convolution</a>
* <a href="{{ site.github.repository_url }}/blob/master/convolution/set_convolution/zeta_moebius.cpp">View this file on GitHub</a>
    - Last commit date: 2019-09-28 15:55:55+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <bits/stdc++.h>
using namespace std;

#define FOR(i, begin, end) for(int i=(begin);i<(end);i++)
#define REP(i, n) FOR(i,0,n)

// [Input] vector<int> f : size: 2^n, 破壊的
// [Output] vector<int> f : size: 2^n

// zeta_pattern1 高速ゼータ変換(1) 入力f[S]に対して、「Sを含む」T全部に対するf[T]の和が出てくる 計算量O(n 2^n)
void zeta_pattern1(vector<int> &f, int n) {
    REP(i, n) REP(b, 1<<n) if (!(b & (1 << i))) f[b] += f[b | (1 << i)];
}

// zeta_pattern2 高速ゼータ変換(2) 入力f[S]に対して、「Sに含まれる」T全部に対するf[T]の和が出てくる 計算量O(n 2^n)
void zeta_pattern2(vector<int> &f, int n) {
    REP(i, n) REP(b, 1<<n) if (b & (1 << i)) f[b] += f[b ^ (1 << i)];
}

// moebius_pattern1 高速メビウス変換(1) zeta_pattern1の逆変換 計算量O(n 2^n)
void moebius_pattern1(vector<int> &g, int n) {
    REP(i, n) REP(b, 1<<n) if (!(b & (1 << i))) g[b] -= g[b | (1 << i)];
}

// moebius_pattern2 高速メビウス変換(2) zeta_pattern2の逆変換 計算量O(n 2^n)
void moebius_pattern2(vector<int> &g, int n) {
    REP(i, n) REP(b, 1<<n) if (b & (1 << i)) g[b] -= g[b ^ (1 << i)];
}

int main()
{
    int N = 3;
    vector<int> x(1 << N);

    x[0] = 0;
    x[1] = 50;
    x[2] = 33;
    x[3] = 67;
    x[4] = 20;
    x[5] = 60;
    x[6] = 47;
    x[7] = 74;

    for (auto v : x) cout << v << " ";
    cout << endl;
    cout << endl;

    vector<int> y = x;

    moebius_pattern1(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;
    zeta_pattern1(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;

    cout << endl;

    moebius_pattern2(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;
    zeta_pattern2(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;

}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "convolution/set_convolution/zeta_moebius.cpp"
#include <bits/stdc++.h>
using namespace std;

#define FOR(i, begin, end) for(int i=(begin);i<(end);i++)
#define REP(i, n) FOR(i,0,n)

// [Input] vector<int> f : size: 2^n, 破壊的
// [Output] vector<int> f : size: 2^n

// zeta_pattern1 高速ゼータ変換(1) 入力f[S]に対して、「Sを含む」T全部に対するf[T]の和が出てくる 計算量O(n 2^n)
void zeta_pattern1(vector<int> &f, int n) {
    REP(i, n) REP(b, 1<<n) if (!(b & (1 << i))) f[b] += f[b | (1 << i)];
}

// zeta_pattern2 高速ゼータ変換(2) 入力f[S]に対して、「Sに含まれる」T全部に対するf[T]の和が出てくる 計算量O(n 2^n)
void zeta_pattern2(vector<int> &f, int n) {
    REP(i, n) REP(b, 1<<n) if (b & (1 << i)) f[b] += f[b ^ (1 << i)];
}

// moebius_pattern1 高速メビウス変換(1) zeta_pattern1の逆変換 計算量O(n 2^n)
void moebius_pattern1(vector<int> &g, int n) {
    REP(i, n) REP(b, 1<<n) if (!(b & (1 << i))) g[b] -= g[b | (1 << i)];
}

// moebius_pattern2 高速メビウス変換(2) zeta_pattern2の逆変換 計算量O(n 2^n)
void moebius_pattern2(vector<int> &g, int n) {
    REP(i, n) REP(b, 1<<n) if (b & (1 << i)) g[b] -= g[b ^ (1 << i)];
}

int main()
{
    int N = 3;
    vector<int> x(1 << N);

    x[0] = 0;
    x[1] = 50;
    x[2] = 33;
    x[3] = 67;
    x[4] = 20;
    x[5] = 60;
    x[6] = 47;
    x[7] = 74;

    for (auto v : x) cout << v << " ";
    cout << endl;
    cout << endl;

    vector<int> y = x;

    moebius_pattern1(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;
    zeta_pattern1(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;

    cout << endl;

    moebius_pattern2(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;
    zeta_pattern2(y, N);
    for (auto v : y) cout << v << " ";
    cout << endl;

}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

