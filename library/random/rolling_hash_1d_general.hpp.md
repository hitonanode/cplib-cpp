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


# :x: random/rolling_hash_1d_general.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7ddf32e17a6ac5ce04a8ecbf782ca509">random</a>
* <a href="{{ site.github.repository_url }}/blob/master/random/rolling_hash_1d_general.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Verified with

* :x: <a href="../../verify/random/test/rolling_hash.test.cpp.html">random/test/rolling_hash.test.cpp</a>
* :x: <a href="../../verify/random/test/rolling_hash_w_modint.test.cpp.html">random/test/rolling_hash_w_modint.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <string>
#include <vector>
using namespace std;

// CUT begin
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "random/rolling_hash_1d_general.hpp"
#include <string>
#include <vector>
using namespace std;

// CUT begin
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

