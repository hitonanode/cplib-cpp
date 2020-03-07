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


# :warning: graph-tree/tree_isomorphism.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#aea7f79aded53b9cdf48a7ce3f3ec60e">graph-tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph-tree/tree_isomorphism.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Depends on

* :heavy_check_mark: <a href="../modulus/modint_fixed.hpp.html">modulus/modint_fixed.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include "modulus/modint_fixed.hpp"
// #include "modulus/modint_runtime.hpp"
#include <chrono>
#include <utility>
#include <vector>
using namespace std;

// CUT begin
// Tree isomorphism with hashing （ハッシュによる木の同型判定）
// Dependence: ModInt or ModIntRuntime
// Reference: <https://snuke.hatenablog.com/entry/2017/02/03/054210>
// Verified: <https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044698> (ModInt)
//           <https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044745> (ModIntRuntime)
using mint = ModInt<1000000007>;
// using mint = ModIntRuntime;
// int ModIntRuntime::mod = 1000000007;
using DoubleHash = pair<mint, mint>;
struct UndirectedTree
{
    using Edges = vector<vector<int>>; // vector<set<int>>;
    int V;
    Edges e;
    UndirectedTree(int v) : V(v), e(v) {}
    void add_edge(int u, int v) {
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    static uint64_t splitmix64(uint64_t x) {
        // <https://codeforces.com/blog/entry/62393> <http://xorshift.di.unimi.it/splitmix64.c>
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    DoubleHash get_hash(DoubleHash x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return {splitmix64(x.first.val + FIXED_RANDOM), splitmix64(x.second.val + FIXED_RANDOM)};
    }

    static void add_hash(DoubleHash &l, const DoubleHash &r) {
        l.first += r.first, l.second += r.second;
    }
    static DoubleHash subtract_hash(const DoubleHash &l, const DoubleHash &r) {
        return {l.first - r.first, l.second - r.second};
    }

    vector<DoubleHash> hash; // hash of the tree, each node regarded as root
    vector<DoubleHash> hash_subtree; // hash of the subtree
    vector<DoubleHash> hash_par; // hash of the subtree whose root is parent[i], not containing i
    DoubleHash hash_p; // \in [1, hmod), should be set randomly
    DoubleHash hash_dfs1_(int now, int prv) {
        hash_subtree[now] = hash_p;
        for (auto nxt : e[now]) if (nxt != prv) add_hash(hash_subtree[now], hash_dfs1_(nxt, now));
        return get_hash(hash_subtree[now]);
    }
    void hash_dfs2_(int now, int prv) {
        add_hash(hash[now], hash_subtree[now]);
        if (prv >= 0) hash_par[now] = subtract_hash(hash[prv], get_hash(hash_subtree[now]));
        for (auto nxt : e[now]) if (nxt != prv) {
            DoubleHash tmp = subtract_hash(hash[now], get_hash(hash_subtree[nxt]));
            add_hash(hash[nxt], get_hash(tmp));
            hash_dfs2_(nxt, now);
        }
    }
    void build_hash(int root, int p1, int p2) {
        hash_p = make_pair(p1, p2);
        hash.resize(V), hash_subtree.resize(V), hash_par.resize(V);
        hash_dfs1_(root, -1);
        hash_dfs2_(root, -1);
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "modulus/modint_fixed.hpp"
#include <iostream>
#include <vector>
#include <set>

// CUT begin
template <int mod>
struct ModInt
{
    using lint = long long;
    static int get_mod() { return mod; }
    static int get_primitive_root() {
        static int primitive_root = 0;
        if (!primitive_root) {
            primitive_root = [&](){
                std::set<int> fac;
                int v = mod - 1;
                for (lint i = 2; i * i <= v; i++) while (v % i == 0) fac.insert(i), v /= i;
                if (v > 1) fac.insert(v);
                for (int g = 1; g < mod; g++) {
                    bool ok = true;
                    for (auto i : fac) if (ModInt(g).power((mod - 1) / i) == 1) { ok = false; break; }
                    if (ok) return g;
                }
                return -1;
            }();
        }
        return primitive_root;
    }
    int val;
    constexpr ModInt() : val(0) {}
    constexpr ModInt &_setval(lint v) { val = (v >= mod ? v - mod : v); return *this; }
    constexpr ModInt(lint v) { _setval(v % mod + mod); }
    explicit operator bool() const { return val != 0; }
    constexpr ModInt operator+(const ModInt &x) const { return ModInt()._setval((lint)val + x.val); }
    constexpr ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val - x.val + mod); }
    constexpr ModInt operator*(const ModInt &x) const { return ModInt()._setval((lint)val * x.val % mod); }
    constexpr ModInt operator/(const ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % mod); }
    constexpr ModInt operator-() const { return ModInt()._setval(mod - val); }
    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this + x; }
    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this - x; }
    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this * x; }
    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this / x; }
    friend constexpr ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a % mod + x.val); }
    friend constexpr ModInt operator-(lint a, const ModInt &x) { return ModInt()._setval(a % mod - x.val + mod); }
    friend constexpr ModInt operator*(lint a, const ModInt &x) { return ModInt()._setval(a % mod * x.val % mod); }
    friend constexpr ModInt operator/(lint a, const ModInt &x) { return ModInt()._setval(a % mod * x.inv() % mod); }
    constexpr bool operator==(const ModInt &x) const { return val == x.val; }
    constexpr bool operator!=(const ModInt &x) const { return val != x.val; }
    bool operator<(const ModInt &x) const { return val < x.val; }  // To use std::map<ModInt, T>
    friend std::istream &operator>>(std::istream &is, ModInt &x) { lint t; is >> t; x = ModInt(t); return is; }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { os << x.val;  return os; }
    constexpr lint power(lint n) const {
        lint ans = 1, tmp = this->val;
        while (n) {
            if (n & 1) ans = ans * tmp % mod;
            tmp = tmp * tmp % mod;
            n /= 2;
        }
        return ans;
    }
    constexpr lint inv() const { return this->power(mod - 2); }
    constexpr ModInt operator^(lint n) const { return ModInt(this->power(n)); }
    constexpr ModInt &operator^=(lint n) { return *this = *this ^ n; }

    inline ModInt fac() const {
        static std::vector<ModInt> facs;
        int l0 = facs.size();
        if (l0 > this->val) return facs[this->val];

        facs.resize(this->val + 1);
        for (int i = l0; i <= this->val; i++) facs[i] = (i == 0 ? ModInt(1) : facs[i - 1] * ModInt(i));
        return facs[this->val];
    }

    ModInt doublefac() const {
        lint k = (this->val + 1) / 2;
        if (this->val & 1) return ModInt(k * 2).fac() / ModInt(2).power(k) / ModInt(k).fac();
        else return ModInt(k).fac() * ModInt(2).power(k);
    }

    ModInt nCr(const ModInt &r) const {
        if (this->val < r.val) return ModInt(0);
        return this->fac() / ((*this - r).fac() * r.fac());
    }

    ModInt sqrt() const {
        if (val == 0) return 0;
        if (mod == 2) return val;
        if (power((mod - 1) / 2) != 1) return 0;
        ModInt b = 1;
        while (b.power((mod - 1) / 2) == 1) b += 1;
        int e = 0, m = mod - 1;
        while (m % 2 == 0) m >>= 1, e++;
        ModInt x = power((m - 1) / 2), y = (*this) * x * x;
        x *= (*this);
        ModInt z = b.power(m);
        while (y != 1) {
            int j = 0;
            ModInt t = y;
            while (t != 1) j++, t *= t;
            z = z.power(1LL << (e - j - 1));
            x *= z, z *= z, y *= z;
            e = j;
        }
        return ModInt(std::min(x.val, mod - x.val));
    }
};

// constexpr lint MOD = 998244353;
// using mint = ModInt<MOD>;
#line 3 "graph-tree/tree_isomorphism.hpp"
// #include "modulus/modint_runtime.hpp"
#include <chrono>
#include <utility>
#include <vector>
using namespace std;

// CUT begin
// Tree isomorphism with hashing （ハッシュによる木の同型判定）
// Dependence: ModInt or ModIntRuntime
// Reference: <https://snuke.hatenablog.com/entry/2017/02/03/054210>
// Verified: <https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044698> (ModInt)
//           <https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044745> (ModIntRuntime)
using mint = ModInt<1000000007>;
// using mint = ModIntRuntime;
// int ModIntRuntime::mod = 1000000007;
using DoubleHash = pair<mint, mint>;
struct UndirectedTree
{
    using Edges = vector<vector<int>>; // vector<set<int>>;
    int V;
    Edges e;
    UndirectedTree(int v) : V(v), e(v) {}
    void add_edge(int u, int v) {
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    static uint64_t splitmix64(uint64_t x) {
        // <https://codeforces.com/blog/entry/62393> <http://xorshift.di.unimi.it/splitmix64.c>
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    DoubleHash get_hash(DoubleHash x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return {splitmix64(x.first.val + FIXED_RANDOM), splitmix64(x.second.val + FIXED_RANDOM)};
    }

    static void add_hash(DoubleHash &l, const DoubleHash &r) {
        l.first += r.first, l.second += r.second;
    }
    static DoubleHash subtract_hash(const DoubleHash &l, const DoubleHash &r) {
        return {l.first - r.first, l.second - r.second};
    }

    vector<DoubleHash> hash; // hash of the tree, each node regarded as root
    vector<DoubleHash> hash_subtree; // hash of the subtree
    vector<DoubleHash> hash_par; // hash of the subtree whose root is parent[i], not containing i
    DoubleHash hash_p; // \in [1, hmod), should be set randomly
    DoubleHash hash_dfs1_(int now, int prv) {
        hash_subtree[now] = hash_p;
        for (auto nxt : e[now]) if (nxt != prv) add_hash(hash_subtree[now], hash_dfs1_(nxt, now));
        return get_hash(hash_subtree[now]);
    }
    void hash_dfs2_(int now, int prv) {
        add_hash(hash[now], hash_subtree[now]);
        if (prv >= 0) hash_par[now] = subtract_hash(hash[prv], get_hash(hash_subtree[now]));
        for (auto nxt : e[now]) if (nxt != prv) {
            DoubleHash tmp = subtract_hash(hash[now], get_hash(hash_subtree[nxt]));
            add_hash(hash[nxt], get_hash(tmp));
            hash_dfs2_(nxt, now);
        }
    }
    void build_hash(int root, int p1, int p2) {
        hash_p = make_pair(p1, p2);
        hash.resize(V), hash_subtree.resize(V), hash_par.resize(V);
        hash_dfs1_(root, -1);
        hash_dfs2_(root, -1);
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

