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


# :heavy_check_mark: random/test/rolling_hash.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/random/test/rolling_hash.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-08 14:58:12+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/random/rand_nondeterministic.hpp.html">random/rand_nondeterministic.hpp</a>
* :heavy_check_mark: <a href="../../../library/random/rolling_hash_1d_general.hpp.html">random/rolling_hash_1d_general.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <string>
#include "random/rolling_hash_1d_general.hpp"
#include "random/rand_nondeterministic.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
using namespace std;

int main()
{
    DoubleHash b(rnd(1, 1000000), rnd(1, 1000000));

    string T, P;
    cin >> T >> P;
    rolling_hash<DoubleHash> rh_T(T, b),rh_P(P, b);

    for (int l = 0; l < (int)(T.length() - P.length() + 1); l++)
    {
        if (rh_T.get_hash(l, l + P.length()) == rh_P.get_hash(0, P.length()))
        {
            cout << l << endl;
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "random/test/rolling_hash.test.cpp"
#include <iostream>
#include <string>
#line 2 "random/rolling_hash_1d_general.hpp"
#include <string>
#include <vector>
using namespace std;

// Rolling Hash (Rabin-Karp), 1dim
template<typename V>
struct rolling_hash
{
    V B;
    vector<V> hash; // hash[i] = s[0] * B^(i - 1) + ... + s[i - 1]
    vector<V> power; // power[i] = B^i
    rolling_hash() {}
    rolling_hash(const string &s, V b) : B(b)
    {
        int N = s.length();
        hash.resize(N + 1), power.resize(N + 1, 1);
        for (int i = 0; i < N; i++)
        {
            power[i + 1] = power[i] * B;
            hash[i + 1] = hash[i] * B + s[i];
        }
    }
    V get_hash(int l, int r) // s[l] * B^(r - l - 1) + ... + s[r - 1]
    {
        return hash[r] - hash[l] * power[r - l];
    }
};

using lint = long long;
using plint = pair<lint, lint>;
struct DoubleHash : public plint
{
    static plint MODs;
    DoubleHash(plint x) : plint(x) {}
    DoubleHash(lint x, lint y) : plint(x, y) {}
    DoubleHash(lint x) : DoubleHash(x, x) {}
    DoubleHash() : DoubleHash(0) {}
    static inline DoubleHash mod_subtract(plint x)
    {
        if (x.first >= MODs.first) x.first -= MODs.first;
        if (x.second >= MODs.second) x.second -= MODs.second;
        return x;
    }
    DoubleHash operator+(const DoubleHash &x) const
    {
        return mod_subtract(plint(this->first + x.first, this->second + x.second));
    }
    DoubleHash operator+(lint x) const
    {
        return mod_subtract(plint(this->first + x, this->second + x));
    }
    DoubleHash operator-(const DoubleHash &x) const
    {
        return mod_subtract(plint(this->first - x.first + MODs.first, this->second - x.second + MODs.second));
    }
    DoubleHash operator*(const DoubleHash &x) const
    {
        return make_pair(this->first * x.first % MODs.first, this->second * x.second % MODs.second);
    }
    DoubleHash operator*(lint x) const
    {
        return make_pair(this->first * x % MODs.first, this->second * x % MODs.second);
    }
};
plint DoubleHash::MODs = plint(1000000007, 998244353);
#line 2 "random/rand_nondeterministic.hpp"
#include <chrono>
#include <random>
using namespace std;

struct rand_int_
{
    using lint = long long;
    mt19937 mt;
    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)
    lint operator()(lint l, lint r) {
        uniform_int_distribution<lint> d(l, r - 1);
        return d(mt);
    }
} rnd;
#line 5 "random/test/rolling_hash.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
using namespace std;

int main()
{
    DoubleHash b(rnd(1, 1000000), rnd(1, 1000000));

    string T, P;
    cin >> T >> P;
    rolling_hash<DoubleHash> rh_T(T, b),rh_P(P, b);

    for (int l = 0; l < (int)(T.length() - P.length() + 1); l++)
    {
        if (rh_T.get_hash(l, l + P.length()) == rh_P.get_hash(0, P.length()))
        {
            cout << l << endl;
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

