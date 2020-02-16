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


# :heavy_check_mark: linear_algebra_matrix/linalg_bitset.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#20f2c5d841ec31673050aaedd8b17f50">linear_algebra_matrix</a>
* <a href="{{ site.github.repository_url }}/blob/master/linear_algebra_matrix/linalg_bitset.hpp">View this file on GitHub</a>
    - Last commit date: 2019-09-16 11:11:53+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/linear_algebra_matrix/test/linalg_bitset.test.cpp.html">linear_algebra_matrix/test/linalg_bitset.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <bitset>
#include <utility>
#include <vector>
using namespace std;


constexpr int Wmax = 320;
vector<bitset<Wmax>> gauss_jordan(int W, vector<bitset<Wmax>> mtr)
{
    int H = mtr.size(), c = 0;
    for (int h = 0; h < H; h++, c++)
    {
        if (c == W) break;
        int piv = -1;
        for (int j = h; j < H; j++) if (mtr[j][c]) {
                piv = j; break;
        }
        if (piv == -1) { h--; continue; }
        swap(mtr[piv], mtr[h]);
        for (int hh = h + 1; hh < H; hh++) {
            if (mtr[hh][c]) mtr[hh] ^= mtr[h];
        }
    }
    return mtr;
}

int rank_gauss_jordan(int W, const vector<bitset<Wmax>> &mtr) // Rank of Gauss-Jordan eliminated matrix
{
    for (int h = (int)mtr.size() - 1; h >= 0; h--) {
        if (mtr[h]._Find_first() < W) return h + 1;
    }
    return 0;
}

vector<bitset<Wmax>> matmul(const vector<bitset<Wmax>> &A, const vector<bitset<Wmax>> &B, int W_B)
{
    int H = A.size(), K = B.size();
    vector<bitset<Wmax>> C(H);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W_B; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] = C[i][j] ^ (A[i][k] & B[k][j]);
            }
        }
    }
    return C;
}

vector<bitset<Wmax>> matpower(vector<bitset<Wmax>> X, long long int n) // Calc X**n
{
    int D = X.size();
    vector<bitset<Wmax>> ret(D);
    for (int i = 0; i < D; i++) ret[i][i] = 1;
    while (n)
    {
        if (n & 1) ret = matmul(ret, X, D);
        X = matmul(X, X, D); n >>= 1;
    }
    return ret;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "linear_algebra_matrix/linalg_bitset.hpp"
#include <bitset>
#include <utility>
#include <vector>
using namespace std;


constexpr int Wmax = 320;
vector<bitset<Wmax>> gauss_jordan(int W, vector<bitset<Wmax>> mtr)
{
    int H = mtr.size(), c = 0;
    for (int h = 0; h < H; h++, c++)
    {
        if (c == W) break;
        int piv = -1;
        for (int j = h; j < H; j++) if (mtr[j][c]) {
                piv = j; break;
        }
        if (piv == -1) { h--; continue; }
        swap(mtr[piv], mtr[h]);
        for (int hh = h + 1; hh < H; hh++) {
            if (mtr[hh][c]) mtr[hh] ^= mtr[h];
        }
    }
    return mtr;
}

int rank_gauss_jordan(int W, const vector<bitset<Wmax>> &mtr) // Rank of Gauss-Jordan eliminated matrix
{
    for (int h = (int)mtr.size() - 1; h >= 0; h--) {
        if (mtr[h]._Find_first() < W) return h + 1;
    }
    return 0;
}

vector<bitset<Wmax>> matmul(const vector<bitset<Wmax>> &A, const vector<bitset<Wmax>> &B, int W_B)
{
    int H = A.size(), K = B.size();
    vector<bitset<Wmax>> C(H);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W_B; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] = C[i][j] ^ (A[i][k] & B[k][j]);
            }
        }
    }
    return C;
}

vector<bitset<Wmax>> matpower(vector<bitset<Wmax>> X, long long int n) // Calc X**n
{
    int D = X.size();
    vector<bitset<Wmax>> ret(D);
    for (int i = 0; i < D; i++) ret[i][i] = 1;
    while (n)
    {
        if (n & 1) ret = matmul(ret, X, D);
        X = matmul(X, X, D); n >>= 1;
    }
    return ret;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

