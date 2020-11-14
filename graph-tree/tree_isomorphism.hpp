#pragma once
#include "modint.hpp"
// #include "number/modint_runtime.hpp"
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
